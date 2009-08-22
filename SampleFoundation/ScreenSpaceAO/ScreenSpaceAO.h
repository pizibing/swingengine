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

#ifndef Swing_ScreenSpaceAO_H
#define Swing_ScreenSpaceAO_H

#include "SEWindowApplication3.h"

using namespace Swing;

class ScreenSpaceAO : public WindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    ScreenSpaceAO(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);

protected:
    void CreateScene(void);
    Node* CreateModel(void);
    void CreateLights(void);

    NodePtr m_spScene;
    WireframeStatePtr m_spWireframe;
    Culler m_Culler;

    CameraPtr m_spScreenCamera;

    TriMeshPtr m_spScenePolygon1;
    TriMeshPtr m_spScenePolygon2;
    TriMeshPtr m_spScenePolygon3;
    TriMeshPtr m_spScenePolygon4;
    TriMeshPtr m_spScenePolygon5;
    TriMeshPtr m_spScenePolygon6;

    ImagePtr m_spSceneImageColor;
    ImagePtr m_spSceneImageNormal;
    ImagePtr m_spSceneImageDepth;
    ImagePtr m_spSSAORandomImage;

    TexturePtr m_spSceneTargetColor;
    TexturePtr m_spSceneTargetNormal;
    TexturePtr m_spSceneTargetDepth;
    TexturePtr m_spSSAORandom;

    FrameBuffer* m_pFrameBufferSceneMRT;
    ImagePtr m_spSceneImageSSAO;
    TexturePtr m_spSceneTargetSSAO;
    FrameBuffer* m_pFrameBufferSSAO;

    LightPtr m_aspLight[4];

    bool m_bShowSSAO;
    bool m_bShowSSAOBlurred;
    bool m_bShowCombined;
    bool m_bShowUnCombined;

    ScreenSpaceAOEffect* m_pSSAOEffect;
};

#endif
