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

#include "SEFoundationPCH.h"
#include "SERendererConstant.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(RendererConstant);
SE_IMPLEMENT_TERMINATE(RendererConstant);

//SE_REGISTER_INITIALIZE(RendererConstant);
//SE_REGISTER_TERMINATE(RendererConstant);

String RendererConstant::ms_StringMap[RendererConstant::MAX_TYPES+1] =
{
    "WMatrix",
    "VMatrix",
    "PMatrix",
    "WVMatrix",
    "VPMatrix",
    "WVPMatrix",
    "WMatrixT",
    "VMatrixT",
    "PMatrixT",
    "WVMatrixT",
    "VPMatrixT",
    "WVPMatrixT",
    "WMatrixI",
    "VMatrixI",
    "PMatrixI",
    "WVMatrixI",
    "VPMatrixI",
    "WVPMatrixI",
    "WMatrixIT",
    "VMatrixIT",
    "PMatrixIT",
    "WVMatrixIT",
    "VPMatrixIT",
    "WVPMatrixIT",

    "MaterialEmissive",
    "MaterialAmbient",
    "MaterialDiffuse",
    "MaterialSpecular",

    "CameraModelPosition",
    "CameraModelDirection",
    "CameraModelUp",
    "CameraModelRight",
    "CameraWorldPosition",
    "CameraWorldDirection",
    "CameraWorldUp",
    "CameraWorldRight",

    "ProjectorModelPosition",
    "ProjectorModelDirection",
    "ProjectorModelUp",
    "ProjectorModelRight",
    "ProjectorWorldPosition",
    "ProjectorWorldDirection",
    "ProjectorWorldUp",
    "ProjectorWorldRight",
    "ProjectorMatrix",

    "Light0ModelPosition",
    "Light0ModelDirection",
    "Light0WorldPosition",
    "Light0WorldDirection",
    "Light0Ambient",
    "Light0Diffuse",
    "Light0Specular",
    "Light0SpotCutoff",
    "Light0Attenuation",

    "Light1ModelPosition",
    "Light1ModelDirection",
    "Light1WorldPosition",
    "Light1WorldDirection",
    "Light1Ambient",
    "Light1Diffuse",
    "Light1Specular",
    "Light1SpotCutoff",
    "Light1Attenuation",

    "Light2ModelPosition",
    "Light2ModelDirection",
    "Light2WorldPosition",
    "Light2WorldDirection",
    "Light2Ambient",
    "Light2Diffuse",
    "Light2Specular",
    "Light2SpotCutoff",
    "Light2Attenuation",

    "Light3ModelPosition",
    "Light3ModelDirection",
    "Light3WorldPosition",
    "Light3WorldDirection",
    "Light3Ambient",
    "Light3Diffuse",
    "Light3Specular",
    "Light3SpotCutoff",
    "Light3Attenuation",

    "Light4ModelPosition",
    "Light4ModelDirection",
    "Light4WorldPosition",
    "Light4WorldDirection",
    "Light4Ambient",
    "Light4Diffuse",
    "Light4Specular",
    "Light4SpotCutoff",
    "Light4Attenuation",

    "Light5ModelPosition",
    "Light5ModelDirection",
    "Light5WorldPosition",
    "Light5WorldDirection",
    "Light5Ambient",
    "Light5Diffuse",
    "Light5Specular",
    "Light5SpotCutoff",
    "Light5Attenuation",

    "Light6ModelPosition",
    "Light6ModelDirection",
    "Light6WorldPosition",
    "Light6WorldDirection",
    "Light6Ambient",
    "Light6Diffuse",
    "Light6Specular",
    "Light6SpotCutoff",
    "Light6Attenuation",

    "Light7ModelPosition",
    "Light7ModelDirection",
    "Light7WorldPosition",
    "Light7WorldDirection",
    "Light7Ambient",
    "Light7Diffuse",
    "Light7Specular",
    "Light7SpotCutoff",
    "Light7Attenuation",

    "LightArray[0].ModelPosition",
    "LightArray[0].ModelDirection",
    "LightArray[0].WorldPosition",
    "LightArray[0].WorldDirection",
    "LightArray[0].Ambient",
    "LightArray[0].Diffuse",
    "LightArray[0].Specular",
    "LightArray[0].SpotCutoff",
    "LightArray[0].Attenuation",

    "LightArray[1].ModelPosition",
    "LightArray[1].ModelDirection",
    "LightArray[1].WorldPosition",
    "LightArray[1].WorldDirection",
    "LightArray[1].Ambient",
    "LightArray[1].Diffuse",
    "LightArray[1].Specular",
    "LightArray[1].SpotCutoff",
    "LightArray[1].Attenuation",

    "LightArray[2].ModelPosition",
    "LightArray[2].ModelDirection",
    "LightArray[2].WorldPosition",
    "LightArray[2].WorldDirection",
    "LightArray[2].Ambient",
    "LightArray[2].Diffuse",
    "LightArray[2].Specular",
    "LightArray[2].SpotCutoff",
    "LightArray[2].Attenuation",

    "LightArray[3].ModelPosition",
    "LightArray[3].ModelDirection",
    "LightArray[3].WorldPosition",
    "LightArray[3].WorldDirection",
    "LightArray[3].Ambient",
    "LightArray[3].Diffuse",
    "LightArray[3].Specular",
    "LightArray[3].SpotCutoff",
    "LightArray[3].Attenuation",

    "LightArray[4].ModelPosition",
    "LightArray[4].ModelDirection",
    "LightArray[4].WorldPosition",
    "LightArray[4].WorldDirection",
    "LightArray[4].Ambient",
    "LightArray[4].Diffuse",
    "LightArray[4].Specular",
    "LightArray[4].SpotCutoff",
    "LightArray[4].Attenuation",

    "LightArray[5].ModelPosition",
    "LightArray[5].ModelDirection",
    "LightArray[5].WorldPosition",
    "LightArray[5].WorldDirection",
    "LightArray[5].Ambient",
    "LightArray[5].Diffuse",
    "LightArray[5].Specular",
    "LightArray[5].SpotCutoff",
    "LightArray[5].Attenuation",

    "LightArray[6].ModelPosition",
    "LightArray[6].ModelDirection",
    "LightArray[6].WorldPosition",
    "LightArray[6].WorldDirection",
    "LightArray[6].Ambient",
    "LightArray[6].Diffuse",
    "LightArray[6].Specular",
    "LightArray[6].SpotCutoff",
    "LightArray[6].Attenuation",

    "LightArray[7].ModelPosition",
    "LightArray[7].ModelDirection",
    "LightArray[7].WorldPosition",
    "LightArray[7].WorldDirection",
    "LightArray[7].Ambient",
    "LightArray[7].Diffuse",
    "LightArray[7].Specular",
    "LightArray[7].SpotCutoff",
    "LightArray[7].Attenuation",

    "LightCount",

    "MAX_TYPES"
};

