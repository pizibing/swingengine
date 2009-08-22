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

#ifndef Swing_BumpMaps_H
#define Swing_BumpMaps_H

#include "SEWindowApplication3.h"

using namespace Swing;

class BumpMaps : public WindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    BumpMaps(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);

protected:
    void CreateScene(void);
    void CreateLights(void);
    Node* CreateModel(void);
    void UpdateEffects(void);

    NodePtr m_spScene;
    TriMeshPtr m_spMesh;
    WireframeStatePtr m_spWireframe;
    Culler m_Culler;

    // L1     =   4 combinations
    // L2     =  10 combinations
    // L3     =  20 combinations
    // L4     =  35 combinations
    // L5     =  56 combinations
    // L6     =  84 combinations
    // L7     = 120 combinations
    // L8     = 165 combinations
    // Total  = 494 combinations
    int m_iACount, m_iDCount, m_iPCount, m_iSCount;
    LightPtr m_aspALight[8];
    LightPtr m_aspDLight[8];
    LightPtr m_aspPLight[8];
    LightPtr m_aspSLight[8];

    DefaultShaderEffectPtr m_spDefaultEffect;
    int m_iActiveLight;
    int m_iLightCount;
    char m_acCaption[9];
};

#endif
