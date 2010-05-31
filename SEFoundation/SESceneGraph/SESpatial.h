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

#ifndef Swing_Spatial_H
#define Swing_Spatial_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEAdvancedObject.h"
#include "SEBoundingVolume.h"
#include "SEEffect.h"
#include "SEGlobalState.h"
#include "SETransformation.h"

namespace Swing
{

class SECuller;
class SELight;

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080707
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SESpatial : public SEAdvancedObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类
    virtual ~SESpatial(void);

    // Local和World变换.
    // 某些情况下你也许需要跳过SESpatial::UpdateGS()模块从而直接设置world变换,
    // 此时应设置WorldIsCurrent为true.
    // 比如IK controller和Skin controller都需要这种能力.
    SETransformation Local;
    SETransformation World;
    bool WorldIsCurrent;

    // 世界空间BV.
    // 某些情况下你也许需要跳过SESpatial::UpdateGS()模块从而直接设置世界空间BV,
    // 此时应设置WorldBoundIsCurrent为true.
    SEBoundingVolumePtr WorldBound;
    bool WorldBoundIsCurrent;

    // 注意:
    // SESpatial不需要体现模型空间BV.

    // 剔除模式
    enum CullingMode
    {
        // 根据世界空间BV与世界空间剔除平面,进行动态剔除.
        CULL_DYNAMIC,

        // 强制剔除,如果是一个SENode节点,则其整个子树都将被剔除.
        CULL_ALWAYS,

        // 强制不剔除,如果是一个SENode节点,则其整个子树都不被剔除.
        // 当首次遇到此SENode节点后,bNoCull参数被设置为true,
        // 并传递给GetUnculledSet/OnGetUnculledSet AB递归链,
        // 从而使递归路径上的所有子节点都不会被剔除.
        CULL_NEVER,

        MAX_CULLING_MODE
    };

    CullingMode Culling;

    // Geometric state和Controller更新入口.
    // UpdateGS函数向下计算每个节点的世界变换,向上计算世界BV.
    // UpdateBS函数只向上计算世界BV,当模型数据改变时,只需改变模型BV和世界BV,
    // 无需重新计算空间变换.
    void UpdateGS(double dAppTime = -SEMathd::MAX_REAL,
        bool bInitiator = true);
    void UpdateBS(void);

    // global state
    inline int GetGlobalStateCount(void) const;
    inline SEGlobalState* GetGlobalState(int i) const;
    SEGlobalState* GetGlobalState(SEGlobalState::StateType eType) const;
    void AttachGlobalState(SEGlobalState* pState);
    void DetachGlobalState(SEGlobalState::StateType eType);
    inline void DetachAllGlobalStates(void);

    // light state
    inline int GetLightCount(void) const;
    inline SELight* GetLight(int i) const;
    void AttachLight(SELight* pLight);
    void DetachLight(SELight* pLight);
    inline void DetachAllLights(void);

    // effect state
    inline int GetEffectCount(void) const;
    inline SEEffect* GetEffect(int i) const;
    void AttachEffect(SEEffect* pEffect);
    void DetachEffect(SEEffect* pEffect);
    inline void DetachAllEffects(void);
    inline void SetStartEffect(int i);
    inline int GetStartEffect(void) const;

    // Render state更新入口.
    virtual void UpdateRS(std::vector<SEGlobalState*>* aGStack = 0,
        std::vector<SELight*>* pLStack = 0);

    // 访问父节点.
    inline SESpatial* GetParent(void);

    // Picking system.
    // 每个派生自SESpatial类的子类都可以进一步派生出与其对应的SEPickRecord子类.
    // 在这些SEPickRecord子类中,可加入任何派生类想要的信息,DoPick函数返回时获取.
    // 在DoPick函数返回表示全部相交点的SEPickRecord数组后,
    // 每个SEPickRecord的射线参数t可作为数组排序的key,从而反映出由近到远的相交
    // 顺序.
    //
    // SEPickRecord类本身虽然不具备RTTI能力,
    // 但我们可以从其成员IObject那里间接获取其RTTI信息.
    // 只要我们知道了IObject的具体类型,
    // 则该SEPickRecord可以被动态类型转换为对应的SEPickRecord派生类.
    class SE_FOUNDATION_API SEPickRecord
    {
    public:
        virtual ~SEPickRecord(void);

        // 与射线相交的对象.
        SESmartPointer<SESpatial> IObject;

        // 相交点处,世界射线的参数t值,非负.
        // 即,如果世界射线是P + t*D,则t >= 0.
        float T;

    protected:
        SEPickRecord(SESpatial* pIObject, float fT);
    };

    typedef std::vector<SEPickRecord*> PickArray;

    // 射线的原点和方向向量都必须在世界坐标系下.
    // 应用程序不能释放PickArray中的所有pick record,
    // 因为这些pick record来自于全局内存池的堆内存.
    virtual void DoPick(const SERay3f& rRay, PickArray& rResults);

    static SEPickRecord* GetClosest(PickArray& rResults);

protected:
    SESpatial(void);

    // 几何数据更新.
    // 派生类SENode实现向下进行AB递归.
    // 向上计算世界空间BV,派生类实现具体行为.
    virtual void UpdateWorldData(double dAppTime);
    virtual void UpdateWorldBound(void) = 0;
    void PropagateBoundToRoot(void);

    // 渲染状态更新.
    void PropagateStateFromRoot(std::vector<SEGlobalState*>* aGStack,
        std::vector<SELight*>* pLStack);
    void PushState(std::vector<SEGlobalState*>* aGStack,
        std::vector<SELight*>* pLStack);
    void PopState(std::vector<SEGlobalState*>* aGStack,
        std::vector<SELight*>* pLStack);
    // 派生类SENode实现向下进行AB递归,
    // 派生类SEGeometry实现收集最终渲染状态.
    virtual void UpdateState(std::vector<SEGlobalState*>* aGStack,
        std::vector<SELight*>* pLStack) = 0;

    SESpatial* m_pParent;

    // 全局渲染状态数组.
    std::vector<SEGlobalStatePtr> m_GlobalStates;

    // 灯光数组.
    // 使用SEObjectPtr避免头文件互相包含依赖.
    std::vector<SEObjectPtr> m_Lights;

    // effect数组.
    // 赋予SEGeometry对象时,单独作用于该对象,
    // 赋予SENode对象时,作用于该SENode子树所有SEGeometry对象.
    std::vector<SEEffectPtr> m_Effects;

    // 通常情况下,所有依附于对象的effect都将被应用于该对象.
    // 但有时为了屏蔽一些effect,我们需要一个起始索引值供应用程序使用,
    // 对于复杂的effect效果,这将会非常有用,能够忽略掉当前的这些effect,
    // 只使用某个特定effect渲染对象.
    // 如果没有这个起始索引值,就必须移除当前所有effect并暂时保存,
    // 然后添加特定effect并渲染,之后移除特定effect,最后再次恢复之前的所有effect.
    // 通过起始索引值,就可以添加特定effect到effect队列末尾,
    // 然后指定该位置为起始应用位置,渲染后,重置起始位置为0,并移除该特定effect.
    int m_iStartEffect;

private:
    static const char* ms_aacCullingMode[MAX_CULLING_MODE];

// 内部使用
public:
    inline void SetParent(SESpatial* pParent);

    // 剔除系统的AB递归函数.
    void OnGetUnculledSet(SECuller& rCuller, bool bNoCull);
    virtual void GetUnculledSet(SECuller& rCuller, bool bNoCull) = 0;
};

typedef SESmartPointer<SESpatial> SESpatialPtr;

#include "SESpatial.inl"

}

#endif
