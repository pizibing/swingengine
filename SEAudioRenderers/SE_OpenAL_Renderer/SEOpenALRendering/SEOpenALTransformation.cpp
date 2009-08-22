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

#include "SEOpenALRendererPCH.h"
#include "SEOpenALRenderer.h"
#include "SEListener.h"

using namespace Swing;

//----------------------------------------------------------------------------
void OpenALRenderer::OnFrameChange()
{
    const Vector3f& rPos = m_pListener->GetLocation();
    const Vector3f& rUVector = m_pListener->GetUVector();
    const Vector3f& rDVector = m_pListener->GetDVector();
    Vector3f vec3fLookAt = rPos + rDVector;

    SE_AL_BEGIN_DEBUG_ALAPI;
    ALfloat afValue[6];
    afValue[0] = rPos.X;
    afValue[1] = rPos.Y;
    afValue[2] = -rPos.Z;
    alListenerfv(AL_POSITION, afValue);
    afValue[0] = vec3fLookAt.X;
    afValue[1] = vec3fLookAt.Y;
    afValue[2] = -vec3fLookAt.Z;
    afValue[3] = rUVector.X;
    afValue[4] = rUVector.Y;
    afValue[5] = -rUVector.Z;
    alListenerfv(AL_ORIENTATION, afValue);
    SE_AL_END_DEBUG_ALAPI;
}
//----------------------------------------------------------------------------