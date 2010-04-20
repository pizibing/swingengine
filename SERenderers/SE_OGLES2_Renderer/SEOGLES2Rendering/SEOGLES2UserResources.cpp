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
void SEOGLES2Renderer::OnReleaseRendererConstantID(void* pID)
{
    SERendererConstantID* pRCID = (SERendererConstantID*)pID;
    SE_DELETE pRCID;
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnReleaseUserConstantID(void* pID)
{
    SEUserConstantID* pUCID = (SEUserConstantID*)pID;
    SE_DELETE pUCID;
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnReleaseSamplerInformationID(void* pID)
{
    SESamplerInformationID* pSIID = (SESamplerInformationID*)pID;
    SE_DELETE pSIID;
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnCopyRendererConstantID(void* pSrcID, void** ppDstID)
{
    SERendererConstantID* pID = SE_NEW SERendererConstantID;
    pID->ID = ((SERendererConstantID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnCopyUserConstantID(void* pSrcID, void** ppDstID)
{
    SEUserConstantID* pID = SE_NEW SEUserConstantID;
    pID->ID = ((SEUserConstantID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnCopySamplerInformationID(void* pSrcID, void** 
    ppDstID)
{
    SESamplerInformationID* pID = SE_NEW SESamplerInformationID;
    pID->ID = ((SESamplerInformationID*)pSrcID)->ID;
    *ppDstID = (void*)pID;
}
//----------------------------------------------------------------------------
