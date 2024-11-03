This toolbox is generally a Linux based project.  It's designed to be separable from the rest of the projects here, in that it can be download and built in isolation, or be part of a larger project.

# Setup

GIT is your friend here, use `git clone`.  

## Directory Layout

Suggested, though not required, is a common directory with separate sub-folders for source, debug, & release builds.

```
me@machine ~/code/toolbox/master % ls -l
total 12
drwxr-xr-x 12 me me 4096 Oct 30 08:39 Debug
drwxr-xr-x 12 me me 4096 Oct 30 08:44 Release
drwxr-xr-x 13 me me 4096 Oct 28 06:54 src
```
The cmake, as provided, will deduce the build type from the directory name.

## Branches

+ `master` is the main trunk, which should generally be buildable, usable, with all or most unit tests passing.
+ `dev` is the main development branch, it'll be merged with master when it meets the above criteria

# Configuration

This toolbox is laid out on the assumption it'll be included with another project.  However, it's also designed to be standalone too (ie just checking it out, maintaining on it).

## local.cmake

If there's any local configuration, a good spot is `local.cmake`.  This file is included by `CMakeLists.txt` but excluded in `.gitignore`, and is read in prior to `configure.cmake` (below).  Build flags can be defined here.

## configure.cmake

This is the general configuration for the toolbox, including the `C++` standard, warnings, packages, etc.  When using the toolbox within another project, it's expected that project will include `configure.cmake` early on in its `CMakeLists.txt`.

## Build Flags

As the toolbox is generalized, however, there are times when the binding needs to be tight for specific use cases, this is where the build flags come in.  Define these prior to including `configure.cmake`.

If you're lazy, want it all, define:

    SET(Build_ALL ON)

### ASIO

For ASIO (network socket library) compability.

    SET(Build_ASIO ON)
    
### CURL

For CURL support

    SET(Build_CURL ON)
    
### Doxygen

For Doxygen support

    SET(Build_Doxygen ON)

### GLM

For GLM support

    SET(Build_GLM ON)

### Qt6

For Qt6 support

    SET(Build_Qt6 ON)
    
### SDK

For SDK examples

    SET(Build_SDK ON)

### SqlLite3

For Sqlite3 support

    SET(Build_SQL ON)
    
### Timing

For build timing

    SET(Build_Timing ON)
    
### Unit Tests

For unit test support

    SET(Build_UnitTests ON)

### Vulkan

For vulkan support (well, it's mostly in the other library, unless things begin to move)

    SET(Build_Vulkan ON) 

# Building

(todo)


