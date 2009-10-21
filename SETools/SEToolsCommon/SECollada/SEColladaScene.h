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

#ifndef Swing_ColladaScene_H
#define Swing_ColladaScene_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEImageConverter.h"
#include "SwingFoundation.h"
#include "SEColladaEffect.h"
#include "SEColladaMaterial.h"
#include "SEColladaAnimation.h"
#include "SEColladaUnimaterialMesh.h"
#include "SEColladaInstanceLight.h"
#include "SEColladaInstanceCamera.h"
#include "SEColladaInstanceMaterial.h"
#include "SEColladaInstanceController.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Shader Elements class
// Description:a helper class
// Author:Sun Che
// Date:20090914
//----------------------------------------------------------------------------
class ColladaShaderElements
{
public:
    ColladaShaderElements(void)
    { 
        memset(this, 0, sizeof(ColladaShaderElements));
    }
    ~ColladaShaderElements(void){}

    domCommon_color_or_texture_type* Emission;
    domCommon_color_or_texture_type* Ambient;
    domCommon_color_or_texture_type* Diffuse;
    domCommon_color_or_texture_type* Specular;
    domCommon_float_or_param_type* Shininess;

    domCommon_color_or_texture_type* Reflective;
    domCommon_float_or_param_type* Reflectivity;
    domCommon_color_or_texture_type_complexType* Transparent;
    domCommon_float_or_param_type* Transarency;
    domCommon_float_or_param_type* IndexOfRefaction;
};

