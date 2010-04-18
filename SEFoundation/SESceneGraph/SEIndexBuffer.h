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

#ifndef Swing_IndexBuffer_H
#define Swing_IndexBuffer_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEBindable.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080621
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEIndexBuffer : public SEObject, public SEBindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SEIndexBuffer(int iICount);
    SEIndexBuffer(const SEIndexBuffer* pIBuffer);
    virtual ~SEIndexBuffer(void);

    inline int operator [] (int i) const;
    inline int& operator [] (int i);

    // 获取索引个数,缓冲区字节数为GetIndexCount()*sizeof(int)
    inline int GetIndexCount(void) const;
    inline int* GetData(void);
    inline const int* GetData(void) const;

    // 用户可能想设置索引的"active count",使用此函数来设置,
    // 函数没有改变实际数据存储,只是设置m_iICount,
    // 用户有责任保存实际索引数目,并在一系列操作完成后恢复实际索引数目,
    // active count不能超过实际索引数目
    inline void SetIndexCount(int iICount);

protected:
    // streaming support
    SEIndexBuffer(void);

	// 索引缓冲区数据
    int m_iICount;
    int* m_pIndex;
};

typedef SESmartPointer<SEIndexBuffer> SEIndexBufferPtr;

#include "SEIndexBuffer.inl"

}

#endif
