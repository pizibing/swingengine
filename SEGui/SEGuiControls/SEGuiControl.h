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

#ifndef Swing_GuiControl_H
#define Swing_GuiControl_H

#include "SEGuiLIB.h"
#include "SENode.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100604
//----------------------------------------------------------------------------
class SE_GUI_API SEGuiControl : public SENode
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // Abstract base class.
    virtual ~SEGuiControl(void);

    enum ControlType
    {
        CT_LABEL,
        CT_SPRITE,
        CT_BUTTON,
        CT_CHECKBOX,
        CT_MAX_COUNT
    };

    virtual ControlType GetControlType(void) const = 0;

protected:
    SEGuiControl(void);

};

typedef SESmartPointer<SEGuiControl> SEGuiControlPtr;

}

#endif