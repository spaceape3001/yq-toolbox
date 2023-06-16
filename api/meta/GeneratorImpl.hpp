////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/Generator.hpp>
#include <meta/TypedArgInfo.hpp>
#include <meta/MetaWriter.hpp>
#include <trait/indices.hpp>

namespace yq {
    
    template <typename...> 
    struct GeneratorInfo::DefineArg {
        static void    define(const std::source_location&, GeneratorInfo*, options_t)
        {
        }
    };
    
    template <typename T, typename... Args> 
    struct GeneratorInfo::DefineArg<T, Args...> {
        static void    define(const std::source_location&sl, GeneratorInfo*parent, options_t options)
        {
            using act_type  = std::remove_cvref_t<T>;
            parent->m_arguments.push_back( new ArgInfo::Typed<act_type>(sl, parent, options));
            DefineArg<Args...>::define(sl, parent, options);
        }
    };

    template <typename...Args> 
    void GeneratorInfo::define_signature(options_t opts)
    {
        DefineArg<Args...>::define(source(), this, opts);
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
    
        SpecificGenerator(std::string_view zName, FN fn, const std::source_location& sl, Meta::options_t opts=0) : 
            Generator<G>(zName, sl, opts), m_function(fn)
        {
            GeneratorInfo::define_signature<Args...>(opts);
        }
        
    private:
        virtual std::error_code _create(void* res, const void* const * args) const override final
        {
            return impl::createGenerator(*(G*) res, m_function, args, indices_gen<ARG_COUNT>());
        }
        
        FN  m_function;
    };
    
    class GeneratorInfo::Writer : public Meta::Writer {
    public:
        
        Writer  argument(std::string_view zName, std::string_view zDescription=std::string_view(), options_t opts=0);
        Writer(GeneratorInfo* obj);
        Writer(GeneratorInfo& obj);
        
    private:
        size_t  m_arg   = 0;
    };

    template <typename G, typename ... Args>
    GeneratorInfo::Writer   register_generator(std::string_view n, G (*fn)(Args...), const std::source_location&sl=std::source_location::current())
    {
        return GeneratorInfo::Writer(new SpecificGenerator<G,Args...>(n, fn, sl));
    }
        
}

