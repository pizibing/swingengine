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

SE_IMPLEMENT_RTTI(Swing, TextureTileL1Effect, ShaderEffect);
SE_IMPLEMENT_STREAM(TextureTileL1Effect);
SE_IMPLEMENT_DEFAULT_NAME_ID(TextureTileL1Effect, ShaderEffect);

//SE_REGISTER_STREAM(TextureTileL1Effect);

float TextureTileL1Effect::ms_afTileParams[2] = 
{
    1.0f,
    1.0f
};

float TextureTileL1Effect::ms_afLightBlendWeight[3] =
{
    0.2f,
    0.7f,
    0.1f
};

//----------------------------------------------------------------------------
TextureTileL1Effect::TextureTileL1Effect(const std::string& rTileName)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("TextureTileL1.v_TextureTileL1");
    m_PShader[0] = SE_NEW PixelShader("TextureTileL1.p_TextureTileL1");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rTileName);

    Texture* pTile = m_PShader[0]->GetTexture(0);
    pTile->SetWrapType(0, Texture::REPEAT);
    pTile->SetWrapType(1, Texture::REPEAT);

    TileX = 1.0f;
    TileY = 1.0f;
    AmbientWeight = 0.2f;
    DiffuseWeight = 0.7f; 
    SpecularWeight = 0.1f;
}
//----------------------------------------------------------------------------
TextureTileL1Effect::TextureTileL1Effect()
{
}
//----------------------------------------------------------------------------
TextureTileL1Effect::~TextureTileL1Effect()
{
}
//----------------------------------------------------------------------------
void TextureTileL1Effect::OnLoadPrograms(int, Program* pVProgram, 
    Program* pPProgram, Program*)
{
    UserConstant* pUC = pVProgram->GetUC("TileParams");
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
void TextureTileL1Effect::OnPreApplyEffect(Renderer*, bool)
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
void TextureTileL1Effect::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(TileX);
    rStream.Read(TileY);
    rStream.Read(AmbientWeight);
    rStream.Read(DiffuseWeight);
    rStream.Read(SpecularWeight);

    SE_END_DEBUG_STREAM_LOAD(TextureTileL1Effect);
}
//----------------------------------------------------------------------------
void TextureTileL1Effect::Link(SEStream& rStream, SEStream::Link* pLink)
{
    ShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool TextureTileL1Effect::Register(SEStream& rStream) const
{
    return ShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void TextureTileL1Effect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ShaderEffect::Save(rStream);

    // native data
    rStream.Write(TileX);
    rStream.Write(TileY);
    rStream.Write(AmbientWeight);
    rStream.Write(DiffuseWeight);
    rStream.Write(SpecularWeight);

    SE_END_DEBUG_STREAM_SAVE(TextureTileL1Effect);
}
//----------------------------------------------------------------------------
int TextureTileL1Effect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = ShaderEffect::GetDiskUsed(rVersion) +
        sizeof(TileX) + sizeof(TileY) + sizeof(AmbientWeight) + 
        sizeof(DiffuseWeight) + sizeof(SpecularWeight);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* TextureTileL1Effect::SaveStrings(const char*)
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
    pTree->Append(ShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------