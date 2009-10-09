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

#include "SEToolsCommonPCH.h"
#include "SEColladaMaterial.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ColladaMaterial, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaMaterial, Object);

//----------------------------------------------------------------------------
ColladaMaterial::ColladaMaterial(ColladaEffect* pEffect)
{
    m_spEffect = pEffect;
}
//----------------------------------------------------------------------------
ColladaMaterial::ColladaMaterial()
{
}
//----------------------------------------------------------------------------
ColladaMaterial::~ColladaMaterial()
{
}
//----------------------------------------------------------------------------
MaterialState* ColladaMaterial::GetMState()
{
    if( m_spEffect )
    {
        return m_spEffect->Material;
    }

    return 0;
}
//----------------------------------------------------------------------------
Texture* ColladaMaterial::GetTexture(int i)
{
    if( 0 <= i && i <= (int)m_spEffect->Textures.size() - 1 )
    {
        return m_spEffect->Textures[i];
    }

    return 0;
}
//----------------------------------------------------------------------------

SE_IMPLEMENT_RTTI(Swing, ColladaInstanceMaterial, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaInstanceMaterial, Object);

//----------------------------------------------------------------------------
ColladaInstanceMaterial::ColladaInstanceMaterial()
{
    TargetName = "";
    TargetMaterial = 0;
}
//----------------------------------------------------------------------------
ColladaInstanceMaterial::~ColladaInstanceMaterial()
{
}
//----------------------------------------------------------------------------