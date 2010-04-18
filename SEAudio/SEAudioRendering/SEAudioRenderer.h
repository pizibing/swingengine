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

#ifndef Swing_AudioRenderer_H
#define Swing_AudioRenderer_H

#include "SEAudioLIB.h"
#include "SEMatrix4.h"

namespace Swing
{

class SEAudioBindable;
class SEAudioResourceIdentifier;
class SEListener;
class SESound;
class SESoundBuffer;
class SESpatial;
class SEUnculledObject;
class SEUnculledSet;

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20090619
//----------------------------------------------------------------------------
class SE_AUDIO_API SEAudioRenderer
{
public:
    // 虚基类.
    // 声音渲染器抽象API.所有声音管线API都要实现这层.
    virtual ~SEAudioRenderer(void);

    // RTTI信息.
    enum
    {
        OPENAL,
        DIRECTSOUND,
        MAX_AUDIORENDERER_TYPES
    };
    virtual int GetType(void) const = 0; // 由声音渲染器派生类实现

    // listener访问.
    void SetListener(SEListener* pListener);
    inline SEListener* GetListener(void) const;

    // 对象渲染入口.
    virtual void PlayScene(SEUnculledSet& rAudibleSet);
    virtual void Play(SESound* pSound);

    // 对象停止渲染入口.
    virtual void StopScene(SEUnculledSet& rAudibleSet);
    virtual void Stop(SESound* pSound);

    // 待实现.
    // 声音渲染器能力限制检测.

    // 声音渲染器绑定资源释放函数的函数指针类型.
    typedef void (SEAudioRenderer::*ReleaseFunction)(SEAudioBindable*);
    // 声音渲染器绑定资源参数更新回调函数的函数指针类型.
    typedef void (SEAudioRenderer::*UpdateParamsFunction)(SEAudioBindable*);

    // 声音渲染器资源装载与释放.
    void LoadAllResources(SESpatial* pScene);
    void ReleaseAllResources(SESpatial* pScene);
    void LoadResources(SESound* pSound);
    void ReleaseResources(SESound* pSound);
    void LoadSound(SESound* pSound);
    void ReleaseSound(SEAudioBindable* pSound);
    void LoadSBuffer(SESoundBuffer* pSBuffer);
    void ReleaseSBuffer(SEAudioBindable* pSBuffer);

    // 声音渲染器资源参数更新.
    void UpdateSoundParams(SEAudioBindable* pSound);

protected:
    // 虚基类
    SEAudioRenderer(void);

    // 支持listener访问和相关更新操作.
    // 当listener相关数据改变时,调用这些回调函数.
    friend class SEListener;
    virtual void OnFrameChange(void) = 0;       // {E:R,U,D}改变
    virtual void OnMasterGainChange(void) = 0;  // master gain改变.

    // per-sound pre/post-play函数入口.
    virtual void OnPrePlaySound(void);
    virtual void OnPostPlaySound(void);

    // 设置声音参数(声音世界空间姿态及其他声音物理参数).
    virtual void SetSoundParams(SEAudioResourceIdentifier* pID) = 0;

    // 声音渲染器派生类渲染函数入口.
    virtual void PlayElements(SEAudioResourceIdentifier* pID) = 0;

    // 声音渲染器派生类停止渲染函数入口.
    virtual void StopElements(SEAudioResourceIdentifier* pID) = 0;

    // 声音渲染器资源装载与释放.
    // 需要具体音频API负责实现.
    virtual void OnLoadSound(SEAudioResourceIdentifier*& rpID,
        SESound* pSound) = 0;
    virtual void OnReleaseSound(SEAudioResourceIdentifier* pID) = 0;
    virtual void OnLoadSBuffer(SEAudioResourceIdentifier*& rpID,
        SESoundBuffer* pSBuffer) = 0;
    virtual void OnReleaseSBuffer(SEAudioResourceIdentifier* pID) = 0;

    // 声音渲染器资源开启与关闭入口.
    SEAudioResourceIdentifier* EnableSound(void);
    void DisableSound(void);

    // 声音渲染器资源开启与关闭.
    // 需要具体音频API负责实现.
    virtual void OnEnableSound(SEAudioResourceIdentifier* pID) = 0;
    virtual void OnDisableSound(SEAudioResourceIdentifier* pID) = 0;
    virtual void OnEnableSBuffer(SEAudioResourceIdentifier* pID) = 0;
    virtual void OnDisableSBuffer(SEAudioResourceIdentifier* pID) = 0;
    virtual void OnAttachSBuffer(SEAudioResourceIdentifier* pSoundID,
        SEAudioResourceIdentifier* pSBufferID) = 0;

    // 声音渲染器资源参数更新.
    // 需要具体音频API负责实现.
    virtual void OnUpdateSoundParams(SEAudioResourceIdentifier* pID) = 0;

// 数据成员:
protected:
    // 待实现.
    // 资源限制,声音渲染器派生类负责设置.

    // 当前listener.
    SEListener* m_pListener;

    // 当前正在渲染的声音对象.
    SESound* m_pSound;
};

#include "SEAudioRenderer.inl"

}

#endif
