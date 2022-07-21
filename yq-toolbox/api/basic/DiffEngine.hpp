////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Array.hpp>
#include <vector>

namespace yq {

    // TODO... DIFF ENGINE


            // Based on https://github.com/RobertElderSoftware/roberteldersoftwarediff/blob/master/myers_diff_and_variations.py
    /*! \brief Difference Engine 

        \tparam VA          The left side of the comparison
        \tparam VB          The right side of the comparison (can be the same)
        \tparam Equivalent  An equivalent operator "=="
        \tparam Added       The *ADDED* functor, taking in a range
        \tparam Removed     The *REMOVED* functor, taking in a range
        \tparam Untouched   The untouched, taking in two ranges
    */
    template <typename VA, typename VB, typename Equivalent, typename Added, typename Removed, typename Untouched> 
    struct DiffEngine {
        const std::vector<VA>&   A;
        const std::vector<VB>&   B;
        ZArray1<ssize_t,ssize_t>     Vf, Vb;
        Equivalent          equiv;
        Added               added;
        Removed             removed;
        Untouched           untouched;
        
        struct Match {
            SSizeRange  x, y;
            ssize_t     D;
            bool        good;
        };
        
        DiffEngine(const std::vector<VA>& a, const std::vector<VB>& b, Equivalent eq, Added ad, Removed rm, Untouched ut) : 
            A(a), B(b), equiv(eq), added(ad), removed(rm), untouched(ut)
        {
            ssize_t mx  = a.size() + b.size() + 1;
            Vf.resize({-mx-1}, {mx+2}, 0ULL);
            Vb.resize({-mx-1}, {mx+2}, 0ULL);
        }

        Match   middleSnake(const SSizeRange& X, const SSizeRange& Y)
        {
            ssize_t N       = X.count();
            ssize_t M       = Y.count();
            ssize_t mx      = N + M;
            ssize_t delta   = N - M;
            ssize_t         x, y, xi, yi, D, k;

            for(D = 0; D <= mx/2+(mx&1); ++D){
                for(k=-D;k<=D;k+=2){
                    if((k==-D) || (k!=D && (Vf[k-1] < Vf[k+1]))){
                        x   = Vf[k+1];
                    } else
                        x   = Vf[k-1]+1;
                    y   = x - k;
                    xi  = x;
                    yi  = y;
                    while((x<N) && (y<M) && equiv(A[X.low+x], B[Y.low+y]))
                        ++x, ++y;
                    Vf[k]   = x;
                    
                    int64_t knd = k - delta;
                    if((delta&1) && (-knd >= -(D-1)) && (-knd <= (D-1))){
                        if(Vf[k] + Vb[-knd] >= N){
                            return Match{ 
                                range(xi+X.low, x+X.low),
                                range(yi+Y.low, y+Y.low),
                                2*D-1, true
                            };
                        }
                    }
                }
                for(k=-D;k<=D;k+=2){
                    if((k==-D) || (k!=D && (Vf[k-1] < Vf[k+1]))){
                        x   = Vb[k+1];
                    } else
                        x   = Vb[k-1]+1;
                    y   = x - k;
                    xi  = x;
                    yi  = y;
                    while((x<N) && (y<M) && equiv(A[X.low+N-x-1], B[Y.low+M-y-1]))
                        ++x, ++y;
                    Vb[k]   = x;
                    int64_t knd = k - delta;
                    if((delta&1) && (-knd >= --D) && (-knd <= D)){
                        if(Vb[k]+Vf[-knd] >= N){
                            return Match{
                                range(X.low+N-x, X.low+N-xi),
                                range(Y.low+M-y, Y.low+M-yi),
                                2*D, true
                            };
                        }
                    }
                }
            }
            return Match{};
        }

        bool            compare(SSizeRange X, SSizeRange Y)
        {
            if(X.count() <= 0){
                if(Y.count() <= 0){
                    return false;
                } else {
                    added(Y);
                    return true;
                }
            } else {
                if(Y.count() <= 0){
                    removed(X);
                    return true;
                } else {
                
                    Match   m   = middleSnake(X,Y);
                    assert(m.good);
                    if((m.D > 1) || (m.x.not_empty()  && m.y.not_empty())){ // can be further subdivided
                        bool    rtn = false;
                        rtn = compare(SSizeRange(X.low, m.x.low), SSizeRange(Y.low, m.y.low)) || rtn; // before....
                        untouched(m.x, m.y);
                        rtn = compare(SSizeRange(m.x.high, X.high), SSizeRange(m.y.high, Y.high)) || rtn;
                        return rtn;
                    } else if(Y.count() > X.count()){
                        //  There's a single insertion (at the end)
                        untouched(m.x, m.y);
                        added(SSizeRange(m.y.high, Y.high));
                        return true;
                    } else if(Y.count() < X.count()){
                        //  There's a single deletion
                        untouched(m.x, m.y);
                        removed(SSizeRange(m.x.high, X.high));
                        return true;
                    } else {
                        //  All unmodified 
                        untouched(m.x, m.y);
                        return false;
                    }
                }
            }
            return false;
        }

        bool            compare()
        {
            return compare({0, (ssize_t) A.size()}, {0, (ssize_t) B.size()});
        }
    };

    template <typename VA, typename VB, typename Equivalent, typename Added, typename Removed, typename Untouched> 
    bool    diff_it(const std::vector<VA>& va, const std::vector<VB>& vb, Equivalent equiv, Added add, Removed rem, Untouched ut)
    {
        return DiffEngine<VA,VB,Equivalent,Added,Removed,Untouched>(va, vb, equiv, add, rem, ut).compare();
    }

    struct DEResult {
        enum Mode {
            Same,
            Add,
            Remove
        };

        SSizeRange   left, right;
        Mode        mode;
    };

    template <typename T, typename CEQ = std::equal_to<T>>
    std::vector<DEResult>    diff_it(const std::vector<T>& Old, const std::vector<T>& New, CEQ cmp = CEQ())
    {
        std::vector<DEResult>   ret;
        diff_it( Old, New, cmp, [&](SSizeRange Y){
            ret.push_back(DEResult{ {}, Y, DEResult::Add });
        }, [&](SSizeRange X){
            ret.push_back(DEResult{ X, {}, DEResult::Remove });
        }, [&](SSizeRange X, SSizeRange Y){
            ret.push_back(DEResult{ X, Y, DEResult::Same });
        });
        return ret;
    }

    inline bool     any_changes(const std::vector<DEResult>&results)
    {
        for(auto& de : results)
            if(de.mode != DEResult::Same)
                return true;
        return false;
    }
}
