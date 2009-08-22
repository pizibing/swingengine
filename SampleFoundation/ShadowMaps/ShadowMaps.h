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

class ShadowMaps : public WindowApplication3
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

    NodePtr m_spScene, m_spShadowMapNode, m_spFlashlight;
    TriMeshPtr m_spGround, m_spTorus, m_spGlobe, m_spLightSphere;
    LightPtr m_spLight;
    WireframeStatePtr m_spWireframe;
    ShadowMapEffectPtr m_spSMEffect;
    ParallaxMapL1dEffectPtr m_spPMEffect;
    Culler m_Culler;

    CameraPtr m_spScreenCamera;
    ImagePtr m_spSceneImage;
    TriMeshPtr m_spScenePolygon1;
    Texture* m_pSceneTarget1;
    FrameBuffer* m_pFrameBuffer;

    char* m_acCaption;
    static char* ms_aacCaptions[3];
};

#endif
