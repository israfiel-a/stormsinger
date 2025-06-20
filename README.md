![top_banner](./.github/banner.jpg)

---

### Stormsinger
![workflow_badge](https://img.shields.io/github/actions/workflow/status/israfiel-a/stormsinger/build-test.yml?label=Build%20Test)
![loc_badge](https://github.com/israfiel-a/stormsinger/blob/badges/loc.svg)
![latest_stable_badge](https://img.shields.io/github/v/release/israfiel-a/stormsinger?label=Stable&color=blue)
![latest_unstable_badge](https://img.shields.io/github/v/release/israfiel-a/stormsinger?label=Experimental&include_preleases=true)

[![wiki_badge](https://img.shields.io/badge/Wiki-grey?logo=wikipedia&logoColor=lightGrey)](https://github.com/israfiel-a/stormsinger/wiki)
[![discord_badge](https://img.shields.io/badge/Discord-grey?logo=discord&logoColor=lightgrey)](https://discord.gg/uU5xQTkfpz)
[![bluesky_badge](https://img.shields.io/badge/Bluesky-grey?logo=bluesky&logoColor=lightgrey)](https://bsky.app/profile/israfilargos.bsky.social)
[![youtube_badge](https://img.shields.io/badge/Youtube-grey?logo=youtube&logoColor=lightgrey)](https://www.youtube.com/@IsrafilArgos)

---

Stormsinger is a small and simple infinite driving game (inspired by [the Long Drive](https://store.steampowered.com/app/1017180/The_Long_Drive/)) built off of my own engine and done as a side project. It's written entirely in [C23](https://en.wikipedia.org/wiki/C23_(C_standard_revision)), and runs well on both [Microsoft Windows](https://www.microsoft.com/en-us/download/windows) and most graphical distributions of [Linux](https://kernel.org/). Stormsinger is named for the main angel in Vitiri theology, a being who's second only to Hekharam himself. It is split into three modules; [Abyssguard](./Abyssguard/README.md), the epithet used for the angelic guardian of the Realms, [Chainbinder](./Chainbinder/README.md), the title given to the angel of craftsmanship, and [Sunbringer](./Sunbringer/README.md), the name of the angel who holds the sun upon his charred back. 

In terms of engine functionality, Abyssguard is the code of the actual game, Chainbinder acts as the engine, and Sunbringer is the asset bundle(r). When the game launches for the first time, the Sunbringer folder is compressed into a [binary format](./Sunbringer/README.md#binary-archive) to be used during actual execution, and the folder is deleted. This game makes an attempt to be as small and memory-efficient as possible.

---

### Dependencies & Support
Stormsinger uses the [Vulkan rendering API](https://www.vulkan.org/) and the [GLFW windowing library](https://www.glfw.org/) to accomplish its work. Beyond those, it needs nothing but OS-provided components. Stormsinger supports Windows XP and later, if you've got a Vulkan-compatible graphics card (somehow). It also supports most graphical distributions of Linux, so long as your kernel is fairly recent, you have Vulkan drivers, and you've got [Wayland](https://wayland.freedesktop.org/) or [X11](https://www.x.org/wiki/) as a windowing system. MacOS is not supported, and not planned. 

Stormsinger builds using [CMake](https://cmake.org/), but it's not too complicated to build manually via something like raw [Makefiles](https://www.gnu.org/software/make/) or [Meson](https://mesonbuild.com/).

Tested architectures:
- Microsoft Windows 10
	- Visual Studio 2022 (cl)
		- x86_64 (Debug, Release)
		- x86_86 (Debug, Release)
- Linux
	- GCC @L v14.2.1
        - x86_64 WAYLAND (Debug, Release)

---

![bottom_banner](./.github/banner.jpg)
