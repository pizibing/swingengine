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
#include "SEColladaTransformation.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ColladaTransformation, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaTransformation, Object);

//----------------------------------------------------------------------------
ColladaTransformation::ColladaTransformation()
{
    TransType = TT_UNKNOWN;
    Animation = 0;
    memset(m_aiChannelID, 0, sizeof(m_aiChannelID));
    m_iChannelCount = 0;
}
//----------------------------------------------------------------------------
ColladaTransformation::~ColladaTransformation()
{
}
//----------------------------------------------------------------------------
void ColladaTransformation::AttachChannel(int iID)
{
    if( m_iChannelCount < MAX_CHANNEL_COUNT )
    {
        m_aiChannelID[m_iChannelCount++] = iID;
    }
}
//----------------------------------------------------------------------------
int ColladaTransformation::GetChannelCount() const
{
    return m_iChannelCount;
}
//----------------------------------------------------------------------------
int ColladaTransformation::GetChannel(int i) const
{
    SE_ASSERT( 0 <= i && i < MAX_CHANNEL_COUNT );

    return m_aiChannelID[i];
}
//----------------------------------------------------------------------------
ColladaTransformation::TransformType ColladaTransformation::GetTransformType(
    char* acType)
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