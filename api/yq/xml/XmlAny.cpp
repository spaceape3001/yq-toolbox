////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XmlAny.hpp"
#include "XmlUtils.hpp"
#include <yq/core/Any.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <yq/errors.hpp>
#include <yq/stream/Text.hpp>
#include "rapidxml.hpp"

namespace yq {
    namespace errors {
        using no_document   = error_db::entry<"XML has no owning document">;
    }

    std::error_code  write_xml(unsafe_k, XmlAttribute& x, const TypeMeta& type, const void*val)
    {
        if(!val)
            return errors::null_pointer();
            
        XmlDocument*    doc = document_for(x);
        if(!doc)
            return errors::no_document();
            
        auto fn1    = type.writer();
        if(fn1 && type.parser()){
            std::string     text;
            stream::Text    str(text);
            fn1(str, val);
            str.flush();
            write_x(x, text);
            return {};
        }
            
        auto fn2    = type.xml_attr_writer();
        if(fn2){
            fn2(x, val);
            return {};
        }
        
        auto fn3    = type.xml_base_writer();
        if(fn3){
            fn3(x, val);
            return {};
        }
        
        return errors::no_handler();
    }

    std::error_code  write_xml(unsafe_k, XmlBase& x, const TypeMeta& type, const void* val)
    {
        if(!val)
            return errors::null_pointer();
        XmlDocument*    doc = document_for(x);
        if(!doc)
            return errors::no_document();

        auto fn1    = type.writer();
        if(fn1 && type.parser()){
            std::string     text;
            stream::Text    str(text);
            fn1(str, val);
            str.flush();
            write_x(x, text);
            return {};
        }
            
        auto fn3    = type.xml_base_writer();
        if(fn3){
            fn3(x, val);
            return {};
        }
        
        return errors::no_handler();
    }
    

    std::error_code  write_xml(unsafe_k, XmlNode& x, const TypeMeta& type, const void* val)
    {
        if(!val)
            return errors::null_pointer();
        XmlDocument*    doc = document_for(x);
        if(!doc)
            return errors::no_document();

        auto fn1    = type.writer();
        if(fn1 && type.parser()){
            std::string     text;
            stream::Text    str(text);
            fn1(str, val);
            str.flush();
            write_x(x, text);
            return {};
        }
            
        auto fn2    = type.xml_node_writer();
        if(fn2){
            fn2(x, val);
            return {};
        }
        
        auto fn3    = type.xml_base_writer();
        if(fn3){
            fn3(x, val);
            return {};
        }
        
        //  *MIGHT* do something with properties/iterables here

        return errors::no_handler();
    }

    std::error_code write_xml_any(XmlAttribute&x, const Any&a)
    {
        return write_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }

    std::error_code write_xml_any(XmlBase&x, const Any&a)
    {
        return write_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }

    std::error_code write_xml_any(XmlNode&x, const Any&a)
    {
        return write_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }

/////////////////////////

    std::error_code read_xml(unsafe_k, const XmlAttribute& x, const TypeMeta& type, void* val)
    {
        if(!val)
            return errors::null_pointer();
            
        auto fn1 = type.parser();
        if(fn1 && type.writer())
            return fn1(val, x.value());
        
        auto fn2    = type.xml_attr_reader();
        if(fn2)
            return fn2(val, x);
        
        auto fn3    = type.xml_base_reader();
        if(fn3)
            return fn3(val, x);
        
        return errors::no_handler();
    }
    
    std::error_code read_xml(unsafe_k, const XmlBase& x, const TypeMeta& type, void* val)
    {
        if(!val)
            return errors::null_pointer();

        auto fn1 = type.parser();
        if(fn1 && type.writer())
            return fn1(val, x.value());
        
        auto fn3    = type.xml_base_reader();
        if(fn3)
            return fn3(val, x);
        
        return errors::no_handler();
    }
    
    std::error_code read_xml(unsafe_k, const XmlNode& x, const TypeMeta& type, void* val)
    {
        if(!val)
            return errors::null_pointer();
        auto fn1 = type.parser();
        if(fn1 && type.writer())
            return fn1(val, x.value());
        
        auto fn2    = type.xml_node_reader();
        if(fn2)
            return fn2(val, x);
        
        auto fn3    = type.xml_base_reader();
        if(fn3)
            return fn3(val, x);

        //  *MIGHT* do something with properties/iterables here
        
        return errors::no_handler();
    }

    std::error_code read_xml_any(const XmlAttribute&x, Any&a)
    {
        return read_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }

    std::error_code read_xml_any(const XmlBase&x, Any&a)
    {
        return read_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }

    std::error_code read_xml_any(const XmlNode&x, Any&a)
    {
        return read_xml(UNSAFE, x, a.type(), a.raw_ptr());
    }
}
