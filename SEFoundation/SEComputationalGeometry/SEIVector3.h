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

#ifndef Swing_IVector3_H
#define Swing_IVector3_H

#include "SEFoundationLIB.h"
#include "SETIVector.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IVector3类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class SEIVector3 : public SETIVector<3>
{
public:
    // construction
    SEIVector3(void);
    SEIVector3(const SEIVector3& rV);
    SEIVector3(const SETIVector<3>& rV);
    SEIVector3(const SE_Int64& riX,  const SE_Int64& riY, 
        const SE_Int64& riZ);

    // member access
    SE_Int64 X(void) const;
    SE_Int64& X(void);
    SE_Int64 Y(void) const;
    SE_Int64& Y(void);
    SE_Int64 Z(void) const;
    SE_Int64& Z(void);

    // assignment
    SEIVector3& operator = (const SEIVector3& rV);
    SEIVector3& operator = (const SETIVector<3>& rV);

    // returns Dot(this, V)
    SE_Int64 Dot(const SEIVector3& rV) const;

    // returns Cross(this, V)
    SEIVector3 Cross(const SEIVector3& rV) const;

    // returns Dot(this, Cross(U, V))
    SE_Int64 TripleScalar(const SEIVector3& rU,  const SEIVector3& rV) const;

protected:
    using SETIVector<3>::m_aiTuple;
};

#include "SEIVector3.inl"

}

#endif
