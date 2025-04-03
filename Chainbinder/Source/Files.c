#include <Chainbinder.h>

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

bool Chainbinder_FileExists(const char *filename)
{
    return access(filename, chainbinderPermissions[CHAINBINDER_EXISTS]) ==
           0;
}

bool Chainbinder_FileExecutable(const char *fileName)
{
#ifdef __GNUC__
    return access(fileName, chainbinderPermissions[CHAINBINDER_EXECUTE]) ==
           0;
#else
    return GetBinaryTypeA(fileName, CHAINBINDER_NULLPTR) != 0;
#endif
}

int Chainbinder_Execute(const char *fileName)
{
    if (!Chainbinder_FileExecutable(fileName)) return -1;

#ifdef __GNUC__
    pid_t pid = fork();
    if (pid < 0) return -1;
    int status = 0;
    (void)waitpid(pid, &status, 0);
    if (!WIFEXITED(status)) return -1;
    return WEXITSTATUS(status);
#else
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
