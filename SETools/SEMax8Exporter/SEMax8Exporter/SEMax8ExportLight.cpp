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

#include "SEMax8SceneBuilder.h"
#include "decomp.h"

//----------------------------------------------------------------------------
void Max8SceneBuilder::BuildAmbientLight()
{
    // 获取Max全局环境光设置信息,并建立相应的Swing Engine灯光.
    Color tempColor = m_pMax->GetAmbient(0, FOREVER);
    Swing::Light* pSELight = new Swing::Light(Swing::Light::LT_AMBIENT);
    pSELight->Ambient = Swing::ColorRGB(tempColor.r, tempColor.g, tempColor.b);
    m_spSEScene->AttachLight(pSELight);
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::BuildLight(INode* pMaxNode, Swing::Spatial* pSENode)
{
    // 根据一个Max层级中的light创建Swing Engine的light.
    // 支持Max的omnidirectional,directional,free spot这三种light.
    // 注意Max中采用把受到light影响的node赋给light,
    // 而Swing Engine中采用把影响node的light赋给node,node具有一个list of lights.
    // 这里使用的方法是,把Swing Engine lights赋给Swing Engine node,
    // 该node代表Max场景中light node的父节点.
    //
    // pMaxNode:
    //     代表light的Max node.
    // pSENode:
    //     要被赋予Max light state的Swing Engine node.

    // 从Max获取light参数.
    ObjectState tempObjectState = pMaxNode->EvalWorldState(m_iTimeStart);
    GenLight* pGenLight = (GenLight*)tempObjectState.obj;
    LightState tempMaxLightState;
    Interval tempValid = FOREVER;
    pGenLight->EvalLightState(m_iTimeStart, tempValid, &tempMaxLightState);

    Swing::Light* pSELight = NULL;

    switch( pGenLight->Type() ) 
    {
    case OMNI_LIGHT:
        pSELight = BuildPointLight(pMaxNode);

        break;
    case TSPOT_LIGHT:
    case FSPOT_LIGHT:
        pSELight = BuildSpotLight(pMaxNode, tempMaxLightState);

        break;
    case TDIR_LIGHT:
    case DIR_LIGHT:
        pSELight = BuildDirectionalLight(pMaxNode);

        break;
    default: // 不支持的light类型
        assert( false );

        return;
    }
    
    pSELight->Intensity = tempMaxLightState.intens;
    
    // Max lights好像只带有一个颜色.
    // 让Swing Engine lights的specular,diffuse都用这个颜色.
    if( tempMaxLightState.affectDiffuse )
    {
        pSELight->Diffuse = Swing::ColorRGB(tempMaxLightState.color.r,
            tempMaxLightState.color.g, tempMaxLightState.color.b);
    }
    if( tempMaxLightState.affectSpecular )
    {
        pSELight->Specular = Swing::ColorRGB(tempMaxLightState.color.r,
            tempMaxLightState.color.g, tempMaxLightState.color.b);
    }
    
    // 设置attenuation参数.
    // Max的光照衰减公式比Swing Engine的简单,
    // 表现为Max的光照衰减公式只允许constant,linear,quadratic之一发挥作用,
    // 而不允许三者共同发挥作用.
    if( pGenLight->GetDecayType() != 0 )
    {
        Interval tempValid;
        float fDecayRadius = pGenLight->GetDecayRadius(m_iTimeStart, tempValid);
        
        switch( pGenLight->GetDecayType() )
        {
        case 0:
            pSELight->Constant = ATTENUATION;
            pSELight->Linear = 0.0f;
            pSELight->Quadratic = 0.0f;

            break;
        case 1:
            pSELight->Constant = 0.0f;
            pSELight->Linear = ATTENUATION / fDecayRadius;
            pSELight->Quadratic = 0.0f;

            break;
        case 2:
            pSELight->Constant = 0.0f;
            pSELight->Linear = 0.0f;
            pSELight->Quadratic = ATTENUATION / (fDecayRadius*fDecayRadius);

            break;
        } 
    }
    else if( pGenLight->GetUseAtten() )
    {
        float fFarAtten = tempMaxLightState.attenEnd;             
        pSELight->Constant = 0.0f;
        pSELight->Linear = ATTENUATION / fFarAtten;
        pSELight->Quadratic = 0.0f;
    }

    pSENode->AttachLight(pSELight);
}
//----------------------------------------------------------------------------
Swing::Vector3f Max8SceneBuilder::GetLightLocation(INode* pNode)
{
    // 计算node的local变换.
    Matrix3 tempLocal = pNode->GetNodeTM(m_iTimeStart) *
        Inverse(pNode->GetParentTM(m_iTimeStart));

    // 把local变换分解出仿射变换分量.
    AffineParts tempAffParts;
    decomp_affine(tempLocal, &tempAffParts);

    // 获取平移变换分量.
    return Swing::Vector3f(tempAffParts.t.x, tempAffParts.t.y, tempAffParts.t.z);
}
//----------------------------------------------------------------------------
Swing::Light* Max8SceneBuilder::BuildPointLight(INode* pNode)
{
    Swing::Light* pSELight = new Swing::Light(Swing::Light::LT_POINT);

    // 设置light的位置.
    pSELight->Position = GetLightLocation(pNode);
    
    return pSELight;
}
//----------------------------------------------------------------------------
Swing::Light* Max8SceneBuilder::BuildSpotLight(INode* pNode, LightState& rLightState)
{
    Swing::Light* pSELight = new Swing::Light(Swing::Light::LT_SPOT);

    // 设置light的位置和方向向量.
    pSELight->Position = GetLightLocation(pNode);
    pSELight->SetDirection(Swing::Vector3f::UNIT_Z);

    // 设置light的angle.
    pSELight->Angle = HALFPI * rLightState.fallsize / 180.0f;

    // 设置light的exponent.
    pSELight->Exponent = 128.0f * ((rLightState.fallsize -
        rLightState.hotsize) / rLightState.fallsize);
    
    return pSELight;
}
//----------------------------------------------------------------------------
Swing::Light* Max8SceneBuilder::BuildDirectionalLight(INode* pNode)
{
    Swing::Light* pSELight = new Swing::Light(Swing::Light::LT_DIRECTIONAL);

    // 设置light的方向向量.
    pSELight->SetDirection(Swing::Vector3f::UNIT_Z);

    return pSELight;
}
//----------------------------------------------------------------------------



