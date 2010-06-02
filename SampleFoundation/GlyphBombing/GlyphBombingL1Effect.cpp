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

#include "GlyphBombingL1Effect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, GlyphBombingL1Effect, SEShaderEffect);
SE_IMPLEMENT_STREAM(GlyphBombingL1Effect);
SE_IMPLEMENT_DEFAULT_NAME_ID(GlyphBombingL1Effect, SEShaderEffect);

SE_REGISTER_STREAM(GlyphBombingL1Effect);

float GlyphBombingL1Effect::ms_fSpecularContribution = 0.0f;
float GlyphBombingL1Effect::ms_fScaleFactor = 0.0f;
SEColorRGBA GlyphBombingL1Effect::ms_ModelColor = SEColorRGBA::SE_RGBA_BLACK;
float GlyphBombingL1Effect::ms_fColAdjust = 0.0f;
float GlyphBombingL1Effect::ms_fPercentage = 0.0f;
float GlyphBombingL1Effect::ms_fSamplesPerCell = 0.0f;
float GlyphBombingL1Effect::ms_fRO1 = 0.0f;
float GlyphBombingL1Effect::ms_fRandomScale = 0.0f;
float GlyphBombingL1Effect::ms_fRandomRotate = 0.0f;
bool GlyphBombingL1Effect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
GlyphBombingL1Effect::GlyphBombingL1Effect(const char* acBaseName,
    const char* acRandomName)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("GlyphBombL1.v_GlyphBombL1");
    m_PShader[0] = SE_NEW SEPixelShader("GlyphBombL1.p_GlyphBombL1");

    m_PShader[0]->SetTextureCount(2);
    m_PShader[0]->SetImageName(0, acBaseName);
    m_PShader[0]->SetImageName(1, acRandomName);

    SpecularContribution = 0.2f;
    ScaleFactor = 4.0f;
    ModelColor = SEColorRGBA::SE_RGBA_WHITE;
    ColAdjust = 0.5f;
    Percentage = 1.0f;
    SamplesPerCell = 1.0f;
    RO1 = 0.5f;
    RandomScale = 0.0f;
    RandomRotate = 0.0f;
}
//----------------------------------------------------------------------------
GlyphBombingL1Effect::GlyphBombingL1Effect()
{
    SpecularContribution = 0.2f;
    ScaleFactor = 4.0f;
    ModelColor = SEColorRGBA::SE_RGBA_WHITE;
    ColAdjust = 0.5f;
    Percentage = 1.0f;
    SamplesPerCell = 1.0f;
    RO1 = 0.5f;
    RandomScale = 0.0f;
    RandomRotate = 0.0f;
}
//----------------------------------------------------------------------------
GlyphBombingL1Effect::~GlyphBombingL1Effect()
{
}
//----------------------------------------------------------------------------
void GlyphBombingL1Effect::OnLoadPrograms(int, SEProgram* pVProgram,
    SEProgram* pPProgram, SEProgram*)
{
    if( !ms_bUCInitialized )
    {
        SEUserConstant* pUC = pVProgram->GetUC("v_fSpecularContribution");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fSpecularContribution);
        }

        pUC = pVProgram->GetUC("v_fScaleFactor");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fScaleFactor);
        }

        pUC = pPProgram->GetUC("p_kModelColor");
        if( pUC )
        {
            pUC->SetDataSource((float*)ms_ModelColor);
        }

        pUC = pPProgram->GetUC("p_fColAdjust");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fColAdjust);
        }

        pUC = pPProgram->GetUC("p_fPercentage");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fPercentage);
        }

        pUC = pPProgram->GetUC("p_fSamplesPerCell");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fSamplesPerCell);
        }

        pUC = pPProgram->GetUC("p_fRO1");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fRO1);
        }

        pUC = pPProgram->GetUC("p_fRandomScale");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fRandomScale);
        }

        pUC = pPProgram->GetUC("p_fRandomRotate");
        if( pUC )
        {
            pUC->SetDataSource(&ms_fRandomRotate);
        }

        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void GlyphBombingL1Effect::OnPreApplyEffect(SERenderer*, bool)
{
    ms_fSpecularContribution = SpecularContribution;
    ms_fScaleFactor = ScaleFactor;
    ms_ModelColor = ModelColor;
    ms_fColAdjust = ColAdjust;
    ms_fPercentage = Percentage;
    ms_fSamplesPerCell = SamplesPerCell;
    ms_fRO1 = RO1;
    ms_fRandomScale = RandomScale;
    ms_fRandomRotate = RandomRotate;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void GlyphBombingL1Effect::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(SpecularContribution);
    rStream.Read(ScaleFactor);
    rStream.Read(ModelColor);
    rStream.Read(ColAdjust);
    rStream.Read(Percentage);
    rStream.Read(SamplesPerCell);
    rStream.Read(RO1);
    rStream.Read(RandomScale);
    rStream.Read(RandomRotate);

    SE_END_DEBUG_STREAM_LOAD(GlyphBombingL1Effect);
}
//----------------------------------------------------------------------------
void GlyphBombingL1Effect::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEShaderEffect::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool GlyphBombingL1Effect::Register(SEStream& rStream) const
{
    return SEShaderEffect::Register(rStream);
}
//----------------------------------------------------------------------------
void GlyphBombingL1Effect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEShaderEffect::Save(rStream);

    // native data
    rStream.Write(SpecularContribution);
    rStream.Write(ScaleFactor);
    rStream.Write(ModelColor);
    rStream.Write(ColAdjust);
    rStream.Write(Percentage);
    rStream.Write(SamplesPerCell);
    rStream.Write(RO1);
    rStream.Write(RandomScale);
    rStream.Write(RandomRotate);

    SE_END_DEBUG_STREAM_SAVE(GlyphBombingL1Effect);
}
//----------------------------------------------------------------------------
int GlyphBombingL1Effect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEShaderEffect::GetDiskUsed(rVersion) +
        sizeof(float) +      // SpecularContribution
        sizeof(float) +      // ScaleFactor
        sizeof(SEColorRGBA) +  // ModelColor
        sizeof(float) +      // ColAdjust
        sizeof(float) +      // Percentage
        sizeof(float) +      // SamplesPerCell
        sizeof(float) +      // RO1
        sizeof(float) +      // RandomScale
        sizeof(float);       // RandomRotate

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* GlyphBombingL1Effect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("specular contribution =", SpecularContribution));
    pTree->Append(Format("scale factor =", ScaleFactor));
    pTree->Append(Format("model color =", ModelColor));
    pTree->Append(Format("col adjust =", ColAdjust));
    pTree->Append(Format("percentage =", Percentage));
    pTree->Append(Format("samples per cell =", SamplesPerCell));
    pTree->Append(Format("R01 =", RO1));
    pTree->Append(Format("random scale =", RandomScale));
    pTree->Append(Format("random rotate =", RandomRotate));

    // children
    pTree->Append(SEShaderEffect::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
