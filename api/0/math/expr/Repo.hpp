////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/CompoundInfo.hpp>
#include <0/meta/InfoBinder.hpp>
#include <0/meta/CompoundInfoStatic.hpp>
#include <unordered_set>
#include <tbb/spin_rw_mutex.h>

namespace yq::expr {


    /*! \brief All things the user expression evaluation needs
    
        Constant ... map of string/any
        Variable ... repo static properties, can change with time
        Function ... repo methods
    */
    class Repo : public CompoundInfo {
    public:
        template <typename> class Writer;
    
        static Repo& instance();
        
        
        Expect<Any>     constant(std::string_view) const;
        Expect<Any>     constant(std::u32string_view) const;

        bool            has_constant(std::string_view) const;
        bool            has_constant(std::u32string_view) const;

        bool            has_function(std::string_view) const;
        bool            has_function(std::u32string_view) const;

        bool            has_operator(std::string_view) const;
        bool            has_operator(std::u32string_view) const;

        bool            has_variable(std::string_view) const;
        bool            has_variable(std::u32string_view) const;

        Expect<Any>     variable(std::string_view) const;
        Expect<Any>     variable(std::u32string_view) const;
        
        template <typename Pred>
        auto            all_functions(std::u32string_view, Pred) const;

        bool            digits_in_text() const { return m_digitsText; }
        bool            punctuation_can_start_text() const { return m_punctStartsText; }
        
        
        bool            is_punct_text(char32_t) const;
        
        template <typename Pred>
        auto            all_operators(std::u32string_view, Pred) const;

        struct OpData;

    private:
        Repo();
        ~Repo();
        
        Repo(const Repo&) = delete;
        Repo(Repo&&) = delete;
        Repo& operator=(const Repo&) = delete;
        Repo& operator=(Repo&&) = delete;
        
        
        using OpMap = MultiMap<std::u32string_view, OpData>;
        using C32Hash       = std::unordered_set<char32_t>;
        
        void    sweep_impl() override;
        
        static const OpData             kStandardOperators[];
        
        u32string_any_map_t             m_constants;
        LUC32<PropertyInfo>             m_variables;
        LUC32<MethodInfo>               m_functions;
        OpMap                           m_operators;
        C32Hash                         m_punctText;
        bool                            m_digitsText        = true;
        bool                            m_punctStartsText   = true;
    };
    
    template <typename>
    class Repo::Writer : public CompoundInfo::Static {
    public:
        Writer(Repo& p) : CompoundInfo::Static(&p), m_repo(p)
        {
        }

        void set_constant(std::string_view k, const Any& cp)
        {
            if(thread_safe_write()){
                m_repo.m_constants[to_u32string(k)] = cp;
            }
        }

        void set_constant(std::string_view k, Any&& mv)
        {
            if(thread_safe_write()){
                m_repo.m_constants[to_u32string(k)] = std::move(mv);
            }
        }

        void set_constant(std::u32string_view k, const Any& cp)
        {
            if(thread_safe_write()){
                m_repo.m_constants[std::u32string(k)] = cp;
            }
        }

        void set_constant(std::u32string_view k, Any&&mv)
        {
            if(thread_safe_write()){
                m_repo.m_constants[std::u32string(k)] = std::move(mv);
            }
        }
        
    private:
        Repo&   m_repo;
    };

    struct Repo::OpData {
        std::u32string_view     text;
        Operator                code        = Operator::None;
        OperatorType            type        = OperatorType::None;
        std::u32string_view     other;
        int8_t                  priority    = 0;
        bool                    self        = false;
    };

    template <typename Pred>
    auto            Repo::all_functions(std::u32string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const MethodInfo*) nullptr));
        if constexpr (!std::is_same_v<pred_result_t, void>){
            auto R  = m_functions.lut32.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                pred_result_t   tmp = pred(r->second);
                if(tmp != pred_result_t{})
                    return tmp;
            }
            return pred_result_t{};
        } else if constexpr (std::is_same_v<pred_result_t, void>){
            auto R  = m_functions.lut32.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                pred(r->second);
            }
            return;
        }
    }

    template <typename Pred>
    auto            Repo::all_operators(std::u32string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const OpData&) * (const OpData*) nullptr));
        if constexpr (!std::is_same_v<pred_result_t, void>){
            auto R  = m_operators.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                pred_result_t   tmp = pred(r->second);
                if(tmp != pred_result_t{})
                    return tmp;
            }
            return pred_result_t{};
        } else if constexpr (std::is_same_v<pred_result_t, void>){
            auto R  = m_operators.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                pred(r->second);
            }
            return;
        }
    }
}

namespace yq {
    template <>
    struct InfoBinder<expr::Repo> {
        using Info = expr::Repo;
        
        static constexpr const bool     Defined     = true;
        static constexpr const bool     IsCompound  = true;     
        static constexpr const bool     IsType      = false;
        static constexpr const bool     IsObject    = false;
        static const expr::Repo&        bind();
        static expr::Repo&              edit();
    };
}

