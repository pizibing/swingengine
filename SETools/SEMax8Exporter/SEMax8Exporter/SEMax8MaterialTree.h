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

#ifndef Swing_Max8MaterialTree_H
#define Swing_Max8MaterialTree_H

#include "SEMaterialState.h"
#include "SEMax8TextureTree.h"
#include <vector>

//----------------------------------------------------------------------------
// 名称:Max8MaterialTree类
// 说明:
// 作者:Sun Che
// 时间:20080815
//----------------------------------------------------------------------------
class Max8MaterialTree
{
public:
    Max8MaterialTree(Swing::MaterialState* pSEMaterialState = NULL);

    // 材质子树
    void SetMChildCount(int iCount);
    int GetMChildCount(void) const;
    void SetMaterial(Swing::MaterialStatePtr spSEMaterialState);
    Swing::MaterialStatePtr GetMaterial(void) const;
    Max8MaterialTree& GetMChild(int i);

    // 纹理子树
    void SetTChildCount(int iCount);
    int GetTChildCount(void) const;
    Swing::TexturePtr GetTexture(int i);
    Max8TextureTree& GetTChild(int i);

private:
    Swing::MaterialStatePtr m_spSEMaterialState;
    std::vector<Max8MaterialTree> m_MChild;
    std::vector<Max8TextureTree> m_TChild;
};

#endif



