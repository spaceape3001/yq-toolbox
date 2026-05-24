# CHANGE LOG

## Upcoming

* C++26 is the new standard, min GCC is 16.
* Removing the old enumeration stuff (`YQ_ENUM()`) in favor of reflection.  This will mean adding `YQ_ENUM_IMPLEMENT()` in places to instantiate the templates in source files. **WARNING enum class does not zero initialize by default!** 

## 2025.12.26

* Removing the `read_file(XmlDocument&, const std::filesystem::path&)` api.  This led to an inherent dangling pointer issue in the string views.   Use `file_bytes(const std::filesystem::path&)` and `parse_xml(XmlDocument&, ByteArray&)` instead, while making sure the ByteArray stay lives as long as you're examining the document.

## 2025.12.19

* Lua support

## 2025.07.19

* ObjectInfo renamed to ObjectMeta (toolbox-scoped), this is to allow for the use of "Info" to be specific to an instance.
* Asset Overhaul, more in the drivers & IO.  The new driver paradigm should be relatively close to previous (in the signature), but also allows for more driver signatures.  Some library support is present, though yet to be vetted (the motivation for this overhaul)
* Asset **RENAMED** to Resource (this is to clear the name for use in the vulkan code)

