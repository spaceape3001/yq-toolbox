////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Any.hpp"

#include <basic/meta/ReservedIDs.hpp>
#include <basic/stream/Text.hpp>
#include <basic/TextUtils.hpp>


namespace yq {
    bool    Any::good(const TypeInfo&ti)
    {
        //  these are the function pointers that won't be checked at runtime
        return ti.m_copyB && ti.m_copyR && ti.m_ctorCopyR && ti.m_ctorCopyB 
            && ti.m_ctorMove && ti.m_dtor && ti.m_equal && ti.m_moveB;
    }


    Any      Any::parse_me(const TypeInfo& ti, const std::string_view&txt)
    {
        Any ret;
        bool    f   = ret.parse(ti, txt);
        return f ? ret : Any();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Any::Any(const Any& cp) : m_type(cp.m_type)
    {
        (m_type -> m_ctorCopyB)(m_data, cp.m_data);
    }
    
    Any::Any(Any&&mv) : m_type(mv.m_type)
    {
        (m_type -> m_ctorMove)(m_data, std::move(mv.m_data));
        mv.m_type   = &invalid();
    }
    
    Any::Any(const TypeInfo* newTypePtr) 
    {
        assert(newTypePtr && good(*newTypePtr));
        m_type  = newTypePtr;
        (m_type -> m_ctorCopyB)(m_data, m_type -> m_default);
    }
    
    //! Creates a defaulted Any to the specified meta-type
    Any::Any(const TypeInfo&newType) : m_type(&newType)
    {
        assert(good(newType));
        (m_type -> m_ctorCopyB)(m_data, m_type -> m_default);
    }
    
    Any::Any(const TypeInfo&newType, const void* dp) : m_type(&newType)
    {
        assert(good(newType));

        if(dp)
            (m_type -> m_ctorCopyR)(m_data, dp);
        else 
            (m_type -> m_ctorCopyB)(m_data, m_type -> m_default);
    }
    

    Any::Any(char ch) : m_type(nullptr)
    {
        set<std::string>(to_string(ch));
    }
    
    Any::Any(char8_t ch) : m_type(nullptr)
    {
        set<std::string>(to_string(ch));
    }
    
    Any::Any(char32_t ch) : m_type(nullptr)
    {
        set<std::string>(copy(to_string(ch)));
    }
    
    Any::Any(const char*z) : m_type(nullptr)
    {
        set<std::string>(z);
    }
    
    Any::Any(char*z) : m_type(nullptr)
    {
        set<std::string>(z);
    }

    Any::Any(const char8_t*z) : m_type(nullptr)
    {
        set<std::string>(to_string(z));
    }
    
    Any::Any(const char32_t*z) : m_type(nullptr)
    {
        set<std::string>(to_string(z));
    }
    
    Any::Any(const std::u8string&z) : m_type(nullptr)
    {
        set<std::string>(to_string(z));
    }
    
    Any::Any(const std::u32string&z) : m_type(nullptr)
    {
        set<std::string>(to_string(z));
    }
    
    Any::Any(const std::wstring&z) : m_type(nullptr)
    {
        set<std::string>(to_string(z));
    }
    

    //  Any(const meta::Type*);

    Any::~Any()
    {
        assert(m_type);
        (m_type -> m_dtor)(m_data);
        
        #ifndef NDEBUG
        m_type      = &invalid();
        #endif
    }
    

    Any&        Any::operator=(const Any& cp)
    {
        assert(m_type);
        if(&cp != this){
            if(cp.m_type == m_type){
                assert(m_type -> m_copyB);

                (m_type -> m_copyB)(m_data, cp.m_data);
            } else {
                assert(m_type -> m_dtor);
                assert(m_type -> m_ctorCopyB);

                (m_type -> m_dtor)(m_data);
                m_type  = cp.m_type;
                (m_type -> m_ctorCopyB)(m_data, cp.m_data);
            }
        }
        return *this;
    }
    
    Any&        Any::operator=(Any&&mv)
    {
        assert(m_type);
        if(&mv != this){
            if(mv.m_type == m_type){
                (m_type -> m_moveB)(m_data, std::move(mv.m_data));
            } else {
                (m_type -> m_dtor)(m_data);
                m_type  = mv.m_type;
                (m_type -> m_ctorMove)(m_data, std::move(mv.m_data));
            }
            mv.m_type   = &invalid();
        }
        return *this;
    }
    
    bool            Any::operator==(const Any&b) const
    {
        if(this == &b)
            return true;
        if(m_type != b.m_type)
            return false;
        return (m_type->m_equal)(m_data, b.m_data);
    }
    

    bool            Any::can_convert(const TypeInfo&newType) const
    {
        if(m_type == &newType)
            return true;
        if(&newType == &invalid())
            return true;
        if(&newType == &any())
            return true;
        return m_type->m_convert.has(&newType);
    }

    void            Any::clear()
    {
        if(m_type){
            m_type -> m_dtor(m_data);
            m_type  = &invalid();
        }
    }
    

    Any         Any::convert(const TypeInfo& newType) const
    {
        assert(m_type);

        if(&newType == m_type)
            return *this;
        if(&newType == &invalid())
            return Any();
        if(m_type == &invalid())
            return Any();
        if(&newType == &any())
            return *this;
            
        auto fn = m_type -> m_convert.get(&newType, nullptr);
        if(!fn)
            return Any();
        
        Any ret(newType);
        fn(ret.raw_ptr(), raw_ptr());
        return ret;
    }


    bool            Any::is_valid() const
    {
        return m_type && (m_type != &invalid());
    }

    bool            Any::parse(const TypeInfo&newType, const std::string_view&txt)
    {   
        assert(m_type);
        if(&newType != m_type){
            assert(good(newType));
            assert(m_type->m_dtor);
            (m_type->m_dtor)(m_data);
            m_type  = &newType;
        }
        
        (m_type->m_ctorCopyB)(m_data, m_type->m_default);
        return (m_type->m_parse)(raw_ptr(), txt);
    }
    

    bool            Any::print(Stream& str) const
    {
        assert(m_type);
        if(m_type->m_print){
            (m_type->m_print)(str, raw_ptr());
            return true;
        }
        return false;
    }

    std::string          Any::printable() const
    {
        std::string  result;
        stream::Text  buf(result);
        print(buf);
        buf.flush();
        return result;  
    }

    const void*      Any::raw_ptr() const 
    {
        return m_type -> is_small() ? (const void*) m_data.Data : m_data.Pointer;
    };
    
    void*            Any::raw_ptr() 
    {
        return m_type -> is_small() ? (void*) m_data.Data : m_data.Pointer;
    };

    void    Any::set(const TypeInfo&newType, const void*val)
    {
        if(m_type){
            if(&newType == m_type){
                assert(m_type -> m_copyR);
                m_type -> m_copyR(m_data, val);
                return ;
            }
            m_type -> m_dtor(m_data);
        }

        assert(good(newType));
        m_type  = &newType;
        if(val){
            m_type -> m_ctorCopyR(m_data, val);
        } else
            m_type -> m_ctorCopyB(m_data, m_type->m_default);
    }

    bool        Any::write(Stream&str) const
    {
        assert(m_type);
        if(m_type -> m_write){
            (m_type->m_write)(str, raw_ptr());
            return true;
        }
        return false;
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    boolean_r   to_boolean(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_boolean(v.data().reference<std::string>());
        case MT_Boolean:
            return boolean_r{ v.data().reference<bool>(), true };
        case MT_Int8:
            return boolean_r{ static_cast<bool>( v.data().reference<int8_t>()), true };
        case MT_Int16:
            return boolean_r{ static_cast<bool>( v.data().reference<int16_t>()), true };
        case MT_Int32:
            return boolean_r{ static_cast<bool>( v.data().reference<int32_t>()), true };
        case MT_Int64:
            return boolean_r{ static_cast<bool>( v.data().reference<int64_t>()), true };
        case MT_UInt8:
            return boolean_r{ static_cast<bool>( v.data().reference<uint8_t>()), true };
        case MT_UInt16:
            return boolean_r{ static_cast<bool>( v.data().reference<uint16_t>()), true };
        case MT_UInt32:
            return boolean_r{ static_cast<bool>( v.data().reference<uint32_t>()), true };
        case MT_UInt64:
            return boolean_r{ static_cast<bool>( v.data().reference<uint64_t>()), true };
        default:
            return {};
        }
    }
    
    double_r    to_double(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_double(v.data().reference<std::string>());
        case MT_Boolean:
            return double_r{ (v.data().reference<bool>()?1.0:0.0), true };
        case MT_Double:
            return double_r{ v.data().reference<double>(), true };
        case MT_Float:
            return double_r{ v.data().reference<float>(), true };
        case MT_Int8:
            return double_r{ static_cast<double>( v.data().reference<int8_t>()), true };
        case MT_Int16:
            return double_r{ static_cast<double>( v.data().reference<int16_t>()), true };
        case MT_Int32:
            return double_r{ static_cast<double>( v.data().reference<int32_t>()), true };
        case MT_Int64:
            return double_r{ static_cast<double>( v.data().reference<int64_t>()), true };
        case MT_UInt8:
            return double_r{ static_cast<double>( v.data().reference<uint8_t>()), true };
        case MT_UInt16:
            return double_r{ static_cast<double>( v.data().reference<uint16_t>()), true };
        case MT_UInt32:
            return double_r{ static_cast<double>( v.data().reference<uint32_t>()), true };
        case MT_UInt64:
            return double_r{ static_cast<double>( v.data().reference<uint64_t>()), true };
        default:
            return {};
        }
    }
    
