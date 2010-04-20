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

#ifndef SHADOWMAPS_H
#define SHADOWMAPS_H

#include "SEWindowApplication3.h"

using namespace Swing;

class ShadowMaps : public SEWindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    ShadowMaps(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);

protected:
    void CreateScene(void);
    void CreateGround(void);
    void CreateTorus(void);
    void CreateGlobe(void);
    void CreateFlashlight(void);

    SENodePtr m_spScene, m_spShadowMapNode, m_spFlashlight;
    SETriMeshPtr m_spGround, m_spTorus, m_spGlobe, m_spLightSphere;
    SELightPtr m_spLight;
    SEWireframeStatePtr m_spWireframe;
    SEShadowMapEffectPtr m_spSMEffect;
    SEParallaxMapL1dEffectPtr m_spPMEffect;
    SECuller m_Culler;

    SECameraPtr m_spScreenCamera;
    SEImagePtr m_spSceneImage;
    SETriMeshPtr m_spScenePolygon1;
    SETexture* m_pSceneTarget1;
    SEFrameBuffer* m_pFrameBuffer;

    char* m_acCaption;
    static char* ms_aacCaptions[3];
};

#endif
