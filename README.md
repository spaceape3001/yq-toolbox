# Your Quill's Toolbox

This is the general utility toolbox for my Your Quill project.  It's split into a separate repository so it can be used with other projects as it contains a nice meta system, math, and other miscellaneous utilities.

## Additional Information

### Building

Your Quill uses CMake for build management and C++23 as the language standard.  On linux, the build type is determined based on the final directory name (ie build/Debug vs build/Release).  

### Contributing

### Dependencies

* C++ 23 compiler (GCC 14 recommended)
* Intel TBB (thread building blocks)
* [Log4Cpp](https://log4cpp.sourceforge.net/) &mdash; O/S installed/package
* Curl &mdash; optional (to the toolbox)
* RapidXML &mdash; use the submodule!
* Boost-ext UT &mdash; submodule
* [NLohmann JSON](https://github.com/nlohmann/json) &mdash; submodule
* Sqlite3
* GLM &mdash; optional (to the toolbox)
* [PStreams](https://pstreams.sourceforge.net/) &mdash; bundled 
* Lua (optional)


