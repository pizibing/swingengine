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

SE_IMPLEMENT_RTTI(Swing, SETerrainEffect, SEShaderEffect);
SE_IMPLEMENT_STREAM(SETerrainEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SETerrainEffect, SEShaderEffect);

//SE_REGISTER_STREAM(SETerrainEffect);

float SETerrainEffect::ms_afFogColorDensity[4] = {0.0f, 0.0f, 0.0f, 0.0f};
bool SETerrainEffect::ms_bFogColorDensityUCInitialized = false;

//----------------------------------------------------------------------------
SETerrainEffect::SETerrainEffect(const char* acBaseName,
    const char* acDetailName, const SEColorRGB& rFogColor, float fFogDensity)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader(
        "BaseMulDetailFogExpSqr.v_BaseMulDetailFogExpSqr");
    m_PShader[0] = SE_NEW SEPixelShader(
        "BaseMulDetailFogExpSqr.p_BaseMulDetailFogExpSqr");

    m_PShader[0]->SetTextureCount(2);
    m_PShader[0]->SetImageName(0, acBaseName);
    m_PShader[0]->SetImageName(1, acDetailName);

    SETexture* pBase = m_PShader[0]->GetTexture(0);
    pBase->SetFilterType(SETexture::LINEAR_LINEAR);
    pBase->SetWrapType(0, SETexture::REPEAT);
    pBase->SetWrapType(1, SETexture::REPEAT);

    SETexture* pDetail = m_PShader[0]->GetTexture(1);
    pDetail->SetFilterType(SETexture::LINEAR_LINEAR);

    SetFogColor(rFogColor);
    SetFogDensity(fFogDensity);
}
//----------------------------------------------------------------------------
SETerrainEffect::SETerrainEffect()
{
}
//----------------------------------------------------------------------------
SETerrainEffect::~SETerrainEffect()
{
}
//----------------------------------------------------------------------------
void SETerrainEffect::OnLoadPrograms(int, SEProgram* pVProgram,
    SEProgram* pPProgram, SEProgram*)
{
    if( !ms_bFogColorDensityUCInitialized )
	{
        SEUserConstant* pUC = pVProgram->GetUC("FogColorDensity");
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
void SETerrainEffect::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEShaderEffect::Load(rStream, pLink);

    rStream.Read(4, ms_afFogColorDensity);

    SE_END_DEBUG_STREAM_LOAD(SETerrainEffect);
}
//----------------------------------------------------------------------------
void SETerrainEffect::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SETerrainEffect::Register(SEStream& rStream) const
{
    return SEShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void SETerrainEffect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEShaderEffect::Save(rStream);

    rStream.Write(4, ms_afFogColorDensity);

    SE_END_DEBUG_STREAM_SAVE(SETerrainEffect);
}
//----------------------------------------------------------------------------
int SETerrainEffect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEShaderEffect::GetDiskUsed(rVersion) +
        4*sizeof(ms_afFogColorDensity[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SETerrainEffect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    SEColorRGB tempColor(ms_afFogColorDensity[0], ms_afFogColorDensity[1],
        ms_afFogColorDensity[2]);
    pTree->Append(Format("fog color =", tempColor));
    pTree->Append(Format("fog density =", ms_afFogColorDensity[3]));

    // children
    pTree->Append(SEShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
