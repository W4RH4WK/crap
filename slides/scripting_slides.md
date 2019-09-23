% Scripting & co
% Alex Hirsch

# Scripting Language

## Don't need that, I already know Java!

- Using the right tool for the right job
- Productivity

## Example Task

- Read in XML containing URLs
- Visit each URL
  - Parse the received HTML output
  - Read the received JSON output
- Do some aggregation
- Store results in a PostgreSQL database

---

- Student using Java as taught by the University
  - Creates an object hierarchy for all the data
  - Uses dedicated serialisation classes for XML / HTML / JSON
  - Uses multiple bloated third-party libraries by copy-pasting JARs around
  - Uses hibernate for database interaction
  - Provides GUI for selecting XML input and database configuration
  - Lines of code: ~ 2500
  - Total development time: 1 month

---

- Engineer knowing Python
  - Uses Dictionaries (key-value collection) for all the data
  - Comes with XML / JSON reader
  - Practical third-party libraries: Requests, Beautiful Soup, …
  - Uses command-line parameters / hard-coded values
  - Lines of code: ~ 300
  - Total development time: 2–4 hours

---

Who is right?

## Limitations

- Dynamic typing
  - Easy to develop / prototype
  - Hard to maintain / refactor
  - Typically requires lots of tests (see average Ruby library)
- Performance
  - Typically higher memory consumption
  - Not trivial to parallelise (see GIL)

## Benefits

- Batteries included
  - Standard library to deal with common problems
- Fast prototyping
  - REPL (read-evaluate-print loop)
  - Hot-reload
- Typically come with package managers (pip, gem, npm, …)
  - Big selection of third-party libraries

## Should I learn a Scripting Language?

YES!

- Certain tasks are easily solvable via scripting languages
- Not every program needs to be rock solid
- …

Okay, which one?

## Meet Python

- Probably your go-to scripting language nowadays
- Lots of programs provide interfaces for Python
- Language can be a bit obscure, but it works
- Third-party packages usually make the right trade-offs
- Commonly used in data science (slowly replacing R)
- Commonly used in statistics and machine learning

## Meet Ruby

- Smaller footprint than Python
- More language-level features (e.g. RegEx)
- Third-party packages typically feature good test coverage

## Meet JavaScript

Don't — it's a mess!

## Alternatives to consider

- Go
  - Statically typed, but fast compile times
  - Useful standard library, good ecosystem
  - Good performance
  - Easier to parallelise
  - No decent package manager (yet)

---

- Haskell
  - Extremely expressive
  - Even complex solutions remain readable
  - Good type-system
  - Sometimes requires deeper theoretical knowledge to be useful
  - Tooling not as good

## Getting Started

- Various tutorials / tours available online
- Editor / IDE integration
- Always use a linter
- Look at top solutions for programming challenges
- Be sure to know what is provided (standard / third-party libraries)
  - Aim for very broad knowledge

# Shell Scripting (Bash)

## Another Scripting Language?

- Shell is not really suitable for complex logic
- However, very useful to combine multiple small programs / tools
- Very extensible
- You become more efficient using the command-line
- Good tool to have at your disposal

Many problems can be solved by combining programs that have already been written.

## Bash Script Example 1

