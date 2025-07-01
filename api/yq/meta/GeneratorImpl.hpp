////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/Generator.hpp>
#include <yq/meta/TypedArgMeta.hpp>
#include <yq/meta/MetaWriter.hpp>
#include <yq/trait/indices.hpp>

namespace yq {
    
    template <typename...> 
    struct GeneratorMeta::DefineArg {
        static void    define(const std::source_location&, GeneratorMeta*)
        {
        }
    };
    
    template <typename T, typename... Args> 
    struct GeneratorMeta::DefineArg<T, Args...> {
        static void    define(const std::source_location&sl, GeneratorMeta*parent)
        {
            using act_type  = std::remove_cvref_t<T>;
            parent->m_arguments.push_back( new ArgMeta::Typed<act_type>(sl, parent));
            DefineArg<Args...>::define(sl, parent);
        }
    };

    template <typename...Args> 
    void GeneratorMeta::define_signature()
    {
        DefineArg<Args...>::define(source(), this);
    }

    namespace impl {
        template <typename G, typename...Args, unsigned... Is>
        std::error_code   createGenerator(G& res, G(*fn)(Args...), const void* const * args, indices<Is...>)
        {
            try {
                res     = (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            }
            catch(std::error_code ec)
            {
                return ec;
            }
        }
    }

    template <typename G, typename ... Args>
    class SpecificGenerator : public Generator<G> {
    public:
        
        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);
        typedef G (*FN)(Args...);
    
        SpecificGenerator(std::string_view zName, FN fn, const std::source_location& sl) : 
            Generator<G>(zName, sl), m_function(fn)
        {
            GeneratorMeta::define_signature<Args...>();
        }
        
    private:
        virtual std::error_code _create(void* res, const void* const * args) const override final
        {
            return impl::createGenerator(*(G*) res, m_function, args, indices_gen<ARG_COUNT>());
        }
        
        FN  m_function;
    };
    
    class GeneratorMeta::Writer : public Meta::Writer {
    public:
        
        Writer  argument(std::string_view zName, std::string_view zDescription=std::string_view());
        Writer(GeneratorMeta* obj);
        Writer(GeneratorMeta& obj);
        
    private:
        size_t  m_arg   = 0;
    };

    template <typename G, typename ... Args>
    GeneratorMeta::Writer   register_generator(std::string_view n, G (*fn)(Args...), const std::source_location&sl=std::source_location::current())
    {
        return GeneratorMeta::Writer(new SpecificGenerator<G,Args...>(n, fn, sl));
    }
        
}

