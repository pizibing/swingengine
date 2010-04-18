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
#include "SETextureTileEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, TextureTileEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(TextureTileEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(TextureTileEffect, ShaderEffect);

//SE_REGISTER_STREAM(TextureTileEffect);

float TextureTileEffect::ms_afTileParams[2] = 
{
    1.0f,
    1.0f
};

//----------------------------------------------------------------------------
TextureTileEffect::TextureTileEffect(const std::string& rTileName)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("TextureTile.v_TextureTile");
    m_PShader[0] = SE_NEW SEPixelShader("TextureTile.p_TextureTile");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rTileName);

    SETexture* pTile = m_PShader[0]->GetTexture(0);
    pTile->SetWrapType(0, SETexture::REPEAT);
    pTile->SetWrapType(1, SETexture::REPEAT);

    TileX = 1.0f;
    TileY = 1.0f;
}
//----------------------------------------------------------------------------
TextureTileEffect::TextureTileEffect()
{
}
//----------------------------------------------------------------------------
TextureTileEffect::~TextureTileEffect()
{
}
//----------------------------------------------------------------------------
void TextureTileEffect::OnLoadPrograms(int, SEProgram* pVProgram, SEProgram*, 
    SEProgram*)
{
    SEUserConstant* pUC = pVProgram->GetUC("TileParams");
    SE_ASSERT( pUC );

    if( pUC )
    {
        pUC->SetDataSource((float*)&ms_afTileParams);
    }
}
//----------------------------------------------------------------------------
void TextureTileEffect::OnPreApplyEffect(SERenderer*, bool)
{
    ms_afTileParams[0] = TileX;
    ms_afTileParams[1] = TileY;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void TextureTileEffect::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(TileX);
    rStream.Read(TileY);

    SE_END_DEBUG_STREAM_LOAD(TextureTileEffect);
}
//----------------------------------------------------------------------------
void TextureTileEffect::Link(SEStream& rStream, SEStream::Link* pLink)
{
    ShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool TextureTileEffect::Register(SEStream& rStream) const
{
    return ShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void TextureTileEffect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ShaderEffect::Save(rStream);

    // native data
    rStream.Write(TileX);
    rStream.Write(TileY);

    SE_END_DEBUG_STREAM_SAVE(TextureTileEffect);
}
//----------------------------------------------------------------------------
int TextureTileEffect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = ShaderEffect::GetDiskUsed(rVersion) +
        sizeof(TileX) + sizeof(TileY);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* TextureTileEffect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    pTree->Append(Format("tile x =", TileX));
    pTree->Append(Format("tile y =", TileY));

    // children
    pTree->Append(ShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------