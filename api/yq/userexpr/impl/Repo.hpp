////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/userexpr/forward.hpp>
#include <yq/core/Any.hpp>
#include <yq/meta/CompoundMeta.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/meta/CompoundMetaStatic.hpp>
#include <yq/meta/MetaLookup.hpp>
#include <yq/userexpr/impl/OpData.hpp>
#include <unordered_set>

namespace yq::expr {

    /*! \brief All things the user expression evaluation needs
    
        Constant ... map of string/any
        Variable ... repo static properties, can change with time
        Function ... repo methods
    */
    class Repo : public CompoundMeta {
    public:
        template <typename> class Writer;
    
        static Repo& instance();
        
        any_x     constant(std::string_view) const;
        any_x     constant(std::u32string_view) const;
        
        const TypeMeta* constant_type(string_view_t) const;

        bool            has_constant(std::string_view) const;
        bool            has_constant(std::u32string_view) const;

        bool            has_function(std::string_view) const;
        bool            has_function(std::u32string_view) const;

        bool            has_operator(std::string_view) const;
        bool            has_operator(std::u32string_view) const;

        bool            has_variable(std::string_view) const;
        bool            has_variable(std::u32string_view) const;

        any_x     variable(std::string_view) const;
        any_x     variable(std::u32string_view) const;
        
        template <typename Pred>
        auto            all_functions(std::u32string_view, Pred) const;

        bool            digits_in_text() const { return m_digitsText; }
        bool            punctuation_can_start_text() const { return m_punctStartsText; }
        
        
        bool            is_punct_text(char32_t) const;
        
        //template <typename Pred>
        //auto            all_operators(std::u32string_view, Pred) const;
		const OpData*	operator_(std::u32string_view k) const;

    private:
        Repo();
        ~Repo();
        
        Repo(const Repo&) = delete;
        Repo(Repo&&) = delete;
        Repo& operator=(const Repo&) = delete;
        Repo& operator=(Repo&&) = delete;
        
        
        using op_data_map_t     = std::map<std::u32string_view, OpData>;
        using char32_set_t      = std::unordered_set<char32_t>;
        
        void    sweep_impl() override;
        
        u32string_any_map_t             m_constants;
        MetaLookup<PropertyInfo>        m_variables;
        MetaLookup<MethodInfo>          m_functions;
        op_data_map_t                   m_operators;
        char32_set_t                    m_punctText;
        bool                            m_digitsText        = true;
        bool                            m_punctStartsText   = true;
    };
    
    Repo&   repo();

    template <typename>
    class Repo::Writer : public CompoundMeta::Static {
    public:
        Writer(Repo& p) : CompoundMeta::Static(&p), m_repo(p)
        {
        }

        void constant(std::string_view k, const Any& cp)
        {
            if(thread_safe_write()){
                m_repo.m_constants[to_u32string(k)] = cp;
            }
        }

        void constant(std::string_view k, Any&& mv)
        {
            if(thread_safe_write()){
                m_repo.m_constants[to_u32string(k)] = std::move(mv);
            }
        }

        void constant(std::u32string_view k, const Any& cp)
        {
            if(thread_safe_write()){
                m_repo.m_constants[std::u32string(k)] = cp;
            }
        }

        void constant(std::u32string_view k, Any&&mv)
        {
            if(thread_safe_write()){
                m_repo.m_constants[std::u32string(k)] = std::move(mv);
            }
        }
        
        void    operand(const OpData& op)
        {
            if(thread_safe_write()){
                m_repo.m_operators[op.text] = op;
            }
        }

        void    operand(OpData&& op)
        {
            if(thread_safe_write()){
                m_repo.m_operators[op.text] = std::move(op);
            }
        }
        
        void    operands(const std::span<const OpData>& ops)
        {
            if(thread_safe_write()){
                for(const OpData& d : ops){
                    m_repo.m_operators[d.text] = d;
                }
            }
        }
        
        void    punct2text(char32_t ch)
        {
            if(thread_safe_write()){
                m_repo.m_punctText.insert(ch);
            }
        }
        
    private:
        Repo&   m_repo;
    };

    template <typename Pred>
    auto            Repo::all_functions(std::u32string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const MethodInfo*) nullptr));
        if constexpr (!std::is_same_v<pred_result_t, void>){
            auto R  = m_functions.lut32.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                if(!r->second->is_static())
                    continue;
                pred_result_t   tmp = pred(r->second);
                if(tmp != pred_result_t{})
                    return tmp;
            }
            return pred_result_t{};
        } else if constexpr (std::is_same_v<pred_result_t, void>){
            auto R  = m_functions.lut32.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                if(!r->second->is_static())
                    continue;
                pred(r->second);
            }
            return;
        }
    }

#if 0
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
#endif

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

