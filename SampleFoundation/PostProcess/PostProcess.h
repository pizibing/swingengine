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

#ifndef Swing_PostProcess_H
#define Swing_PostProcess_H

#include "SEWindowApplication3.h"

using namespace Swing;

class PostProcess : public SEWindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    PostProcess(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);

protected:
    void CreateScene(void);
    void CreateTeapot(void);
    void CreateLights(void);

    SENodePtr m_spScene;
    SETriMeshPtr m_spTeapot;
    SEWireframeStatePtr m_spWireframe;
    SECuller m_Culler;

    SECameraPtr m_spScreenCamera;
    SEImagePtr m_spSceneImage;
    SETriMeshPtr m_spScenePolygon1;
    SETriMeshPtr m_spScenePolygon2;
    SETriMeshPtr m_spScenePolygon3;
    SETexture* m_pSceneTarget1;
    SETexture* m_pSceneTarget2;
    SETexture* m_pSceneTarget3;
    SEFrameBuffer* m_pFrameBuffer1;
    SEFrameBuffer* m_pFrameBuffer2;
    SEFrameBuffer* m_pFrameBuffer3;

    SELightPtr m_aspLight[2];

    bool m_bPostProcess;
};

#endif
