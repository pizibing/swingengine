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

#include "SEToolsCommonPCH.h"
#include "SEColladaScene.h"

using namespace Swing;

//----------------------------------------------------------------------------
SELight* SEColladaScene::GetLight(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( strcmp(m_Lights[i]->GetName().c_str(), acName) == 0 )
        {
            return m_Lights[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
SELight* SEColladaScene::LoadLight(domLightRef spDomLight)
{
    xsID strLightID = spDomLight->getId();
    if( !strLightID )
    {
        return 0;
    }

    SELight* pLight = GetLight(strLightID);
    if( pLight )
    {
        // This light is already in our light catalog.
        return pLight;
    }

    ToolSystem::DebugOutput("Add new light:%s", (const char*)strLightID);

    domLight* pDomLight = (domLight*)(domLight*)spDomLight;

    if( pDomLight )
    {
        // Get the common technique for this light.
        // TODO:
        // Only support <technique_common> for now.
        domLight::domTechnique_common* pDomTechniqueCommon = 
            pDomLight->getTechnique_common();
        if( !pDomTechniqueCommon ) 
        {
            return 0;
        }

        // Create a Swing Engine light.
        pLight = SE_NEW SELight;
        pLight->SetName((const char*)strLightID);

        // Only one of these light types can be present.
        domLight::domTechnique_common::domAmbient* pDomAmbient = 
            pDomTechniqueCommon->getAmbient();
        domLight::domTechnique_common::domDirectional* pDomDirectional = 
            pDomTechniqueCommon->getDirectional();
        domLight::domTechnique_common::domPoint* pDomPoint = 
            pDomTechniqueCommon->getPoint();
        domLight::domTechnique_common::domSpot* pDomSpot = 
            pDomTechniqueCommon->getSpot();

        if( pDomAmbient )
        {
            pLight->Type = SELight::LT_AMBIENT;
            domFloat3& rDomFloat3 = pDomAmbient->getColor()->getValue();
            pLight->Ambient	= SEColorRGB((float)(rDomFloat3[0]), 
                (float)(rDomFloat3[1]), (float)(rDomFloat3[2]));
        }
        else if( pDomDirectional )
        {
            pLight->Type = SELight::LT_DIRECTIONAL;
            domFloat3& rDomFloat3 = pDomDirectional->getColor()->getValue();
            pLight->Ambient = SEColorRGB((float)(rDomFloat3[0]), 
                (float)(rDomFloat3[1]), (float)(rDomFloat3[2]));
            pLight->Diffuse = pLight->Ambient;
            pLight->Specular = pLight->Ambient;
        }
        else if( pDomPoint )
        {
            pLight->Type = SELight::LT_POINT;
            domFloat3& rDomFloat3 = pDomPoint->getColor()->getValue();
            pLight->Ambient = SEColorRGB((float)(rDomFloat3[0]), 
                (float)(rDomFloat3[1]), (float)(rDomFloat3[2]));
            pLight->Diffuse = pLight->Ambient;
            pLight->Specular = pLight->Ambient;

            if( pDomPoint->getConstant_attenuation() )
            {
                pLight->Constant = 
                    (float)(pDomPoint->getConstant_attenuation()->getValue());
            }
            if( pDomPoint->getLinear_attenuation() )
            {
                pLight->Linear = 
                    (float)(pDomPoint->getLinear_attenuation()->getValue());
            }
            if( pDomPoint->getQuadratic_attenuation() )
            {
                pLight->Quadratic = 
                    (float)(pDomPoint->getQuadratic_attenuation()->getValue());
            }
        }
        else if( pDomSpot )
        {
            pLight->Type = SELight::LT_SPOT;
            domFloat3& rDomFloat3 = pDomSpot->getColor()->getValue();
            pLight->Ambient = SEColorRGB((float)(rDomFloat3[0]), 
                (float)(rDomFloat3[1]), (float)(rDomFloat3[2]));
            pLight->Diffuse = pLight->Ambient;
            pLight->Specular = pLight->Ambient;

            if( pDomSpot->getConstant_attenuation() )
            {
                pLight->Constant = 
                    (float)(pDomSpot->getConstant_attenuation()->getValue());
            }
            if( pDomSpot->getLinear_attenuation() )
            {
                pLight->Linear = 
                    (float)(pDomSpot->getLinear_attenuation()->getValue());
            }
            if( pDomSpot->getQuadratic_attenuation() )
            {
                pLight->Quadratic = 
                    (float)(pDomSpot->getQuadratic_attenuation()->getValue());
            }
            if( pDomSpot->getFalloff_angle() )
            {
                // COLLADA uses degree, Swing Engine uses radians.
                float fAngle = SEMath<float>::DEG_TO_RAD * 
                    (float)(pDomSpot->getFalloff_angle()->getValue());
                pLight->SetAngle(fAngle);
            }
            if( pDomSpot->getFalloff_exponent() )
            {
                pLight->Exponent = 
                    (float)(pDomSpot->getFalloff_exponent()->getValue());
            }
        }

        m_Lights.push_back(pLight);

        return pLight;
    }

    return 0;
}
//----------------------------------------------------------------------------
SEColladaInstanceLight* SEColladaScene::LoadInstanceLight(SENode* pParentNode, 
    domInstance_lightRef spDomInstanceLight)
{
    xsAnyURI& rUrlType  = spDomInstanceLight->getUrl();
    domElement* pDomElement = (domElement*)rUrlType.getElement();
    if( !pDomElement )
    {
        // This instance light is not found, skip to the next one.
        ToolSystem::DebugOutput("Can't find this light:%s", 
            (const char*)rUrlType.getURI());

        return 0;
    }

    SELight* pLight = LoadLight((domLight*)pDomElement);
    if( pLight )
    {
        // We should make a copy of the original light because each
        // instance of that light has its own transformation based on its
        // parent node's transformation.
        SEObjectPtr spObject = pLight->Copy();
        SELight* pNewLight = DynamicCast<SELight>(spObject);
        SE_ASSERT( pNewLight );

        SEColladaInstanceLight* pInstanceLight = 
            SE_NEW SEColladaInstanceLight(pParentNode, pNewLight);

        return pInstanceLight;
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEColladaScene::ProcessLights()
{
    for( int i = 0; i < (int)m_InstanceLights.size(); i++ )
    {
        SELight* pLight = m_InstanceLights[i]->GetLight();
        SENode* pParentNode = m_InstanceLights[i]->GetParentNode();

        pLight->Position = pParentNode->World.GetTranslate();
        if( pLight->Type == SELight::LT_DIRECTIONAL || 
            pLight->Type == SELight::LT_SPOT )
        {
            bool bIsSRMatrix = pParentNode->World.IsSRMatrix();
            SE_ASSERT( bIsSRMatrix );
            if( bIsSRMatrix )
            {
                pParentNode->World.GetRotate().GetRow(0, pLight->RVector);
                pParentNode->World.GetRotate().GetRow(1, pLight->UVector);
                pParentNode->World.GetRotate().GetRow(2, pLight->DVector);
            }
        }
    }
}
//----------------------------------------------------------------------------