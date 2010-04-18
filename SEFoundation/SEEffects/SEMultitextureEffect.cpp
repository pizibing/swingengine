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
#include "SEMultitextureEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, MultitextureEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(MultitextureEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(MultitextureEffect, ShaderEffect);

//SE_REGISTER_STREAM(MultitextureEffect);

//----------------------------------------------------------------------------
MultitextureEffect::MultitextureEffect(int iTextureCount)
    :
    ShaderEffect(1)
{
    m_aImageName = 0;
    SetTextureCount(iTextureCount);
}
//----------------------------------------------------------------------------
MultitextureEffect::MultitextureEffect()
{
    m_iTextureCount = 0;
    m_aImageName = 0;
}
//----------------------------------------------------------------------------
MultitextureEffect::~MultitextureEffect()
{
}
//----------------------------------------------------------------------------
void MultitextureEffect::SetTextureCount(int iTextureCount)
{
    SE_ASSERT( iTextureCount >= 1 );

    m_iTextureCount = iTextureCount;
    SE_DELETE[] m_aImageName;
    m_aImageName = SE_NEW std::string[m_iTextureCount];

    m_RStateBlocks.resize(m_iTextureCount);
    SetDefaultAlphaState();
}
//----------------------------------------------------------------------------
int MultitextureEffect::GetTextureCount() const
{
    return m_iTextureCount;
}
//----------------------------------------------------------------------------
void MultitextureEffect::SetImageName(int i, const std::string& rImageName)
{
    SE_ASSERT( 0 <= i && i < m_iTextureCount );

    m_aImageName[i] = rImageName;
}
//----------------------------------------------------------------------------
const std::string& MultitextureEffect::GetImageName(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iTextureCount );

    return m_aImageName[i];
}
//----------------------------------------------------------------------------
void MultitextureEffect::Configure()
{
    if( m_iTextureCount == 1 )
    {
        m_VShader[0] = SE_NEW SEVertexShader("SETexture.v_Texture");
        m_PShader[0] = SE_NEW SEPixelShader("SETexture.p_Texture");
        m_PShader[0]->SetTextureCount(1);
        m_PShader[0]->SetImageName(0, m_aImageName[0]);

        return;
    }

    const size_t uiNumberSize = 4;
    char acNumber[uiNumberSize];

    // In a single-effect drawing pass, texture 0 is a source to be blended
    // with a nonexistent destination.  As such, we think of the source mode
    // as SBF_ONE and the destination mode as SDF_ZERO.
    std::string tempVShaderName("T0d2");
    std::string tempPShaderName("T0s1d0");
    int i;
    for( i = 1; i < m_iTextureCount; i++ )
    {
        tempVShaderName += "T";
        tempPShaderName += "T";
        SESystem::SE_Sprintf(acNumber, uiNumberSize, "%d", i);
        tempVShaderName += std::string(acNumber) + std::string("d2");
        tempPShaderName += std::string(acNumber);

        SEGlobalState* pState = m_RStateBlocks[i]->States[SEGlobalState::ALPHA];
        SEAlphaState* pAS = (SEAlphaState*)pState;

        // Source blending mode.
        tempPShaderName += "s";
        SESystem::SE_Sprintf(acNumber, uiNumberSize, "%d", (int)pAS->SrcBlend);
        tempPShaderName += std::string(acNumber);

        // Destination blending mode.
        tempPShaderName += "d";
        SESystem::SE_Sprintf(acNumber, uiNumberSize, "%d", (int)pAS->DstBlend);
        tempPShaderName += std::string(acNumber);
    }
    tempVShaderName += std::string("PassThrough");

    m_VShader[0] = SE_NEW SEVertexShader(tempVShaderName);
    m_PShader[0] = SE_NEW SEPixelShader(tempPShaderName);
    m_PShader[0]->SetTextureCount(m_iTextureCount);
    for( i = 0; i < m_iTextureCount; i++ )
    {
        m_PShader[0]->SetImageName(i, m_aImageName[i]);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void MultitextureEffect::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(m_iTextureCount);
    SetTextureCount(m_iTextureCount);
    for( int i = 0; i < m_iTextureCount; i++ )
    {
        rStream.Read(m_aImageName[i]);
    }

    SE_END_DEBUG_STREAM_LOAD(MultitextureEffect);
}
//----------------------------------------------------------------------------
void MultitextureEffect::Link(SEStream& rStream, SEStream::Link* pLink)
{
    ShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool MultitextureEffect::Register(SEStream& rStream) const
{
    return ShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void MultitextureEffect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ShaderEffect::Save(rStream);

    // native data
    rStream.Write(m_iTextureCount);
    for( int i = 0; i < m_iTextureCount; i++ )
    {
        rStream.Write(m_aImageName[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(MultitextureEffect);
}
//----------------------------------------------------------------------------
int MultitextureEffect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = ShaderEffect::GetDiskUsed(rVersion) +
        sizeof(m_iTextureCount);
 
    for( int i = 0; i < m_iTextureCount; i++ )
    {
        iSize += sizeof(int) + (int)m_aImageName[i].length();
    }

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* MultitextureEffect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("texture quantity =", m_iTextureCount));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    for( int i = 0; i < m_iTextureCount; i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "image[%d] =", i);
        pTree->Append(Format(acTitle, m_aImageName[i].c_str()));
    }

    // children
    pTree->Append(ShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
