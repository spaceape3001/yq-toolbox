////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/Result.hpp>
#include <yq/meta/ReservedIDs.hpp>
#include <yq/stream/StdError.hpp>
#include <yq/stream/StdOutput.hpp>
#include <yq/stream/Text.hpp>
#include <yq/text/copy.hpp>
#include <yq/text/parse.hpp>
//#include <0/basic/TextUtils.hpp>


namespace yq {
    
    static const TypeMeta& invalidType() { return invalid(); }


    bool    Any::good(const TypeMeta&ti)
    {
        //  these are the function pointers that won't be checked at runtime
        return ti.m_copyB && ti.m_copyR && ti.m_ctorCopyR && ti.m_ctorCopyB 
            && ti.m_ctorMove && ti.m_dtor && ti.m_equal && ti.m_moveB;
    }


    any_error_t  Any::parse_me(const TypeMeta& ti, std::string_view txt)
    {
        Any ret;
        std::error_code ec   = ret.parse(ti, txt);
        if( ec != std::error_code())
            ret = Any();
        return { std::move(ret), ec };
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Any::Any(const Any& cp) : m_type(cp.m_type)
    {
        (m_type -> m_ctorCopyB)(m_data, cp.m_data);
    }
    
    Any::Any(Any&&mv) : m_type(mv.m_type)
    {
        (m_type -> m_ctorMove)(m_data, std::move(mv.m_data));
        mv.m_type   = &invalidType();
    }
    
    Any::Any(const TypeMeta* newTypePtr) 
    {
        assert(newTypePtr && good(*newTypePtr));
        m_type  = newTypePtr;
        (m_type -> m_ctorCopyB)(m_data, m_type -> m_default);
    }
    
    //! Creates a defaulted Any to the specified meta-type
    Any::Any(const TypeMeta&newType) : m_type(&newType)
    {
        assert(good(newType));
        (m_type -> m_ctorCopyB)(m_data, m_type -> m_default);
    }
    
    Any::Any(const TypeMeta&newType, const void* dp) : m_type(&newType)
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
    
    Any::Any(const std::string&z) : m_type(nullptr)
    {
        set<std::string>(z);
    }
    
    Any::Any(std::string_view z) : m_type(nullptr)
    {
        set<std::string>(std::string(z));
    }
    
    Any::Any(parse_k, const TypeMeta&ti, std::string_view txt) : Any(PARSE, ti, txt, THROW)
    {
    }
    
    Any::Any(parse_k, const TypeMeta&ti, std::string_view txt, no_throw_k) : Any()
    {
        parse(ti, txt);
    }

    Any::Any(parse_k, const TypeMeta&ti, std::string_view txt, throw_k) : Any()
    {
        std::error_code ec  = parse(ti, txt);
        if(ec != std::error_code())
            throw ec;
    }

    Any::Any(parse_k, const TypeMeta& ti, std::string_view txt, std::error_code&ec) : Any()
    {
        ec  = parse(ti, txt);
    }

    //  Any(const meta::Type*);

    Any::~Any()
    {
        assert(m_type);
        (m_type -> m_dtor)(m_data);
        
        #ifndef NDEBUG
        m_type      = &invalidType();
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
            mv.m_type   = &invalidType();
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
    
    bool            Any::can_convert(const TypeMeta&newType) const
    {
        if(m_type == &newType)
            return true;
        if(&newType == &invalidType())
            return true;
        if(&newType == &any())
            return true;
        return m_type->m_convert.has(&newType);
    }

    bool        Any::can_print() const
    {
        if(!m_type)
            return false;
        return m_type -> can_print();
    }

    bool        Any::can_write() const
    {
        if(!m_type)
            return false;
        return m_type -> can_write();
    }
    
    bool        Any::can_write_and_parse() const
    {
        if(!m_type)
            return false;
        return m_type -> can_write_and_parse();
    }

    void            Any::clear()
    {
        if(m_type){
            m_type -> m_dtor(m_data);
            m_type  = &invalidType();
        }
    }
    

    any_x     Any::convert(const TypeMeta& newType) const
    {
        assert(m_type);
        if(!m_type)
            return errors::null_any_kype() ;
            
        if(&newType == m_type)
            return *this;
        if(&newType == &invalidType())
            return *this;
        if(&newType == &any())
            return *this;
        if(m_type == &invalidType())
            return errors::invalid_conversion();
            
        auto fn = m_type -> m_convert.get(&newType, nullptr);
        if(!fn)
            return errors::no_conversion_handler();
        
        Any ret(newType);
        std::error_code ec = fn(ret.raw_ptr(), raw_ptr());
        if(ec != std::error_code()) // at least until we update the function
            return std::unexpected(ec);
        return ret;
    }

    bool            Any::is_valid() const
    {
        return m_type && (m_type != &invalidType());
    }

    std::error_code Any::parse(const TypeMeta&newType, const std::string_view&txt)
    {   
        assert(m_type);
        if(!m_type)
            return errors::null_any_kype();
        
        if(&newType != m_type){
            assert(good(newType));
            assert(m_type->m_dtor);
            (m_type->m_dtor)(m_data);
            m_type  = &newType;
        }
        
        (m_type->m_ctorCopyB)(m_data, m_type->m_default);
        if(!(m_type->m_parse))
            return errors::no_handler();
        return (m_type->m_parse)(raw_ptr(), txt);
    }
    

    std::error_code Any::print(Stream& str, std::string_view k) const
    {
        assert(m_type);
        if(!m_type)
            return errors::null_any_kype();
        TypeMeta::FNFormat    fn  = m_type->printer(k);
        if(!fn)
            return errors::no_print_handler();
        (fn)(str, raw_ptr());
        return std::error_code();
    }

    std::error_code     Any::print(Stream&str, string_view_initializer_list_t keys) const
    {
        assert(m_type);
        if(!m_type)
            return errors::null_any_kype();
        TypeMeta::FNFormat    fn  = m_type->printer(keys);
        if(!fn)
            return errors::no_print_handler();
        (fn)(str, raw_ptr());
        return std::error_code();
    }

    std::error_code     Any::print(cerr_t, std::string_view k) const
    {
        stream::StdError  str;
        return print(str, k);
    }
    
    std::error_code     Any::print(cerr_t, string_view_initializer_list_t keys) const
    {
        stream::StdError  str;
        return print(str, keys);
    }
    
    std::error_code     Any::print(cout_k, std::string_view k) const
    {
        stream::StdOutput  str;
        return print(str, k);
    }
    
    std::error_code     Any::print(cout_k, string_view_initializer_list_t keys) const
    {
        stream::StdOutput  str;
        return print(str, keys);
    }


    std::string          Any::printable(std::string_view k) const
    {
        std::string  result;
        stream::Text  buf(result);
        print(buf, k);
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

    void    Any::set(const TypeMeta&newType, const void*val)
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

    uint64_t  Any::type_id() const
    {
        if(!m_type)
            return 0;
        return m_type -> id();
    }

    std::error_code Any::write(Stream&str) const
    {
        assert(m_type);
        if(!m_type)
            return errors::null_any_kype();
        if(!(m_type -> m_write))
            return errors::no_write_handler();
        (m_type->m_write)(str, raw_ptr());
        return std::error_code();
    }
    
    std::string     Any::writable() const
    {
        std::string  result;
        stream::Text  buf(result);
        write(buf);
        buf.flush();
        return result;  
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    boolean_x  to_boolean(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_boolean(v.data().reference<std::string>());
        case MT_Boolean:
            return v.data().reference<bool>();
        case MT_Int8:
            return static_cast<bool>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<bool>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<bool>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<bool>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<bool>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<bool>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<bool>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<bool>( v.data().reference<uint64_t>());
        default:
            break;
        }

        auto v2   = v.value<bool>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }
    
    double_x   to_double(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_double(v.data().reference<std::string>());
        case MT_Boolean:
            return v.data().reference<bool>()?1.0:0.0;
        case MT_Double:
            return v.data().reference<double>();
        case MT_Float:
            return v.data().reference<float>();
        case MT_Int8:
            return static_cast<double>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<double>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<double>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<double>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<double>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<double>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<double>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<double>( v.data().reference<uint64_t>());
        default:
            break;
        }

        auto v2     = v.value<double>();
        if(v2.good)
            return v2.value;
            
        auto v3     = v.value<float>();
        if(v3.good)
            return v3.value;

        return errors::bad_conversion();
    }
    
    float_x  to_float(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_float(v.data().reference<std::string>());
        case MT_Boolean:
            return v.data().reference<bool>()?1.0f:0.0f;
        case MT_Double:
            return (float) v.data().reference<double>();
        case MT_Float:
            return v.data().reference<float>();
        case MT_Int8:
            return static_cast<float>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<float>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<float>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<float>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<float>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<float>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<float>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<float>( v.data().reference<uint64_t>());
        default:
            break;
        }

        auto v3     = v.value<float>();
        if(v3.good)
            return v3.value;

        auto v2     = v.value<double>();
        if(v2.good)
            return (float) v2.value;

        return errors::bad_conversion();
    }
    
    integer_x     to_int(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<int>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }
    
    int8_x      to_int8(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int8(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int8_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int8_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int8_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int8_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<int8_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int8_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int8_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int8_t>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int8_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int8_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int8_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int8_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    int16_x      to_int16(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int16(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int16_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int16_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int16_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int16_t>( v.data().reference<int16_t>());
        case MT_Int16:
            return static_cast<int16_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int16_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int16_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int16_t>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int16_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int16_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int16_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int16_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }


    int32_x     to_int32(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int32(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int32_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int32_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int32_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int32_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<int32_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int32_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int32_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int32_t>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int32_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int32_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int32_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int32_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    int64_x     to_int64(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int64(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int64_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int64_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int64_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int64_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<int64_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int64_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int64_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int64_t>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int64_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int64_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int64_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int64_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    integer_x     to_integer(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_int(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<int>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<int>(v.data().reference<float>());
        case MT_Double:
            return static_cast<int>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<int>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<int>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<int>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<int>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<int>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<int>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<int>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<int>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<int>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    short_x     to_short(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_short(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<short>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<short>(v.data().reference<float>());
        case MT_Double:
            return static_cast<short>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<short>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<short>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<short>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<short>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<short>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<short>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<short>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<short>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<short>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    string_x    to_string(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return v.data().reference<std::string>();
        case MT_Boolean:
            return to_string(v.data().reference<bool>());
        case MT_Float:
            return to_string(v.data().reference<float>());
        case MT_Double:
            return to_string(v.data().reference<double>());
        case MT_Int8:
            return to_string( v.data().reference<int8_t>());
        case MT_Int16:
            return to_string( v.data().reference<int16_t>());
        case MT_Int32:
            return to_string( v.data().reference<int32_t>());
        case MT_Int64:
            return to_string( v.data().reference<int64_t>());
        case MT_UInt8:
            return to_string( v.data().reference<uint8_t>());
        case MT_UInt16:
            return to_string( v.data().reference<uint16_t>());
        case MT_UInt32:
            return to_string( v.data().reference<uint32_t>());
        case MT_UInt64:
            return to_string( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<std::string>();
        if(v2.good)
            return v2.value;
        
        if(!v.can_print())
            return errors::bad_conversion();

        return v.printable();
    }

    uint8_x     to_uint8(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uint8(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<uint8_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<uint8_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<uint8_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<uint8_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<uint8_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<uint8_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<uint8_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<uint8_t>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<uint8_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<uint8_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<uint8_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<uint8_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    uint16_x     to_uint16(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uint16(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<uint16_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<uint16_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<uint16_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<uint16_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<uint16_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<uint16_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<uint16_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<uint16_t>( v.data().reference<uint16_t>());
        case MT_UInt16:
            return static_cast<uint16_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<uint16_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<uint16_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<uint16_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    uint32_x     to_uint32(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uint32(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<uint32_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<uint32_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<uint32_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<uint32_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<uint32_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<uint32_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<uint32_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<uint32_t>( v.data().reference<uint32_t>());
        case MT_UInt16:
            return static_cast<uint32_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<uint32_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<uint32_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<uint32_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    uint64_x     to_uint64(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uint64(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<uint64_t>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<uint64_t>(v.data().reference<float>());
        case MT_Double:
            return static_cast<uint64_t>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<uint64_t>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<uint64_t>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<uint64_t>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<uint64_t>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<uint64_t>( v.data().reference<uint64_t>());
        case MT_UInt16:
            return static_cast<uint64_t>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<uint64_t>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<uint64_t>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<uint64_t>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    unsigned_x   to_uint(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uinteger(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<unsigned int>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<unsigned int>(v.data().reference<float>());
        case MT_Double:
            return static_cast<unsigned int>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<unsigned int>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<unsigned int>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<unsigned int>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<unsigned int>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<unsigned int>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<unsigned int>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<unsigned int>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<unsigned int>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<unsigned int>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }
    
    unsigned_x     to_uinteger(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_uinteger(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<unsigned int>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<unsigned int>(v.data().reference<float>());
        case MT_Double:
            return static_cast<unsigned int>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<unsigned int>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<unsigned int>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<unsigned int>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<unsigned int>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<unsigned int>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<unsigned int>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<unsigned int>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<unsigned int>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<unsigned int>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }

    ushort_x    to_ushort(const Any&v)
    {
        switch(v.type().id()){
        case MT_String:
            return to_ushort(v.data().reference<std::string>());
        case MT_Boolean:
            return static_cast<unsigned short>(v.data().reference<bool>());
        case MT_Float:
            return static_cast<unsigned short>(v.data().reference<float>());
        case MT_Double:
            return static_cast<unsigned short>(v.data().reference<double>());
        case MT_Int8:
            return static_cast<unsigned short>( v.data().reference<int8_t>());
        case MT_Int16:
            return static_cast<unsigned short>( v.data().reference<int16_t>());
        case MT_Int32:
            return static_cast<unsigned short>( v.data().reference<int32_t>());
        case MT_Int64:
            return static_cast<unsigned short>( v.data().reference<int64_t>());
        case MT_UInt8:
            return static_cast<unsigned short>( v.data().reference<uint8_t>());
        case MT_UInt16:
            return static_cast<unsigned short>( v.data().reference<uint16_t>());
        case MT_UInt32:
            return static_cast<unsigned short>( v.data().reference<uint32_t>());
        case MT_UInt64:
            return static_cast<unsigned short>( v.data().reference<uint64_t>());
        default:
            break;
        }
        
        auto v2   = v.value<unsigned short>();
        if(v2.good)
            return v2.value;
        return errors::bad_conversion();
    }
}
