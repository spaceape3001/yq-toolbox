////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/Meta.hpp>
#include <vector>
#include <span>
#include <typeinfo>

namespace yq {

    class GeneratorMeta : public Meta {
    public:
    
        class Writer;
        const std::vector<const ArgMeta*>& arguments() const { return m_arguments; }
    
        static std::vector<std::string_view> generator_types();
    
    protected:
        std::vector<const ArgMeta*> m_arguments;

        struct Repo;
        static Repo*    newRepo(const char*);
        
        //! Adds a repo, if r is not null, returns the "current" repo otherwise
        static Repo*    addRepo(Repo* r=nullptr);

        GeneratorMeta(std::string_view zName, const std::source_location& sl);
        
        static const std::vector<const GeneratorMeta*>&     all(const Repo&);
        static const GeneratorMeta*                         find(const Repo&, std::string_view);
        static void                                         register_me(Repo&, const GeneratorMeta*);

        template <typename...> struct DefineArg;
        template <typename...> void define_signature();
        
        std::error_code         create(void*, std::span<const Any> args) const;
        virtual std::error_code _create(void* res, const void* const * args) const = 0;
        
        void    fill_argument_info(size_t, std::string_view zName, std::string_view zDescription);
    };

    /*! \brief Generator is about creating helpers or similar things
    */
    template <typename G>
    class Generator : public GeneratorMeta {
    public:
        Expect<G>       create(std::span<const Any> args) const
        {
            G           ret = G{};
            std::error_code ec  = GeneratorMeta::create(&ret, args);
            if(ec)
                return unexpected(ec);
            return ret;
        }
        
        static std::span<const Generator*>  all()
        {
            const auto& ret = GeneratorMeta::all(*repo());
            return std::span<const Generator*>( (const Generator*) ret.data(), ret.size());
        }
        
        static const Generator*             lookup(std::string_view k)
        {
            return static_cast<const Generator*>(GeneratorMeta::find(*repo(), k));
        }
        
    private:
        static Repo*    repo()
        {
            static Repo*    ret   = newRepo(typeid(G).name());
            return ret;
        }
    };
}
