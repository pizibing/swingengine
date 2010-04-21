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
SEColladaEffect* SEColladaScene::GetEffect(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Effects.size(); i++ )
    {
        if( strcmp(m_Effects[i]->GetName().c_str(), acName) == 0 )
        {
            return m_Effects[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
bool SEColladaScene::LoadEffectLibrary(domLibrary_effectsRef spLib)
{
    ToolSystem::SE_DebugOutput("SEColladaScene::Loading SEEffect Library" );

    int iEffectCount = (int)spLib->getEffect_array().getCount();
    for( int i = 0; i < iEffectCount; i++ )
    {
        LoadEffect(spLib->getEffect_array()[i]);
    }

    return true;
}
//----------------------------------------------------------------------------
SEColladaEffect* SEColladaScene::LoadEffect(domEffectRef spDomEffect)
{
    if( !spDomEffect )
    {
        return 0;
    }

    xsID strEffectID = spDomEffect->getId();
    if( !strEffectID )
    {
        return 0;
    }

    SEColladaEffect* pEffect = GetEffect((const char*)strEffectID);
    if( pEffect )
    {
        // This effect is already in our effect catalog.
        return pEffect;
    }

    ToolSystem::SE_DebugOutput("Add new effect %s", strEffectID);
    
    domEffect* pDomEffect = (domEffect*)spDomEffect;
    if( pDomEffect )
    {
        // CAUTION 1: effect element could have images.
        // Get all images in effect.
        int iEffectImageCount = (int)pDomEffect->getImage_array().getCount();
        for( int i = 0; i < iEffectImageCount; i++ )
        {
            LoadImage(pDomEffect->getImage_array()[i]);
        }

        // Create our effect base on COLLADA effect.
        pEffect = SE_NEW SEColladaEffect;
        pEffect->SetName(strEffectID);

        // How many profiles are there?
        int iProfileCount = 
            (int)pDomEffect->getFx_profile_abstract_array().getCount(); 

        // Just scan the profiles to find the profile_COMMON for now.
        for( int i = 0; i < iProfileCount; i++ )
        {
            domFx_profile_abstract* pDomProfile = 
                pDomEffect->getFx_profile_abstract_array()[i];
            char* acTypeName = (char*)pDomProfile->getTypeName();

            if( strcmp("profile_COMMON", acTypeName) == 0 )
            {
                // Found the common profile, get the technique from it as well.
                domProfile_COMMON* pDomProfileCommon = 
                    (domProfile_COMMON*)pDomProfile;

                // CAUTION 2: profile element could have images.
                // Get all images in profile_COMMON.
                int iProfileImageCount = 
                    (int)pDomProfileCommon->getImage_array().getCount();
                for( int j = 0; j < iProfileImageCount; j++ )
                {
                    LoadImage(pDomProfileCommon->getImage_array()[j]);
                }

                domProfile_COMMON::domTechnique* pDomTechnique = 
                    pDomProfileCommon->getTechnique(); 
                if( !pDomTechnique )
                {
                    break;
                }

                // CAUTION 3: technique element could have images.
                // Get all images in profile_COMMON's technique.
                int iTechniqueImageCount = 
                    (int)pDomTechnique->getImage_array().getCount();
                for( int j = 0; j < iTechniqueImageCount; j++ )
                {
                    LoadImage(pDomTechnique->getImage_array()[j]);
                }				

                // This support is really basic, since the shader models don't 
                // descend from a common type.
                // We have to handle each one individually. There can only be 
                // one lighting model in the technique.
                // All of them assume the texture is in the diffuse component 
                // for now.

                SEColladaShaderElements tempShaderElements;
                domProfile_COMMON::domTechnique::domConstant* pDomConstant = 
                    pDomTechnique->getConstant();
                if( pDomConstant )
                {
                    ParseConstant(pEffect, &tempShaderElements, pDomConstant);
                }
                domProfile_COMMON::domTechnique::domLambert* pDomLambert = 
                    pDomTechnique->getLambert();
                if( pDomLambert )
                {
                    ParseLambert(pEffect, &tempShaderElements, pDomLambert);
                }
                domProfile_COMMON::domTechnique::domPhong* pDomPhong = 
                    pDomTechnique->getPhong();
                if( pDomPhong )
                {
                    ParsePhong(pEffect, &tempShaderElements, pDomPhong);
                }
                domProfile_COMMON::domTechnique::domBlinn* pDomBlinn = 
                    pDomTechnique->getBlinn();
                if( pDomBlinn )
                {
                    ParseBlinn(pEffect, &tempShaderElements, pDomBlinn);
                }

                // Hash the newparam elements of the profile for later use.
                domCommon_newparam_type_Array& rDomNewparamArray = 
                    pDomProfileCommon->getNewparam_array();
                std::map<std::string, domCommon_newparam_type*> tempNewParams;
                int iNewParamCount = (int)rDomNewparamArray.getCount();
                for( int j = 0; j < iNewParamCount; j++ )
                {
                    xsNCName strNewParamSID = rDomNewparamArray[j]->getSid();
                    tempNewParams[strNewParamSID] = rDomNewparamArray[j];
                }
                
                // TODO: 
                // Take only the texture from diffuse for now.
                SETexture* pTexture = GetTextureFromShaderElement(
                    tempNewParams, tempShaderElements.Diffuse);
                if( pTexture )
                {
                    pEffect->Textures.push_back(pTexture);
                }
                
                // Handle an effect with no texture.
                m_Effects.push_back(pEffect);

                return pEffect;
            } 
            else 
            {
                ToolSystem::SE_DebugOutput("%s is not supported yet", 
                    acTypeName);
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
float SEColladaScene::GetFloat(domCommon_float_or_param_type* pParam)
{
    if( pParam->getFloat() )
    {
        return (float)pParam->getFloat()->getValue();
    }

    return 0.0f;
}
//----------------------------------------------------------------------------
SEColorRGB SEColladaScene::GetColor(
    domCommon_color_or_texture_type_complexType* pParam)
{
    if( pParam->getColor() )
    {
        domFx_color_common& rDomColor = pParam->getColor()->getValue();

        return SEColorRGB((float)rDomColor[0], (float)rDomColor[1], 
            (float)rDomColor[2]);
    }

    return SEColorRGB::SE_RGB_BLACK;
}
//----------------------------------------------------------------------------
SETexture* SEColladaScene::GetTextureFromShaderElement(
    std::map<std::string, domCommon_newparam_type*>& rNewParams, 
    domCommon_color_or_texture_type* pShaderElement)
{
    if( !pShaderElement )
    {
        return 0;
    }

    domCommon_color_or_texture_type::domTexture* pDomTextureElement = 
        pShaderElement->getTexture();
    if( !pDomTextureElement )
    {
        return 0;
    }

    // If we can not find the newparam of sampler from our hash map,
    // then we try to solve it by using DAE runtime helper functions.
    std::string strSamplerSID = pDomTextureElement->getTexture();
    domCommon_newparam_type* pDomNewParam = rNewParams[strSamplerSID];
    if( !pDomNewParam )
    {
        xsIDREF tempIDRef(strSamplerSID.c_str());
        tempIDRef.setContainer(pShaderElement);
        tempIDRef.resolveElement();
        domImage* pDomImage = (domImage*)tempIDRef.getElement();

        SEImage* pImage = LoadImage(pDomImage);
        SE_ASSERT( pImage );
        SETexture* pTexture = SE_NEW SETexture(pImage);

        return pTexture;
    }

    std::string strSurfaceSID = 
        pDomNewParam->getSampler2D()->getSource()->getValue();

    pDomNewParam = rNewParams[strSurfaceSID];
    domFx_surface_init_common* pDomSurfaceInit = 
        pDomNewParam->getSurface()->getFx_surface_init_common();
    if( !pDomSurfaceInit )
    {
        return 0;
    }

    xsIDREF& rIDRef = pDomSurfaceInit->getInit_from_array()[0]->getValue();
    rIDRef.resolveElement();
    domImage* pDomImage = (domImage*)rIDRef.getElement();

    SEImage* pImage = LoadImage(pDomImage);
    SE_ASSERT( pImage );
    SETexture* pTexture = SE_NEW SETexture(pImage);

    return pTexture;
}
//----------------------------------------------------------------------------
void SEColladaScene::ParseConstant(SEColladaEffect* pEffect, 
    SEColladaShaderElements* pShaderElements,
    domProfile_COMMON::domTechnique::domConstant* pDomConstant)
{
    pShaderElements->Emission = pDomConstant->getEmission();
    if( pShaderElements->Emission )
    {
        pEffect->Material->Emissive = GetColor(pShaderElements->Emission);
    }

    pShaderElements->Reflective = pDomConstant->getReflective();
    if( pShaderElements->Reflective )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflective = 
        //     GetColor(pShaderElements->Reflective);
    }

    pShaderElements->Reflectivity = pDomConstant->getReflectivity();
    if( pShaderElements->Reflectivity )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflectivity = 
        //     GetFloat(pShaderElements->Reflectivity);
    }

    pShaderElements->Transparent = pDomConstant->getTransparent();
    if( pShaderElements->Transparent ) 
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Transparent = GetColor(pShaderElements->Transparent);
    }

    pShaderElements->Transarency = pDomConstant->getTransparency();
    if( pShaderElements->Transarency )
    {
        pEffect->Material->Alpha = GetFloat(pShaderElements->Transarency);
    }

    pShaderElements->IndexOfRefaction = pDomConstant->getIndex_of_refraction();
    if( pShaderElements->IndexOfRefaction )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->RefractiveIndex = 
        //     GetFloat(pShaderElements->IndexOfRefaction);
    }
}
//----------------------------------------------------------------------------
void SEColladaScene::ParseLambert(SEColladaEffect* pEffect, 
    SEColladaShaderElements* pShaderElements,
    domProfile_COMMON::domTechnique::domLambert* pDomLambert)
{
    pShaderElements->Emission = pDomLambert->getEmission();
    if( pShaderElements->Emission )
    {
        pEffect->Material->Emissive = GetColor(pShaderElements->Emission);
    }

    pShaderElements->Ambient = pDomLambert->getAmbient();
    if( pShaderElements->Ambient )
    {
        pEffect->Material->Ambient = GetColor(pShaderElements->Ambient);
    }

    pShaderElements->Diffuse = pDomLambert->getDiffuse();
    if( pShaderElements->Diffuse )
    {
        pEffect->Material->Diffuse = GetColor(pShaderElements->Diffuse);
    }

    pShaderElements->Reflective = pDomLambert->getReflective();
    if( pShaderElements->Reflective )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflective = 
        //     GetColor(pShaderElements->Reflective);
    }

    pShaderElements->Reflectivity = pDomLambert->getReflectivity();
    if( pShaderElements->Reflectivity )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflectivity = 
        //     GetFloat(pShaderElements->Reflectivity);
    }

    pShaderElements->Transparent = pDomLambert->getTransparent();
    if( pShaderElements->Transparent ) 
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Transparent = GetColor(pShaderElements->Transparent);
    }

    pShaderElements->Transarency = pDomLambert->getTransparency();
    if( pShaderElements->Transarency )
    {
        pEffect->Material->Alpha = GetFloat(pShaderElements->Transarency);
    }

    pShaderElements->IndexOfRefaction = pDomLambert->getIndex_of_refraction();
    if( pShaderElements->IndexOfRefaction )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->RefractiveIndex = 
        //     GetFloat(pShaderElements->IndexOfRefaction);
    }
}
//----------------------------------------------------------------------------
void SEColladaScene::ParsePhong(SEColladaEffect* pEffect, 
    SEColladaShaderElements* pShaderElements,
    domProfile_COMMON::domTechnique::domPhong* pDomPhong)
{
    pShaderElements->Emission = pDomPhong->getEmission();
    if( pShaderElements->Emission )
    {
        pEffect->Material->Emissive = GetColor(pShaderElements->Emission);
    }

    pShaderElements->Ambient = pDomPhong->getAmbient();
    if( pShaderElements->Ambient )
    {
        pEffect->Material->Ambient = GetColor(pShaderElements->Ambient);
    }

    pShaderElements->Diffuse = pDomPhong->getDiffuse();
    if( pShaderElements->Diffuse )
    {
        pEffect->Material->Diffuse = GetColor(pShaderElements->Diffuse);
    }

    pShaderElements->Specular = pDomPhong->getSpecular();
    if( pShaderElements->Specular )
    {
        pEffect->Material->Specular = GetColor(pShaderElements->Specular);
    }

    pShaderElements->Shininess = pDomPhong->getShininess();
    if( pShaderElements->Shininess )
    {
        pEffect->Material->Shininess = GetFloat(pShaderElements->Shininess);
    }

    pShaderElements->Reflective = pDomPhong->getReflective();
    if( pShaderElements->Reflective )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflective = 
        //     GetColor(pShaderElements->Reflective);
    }

    pShaderElements->Reflectivity = pDomPhong->getReflectivity();
    if( pShaderElements->Reflectivity )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflectivity = 
        //     GetFloat(pShaderElements->Reflectivity);
    }

    pShaderElements->Transparent = pDomPhong->getTransparent();
    if( pShaderElements->Transparent ) 
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Transparent = GetColor(pShaderElements->Transparent);
    }

    pShaderElements->Transarency = pDomPhong->getTransparency();
    if( pShaderElements->Transarency )
    {
        pEffect->Material->Alpha = GetFloat(pShaderElements->Transarency);
    }

    pShaderElements->IndexOfRefaction = pDomPhong->getIndex_of_refraction();
    if( pShaderElements->IndexOfRefaction )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->RefractiveIndex = 
        //     GetFloat(pShaderElements->IndexOfRefaction);
    }
}
//----------------------------------------------------------------------------
void SEColladaScene::ParseBlinn(SEColladaEffect* pEffect, 
    SEColladaShaderElements* pShaderElements,
    domProfile_COMMON::domTechnique::domBlinn* pDomblinn)
{
    pShaderElements->Emission = pDomblinn->getEmission();
    if( pShaderElements->Emission )
    {
        pEffect->Material->Emissive = GetColor(pShaderElements->Emission);
    }

    pShaderElements->Ambient = pDomblinn->getAmbient();
    if( pShaderElements->Ambient )
    {
        pEffect->Material->Ambient = GetColor(pShaderElements->Ambient);
    }

    pShaderElements->Diffuse = pDomblinn->getDiffuse();
    if( pShaderElements->Diffuse )
    {
        pEffect->Material->Diffuse = GetColor(pShaderElements->Diffuse);
    }

    pShaderElements->Specular = pDomblinn->getSpecular();
    if( pShaderElements->Specular )
    {
        pEffect->Material->Specular = GetColor(pShaderElements->Specular);
    }

    pShaderElements->Shininess = pDomblinn->getShininess();
    if( pShaderElements->Shininess )
    {
        pEffect->Material->Shininess = GetFloat(pShaderElements->Shininess);
    }

    pShaderElements->Reflective = pDomblinn->getReflective();
    if( pShaderElements->Reflective )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflective = 
        //     GetColor(pShaderElements->Reflective);
    }

    pShaderElements->Reflectivity = pDomblinn->getReflectivity();
    if( pShaderElements->Reflectivity )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->Reflectivity = 
        //     GetFloat(pShaderElements->Reflectivity);
    }

    pShaderElements->Transparent = pDomblinn->getTransparent();
    if( pShaderElements->Transparent ) 
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Transparent = GetColor(pShaderElements->Transparent);
    }

    pShaderElements->Transarency = pDomblinn->getTransparency();
    if( pShaderElements->Transarency )
    {
        pEffect->Material->Alpha = GetFloat(pShaderElements->Transarency);
    }

    pShaderElements->IndexOfRefaction = pDomblinn->getIndex_of_refraction();
    if( pShaderElements->IndexOfRefaction )
    {
        // TODO:
        // We don't have this parameter for now.
        // pEffect->Material->RefractiveIndex = 
        //     GetFloat(pShaderElements->IndexOfRefaction);
    }
}
//----------------------------------------------------------------------------