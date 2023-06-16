////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/Meta.hpp>
#include <vector>
#include <span>

namespace yq {

    class GeneratorInfo : public Meta {
    public:
    
        class Writer;
        const std::vector<const ArgInfo*>& arguments() const { return m_arguments; }
    
    protected:
        std::vector<const ArgInfo*> m_arguments;

        struct Repo;
        static Repo*    newRepo();

        GeneratorInfo(std::string_view zName, const std::source_location& sl, options_t opts=0);
        
        static const std::vector<const GeneratorInfo*>&     all(Repo&);
        static const GeneratorInfo*                         find(Repo&, std::string_view);
        static void                                         register_me(Repo&, const GeneratorInfo*);

        template <typename...> struct DefineArg;
        template <typename...> void define_signature(options_t options=0);
        
        std::error_code         create(void*, std::span<const Any> args) const;
        virtual std::error_code _create(void* res, const void* const * args) const = 0;
        
        void    fill_argument_info(size_t, std::string_view zName, std::string_view zDescription, options_t opts);
    };

    /*! \brief Generator is about creating helpers or similar things
    */
    template <typename G>
    class Generator : public GeneratorInfo {
    public:
        Expect<G>       create(std::span<const Any> args) const
        {
            G           ret = G{};
            std::error_code ec  = GeneratorInfo::create(&ret, args);
            if(ec)
                return unexpected(ec);
            return ret;
        }
        
        static std::span<const Generator*>  all()
        {
            const auto& ret = GeneratorInfo::all(*repo());
            return std::span<const Generator*>( (const Generator*) ret.data(), ret.size());
        }
        
        static const Generator*             lookup(std::string_view k)
        {
            return static_cast<const Generator*>(GeneratorInfo::find(*repo(), k));
        }
        
    private:
        static Repo*    repo()
        {
            static Repo*    ret   = newRepo();
            return ret;
        }
    };
}
