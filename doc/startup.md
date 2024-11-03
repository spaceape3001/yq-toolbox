#  Startup


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

This toolbox and suite of applications emply the concept of delayed initialization.  This means that it isn't ran until explicitly called in the start of the main routine, which allows for configuration of things like loggers, plugins, etc.  Thus, for something with meta or similar registration, you'll see the same pattern.  

```
#include <yq/core/DelayInit.hpp>

void some_function()
{
}

static void reg_mycapability()
{
   auto w = writer<MyType>();
   w.description("My Type");
   
   reg_some_capability("really neat", &some_function);
}

YQ_INVOKE(reg_mycapability();)

```
 
The `YQ_INVOKE()` macro is a variable argument, pastes its contents into a lambda function to be called.  For clarity and debugging, the contents are typically kept to a single function call, hence the semicolon `;` in the invocation. 

A daisy chain of these hooks is created when the program or a plugin is loaded.  Some meta might also spawn off further delay initializations.  However, they are not run until `DelayInit::init_all()` is called.

## Plugins

## Meta Initialization

For objects, if the class has `init_info()` defined, it will be called (ie, it will be automatically inserted into delay initialization system).

## PID Files

## Example

Putting the above together, the typical startup will look something like the following.

```
#include <yq/core/BasicApp.hpp>             //< For basic application support
#include <yq/core/DelayInit.hpp>
#include <yq/core/Logging.hpp>              //< Logging support
#include <yq/meta/Meta.hpp>                 //< Lots of things use meta
#include <yq/process/PidFile.hpp>           //< If you want to guard against multiple launches
#include <yq/process/PluginLoader.hpp>      //< If you have plugins

int main(int argc, char* argv[])
{
    yq::log_to_std_error();                 //< Usually the easiest
    yq::log_to_file("myfile.log);           //< Recording it to a file
    
    yq::DelayInit::init_all();              //< Runs uninvoked YQ_INVOKE() macros
                                            //< Also, implicitly ran by Meta::init
    
    yq::PidFile   pid("myapp.pid");         //< Records our PID into a file
    if(!pid.first()){
        //  Is it a problem we're not the only instance?  If so, complain/bail/whatever.
    }
    
    yq::Meta::init();                       //< Sweeps to build out the meta
    
    yq::BasicApp  app(argc, argv);          //< Tachyon has a different application, still, same idea
    
    yq::load_plugin("some_plugin.so");      //< Load a specific plugin
    yq::load_plugin_dir("some_plugin_dir"); //< Load *that* directory (it's not recursive)
    
    yq::Meta::freeze();                     //< Done building meta, disallow modifications
}

```

