#include <type_traits>
#include <string_view>

template <class T>
concept Enumerated = requires {
    std::is_enum_v<T>;
};

template <Enumerated> 
struct EnumeratedData {
    static constexpr const char*  szName          = "";
    static constexpr const char*  szDefinition    = "";
};

#define ENUMERATION(name, ...)                              \
    enum class name {                                       \
        __VA_ARGS__                                         \
    };                                                      \
    template<>                                              \
    struct EnumeratedData<name> {                           \
        static constexpr const char* szName           = #name;        \
        static constexpr const char* szDefinition    = #__VA_ARGS__;  \
    };

ENUMERATION(Color, Red, Green, Blue, Indigo)

template <Enumerated>
std::string_view    key(Enumerated);

template <Enumerated>
Enumerated          enumerated(std::string_view)

