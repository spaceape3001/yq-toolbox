////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/polymesh3.hpp>
#include <type_traits>
#include <yq/keywords.hpp>
#include <vector>

namespace yq {
    template <typename> struct Vector3;
    
    template <typename T, typename I>
    struct Polymesh3 {
        static_assert(std::is_unsigned_v<I>, "Indexes need to be unsigned!");
    
        using component_type        = T;
        using index_type            = I;
        using point_type            = Vector3<T>;
    
        struct Face {
            std::vector<index_type> vertex;
            
            bool operator==(const Face&) const;
        };

        struct Line {
            std::vector<index_type> vertex;

            bool operator==(const Line&) const;
        };
    
        std::vector<point_type>     vertices;
        std::vector<Face>           faces;
        std::vector<Line>           lines;
        std::vector<I>              points;
        
        Polymesh3(){}
        ~Polymesh3(){}
        
        const Face&         face(I i) const;
        Face&               face(I i);
        const Line&         line(I i) const;
        Line&               line(I i);
        const point_type&   vertex(I i) const;
        point_type&         vertex(I i);
        
        bool    operator==(const Polymesh3&) const;
    };
}
