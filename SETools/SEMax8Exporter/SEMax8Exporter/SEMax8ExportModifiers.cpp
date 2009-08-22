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

#include "SEMax8SceneBuilder.h"
#include "iparamb2.h"
#include "iskin.h"
#include "modstack.h"

using namespace std;

//----------------------------------------------------------------------------
void Max8SceneBuilder::ApplyModifiers()
{
    // 把之前遍历Max场景所收集到的修改器添加给Swing Engine场景视图对应节点.
    // 当前只支持skin修改器.

    vector<ModifierInfo*>::iterator pI;
    for( pI = m_ModList.begin(); pI < m_ModList.end(); pI++ )
    {
        ModifierInfo* pInfo = *pI;
        vector<Modifier*>::iterator pJ = pInfo->Modifiers.begin();
        for( /**/; pJ < pInfo->Modifiers.end(); pJ++ )
        {
            Modifier* pModifier = *pJ;
            Class_ID tempID = pModifier->ClassID();
            if( tempID == SKIN_CLASSID )
            {
                ProcessSkin(pInfo->Node, pModifier);
            }
        }
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::FindModifiers(INode* pMaxNode,
    vector<Modifier*>& rModifiers)
{
    // 判断一个Max节点是否带有修改器.如果有则收集,供稍后使用.
    //
    // pMaxNode:
    //     待检查的Max节点指针.
    // rModifiers:
    //     用于收集的修改器指针数组.

    // 从节点获取其对象.
    Object* pObj = pMaxNode->GetObjectRef();
    if( !pObj )
    {
        return;
    }

    // 是否为派生对象?
    while( pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID )
    {
        // 是则转换.
        IDerivedObject* pDerObj = static_cast<IDerivedObject*>(pObj);

        // 迭代访问修改器堆栈的所有元素.
        int iModStackIndex = 0;
        while( iModStackIndex < pDerObj->NumModifiers() )
        {
            // 获取当前修改器.
            Modifier* pMod = pDerObj->GetModifier(iModStackIndex);
            if( pMod )
            {
                rModifiers.push_back(pMod);
            }

            iModStackIndex++;
        }
        pObj = pDerObj->GetObjRef();
    }
}
//----------------------------------------------------------------------------