    float_r     to_float(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_float(v.data().reference<std::string>());
        case MT_Boolean:
            return float_r{ v.data().reference<bool>()?1.0f:0.0f, true };
        case MT_Double:
            return float_r{ (float) v.data().reference<float>(), true };
        case MT_Float:
            return float_r{ v.data().reference<float>(), true };
        case MT_Int8:
            return float_r{ static_cast<float>( v.data().reference<int8_t>()), true };
        case MT_Int16:
            return float_r{ static_cast<float>( v.data().reference<int16_t>()), true };
        case MT_Int32:
            return float_r{ static_cast<float>( v.data().reference<int32_t>()), true };
        case MT_Int64:
            return float_r{ static_cast<float>( v.data().reference<int64_t>()), true };
        case MT_UInt8:
            return float_r{ static_cast<float>( v.data().reference<uint8_t>()), true };
        case MT_UInt16:
            return float_r{ static_cast<float>( v.data().reference<uint16_t>()), true };
        case MT_UInt32:
            return float_r{ static_cast<float>( v.data().reference<uint32_t>()), true };
        case MT_UInt64:
            return float_r{ static_cast<float>( v.data().reference<uint64_t>()), true };
        default:
            return {};
        }
    }
    
    int_r       to_int(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int(v.data().reference<std::string>());
        case MT_Boolean:
            return int_r{ static_cast<int>(v.data().reference<bool>()), true };
        case MT_Float:
            return int_r{ static_cast<int>(v.data().reference<float>()), true };
        case MT_Double:
            return int_r{ static_cast<int>(v.data().reference<double>()), true };
        case MT_Int8:
            return int_r{ static_cast<int>( v.data().reference<int8_t>()), true };
        case MT_Int16:
            return int_r{ static_cast<int>( v.data().reference<int16_t>()), true };
        case MT_Int32:
            return int_r{ static_cast<int>( v.data().reference<int32_t>()), true };
        case MT_Int64:
            return int_r{ static_cast<int>( v.data().reference<int64_t>()), true };
        case MT_UInt8:
            return int_r{ static_cast<int>( v.data().reference<uint8_t>()), true };
        case MT_UInt16:
            return int_r{ static_cast<int>( v.data().reference<uint16_t>()), true };
        case MT_UInt32:
            return int_r{ static_cast<int>( v.data().reference<uint32_t>()), true };
        case MT_UInt64:
            return int_r{ static_cast<int>( v.data().reference<uint64_t>()), true };
        default:
            return {};
        }
    }
    
    #if 0
    int8_r      to_int8(const Any&v);
    int16_r     to_int16(const Any&v);
    int32_r     to_int32(const Any&v);
    int64_r     to_int64(const Any&v);
    integer_r   to_integer(const Any&v);
    short_r     to_short(const Any&v);
    //string_r    to_string(const Any&v);
    uint8_r     to_uint8(const Any&v);
    uint16_r    to_uint16(const Any&v);
    uint32_r    to_uint32(const Any&v);
    uint64_r    to_uint64(const Any&v);
    unsigned_r  to_uinteger(const Any&v);
    ushort_r    to_ushort(const Any&v);
    #endif

}
