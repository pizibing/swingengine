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
#include "SETextureTileL1Effect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SETextureTileL1Effect, SEShaderEffect);
SE_IMPLEMENT_STREAM(SETextureTileL1Effect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SETextureTileL1Effect, SEShaderEffect);

//SE_REGISTER_STREAM(SETextureTileL1Effect);

float SETextureTileL1Effect::ms_afTileParams[2] = 
{
    1.0f,
    1.0f
};

float SETextureTileL1Effect::ms_afLightBlendWeight[3] =
{
    0.2f,
    0.7f,
    0.1f
};

//----------------------------------------------------------------------------
SETextureTileL1Effect::SETextureTileL1Effect(const std::string& rTileName)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("TextureTileL1.v_TextureTileL1");
    m_PShader[0] = SE_NEW SEPixelShader("TextureTileL1.p_TextureTileL1");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rTileName);

    SETexture* pTile = m_PShader[0]->GetTexture(0);
    pTile->SetWrapType(0, SETexture::REPEAT);
    pTile->SetWrapType(1, SETexture::REPEAT);

    TileX = 1.0f;
    TileY = 1.0f;
    AmbientWeight = 0.2f;
    DiffuseWeight = 0.7f; 
    SpecularWeight = 0.1f;
}
//----------------------------------------------------------------------------
SETextureTileL1Effect::SETextureTileL1Effect()
{
}
//----------------------------------------------------------------------------
SETextureTileL1Effect::~SETextureTileL1Effect()
{
}
//----------------------------------------------------------------------------
void SETextureTileL1Effect::OnLoadPrograms(int, SEProgram* pVProgram, 
    SEProgram* pPProgram, SEProgram*)
{
    SEUserConstant* pUC = pVProgram->GetUC("TileParams");
    SE_ASSERT( pUC );
    if( pUC )
    {
        pUC->SetDataSource((float*)&ms_afTileParams);
    }

    pUC = pPProgram->GetUC("LightBlendWeight");
    SE_ASSERT( pUC );
    if( pUC )
    {
        pUC->SetDataSource((float*)&ms_afLightBlendWeight);
    }
}
//----------------------------------------------------------------------------
void SETextureTileL1Effect::OnPreApplyEffect(SERenderer*, bool)
{
    ms_afTileParams[0] = TileX;
    ms_afTileParams[1] = TileY;
    ms_afLightBlendWeight[0] = AmbientWeight;
    ms_afLightBlendWeight[1] = DiffuseWeight;
    ms_afLightBlendWeight[2] = SpecularWeight;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SETextureTileL1Effect::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(TileX);
    rStream.Read(TileY);
    rStream.Read(AmbientWeight);
    rStream.Read(DiffuseWeight);
    rStream.Read(SpecularWeight);

    SE_END_DEBUG_STREAM_LOAD(SETextureTileL1Effect);
}
//----------------------------------------------------------------------------
void SETextureTileL1Effect::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEShaderEffect::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SETextureTileL1Effect::Register(SEStream& rStream) const
{
    return SEShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void SETextureTileL1Effect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEShaderEffect::Save(rStream);

    // native data
    rStream.Write(TileX);
    rStream.Write(TileY);
    rStream.Write(AmbientWeight);
    rStream.Write(DiffuseWeight);
    rStream.Write(SpecularWeight);

    SE_END_DEBUG_STREAM_SAVE(SETextureTileL1Effect);
}
//----------------------------------------------------------------------------
int SETextureTileL1Effect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEShaderEffect::GetDiskUsed(rVersion) +
        sizeof(TileX) + sizeof(TileY) + sizeof(AmbientWeight) + 
        sizeof(DiffuseWeight) + sizeof(SpecularWeight);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SETextureTileL1Effect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    pTree->Append(Format("tile x =", TileX));
    pTree->Append(Format("tile y =", TileY));
    pTree->Append(Format("ambient weight =", AmbientWeight));
    pTree->Append(Format("diffuse weight =", DiffuseWeight));
    pTree->Append(Format("specular weight", SpecularWeight));

    // children
    pTree->Append(SEShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------