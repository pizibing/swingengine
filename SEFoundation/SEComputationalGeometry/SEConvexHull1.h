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
// real-valued numbers,  but this provides some convenience for SEConvexHull2f and
// SEConvexHull3f when the input point set has intrinsic dimension smaller than
// the containing space.  The interface of SEConvexHull1f is also the model for
// those of SEConvexHull2f and SEConvexHull3f.

#include "SEFoundationLIB.h"
#include "SEConvexHull.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEConvexHull1f : public SEConvexHullf
{
public:
    // The input to the constructor is the array of vertices you want to sort.
    // If you want SEConvexHull1f to delete the array during destruction,  set
    // bOwner to 'true'.  Otherwise,  you own the array and must delete it
    // yourself.  TO DO:  The computation type is currently ignored by this
    // class.  Add support for the various types later.
    SEConvexHull1f(int iVertexCount,  float* afVertex,  float fEpsilon, 
        bool bOwner,  SEQuery::Type eQueryType);
    virtual ~SEConvexHull1f(void);

    // The input vertex array.
    const float* GetVertices(void) const;

    // Support for streaming to/from disk.
    SEConvexHull1f(const char* acFilename);
    bool Load(const char* acFilename);
    bool Save(const char* acFilename) const;

private:
    float* m_afVertex;

    class SE_FOUNDATION_API SESortedVertex
    {
    public:
        float Value;
        int Index;

        bool operator < (const SESortedVertex& rProj) const
        {
            return Value < rProj.Value;
        }
    };
};

}

#endif
