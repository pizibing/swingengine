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
#include "SETriangle2.h"

using namespace Swing;

//----------------------------------------------------------------------------
Triangle2f::Triangle2f()
{
    // Œ¥≥ı ºªØ.
}
//----------------------------------------------------------------------------
Triangle2f::Triangle2f(const Vector2f& rV0, const Vector2f& rV1, 
    const Vector2f& rV2)
{
    V[0] = rV0;
    V[1] = rV1;
    V[2] = rV2;
}
//----------------------------------------------------------------------------
Triangle2f::Triangle2f(const Vector2f aV[3])
{
    for( int i = 0; i < 3; i++ )
    {
        V[i] = aV[i];
    }
}
//----------------------------------------------------------------------------
float Triangle2f::GetDistance(const Vector2f& rQ) const
{
    Vector2f vec2fDiff = V[0] - rQ;
    Vector2f vec2fE0 = V[1] - V[0], vec2fE1 = V[2] - V[0];
    float fA00 = vec2fE0.GetSquaredLength();
    float fA01 = vec2fE0.Dot(vec2fE1);
    float fA11 = vec2fE1.GetSquaredLength();
    float fB0 = vec2fDiff.Dot(vec2fE0);
    float fB1 = vec2fDiff.Dot(vec2fE1);
    float fC = vec2fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(fA00*fA11 - fA01*fA01);
    float fS = fA01*fB1 - fA11*fB0;
    float fT = fA01*fB0 - fA00*fB1;
    float fSqrDist;

    if( fS + fT <= fDet )
    {
        if( fS < 0.0f )
        {
            if( fT < 0.0f )  // region 4
            {
                if( fB0 < 0.0f )
                {
                    if( -fB0 >= fA00 )
                    {
                        fSqrDist = fA00 + 2.0f*fB0 + fC;
                    }
                    else
                    {
                        fSqrDist = fC - fB0*fB0/fA00;
                    }
                }
                else
                {
                    if( fB1 >= 0.0f )
                    {
                        fSqrDist = fC;
                    }
                    else if( -fB1 >= fA11 )
                    {
                        fSqrDist = fA11 + 2.0f*fB1 + fC;
                    }
                    else
                    {
                        fSqrDist = fC - fB1*fB1/fA11;
                    }
                }
            }
            else  // region 3
            {
                if( fB1 >= 0.0f )
                {
                    fSqrDist = fC;
                }
                else if( -fB1 >= fA11 )
                {
                    fSqrDist = fA11 + 2.0f*fB1 + fC;
                }
                else
                {
                    fSqrDist = fC - fB1*fB1/fA11;
                }
            }
        }
        else if( fT < 0.0f )  // region 5
        {
            if( fB0 >= 0.0f )
            {
                fSqrDist = fC;
            }
            else if( -fB0 >= fA00 )
            {
                fSqrDist = fA00 + 2.0f*fB0 + fC;
            }
            else
            {
                fSqrDist = fB0*fS + fC - fB0*fB0/fA00;
            }
        }
        else  // region 0
        {
            // minimum at interior point
            float fInvDet = 1.0f / fDet;
            fS *= fInvDet;
            fT *= fInvDet;
            fSqrDist = fS*(fA00*fS + fA01*fT + 2.0f*fB0) +
                fT*(fA01*fS + fA11*fT + 2.0f*fB1) + fC;
        }
    }
    else
    {
        float fTmp0, fTmp1, fNumer, fDenom;

        if( fS < 0.0f )  // region 2
        {
            fTmp0 = fA01 + fB0;
            fTmp1 = fA11 + fB1;
            if( fTmp1 > fTmp0 )
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f*fA01 + fA11;
                if( fNumer >= fDenom )
                {
                    fSqrDist = fA00 + 2.0f*fB0 + fC;
                }
                else
                {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist = fS*(fA00*fS + fA01*fT + 2.0f*fB0) +
                        fT*(fA01*fS + fA11*fT + 2.0f*fB1) + fC;
                }
            }
            else
            {
                if( fTmp1 <= 0.0f )
                {
                    fSqrDist = fA11 + 2.0f*fB1 + fC;
                }
                else if( fB1 >= 0.0f )
                {
                    fSqrDist = fC;
                }
                else
                {
                    fSqrDist = fC - fB1*fB1/fA11;
                }
            }
        }
        else if( fT < 0.0f )  // region 6
        {
            fTmp0 = fA01 + fB1;
            fTmp1 = fA00 + fB0;
            if( fTmp1 > fTmp0 )
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f*fA01 + fA11;
                if( fNumer >= fDenom )
                {
                    fT = 1.0f;
                    fS = 0.0f;
                    fSqrDist = fA11 + 2.0f*fB1 + fC;
                }
                else
                {
                    fT = fNumer / fDenom;
                    fS = 1.0f - fT;
                    fSqrDist = fS*(fA00*fS + fA01*fT + 2.0f*fB0) +
                        fT*(fA01*fS + fA11*fT + 2.0f*fB1) + fC;
                }
            }
            else
            {
                if( fTmp1 <= 0.0f )
                {
                    fSqrDist = fA00 + 2.0f*fB0 + fC;
                }
                else if( fB0 >= 0.0f )
                {
                    fSqrDist = fC;
                }
                else
                {
                    fSqrDist = fC - fB0*fB0/fA00;
                }
            }
        }
        else  // region 1
        {
            fNumer = fA11 + fB1 - fA01 - fB0;
            if( fNumer <= 0.0f )
            {
                fSqrDist = fA11 + 2.0f*fB1 + fC;
            }
            else
            {
                fDenom = fA00 - 2.0f*fA01 + fA11;
                if( fNumer >= fDenom )
                {
                    fSqrDist = fA00 + 2.0f*fB0 + fC;
                }
                else
                {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist = fS*(fA00*fS + fA01*fT + 2.0f*fB0) +
                        fT*(fA01*fS + fA11*fT + 2.0f*fB1) + fC;
                }
            }
        }
    }

    return Math<float>::Sqrt(Math<float>::FAbs(fSqrDist));
}
//----------------------------------------------------------------------------
