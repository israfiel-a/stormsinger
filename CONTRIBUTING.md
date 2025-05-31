![top_banner](./.github/banner.jpg)

---

### Contributing
Stormsinger is open source. I *want* improvements, because I am *certainly* not the best programmer out there. If you want a system to be improved, improve it! I only have so much time and so much motivation, so I'll welcome your changes. However, I do have standards.

Table of contents:
- [Style](#style)
    - [Automatic Formatting](#automatic-formatting)
    - [File Names](#file-names)
- [Quality](#quality)
    - [Performance](#performance)
    - [Purpose](#purpose)
    - [Documentation](#documentation)

---

### Style
All code is expected to be held to the same styling standards, to ease things like static analysis and general readability. If you have a problem with the styling rules, you should [open an issue](https://github.com/israfiel-a/stormsinger/issues).

#### Automatic Formatting
A clang-format style document is provided alongside source code. This document details how exactly code should be styled automatically via the [Clang-format]() tool. This should be used to prevent the mistakes that come from manual styling. If you wish to create another document for a different styling tool, [open a pull request](https://github.com/israfiel-a/stormsinger/pulls).

#### File Names
Files are expected to be named concisely and purposefully. There is no true "character limit", nor word limit, but one should strive to keep the title of each file/folder to exact the context required. For example, the `Device.c` file in the `Vulkan` folder. On its own, one might call `Device.c` a fairly ambiguous filename. However, within the context of the `Vulkan` folder, one can figure out that it means "device" in the `VkDevice` way.

If the file contains a header guard, it must follow the following pattern: `[PACKAGE_NAME]_[PARENT_FOLDER]_[FILENAME]_H`. There is to be **no** deviation from this pattern, ever. If a file is moved or renamed, this guard must also be changed.

---

### Quality
This is not a shovelware slop project; all code contributed must at least have a certain level of quality to it. Must it be Linus Torvalds-Terry Davis quality? No. Must it be as good as you can make it? Yes.

#### Performance
Code is expected to be performant, at least within reason. I do not expect you to stare at a function for nine hours attempting to figure out how this algorithm could be implemented better, but if you have three nested `for` loops, maybe refactor. Singular functions should not take milliseconds, and it should be performant on **all** required OSes, at least by time of staging merge.

#### Purpose
All code must be purposeful. A purpose of "bug fix" is not nearly enough--I need your commit message to detail exactly the problem you've solved or portion you've changed. I need, in your pull request, a clear statement of purpose and intent, otherwise you simply will not be merged. End of story. It's truly not that difficult; a simple "fixed issue with \_\_\_ not working correctly on \_\_\_" would be enough. 

#### Documentation
All documentation must be in place before staging merge. This is non-negotiable. I do not want comment rot, but each segment of code shall be properly documented. Files must be documented, functions must be documented, and global variables must be documented. Any code whose purpose or side-effects is not immediately apparent must be documented. Documentation must also be formatted. For files:

```c
/**
 * @file [folder]/[filename].[extension]
 * @author [authors]
 * @brief [brief description]
 *
 * @since [version]
 * @updated [version]
 *
 * @copyright (c) [years] - the Stormsinger Project
 * This document is under the GNU Affero General Public License v3.0. It
 * can be modified and distributed (commercially or otherwise) freely, and
 * can be used privately and within patents. No liability or warranty is
 * guaranteed. However, on use, the user must state license and copyright,
 * any changes made, and disclose the source of the document. For more
 * information see the @file LICENSE.md file included with this
 * distribution of the source code, or https://www.gnu.org/licenses/agpl.
 */
```

For functions:

```c
/**
 * @brief [brief description]
 * @author [authors]
 *
 * @since [version]
 * @updated [version]
 *
 * @param [param name] [param description]
 * @returns [return description]
 * 
 * @see [related functions/variables]
 */
```

For global variables:

```c
/**
 * @brief [brief description]
 * @author [authors]
 * @since [version]
 */
```

Note that no update version is required for global variables. They're simply not consequential enough to require it--the only changes would be name changes, and documenting that would be rather ridiculous.

---

![bottom_banner](./.github/banner.jpg)
