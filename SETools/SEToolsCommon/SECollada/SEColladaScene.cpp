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

ColladaScene::OrientationMode ColladaScene::ms_eOrientationMode = 
    ColladaScene::OM_UNKNOWN;

//----------------------------------------------------------------------------
ColladaScene::ColladaScene(IDirect3DDevice9* pDevice)
{
    m_pDAE = SE_NEW DAE;
    m_pImageConverter = SE_NEW ImageConverter(pDevice);
}
//----------------------------------------------------------------------------
ColladaScene::~ColladaScene()
{
    SE_DELETE m_pDAE;
    SE_DELETE m_pImageConverter;
}
//----------------------------------------------------------------------------
void ColladaScene::Load(const char* acFilename)
{
    ToolSystem::SE_DebugOutput("COLLADA DOM loading process started" );

    // Load a .dae file from disk, and set up DAE runtime automatically.
    daeInt iRes = m_pDAE->load(acFilename);
    if( iRes != DAE_OK )
    {
        ToolSystem::SE_DebugOutput("The COLLADA file %s is illegal", 
            acFilename);
        return;
    }

    // Get the DOM interface for later use.
    domCOLLADA* pDom = m_pDAE->getDom(acFilename);

    // Do triangulation work unconditionally at the very beginning.
    ToolSystem::SE_DebugOutput("Begin conditioning of triangulation");
    Triangulate(m_pDAE);
    ToolSystem::SE_DebugOutput("Finish conditioning of triangulation");

    // Get current coordinate frame orientation.
    if( pDom->getAsset()->getUp_axis() )
    {
        domAsset::domUp_axis* pUp = pDom->getAsset()->getUp_axis();
        switch( pUp->getValue() )
        {
        case UPAXISTYPE_X_UP:
            ToolSystem::SE_DebugOutput("Right-handed system with X upward");
            ms_eOrientationMode = OM_X_UP;
            break;

        case UPAXISTYPE_Y_UP:
            ToolSystem::SE_DebugOutput("Right-handed system with Y upward");
            ms_eOrientationMode = OM_Y_UP;
            break;

        case UPAXISTYPE_Z_UP:
            ToolSystem::SE_DebugOutput("Right-handed system with Z upward");
            ms_eOrientationMode = OM_Z_UP;
            break;

        default:
            break; 
        }
    }

    // Load all the image libraries.
    int iImageLibCount = (int)pDom->getLibrary_images_array().getCount();
    for( int i = 0; i < iImageLibCount; i++ )
    {
        LoadImageLibrary(pDom->getLibrary_images_array()[i]);			
    }

    // Load all the effect libraries.
    int iEffectLibCount = (int)pDom->getLibrary_effects_array().getCount();
    for( int i = 0; i < iEffectLibCount; i++ )
    {
        LoadEffectLibrary(pDom->getLibrary_effects_array()[i]);			
    }

    // Load all the material libraries.
    int iMaterialLibCount = 
        (int)pDom->getLibrary_materials_array().getCount();
    for( int i = 0; i < iMaterialLibCount; i++ )
    {
        LoadMaterialLibrary(pDom->getLibrary_materials_array()[i]);			
    }

    // Load all the animation libraries.
    int iAnimationLibCount = 
        (int)pDom->getLibrary_animations_array().getCount();
    for( int i = 0; i < iAnimationLibCount; i++ )
    {
        LoadAnimationLibrary(pDom->getLibrary_animations_array()[i] );			
    }

    // Swing Engine scene graph creation pass.
    // Find the scene we want and load it.
    domCOLLADA::domSceneRef spDomScene = pDom->getScene();
    daeElement* pDefaultScene = 0;
    if( spDomScene )
    {
        domInstanceWithExtraRef spInstanceVisualScene = 
            spDomScene->getInstance_visual_scene();
        if( spInstanceVisualScene )
        {
            pDefaultScene = spInstanceVisualScene->getUrl().getElement();
        }
    }
    if( pDefaultScene )
    {
        LoadScene((domVisual_scene*)pDefaultScene);
    }

    // Deferred processing of lights.
    ProcessLights();

    // Deferred processing of cameras.
    ProcessCameras();

    // Deferred processing of controllers.
    // TODO:
    // Impliment controller option.
    ProcessControllers();
}
//----------------------------------------------------------------------------
Node* ColladaScene::GetScene()
{
    return m_spSceneRoot;
}
//----------------------------------------------------------------------------
unsigned int ColladaScene::GetMaxOffset(
    domInputLocalOffset_Array& rInputArray)
{
    unsigned int uiMaxOffset = 0;
    for( int i = 0; i < (int)rInputArray.getCount(); i++ ) 
    {
        if( rInputArray[i]->getOffset() > uiMaxOffset ) 
        {
            uiMaxOffset = (unsigned int)rInputArray[i]->getOffset();
        }
    }

    return uiMaxOffset;
}
//----------------------------------------------------------------------------
void ColladaScene::CreateTrianglesFromPolylist(domMesh* pDomMesh, 
    domPolylist* pDomPolylist)
{
    // Create a new <triangles> inside the mesh that has the same material 
    // as the <polylist>.
    domTriangles* pDomTriangles = (domTriangles*)pDomMesh->createAndPlace(
        "triangles");
    pDomTriangles->setMaterial(pDomPolylist->getMaterial());
    domP* pDomTrianglesP = (domP*)pDomTriangles->createAndPlace("p");

    // Give the new <triangles> the same <_dae> and <parameters> as the old 
    // <polylist>.
    for( int i = 0; i < (int)(pDomPolylist->getInput_array().getCount()); i++ )
    {
        pDomTriangles->placeElement(
            pDomPolylist->getInput_array()[i]->clone());
    }

    // Get the number of inputs and primitives for the polygons array.
    int iInputCount = (int)GetMaxOffset(pDomPolylist->getInput_array()) + 1;
    int iPrimitiveCount = (int)(pDomPolylist->getVcount()->getValue().getCount());

    unsigned int uiOffset = 0;
    unsigned int uiTrianglesProcessed = 0;

    // Triangulate all the primitives, this generates all the triangles in a 
    // single <p> element.
    for( int j = 0; j < iPrimitiveCount; j++ )
    {
        int iTriangleCount = (int)pDomPolylist->getVcount()->getValue()[j] - 2;

        // Write out the primitives as triangles, just fan using the first element
        // as the base.
        int iIndex = iInputCount;
        for( int k = 0; k < iTriangleCount; k++ )
        {
            // First vertex.
            for( int l = 0; l < iInputCount; l++ )
            {
                pDomTrianglesP->getValue().append(
                    pDomPolylist->getP()->getValue()[uiOffset + l]);
            }
            // Second vertex.
            for( int l = 0; l < iInputCount; l++ )
            {
                pDomTrianglesP->getValue().append(
                    pDomPolylist->getP()->getValue()[uiOffset + iIndex + l]);
            }
            // Third vertex.
            iIndex += iInputCount;
            for( int l = 0; l < iInputCount; l++ )
            {
                pDomTrianglesP->getValue().append(
                    pDomPolylist->getP()->getValue()[uiOffset + iIndex + l]);
            }

            uiTrianglesProcessed++;
        }

        uiOffset += (unsigned int)pDomPolylist->getVcount()->getValue()[j] * 
            iInputCount;
    }
    pDomTriangles->setCount(uiTrianglesProcessed);
}
//----------------------------------------------------------------------------
void ColladaScene::CreateTrianglesFromPolygons(domMesh* pDomMesh, 
    domPolygons* pDomPolygons)
{
    // Create a new <triangles> inside the mesh that has the same material as
    // the <polygons>.
    domTriangles *pDomTriangles = (domTriangles*)pDomMesh->createAndPlace(
        "triangles");
    pDomTriangles->setCount(0);
    pDomTriangles->setMaterial(pDomPolygons->getMaterial());
    domP* pDomTrianglesP = (domP*)pDomTriangles->createAndPlace("p");

    // Give the new <triangles> the same <_dae> and <parameters> as the old 
    // <polygons>.
    for( int i = 0; i < (int)(pDomPolygons->getInput_array().getCount()); i++ )
    {
        pDomTriangles->placeElement(
            pDomPolygons->getInput_array()[i]->clone());
    }

    // Get the number of inputs and primitives for the polygons array.
    int iInputCount = (int)GetMaxOffset(pDomPolygons->getInput_array()) + 1;
    int iPrimitiveCount = (int)(pDomPolygons->getP_array().getCount());

    // Triangulate all the primitives, this generates all the triangles in a 
    // single <p> element.
    for( int j = 0; j < iPrimitiveCount; j++ )
    {
        // Check the polygons for consistancy (some exported files have had 
        // the wrong number of indices).
        domP* pDomCurrentP = pDomPolygons->getP_array()[j];
        int iElementCount = (int)(pDomCurrentP->getValue().getCount());
        if( (iElementCount%iInputCount) != 0 )
        {

        }
        else
        {
            int iTriangleCount = (iElementCount/iInputCount) - 2;
            // Write out the primitives as triangles, just fan using the first
            // element as the base.
            int iIndex = iInputCount;
            for( int k = 0; k < iTriangleCount; k++ )
            {
                // First vertex.
                for( int l = 0; l < iInputCount; l++ )
                {
                    pDomTrianglesP->getValue().append(
                        pDomCurrentP->getValue()[l]);
                }
                // Second vertex.
                for( int l = 0; l < iInputCount; l++ )
                {
                    pDomTrianglesP->getValue().append(
                        pDomCurrentP->getValue()[iIndex + l]);
                }
                // Third vertex.
                iIndex += iInputCount;
                for( int l = 0; l < iInputCount; l++ )
                {
                    pDomTrianglesP->getValue().append(
                        pDomCurrentP->getValue()[iIndex + l]);
                }
                pDomTriangles->setCount(pDomTriangles->getCount() + 1);
            }
        }
    }
}
//----------------------------------------------------------------------------
void ColladaScene::Triangulate(DAE* pDAE)
{
    SE_ASSERT( pDAE );

    daeDatabase* pDataBase = pDAE->getDatabase();
    SE_ASSERT( pDataBase );

    int iGeometryCount = (int)(pDataBase->getElementCount(0, "geometry"));
    for( int i = 0; i < iGeometryCount; i++ )
    {
        // Find the next geometry element.
        domGeometry* pDomGeometry;
        pDataBase->getElement((daeElement**)&pDomGeometry, i, 0, "geometry");

        // Get the mesh out of the geometry.
        domMesh* pDomMesh = pDomGeometry->getMesh();
        if( !pDomMesh )
            continue;

        // Loop over all the polygons elements.
        int iPolygonsCount = (int)(pDomMesh->getPolygons_array().getCount());
        for( int j = 0; j < iPolygonsCount; j++ )
        {
            // Get the polygons out of the mesh.
            domPolygons* pDomPolygons = pDomMesh->getPolygons_array()[j];
            CreateTrianglesFromPolygons(pDomMesh, pDomPolygons);
        }
        while( pDomMesh->getPolygons_array().getCount() > 0 )
        {
            domPolygons* pDomPolygons = pDomMesh->getPolygons_array().get(0);  
            // Remove the polygons from the mesh.
            pDomMesh->removeChildElement(pDomPolygons);
        }

        // Loop over all the polylist elements.
        int iPolylistCount = (int)(pDomMesh->getPolylist_array().getCount());
        for( int j = 0; j < iPolylistCount; j++)
        {
            // Get the polylist out of the mesh.
            domPolylist* pDomPolylist = pDomMesh->getPolylist_array()[j];
            CreateTrianglesFromPolylist(pDomMesh, pDomPolylist);
        }
        while( pDomMesh->getPolylist_array().getCount() > 0 )
        {
            domPolylist* pDomPolylist = pDomMesh->getPolylist_array().get(0);  
            // Remove the polylist from the mesh.
            pDomMesh->removeChildElement(pDomPolylist);
        }
    }
}
//----------------------------------------------------------------------------
Vector3f ColladaScene::GetTransformedVector(float fX, float fY, float fZ)
{
    Vector3f vec3fRes;

    // COLLADA uses right-handed based system, now we only have these three 
    // situations to deal with. The result vector is a left-handed based 
    // Swing Engine vector.
    switch(ms_eOrientationMode)
    {
    case OM_Y_UP:
        vec3fRes.X = fX;
        vec3fRes.Y = fY;
        vec3fRes.Z = -fZ;
        break;

    case OM_Z_UP:
        vec3fRes.X = fX;
        vec3fRes.Y = fZ;
        vec3fRes.Z = fY;
        break;

    case OM_X_UP:
        vec3fRes.X = -fY;
        vec3fRes.Y = fX;
        vec3fRes.Z = -fZ;
        break;

    default:
        SE_ASSERT( false );
    }

    return vec3fRes;
}
//----------------------------------------------------------------------------
bool ColladaScene::LoadScene(domVisual_sceneRef spDomVisualScene)
{
    // Create Swing Engine scene graph's root.
    // Save the scene name instead of scene id.
    m_spSceneRoot = SE_NEW Node;
    xsNCName strSceneName = spDomVisualScene->getName();
    m_spSceneRoot->SetName(strSceneName);

    ToolSystem::SE_DebugOutput("ColladaScene::Loading Collada Scene %s", 
        (const char*)strSceneName);

    // Recurse through the scene, load and add nodes.
    domNode_Array& rDomNodeArray = spDomVisualScene->getNode_array();
    int iTopLevelNodeCount = (int)rDomNodeArray.getCount();
    for( int i = 0; i < iTopLevelNodeCount; i++ )
    {
        Node* pNode = LoadNode(rDomNodeArray[i], m_spSceneRoot);
        if( pNode )
        {
            const char* acNodeName = (const char*)pNode->GetName();
            m_Nodes[acNodeName] = pNode;
        }
    }

    // Finally add the scene root node.
    m_Nodes[strSceneName] = m_spSceneRoot;

    // Update Swing Engine scene graph.
    m_spSceneRoot->UpdateRS();
    m_spSceneRoot->UpdateGS();

    return true;
}
//----------------------------------------------------------------------------