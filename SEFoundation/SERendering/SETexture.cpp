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
#include "SETexture.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SETexture, SEObject);
SE_IMPLEMENT_STREAM(SETexture);
SE_IMPLEMENT_DEFAULT_NAME_ID(SETexture, SEObject);

//SE_REGISTER_STREAM(SETexture);

const char* SETexture::ms_pFilterType[MAX_FILTER_TYPES] =
{
    "NEAREST",
    "LINEAR",
    "NEAREST_NEAREST",
    "NEAREST_LINEAR",
    "LINEAR_NEAREST",
    "LINEAR_LINEAR"
};

const char* SETexture::ms_pWrapType[MAX_WRAP_TYPES] =
{
    "CLAMP",
    "REPEAT",
    "MIRRORED_REPEAT",
    "CLAMP_BORDER",
    "CLAMP_EDGE"
};

const char* SETexture::ms_pDepthCompare[DC_COUNT] =
{
    "DC_NEVER",
    "DC_LESS",
    "DC_EQUAL",
    "DC_LEQUAL",
    "DC_GREATER",
    "DC_NOTEQUAL",
    "DC_GEQUAL",
    "DC_ALWAYS"
};

//----------------------------------------------------------------------------
SETexture::SETexture(SEImage* pImage)
    :
    m_spImage(pImage),
    m_BorderColor(SEColorRGBA::SE_RGBA_BLACK)
{
    if( pImage )
    {
        SetName(pImage->GetName());
    }
    else
    {
        SetName("");
    }

    m_eFType = LINEAR;
    m_eWrapTypes[0] = CLAMP_EDGE;
    m_eWrapTypes[1] = CLAMP_EDGE;
    m_eWrapTypes[2] = CLAMP_EDGE;
    m_eCompare = DC_COUNT;
    m_bOffscreenTexture = false;
}
//----------------------------------------------------------------------------
SETexture::SETexture(SEImage* pDepthImage, DepthCompare eCompare)
    :
    m_spImage(pDepthImage),
    m_BorderColor(SEColorRGBA::SE_RGBA_BLACK)
{
    SetName("");
    m_eFType = LINEAR;
    m_eWrapTypes[0] = CLAMP_EDGE;
    m_eWrapTypes[1] = CLAMP_EDGE;
    m_eWrapTypes[2] = CLAMP_EDGE;
    m_eCompare = eCompare;

    m_bOffscreenTexture = false;
}
//----------------------------------------------------------------------------
SETexture::~SETexture()
{
    // 通知所有正在使用此texture的renderer,此资源正要被释放,
    // 因此这些renderer可以及时释放掉与此texture有关的其他资源(VRAM中)
    Release();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SETexture::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    int iTemp;
    rStream.Read(iTemp);
    m_eFType = (FilterType)iTemp;
    for( int i = 0; i < 3; i++ )
    {
        rStream.Read(iTemp);
        m_eWrapTypes[i] = (WrapType)iTemp;
    }
    rStream.Read(m_BorderColor);
    rStream.Read(iTemp);
    m_eCompare = (DepthCompare)iTemp;
    rStream.Read(m_bOffscreenTexture);

    // 数据成员m_spImage在程序运行时刻装载资源时设置.

    SE_END_DEBUG_STREAM_LOAD(SETexture);
}
//----------------------------------------------------------------------------
void SETexture::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SETexture::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SETexture::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

    rStream.Write((int)m_eFType);
    for( int i = 0; i < 3; i++ )
    {
        rStream.Write((int)m_eWrapTypes[i]);
    }
    rStream.Write(m_BorderColor);
    rStream.Write((int)m_eCompare);
    rStream.Write(m_bOffscreenTexture);

    // 数据成员m_spImage在程序运行时刻装载资源时设置.

    SE_END_DEBUG_STREAM_SAVE(SETexture);
}
//----------------------------------------------------------------------------
int SETexture::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEObject::GetDiskUsed(rVersion) +
        sizeof(int) + // m_eFType
        3*sizeof(int) + // m_eWrapTypes[]
        sizeof(m_BorderColor) +
        sizeof(int) + // m_eCompare
        sizeof(char);  // m_bOffscreenTexture
}
//----------------------------------------------------------------------------
SEStringTree* SETexture::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("filter = ", ms_pFilterType[m_eFType]));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    for( int i = 0; i < 3; i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "wrap[%d] =", i);
        pTree->Append(Format(acTitle, ms_pWrapType[m_eWrapTypes[i]]));
    }

    pTree->Append(Format("border color =", m_BorderColor));
    if( m_eCompare != DC_COUNT )
    {
        pTree->Append(Format("depth compare = ",
            ms_pDepthCompare[m_eCompare]));
    }
    pTree->Append(Format("offscreen =", m_bOffscreenTexture));

    // children
    pTree->Append(SEObject::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
