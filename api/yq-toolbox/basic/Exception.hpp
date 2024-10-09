#pragma once

#include <exception>
#include <source_location>
#include <stacktrace>
#include <system_error>
#include <yq-toolbox/basic/Any.hpp>
#include <yq-toolbox/basic/Flags.hpp>
#include <yq-toolbox/io/Stream.hpp>
#include <yq/typedef/string_pairs.hpp>

namespace yq {

    template <typename X>
    concept Exceptional = std::derived_from<X, std::exception>;
    
    class Barf : public Stream {
    public:
    
        enum Action : uint8_t {
            //! Log it
            Spew,
            
            //! Swallow exception
            Swallow,
            
            //! Rethrow the exception
            Rethrow
        };
        
        using ActionList    = std::initializer_list<Action>;
    
        using Actions = Flags<Action>;
        
        static constexpr const ActionList  kDefaultActions = {};
        
        struct Bit  {
            std::error_code                 code;
            std::string                     complaint;
            string_any_map_t                data;
            std::source_location            location;

            Bit& operator<<(std::initializer_list<string_any_pair_t>);
        };
        
        Barf();
        Barf(const Barf&);
        Barf(Barf&&);
        Barf& operator=(const Barf&);
        Barf& operator=(Barf&&);
        ~Barf();
        
        std::span<const Bit>        bits() const { return m_bits; }
        const std::stacktrace&      stack() const { return m_stack; }
        
        bool    write(const char* buf, size_t cb) override;
        
        Barf&   complain(std::string&&, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current());
        Barf&   complain(std::error_code, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current());
        Barf&   complain(std::error_code, std::string&&, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current());
        
        Barf&   nail(std::string&&key, Any&& value);
        Barf&   nail(std::initializer_list<string_any_pair_t>);
        
    protected:
    
        Barf(Bit&&, std::initializer_list<string_any_pair_t>kv={});

        Bit&                    _complain(Bit&&);
    
        std::vector<Bit>            m_bits;
        std::stacktrace             m_stack;
    };
    
    template <typename B>
    concept Barfable = std::derived_from<B, Barf>;
    
    template <Barfable B, Exceptional X>
    class ExceptionalBarf : public B, public X {
    public:
        ExceptionalBarf(Barf::Bit&& bit, std::initializer_list<string_any_pair_t>kv={}) : B(std::move(bit), kv) 
        {
        }
    };
    
    template <Barfable B=Barf, Exceptional X=std::exception>
    ExceptionalBarf<B,X>    vomit(std::error_code ec, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current())
    {
        return ExceptionalBarf<B,X>({ .code = ec, .location=loc }, kv);
    }
    
    template <Barfable B=Barf, Exceptional X=std::exception>
    ExceptionalBarf<B,X>    vomit(std::error_code ec, std::string&&k, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current())
    {
        return ExceptionalBarf<B,X>({ .code=ec, .complaint=k, .location=loc }, kv);
    }

    template <Barfable B=Barf, Exceptional X=std::exception>
    ExceptionalBarf<B,X>    vomit(std::string&&k, std::initializer_list<string_any_pair_t> kv={}, const std::source_location& loc=std::source_location::current())
    {
        return ExceptionalBarf<B,X>({ .complaint=k, .location=loc }, kv);
    }

    template <typename Pred>
    void    barf_bag(Barf::Actions, Pred&&);

    template <typename Pred>
    void    barf_bag(Barf::ActionList, Pred&&);

    template <typename Pred>
    void    barf_bag(Pred&&);
    
}
