# Logging

Logging in this toolbox (and suite of repos) leverages [LOG4CPP](https://log4cpp.sourceforge.net).  It's a nice solid logger utility, simple to use as one expects it.

## Usage

General usage, create a log stream at chosen priority, pipe your description and other information to it.

```
#include <yq/core/Logging.hpp>

int main(int argc, char* argv[])
{
    yq::log_to_std_output();
    yCritical() << "Testing the logging system.";
    return 0;
}
```

There's a macro for each priority level.   Sublibraries will typically have a `logging.hpp` header that specializes the macros, ie

```
#pragma once
#include <yq/core/Logging.hpp>

#define libraryAlert        yAlert("library")
#define libraryCritical     yCritical("library")
#define libraryDebug        yDebug("library")
#define libraryEmergency    yEmergency("library")
#define libraryFatal        yFatal("library")
#define libraryInfo         yInfo("library")
#define libraryNotice       yNotice("library")
#define libraryWarning      yWarning("library")
```

Per convention, these get listed alphabetically in the header.

## Output Control

Built-in options for logging output are 
- Standard Output
- Standard Error
- A file

### Standard Output

To enable, it's a one line call at startup.
```
    yq::log_to_std_output(priority);    //< default priority is everything
```

### Standard Error

To enable, it's a one line call at startup.
```
    yq::log_to_std_error(priority);     //< default priority is everything
```

### File

To add a file, it's again a one line call at startup.
```
    yq::log_to_file(path, priority);    //< default priority is everything
```

### Custom

Custom output options can be created.  See Log4CPP about appenders, and appending it to the root (or sub) category.

```
    class MyCustomAppender;
    log4cpp::Category::getRoot().addAppender(new MyCustomAppender);
```

