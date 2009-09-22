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
	//CrtTriangles * triangles = CrtNew(CrtTriangles);
	//// triangles count
	//triangles->count = (int) dom_triangles->getCount();
	//GrowVertexData(geometry, triangles->count * 3);
	//// resolve Material	
	//daeString str_material = dom_triangles->getMaterial();
	//if (str_material)
	//	CrtCpy(triangles->MaterialName, str_material);
	//
	//// prepare data
	//triangles->geometry = geometry;
	//domInputLocalOffset_Array & inputs = dom_triangles->getInput_array();
	//CrtOffsets offsets(inputs);

	//// set index, they all have the same index since we process deindexer conditioner
	//domListOfUInts P = dom_triangles->getP()->getValue();
	//triangles->indexes = CrtNewData(int, triangles->count * 3);
	//for (int ivertex=0; ivertex< triangles->count * 3; ivertex++)
	//{
	//	triangles->indexes[ivertex] = SetVertexData(offsets, geometry, P, ivertex);
	//}

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
        TriMesh* pSubMesh = BuildTriangles(rDomTrianglesArray[i]);
        rpMeshRoot->AttachChild(pSubMesh);
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