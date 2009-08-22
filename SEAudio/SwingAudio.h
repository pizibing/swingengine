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

//----------------------------------------------------------------------------
// Swing Engine's audio lib,my first step to audio programming.
// While you guys can not hear that :-), but it's really works well,any way,
// a small step,a whole new world.
//----------------------------------------------------------------------------

#ifndef Swing_AudioHead_H
#define Swing_AudioHead_H

// Audio Register
#include "SEAudioRegister.h"

// Audio Rendering
#include "SEWave.h"
#include "SEWaveCatalog.h"
#include "SEListener.h"
#include "SEAudioBindable.h"
#include "SEAudioRenderer.h"

// Object System
#include "SEWaveVersion.h"

// Scene Graph
#include "SESoundBuffer.h"
#include "SESound.h"

#endif
