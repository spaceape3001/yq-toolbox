////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/PVector.hpp>
#include <yq/container/Array.hpp>
#include <vector>

#include <0/basic/Logging.hpp>

namespace yq {

    namespace diff {
        
        template <typename T>
        bool    cxx_equality(const T& a, const T& b)
        {
            return a == b;
        }
    
        struct match_t {
            SizeRange   x = {}, y = {};
            ssize_t     D = 0;
            
            constexpr bool    operator==(const match_t&) const noexcept = default;
        };
        
       enum class Edit : uint8_t {
            Same,
            Add,
            Remove
        };
        
        
        //! Option to use in lieu of assertion
        static constexpr const unsigned int THROW    = 0x1;
        
        static constexpr const unsigned int NOISY    = 0x2;

        static constexpr const unsigned int NOISY_MS = 0x4;


        struct edit_t {
            SizeRange       left    = {}, right = {};
            size_t          cnt     = 0;
            Edit        type    = Edit{};
            
            constexpr bool  operator==(const edit_t&) const noexcept = default;
        };


        template <typename VA, typename VB, typename Equivalent>
        match_t middle_snake(const std::vector<VA>& A, SizeRange X, const std::vector<VB>& B, SizeRange Y, Equivalent equiv, unsigned int opts=0)
        {
            static constexpr const unsigned int     NOISE_MASK  = NOISY | NOISY_MS;
        
            assert(X.count() < SIZE_MAX / 2);
            assert(Y.count() < SIZE_MAX / 2);
        
            if(opts&NOISE_MASK){
                yInfo() << "yq::diff::middle_snake([" << X.low << "," << X.high << "], [" << Y.low << "," << Y.high << "])";
            }

            ssize_t N       = (ssize_t) X.count();
            ssize_t M       = (ssize_t) Y.count();
            ssize_t mx      = N + M;
            ssize_t delta   = N - M;
            ssize_t         x, y, xi, yi, D, k;

            if(opts&NOISE_MASK){
                yInfo() << "N -> " << X.count();            
                yInfo() << "M -> " << Y.count();            
                yInfo() << "MAX -> " << mx;
                yInfo() << "DELTA -> " << delta;
            }
            
            PVector<ssize_t>    Vf, Vb;
            
            Vf.resize(mx+2, 0ULL);
            Vb.resize(mx+2, 0ULL);

            for(D = 0; D <= mx/2+(mx%2); ++D){
                if(opts&NOISE_MASK){
                    yInfo() << "Main loop D = " << D;
                }
                for(k=-D;k<=D;k+=2){
                    if((k==-D) || ((k!=D) && (Vf[k-1] < Vf[k+1]))){
                        x   = Vf[k+1];
                    } else
                        x   = Vf[k-1]+1;
                    y   = x - k;
                    xi  = x;
                    yi  = y;
                    if(opts&NOISE_MASK){
                        yInfo() << "L1 k " << k << " x=" << x << " y=" << y;                
                    }
                    while((x<N) && (y<M) && equiv(A[X.low+x], B[Y.low+y]))
                    {
                        ++x, ++y;
                        if(opts&NOISE_MASK){
                            yInfo() << "L1 BUMP";
                        }
                    }
                    Vf[k]   = x;
                    
                    ssize_t knd = k - delta;
                    if(opts&NOISE_MASK){
                        yInfo() << "  ---> x=" << x << " y=" << y << " --> Vf[" << k << "]:=" << x << " & (k-delta)=" << knd;
                    }

                    if(((delta%2) != 0) && (-knd >= -(D-1)) && (-knd <= (D-1))){
                        if(opts&NOISE_MASK){
                            yInfo() << "L1 possible";                    
                        }
                        if(Vf[k] + Vb[-knd] >= N){
                            if(opts&NOISE_MASK){
                                yInfo() << "L1 Match detected";
                            }
                            return match_t{ 
                                { xi+X.low, x + X.low },
                                { yi+Y.low, y + Y.low },
                                2*D-1, 
                            };
                        }
                    }
                }
                for(k=-D;k<=D;k+=2){
                    if((k==-D) || ((k!=D) && (Vf[k-1] < Vf[k+1]))){
                        x   = Vb[k+1];
                    } else
                        x   = Vb[k-1]+1;
                    y   = x - k;
                    xi  = x;
                    yi  = y;
                    if(opts&NOISE_MASK){
                        yInfo() << "L2 k " << k << " x=" << x << " y=" << y;                
                    }
                    while((x<N) && (y<M) && equiv(A[X.low+N-x-1], B[Y.low+M-y-1])){
                        ++x, ++y;
                        if(opts&NOISE_MASK){
                            yInfo() << "L2 BUMP";
                        }
                    }
                    Vb[k]   = x;
                    ssize_t knd = k - delta;
                    if(opts&NOISE_MASK){
                        yInfo() << "  ---> x=" << x << " y=" << y << " --> Vb[" << k << "]:=" << x << " & (k-delta)=" << knd;
                    }
                    if(((delta%2) == 0) && (-knd >= -D) && (-knd <= D)){
                        if(opts&NOISE_MASK){
                            yInfo() << "L2 possible";                    
                        }
                        if(Vb[k]+Vf[-knd] >= N){
                            if(opts&NOISE_MASK){
                                yInfo() << "L2 Match detected";
                            }
                            return match_t{
                                { N + X.low - x, N + X.low - xi }, 
                                { M + Y.low - y, M + Y.low - yi },
                                2*D
                            };
                        }
                    }
                }
            }
            
            if(opts & THROW){
                throw std::logic_error("Middle snake failed");
            } else {
                assert(false && "MIDDLE SNAKE FAILED!");
            }
            
            return {};  // It is a LOGIC ERROR to reach here, however, adding this in to hush the warning
        }
        
