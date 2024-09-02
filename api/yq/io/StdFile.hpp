////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/io/AbstractFile.hpp>
#include <yq/config/xml_fwd.hpp>

namespace yq {
    class Stream;
    class ByteArray;
    class KVTree;

    class StdFile : public AbstractFile {
    public:

        //! Enable if attributes can recurse
        virtual bool        recursive_attributes() const { return true; }
        
        //! Enable if we're expecting body (ie, context)
        virtual bool        has_body() const { return false; }
        
        //! Enable if we tolerate XML loading (not saving)
        virtual bool        xml_read() const { return false; }
        
        //! Enabled to seamless rewrite XML to STD format
        virtual bool        xml_auto_convert() const { return true; }

    protected:
        //! Reading (from abstract file)
        virtual std::error_code     read(ByteArray&&buffer, std::string_view fname) override;
        //! Writing (from abstract file)
        virtual std::error_code     write(Stream&) const override;
        
        //  override depending on has_body() above
        
        //! Override to read with body
        virtual std::error_code     read(KVTree&&, std::string_view body, std::string_view fname);
        
        //! Override to write with body
        virtual std::error_code     write(KVTree&, Stream&) const;

        //! Override to read without body
        virtual std::error_code     read(KVTree&&, std::string_view fname);
        
        //! Override to write without body
        virtual std::error_code     write(KVTree&) const;
        
        //! Override to read from XML instead
        virtual std::error_code     read(const XmlDocument&, std::string_view fname);
        
        virtual std::error_code     write(XmlDocument&) const;
    };
}
