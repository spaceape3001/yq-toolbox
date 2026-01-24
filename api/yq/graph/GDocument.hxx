////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GDocument.hpp>
#include <yq/graph/GEdgeData.hpp>
#include <yq/graph/GGraphData.hpp>
#include <yq/graph/GLineData.hpp>
#include <yq/graph/GNodeData.hpp>
#include <yq/graph/GPortData.hpp>
#include <yq/graph/GShapeData.hpp>
#include <yq/graph/GTextData.hpp>

namespace yq {
    template <typename Pred>
    auto    GDocument::datas(for_k, Pred&& pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            pred(d);
        }
    }

    template <typename Pred>
    auto    GDocument::datas(for_k, Pred&& pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            pred(*d);
        }
    }

    template <typename Pred>
    auto    GDocument::edges(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_edge())
                continue;
            pred(*static_cast<GEdgeData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::edges(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_edge())
                continue;
            pred(*static_cast<const GEdgeData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::graphs(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_graph())
                continue;
            pred(*static_cast<GGraphData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::graphs(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_graph())
                continue;
            pred(*static_cast<const GGraphData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::lines(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_line())
                continue;
            pred(*static_cast<GLineData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::lines(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_line())
                continue;
            pred(*static_cast<const GLineData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::nodes(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_node())
                continue;
            pred(*static_cast<GNodeData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::nodes(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_node())
                continue;
            pred(*static_cast<const GNodeData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::ports(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_port())
                continue;
            pred(*static_cast<GPortData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::ports(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_port())
                continue;
            pred(*static_cast<const GPortData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::shapes(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_shape())
                continue;
            pred(*static_cast<GShapeData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::shapes(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_shape())
                continue;
            pred(*static_cast<const GShapeData*>(d));
        }
    }

    template <typename Pred>
    auto    GDocument::texts(for_k, Pred&&pred)
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_text())
                continue;
            pred(*static_cast<GTextData*>(d));
        }
    }
    
    template <typename Pred>
    auto    GDocument::texts(for_k, Pred&&pred) const
    {
        for(auto d : m_data){
            if(!d)
                continue;
            if(d->deleted)
                continue;
            if(!d->is_text())
                continue;
            pred(*static_cast<const GTextData*>(d));
        }
    }
}
