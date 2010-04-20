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
#include "ConstantColorController.h"
#include "DynamicMultiTextureEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ConstantColorController, SEController);
SE_IMPLEMENT_STREAM(ConstantColorController);
SE_IMPLEMENT_DEFAULT_NAME_ID(ConstantColorController, SEController);
SE_IMPLEMENT_DEFAULT_STREAM(ConstantColorController, SEController);

SE_REGISTER_STREAM(ConstantColorController);

//----------------------------------------------------------------------------
ConstantColorController::ConstantColorController()
{
}
//----------------------------------------------------------------------------
ConstantColorController::~ConstantColorController()
{
}
//----------------------------------------------------------------------------
bool ConstantColorController::Update(double dAppTime)
{
    if( !SEController::Update(dAppTime) )
    {
        return false;
    }

    DynamicMultiTextureEffect* pEffect = 
        StaticCast<DynamicMultiTextureEffect>(m_pObject);
    (void)pEffect;

    float fCtrlTime = (float)GetControlTime(dAppTime);
    pEffect->ConstantColor.X = fCtrlTime;
    pEffect->ConstantColor.Y = fCtrlTime;
    pEffect->ConstantColor.Z = fCtrlTime;

    return true;
}
//----------------------------------------------------------------------------
void ConstantColorController::SetObject(SEObject* pObject)
{
    if( pObject )
    {
        DynamicMultiTextureEffect* pEffect = 
            StaticCast<DynamicMultiTextureEffect>(pObject);
        SE_ASSERT( pEffect );
        (void)pEffect;
    }

    SEController::SetObject(pObject);
}
//----------------------------------------------------------------------------