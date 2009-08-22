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
#include "SEShadowMapEffect.h"
#include "SEBitHacks.h"
#include "SEGeometry.h"
#include "SEUnculledSet.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ShadowMapEffect, Effect);
SE_IMPLEMENT_STREAM(ShadowMapEffect);

//SE_REGISTER_STREAM(ShadowMapEffect);

//----------------------------------------------------------------------------
ShadowMapEffect::ShadowMapEffect(Camera* pProjector,
    const String& rProjectionImage, Image::FormatMode eDepthFormat, 
    int iDepthWidth, int iDepthHeight, float fDepthBias)
    :
    m_spProjector(pProjector)
{
    // 20090305更新.
    //SE_ASSERT(IsPowerOfTwo((unsigned int)iDepthWidth)
    //    && IsPowerOfTwo((unsigned int)iDepthHeight));

    // 创建depth effect.
    VertexShader* pVShader = 
        SE_NEW VertexShader("ProjectedShadow.v_ProjectedDepth");
    PixelShader* pPShader = 
       SE_NEW PixelShader("ProjectedShadow.p_ProjectedDepth");
    m_spDepthEffect = SE_NEW ShaderEffect(1);
    m_spDepthEffect->SetVShader(0, pVShader);
    m_spDepthEffect->SetPShader(0, pPShader);
    m_pDepthBuffer = 0;  // 延迟创建,直到第一次Draw调用时.

    // 为depth texture创建一个image.
    int iCount = 4*iDepthWidth*iDepthHeight;
    unsigned char* aucData = SE_NEW unsigned char[iCount];
    m_spDepthImage = SE_NEW Image(eDepthFormat, iDepthWidth,
        iDepthHeight, aucData, "DepthImage");

    // 创建shadow map effect.
    pVShader = SE_NEW VertexShader("ProjectedShadow.v_ShadowMap");
    pPShader = SE_NEW PixelShader("ProjectedShadow.p_ShadowMap");
    pPShader->SetTextureCount(2);
    pPShader->SetImageName(0, rProjectionImage);
    pPShader->SetImageName(1, "DepthImage");
    Texture* pProjectedTexture = pPShader->GetTexture(0);
    pProjectedTexture->SetFilterType(Texture::LINEAR);
    m_spShadowEffect = SE_NEW ShaderEffect(1);
    m_spShadowEffect->SetVShader(0, pVShader);
    m_spShadowEffect->SetPShader(0, pPShader);
    AlphaState* pAState = m_spShadowEffect->GetBlending(0);
    pAState->SrcBlend = AlphaState::SBF_DST_COLOR;
    pAState->DstBlend = AlphaState::DBF_ZERO;

    m_afDepthBias[0] = fDepthBias;
}
//----------------------------------------------------------------------------
ShadowMapEffect::ShadowMapEffect()
{
    m_pDepthBuffer = 0;
    m_pDepthTexture = 0;
}
//----------------------------------------------------------------------------
ShadowMapEffect::~ShadowMapEffect()
{
    SE_DELETE m_pDepthBuffer;
}
//----------------------------------------------------------------------------
void ShadowMapEffect::Draw(Renderer* pRenderer, Spatial*, int iMin, int iMax, 
    UnculledObject* pVisibleSet)
{
    // 由于需要用到具体的渲染器实例,所以depth buffer在这里延迟创建.
    // 因为shadow map effect可能会从磁盘通过stream装载,因此有必要延迟创建.
    if( !m_pDepthBuffer )
    {
        m_pDepthTexture = m_spShadowEffect->GetPShader(0)->GetTexture(1);
        m_pDepthTexture->SetFilterType(Texture::LINEAR);
        m_pDepthTexture->SetOffscreenTexture(true);
        pRenderer->LoadResources(m_spShadowEffect);

        PixelProgram* pProgram = m_spShadowEffect->GetPProgram(0);
        pProgram->GetUC("DepthBias")->SetDataSource(m_afDepthBias);

        Texture** apTargets = SE_NEW Texture*[1];
        apTargets[0] = m_pDepthTexture;
        m_pDepthBuffer = FrameBuffer::Create(pRenderer->GetFormatType(),
            pRenderer->GetDepthType(), pRenderer->GetStencilType(),
            pRenderer->GetBufferingType(), pRenderer->GetMultisamplingType(),
            pRenderer, 1, apTargets);
        SE_ASSERT(m_pDepthBuffer);
    }

    // 用projector作为camera渲染出深度图.
    // projector camera的设置必须先于framebuffer的Enable函数,
    // 因为在Enable函数中将会使用projector的相关变换矩阵.
    Camera* pSaveCamera = pRenderer->GetCamera();
    pRenderer->SetCamera(m_spProjector);
    m_pDepthBuffer->Enable();
    pRenderer->ClearBuffers();

    // 另一个试图解决depth bias问题的方法.
    // CullState* pCState = pRenderer->GetCullState();
    // pCState->CullFace = CullState::CT_FRONT;
    // pRenderer->SetCullState(pCState);

    int i;
    for( i = iMin; i <= iMax; i++ )
    {
        if( pVisibleSet[i].IsRenderable() )
        {
            Geometry* pGeometry = (Geometry*)pVisibleSet[i].Object;
            pGeometry->AttachEffect(m_spDepthEffect);
            pGeometry->SetStartEffect(pGeometry->GetEffectCount() - 1);
            pRenderer->Draw(pGeometry);
            pGeometry->SetStartEffect(0);
            pGeometry->DetachEffect(m_spDepthEffect);
        }
    }

    // 另一个试图解决depth bias问题的方法.
    // pCState->CullFace = CullState::CT_BACK;
    // pRenderer->SetCullState(pCState);

//#if 0
//    // BEGIN TEST
//    m_pDepthBuffer->CopyToTexture(true);
//    Image* pDTImage = m_pDepthTexture->GetImage();
//    ImageRGB82D tempImage(pDTImage->GetBound(0), pDTImage->GetBound(1));
//    unsigned char* pucData = pDTImage->GetData();
//    for( int i = 0; i < pDTImage->GetCount(); i++ )
//    {
//        unsigned char ucR = *pucData++;
//        unsigned char ucG = *pucData++;
//        unsigned char ucB = *pucData++;
//        pucData++;
//        tempImage[i] = GetColor24(ucR, ucG, ucB);
//    }
//    tempImage.Save("dimage.im");
//    // END TEST
//#endif

    // 深度图渲染完毕.必须在调用Disable函数前,恢复之前的camera.
    // 从而使之前的camera的相关变换矩阵在Disable函数中被使用.
    pRenderer->SetCamera(pSaveCamera);
    m_pDepthBuffer->Disable();

    // 正常渲染shadow map effect作用域内的所有可渲染对象, 
    // shadow effect中同时使用了projection image和shadow.
    // 通过projection image可以直观的观察到projector作为camera时的渲染区域.
    pRenderer->SetProjector(m_spProjector);
    pRenderer->ClearBuffers();
    for( i = iMin; i <= iMax; i++ )
    {
        if( pVisibleSet[i].IsRenderable() )
        {
            Geometry* pGeometry = (Geometry*)pVisibleSet[i].Object;
            pGeometry->AttachEffect(m_spShadowEffect);
            pRenderer->Draw(pGeometry);
            pGeometry->DetachEffect(m_spShadowEffect);
        }
    }
    pRenderer->SetProjector(0);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* ShadowMapEffect::GetObjectByName(const String& rName)
{
    Object* pFound = Effect::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( m_spProjector )
    {
        pFound = m_spProjector->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spDepthEffect )
    {
        pFound = m_spDepthEffect->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spDepthImage )
    {
        pFound = m_spDepthImage->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spShadowEffect )
    {
        pFound = m_spShadowEffect->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void ShadowMapEffect::GetAllObjectsByName(const String& rName,
    std::vector<Object*>& rObjects)
{
    Effect::GetAllObjectsByName(rName, rObjects);

    if( m_spProjector )
    {
        m_spProjector->GetAllObjectsByName(rName, rObjects);
    }

    if( m_spDepthEffect )
    {
        m_spDepthEffect->GetAllObjectsByName(rName, rObjects);
    }

    if( m_spDepthImage )
    {
        m_spDepthImage->GetAllObjectsByName(rName, rObjects);
    }

    if( m_spShadowEffect )
    {
        m_spShadowEffect->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
Object* ShadowMapEffect::GetObjectByID(unsigned int uiID)
{
    Object* pFound = Effect::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( m_spProjector )
    {
        pFound = m_spProjector->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spDepthEffect )
    {
        pFound = m_spDepthEffect->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spDepthImage )
    {
        pFound = m_spDepthImage->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( m_spShadowEffect )
    {
        pFound = m_spShadowEffect->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void ShadowMapEffect::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Effect::Load(rStream, pLink);

    // native data
    rStream.Read(m_afDepthBias[0]);

    // link data
    Object* pObject;
    rStream.Read(pObject);  // m_spProjector
    pLink->Add(pObject);
    rStream.Read(pObject);  // m_spDepthEffect
    pLink->Add(pObject);
    rStream.Read(pObject);  // m_spDepthImage
    pLink->Add(pObject);
    rStream.Read(pObject);  // m_spShadowEffect
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(ShadowMapEffect);
}
//----------------------------------------------------------------------------
void ShadowMapEffect::Link(Stream& rStream, Stream::Link* pLink)
{
    Effect::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    m_spProjector = (Camera*)rStream.GetFromMap(pLinkID);
    pLinkID = pLink->GetLinkID();
    m_spDepthEffect = (ShaderEffect*)rStream.GetFromMap(pLinkID);
    pLinkID = pLink->GetLinkID();
    m_spDepthImage = (Image*)rStream.GetFromMap(pLinkID);
    pLinkID = pLink->GetLinkID();
    m_spShadowEffect = (ShaderEffect*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool ShadowMapEffect::Register(Stream& rStream) const
{
    if( !Effect::Register(rStream) )
    {
        return false;
    }

    if( m_spProjector )
    {
        m_spProjector->Register(rStream);
    }

    if( m_spDepthEffect )
    {
        m_spDepthEffect->Register(rStream);
    }

    if( m_spDepthImage )
    {
        m_spDepthImage->Register(rStream);
    }

    if( m_spShadowEffect )
    {
        m_spShadowEffect->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void ShadowMapEffect::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Effect::Save(rStream);

    // native data
    rStream.Write(m_afDepthBias[0]);

    // link data
    rStream.Write(m_spProjector);
    rStream.Write(m_spDepthEffect);
    rStream.Write(m_spDepthImage);
    rStream.Write(m_spShadowEffect);

    SE_END_DEBUG_STREAM_SAVE(ShadowMapEffect);
}
//----------------------------------------------------------------------------
int ShadowMapEffect::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Effect::GetDiskUsed(rVersion) +
        sizeof(m_afDepthBias[0]) +
        sizeof(m_spProjector) +
        sizeof(m_spDepthEffect) +
        sizeof(m_spDepthImage) +
        sizeof(m_spShadowEffect);
}
//----------------------------------------------------------------------------
StringTree* ShadowMapEffect::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(Format("depth bias =", m_afDepthBias[0]));

    // children
    pTree->Append(Effect::SaveStrings());

    if( m_spProjector )
    {
        pTree->Append(m_spProjector->SaveStrings());
    }

    if( m_spDepthEffect )
    {
        pTree->Append(m_spDepthEffect->SaveStrings());
    }

    if( m_spDepthImage )
    {
        pTree->Append(m_spDepthImage->SaveStrings());
    }

    if( m_spShadowEffect )
    {
        pTree->Append(m_spShadowEffect->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
