////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "KeyValue.hpp"
#include <yq/container/ByteArray.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/stream/LineCol.hpp>

namespace yq {
#if 0
    namespace {
        string_view_set_t   make_set(const std::vector<const KeyValue*>&subs, const std::string_view& sep)
        {
            string_view_set_t       ret;
            for(const KeyValue* a : subs){
                if(!a)
                    continue;
                
                
                for(const std::string_view& s : split(a->data, sep)){
                    std::string_view v   = trimmed(s);
                    if(v.empty())
                        continue;
                    ret << v;
                }
            }
            return ret;
        }
    }
#endif

        #if 0
        namespace {
            std::vector<AttrData>::iterator      find(std::vector<AttrData>& dst, const AttrData& ref)
            {
                for(auto i = dst.begin(); i != dst.end(); ++i){
                    if(!is_similar(i->key, ref.key))
                        continue;
                    if(ref.id != i->id)
                        continue;
                    if(!is_similar(ref.root_dir, i->root_dir))
                        continue;
                }
                return dst.end();
            }

            void    fuse(std::vector<AttrData>& dst, const std::vector<AttrData>& src, const RootDir* rt)
            {
                for(const AttrData& a : src){
                    switch(a.action){
                    case Action::Add:
                        dst << a;
                        dst.back().root_dir = rt -> key();
                        break;
                    case Action::Modify: {
                        auto i = find(dst, a);
                        if(i != dst.end()){
                            //  TODO
                            fuse(i->sub, a.sub, rt);
                        }
                        break;
                    }
                    case Action::Remove: {
                        auto i = find(dst, a);
                        if(i != dst.end())
                            dst.erase(i);
                        break;
                    }
                    case Action::Existing: {
                        auto i = find(dst, a);
                        if(i != dst.end())
                            fuse(i->sub, a.sub, rt);
                        break;
                    }
                    }
                }
                
            }
        }
        #endif
    
    size_t              KVTree::count_keys(std::string_view z) const
    {
        size_t  cnt = 0;
        for(auto& a : subs)
            if(is_similar(a.key, z))
                ++cnt;
        return cnt;
    }

    size_t              KVTree::count_all() const
    {
        size_t  cnt = subs.size();
        for(auto& a : subs)
            cnt += a.count_all();
        return cnt;
    }

    KeyValue*           KVTree::first(std::initializer_list<const char*>z)
    {
        return first(kv::key(z));
    }

    const KeyValue*     KVTree::first(std::initializer_list<const char*>z) const
    {
        return first(kv::key(z));
    }

    void                KVTree::fusion(const KVTree&rhs) 
    {
        //  TODO properly (LATER)
        subs    += rhs.subs;
    }


    size_t              KVTree::max_key_size(bool recursive) const
    {
        size_t  mx  = 0;
        for(auto& a : subs){
            mx      = std::max(mx, a.key.size());
            if(recursive)
                mx  = std::max(mx, a.max_key_size(true));
        }
        return mx;
    }

    KeyValue*  KVTree::set(std::string_view key, std::string_view data, bool purge)
    {
        return set(kv::key(key), key, data, purge);
    }
    
    KeyValue*  KVTree::set(std::string_view key, std::string&& data, bool purge)
    {
        return set(kv::key(key), key, std::move(data), purge);
    }
    
    KeyValue*  KVTree::set(const string_view_vector_t& keys, std::string_view  data, bool purge)
    {
        return set(kv::key(keys), *(keys.begin()), data, purge);
    }

    KeyValue*  KVTree::set(const string_view_vector_t& keys, std::string&&  data, bool purge)
    {
        return set(kv::key(keys), *(keys.begin()), std::move(data), purge);
    }
    
    KeyValue*  KVTree::set(const std::initializer_list<std::string_view>& keys, std::string_view data, bool purge)
    {
        return set(kv::key(keys), *(keys.begin()), data, purge);
    }

    KeyValue*  KVTree::set(const std::initializer_list<std::string_view>& keys, std::string&& data, bool purge)
    {
        return set(kv::key(keys), *(keys.begin()), std::move(data), purge);
    }
    

