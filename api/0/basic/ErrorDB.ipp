////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ErrorDB.hpp"
#include <atomic>
#include <mutex>

#include <0/basic/Logging.hpp>

namespace yq {
    namespace error_db {
        struct Table {
            static constexpr const size_t       N   = 2047;
            std::string_view        reasons[N]  = {};
            std::atomic<Table*>     next        = nullptr;
            std::atomic<size_t>     count       = { 0 };
            
            std::string_view    get(size_t n) const
            {
                if(n>=N){
                    const Table*    t   = next;
                    if(!t)
                        return std::string_view();
                    return t->get(n-N);
                }
            
                size_t  j   = count;
                if(n >= j)
                    return std::string_view();
                return reasons[n];
            }
            
            size_t  add(std::string_view v)
            {
                size_t  n   = count;
                if( n >= N){    // shouldn't ever be higher....
                    Table   *t  = next;
                    if(!t)
                        next = t = new Table;
                    return N + t->add(v);
                }
                reasons[n]  = v;
                ++count;
                return n;
            }
        };
        
        struct Repo {
            using map_t = std::map<std::string_view, size_t>;
        
            Table               db;
            std::mutex          mutex;
            map_t               lut;
            std::atomic<size_t> count = { 0 };
            
            Repo()
            {
                yInfo() << "Size of error_db::Table is " << sizeof(Table);
                db.add("Unspecified/unknown error");
            }
            
            size_t add(std::string_view z)
            {
                std::scoped_lock    _lock(mutex);
                auto [i, f] = lut.insert({ z, -1 });
                if(f){
                    i->second   = db.add(z);
                    count       = i->second;
                }
                return i->second;
            }
            
            std::string_view    message(size_t n) const
            {
                if(n > count)
                    n   = 0;
                std::string_view    m   = db.get(n);
                if(m.empty())
                    m   = db.reasons[0];
                return m;
            }
        };
        
        Repo& repo()
        {
            static Repo*    s_repo  = new Repo;
            return *s_repo;
        }
        
        int reason(const char* c)
        {
            if(!c)          // no nulls
                return 0;
            if(!*c)         // no empties
                return 0;
            return (int) repo().add(c);
        }
        
        class Category : public std::error_category {
        public:
            Category() {}
            
            const char* name() const noexcept override 
            { 
                return "YQ Errors";
            }

            std::string message(int c) const override
            {
                return std::string(repo().message((size_t) c));
            }
        };
        
        const std::error_category& category()
        {
            static Category*    s_ret   = new Category;
            return *s_ret;
        }
        

        std::error_code make_error(const char* z)
        {
            return std::error_code( reason(z), category());
        }
    }

}
