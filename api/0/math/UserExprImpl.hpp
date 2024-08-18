////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>
#include <0/math/Operator.hpp>
#include <0/math/UserExpr.hpp>
#include <0/meta/CompoundInfo.hpp>
#include <0/meta/InfoBinder.hpp>
#include <0/meta/CompoundInfoStatic.hpp>
#include <unordered_set>
#include <tbb/spin_rw_mutex.h>

namespace log4cpp { class CategoryStream; }


namespace yq::expr {


    YQ_ENUM(SymCategory,,
        None	= 0,
        Error,
        Operator,
        Space,
        Text,
        Value,
        Open,
        Close,
        Special
    );

    YQ_ENUM(SymKind,, 
        None		= 0,
        
            // OPERATORS (at front to match the operators enumeration)
        YQ_OPERATORS,

            // VALUES
        Integer,
        Octal,
        Hexadecimal,
        Float,

            // TEXTS
        Variable,
        Function,
        Constant,
        Constructor,
        
            // SPECIALS
        Assign,
        Duplicate,
        Comma,
        
            // OPEN/CLOSE
        Generic,
        Array,
        Tuple
    );

	struct Symbol {
        using Category  = expr::SymCategory;
        using Kind      = expr::SymKind;
		
		std::u32string	text;
		Any				value;
		SymCategory		category	= SymCategory::None;
		SymKind			kind		= SymKind::None;
		uint16_t        priority	= 0;
        uint16_t        argcnt      = 0;
		
		constexpr bool operator==(const Symbol&) const = default;

		constexpr operator SymCode() const noexcept;
	};

	struct SymCode {
		SymCategory	category	= SymCategory::None;
		SymKind		kind		= SymKind::None;
		
		constexpr bool operator==(const SymCode&) const = default;
	};

	constexpr Symbol::operator SymCode() const noexcept 
	{
		return { .category=category, .kind=kind };
	}


    //! Light weight token
    struct Token {
		SymCategory	category	= SymCategory::None;
		SymKind		kind		= SymKind::None;
        size_t              length     	= 0;
        
        constexpr bool  operator==(const Token&) const noexcept = default;
    };
    
    /*! User expression instruction
    
        We'd tried a common class to symbols, but that's an ugly hack.
    */
    class Instruction {
    public:
    
        using result_t  = std::variant<std::monostate, int, const TypeInfo*, std::vector<const TypeInfo*>>;

        // Defining text
        string_view_t               text() const { return m_text; }
        
        //! Executes this instruction
        virtual std::error_code     execute(any_stack_t& valueStack, u32string_any_map_t& variables) const = 0;
        
        //! Expected result (monostate if unknown)
        virtual result_t    result() const;
        
        //! Expected result for argument types
        virtual result_t    result(std::span<const TypeInfo*>) const;
        
        //! Destructor
        virtual ~Instruction();

    protected:
        Instruction(const string_t&);
        
        const string_t  m_text;
    };

    struct OpData {
        std::u32string_view     text;
        Operator                code        = Operator::None;
        OperatorType            type        = OperatorType::None;
        Symbol::Category		category	= Symbol::Category::None;
        Symbol::Kind			kind		= Symbol::Kind::None;
        std::u32string_view     other;
        uint8_t                 priority    = 0;
        uint8_t                 args        = 0;
        bool					left		= false;
        bool					right		= false;
        bool                    self        = false;
    };


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
        
        
        using OpMap 		= std::map<std::u32string_view, const OpData*>;
        using C32Hash       = std::unordered_set<char32_t>;
        
        void    sweep_impl() override;
        
        static const OpData             kStandardOperators[];
        
        u32string_any_map_t             m_constants;
        LUC32<PropertyInfo>             m_variables;
        LUC32<MethodInfo>               m_functions;
        OpMap                           m_operators;
        char32_set_t                    m_punctText;
        bool                            m_digitsText        = true;
        bool                            m_punctStartsText   = true;
    };
    
    Repo&   repo();

    /*! \brief Sub-tokenizes
    
        This is the sub-tokenizer, it scans the text for what seems like the next
        relevant symbol.  
    */
    Token        token(std::u32string_view);

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Symbol&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const SymVector&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Token&);
    std::ostream&    operator<<(std::ostream&, const Symbol&);
    std::ostream&    operator<<(std::ostream&, const SymVector&);
    std::ostream&    operator<<(std::ostream&, const Token&);

}


namespace yq::expr {
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
