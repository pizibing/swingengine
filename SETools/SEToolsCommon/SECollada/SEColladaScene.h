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

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Shader Elements class
// Description:
// Author:Sun Che
// Date:20090914
//----------------------------------------------------------------------------
class ColladaShaderElements
{
public:
    domCommon_color_or_texture_type* Emission;
    domCommon_color_or_texture_type* Ambient;
    domCommon_color_or_texture_type* Diffuse;
    domCommon_color_or_texture_type* Specular;
    domCommon_float_or_param_type* Shininess;

    domCommon_color_or_texture_type* Reflective;
    domCommon_float_or_param_type* Reflectivity;
    domCommon_color_or_texture_type_complexType* Transparent;
    domCommon_float_or_param_type* Transarency;
    domCommon_float_or_param_type* Index_of_refaction;
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
	    OM_YUp,
	    OM_ZUp,
	    OM_XUp
    };

    // Load a COLLADA DOM file, then create a Swing Engine scene graph base on
    // COLLADA runtime scene graph.
    void Load(const char* acFilename);

    Image* GetImage(const char* acName);
    ShaderEffect* GetEffect(const char* acName);

private:
    // Triangulation.
    unsigned int GetMaxOffset(domInputLocalOffset_Array& rInputArray);
    void CreateTrianglesFromPolygons(domMesh* pDomMesh, 
        domPolygons* pDomPolygons);
    void CreateTrianglesFromPolylist(domMesh* pDomMesh, 
        domPolylist* pDomPolylist);
    void Triangulate(DAE* pDAE);

    bool LoadMaterialLibrary(domLibrary_materialsRef spLib);
    bool LoadImageLibrary(domLibrary_imagesRef spLib);
    bool LoadEffectLibrary(domLibrary_effectsRef spLib);
    bool LoadAnimationLibrary(domLibrary_animationsRef spLib);

    Image* LoadImage(domImageRef spDomImage);
    ShaderEffect* LoadEffect(domEffectRef spDomEffect);
    Light* LoadLight(domLightRef spDomLight);
    Camera* LoadCamera(domCameraRef spDomCamera);
    MaterialState* LoadMaterial(domMaterialRef spDomMaterial);
    void ParseGeometry(Geometry* pGeometry, domGeometry* pDomGeometry);
    Geometry* LoadGeometry(domGeometryRef spDomGeometry);
    //Texture* LoadTexture(domTextureRef spDomTexture);
    //Animation* LoadAnimation(domAnimationRef spDomAnimation);
    //Skin* LoadSkin(domSkinRef spDomSkin);
    Node*          LoadNode(domNodeRef spDomNode, Node* pParentNode);
    //Morph* LoadMorph(domMorphRef spDomMorph);
    //Controller* LoadController(domControllerRef spDomController);

    ColorRGB GetColor(domCommon_color_or_texture_type_complexType* pParam);
    void ParseBlinn(ColladaEffect* pEffect, 
        domProfile_COMMON::domTechnique::domBlinn* pDomblinn);

    std::vector<ImagePtr> m_Images;
    std::vector<ShaderEffectPtr> m_Effects;
    //std::vector<Geometry*> Geometries;
    //std::vector<Light*> Lights;
    //std::vector<Camera*> Cameras;
    //std::vector<Material*> Materials;
    //std::vector<Texture*> Textures;
    //std::vector<Shader*> Shaders;
    //std::vector<Controller*> Controllers;
    //std::vector<Animation*> Animations;
    //std::map<std::string, Node*> Nodes;

    DAE* m_pDAE;
    ImageConverter* m_pImageConverter;

    OrientationMode m_eOrientationMode;
};

}

#endif