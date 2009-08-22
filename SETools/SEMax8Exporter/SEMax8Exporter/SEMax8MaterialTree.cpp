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

#include "SEMax8MaterialTree.h"

using namespace Swing;
using namespace std;

//----------------------------------------------------------------------------
Max8MaterialTree::Max8MaterialTree(Swing::MaterialState* pSEMaterialState)
{
    m_spSEMaterialState = pSEMaterialState;
}
//----------------------------------------------------------------------------
void Max8MaterialTree::SetMChildCount(int iCount)
{
    m_MChild.resize(iCount);
}
//----------------------------------------------------------------------------
int Max8MaterialTree::GetMChildCount() const
{
    return (int)m_MChild.size();
}
//----------------------------------------------------------------------------
void Max8MaterialTree::SetMaterial(Swing::MaterialStatePtr spSEMaterialState)
{
    m_spSEMaterialState = spSEMaterialState;
}
//----------------------------------------------------------------------------
MaterialStatePtr Max8MaterialTree::GetMaterial() const
{
    return m_spSEMaterialState;
}
//----------------------------------------------------------------------------
Max8MaterialTree& Max8MaterialTree::GetMChild(int i)
{
    return m_MChild[i];
}
//----------------------------------------------------------------------------
void Max8MaterialTree::SetTChildCount(int iCount)
{
    m_TChild.resize(iCount);
}
//----------------------------------------------------------------------------
int Max8MaterialTree::GetTChildCount() const
{
    return (int)m_TChild.size();
}
//----------------------------------------------------------------------------
TexturePtr Max8MaterialTree::GetTexture(int i)
{
    return m_TChild[i].GetTexture();
}
//----------------------------------------------------------------------------
Max8TextureTree& Max8MaterialTree::GetTChild(int i)
{
    return m_TChild[i];
}
//----------------------------------------------------------------------------



