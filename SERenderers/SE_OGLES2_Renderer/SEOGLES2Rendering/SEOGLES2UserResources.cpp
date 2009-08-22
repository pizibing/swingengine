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

#include "SEOGLES2RendererPCH.h"
#include "SEOGLES2Renderer.h"
#include "SEOGLES2Resources.h"

using namespace Swing;

//----------------------------------------------------------------------------
void OGLES2Renderer::OnReleaseRendererConstantID(void* pID)
{
    RendererConstantID* pRCID = (RendererConstantID*)pID;
    SE_DELETE pRCID;
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnReleaseUserConstantID(void* pID)
{
    UserConstantID* pUCID = (UserConstantID*)pID;
    SE_DELETE pUCID;
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnReleaseSamplerInformationID(void* pID)
{
    SamplerInformationID* pSIID = (SamplerInformationID*)pID;
    SE_DELETE pSIID;
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnCopyRendererConstantID(void* pSrcID, void** ppDstID)
{
    RendererConstantID* pID = SE_NEW RendererConstantID;
    pID->ID = ((RendererConstantID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnCopyUserConstantID(void* pSrcID, void** ppDstID)
{
    UserConstantID* pID = SE_NEW UserConstantID;
    pID->ID = ((UserConstantID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnCopySamplerInformationID(void* pSrcID, void** ppDstID)
{
    SamplerInformationID* pID = SE_NEW SamplerInformationID;
    pID->ID = ((SamplerInformationID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
