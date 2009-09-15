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
ShaderEffect* ColladaScene::GetEffect(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Effects.size(); i++ )
    {
        if( strcmp(m_Effects[i]->GetName(), acName) == 0 )
        {
            return m_Effects[i];
        }
    }

	return 0;
}
//----------------------------------------------------------------------------
bool ColladaScene::LoadEffectLibrary(domLibrary_effectsRef spLib)
{
    ToolSystem::SE_DebugOutput("ColladaScene::Loading Effect Library" );
    int iEffectCount = (int)spLib->getEffect_array().getCount();
    for( int i = 0; i < iEffectCount; i++ )
    {
        LoadEffect(spLib->getEffect_array()[i]);
    }

    return true;
}
//----------------------------------------------------------------------------
ShaderEffect* ColladaScene::LoadEffect(domEffectRef spDomEffect)
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

    ShaderEffect* pEffect = GetEffect((const char*)strEffectID);
    // This effect is already in our effect catalog.
    if( pEffect )
    {
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
        pEffect = SE_NEW ColladaEffect;
        pEffect->SetName(strEffectID);

        // How many profiles are there?
        int iProfileCount = 
            (int)pDomEffect->getFx_profile_abstract_array().getCount(); 

        // Scan the profiles to find the profile_COMMON.
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

				//domProfile_COMMON::domTechnique::domConstant *constant = technique->getConstant();
				//if (constant)
				//	ReadConstant(newEffect, &shader, constant);
				//domProfile_COMMON::domTechnique::domLambert *lambert = technique->getLambert();
				//if (lambert)
				//	ReadLambert(newEffect, &shader, lambert);
				//domProfile_COMMON::domTechnique::domPhong *phong = technique->getPhong();
				//if (phong)
				//	ReadPhong(newEffect, &shader, phong);
                domProfile_COMMON::domTechnique::domBlinn* pDomBlinn = 
                    pDomTechnique->getBlinn();
                if( pDomBlinn )
                {
                    ParseBlinn((ColladaEffect*)pEffect, pDomBlinn);
                }

			//	domCommon_newparam_type_Array newparam_array = common->getNewparam_array();
			//	std::map<string, domCommon_newparam_type*> NewParams;
			//	size_t uiNewParamCount = newparam_array.getCount();
			//	for (CrtUInt i = 0; i < uiNewParamCount; i++) 
			//	{
			//		NewParams[newparam_array[i]->getSid()] = newparam_array[i];
			//	}
			//	
			//	// TODO: take only the texture from diffuse for now
			//	CrtImage * image;
			//	image = GetTextureFromShader(NewParams, shader.diffuse);
			//	if (image)
			//		newEffect->Textures.push_back(image);
			//	
			//	// Handle an effect with no texture
			//	Effects.push_back(newEffect);
			//	return newEffect; 	
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
void ColladaScene::ParseBlinn(ColladaEffect* pEffect, 
    domProfile_COMMON::domTechnique::domBlinn* pDomblinn)
{
    domCommon_color_or_texture_type* pDomParam = pDomblinn->getEmission();
    if( pDomParam )
    {
        pEffect->Material->Emissive = GetColor(pDomParam);
    }

    pDomParam = pDomblinn->getAmbient();
    if( pDomParam )
    {
        pEffect->Material->Ambient = GetColor(pDomParam);
    }
}
//----------------------------------------------------------------------------