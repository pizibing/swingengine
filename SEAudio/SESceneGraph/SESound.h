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

#ifndef Swing_Sound_H
#define Swing_Sound_H

#include "SEAudioLIB.h"
#include "SESpatial.h"
#include "SESoundBuffer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:场景视图声音节点基类
// 说明:
// 作者:Sun Che
// 时间:20090618
//----------------------------------------------------------------------------
class SE_AUDIO_API Sound : public Spatial, public AudioBindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

    // 注意:
    // Sound节点用于表示3D空间中的发声音源.
    // Sound节点存储与该音源相关的所需音源物理参数,
    // Sound类及其派生类型只能作为场景视图树的叶子节点.
    // 节点的世界变换体现了音源的空间定位姿态.
    // 用户有责任确保节点的空间变换不包含非统一缩放变换.
    // 节点的模型/世界空间BV是一个半径为0的质点.
    // 根据音源的物理性质,我们不应该使用view frustum来对Sound节点进行可视剔除,
    // 而应该根据其相对于空间中Listener对象的空间姿态,距离,以及指向性进行剔除,
    // 目前由音频管线API来完成此工作.因此Sound节点的Culling应设置为CULL_NEVER,
    // 从而确保其不被引擎图形管线的view frustum剔除.
    //
    // 当使用PCM wave作为音源数据时,只有WT_MONO*格式支持3D空间声音定位.
    // 其他多声道格式都无法产生用户所期望的基于Sound节点对象和Listener对象的
    // 空间声音定位.
    //
    // 目前我们假设音源为静态音源,即:
    // 不包含音源运动方向及速度大小的描述以及多普勒参数,从而忽略多普勒效应.
    // 关于多普勒效应:
    // The Doppler effect (or Doppler shift), named after Austrian physicist
    // Christian Doppler who proposed it in 1842, is the change in frequency
    // of a wave for an observer moving relative to the source of the waves.
    // It is commonly heard when a vehicle sounding a siren approaches, passes
    // and recedes from an observer. The received frequency is increased
    // (compared to the emitted frequency) during the approach, it is identical
    // at the instant of passing by, and it is decreased during the recession.
    // For waves that propagate in a medium, such as sound waves, the velocity
    // of the observer and of the source are relative to the medium in which the
    // waves are transmitted. The total Doppler effect may therefore result from
    // motion of the source, motion of the observer, or motion of the medium.
    // Each of these effects is analyzed separately. For waves which do not
    // require a medium, such as light or gravity in special relativity, only
    // the relative difference in velocity between the observer and the source
    // needs to be considered.
    // from: http://en.wikipedia.org/wiki/Doppler_effect

public:
    Sound(SoundBuffer* pSBuffer);
    virtual ~Sound(void);

    // 成员访问.
    SoundBufferPtr SBuffer;
    BoundingVolumePtr ModelBound;

    // 声音参数.
    float Pitch;        // default: 1.0f
    float Gain;         // default: 1.0f
    float RollOffRate;  // default: 1.0f
    bool Looping;       // default: false

    // Picking support.
    // 这个类仅仅用于维护类派生链的完整性.
    class SE_AUDIO_API PickRecord : public Spatial::PickRecord
    {
    protected:
        PickRecord(Sound* pIObject, float fT);
    };

protected:
    Sound(void);

    // 世界空间数据及相关音频参数更新.
    virtual void UpdateWorldData(double dAppTime);
    virtual void UpdateWorldBound(void);

    // 渲染状态更新,实现基类接口.
    // 对于Sound类,这是一个空函数,
    // 因为Sound对象收集几何管线的渲染状态是毫无意义的.
    virtual void UpdateState(std::vector<GlobalState*>* aGStack,
        std::vector<Light*>* pLStack);

    // 支持剔除系统,收集可渲染对象.
    virtual void GetUnculledSet(Culler& rCuller, bool bNoCull);
};

typedef SESmartPointer<Sound> SoundPtr;

}

#endif
