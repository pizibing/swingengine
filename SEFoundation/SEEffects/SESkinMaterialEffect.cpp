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
#include "SESkinMaterialEffect.h"
#include "SENode.h"
#include "SEVertexProgramCatalog.h"
#include "SETransformation.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SkinMaterialEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(SkinMaterialEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SkinMaterialEffect, ShaderEffect);

//SE_REGISTER_STREAM(SkinMaterialEffect);

Matrix4f SkinMaterialEffect::ms_aSkinMatrix[SM_COUNT] = 
{
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY,
    Matrix4f::IDENTITY
};
bool SkinMaterialEffect::ms_bSkinMatrixUCInitialized = false;

//----------------------------------------------------------------------------
SkinMaterialEffect::SkinMaterialEffect(int iBoneCount, Node** apBones, 
    Transformation* aOffset)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("SkinMaterial.v_SkinMaterial");
    m_PShader[0] = SE_NEW PixelShader("SkinMaterial.p_SkinMaterial");

    SE_ASSERT( iBoneCount < SM_COUNT );

    m_iBoneCount = iBoneCount;
    m_apBones = apBones;
    m_aOffset = aOffset;
}
//----------------------------------------------------------------------------
SkinMaterialEffect::SkinMaterialEffect()
{
    m_iBoneCount = 0;
    m_apBones = 0;
    m_aOffset = 0;
}
//----------------------------------------------------------------------------
SkinMaterialEffect::~SkinMaterialEffect()
{
    SE_DELETE[] m_apBones;
    SE_DELETE[] m_aOffset;
}
//----------------------------------------------------------------------------
void SkinMaterialEffect::OnLoadPrograms(int, Program* pVProgram, Program*,
    Program*)
{
    if( !ms_bSkinMatrixUCInitialized )
    {
        char tempName[15]; // "SkinMatrix[xx]"

        int iMaxCount = 0;
        int iVProfile = VertexProgramCatalog::GetActive()->GetProfile();

        switch( iVProfile )
        {
        case Renderer::VS_2_0:
            iMaxCount = VS_2_0_COUNT;
            break;
        case Renderer::VS_3_0:
            iMaxCount = VS_3_0_COUNT;
            break;
        case Renderer::ARBVP1:
            iMaxCount = ARBVP1_COUNT;
            break;
        case Renderer::VP40:
            iMaxCount = VP40_COUNT;
            break;
        case Renderer::SFTVP1:
            iMaxCount = SFTVP1_COUNT;
            break;
        }

        for( int i = 0; i < iMaxCount; i++ )
        {
            System::SE_Sprintf(tempName, 15, "SkinMatrix[%d]", i);
            UserConstant* pUC = pVProgram->GetUC(tempName);
            SE_ASSERT( pUC );
        
            if( pUC )
                pUC->SetDataSource((float*)ms_aSkinMatrix[i]);
        }

        ms_bSkinMatrixUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void SkinMaterialEffect::OnPreApplyEffect(Renderer*, bool)
{
    Transformation tempT;
    for( int i = 0; i < m_iBoneCount; i++ )
    {
        tempT.Product(m_aOffset[i], m_apBones[i]->World);
        tempT.GetHomogeneous(ms_aSkinMatrix[i]);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SkinMaterialEffect::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ShaderEffect::Load(rStream, pLink);

    // native data
    rStream.Read(m_iBoneCount);

    int i;

    m_aOffset = SE_NEW Transformation[m_iBoneCount];
    for( i = 0; i < m_iBoneCount; i++ )
    {
        rStream.Read(m_aOffset[i]);
    }

    // link data
    for( i = 0; i < m_iBoneCount; i++ )
    {
        Object* pObject;
        rStream.Read(pObject);  // m_apBones[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SkinMaterialEffect);
}
//----------------------------------------------------------------------------
void SkinMaterialEffect::Link(Stream& rStream, Stream::Link* pLink)
{
    ShaderEffect::Link(rStream, pLink);

    m_apBones = SE_NEW Node*[m_iBoneCount];
    for( int i = 0; i < m_iBoneCount; i++ )
    {
        Object* pLinkID = pLink->GetLinkID();
        m_apBones[i] = (Node*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SkinMaterialEffect::Register(Stream& rStream) const
{
    if( !ShaderEffect::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < m_iBoneCount; i++ )
    {
        if( m_apBones[i] )
        {
            m_apBones[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SkinMaterialEffect::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ShaderEffect::Save(rStream);

    // native data
    rStream.Write(m_iBoneCount);

    int i;

    for( i = 0; i < m_iBoneCount; i++ )
    {
        rStream.Write(m_aOffset[i]);
    }

    // link data
    for( i = 0; i < m_iBoneCount; i++ )
    {
        rStream.Write(m_apBones[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SkinMaterialEffect);
}
//----------------------------------------------------------------------------
int SkinMaterialEffect::GetDiskUsed(const StreamVersion& rVersion) const
{
    return ShaderEffect::GetDiskUsed(rVersion) +
        sizeof(m_iBoneCount) + 
        m_iBoneCount*Transformation::DISK_USED +
        m_iBoneCount*sizeof(m_apBones[0]);
}
//----------------------------------------------------------------------------
StringTree* SkinMaterialEffect::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(Format("bone count = ", m_iBoneCount));

    // children
    pTree->Append(ShaderEffect::SaveStrings());
    pTree->Append(Format("bones", m_iBoneCount, m_apBones));

    return pTree;
}
//----------------------------------------------------------------------------