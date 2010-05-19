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
#include <set>

using namespace Swing;
using namespace std;

//----------------------------------------------------------------------------
SENode* SEColladaScene::GetGeometry(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Geometries.size(); i++ )
    {
		if( strcmp(m_Geometries[i]->GetName().c_str(), acName) == 0 )
        {
            return m_Geometries[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEColladaScene::PackVertices(SEColladaUnimaterialMesh* pUniMesh,
    domListOfFloats* pDomPositionData, int iPositionStride, domListOfUInts& 
    rDomIndexData, int iIndexCount, int iStride, int iPositionOffset, 
    SEVector3f* aNormal)
{
    // 当前部分所使用的顶点索引,set确保顶点唯一性.
    set<int> tempVIndexSet;
    int iBase, iVIndex;
    for( int i = 0; i < iIndexCount; i++ )
    {
        iBase = i*iStride;
        iVIndex = (int)rDomIndexData[iBase + iPositionOffset];
        tempVIndexSet.insert(iVIndex);
    }

    // 全局网格顶点索引是顶点在整个COLLADA网格顶点资源数组(pDomPositionData)中
    // 的索引.建立一个全局网格顶点索引的反向映射表,
    // 针对当前使用同一材质的子网格,建立一个子网格顶点资源数组,
    // 该顶点数组下标0到n,表示n+1个不重复的顶点),
    // 建立反向映射数组(数组下标0到m,表示顶点的全局网格顶点索引,m为最大索引值).
    // STL set类默认把插入的元素按照增序排列存储,
    // 因此当前set中末尾元素必定为当前子网格的最大全局网格顶点索引.
    // 如果tempVIndexSet[i] = j,则aiVMap[j] = i.
    // 如果是当前子网格没有用到的全局网格顶点索引,则aiVMap[j] = -1.
    int iVMax = *tempVIndexSet.rbegin();
    int* aiVMap = SE_NEW int[iVMax + 1];
    memset(aiVMap, 0xFF, (iVMax + 1)*sizeof(int));

    int iVCount = (int)tempVIndexSet.size();
    pUniMesh->VCount() = iVCount;
    pUniMesh->Vertex() = SE_NEW SEVector3f[iVCount];
    pUniMesh->Normal() = SE_NEW SEVector3f[iVCount];

    set<int>::iterator tempIter = tempVIndexSet.begin();
    for( int i = 0; i < (int)tempVIndexSet.size(); i++, tempIter++ )
    {
        int j = *tempIter;
        aiVMap[j] = i;

        float fX = (float)(*pDomPositionData)[iPositionStride*j    ];
        float fY = (float)(*pDomPositionData)[iPositionStride*j + 1];
        float fZ = (float)(*pDomPositionData)[iPositionStride*j + 2];
        SEVector3f vec3fPosition = GetTransformedVector(fX, fY, fZ);
        pUniMesh->Vertex()[i].X = vec3fPosition.X;
        pUniMesh->Vertex()[i].Y = vec3fPosition.Y;
        pUniMesh->Vertex()[i].Z = vec3fPosition.Z;
        pUniMesh->Normal()[i].X = aNormal[j].X;
        pUniMesh->Normal()[i].Y = aNormal[j].Z;
        pUniMesh->Normal()[i].Z = aNormal[j].Y;
    }

    // Build sub-mesh index buffer for faces of vertices.
    // For each triangle, we swap COLLADA counter-clockwise order to
    // Swing Engine clockwise order. Say, V0, V1, V2 to V0, V2, V1.
    pUniMesh->FCount() = iIndexCount/3;
    pUniMesh->Face() = SE_NEW int[iIndexCount];
    for( int i = 0; i < pUniMesh->FCount(); i++ )
    {
        int iIndex = 3*i;
        iBase = iIndex*iStride;
        iVIndex = (int)rDomIndexData[iBase + iPositionOffset];
        pUniMesh->Face()[iIndex] = aiVMap[iVIndex];

        iIndex++;
        iBase = iIndex*iStride;
        iVIndex = (int)rDomIndexData[iBase + iPositionOffset];
        pUniMesh->Face()[iIndex + 1] = aiVMap[iVIndex];

        iIndex++;
        iBase = iIndex*iStride;
        iVIndex = (int)rDomIndexData[iBase + iPositionOffset];
        pUniMesh->Face()[iIndex - 1] = aiVMap[iVIndex];
    }
    SE_DELETE[] aiVMap;
}
//----------------------------------------------------------------------------
void SEColladaScene::PackTextures(SEColladaUnimaterialMesh* pUniMesh,
    domListOfFloats* pDomTCoordData, int iTCoordStride, domListOfUInts& 
    rDomIndexData, int iIndexCount, int iStride, int iTCoordOffset)
{
    // 当前部分所使用的纹理坐标索引,set确保纹理坐标唯一性.
    set<int> tempTIndexSet;
    int iBase, iTIndex;
    for( int i = 0; i < iIndexCount; i++ )
    {
        iBase = i*iStride;
        iTIndex = (int)rDomIndexData[iBase + iTCoordOffset];
        tempTIndexSet.insert(iTIndex);
    }

    // 全局网格纹理坐标索引是纹理坐标在整个COLLADA网格纹理坐标资源数组中的索引.
    // 建立一个全局网格纹理坐标索引的反向映射表,
    // 针对当前使用同一材质的子网格,建立一个子网格纹理坐标资源数组,
    // 该纹理坐标数组下标0到n,表示n+1个不重复的纹理坐标),
    // 建立反向映射数组(数组下标0到m,表示纹理坐标的全局网格纹理坐标索引,m为最大
    // 索引值).
    // STL set类默认把插入的元素按照增序排列存储,
    // 因此当前set中末尾元素必定为当前子网格的最大全局网格纹理坐标索引.
    // 如果tempTIndexSet[i] = j,则aiTMap[j] = i.
    // 如果是当前子网格没有用到的全局网格纹理坐标索引,则aTMap[j] = -1.
    int iTMax = *tempTIndexSet.rbegin();
    int* aiTMap = SE_NEW int[iTMax + 1];
    memset(aiTMap, 0xFF, (iTMax + 1)*sizeof(int));

    int iTCount = (int)tempTIndexSet.size();
    pUniMesh->TCount() = iTCount;
    pUniMesh->SETexture() = SE_NEW SEVector2f[iTCount];

    set<int>::iterator tempIter = tempTIndexSet.begin();
    for( int i = 0; i < (int)tempTIndexSet.size(); i++, tempIter++ )
    {
        int j = *tempIter;
        aiTMap[j] = i;

        float fX = (float)(*pDomTCoordData)[iTCoordStride*j    ];
        float fY = (float)(*pDomTCoordData)[iTCoordStride*j + 1];
        pUniMesh->SETexture()[i].X = fX;
        pUniMesh->SETexture()[i].Y = 1.0f - fY;
    }

    // Build sub-mesh index buffer for faces of TCoords.
    // For each triangle, we swap COLLADA counter-clockwise order to
    // Swing Engine clockwise order. Say, V0,V1,V2 to V0, V2, V1.
    pUniMesh->TFace() = SE_NEW int[iIndexCount];
    for( int i = 0; i < pUniMesh->FCount(); i++ )
    {
        int iIndex = 3*i;
        iBase = iIndex*iStride;
        iTIndex = (int)rDomIndexData[iBase + iTCoordOffset];
        pUniMesh->TFace()[iIndex] = aiTMap[iTIndex];

        iIndex++;
        iBase = iIndex*iStride;
        iTIndex = (int)rDomIndexData[iBase + iTCoordOffset];
        pUniMesh->TFace()[iIndex + 1] = aiTMap[iTIndex];

        iIndex++;
        iBase = iIndex*iStride;
        iTIndex = (int)rDomIndexData[iBase + iTCoordOffset];
        pUniMesh->TFace()[iIndex - 1] = aiTMap[iTIndex];
    }
    SE_DELETE[] aiTMap;
}
//----------------------------------------------------------------------------
SETriMesh* SEColladaScene::BuildTriangles(domTriangles* pDomTriangles)
{
    // Try to find an instance material object used by this sub-mesh.
    xsNCName strIMaterialName = pDomTriangles->getMaterial();
    SEColladaInstanceMaterial* pSubMeshIMaterial = 0;
    if( strIMaterialName )
    {
        pSubMeshIMaterial = GetInstanceMaterial((const char*)strIMaterialName);
    }

    // Create a uni-material sub-mesh.
    SEColladaUnimaterialMesh* pSubMesh = SE_NEW SEColladaUnimaterialMesh;
    if( pSubMeshIMaterial && pSubMeshIMaterial->TargetMaterial )
    {
        pSubMesh->MState() = pSubMeshIMaterial->TargetMaterial->GetMState();

        // TODO:
        // Just grab the first texture as a diffuse texture for now.
        pSubMesh->TState() = pSubMeshIMaterial->TargetMaterial->GetTexture(0);
    }

    int iTriangleCount = (int)pDomTriangles->getCount();
    int iIndexCount = 3*iTriangleCount;

    // Get vertex buffer source data.
    domInputLocalOffset_Array& rDomInputs = pDomTriangles->getInput_array();
    SEColladaInputArray tempOffsets(rDomInputs);
    domListOfFloats* pDomPositionData = tempOffsets.GetPositionData();
    domListOfFloats* pDomNormalData = tempOffsets.GetNormalData();
    domListOfFloats* pDomTCoordData = tempOffsets.GetTCoordData();
    int iPositionStride = tempOffsets.GetPositionStride();
    int iNormalStride = tempOffsets.GetNormalStride();
    int iTCoordStride = tempOffsets.GetTCoordStride();
    int iVCount = (int)pDomPositionData->getCount()/iPositionStride;
    int iStride = tempOffsets.GetMaxOffset();
    int iPositionOffset = tempOffsets.GetPositionOffset();
    int iNormalOffset = tempOffsets.GetNormalOffset();
    int iTCoordOffset = tempOffsets.GetTCoordOffset();

    // Get index source data.
    domListOfUInts& rDomIndexData = pDomTriangles->getP()->getValue();

    // Recompute vertex normal by averaging contributions of trangles share 
    // the same vertex.
    // TODO:
    // Impliment importer option.
    SEVector3f* aNormal = SE_NEW SEVector3f[iVCount];
    if( iNormalOffset > -1 )
    {
        int iBase, iVIndex, iNIndex;
        float fX, fY, fZ;
        for( int i = 0; i < iIndexCount; i++ )
        {
            iBase = i*iStride;
            iVIndex = (int)rDomIndexData[iBase + iPositionOffset];
            iNIndex = (int)rDomIndexData[iBase + iNormalOffset];

            // Get a normal from normal source.
            fX = (float)(*pDomNormalData)[iNormalStride*iNIndex    ];
            fY = (float)(*pDomNormalData)[iNormalStride*iNIndex + 1];
            fZ = (float)(*pDomNormalData)[iNormalStride*iNIndex + 2];

            // Get a Swing Engine normal vector and do averaging by using it.
            SEVector3f vec3fNormal = GetTransformedVector(fX, fY, fZ);
            aNormal[iVIndex] += vec3fNormal;
        }
    }

    // Pack vertex data for the mesh.
    PackVertices(pSubMesh, pDomPositionData, iPositionStride, rDomIndexData, 
        iIndexCount, iStride, iPositionOffset, aNormal);

    // TODO:
    // if DCC has vertex color data for the mesh, maybe we should pack it.
    // Then impliment importer option.

    // Pack texture coordinate data for the mesh.
    if( EnableTCoord && iTCoordOffset > -1 )
    {
        PackTextures(pSubMesh, pDomTCoordData, iTCoordStride, rDomIndexData, 
            iIndexCount, iStride, iTCoordOffset);
    }

    // Generate the final uni-material sub-mesh before calling ToTriMesh().
    pSubMesh->DuplicateGeometry();

    // Generate a Swing Engine SETriMesh object based on the COLLADA sub-mesh.
    SETriMesh* pResMesh = pSubMesh->ToTriMesh();

    SE_DELETE[] aNormal;
    SE_DELETE pSubMesh;

    return pResMesh;
}
//----------------------------------------------------------------------------
void SEColladaScene::ParseGeometry(SENode*& rpMeshRoot, domGeometry* 
    pDomGeometry)
{
    domMesh* pDomMesh = pDomGeometry->getMesh();
    xsID strGeometryID = pDomGeometry->getId();
    rpMeshRoot = SE_NEW SENode;
    rpMeshRoot->SetName((const char*)strGeometryID);
    const size_t uiBufferSize = 64;
    char acMeshName[uiBufferSize];

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
        // Each <triangles> element is a sub-mesh of the current geometry,
        // the sub-mesh could has its own material(effect) for rendering.
        SETriMesh* pSubMesh = BuildTriangles(rDomTrianglesArray[i]);
        if( pSubMesh )
        {
            SESystem::SE_Sprintf(acMeshName, uiBufferSize, "%s_Triangles%d", 
                (const char*)strGeometryID, i);
            pSubMesh->SetName(acMeshName);
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
SENode* SEColladaScene::LoadGeometry(domGeometryRef spDomGeometry)
{
    xsID strGeometryID = spDomGeometry->getId();
    if( !strGeometryID )
    {
        return 0;
    }

    SENode* pMeshRoot = GetGeometry(strGeometryID);
    if( pMeshRoot )
    {
        // This geometry is already in our geometry catalog.
        return pMeshRoot;
    }

    ToolSystem::DebugOutput("Add new geometry %s", strGeometryID);

    // See what kind of data is in the geometry (there can be only one).
    domAsset* pDomAsset = spDomGeometry->getAsset();
    domMesh* pDomMesh = spDomGeometry->getMesh();
    domConvex_mesh* pDomConvexMesh = spDomGeometry->getConvex_mesh();
    domExtra_Array& rDomExtraArray = spDomGeometry->getExtra_array();
    domSpline* pDomSpline = spDomGeometry->getSpline();

    if( pDomAsset )
    {
        ToolSystem::DebugOutput("<asset>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( pDomConvexMesh )
    {
        ToolSystem::DebugOutput("<convex_mesh>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( rDomExtraArray.getCount() )
    {
        ToolSystem::DebugOutput("<extra>:%s, not support, skipped it", 
            strGeometryID);
    }
    else if( pDomSpline )
    {
        ToolSystem::DebugOutput("<spline>:%s, not support, skipped it", 
            strGeometryID);
    }

    if( !pDomMesh )
    {
        return 0;
    }

    // We only support <mesh> element for now.
    ParseGeometry(pMeshRoot, spDomGeometry);

    if( pMeshRoot )
    {
        m_Geometries.push_back(pMeshRoot);
    }

    return pMeshRoot;
}
//----------------------------------------------------------------------------
SENode* SEColladaScene::LoadInstanceGeometry(domInstance_geometryRef spLib)
{
    // Get all instance materials used by this instance geometry object.
    // Each instance material points to a material object in our material 
    // catalog.
    domBind_material* pDomBindMaterial =  spLib->getBind_material();
    if( pDomBindMaterial )
    {
        // Get the <technique_common> element.
        domBind_material::domTechnique_common* pDomTechniqueCommon = 
            pDomBindMaterial->getTechnique_common();
        if( pDomTechniqueCommon )
        {
            // Get all <instance_material> elements.
            domInstance_material_Array& rDomInstanceMaterialArray = 
                pDomTechniqueCommon->getInstance_material_array();

            int iIMaterialCount = (int)rDomInstanceMaterialArray.getCount();
            for( int i = 0; i < iIMaterialCount; i++ )
            {
                SEColladaInstanceMaterial* pInstanceMaterial = 
                    LoadInstanceMaterial(rDomInstanceMaterialArray[i]);

                if( pInstanceMaterial )
                {
                    m_InstanceMaterials.push_back(pInstanceMaterial);
                }
            }
        }
    }

    // Find the <geometry> which the <instance_geometry> is pointing to 
    // (there can be only one) by searching the Geometries list in the scene.
    xsAnyURI& rUrlType  = spLib->getUrl();
    rUrlType.resolveElement();
    domElement* pDomElement = (domElement*)rUrlType.getElement();

    // If this instance geometry is not found then we skip to the next one.
    if( !pDomElement )
    {
        return 0;
    }

    SENode* pMeshRoot = LoadGeometry((domGeometry*)pDomElement);
    return pMeshRoot;
}
//----------------------------------------------------------------------------