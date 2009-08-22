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

#ifndef Swing_OpenALRenderer_H
#define Swing_OpenALRenderer_H

// 待实现.
// 我们暂时没有OpenAL的封装器.
// 因此使用平台SDK提供的OpenAL headers.
#if defined(_WIN32)
#include <al.h>
#include <alc.h>
#elif defined(__APPLE__)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

// 避免al.h中OPENAL宏定义和AudioRenderer::OPENAL枚举值定义冲突造成编译错误.
#if defined(OPENAL)
#undef OPENAL
#define OPENALUNDEFINED
#endif

#include "SEOpenALRendererLIB.h"
#include "SEAudioRenderer.h"
#include "SEMain.h"
#include "SEWave.h"
#include "SEWaveCatalog.h"

//----------------------------------------------------------------------------
#ifdef _DEBUG
#define SE_AL_BEGIN_DEBUG_ALAPI alGetError()
#define SE_AL_END_DEBUG_ALAPI \
{ \
    ALenum tempError = alGetError(); \
    SE_ASSERT( tempError == AL_NO_ERROR ); \
}
#else
#define SE_AL_BEGIN_DEBUG_ALAPI
#define SE_AL_END_DEBUG_ALAPI
#endif
//----------------------------------------------------------------------------

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:OpenAL1.0 Renderer虚基类
// 说明:
// 作者:Sun Che
// 时间:20090623
//----------------------------------------------------------------------------
class SE_AUDIO_RENDERER_API OpenALRenderer : public AudioRenderer
{
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    // RTTI.
    virtual int GetType(void) const { return AudioRenderer::OPENAL; }

    // 虚基类.
    // 在OpenAL context创建后,由派生类构造函数调用InitializeState函数.
    virtual ~OpenALRenderer(void);
    void InitializeState(void);

protected:
    OpenALRenderer(void);

    // listener更新.
    virtual void OnFrameChange(void);
    virtual void OnMasterGainChange(void);

    // 设置声音参数(声音世界空间姿态及其他声音物理参数).
    virtual void SetSoundParams(AudioResourceIdentifier* pID);

    // 声音渲染器派生类渲染函数入口.
    virtual void PlayElements(AudioResourceIdentifier* pID);

    // 声音渲染器派生类停止渲染函数入口.
    virtual void StopElements(AudioResourceIdentifier* pID);

    // 声音渲染器资源装载与释放.
    virtual void OnLoadSound(AudioResourceIdentifier*& rpID, Sound* pSound);
    virtual void OnReleaseSound(AudioResourceIdentifier* pID);
    virtual void OnLoadSBuffer(AudioResourceIdentifier*& rpID,
        SoundBuffer* pSBuffer);
    virtual void OnReleaseSBuffer(AudioResourceIdentifier* pID);

    // 声音渲染器资源开启与关闭.
    virtual void OnEnableSound(AudioResourceIdentifier* pID);
    virtual void OnDisableSound(AudioResourceIdentifier* pID);
    virtual void OnEnableSBuffer(AudioResourceIdentifier* pID);
    virtual void OnDisableSBuffer(AudioResourceIdentifier* pID);
    virtual void OnAttachSBuffer(AudioResourceIdentifier* pSoundID,
        AudioResourceIdentifier* pSBufferID);

    // 声音渲染器资源参数更新.
    virtual void OnUpdateSoundParams(AudioResourceIdentifier* pID);

    // helper function, change sound source's frame.
    void SetSoundFrame(unsigned int uiID, Sound* pSound);

    static WaveCatalog* ms_pWaveCatalog;

    // 引擎层参数常量与OpenAL渲染器层参数常量映射表.
    static ALenum ms_aeWaveType[Wave::WT_COUNT];
};

}

#if defined(OPENALUNDEFINED)
#define OPENAL
#endif

#endif
