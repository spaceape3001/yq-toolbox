////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/TypeInfo.hpp>
#include <basic/meta/ReservedIDs.hpp>
#include <basic/meta/Init.hpp>

#include <basic/DelayInit.hpp>
#include <basic/TextUtils.hpp>
#include <basic/Any.hpp>

YQ_TYPE_FIXED(MT_String, std::string)
YQ_TYPE_FIXED(MT_Boolean, bool)
YQ_TYPE_FIXED(MT_Float, float)
YQ_TYPE_FIXED(MT_Double, double)
YQ_TYPE_FIXED(MT_Int8, int8_t)
YQ_TYPE_FIXED(MT_Int16, int16_t)
YQ_TYPE_FIXED(MT_Int32, int32_t)
YQ_TYPE_FIXED(MT_Int64, int64_t)
YQ_TYPE_FIXED(MT_UInt8, uint8_t)
YQ_TYPE_FIXED(MT_UInt16, uint16_t)
YQ_TYPE_FIXED(MT_UInt32, uint32_t)
YQ_TYPE_FIXED(MT_UInt64, uint64_t)

namespace yq {
    namespace {
    
        bool    parse_string(const std::string_view& txt, std::string& v)
        {
            v   = txt;
            return true;
        }
    
        bool    parse_boolean(const std::string_view&txt, bool&v)
        {
            auto r  = to_boolean(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_double(const std::string_view&txt, double&v)
        {
            auto r  = to_double(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_float(const std::string_view&txt, float&v)
        {
            auto r  = to_float(txt);
            v   = r.value;
            return r.good;
        }
        
        
        bool    parse_int8(const std::string_view&txt, int8_t&v)
        {
            auto r  = to_int8(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_int16(const std::string_view&txt, int16_t&v)
        {
            auto r  = to_int16(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_int32(const std::string_view&txt, int32_t&v)
        {
            auto r  = to_int32(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_int64(const std::string_view&txt, int64_t&v)
        {
            auto r  = to_int64(txt);
            v   = r.value;
            return r.good;
        }

        bool    parse_uint8(const std::string_view&txt, uint8_t&v)
        {
            auto r  = to_uint8(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_uint16(const std::string_view&txt, uint16_t&v)
        {
            auto r  = to_uint16(txt);
            v   = r.value;
            return r.good;
        }
        
        bool    parse_uint32(const std::string_view&txt, uint32_t&v)
        {
            auto r  = to_uint32(txt);
            v   = r.value;
            return r.good;
        }


        bool    parse_uint64(const std::string_view&txt, uint64_t&v)
        {
            auto r  = to_uint64(txt);
            v   = r.value;
            return r.good;
        }
        
        //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void    print_string(Stream& str, const std::string& v)
        {
            str << v;
        }

        void    print_boolean(Stream& str, bool v)
        {
            str << v;
        }

        void    print_double(Stream& str, double v)
        {
            str << v;
        }

        void    print_float(Stream& str, float v)
        {
            str << v;
        }

        void    print_int8(Stream& str, int8_t v)
        {
            str << v;
        }

        void    print_int16(Stream& str, int16_t v)
        {
            str << v;
        }

        void    print_int32(Stream& str, int32_t v)
        {
            str << v;
        }

        void    print_int64(Stream& str, int64_t v)
        {
            str << v;
        }


        void    print_uint8(Stream& str, uint8_t v)
        {
            str << v;
        }

        void    print_uint16(Stream& str, uint16_t v)
        {
            str << v;
        }

        void    print_uint32(Stream& str, uint32_t v)
        {
            str << v;
        }

        void    print_uint64(Stream& str, uint64_t v)
        {
            str << v;
        }
    

        void    init_stdtypes()
        {
            {
                auto w = writer<bool>();
                w.parse<parse_boolean>();
                w.print<print_boolean>();
            }
            {
                auto w = writer<double>();
                w.parse<parse_double>();
                w.print<print_double>();
            }
            {
                auto w = writer<float>();
                w.parse<parse_float>();
                w.print<print_float>();
            }
            {
                auto w  = writer<int8_t>();
                w.parse<parse_int8>();
                w.print<print_int8>();
            }
            {
                auto w  = writer<int16_t>();
                w.parse<parse_int16>();
                w.print<print_int16>();
            }
            {
                auto w  = writer<int32_t>();
                w.alias("Integer");
                w.parse<parse_int32>();
                w.print<print_int32>();
            }
            {
                auto w  = writer<int64_t>();
                w.parse<parse_int64>();
                w.print<print_int64>();
            }
            {
                auto w  = writer<uint8_t>();
                w.parse<parse_uint8>();
                w.print<print_uint8>();
            }
            {
                auto w  = writer<uint16_t>();
                w.parse<parse_uint16>();
                w.print<print_uint16>();
            }
            {
                auto w  = writer<uint32_t>();
                w.parse<parse_uint32>();
                w.print<print_uint32>();
            }
            {
                auto w  = writer<uint64_t>();
                w.parse<parse_uint64>();
                w.print<print_uint64>();
            }
            {
                auto w  = writer<std::string>();
                w.alias("String");
                w.parse<parse_string>();
                w.print<print_string>();
            }
        }
    }
}

YQ_INVOKE(
    yq::init_stdtypes();
)
