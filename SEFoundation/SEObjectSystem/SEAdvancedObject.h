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

#ifndef Swing_AdvancedObject_H
#define Swing_AdvancedObject_H

#include "SEFoundationLIB.h"
#include "SEObject.h"

namespace Swing
{

class SEController;

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100531
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEAdvancedObject : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    ~SEAdvancedObject(void);

protected:
    // Abstract base class.
    SEAdvancedObject(void);

// Controller system.
public:
    int GetControllerCount(void) const;
    SEController* GetController(int i) const;
    void AttachController(SEController* pController);
    void DetachController(SEController* pController);
    void DetachAllControllers(void);
    bool UpdateControllers(double dAppTime);

private:
    std::vector<SEObjectPtr> m_Controllers;
};

typedef SESmartPointer<SEAdvancedObject> SEAdvancedObjectPtr;

}

#endif