    //std::string_view KVTree::value(std::initializer_list<const char*>z) const
    //{
        //return value(kv::key(z));
    //}
    


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    KVTree&          KVTree::operator+=(KeyValue&& v)
    {
        subs << std::move(v);
        return *this;
    }

    KVTree&          KVTree::operator+=(const KeyValue& v)
    {
        subs << v;
        return *this;
    }

    KVTree&          KVTree::operator+=(KVTree&&rhs)
    {
        // FULL TODO (later)
        subs += std::move(rhs.subs);
        return *this;
    }

    KVTree&          KVTree::operator+=(const KVTree&rhs)
    {
        // FULL TODO (later)
        subs += rhs.subs;
        return *this;
    }

    KVTree&           KVTree::operator<<(KeyValue&&v)
    {
        subs << std::move(v);
        return *this;
    }

    KVTree&           KVTree::operator<<(const KeyValue&v)
    {
        subs << v;
        return *this;
    }



    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    namespace {

        void    add_attr(Vector<KeyValue>&datas, size_t&i, KeyValue&v)
        {
            size_t      z   = datas[i].indent;
            v.subs << std::move(datas[i]);
            while( (++i) < datas.size()){
                if(datas[i].indent == z){
                    v.subs << std::move(datas[i]);
                    continue;
                } 
                
                while((i < datas.size()) && (datas[i].indent > z))
                    add_attr(datas, i, v.subs.back());

                if(i >= datas.size())
                    break;
                if(datas[i].indent < z)
                    break;
                    
                v.subs << std::move(datas[i]);
            }
        }
        
    }

