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

## External Dependencies

(more todo here)

### Log4cpp

[Log4cpp](https://log4cpp.sourceforge.net/)

## Branches

+ `master` is the main trunk, which should generally be buildable, usable, with all or most unit tests passing.
+ `dev` is the main development branch, it'll be merged with master when it meets the above criteria

# Configuration

(todo)

# Building

(todo)


