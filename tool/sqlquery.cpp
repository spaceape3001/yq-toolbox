////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <0/basic/Vector.hpp>
#include <0/basic/Logging.hpp>
#include <0/sql/SqlLite.hpp>
#include <0/sql/SqlQuery.hpp>
#include <0/basic/TextUtils.hpp>

using namespace yq;

struct Column {
    std::string         name;
    Vector<std::string> data;
    size_t              width   = 0;
    
    Column(std::string_view n) : name(n), width(n.size()) {}
    void    add(std::string_view d)
    {
        data << copy(d);
        width = std::max(width, d.size());
    }
};

int main(int argc, char **argv)
{
    if(argc < 3){
        std::cerr << "Usage: " << argv[0] << " (database) (sql-statement)\n";
        return -1;
    }
    
    log_to_std_error();

    SqlLite db;
    if(!db.open(argv[1])){
        std::cerr << "Failed to open the specified database.\n";
        return -1;
    }
    
    SqlQuery sql(db, argv[2]);
    if(!sql.valid()){
        std::cerr << "SQL failed to parse.\n";
        return -1;
    }

    SQResult    r;
    int     cc  = sql.column_count();
    if(cc<=0){
        r   = sql.step();
        if(r == SQResult::Done){
            std::cout << "Qapla'!\n";
            return 0;
        }
        std::cout << "Bad SQL Execution\n";
        return -1;
    }
    
    Vector<Column>      data;
    for(int i=0;i<cc; ++i)
        data << Column(sql.column_name(i+1));
    
    int              count = 0;
    
    while((r = sql.step()) == SQResult::Row){
        ++ count;
        for(int i=0;i<cc;++i)
            data[i].add( sql.v_text(i+1));
    }
    
    std::cout << count << " Results.\n";;
    std::cout << "\n";

    int     n = 0;
    for(auto& c : data){
        if(c.width == 0)
            c.width = 1;
        if(n)
            std::cout << '|';
        std::cout << ' ';
        std::cout << pad_right(c.name, c.width);
        std::cout << ' ';
        n += c.width;
    }
    std::cout << '\n';
    n       = 0;
    for(auto& c : data){
        if(n++)
            std::cout << '+';
        std::cout << pad_right(""sv, c.width+2, '-');
    }
    std::cout << '\n';
    
    //  now, the data
    for(int i=0;i<count;++i){
        n   = 0;
        for(auto& c : data){
            if(n++)
                std::cout << '|';
            std::cout << ' ';
            std::cout << pad_right(c.data[i], c.width);
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    
    std::cout << '\n';
    std::cout << "Qapla'!\n";

    return 0;
}
