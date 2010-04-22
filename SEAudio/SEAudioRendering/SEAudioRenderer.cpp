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

#include "SEAudioPCH.h"
#include "SEAudioRenderer.h"
#include "SEListener.h"
#include "SESound.h"
#include "SENode.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEAudioRenderer::SEAudioRenderer()
{
    // 派生类应该检测并设置设备能力.
    m_pListener = 0;
    m_pSound = 0;
}
//----------------------------------------------------------------------------
SEAudioRenderer::~SEAudioRenderer()
{
    SetListener(0);
}
//----------------------------------------------------------------------------
void SEAudioRenderer::SetListener(SEListener* pListener)
{
    if( m_pListener )
    {
        m_pListener->m_pAudioRenderer = 0;
    }

    if( pListener )
    {
        pListener->m_pAudioRenderer = this;
    }

    m_pListener = pListener;

    if( m_pListener )
    {
        OnFrameChange();
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::OnPrePlaySound()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
void SEAudioRenderer::OnPostPlaySound()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 装载与释放资源
//----------------------------------------------------------------------------
void SEAudioRenderer::LoadAllResources(SESpatial* pScene)
{
    SESound* pSound = DynamicCast<SESound>(pScene);
    if( pSound )
    {
        LoadResources(pSound);
    }

    SENode* pNode = DynamicCast<SENode>(pScene);
    if( pNode )
    {
        for( int i = 0; i < pNode->GetCount(); i++ )
        {
            SESpatial* pChild = pNode->GetChild(i);
            if( pChild )
            {
                LoadAllResources(pChild);
            }
        }
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::ReleaseAllResources(SESpatial* pScene)
{
    SESound* pSound = DynamicCast<SESound>(pScene);
    if( pSound )
    {
        ReleaseResources(pSound);
    }

    SENode* pNode = DynamicCast<SENode>(pScene);
    if( pNode )
    {
        for( int i = 0; i < pNode->GetCount(); i++ )
        {
            SESpatial* pChild = pNode->GetChild(i);
            if( pChild )
            {
                ReleaseAllResources(pChild);
            }
        }
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::LoadResources(SESound* pSound)
{
    SE_ASSERT( pSound );

    // 把sound装入音频设备.
    LoadSound(pSound);
}
//----------------------------------------------------------------------------
void SEAudioRenderer::ReleaseResources(SESound* pSound)
{
    SE_ASSERT( pSound );

    // 从音频设备释放sound.
    ReleaseSound(pSound);
}
//----------------------------------------------------------------------------
void SEAudioRenderer::LoadSound(SESound* pSound)
{
    if( !pSound )
    {
        return;
    }

    SEAudioResourceIdentifier* pSoundID = pSound->GetIdentifier(this);
    if( !pSoundID )
    {
        OnLoadSound(pSoundID, pSound);
        pSound->OnLoad(this, &SEAudioRenderer::ReleaseSound,
            &SEAudioRenderer::UpdateSoundParams, pSoundID);

        if( pSound->SBuffer )
        {
            LoadSBuffer(pSound->SBuffer);
            SEAudioResourceIdentifier* pSBufferID = 
                pSound->SBuffer->GetIdentifier(this);

            OnAttachSBuffer(pSoundID, pSBufferID);
        }
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::ReleaseSound(SEAudioBindable* pSound)
{
    if( !pSound )
    {
        return;
    }

    SEAudioResourceIdentifier* pID = pSound->GetIdentifier(this);
    if( pID )
    {
        OnReleaseSound(pID);
        pSound->OnRelease(this, pID);
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::LoadSBuffer(SESoundBuffer* pSBuffer)
{
    if( !pSBuffer )
    {
        return;
    }

    SEAudioResourceIdentifier* pID = pSBuffer->GetIdentifier(this);
    if( !pID )
    {
        OnLoadSBuffer(pID, pSBuffer);
        pSBuffer->OnLoad(this, &SEAudioRenderer::ReleaseSBuffer, 0, pID);
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::ReleaseSBuffer(SEAudioBindable* pSBuffer)
{
    if( !pSBuffer )
    {
        return;
    }

    SEAudioResourceIdentifier* pID = pSBuffer->GetIdentifier(this);
    if( pID )
    {
        OnReleaseSBuffer(pID);
        pSBuffer->OnRelease(this, pID);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 资源参数更新
//----------------------------------------------------------------------------
void SEAudioRenderer::UpdateSoundParams(SEAudioBindable* pSound)
{
    if( !pSound )
    {
        return;
    }

    SEAudioResourceIdentifier* pID = pSound->GetIdentifier(this);
    if( pID )
    {
        OnUpdateSoundParams(pID);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 资源开启与关闭
//----------------------------------------------------------------------------
SEAudioResourceIdentifier* SEAudioRenderer::EnableSound()
{
    // 确保sound及其sound buffer装载入音频设备.
    LoadSound(m_pSound);
    SEAudioResourceIdentifier* pID = m_pSound->GetIdentifier(this);
    SE_ASSERT( pID );

    OnEnableSound(pID);
    return pID;
}
//----------------------------------------------------------------------------
void SEAudioRenderer::DisableSound()
{
    SEAudioResourceIdentifier* pID = m_pSound->GetIdentifier(this);
    SE_ASSERT( pID );

    OnDisableSound(pID);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 对象渲染入口
//----------------------------------------------------------------------------
void SEAudioRenderer::PlayScene(SEUnculledSet& rAudibleSet)
{
    const int iAudibleCount = rAudibleSet.GetCount();
    SEUnculledObject* pAudibleSet = rAudibleSet.GetUnculled();
    for( int i = 0; i < iAudibleCount; i++ )
    {
        if( pAudibleSet[i].IsRenderable() )
        {
            Play((SESound*)pAudibleSet[i].Object);
        }
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::Play(SESound* pSound)
{
    SE_ASSERT( pSound );

    // 引用当前可渲染对象,供其它函数使用.
    m_pSound = pSound;

    // per-sound pre-play,声音渲染器派生类自定义行为入口.
    OnPrePlaySound();

    // 开启当前可渲染对象的sound,并为其装载sound buffer.
    SEAudioResourceIdentifier* pID = EnableSound();

    // 更新声音参数.
    SetSoundParams(pID);

    // 渲染.
    PlayElements(pID);

    // 关闭当前可渲染对象的sound.
    DisableSound();

    // per-sound post-play,声音渲染器派生类自定义行为入口.
    OnPostPlaySound();

    // 渲染完毕,解除引用当前可渲染对象.
    m_pSound = 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 对象停止渲染入口
//----------------------------------------------------------------------------
void SEAudioRenderer::StopScene(SEUnculledSet& rAudibleSet)
{
    const int iAudibleCount = rAudibleSet.GetCount();
    SEUnculledObject* pAudibleSet = rAudibleSet.GetUnculled();
    for( int i = 0; i < iAudibleCount; i++ )
    {
        if( pAudibleSet[i].IsRenderable() )
        {
            Stop((SESound*)pAudibleSet[i].Object);
        }
    }
}
//----------------------------------------------------------------------------
void SEAudioRenderer::Stop(SESound* pSound)
{
    SE_ASSERT( pSound );

    SEAudioResourceIdentifier* pID = pSound->GetIdentifier(this);
    if( pID )
    {
        // 停止渲染.
        StopElements(pID);
    }
}
//----------------------------------------------------------------------------