        template <typename T>
        match_t middle_snake(const std::vector<T>& A, SizeRange X, const std::vector<T>& B, SizeRange Y, unsigned int opts=0)
        {
            return middle_snake(A,X,B,Y, std::equal<T>, opts);
        }

        template <typename T>
        match_t middle_snake(const std::vector<T>& A, const std::vector<T>& B, unsigned int opts=0ULL)
        {
            return middle_snake(A,SizeRange{0ULL, A.size()},B,SizeRange{0ULL, B.size()}, cxx_equality<T>, opts);
        }

        /*! \brief Difference Engine 
            
            This routine compares the items in the two vectors, giving the edits needed for the transformation.
            These edits are simple, they do not track whether a add/remove pair is modification or simply 
            a change, that's up to the caller.  

            \tparam VA          The left side of the comparison
            \tparam VB          The right side of the comparison (can be the same)
            \tparam Equivalent  An equivalent operator "==", expecting Equivalent(VA(),VB()) => boolean
            \tparam Added       The *ADDED* functor, taking in a range, expecting Added(SizeRange) for rows added (in B)
            \tparam Removed     The *REMOVED* functor, taking in a range, expecting Removed(SizeRange) for rows removed (in A)
            \tparam Untouched   The untouched, taking in two ranges, expecting Untouched(SizeRange xRows, SizeRows yRows)
            
            \param A            The left vector
            \param X            Range of A being differenced
            \param B            The right vector
            \param Y            Range of B being differenced
            \param equiv        Equivalency functor (expecting arguments of VA, VB)
            \param untouched    Untouched sink, handling the untouched/unchanged mappings from A to B
            \param add          Added item sink, handling the entries in B that aren't in A
            \param remove       Removed item sink, handling the entries in A that aren't in B
            \param opts         Options.  Note, altering to THROW will cause the middle snake to throw an exception in lieu of asserting
            \param depth        Used within to track how many calls deep into the recursion we are
            
            \note The calls to untouched, add, and remove should be in sequential order.
            
            This routine is based on https://github.com/RobertElderSoftware/roberteldersoftwarediff/blob/master/myers_diff_and_variations.py
        */
        template <typename VA, typename VB, typename Equivalent, typename Untouched, typename Added, typename Removed> 
        void    diff_engine(const std::vector<VA>& A, SizeRange X, const std::vector<VB>& B, SizeRange Y, Equivalent equiv, Untouched untouched, Added add, Removed remove, unsigned int opts=0ULL, unsigned int depth=0)
        {
            std::string     pad;
            if(opts&NOISY){
                pad = std::string(depth*2, ' ');
                yInfo() << pad << "yq::diff::diff_engine([" << X.low << "," << X.high << "], [" << Y.low << "," << Y.high << "], " << depth << ")";
            }

            if(X.not_empty() && Y.not_empty()){
                auto dd = middle_snake(A, X, B, Y, equiv, opts & ~NOISY);
                
                if(opts&NOISY){
                    yInfo() << pad << "Match { D=" << dd.D << " x=" << dd.x.low << " y=" << dd.y.low << " u=" << dd.x.high << " v=" << dd.y.high << " }";
                }

                if((dd.D > 1) || (dd.x.not_empty() && dd.y.not_empty())){
                    if(opts&NOISY){
                        yInfo() << pad << " branch A";
                    }
                    //  There's a snake.... 
                    //  deleted/inserts before the snake
                    diff_engine(A, SizeRange{X.low,  dd.x.low}, B, SizeRange{Y.low, dd.y.low}, equiv, untouched, add, remove, opts, depth+1);
                    if(dd.x.not_empty())   
                    
                            // something is the same
                        untouched(dd.x, dd.y);
                    diff_engine(A, SizeRange{dd.x.high, X.high}, B, SizeRange{dd.y.high, Y.high}, equiv, untouched, add, remove, opts, depth+1);
                } else if(Y.count() > X.count()){
                    if(opts&NOISY){
                        yInfo() << pad << " branch B";
                    }
                    
                    size_t      M   = X.count()+Y.low;
                    
                    //  One edit left; FIRST x count is the snake, last is an insertion
                    untouched(X, SizeRange{ Y.low, M });
                    add(SizeRange{ M, Y.high });
                } else if(X.count() > Y.count()){
                    if(opts&NOISY){
                        yInfo() << pad << " branch C";
                    }
                    //  One edit left, FIRST y count is the snake, last is a deletion
                    
                    size_t      N   = Y.count()+X.low;
                    
                    untouched(SizeRange{ X.low, N }, Y);
                    remove(SizeRange{ N, X.high });
                } else {
                    if(opts&NOISY){
                        yInfo() << pad << " branch D";
                    }
                    // unmodified
                    untouched(X,Y);
                }
            } else if(X.not_empty()){
                if(opts&NOISY){
                    yInfo() << pad << "pure delete";            
                }
                // Pure deletions
                remove(X);
            } else if(Y.not_empty()){
                if(opts&NOISY){
                    yInfo() << pad << "pure insert";            
                }
                add(Y);
            } else {
                if(opts&NOISY){
                    yInfo() << pad << "hollow";            
                }
            }
        }