[Integration Test Runner](https://git.uibk.ac.at/c7031162/mcc/blob/master/scripts/run_integration_tests)

- Used in compiler construction

## Bash Script Example 2

[DIFAS](https://github.com/w4rh4wk/difas)

Dependency Installer for Archaic Systems

- Tiny set of Bash scripts
- Easily extensible
- Inspired by Arch's PKGBUILD

## What to watch out for

- Lot's of obscure features that should probably be avoided
- Read up on best practices
- Use ShellCheck
- Don't over-do it!

# Package Manager

## About Package Managers

- Manages software (versions)
  - Install / Remove
  - Update
  - Deal with dependencies
  - …
- Can be used to manage project dependencies
- Typically verifies downloaded package checksum / signature

---

- System package managers
  - dpkg
  - rpm
  - …
- Language specific package managers
  - pip
  - gem
  - npm
  - …

## Language specific package managers

- Can operate on a user / project level
- Often integrate with the build process (see Rust's Cargo)
- Gives you access to lots of useful third-party software

## Package Manager Example

    $ sudo apt install cmatrix
    Reading package lists... Done
    Building dependency tree
    Reading state information... Done
    Suggested packages:
      cmatrix-xfont
    The following NEW packages will be installed:
      cmatrix
    0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
    Get:1 http://archive.ubuntu.com/ubuntu bionic/universe amd64 cmatrix amd64 1.2a-5build3 [16.1 kB]
    Fetched 16.1 kB in 0s (81.2 kB/s)
    Preparing to unpack .../cmatrix_1.2a-5build3_amd64.deb ...
    Unpacking cmatrix (1.2a-5build3) ...
    Setting up cmatrix (1.2a-5build3) ...
    Processing triggers for man-db (2.8.3-2ubuntu0.1) ...

---

    $ apt show cmatrix
    Package: cmatrix
    Version: 1.2a-5build3
    Priority: optional
    Section: universe/misc
    Origin: Ubuntu
    Maintainer: Ubuntu Developers <ubuntu-devel-discuss@lists.ubuntu.com>
    Original-Maintainer: Diego Fernández Durán <diego@goedi.net>
    Bugs: https://bugs.launchpad.net/ubuntu/+filebug
    Installed-Size: 49.2 kB
    Depends: libc6 (>= 2.4), libncurses5 (>= 6), libtinfo5 (>= 6)
    Recommends: kbd
    Suggests: cmatrix-xfont
    Homepage: http://www.asty.org/cmatrix/

---

    $ apt depends cmatrix
    cmatrix
      Depends: libc6 (>= 2.4)
      Depends: libncurses5 (>= 6)
      Depends: libtinfo5 (>= 6)
      Recommends: kbd
      Suggests: cmatrix-xfont

---

    $ apt depends firefox
    firefox
      Depends: lsb-release
      Depends: libatk1.0-0 (>= 1.12.4)
      Depends: libc6 (>= 2.27)
      Depends: libcairo-gobject2 (>= 1.10.0)
      Depends: libcairo2 (>= 1.10.0)
      Depends: libdbus-1-3 (>= 1.9.14)
      Depends: libdbus-glib-1-2 (>= 0.78)
      Depends: libfontconfig1 (>= 2.12)
      Depends: libfreetype6 (>= 2.3.5)
      Depends: libgcc1 (>= 1:4.2)
      Depends: libgdk-pixbuf2.0-0 (>= 2.22.0)
      Depends: libglib2.0-0 (>= 2.31.8)
      Depends: libgtk-3-0 (>= 3.4)
      Depends: libpango-1.0-0 (>= 1.22.0)
      Depends: libpangocairo-1.0-0 (>= 1.14.0)
      Depends: libstartup-notification0 (>= 0.8)
      Depends: libstdc++6 (>= 6)
      Depends: libx11-6
      Depends: libx11-xcb1
      Depends: libxcb-shm0
      Depends: libxcb1
      Depends: libxcomposite1 (>= 1:0.3-1)
      Depends: libxdamage1 (>= 1:1.1)
      Depends: libxext6
      Depends: libxfixes3
      Depends: libxrender1
      Depends: libxt6
      Recommends: xul-ext-ubufox
      Recommends: libcanberra0
      Recommends: libdbusmenu-glib4
      Recommends: libdbusmenu-gtk3-4
      Suggests: fonts-lyx
      Replaces: <kubuntu-firefox-installer>

## Creating Packages (System)

- Not trivial
  - Obscure tooling, outdated documentation
- Lots of things to consider
  - Dependencies
  - Version bounds
  - Licence
  - …
- Pays off for deploying larger, more complicated applications
- Typically requires self-hosted repository

## Creating Packages (Language Specific)

- Much easier
  - Good documentation
  - Lots of examples
- Often encouraged by the community
- Integrates with the build process
- Repositories open for everyone (e.g. Python Package Index)

## Main Advantages

- Keeps everything organized
  - Files
  - Which packages are no longer needed
- Normally only *one* installed version per package
  - Good code reuse
  - Easy to update / fix security issues
- Repository managed by your distribution vendor
  - They are usually more concerned about your well being than software authors

---

Compare this to your average Windows / Mac install experience:

- No signature checks (unless it's a driver)
- Manually interacting with the installer
- Brings along all dependencies
  - You rely on the author to ship updates of dependencies
- Annoying auto-updaters

# Exercises

## New Scripting Language

- Pick up a new scripting language
- Critically think about its good and bad parts
- Is it a useful addition to your skill set?

## Shell Scripting

- Learn the basics of Bash scripting
- Critically think about its limitations
- Think about the criteria for deciding when to use Shell / scripting language

## Using a Package Manager

- Play around with your system's package manager
- Create a small package using your newly learned scripting language and its associated package manager

## Reading Material

- [Bash Scripting Tutorial for Beginners](https://linuxconfig.org/bash-scripting-tutorial-for-beginners)
- [Pure Bash Bible](https://github.com/dylanaraps/pure-bash-bible)
- [Fedora Package Management System](https://fedoraproject.org/wiki/Package_management_system)
