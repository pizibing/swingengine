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

#include "SEFoundationPCH.h"
#include "SEApprGaussPointsFit3.h"
#include "SEEigen.h"

using namespace Swing;

//----------------------------------------------------------------------------
Box3f Swing::GaussPointsFit3f(int iCount, const Vector3f* aPoint)
{
    Box3f tempBox(Vector3f::ZERO, Vector3f::UNIT_X, Vector3f::UNIT_Y, 
        Vector3f::UNIT_Z, 1.0f, 1.0f, 1.0f);

    // 计算顶点的平均中心.
    tempBox.Center = aPoint[0];
    int i;
    for( i = 1; i < iCount; i++ )
    {
        tempBox.Center += aPoint[i];
    }
    float fInvCount = 1.0f / iCount;
    tempBox.Center *= fInvCount;

    // 计算顶点的协方差矩阵.
    float fSumXX = 0.0f, fSumXY = 0.0f, fSumXZ = 0.0f;
    float fSumYY = 0.0f, fSumYZ = 0.0f, fSumZZ = 0.0f;
    for( i = 0; i < iCount; i++ )
    {
        Vector3f vec3fDiff = aPoint[i] - tempBox.Center;
        fSumXX += vec3fDiff.X * vec3fDiff.X;
        fSumXY += vec3fDiff.X * vec3fDiff.Y;
        fSumXZ += vec3fDiff.X * vec3fDiff.Z;
        fSumYY += vec3fDiff.Y * vec3fDiff.Y;
        fSumYZ += vec3fDiff.Y * vec3fDiff.Z;
        fSumZZ += vec3fDiff.Z * vec3fDiff.Z;
    }

    fSumXX *= fInvCount;
    fSumXY *= fInvCount;
    fSumXZ *= fInvCount;
    fSumYY *= fInvCount;
    fSumYZ *= fInvCount;
    fSumZZ *= fInvCount;

    // 建立eigensolver并求解.
    Eigen tempES(3);
    tempES(0, 0) = fSumXX;
    tempES(0, 1) = fSumXY;
    tempES(0, 2) = fSumXZ;
    tempES(1, 0) = fSumXY;
    tempES(1, 1) = fSumYY;
    tempES(1, 2) = fSumYZ;
    tempES(2, 0) = fSumXZ;
    tempES(2, 1) = fSumYZ;
    tempES(2, 2) = fSumZZ;
    tempES.IncrSortEigenStuff3();

    for( i = 0; i < 3; i++ )
    {
        tempBox.Extent[i] = tempES.GetEigenvalue(i);
        tempES.GetEigenvector(i, tempBox.Axis[i]);
    }

    return tempBox;
}
//----------------------------------------------------------------------------
