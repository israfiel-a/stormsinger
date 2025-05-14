#include <Chainbinder.h>
#include <Reporting.h>
#include <stdio.h>

#ifdef __GNUC__

#include <sys/wait.h>
#include <unistd.h>
static const int chainbinderPermissions[] = {
    R_OK, W_OK, X_OK, R_OK | W_OK, R_OK | W_OK | X_OK, F_OK};

#else

#include <io.h>
#include <windows.h>
// Microsoft's way of doing this is archaic at BEST.
static const int chainbinderPermissions[] = {4, 2, 0, 6, 0, 0};

#define access _access

#endif // __GNUC__

bool Chainbinder_FileExists(const char *const filename)
{
    return access(filename, chainbinderPermissions[CHAINBINDER_EXISTS]) ==
           0;
}

bool Chainbinder_FileExecutable(const char *const fileName)
{
#ifdef __GNUC__
    return access(fileName, chainbinderPermissions[CHAINBINDER_EXECUTE]) ==
           0;
#else
    return GetBinaryTypeA(fileName, CHAINBINDER_NULLPTR) != 0;
#endif
}

int Chainbinder_Execute(const char *fileName, char **argv)
{
    if (!Chainbinder_FileExists(fileName))
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to execute ghost file '%s'.", fileName);
        return -1;
    }
    if (!Chainbinder_FileExecutable(fileName))
    {
        Chainbinder_Log(
            CHAINBINDER_WARNING,
            "Tried to execute file without proper permissions.");
        return -1;
    }

#ifdef __GNUC__

    pid_t pid = fork();
    if (pid == -1)
    {
        Chainbinder_Log(CHAINBINDER_ERROR, "Failed to fork process.");
        return -1;
    }

    char *trueArgv[] = {
        (char *)fileName,
        (argv != CHAINBINDER_NULLPTR ? *argv : CHAINBINDER_NULLPTR)};
    // This is executed within the new process.
    if (pid == 0 && execve(fileName, trueArgv, CHAINBINDER_NULLPTR) == -1)
    {
        Chainbinder_Log(CHAINBINDER_ERROR, "Failed to execute file '%s'.",
                        fileName);
        return -1;
    }

    int status = 0;
    pid_t waitStatus = waitpid(pid, &status, 0);
    if (waitStatus == (pid_t)-1)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Unable to wait for process '%s'.", fileName);
        return -1;
    }

    if (!WIFEXITED(status))
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Process '%s' ended with an unexpected result.",
                        fileName);
        return -1;
    }
    return WEXITSTATUS(status);

#else
    // TODO: This needs to be implemented.
    (void)argv;

    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION processInfo;
    if (CreateProcess(fileName, CHAINBINDER_NULLPTR, CHAINBINDER_NULLPTR,
                      CHAINBINDER_NULLPTR, TRUE, 0, CHAINBINDER_NULLPTR,
                      CHAINBINDER_NULLPTR, &info, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        DWORD returnCode;
        GetExitCodeProcess(processInfo.hProcess, &returnCode);

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        return (int)returnCode;
    }
    else return -1;
#endif
}

bool Chainbinder_DeleteFile(const char *fileName)
{
    return remove(fileName) != -1;
}
