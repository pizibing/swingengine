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
#include "SETerrainEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, TerrainEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(TerrainEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(TerrainEffect, ShaderEffect);

//SE_REGISTER_STREAM(TerrainEffect);

float TerrainEffect::ms_afFogColorDensity[4] = {0.0f, 0.0f, 0.0f, 0.0f};
bool TerrainEffect::ms_bFogColorDensityUCInitialized = false;

//----------------------------------------------------------------------------
TerrainEffect::TerrainEffect(const char* acBaseName,
    const char* acDetailName, const ColorRGB& rFogColor, float fFogDensity)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader(
        "BaseMulDetailFogExpSqr.v_BaseMulDetailFogExpSqr");
    m_PShader[0] = SE_NEW PixelShader(
        "BaseMulDetailFogExpSqr.p_BaseMulDetailFogExpSqr");

    m_PShader[0]->SetTextureCount(2);
    m_PShader[0]->SetImageName(0, acBaseName);
    m_PShader[0]->SetImageName(1, acDetailName);

    Texture* pBase = m_PShader[0]->GetTexture(0);
    pBase->SetFilterType(Texture::LINEAR_LINEAR);
    pBase->SetWrapType(0, Texture::REPEAT);
    pBase->SetWrapType(1, Texture::REPEAT);

    Texture* pDetail = m_PShader[0]->GetTexture(1);
    pDetail->SetFilterType(Texture::LINEAR_LINEAR);

    SetFogColor(rFogColor);
    SetFogDensity(fFogDensity);
}
//----------------------------------------------------------------------------
TerrainEffect::TerrainEffect()
{
}
//----------------------------------------------------------------------------
TerrainEffect::~TerrainEffect()
{
}
//----------------------------------------------------------------------------
void TerrainEffect::OnLoadPrograms(int, Program* pVProgram,
    Program* pPProgram, Program*)
{
    if( !ms_bFogColorDensityUCInitialized )
	{
        UserConstant* pUC = pVProgram->GetUC("FogColorDensity");
        if( pUC )
            pUC->SetDataSource(ms_afFogColorDensity);

        pUC = pPProgram->GetUC("FogColorDensity");
        if( pUC )
            pUC->SetDataSource(ms_afFogColorDensity);

        ms_bFogColorDensityUCInitialized = true;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void TerrainEffect::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ShaderEffect::Load(rStream, pLink);

    rStream.Read(4, ms_afFogColorDensity);

    SE_END_DEBUG_STREAM_LOAD(TerrainEffect);
}
//----------------------------------------------------------------------------
void TerrainEffect::Link(Stream& rStream, Stream::Link* pLink)
{
    ShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool TerrainEffect::Register(Stream& rStream) const
{
    return ShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void TerrainEffect::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ShaderEffect::Save(rStream);

    rStream.Write(4, ms_afFogColorDensity);

    SE_END_DEBUG_STREAM_SAVE(TerrainEffect);
}
//----------------------------------------------------------------------------
int TerrainEffect::GetDiskUsed(const StreamVersion& rVersion) const
{
    return ShaderEffect::GetDiskUsed(rVersion) +
        4*sizeof(ms_afFogColorDensity[0]);
}
//----------------------------------------------------------------------------
StringTree* TerrainEffect::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    ColorRGB tempColor(ms_afFogColorDensity[0], ms_afFogColorDensity[1],
        ms_afFogColorDensity[2]);
    pTree->Append(Format("fog color =", tempColor));
    pTree->Append(Format("fog density =", ms_afFogColorDensity[3]));

    // children
    pTree->Append(ShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
