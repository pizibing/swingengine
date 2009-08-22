// Swing Engine Version 1 Source Code 
// Most of techniques in the engine are mainly based on David Eberly's
// Wild Magic 4 open-source code.The author of Swing Engine learned a lot
// from Eberly's experience of architecture and algorithm.
// Several sub-systems are totally new,and others are re-implimented or
// re-organized based on Wild Magic 4's sub-systems.
// Copyright (c) 2007-2010.  All Rights Reserved
//
// Eberly's permission:
// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// the location:
// http://www.gnu.org/copyleft/lgpl.html

#ifndef Swing_ConvexHull1_H
#define Swing_ConvexHull1_H

// A fancy class to compute the minimum and maximum of a collection of
// real-valued numbers,  but this provides some convenience for ConvexHull2f and
// ConvexHull3f when the input point set has intrinsic dimension smaller than
// the containing space.  The interface of ConvexHull1f is also the model for
// those of ConvexHull2f and ConvexHull3f.

#include "SEFoundationLIB.h"
#include "SEConvexHull.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:ConvexHull1f类
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ConvexHull1f : public ConvexHullf
{
public:
    // The input to the constructor is the array of vertices you want to sort.
    // If you want ConvexHull1f to delete the array during destruction,  set
    // bOwner to 'true'.  Otherwise,  you own the array and must delete it
    // yourself.  TO DO:  The computation type is currently ignored by this
    // class.  Add support for the various types later.
    ConvexHull1f(int iVertexCount,  float* afVertex,  float fEpsilon, 
        bool bOwner,  Query::Type eQueryType);
    virtual ~ConvexHull1f(void);

    // The input vertex array.
    const float* GetVertices(void) const;

    // Support for streaming to/from disk.
    ConvexHull1f(const char* acFilename);
    bool Load(const char* acFilename);
    bool Save(const char* acFilename) const;

private:
    float* m_afVertex;

    class SE_FOUNDATION_API SortedVertex
    {
    public:
        float Value;
        int Index;

        bool operator < (const SortedVertex& rProj) const
        {
            return Value < rProj.Value;
        }
    };
};

}

#endif
