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

#include "SEToolsCommonPCH.h"
#include "SEColladaScene.h"
#include "SEColladaTransformation.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEColladaTransformation, SEObject);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEColladaTransformation, SEObject);

//----------------------------------------------------------------------------
SEColladaTransformation::SEColladaTransformation()
{
    TransType = TT_UNKNOWN;
    Animation = 0;
    memset(m_aiChannelID, 0, sizeof(m_aiChannelID));
    m_iChannelCount = 0;
}
//----------------------------------------------------------------------------
SEColladaTransformation::~SEColladaTransformation()
{
}
//----------------------------------------------------------------------------
void SEColladaTransformation::AttachChannel(int iID)
{
    if( m_iChannelCount < MAX_CHANNEL_COUNT )
    {
        m_aiChannelID[m_iChannelCount++] = iID;
    }
}
//----------------------------------------------------------------------------
int SEColladaTransformation::GetChannelCount() const
{
    return m_iChannelCount;
}
//----------------------------------------------------------------------------
int SEColladaTransformation::GetChannel(int i) const
{
    SE_ASSERT( 0 <= i && i < MAX_CHANNEL_COUNT );

    return m_aiChannelID[i];
}
//----------------------------------------------------------------------------
SEColladaTransformation::TransformType 
    SEColladaTransformation::GetTransformType(char* acType)
{
    if( strcmp(acType, "scale") == 0 )
    {
        return TT_SCALE;
    }
    else if( strcmp(acType, "rotate") == 0 )
    {
        return TT_ROTATE;
    }
    else if( strcmp(acType, "translate") == 0 )
    {
        return TT_TRANSLATE;
    }
    else if( strcmp(acType, "matrix") == 0 )
    {
        return TT_MATRIX;
    }
    else if( strcmp(acType, "lookat") == 0 )
    {
        return TT_LOOKAT;
    }
    else if( strcmp(acType, "skew") == 0 )
    {
        return TT_SKEW;
    }
    else
    {
        return TT_UNKNOWN;
    }
}
//----------------------------------------------------------------------------
SETransformation SEColladaTransformation::ToTransformation()
{
    SETransformation tempRes;

    switch( TransType )
    {
    case TT_SCALE:
        {
            // Get the scale data.
            SEVector3f vec3fScale = SEColladaScene::GetTransformedVector(
                SRTData[0], SRTData[1], SRTData[2]);

            // Is this an uniform scale?
            if( vec3fScale.X == vec3fScale.Y && 
                vec3fScale.Y == vec3fScale.Z )
            {
                tempRes.SetUniformScale(vec3fScale.X);
            }
            else
            {
                tempRes.SetScale(vec3fScale);
            }
        }
        break;

    case TT_ROTATE:
        {
            // Get the rotation data.
            SEVector3f vec3fRotAxis = SEColladaScene::GetTransformedVector(
                SRTData[0], SRTData[1], SRTData[2]);
            float fRotAngle = -SRTData[3]*SEMath<float>::DEG_TO_RAD;

            SEMatrix3f mat3fR(vec3fRotAxis, fRotAngle);
            tempRes.SetRotate(mat3fR);
        }
        break;

    case TT_TRANSLATE:
        {
            // Get the transation data.
            SEVector3f vec3fTrans = SEColladaScene::GetTransformedVector(
                SRTData[0], SRTData[1], SRTData[2]);

            tempRes.SetTranslate(vec3fTrans);
        }
        break;

    case TT_MATRIX:
        // TODO:
        // Support this transformation.
        SE_ASSERT( false );
        break;

    case TT_LOOKAT:
        // TODO:
        // Support this transformation.
        SE_ASSERT( false );
        break;

    case TT_SKEW:
        // TODO:
        // Support this transformation.
        SE_ASSERT( false );
        break;

    default:
        break;
    }

    return tempRes;
}
//----------------------------------------------------------------------------