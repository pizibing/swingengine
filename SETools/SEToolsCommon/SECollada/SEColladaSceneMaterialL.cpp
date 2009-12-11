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
ColladaMaterial* ColladaScene::GetMaterial(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Materials.size(); i++ )
    {
        if( strcmp(m_Materials[i]->GetName().c_str(), acName) == 0 )
        {
            return m_Materials[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
ColladaInstanceMaterial* ColladaScene::GetInstanceMaterial(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_InstanceMaterials.size(); i++ )
    {
        if( strcmp(m_InstanceMaterials[i]->GetName().c_str(), acName) == 0 )
        {
            return m_InstanceMaterials[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
bool ColladaScene::LoadMaterialLibrary(domLibrary_materialsRef spLib)
{
    ToolSystem::SE_DebugOutput("ColladaScene::Loading Material Library");

    int iMaterialCount = (int)spLib->getMaterial_array().getCount();
    for( int i = 0; i < iMaterialCount; i++ )
    {
        LoadMaterial(spLib->getMaterial_array()[i]);
    }

    return true; 
}
//----------------------------------------------------------------------------
ColladaMaterial* ColladaScene::LoadMaterial(domMaterialRef spDomMaterial)
{
    if( !spDomMaterial )
    {
        return 0;
    }

    xsID strMaterialID = spDomMaterial->getId();
    if( !strMaterialID )
    {
        return 0;
    }

    ColladaMaterial* pMaterial = GetMaterial(strMaterialID);
    if( pMaterial )
    {
        // This material is already in our material catalog.
        return pMaterial;
    }

    ToolSystem::SE_DebugOutput("Add new material %s", strMaterialID);

    domMaterial* pDomMaterial = (domMaterial*)spDomMaterial;
    if( pDomMaterial ) 
    {
        domInstance_effect* pDomInstanceEffect = 
            pDomMaterial->getInstance_effect();
        if( !pDomInstanceEffect )
        {
            return 0;
        }

        domElement* pDomElement = pDomInstanceEffect->getUrl().getElement();
        if( !pDomElement )
        {
            return 0;
        }

        // Find the effect that the material is refering to.
        ColladaEffect* pEffect = LoadEffect((domEffect*)pDomElement);
        if( pEffect )
        {
            ColladaMaterial* pMaterial = SE_NEW ColladaMaterial(pEffect);
            pMaterial->SetName(strMaterialID);
            ToolSystem::SE_DebugOutput(
                "Attaching effect %s to material %s \n", pEffect->GetName(), 
                pMaterial->GetName()); 
            m_Materials.push_back(pMaterial);

            return pMaterial; 	
        } 
        else
        {
            std::string strOutput = "No effect %s for old-style matrial %s ";
            strOutput += "(no problem if there is a cfx version of this ";
            strOutput += "material)";

            ToolSystem::SE_DebugOutput(strOutput.c_str(), 
                pDomElement->getID(), strMaterialID);

            return 0;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
ColladaInstanceMaterial* ColladaScene::LoadInstanceMaterial(
    domInstance_materialRef spLib)
{
    ColladaInstanceMaterial* pInstanceMaterial = 
        SE_NEW ColladaInstanceMaterial;

    xsNCName strSymbol = spLib->getSymbol();
    daeString strTarget = spLib->getTarget().getID();
    pInstanceMaterial->SetName((const char*)strSymbol);
    pInstanceMaterial->TargetName = (const char*)strTarget;

    domElement* pDomElement = spLib->getTarget().getElement();
    if( pDomElement )
    {
        // Add or find this material object.
        ColladaMaterial* pMaterial = LoadMaterial((domMaterial*)pDomElement);
        if( pMaterial )
        {
            pInstanceMaterial->TargetMaterial = pMaterial;
        }
        else
        {
            ToolSystem::SE_DebugOutput("Couldn't find target material:%s",
                pInstanceMaterial->TargetName.c_str());
        }
    }

    return pInstanceMaterial;
}
//----------------------------------------------------------------------------