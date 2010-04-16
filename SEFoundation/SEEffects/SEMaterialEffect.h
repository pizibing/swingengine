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
// 名称:material effect类
// 说明:重新设计中,不要使用.
// 作者:Sun Che
// 时间:20080820
//----------------------------------------------------------------------------
class SE_FOUNDATION_API MaterialEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    MaterialEffect(void);
    virtual ~MaterialEffect(void);

    virtual void SetPassCount(int iPassCount);

    virtual void SetGlobalState(int iPass, Renderer* pRenderer,
        bool bPrimaryEffect);
    virtual void RestoreGlobalState(int iPass, Renderer* pRenderer,
        bool bPrimaryEffect);

    void AttachPassGlobalState(int iPass, GlobalState* pState);
    void DetachPassGlobalState(int iPass, GlobalState::StateType eType);
    GlobalState* GetPassGlobalState(int iPass, 
        GlobalState::StateType eType) const;

    void ConfigureShader(void);

protected:
    // 均与m_iPassCount数对应.
    std::vector<GlobalStatePtr> m_MaterialState;
    std::vector<GlobalStatePtr> m_CullState;
    std::vector<GlobalStatePtr> m_PolygonOffsetState;
    std::vector<GlobalStatePtr> m_WireframeState;
    std::vector<GlobalStatePtr> m_StencilState;
    std::vector<GlobalStatePtr> m_ZBufferState;
};

typedef SESmartPointer<MaterialEffect> MaterialEffectPtr;

}

#endif
