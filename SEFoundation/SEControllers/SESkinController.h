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

#ifndef Swing_SkinController_H
#define Swing_SkinController_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEController.h"
#include "SEVector3.h"

namespace Swing
{

class Node;

//----------------------------------------------------------------------------
// 名称:蒙皮控制器类
// 说明:由CPU进行蒙皮顶点计算.
// 作者:Sun Che
// 时间:20080826
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SkinController : public Controller
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // SkinController负责删除构造函数传入的这些数组.
    // weight和offset数组必须是已经通过SESystem.h中的模板函数创建的数组.
    SkinController(int iVertexCount, int iBoneCount, Node** apBones,
        float** aafWeight, Vector3f** aaOffset);
    virtual ~SkinController(void);

    inline int GetVertexCount(void) const;
    inline int GetBoneCount(void) const;
    inline Node* GetBone(int iBone) const;
    inline float& Weight(int iVertex, int iBone);
    inline Vector3f& Offset(int iVertex, int iBone);

    virtual bool Update(double dAppTime);

protected:
    SkinController(void);

    int m_iVertexCount;    // vc
    int m_iBoneCount;      // bc
    Node** m_apBones;      // bones[bc]
    float** m_aafWeight;   // weight[vc][bc]
    Vector3f** m_aaOffset; // offset[vc][bc]
};

typedef SESmartPointer<SkinController> SkinControllerPtr;
#include "SESkinController.inl"

}

#endif
