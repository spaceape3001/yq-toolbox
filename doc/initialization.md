#  Initialization

## Logging Initialization

Logging capabilities can be enabled at the start of main.

```
#include <yq/core/Logging.hpp>

int main(int argc, char* argv[])
{
    yq::log_to_std_error();         // <-- Call to enable logging to standard error
    yq::log_to_std_output();        // <-- Call to enable logging to standard output
    yq::log_to_file("myfile.log");  // <-- Call to enable logging to file
}
```

The standard error/output are not mutually exclusive, anybody who loves their console output filled up with log messages can do both!

## Delayed Initialization



## Plugins

## Meta Initialization


