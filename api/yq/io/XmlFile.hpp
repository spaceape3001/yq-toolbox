////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/basic/Enum.hpp>
#include <yq/config/xml_fwd.hpp>
#include <yq/io/AbstractFile.hpp>
#include <initializer_list>

namespace yq {

    class XmlFile : public AbstractFile {
    public:

    protected:
        XmlFile();
        ~XmlFile();

        virtual std::error_code    read(const XmlDocument&, std::string_view fname) = 0;
        virtual std::error_code    write(XmlDocument&) const = 0;

        virtual std::error_code    read(ByteArray&&, std::string_view fname) override;
        virtual std::error_code    write(yq::Stream&) const override;

        virtual bool    is_binary() const override { return false; }
    };
    
}
