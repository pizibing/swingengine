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

#ifndef Swing_MaterialEffect_H
#define Swing_MaterialEffect_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEShaderEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:重新设计中,不要使用.
// Author:Sun Che
// Date:20080820
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEMaterialEffect : public SEShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SEMaterialEffect(void);
    virtual ~SEMaterialEffect(void);

    virtual void SetPassCount(int iPassCount);

    virtual void SetGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect);
    virtual void RestoreGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect);

    void AttachPassGlobalState(int iPass, SEGlobalState* pState);
    void DetachPassGlobalState(int iPass, SEGlobalState::StateType eType);
    SEGlobalState* GetPassGlobalState(int iPass, 
        SEGlobalState::StateType eType) const;

    void ConfigureShader(void);

protected:
    // 均与m_iPassCount数对应.
    std::vector<SEGlobalStatePtr> m_MaterialState;
    std::vector<SEGlobalStatePtr> m_CullState;
    std::vector<SEGlobalStatePtr> m_PolygonOffsetState;
    std::vector<SEGlobalStatePtr> m_WireframeState;
    std::vector<SEGlobalStatePtr> m_StencilState;
    std::vector<SEGlobalStatePtr> m_ZBufferState;
};

typedef SESmartPointer<SEMaterialEffect> SEMaterialEffectPtr;

}

#endif
