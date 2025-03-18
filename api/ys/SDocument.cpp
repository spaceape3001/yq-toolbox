////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SDocument.hpp"
#include "SObject.hpp"
#include <ys/bit/ID.hpp>
#include <yq/xml/XmlFile.hpp>
#include <yq/xml/XmlUtils.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/errors.hpp>
#include <ys/strings.hpp>
#include <ys/logging.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/text/match.hpp>
#include <yq/xml/XmlUtils.hpp>

namespace yq::spatial {
    SDocument::SDocument()
    {
        m_objects.push_back(nullptr);
    }
    
    SDocument::~SDocument()
    {
    }


    std::string_view        SDocument::attribute(const std::string&k) const
    {
        return m_attributes.get(k);
    }

    void                    SDocument::attribute_erase(const std::string&k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            SDocument::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    SDocument::attribute_set(const std::string& k, const std::string& v)
    {
        m_attributes.set(k,v);
    }
    
    void                    SDocument::attribute_set(const std::string& k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }

    const string_map_t&     SDocument::attributes() const
    {
        return m_attributes.data();
    }

    void                    SDocument::bump()
    {
        ++m_revision;
    }

    SObject*                SDocument::create(const SObjectInfo& info)
    { 
        return info.create(*this);
    }

    ID  SDocument::insert(SObject* obj)
    {
        if(!obj)
            return {};
        ID  ret{ (ID::id_t) m_objects.size() };
        m_objects.push_back(obj);
        return ret;
    }

    bool                    SDocument::is_attribute(const std::string&k) const
    {
        return m_attributes.contains(k);
    }
    
    bool                    SDocument::is_variable(const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    SObject*                SDocument::object(ID i)
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }
    
    const SObject*          SDocument::object(ID i) const
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }

    void                    SDocument::set_description(const std::string&d)
    {
        m_description = d;
        bump();
    }

    void                    SDocument::set_notes(const std::string& n)
    {
        m_notes = n;
        bump();
    }

    void                    SDocument::set_title(const std::string& t)
    {
        m_title = t;
        bump();
    }

    void    SDocument::uid_map(const std::string&s, ID )
    {
        // TODO
    }
    
    void    SDocument::uid_umap(const std::string&s, ID)
    {
        // TODO
    }

    std::string_view        SDocument::variable(const std::string&k) const
    {
        return m_variables.get(k);
    }

    void                    SDocument::variable_erase(const std::string&k)
    {
        m_variables.erase(k);
    }
    
    string_set_t            SDocument::variable_keys() const
    {
        return m_variables.keys();
    }
    
    void                    SDocument::variable_set(const std::string&k, const std::string&v)
    {
        m_variables.set(k, v);
    }
    
    void                    SDocument::variable_set(const std::string&k, std::string&&v)
    {
        m_variables.set(k, std::move(v));
    }
    
    const string_map_t&     SDocument::variables() const
    {
        return m_variables.data();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  B3
    

    bool     SDocument::census_b3(Census&, const std::filesystem::path&)
    {   
        b3Error << "B3 reading not yet implemented";
        return false;
    }

    template <typename Pred> 
    bool         SDocument::load_b3(ByteArray& bytes, Pred&& pred)
    {
        b3Error << "B3 reading not yet implemented";
        return false;
    }
    
    bool         SDocument::save_b3(const std::filesystem::path&) const
    {
        b3Error << "B3 saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  XML

    bool     SDocument::census_xml(Census&, const std::filesystem::path& fp)
    {
        XmlDocument doc;
        std::error_code ec  = read_file(doc, fp);
        if(ec != std::error_code())
            return false;
        const XmlNode* root = doc.first_node(szB3X);
        if(!root)
            return false;
        
        b3Error << "xml reading not yet implemented";
        return false;
    }

    bool         SDocument::read(const XmlDocument&doc)
    {
        const XmlNode* root = doc.first_node(szB3X);
        if(!root){
            b3Error << szExtXML << " does not contain the root element";
            return false;
        }
        
        b3Error << "xml reading not yet implemented";
        return false;
    }

    template <typename Pred> 
    bool         SDocument::load_xml(ByteArray& bytes, Pred&& pred)
    {
        XmlDocument doc;
        bytes << '\0';  // safety....

        try {
            doc.parse<0>(bytes.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - bytes.data();
            b3Error << "Xml parse error: " << pe.what() << " (at byte " << pt << ")";
            return false;
        }
        
        SDocument*p   = pred();
        if(!p)
            return false;
        
        return p->read(doc);
    }

    bool         SDocument::save_xml(const std::filesystem::path&) const
    {
        XmlDocument doc;
        
        
    
        b3Error << "xml saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  IO (High Level)

    static SFormat  guess_format(const std::filesystem::path& fp)
    {
        std::string sfx = fp.extension().string().substr(1);
        if(is_similar(sfx, SDocument::szExtB3))
            return B3;
        if(is_similar(sfx, SDocument::szExtXML))
            return XML;
        return SFormat::AUTO;
    }

    bool   SDocument::census(Census&ret, const std::filesystem::path&fp, SFormat fmt)
    {
        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);
        switch(fmt){
        case SFormat::XML:
            return census_xml(ret, fp);
        case SFormat::B3:
            return census_b3(ret, fp);
        default:
            b3Error << "Unable to determine format for " << fp.string();
            return false;
        }
    }

    template <typename Pred> 
    bool    SDocument::load(const std::filesystem::path& fp, SFormat fmt, Pred&& pred)
    {
        if(!file_exists(fp)){
            b3Error << "File does not exist.  " << fp.string();
            return false;
        }
        
        if(!file_readable(fp)){
            b3Error << "File is not readable.  " << fp.string();
            return false;
        }

        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);

        if(fmt == SFormat::AUTO){
            b3Error << "Unable to determine format for " << fp.string();
            return false;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        if(bytes.empty()){
            b3Error << "File is empty.  " << fp.string();
            return false;
        }
        
        switch(fmt){
        case SFormat::B3:
            return load_b3(bytes, std::move(pred));
        case SFormat::XML:
            return load_xml(bytes, std::move(pred));
        default:
            return false;
        }
    }

    SDocumentSPtr    SDocument::load(shared_k, const std::filesystem::path&fp, SFormat sf)
    {
        SDocumentSPtr   ret;
        
        bool    loaded  = load(fp, sf, [&]() -> SDocument* {
            ret = std::make_shared<SDocument>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    SDocumentUPtr    SDocument::load(unique_k, const std::filesystem::path&fp, SFormat sf)
    {
        SDocumentUPtr   ret;
        bool    loaded  = load(fp, sf, [&]() -> SDocument* {
            ret = std::make_unique<SDocument>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    SDocument*       SDocument::load(raw_k, const std::filesystem::path&fp, SFormat sf)
    {
        SDocument*  ret = nullptr;
        bool    loaded  = load(fp, sf, [&]() -> SDocument* {
            ret = new SDocument;
            return ret;
        });
        if(loaded)
            return ret;
        if(ret)
            delete ret;
        return nullptr;
    }

    bool             SDocument::save(const std::filesystem::path&fp, SFormat fmt) const
    {
        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);
        switch(fmt){
        case SFormat::B3:
            return save_b3(fp);
        case SFormat::XML:
            return save_xml(fp);
        default:
            b3Error << "Unable to determine format for " << fp.string();
            return false;
        }
    }
}