//----------------------------------------------------------------------------
// Name:COLLADA Scene class
// Description:
// Author:Sun Che
// Date:20090914
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API ColladaScene
{
public:
    ColladaScene(IDirect3DDevice9* pDevice);
    ~ColladaScene(void);

    // Current coordinate frame orientation mode, depending on the DCC tools.
    enum OrientationMode
    {
        OM_Y_UP,
        OM_Z_UP,
        OM_X_UP
    };

    // Node's transformation type.
    enum TransformType
    {
        TT_SCALE,
        TT_ROTATE,
        TT_TRANSLATE,
        TT_MATRIX,
        TT_LOOKAT,
        TT_SKEW,
        TT_UNKNOWN
    };

    enum SkinEffect
    {
        SE_DEFAULT,
        SE_MATERIAL,
        SE_MATERIALTEXTURE,
        SE_UNKNOWN
    };

    // Load a COLLADA DOM file, then create a Swing Engine scene graph base on
    // COLLADA runtime scene graph.
    void Load(const char* acFilename);

    // Get scene graph root node.
    Node* GetScene(void);

    // Member access.
    int GetImageCount(void) const;
    Image* GetImage(const char* acName);
    Image* GetImage(int i);
    ColladaEffect* GetEffect(const char* acName);
    ColladaMaterial* GetMaterial(const char* acName);
    ColladaInstanceMaterial* GetInstanceMaterial(const char* acName);
    Node* GetNode(const char* acName);
    Node* GetGeometry(const char* acName);
    Light* GetLight(const char* acName);
    Camera* GetCamera(const char* acName);

private:
    // This helper class holds the relationship between a Swing Engine bone node
    // and a COLLADA joint node.
    class Bone
    {
    public:
        Bone(void)
        {
            BoneNode = 0;
            BoneDomNode = 0;
        }

        Node* BoneNode;
        domNode* BoneDomNode;
    };

    // This helper class represents the weight of a bone that is applied to a 
    // specific vertex.
    class BoneWeight
    {
    public:
        BoneWeight(void)
        {
            BoneID = -1;
            Weight = 0.0f;
        }

        bool operator == (const BoneWeight& rBoneWeight) const
        {
            return Weight == rBoneWeight.Weight;
        }
        bool operator < (const BoneWeight& rBoneWeight) const
        {
            return Weight < rBoneWeight.Weight;
        }

        int BoneID;
        float Weight;
    };

    // Entry point.
    bool LoadScene(domVisual_sceneRef spDomVisualScene);

    // COLLADA mesh Triangulation.
    unsigned int GetMaxOffset(domInputLocalOffset_Array& rInputArray);
    void CreateTrianglesFromPolygons(domMesh* pDomMesh, 
        domPolygons* pDomPolygons);
    void CreateTrianglesFromPolylist(domMesh* pDomMesh, 
        domPolylist* pDomPolylist);
    void Triangulate(DAE* pDAE);

    // Transform the input DCC coordinate to Swing Engine coordinate.
    // Say, from a right-handed based system to Swing Engine left-handed based
    // system.
    Vector3f GetTransformedVector(float fX, float fY, float fZ);

    // Node stuff.
    Node* LoadNode(domNodeRef spDomNode, Node* pParentNode);
    TransformType GetTransformType(char* acType);
    void GetLocalTransformation(Node* pNode, domNodeRef spDomNode);
    TriMesh* CreateJointMesh(const char* acJointName, float fSize = 0.25f);
    domNode* GetDomNodeBySID(domNodeRef spDomNode, xsNCName strSID);
    Node* GetBoneNodeByDomNode(domNode* pDomNode);

    // Geometry stuff.
    Node* LoadGeometry(domGeometryRef spDomGeometry);
    Node* LoadInstanceGeometry(domInstance_geometryRef spLib);
    void PackVertices(ColladaUnimaterialMesh* pUniMesh,
        domListOfFloats* pDomPositionData, domListOfUInts& rDomIndexData, 
        int iIndexCount, int iStride, int iPositionOffset, Vector3f* aNormal);
    void PackTextures(ColladaUnimaterialMesh* pUniMesh,
        domListOfFloats* pDomTCoordData, domListOfUInts& rDomIndexData, 
        int iIndexCount, int iStride, int iTCoordOffset);
    TriMesh* BuildTriangles(domTriangles* pDomTriangles);
    void ParseGeometry(Node*& rpMeshRoot, domGeometry* pDomGeometry);

    // Image stuff.
    bool LoadImageLibrary(domLibrary_imagesRef spLib);
    Image* LoadImage(domImageRef spDomImage);

    // Material stuff.
    bool LoadMaterialLibrary(domLibrary_materialsRef spLib);
    ColladaMaterial* LoadMaterial(domMaterialRef spDomMaterial);
    ColladaInstanceMaterial* LoadInstanceMaterial(
        domInstance_materialRef spLib);

    // Effect stuff.
    bool LoadEffectLibrary(domLibrary_effectsRef spLib);
    ColladaEffect* LoadEffect(domEffectRef spDomEffect);
    ColorRGB GetColor(domCommon_color_or_texture_type_complexType* pParam);
    float GetFloat(domCommon_float_or_param_type* pParam);
    Texture* GetTextureFromShaderElement(
        std::map<std::string, domCommon_newparam_type*>& rNewParams, 
        domCommon_color_or_texture_type* pShaderElement);

    // Animation stuff.
    bool LoadAnimationLibrary(domLibrary_animationsRef spLib);
    ColladaAnimation* LoadAnimation(domAnimationRef spDomAnimation);
    ColladaAnimationSource* LoadAnimationSource(domSourceRef spDomSource);
    ColladaAnimationSampler* LoadAnimationSampler(
        ColladaAnimation* pAnimation, domSamplerRef spDomSampler);
    ColladaAnimationChannel* LoadAnimationChannel(
        ColladaAnimation* pAnimation, domChannelRef spDomChannel);

    // Light stuff.
    Light* LoadLight(domLightRef spDomLight);
    ColladaInstanceLight* LoadInstanceLight(Node* pParentNode, 
        domInstance_lightRef spDomInstanceLight);
    void ParseConstant(ColladaEffect* pEffect, 
        ColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domConstant* pDomConstant);
    void ParseLambert(ColladaEffect* pEffect, 
        ColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domLambert* pDomLambert);
    void ParsePhong(ColladaEffect* pEffect, 
        ColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domPhong* pDomPhong);
    void ParseBlinn(ColladaEffect* pEffect, 
        ColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domBlinn* pDomblinn);

    // Camera stuff.
    Camera* LoadCamera(domCameraRef spDomCamera);
    ColladaInstanceCamera* LoadInstanceCamera(Node* pParentNode, 
        domInstance_cameraRef spDomInstanceCamera);

    // Controller stuff.
    Node* LoadInstanceController(domInstance_controllerRef spLib);
    void ApplyControllers(void);
    void ProcessSkin(ColladaInstanceController* pIController);
    void ProcessMorph(ColladaInstanceController* pIController);

    DAE* m_pDAE;
    ImageConverter* m_pImageConverter;
    NodePtr m_spSceneRoot;
    OrientationMode m_eOrientationMode;

    std::vector<ImagePtr> m_Images;
    std::vector<ColladaEffectPtr> m_Effects;
    std::vector<ColladaMaterialPtr> m_Materials;
    std::vector<ColladaInstanceMaterialPtr> m_InstanceMaterials;
    std::vector<ColladaInstanceLightPtr> m_InstanceLights;
    std::vector<ColladaInstanceCameraPtr> m_InstanceCameras;
    std::vector<ColladaAnimationPtr> m_Animations;
    std::map<std::string, NodePtr> m_Nodes;
    std::vector<NodePtr> m_Geometries;
    std::vector<LightPtr> m_Lights;
    std::vector<CameraPtr> m_Cameras;
    std::vector<ColladaInstanceControllerPtr> m_InstanceControllers;
    std::vector<Bone> m_Bones;
};

}

#endif