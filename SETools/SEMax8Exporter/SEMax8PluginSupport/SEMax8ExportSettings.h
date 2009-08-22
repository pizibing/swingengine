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

#ifndef Swing_Max8ExportSettings_H
#define Swing_Max8ExportSettings_H

#include <wtypes.h>

//----------------------------------------------------------------------------
// 名称:Max8ExportSettings类
// 说明:
// 作者:Sun Che
// 时间:20080814
//----------------------------------------------------------------------------
class Max8ExportSettings
{
public:
    Max8ExportSettings(void);

    // object settings
    BOOL IncludeObjects;
    BOOL IncludeCameras;
    BOOL IncludeLights;
    BOOL IncludeMeshes;

    // mesh settings
    BOOL IncludeMaterials;
    BOOL IncludeNormals;
    BOOL IncludeTexCoords;
    BOOL IncludeVertexColors;
    BOOL GenerateMaps;

    // modifier settings
    BOOL IncludeModifiers;
    BOOL IncludeSkins;
    BOOL UseGPUSkin;

    // animation settings
    BOOL IncludeCurrentFrame;
    BOOL IncludeKeyFrames;
    BOOL IncludeAllFrames;
    BOOL UseLocalTime;
    int StartFrame;
    int EndFrame;
};

#endif