StringHashTable<RendererConstant::Type>* RendererConstant::ms_pTypeMap = 0;
RendererConstant::ReleaseID RendererConstant::OnReleaseID = 0;
RendererConstant::CopyID RendererConstant::OnCopyID = 0;

//----------------------------------------------------------------------------
void RendererConstant::Initialize()
{
    SE_ASSERT( ms_pTypeMap == 0 );

    ms_pTypeMap = SE_NEW StringHashTable<RendererConstant::Type>(MAX_TYPES);

    for( int i = 0; i < (int)MAX_TYPES; i++ )
    {
        ms_pTypeMap->Insert(ms_StringMap[i], (Type)i);
    }
}
//----------------------------------------------------------------------------
void RendererConstant::Terminate()
{
    SE_DELETE ms_pTypeMap;
}
//----------------------------------------------------------------------------
RendererConstant::RendererConstant(Type eType, void* pID, int iDataCount)
{
    SE_ASSERT( pID );
    SE_ASSERT( iDataCount > 0 && iDataCount <= 16 );

    m_eType = eType;
    m_pID = pID;
    m_iDataCount = iDataCount;

    memset(m_afData, 0, 16*sizeof(float));
}
//----------------------------------------------------------------------------
RendererConstant::RendererConstant(const RendererConstant& rRC)
{
    m_eType = rRC.m_eType;
    m_iDataCount = rRC.m_iDataCount;
    memcpy(m_afData, rRC.m_afData, m_iDataCount*sizeof(float));

    if( OnCopyID )
    {
        OnCopyID(rRC.m_pID, &m_pID);
    }
    else
    {
        m_pID = rRC.m_pID;
    }
}
//----------------------------------------------------------------------------
RendererConstant::~RendererConstant()
{
    if( OnReleaseID )
    {
        OnReleaseID(m_pID);
    }
}
//----------------------------------------------------------------------------
const String& RendererConstant::GetName(Type eType)
{
    return ms_StringMap[eType];
}
//----------------------------------------------------------------------------
RendererConstant::Type RendererConstant::GetType(const String& rName)
{
    Type* pType = ms_pTypeMap->Find(rName);

    if( pType )
    {
        return *pType;
    }

    return MAX_TYPES;
}
//----------------------------------------------------------------------------