    KVTree::Parsed   KVTree::parse(std::string_view buffer, std::string_view fname, unsigned int opts)
    {
        if(buffer.empty())
            return { std::string_view(), errors::none() };
            
        enum class Mode {
            SPACE,          //!< Space at start of line
            CMD,            //!< Cmd at the start of the line
            CMDS,           //!< Space between command and ID
            ID,             //!< ID
            IDS,            //!< Space between ID and key
            KEY,            //!< Key
            KEYS,           //!< Space between key and data
            VALUE,          //!< Everything afterwards to new-line
            BODY            //!< Body of the document
        };

        Mode            mode        = Mode::SPACE;
        bool            doBody      = static_cast<bool>(opts & BODY);
        
        const char*     bstart      = nullptr;

        KeyValue        val;
        unsigned int    line    = 1;
        unsigned int    lident  = 0;
        Vector<KeyValue>   datas;

        auto push   = [&](){
            if(!val.empty()){
                lident  = val.indent;
                if(!val.data.empty() && val.data.back() == '"')
                    val.data.pop_back();
                
                datas << std::move(val);
                val     = KeyValue();
            }
            mode    = Mode::SPACE;
        };
        
        for(const char& ch : buffer){
            if(!ch)
                continue;
            switch(mode){
            case Mode::BODY:
                //if(ch)
                    //*body += ch;
                break;
            case Mode::SPACE:
                switch(ch){
                case '#':
                    val.cmd = "#";
                    mode    = Mode::VALUE;
                    break;
                case '\n':
                    if(doBody){
                        bstart  = &ch;
                        mode    = Mode::BODY;
                    } else {
                        //  No body means a new attribute, clone the last indent
                        KeyValue   a;
                        a.indent    = lident;
                        datas << a;
                    }
                    ++line;
                    break;
                case '%':
                    mode    = Mode::KEY;
                    val.key += '%';
                    break;
                case '[':
                    mode    = Mode::ID;
                    break;
                default:
                    if(ispunct(ch)){
                        mode    = Mode::CMD;
                        val.cmd += ch;
                        break;
                    }
                    if(isalnum(ch)){
                        mode    = Mode::KEY;
                        val.key += ch;
                        break;
                    }
                    if(isspace(ch)){
                        if(datas.empty() && !val.indent){
                            yWarning() << "First attribute should always start left-adjusted! " << line << " : " << fname;
                        }
                        ++ val.indent;
                        break;
                    }
                    //  This state is an error!
                    yError() << "Non processible character (in blank-line) found on line " << line << " : " << fname;
                    break;
                }
                break;
            case Mode::CMD:
                if(isspace(ch)){
                    mode    = Mode::CMDS;
                    break;
                }
                if(isalnum(ch) || ispunct(ch)){
                    val.cmd += ch;
                    break;
                }
                if(ch == '\n'){
                    push();
                    break;
                }
                break;
            case Mode::CMDS:
                switch(ch){
                case '[':
                    mode    = Mode::ID;
                    break;
                case '\n':
                    push();
                    break;
                default:
                    if(isalnum(ch)){
                        val.key += ch;
                        mode    = Mode::KEY;
                        break;
                    }
                    if(isspace(ch))
                        break;
                    yError() << "Non processible character (in post command space) found on line " << line << " : " << fname;
                    break;
                }
                break;
            case Mode::ID:
                switch(ch){
                case ']':
                    mode    = Mode::IDS;
                    break;
                case '\n':
                    yError() << "Line break during ID, on line " << line << " : " << fname;
                    push();
                    break;
                case '[':
                    yError() << "Stray '[' detected on line " << line << " : " << fname;
                    break;
          
                default:
                    if(isalnum(ch) || ispunct(ch)){
                        val.id += ch;
                        break;
                    }
                    if(isspace(ch)){
                        yError() << "Erroneous space detected in ID on line " << line << " : " << fname;
                        break;
                    }
                    break;
                }
                break;
            case Mode::IDS:
                switch(ch){
                case '\n':
                    push();
                    break;
                default:
                    if(isalnum(ch)){
                        val.key += ch;
                        mode    = Mode::KEY;
                        break;
                    }
                    if(isspace(ch))
                        break;
                        
                    yError() << "Non processible character (in post ID space) found on line " << line << " : " << fname;
                    break;
                }
                break;
            case Mode::KEY:
                switch(ch){
                case '\n':
                    push();
                    break;
                default:
                    if(isalnum(ch) || ispunct(ch)){
                        val.key += ch;
                        break;
                    }
                    if(isspace(ch)){
                        mode        = Mode::KEYS;
                        break;
                    }
                    yError() << "Non processible character (in post key space) found on line " << line << " : " << fname;
                    break;
                }
                break;
            case Mode::KEYS:
                switch(ch){
                case '\n':
                    push();
                    break;
                case '"':
                    mode        = Mode::VALUE;
                    break;
                default:
                    if(isspace(ch)){
                        break;
                    } else {
                        val.data += ch;
                        mode    =    Mode::VALUE;
                        break;
                    }
                    break;
                }
                break;
            case Mode::VALUE:
                if(ch == '\n'){
                    push();
                } else {
                    val.data += ch;
                }
                break;
            }
            
            if(bstart)
                break;
        }
        

        Parsed  ret{ std::string_view(), errors::none() };
        if(datas.empty())
            return ret;

        if(bstart)
            ret.body    = std::string_view(bstart, buffer.end());
            
        if(static_cast<bool>(opts & RECURSIVE)){
            unsigned int        z   = datas[0].indent;
            for(size_t i=0; i<datas.size(); ++i){
                if(datas[i].indent <= z){
                    subs << std::move(datas[i]);
                } else {
                    add_attr(datas, i, subs.back());
                    if(i<datas.size())
                        subs << std::move(datas[i]);
                }
            }
        } else {
            subs       = std::move(datas);
        }
        
        return ret;
    }

    namespace {
        size_t      max_pad(const KVTree& at)
        {
            size_t  a   = 0;
            for(const KeyValue& v : at.subs){
                if(v.empty())
                    continue;
                if(v.cmd == "#")
                    continue;
                size_t  b   = v.cmd.size() + v.id.size() + v.key.size();
                if(!v.cmd.empty())
                    ++b;
                if(!v.id.empty())
                    b += 3;
                a   = std::max({a,b,max_pad(v)});
            }
            ++a;
            return a;
        }

        void       write_subs(yq::stream::LineCol& out, const std::vector<KeyValue>&datas, unsigned int mxval, unsigned int depth=0) 
        {
            for(const KeyValue& v : datas){
                if(v.empty()){
                    out << '\n';
                    continue;
                }

                for(unsigned int n = 0;n<depth;++n)
                    out << "    ";
                    
                if(v.cmd == "#"){
                    out << "#" << v.data << '\n';
                } else {
                    size_t  tgt = mxval + out.column();
                    if(!v.cmd.empty())
                        out << v.cmd << ' ';
                    if(!v.id.empty())
                        out << '[' << v.id << ']' << ' ';
                    if(!v.key.empty())
                        out << v.key;
                    while(out.column() < tgt)
                        out << ' ';
                    out << v.data << '\n';
                }
                write_subs(out, v.subs, mxval, depth+1);
            }
        }

    }




