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
#include "SEColladaTransformation.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:a helper class
// Author:Sun Che
// Date:20090914
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API SEColladaShaderElements
{
public:
    SEColladaShaderElements(void)
    { 
        memset(this, 0, sizeof(SEColladaShaderElements));
    }
    ~SEColladaShaderElements(void){}

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
// Description: This is a singleton class.
// Author:Sun Che
// Date:20090914
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API SEColladaScene
{
public:
    SEColladaScene(SEImageConverter* pImageConverter);
    ~SEColladaScene(void);

    // Current coordinate frame orientation mode, depending on the DCC tools.
    enum OrientationMode
    {
        OM_Y_UP,
        OM_Z_UP,
        OM_X_UP,
        OM_UNKNOWN
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
    SENode* GetScene(void);

    // Member access.
    int GetImageCount(void) const;
    SEImage* GetImage(const char* acName);
    SEImage* GetImage(int i);
    SEColladaEffect* GetEffect(const char* acName);
    SEColladaMaterial* GetMaterial(const char* acName);
    SEColladaInstanceMaterial* GetInstanceMaterial(const char* acName);
    SENode* GetNode(const char* acName);
    SENode* GetGeometry(const char* acName);
    SELight* GetLight(const char* acName);
    SECamera* GetCamera(const char* acName);

private:
    // This helper class represents a specific type of transformation
    // happened at a specific time.
    class KeyInfo
    {
    public:
        KeyInfo(void)
        {
            Time = 0.0f;
            Type = SEColladaTransformation::TT_UNKNOWN;
        }

        bool operator == (const KeyInfo& rKeyInfo) const
        {
            return (Time == rKeyInfo.Time) && (Type == rKeyInfo.Type);
        }
        bool operator < (const KeyInfo& rKeyInfo) const
        {
            return Time < rKeyInfo.Time;
        }

        float Time;
        SEColladaTransformation::TransformType Type;
    };

    // This helper class holds the relationship between a Swing Engine bone 
    // node and a COLLADA joint node.
    class Bone
    {
    public:
        Bone(void)
        {
            BoneNode = 0;
            BoneDomNode = 0;
        }

        SENode* BoneNode;
        domNode* BoneDomNode;
    };

    // This helper class represents the weight of a bone that is applied to 
    // a specific vertex.
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

    // COLLADA mesh triangulation.
    unsigned int GetMaxOffset(domInputLocalOffset_Array& rInputArray);
    void CreateTrianglesFromPolygons(domMesh* pDomMesh, 
        domPolygons* pDomPolygons);
    void CreateTrianglesFromPolylist(domMesh* pDomMesh, 
        domPolylist* pDomPolylist);
    void Triangulate(DAE* pDAE);

    // SENode stuff.
    SENode* LoadNode(domNodeRef spDomNode, SENode* pParentNode);
    void GetLocalTransSequence(SENode* pNode, domNodeRef spDomNode, 
        std::vector<SEColladaTransformation*>& rColladaTransSequence);
    SETransformation GetLocalTransformation(
        std::vector<SEColladaTransformation*>& rColladaTransSequence,
        float fTime = 0.0f);
    SETriMesh* CreateJointMesh(const char* acJointName, float fSize = 0.25f);
    domNode* GetDomNodeBySID(domNodeRef spDomNode, xsNCName strSID);
    SENode* GetBoneNodeByDomNode(domNode* pDomNode);

    // Geometry stuff.
    SENode* LoadGeometry(domGeometryRef spDomGeometry);
    SENode* LoadInstanceGeometry(domInstance_geometryRef spLib);
    void PackVertices(SEColladaUnimaterialMesh* pUniMesh,
        domListOfFloats* pDomPositionData, domListOfUInts& rDomIndexData, 
        int iIndexCount, int iStride, int iPositionOffset, 
        SEVector3f* aNormal);
    void PackTextures(SEColladaUnimaterialMesh* pUniMesh,
        domListOfFloats* pDomTCoordData, domListOfUInts& rDomIndexData, 
        int iIndexCount, int iStride, int iTCoordOffset);
    SETriMesh* BuildTriangles(domTriangles* pDomTriangles);
    void ParseGeometry(SENode*& rpMeshRoot, domGeometry* pDomGeometry);

    // SEImage stuff.
    bool LoadImageLibrary(domLibrary_imagesRef spLib);
    SEImage* LoadImage(domImageRef spDomImage);

    // Material stuff.
    bool LoadMaterialLibrary(domLibrary_materialsRef spLib);
    SEColladaMaterial* LoadMaterial(domMaterialRef spDomMaterial);
    SEColladaInstanceMaterial* LoadInstanceMaterial(
        domInstance_materialRef spLib);

    // SEEffect stuff.
    bool LoadEffectLibrary(domLibrary_effectsRef spLib);
    SEColladaEffect* LoadEffect(domEffectRef spDomEffect);
    SEColorRGB GetColor(domCommon_color_or_texture_type_complexType* pParam);
    float GetFloat(domCommon_float_or_param_type* pParam);
    SETexture* GetTextureFromShaderElement(
        std::map<std::string, domCommon_newparam_type*>& rNewParams, 
        domCommon_color_or_texture_type* pShaderElement);

    // Animation stuff.
    bool LoadAnimationLibrary(domLibrary_animationsRef spLib);
    SEColladaAnimation* LoadAnimation(domAnimationRef spDomAnimation);
    SEColladaAnimationSource* LoadAnimationSource(domSourceRef spDomSource);
    SEColladaAnimationSampler* LoadAnimationSampler(
        SEColladaAnimation* pAnimation, domSamplerRef spDomSampler);
    SEColladaAnimationChannel* LoadAnimationChannel(
        SEColladaAnimation* pAnimation, domChannelRef spDomChannel);
    void BuildKeyFrameController(SENode* pNode,
        std::vector<SEColladaTransformation*>& rColladaTransSequence);

    // SELight stuff.
    SELight* LoadLight(domLightRef spDomLight);
    SEColladaInstanceLight* LoadInstanceLight(SENode* pParentNode, 
        domInstance_lightRef spDomInstanceLight);
    void ParseConstant(SEColladaEffect* pEffect, 
        SEColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domConstant* pDomConstant);
    void ParseLambert(SEColladaEffect* pEffect, 
        SEColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domLambert* pDomLambert);
    void ParsePhong(SEColladaEffect* pEffect, 
        SEColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domPhong* pDomPhong);
    void ParseBlinn(SEColladaEffect* pEffect, 
        SEColladaShaderElements* pShaderElements,
        domProfile_COMMON::domTechnique::domBlinn* pDomblinn);
    void ProcessLights(void);

    // SECamera stuff.
    SECamera* LoadCamera(domCameraRef spDomCamera);
    SEColladaInstanceCamera* LoadInstanceCamera(SENode* pParentNode, 
        domInstance_cameraRef spDomInstanceCamera);
    void ProcessCameras(void);

    // Controller stuff.
    SENode* LoadInstanceController(domInstance_controllerRef spLib);
    void ProcessControllers(void);
    void ProcessSkin(SEColladaInstanceController* pIController);
    void ProcessMorph(SEColladaInstanceController* pIController);

    DAE* m_pDAE;
    SEImageConverter* m_pImageConverter;
    SENodePtr m_spSceneRoot;
    static OrientationMode ms_eOrientationMode;

    std::vector<SEImagePtr> m_Images;
    std::vector<SEColladaEffectPtr> m_Effects;
    std::vector<SEColladaMaterialPtr> m_Materials;
    std::vector<SEColladaInstanceMaterialPtr> m_InstanceMaterials;
    std::vector<SEColladaInstanceLightPtr> m_InstanceLights;
    std::vector<SEColladaInstanceCameraPtr> m_InstanceCameras;
    std::vector<SEColladaAnimationPtr> m_Animations;
    std::map<std::string, SENodePtr> m_Nodes;
    std::vector<SENodePtr> m_Geometries;
    std::vector<SELightPtr> m_Lights;
    std::vector<SECameraPtr> m_Cameras;
    std::vector<SEColladaInstanceControllerPtr> m_InstanceControllers;
    std::vector<Bone> m_Bones;

// Internal use.
public:
    // Transform the input DCC coordinate to Swing Engine coordinate.Say,
    // from a right-handed based system to Swing Engine left-handed based
    // system.
    static SEVector3f GetTransformedVector(float fX, float fY, float fZ);
};

}

#endif