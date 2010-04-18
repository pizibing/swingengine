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

#include "SEDX9RendererPCH.h"
#include "SEDX9Renderer.h"

using namespace Swing;

// 固定管线这样做.
////----------------------------------------------------------------------------
//void SEDX9Renderer::SetMaterialState(MaterialState* pState)
//{
//    SERenderer::SetMaterialState(pState);
//
//    D3DMATERIAL9 TempMaterial;
//
//    TempMaterial.Emissive.r = pState->Emissive.R;
//    TempMaterial.Emissive.g = pState->Emissive.G;
//    TempMaterial.Emissive.b = pState->Emissive.B;
//    TempMaterial.Emissive.a = 1.0f;
//
//    TempMaterial.Ambient.r = pState->Ambient.R;
//    TempMaterial.Ambient.g = pState->Ambient.G;
//    TempMaterial.Ambient.b = pState->Ambient.B;
//    TempMaterial.Ambient.a = 1.0f;
//
//    TempMaterial.Diffuse.r = pState->Diffuse.R;
//    TempMaterial.Diffuse.g = pState->Diffuse.G;
//    TempMaterial.Diffuse.b = pState->Diffuse.B;
//    TempMaterial.Diffuse.a = pState->Alpha;
//
//    TempMaterial.Specular.r = pState->Specular.R;
//    TempMaterial.Specular.g = pState->Specular.G;
//    TempMaterial.Specular.b = pState->Specular.B;
//    TempMaterial.Specular.a = 1.0f;
// 
//    TempMaterial.Power = pState->Shininess;
//
//    ms_hResult = m_pDXDevice->SetMaterial(&TempMaterial);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//    // Enable per-vertex color which allows the system to include the
//    // color defined for individual vertices in its lighting calculations. 
//    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//    // Allow the diffuse and specular colors to come from the color
//    // information specified along with the vertex.  Note that if
//    // those particular colors are not defined along with the vertex
//    // then the colors diffuse or specular color from the specified
//    // material is used.
//    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,
//        D3DMCS_COLOR1);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE,
//        D3DMCS_COLOR2);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//    // Use the ambient and emissive colors defined in the material.
//    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,
//        D3DMCS_MATERIAL);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE,
//        D3DMCS_MATERIAL);
//    SE_ASSERT( SUCCEEDED(ms_hResult) );
//}
////----------------------------------------------------------------------------

