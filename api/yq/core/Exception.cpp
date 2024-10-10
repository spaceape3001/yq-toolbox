////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Exception.hxx>

namespace yq {

    Barf::Bit& Barf::Bit::operator<<(std::initializer_list<string_any_pair_t> kv)
    {
        for(auto i : kv)
            data[i.first]   = i.second;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////

    Barf::Barf() = default;
    Barf::Barf(const Barf&) = default;
    Barf::Barf(Barf&&) = default;
    Barf& Barf::operator=(const Barf&) = default;
    Barf& Barf::operator=(Barf&&) = default;
    Barf::~Barf() = default;

    Barf::Barf(Bit&& b, std::initializer_list<string_any_pair_t> kv) : m_stack(std::stacktrace::current(2)) // guessing to two... 
    {
        m_bits.push_back(std::move(b));
        m_bits.back() << kv;
    }

    Barf::Bit&  Barf::_complain(Bit&& b)
    {
        m_bits.push_back(std::move(b));
        Bit& ret    = m_bits.back();
        if(ret.complaint.empty())
            ret.complaint   = ret.code.message();
        return ret;
    }

    Barf&  Barf::complain(std::string&&k, std::initializer_list<string_any_pair_t> kv, const std::source_location& loc)
    {
        _complain({.complaint=k, .location=loc}) << kv;
        return *this;
    }
    
    Barf&  Barf::complain(std::error_code ec, std::initializer_list<string_any_pair_t> kv, const std::source_location& loc)
    {
        _complain({.code=ec, .location=loc}) << kv;
        return *this;
    }
    
    Barf&  Barf::complain(std::error_code ec, std::string&&k, std::initializer_list<string_any_pair_t> kv, const std::source_location& loc)
    {
        _complain({.code=ec, .complaint=k, .location=loc}) << kv;
        return *this;
    }
    
    Barf&   Barf::nail(std::string&&key, Any&& value)
    {
        if(!m_bits.empty())
            m_bits.back().data[std::move(key)] = std::move(value);
        return *this;
    }
    
    Barf&   Barf::nail(std::initializer_list<string_any_pair_t> kv)
    {
        if(!m_bits.empty())
            m_bits.back() << kv;
        return *this;
    }

    bool    Barf::write(const char* buf, size_t cb)
    {
        if(buf && cb && !m_bits.empty())
            m_bits.back().complaint.append(buf, cb);
        return true;
    }
}