        template <typename VA, typename VB, typename Equivalent, typename Untouched, typename Added, typename Removed> 
        void    diff_engine(const std::vector<VA>& A, const std::vector<VB>& B, Equivalent equiv, Untouched untouched, Added add, Removed remove, unsigned int opts=0ULL)
        {
            diff_engine(
                A, SizeRange{ 0ULL, A.size() }, 
                B, SizeRange{ 0ULL, B.size() }, 
                equiv, untouched, add, remove, opts
            );
        }
        
        /*! \brief Differencing that returns a vector of edits
        
            This is an easier difference API that returns the differencing as a sequence of edit-record structures
            in a standard vector, and auto-generates the initial size ranges
        
            \tparam VA          The left side of the comparison
            \tparam VB          The right side of the comparison (can be the same)
            \tparam Equivalent  An equivalent operator "==", expecting Equivalent(VA(),VB()) => boolean

            \param A            The left vector
            \param B            The right vector
            \param equiv        Equivalency functor (expecting arguments of VA, VB)
            \param opts         Options.  Note, altering to THROW will cause the middle snake to throw an exception in lieu of asserting
        */
        template <typename VA, typename VB, typename Equivalent>
        std::vector<edit_t> compare(const std::vector<VA>& A, const std::vector<VB>& B, Equivalent equiv, unsigned int opts=0)
        {
            std::vector<edit_t> ret;
            
            diff_engine(
                A, SizeRange{ 0ULL, A.size() }, 
                B, SizeRange{ 0ULL, B.size() }, 
                equiv, 
                [&](SizeRange a, SizeRange b)
                {
                    if(opts & NOISY){
                        yInfo() << "Untouched [" << a.low << "," << a.high << "] -> [" << b.low << "," << b.high << "]";
                    }
                    ret.push_back(edit_t{ a, b, a.count(), Edit::Same });
                },
                [&](SizeRange b)
                {
                    if(opts & NOISY){
                        yInfo() << "Inserted " << b.low << "->" << b.high;
                    }
                    ret.push_back(edit_t{ {}, b, b.count(), Edit::Add });
                },
                [&](SizeRange a)
                {
                    if(opts & NOISY){
                        yInfo() << "Removed " << a.low << "->" << a.high;
                    }
                    ret.push_back(edit_t{ a, {}, a.count(), Edit::Remove });
                },
                opts
            );
            
            return ret;
        }
        
        /*! \brief Consolidates sequential edit_t edits that are the same type and otherwise compatible
        */
        inline std::vector<edit_t> consolidate(const std::vector<edit_t>& input)
        {
            std::vector<edit_t> ret;
            ret.reserve(input.size());
            for(const edit_t& next : input){
                bool    skip    = false;
                do {
                    if(ret.empty())
                        break;
                    
                    auto& prev   = ret.back();
                    if(prev.type != next.type)
                        break;
                
                    if(prev.left.high != next.left.low)
                        break;
                    if(prev.right.high != next.right.low)
                        break;
                    prev.left.high  = next.left.high;
                    prev.right.high = next.right.high;
                    prev.cnt   += next.cnt;
                    skip        = true;
                } while(false);
                if(!skip)
                    ret.push_back(next);
            }
            return ret;
        }
        

        template <typename T>
        std::vector<edit_t> compare(const std::vector<T>& A, const std::vector<T>& B, unsigned int opts=0)
        {
            return compare(A, B, cxx_equality<T>, opts);
        }

        inline bool     any_changes(const std::vector<edit_t>&results)
        {
            for(auto& de : results)
                if(de.type != Edit::Same)
                    return true;
            return false;
        }
    }
}
