////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StdFile.hpp"

#include <yq/errors.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/basic/Logging.hpp>
#include <yq/io/KeyValue.hpp>
#include <yq/io/stream/Text.hpp>
#include <yq/io/StreamOps.hpp>

#include <rapidxml.hpp>

namespace yq::errors {
    using bad_std_syntax    = error_db::entry<"Bad Key/Value Parsing">;
}

namespace yq {
    std::error_code    StdFile::read(ByteArray&&buffer, std::string_view fname) 
    {
        std::string_view    file    = buffer.as_view();
        if(xml_read() && starts_igCase(file, "<?xml")){
            buffer << '\0';
            XmlDocument     doc;
            try {
                doc.parse<0>(buffer.data());
            } catch(const rapidxml::parse_error& pe){
                size_t  pt  = pe.where<char>() - buffer.data();
                yError() << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << fname;
                return errors::xml_bad_syntax();
            }
            
            std::error_code ec  = read(doc,fname);
            if(ec != errors::none() || !xml_auto_convert())
                return ec;
            
            //  overwrite with key-value
            return save_to(fname);
        } else {
            KVTree      tree;
            
            unsigned int    opts    = 0;
            if(has_body())
                opts |= KVTree::BODY;
            if(recursive_attributes())
                opts |= KVTree::RECURSIVE;
            
                // which will e boolean until key-values return std::error_code
            auto ret    = tree.parse(buffer.as_view(), fname, opts);
            if(ret.ec != std::error_code()) [[unlikely]]
                return ret.ec;
            if(has_body())
                return read(std::move(tree), ret.body, fname);
            else
                return read(std::move(tree), fname);
        }
    }

    std::error_code     StdFile::read(KVTree&&, std::string_view, std::string_view) 
    { 
        return errors::none();
    }
    
    std::error_code StdFile::write(KVTree&, Stream&) const 
    { 
        return errors::none();
    }

    std::error_code     StdFile::read(KVTree&&, std::string_view) 
    { 
        return errors::none();
    }
    
    std::error_code    StdFile::write(KVTree&) const 
    { 
        return errors::none();
    }
    
    std::error_code  StdFile::read(const XmlDocument&, std::string_view) 
    { 
        return errors::todo();
    }

    std::error_code    StdFile::write(yq::Stream& buffer) const
    {
        KVTree          tree;
        std::string     body;
        std::error_code ec;
        
        if(has_body()){
            stream::Text        text(body);
            ec  = write(tree, text);
        } else {
            ec  = write(tree);
        }
        
        if(ec != errors::none())
            return ec;
        
        tree.write(buffer);
        if(!body.empty())
            buffer << '\n' << body;
        return errors::none();
    }

    std::error_code     StdFile::write(XmlDocument&) const
    {
        return errors::todo();
    }
}
