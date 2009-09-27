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
Node* ColladaScene::GetGeometry(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Geometries.size(); i++ )
    {
        if( strcmp(m_Geometries[i]->GetName(), acName) == 0 )
        {
            return m_Geometries[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
TriMesh* ColladaScene::BuildTriangles(domTriangles* pDomTriangles)
{
    xsNCName strMaterial = pDomTriangles->getMaterial();
    if( strMaterial )
    {
        // TODO:
    }

    int iTriangleCount = (int)pDomTriangles->getCount();
    int iIndexCount = 3*iTriangleCount;

    // Get vertex buffer source data.
    domInputLocalOffset_Array& rDomInputs = pDomTriangles->getInput_array();
    ColladaInputArray tempOffsets(rDomInputs);
    domListOfFloats* pDomPositionData = tempOffsets.GetPositionData();
    domListOfFloats* pDomNormalData = tempOffsets.GetNormalData();
    int iVCount = (int)pDomPositionData->getCount()/3;
    int iStride = tempOffsets.GetMaxOffset();
    int iPositionOffset = tempOffsets.GetPositionOffset();
    int iNormalOffset = tempOffsets.GetNormalOffset();

    // Get index source data.
    domListOfUInts& rDomListOfUInts = pDomTriangles->getP()->getValue();

    Vector3f* aNormal = SE_NEW Vector3f[iVCount];
    // Recompute vertex normal by averaging contributions of trangles share 
    // the same vertex.
    if( iNormalOffset > -1 )
    {
        int iBase, iVIndex, iNIndex;
        for( int i = 0; i < iIndexCount; i++ )
        {
            iBase = i*iStride;
            iVIndex = (int)rDomListOfUInts[iBase + iPositionOffset];
            iNIndex = (int)rDomListOfUInts[iBase + iNormalOffset];

            // Get a normal from normal source.
            float fX = (float)(*pDomNormalData)[3*iNIndex    ];
            float fY = (float)(*pDomNormalData)[3*iNIndex + 1];
            float fZ = (float)(*pDomNormalData)[3*iNIndex + 2];

            // Get a Swing Engine normal vector and do averaging by using it.
            Vector3f vec3fNormal = GetTransformedVector(fX, fY, fZ);
            aNormal[iVIndex] += vec3fNormal;
        }
    }

    SE_DELETE[] aNormal;

    return 0;
}
//----------------------------------------------------------------------------
void ColladaScene::ParseGeometry(Node*& rpMeshRoot, domGeometry* pDomGeometry)
{
    domMesh* pDomMesh = pDomGeometry->getMesh();
    xsID strGeometryID = pDomGeometry->getId();
    rpMeshRoot = SE_NEW Node;
    rpMeshRoot->SetName((const char*)strGeometryID);

    // Not sure if we should get primitives by groups or by whatever comes 
    // first, I think it shouldn't matter, let's confirm later.

    // <polylist> element.
    int iPolylistCount = (int)pDomMesh->getPolylist_array().getCount();
    for( int i = 0; i< iPolylistCount; i++ )
    {
        // TODO:
        // Support this.
    }

    // <polygons> element.
    int iPolygonsCount = (int)pDomMesh->getPolygons_array().getCount();
    for( int i = 0; i < iPolygonsCount; i++ )
    {
        // TODO:
        // Support this.
    }

    // <triangles> element.
    domTriangles_Array& rDomTrianglesArray = pDomMesh->getTriangles_array();
    int iTrianglesCount = (int)rDomTrianglesArray.getCount();
    for( int i = 0; i < iTrianglesCount; i++ )
    {
        // Each <triangles> element is a sub mesh of the current geometry,
        // the sub mesh could has its own material(effect) for rendering.
        TriMesh* pSubMesh = BuildTriangles(rDomTrianglesArray[i]);
        if( pSubMesh )
        {
            rpMeshRoot->AttachChild(pSubMesh);
        }
    }

    // <tristrips> element.
    int iTriStripsCount = (int)pDomMesh->getTristrips_array().getCount();
    for( int i = 0; i < iTriStripsCount ; i++ )
    {
        // TODO:
        // Support this.
    }

    // <trifans> element.
    int iTriFansCount = (int)pDomMesh->getTrifans_array().getCount();
    for( int i = 0; i< iTriFansCount ; i++ )
    {
        // TODO:
        // Support this.
    }

    // <lines> element.
    int iLinesCount = (int)pDomMesh->getLines_array().getCount();
    for( int i = 0; i < iLinesCount ; i++)
    {
        // TODO:
        // Support this.
    }

    int iLineStripsCount = (int)pDomMesh->getLinestrips_array().getCount();
    for( int i = 0; i< iLineStripsCount ; i++ )
    {
        // TODO:
        // Support this.
    }

}
//----------------------------------------------------------------------------
Node* ColladaScene::LoadGeometry(domGeometryRef spDomGeometry)
{
    xsID strGeometryID = spDomGeometry->getId();
    if( !strGeometryID )
    {
        return 0;
    }

    Node* pMeshRoot = GetGeometry(strGeometryID);
    // This geometry is already in our geometry catalog.
    if( pMeshRoot )
    {
        return pMeshRoot;
    }

    ToolSystem::SE_DebugOutput("Add new geometry %s", strGeometryID);

    // See what kind of data is in the geometry (there can be only one).
    domAsset* pDomAsset = spDomGeometry->getAsset();
    domMesh* pDomMesh = spDomGeometry->getMesh();
    domConvex_mesh* pDomConvexMesh = spDomGeometry->getConvex_mesh();
    domExtra_Array& rDomExtraArray = spDomGeometry->getExtra_array();
    domSpline* pDomSpline = spDomGeometry->getSpline();

    if( pDomAsset )
    {
        ToolSystem::SE_DebugOutput( "<asset>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( pDomConvexMesh )
    {
        ToolSystem::SE_DebugOutput( "<convex_mesh>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( rDomExtraArray.getCount() )
    {
        ToolSystem::SE_DebugOutput( "<extra>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( pDomSpline )
    {
        ToolSystem::SE_DebugOutput( "<spline>:%s, not support, skipped it", 
            strGeometryID);
    }

    if( !pDomMesh )
    {
        return 0;
    }

    // We only support <mesh> element for now.
    ParseGeometry(pMeshRoot, spDomGeometry);

    m_Geometries.push_back(pMeshRoot);
    return pMeshRoot;
}
//----------------------------------------------------------------------------
Node* ColladaScene::LoadInstanceGeometry(domInstance_geometryRef splib)
{
    // Find the <geometry> which the <instance_geometry> is pointing to 
    // (there can be only one) by searching the Geometries list in the scene.
    xsAnyURI& rUrlType  = splib->getUrl();
    rUrlType.resolveElement();
    domElement* pDomElement = (domElement*)rUrlType.getElement();

    // If this instance geometry is not found then we skip to the next one.
    if( !pDomElement )
    {
        return 0;
    }

    Node* pMeshRoot = LoadGeometry((domGeometry*)pDomElement);
    if( !pMeshRoot )
    {
        return 0;
    }

    //CrtInstanceGeometry *newCrtInstanceGeometry = CrtNew(CrtInstanceGeometry);
    //CrtAssert("No memory\n", newCrtInstanceGeometry!=NULL);
    //newCrtInstanceGeometry->AbstractGeometry = geo;

    //domBind_material *bindMaterial =  lib->getBind_material();
    //if(bindMaterial)
    //{
    //	// Get the <technique_common>
    //	domBind_material::domTechnique_common *techniqueCommon = bindMaterial->getTechnique_common();
    //	if(techniqueCommon)
    //	{
    //		// Get the <instance_material>s
    //		domInstance_material_Array &instanceMaterialArray = techniqueCommon->getInstance_material_array();
    //		for(int j = 0; j < instanceMaterialArray.getCount(); j++)
    //		{
    //			CrtInstanceMaterial * newiMaterial = ReadInstanceMaterial(instanceMaterialArray[j]);
    //			newCrtInstanceGeometry->MaterialInstances.push_back(newiMaterial);
    //		}
    //	}
    //}

    return pMeshRoot;
}
//----------------------------------------------------------------------------