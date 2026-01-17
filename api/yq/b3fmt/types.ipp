////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "types.hpp"
#include <yq/coord/Coord1.hpp>
#include <yq/coord/Coord2.hpp>
#include <yq/coord/Coord3.hpp>
#include <yq/coord/Coord4.hpp>
#include <yq/coord/Coord5.hpp>
#include <yq/coord/Coord6.hpp>
#include <yq/shape/Size1.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/shape/Size3.hpp>
#include <yq/shape/Size4.hpp>
#include <yq/vector/Vector1.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector4.hpp>


namespace yq::b3 {

    CoordN::operator Coord1I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        
        return Coord1I(i);
    }

    CoordN::operator Coord2I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        int   j       = (indices.size() >= 2) ? indices[1] : 0;
        
        return Coord2I(i,j);
    }

    CoordN::operator Coord3I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        int   j       = (indices.size() >= 2) ? indices[1] : 0;
        int   k       = (indices.size() >= 3) ? indices[2] : 0;
        
        return Coord3I(i,j,k);
    }

    CoordN::operator Coord4I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        int   j       = (indices.size() >= 2) ? indices[1] : 0;
        int   k       = (indices.size() >= 3) ? indices[2] : 0;
        int   l       = (indices.size() >= 4) ? indices[3] : 0;
        
        return Coord4I(i,j,k,l);
    }

    CoordN::operator Coord5I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        int   j       = (indices.size() >= 2) ? indices[1] : 0;
        int   k       = (indices.size() >= 3) ? indices[2] : 0;
        int   l       = (indices.size() >= 4) ? indices[3] : 0;
        int   m       = (indices.size() >= 5) ? indices[4] : 0;

        return Coord5I(i,j,k,l,m);
    }

    CoordN::operator Coord6I() const
    {
        int   i       = (indices.size() >= 1) ? indices[0] : 0;
        int   j       = (indices.size() >= 2) ? indices[1] : 0;
        int   k       = (indices.size() >= 3) ? indices[2] : 0;
        int   l       = (indices.size() >= 4) ? indices[3] : 0;
        int   m       = (indices.size() >= 5) ? indices[4] : 0;
        int   n       = (indices.size() >= 6) ? indices[5] : 0;

        return Coord6I(i,j,k,l,m,n);
    }

    ////////////////////////////////////////////////////////////////////////////

    CountN::operator Size1I() const
    {
        int  x   = (axes.size() >= 1) ? axes[0] : 0;
        
        return Size1I(x);
    }
    
    CountN::operator Size2I() const
    {
        int  x   = (axes.size() >= 1) ? axes[0] : 0;
        int  y   = (axes.size() >= 2) ? axes[1] : 0;
        
        return Size2I(x,y);
    }
    
    CountN::operator Size3I() const
    {
        int  x   = (axes.size() >= 1) ? axes[0] : 0;
        int  y   = (axes.size() >= 2) ? axes[1] : 0;
        int  z   = (axes.size() >= 3) ? axes[2] : 0;
        
        return Size3I(x,y,z);
    }
    
    CountN::operator Size4I() const
    {
        int  x   = (axes.size() >= 1) ? axes[0] : 0;
        int  y   = (axes.size() >= 2) ? axes[1] : 0;
        int  z   = (axes.size() >= 3) ? axes[2] : 0;
        int  w   = (axes.size() >= 4) ? axes[3] : 0;
        
        return Size4I(x,y,z,w);
    }
    

    ////////////////////////////////////////////////////////////////////////////

    PointN::operator Vector1D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        
        return Vector1D(x);
    }
    
    PointN::operator Vector2D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        
        return Vector2D(x,y);
    }
    
    PointN::operator Vector3D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        
        return Vector3D(x,y,z);
    }
    
    PointN::operator Vector4D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        double  w   = (axes.size() >= 4) ? axes[3] : 0.;
        
        return Vector4D(x,y,z,w);
    }
    
    ////////////////////////////////////////////////////////////////////////////

    SizeN::operator Size1D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        
        return Size1D(x);
    }
    
    SizeN::operator Size2D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        
        return Size2D(x,y);
    }
    
    SizeN::operator Size3D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        
        return Size3D(x,y,z);
    }
    
    SizeN::operator Size4D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        double  w   = (axes.size() >= 4) ? axes[3] : 0.;
        
        return Size4D(x,y,z,w);
    }
    
    ////////////////////////////////////////////////////////////////////////////

    VectorN::operator Vector1D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        
        return Vector1D(x);
    }
    
    VectorN::operator Vector2D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        
        return Vector2D(x,y);
    }
    
    VectorN::operator Vector3D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        
        return Vector3D(x,y,z);
    }
    
    VectorN::operator Vector4D() const
    {
        double  x   = (axes.size() >= 1) ? axes[0] : 0.;
        double  y   = (axes.size() >= 2) ? axes[1] : 0.;
        double  z   = (axes.size() >= 3) ? axes[2] : 0.;
        double  w   = (axes.size() >= 4) ? axes[3] : 0.;
        
        return Vector4D(x,y,z,w);
    }
}