    void    KVTree::write(yq::Stream& out) const
    {
        yq::stream::LineCol     counter(out);
        write_subs(counter, subs, max_pad(*this));
    }



    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool                KeyValue::empty() const
    {
        return cmd.empty() && id.empty() && key.empty() && data.empty() && subs.empty(); 
    }
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    namespace kv {
        bool SingleKeyMatch::operator()(const KeyValue& a) const
        {
            return is_in(a.key, pat);
        }

        SingleKeyMatch        key(std::string_view s) 
        { 
            return SingleKeyMatch{s}; 
        }

            //  ------------------------------------------------------------------------------------------------

        bool InitKeyMatch::operator()(const KeyValue& a) const
        {
            return is_in(a.key, pat);
        }

        //inline InitKeyMatch          key(std::initializer_list<std::string_view> s) { return InitKeyMatch{s}; }
        //inline InitKeyMatch          key(std::string_view a, std::string_view b) { return InitKeyMatch{{a, b}}; }
        //inline InitKeyMatch          key(std::string_view a, std::string_view b, std::string_view c) { return InitKeyMatch{{a, b, c}}; }
        //inline InitKeyMatch          key(std::string_view a, std::string_view b, std::string_view c, std::string_view d) { return InitKeyMatch{{a, b, c, d}}; }
        //inline InitKeyMatch          key(std::string_view a, std::string_view b, std::string_view c, std::string_view d, std::string_view e) { return InitKeyMatch{{a, b, c, d, e}}; }

            //  ------------------------------------------------------------------------------------------------

        bool PtrVectorKeyMatch::operator()(const KeyValue& a) const
        {
            return is_in(a.key, *pat);
        }


            //  ------------------------------------------------------------------------------------------------

        bool VectorKeyMatch::operator()(const KeyValue& a) const
        {
            return is_in(a.key, pat);
        }

            //  ------------------------------------------------------------------------------------------------
            
        VectorKeyMatch        key(const std::vector<std::string_view>& s) 
        { 
            return VectorKeyMatch(s); 
        }

        VectorKeyMatch        key(std::initializer_list<const char*> keys) 
        { 
            VectorKeyMatch ret;
            for(auto& k : keys)
                ret.pat.push_back(k);
            return ret;
        }
        
        VectorKeyMatch          key(std::initializer_list<std::string_view> s) 
        { 
            VectorKeyMatch ret;
            for(auto& k : s)
                ret.pat.push_back(k);
            return ret;
        }

        VectorKeyMatch          key(std::string_view a, std::string_view b) 
        { 
            VectorKeyMatch ret;
            ret.pat.push_back(a);
            ret.pat.push_back(b);
            return ret;
        }
        
        VectorKeyMatch          key(std::string_view a, std::string_view b, std::string_view c) 
        { 
            VectorKeyMatch ret;
            ret.pat.push_back(a);
            ret.pat.push_back(b);
            ret.pat.push_back(c);
            return ret;
        }
        
        VectorKeyMatch          key(std::string_view a, std::string_view b, std::string_view c, std::string_view d) 
        { 
            VectorKeyMatch ret;
            ret.pat.push_back(a);
            ret.pat.push_back(b);
            ret.pat.push_back(c);
            ret.pat.push_back(d);
            return ret;
        }
        
        VectorKeyMatch          key(std::string_view a, std::string_view b, std::string_view c, std::string_view d, std::string_view e) 
        { 
            VectorKeyMatch ret;
            ret.pat.push_back(a);
            ret.pat.push_back(b);
            ret.pat.push_back(c);
            ret.pat.push_back(d);
            ret.pat.push_back(e);
            return ret;
        }

            //  ------------------------------------------------------------------------------------------------

        bool SetKeyMatch::operator()(const KeyValue& a) const
        {
            return is_in(a.key, pat);
        }

            //  ------------------------------------------------------------------------------------------------
    }
}
