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
#include "SEMath.h"

namespace Swing
{
template<> const float SEMath<float>::EPSILON = FLT_EPSILON;
template<> const float SEMath<float>::ZERO_TOLERANCE = 1e-06f;
template<> const float SEMath<float>::MAX_REAL = FLT_MAX;
template<> const float SEMath<float>::PI = (float)(4.0*atan(1.0));
template<> const float SEMath<float>::TWO_PI = 2.0f*SEMath<float>::PI;
template<> const float SEMath<float>::HALF_PI = 0.5f*SEMath<float>::PI;
template<> const float SEMath<float>::INV_PI = 1.0f/SEMath<float>::PI;
template<> const float SEMath<float>::INV_TWO_PI = 1.0f/SEMath<float>::TWO_PI;
template<> const float SEMath<float>::DEG_TO_RAD = SEMath<float>::PI/180.0f;
template<> const float SEMath<float>::RAD_TO_DEG = 180.0f/SEMath<float>::PI;

template<> const double SEMath<double>::EPSILON = DBL_EPSILON;
template<> const double SEMath<double>::ZERO_TOLERANCE = 1e-08;
template<> const double SEMath<double>::MAX_REAL = DBL_MAX;
template<> const double SEMath<double>::PI = 4.0*atan(1.0);
template<> const double SEMath<double>::TWO_PI = 2.0*SEMath<double>::PI;
template<> const double SEMath<double>::HALF_PI = 0.5*SEMath<double>::PI;
template<> const double SEMath<double>::INV_PI = 1.0/SEMath<double>::PI;
template<> const double SEMath<double>::INV_TWO_PI = 
    1.0/SEMath<double>::TWO_PI;
template<> const double SEMath<double>::DEG_TO_RAD = SEMath<double>::PI/180.0;
template<> const double SEMath<double>::RAD_TO_DEG = 180.0/SEMath<double>::PI;

//----------------------------------------------------------------------------
template <>
float SEMath<float>::FastInvSqrt(float fValue)
{
    float fHalf = 0.5f*fValue;
    int i  = *(int*)&fValue;
    i = 0x5f3759df - (i >> 1);
    fValue = *(float*)&i;
    fValue = fValue*(1.5f - fHalf*fValue*fValue);
    return fValue;
}
//----------------------------------------------------------------------------
template <>
double SEMath<double>::FastInvSqrt(double dValue)
{
    double dHalf = 0.5*dValue;
    SE_Int64 i  = *(SE_Int64*)&dValue;
#if defined(SE_USING_VC70) || defined(SE_USING_VC6)
    i = 0x5fe6ec85e7de30da - (i >> 1);
#else
    i = 0x5fe6ec85e7de30daLL - (i >> 1);
#endif
    dValue = *(double*)&i;
    dValue = dValue*(1.5 - dHalf*dValue*dValue);
    return dValue;
}
//----------------------------------------------------------------------------
}