////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <type_traits>

namespace yq {
    template <typename Base, typename Desired, typename Pred, typename K, typename C>
    auto    foreach_map(std::map<K,Base*,C> data, Pred&&pred) 
    {
        using base_t    = std::remove_cv_t<Base>;
        using desired_t = std::remove_cv_t<Desired>;
        static constexpr const bool is_base   = std::is_same_v<base_t, desired_t>;
        
        if constexpr ( std::is_invocable_v<Pred, desired_t&> ){
            using return_t  = std::invoke_result_t<Pred, desired_t&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : data){
                Desired*  val = nullptr;
                if constexpr (is_base){
                    val = itr.second;
                } else {
                    val = dynamic_cast<Desired*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(*val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr ( std::is_invocable_v<Pred, desired_t*> ){
            using return_t  = std::invoke_result_t<Pred, desired_t*>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : data){
                Desired*  val = nullptr;
                if constexpr (is_base){
                    val = itr.second;
                } else {
                    val = dynamic_cast<Desired*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(val);
            }
            if constexpr (!is_void)
                return return_t{};
        }
    }
}
