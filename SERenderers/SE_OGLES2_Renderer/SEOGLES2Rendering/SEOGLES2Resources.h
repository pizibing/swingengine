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

#ifndef Swing_OGLES2Resources_H
#define Swing_OGLES2Resources_H

#include "SEOGLES2RendererLIB.h"
#include "SEOGLES2Renderer.h"
#include "SEAttributes.h"
#include "SEBindable.h"

namespace Swing
{

class SE_RENDERER_API VProgramID : public ResourceIdentifier
{
public:
    unsigned int ID;
    unsigned int Owner;
};

class SE_RENDERER_API PProgramID : public ResourceIdentifier
{
public:
    unsigned int ID;
    unsigned int Owner;
};

class SE_RENDERER_API TextureID : public ResourceIdentifier
{
public:
    unsigned int ID;
    Texture* TextureObject;
};

class SE_RENDERER_API VBufferID : public ResourceIdentifier
{
public:
    Attributes IAttr;  // multipass时,用于shader输入属性匹配性检测.
    Attributes OAttr;
    unsigned int ID;
};

class SE_RENDERER_API IBufferID : public ResourceIdentifier
{
public:
    unsigned int ID;
};

class SE_RENDERER_API ProgramData
{
public:
    unsigned int ID;
    unsigned int Owner;

    void SetPositionAttribID(unsigned int uiAttribID)
    {
        m_uiPositionAttribID = uiAttribID;
    }
    void SetNormalAttribID(unsigned int uiAttribID)
    {
        m_uiNormalAttribID = uiAttribID;
    }
    void SetColorAttribID(int iUnit, unsigned int uiAttribID)
    {
        int iMaxUnits = (int)m_ColorAttribIDs.size();
        if( iUnit >= iMaxUnits )
        {
            m_ColorAttribIDs.resize(iUnit+1);
        }

        m_ColorAttribIDs[iUnit] = uiAttribID;
    }
    void SetTCoordAttribID(int iUnit, unsigned int uiAttribID)
    {
        int iMaxUnits = (int)m_TCoordAttribIDs.size();
        if( iUnit >= iMaxUnits )
        {
            m_TCoordAttribIDs.resize(iUnit+1);
        }

        m_TCoordAttribIDs[iUnit] = uiAttribID;
    }
    unsigned int GetPositionAttribID(void) const
    {
        return m_uiPositionAttribID;
    }
    unsigned int GetNormalAttribID(void) const
    {
        return m_uiNormalAttribID;
    }
    unsigned int GetColorAttribID(int iUnit) const
    {
        SE_ASSERT( 0 <= iUnit && iUnit < (int)m_ColorAttribIDs.size() );

        return m_ColorAttribIDs[iUnit];
    }
    unsigned int GetTCoordAttribID(int iUnit) const
    {
        SE_ASSERT( 0 <= iUnit && iUnit < (int)m_TCoordAttribIDs.size() );

        return m_TCoordAttribIDs[iUnit];
    }

private:
    unsigned int m_uiPositionAttribID;
    unsigned int m_uiNormalAttribID;
    std::vector<unsigned int> m_ColorAttribIDs;
    std::vector<unsigned int> m_TCoordAttribIDs;
};

class SE_RENDERER_API RendererConstantID
{
public:
    unsigned int ID;
};

class SE_RENDERER_API UserConstantID
{
public:
    unsigned int ID;
};

class SE_RENDERER_API SamplerInformationID
{
public:
    unsigned int ID;
};

}

#endif
