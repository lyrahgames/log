<h1 align="center">
    Lyrahgames' Simple Log Package
</h1>

<p align="center">
    C++ Header-Only Library Implementing a Really Simple Logging Mechanism
</p>

## Development Status

<p align="center">
    <img src="https://img.shields.io/github/languages/top/lyrahgames/log.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/languages/code-size/lyrahgames/log.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/repo-size/lyrahgames/log.svg?style=for-the-badge">
    <a href="COPYING.md">
        <img src="https://img.shields.io/github/license/lyrahgames/log.svg?style=for-the-badge&color=blue">
    </a>
</p>

<b>
<table align="center">
    <tr>
        <td>
            master
        </td>
        <td>
            <a href="https://github.com/lyrahgames/log">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/log/master.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <!-- <td>
            <a href="https://circleci.com/gh/lyrahgames/log/tree/master"><img src="https://circleci.com/gh/lyrahgames/log/tree/master.svg?style=svg"></a>
        </td> -->
        <!-- <td>
            <a href="https://codecov.io/gh/lyrahgames/log">
              <img src="https://codecov.io/gh/lyrahgames/log/branch/master/graph/badge.svg" />
            </a>
        </td> -->
        <td>
            <a href="https://ci.stage.build2.org/?builds=lyrahgames-log&pv=&tc=*&cf=&mn=&tg=&rs=*">
                <img src="https://img.shields.io/badge/b|2 ci.stage.build2.org-Click here!-blue">
            </a>
        </td>
    </tr>
    <!-- <tr>
        <td>
            develop
        </td>
        <td>
            <a href="https://github.com/lyrahgames/log/tree/develop">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/log/develop.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <td>
            <a href="https://circleci.com/gh/lyrahgames/log/tree/develop"><img src="https://circleci.com/gh/lyrahgames/log/tree/develop.svg?style=svg"></a>
        </td>
        <td>
            <a href="https://codecov.io/gh/lyrahgames/log">
              <img src="https://codecov.io/gh/lyrahgames/log/branch/develop/graph/badge.svg" />
            </a>
        </td>
    </tr> -->
    <tr>
        <td>
        </td>
    </tr>
    <tr>
        <td>
            Current
        </td>
        <td>
            <a href="https://github.com/lyrahgames/log">
                <img src="https://img.shields.io/github/commit-activity/y/lyrahgames/log.svg?logo=github&logoColor=white">
            </a>
        </td>
        <!-- <td>
            <img src="https://img.shields.io/github/release/lyrahgames/log.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/release-pre/lyrahgames/log.svg?label=pre-release&logo=github&logoColor=white">
        </td> -->
        <td>
            <img src="https://img.shields.io/github/tag/lyrahgames/log.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/tag-date/lyrahgames/log.svg?label=latest%20tag&logo=github&logoColor=white">
        </td>
        <!-- <td>
            <a href="https://queue.cppget.org/log">
                <img src="https://img.shields.io/website/https/queue.cppget.org/log.svg?down_message=empty&down_color=blue&label=b|2%20queue.cppget.org&up_color=orange&up_message=running">
            </a>
        </td> -->
    </tr>
</table>
</b>

## Requirements
<b>
<table>
    <tr>
        <td>Language Standard:</td>
        <td>C++20</td>
    </tr>
    <tr>
        <td>Compiler:</td>
        <td>
            GCC | Clang
        </td>
    </tr>
    <tr>
        <td>Build System:</td>
        <td>
            <a href="https://build2.org/">build2</a>
        </td>
    </tr>
    <tr>
        <td>Operating System:</td>
        <td>
            Linux
        </td>
    </tr>
    <tr>
        <td>Dependencies:</td>
        <td>
            <a href="http://github.com/build2-packaging/fmt">
                fmt
            </a><br>
            <a href="http://github.com/lyrahgames/xstd">
                lyrahgames-xstd
            </a>
        </td>
    </tr>
</table>
</b>

## Getting Started

```c++
#include <lyrahgames/log/log.hpp>

using namespace lyrahgames;

int main() {
  log::log log{};
  // log.quiet = true;
  log.info("This is an information for the user.");
  log.warning("This is a warning.");
  log.error("This is an error.");
}

```

## Usage with build2
Add this repository to the `repositories.manifest` file of your build2 package.

    :
    role: prerequisite
    location: https://github.com/lyrahgames/log.git

Add the following entry to the `manifest` file with a possible version dependency.

    depends: lyrahgames-log

Add these entries to your `buildfile`.

    import libs = lyrahgames-log%lib{lyrahgames-log}
    exe{your-executable}: {hxx cxx}{**} $libs


## Installation
The standard installation process will only install the header-only library with some additional description, library, and package files.

    bpkg -d build2-packages cc \
      config.install.root=/usr/local \
      config.install.sudo=sudo

Get the latest package release and build it.

    bpkg build https://github.com/lyrahgames/log.git

Install the built package.

    bpkg install lyrahgames-log

For uninstalling, do the following.

    bpkg uninstall lyrahgames-log

If your package uses an explicit `depends: lyrahgames-log` make sure to initialize this dependency as a system dependency when creating a new configuration.

    bdep init -C @build cc config.cxx=g++ "config.cxx.coptions=-O3" -- "?sys:lyrahgames-log/*"

## Alternative Usage
To use other build systems or manual compilation, you only have to add the `lyrahgames/log/` directory to your project and include it in the compilation process.

