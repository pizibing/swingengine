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

#ifndef Swing_ColladaInstanceController_H
#define Swing_ColladaInstanceController_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SENode.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description: A helper class.
// Author:Sun Che
// Date:20091013
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API SEColladaInstanceController : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    enum ControllerType
	{
		CT_SKIN,
		CT_MORPH,
        CT_UNKNOWN
	};

    SEColladaInstanceController(ControllerType eType, domController* 
        pController, domNode* pSkeletonRoot, SENode* pMeshRoot);
    ~SEColladaInstanceController(void);

    // Member access.
    ControllerType GetControllerType(void) const;
    domController* GetController(void);
    domNode* GetSkeletonRoot(void);
    SENode* GetMeshRoot(void);

private:
    SEColladaInstanceController(void);

    ControllerType m_eControllerType;
    domController* m_pController;
    domNode* m_pSkeletonRoot;
    SENode* m_pMeshRoot;
};

typedef SESmartPointer<SEColladaInstanceController> 
    SEColladaInstanceControllerPtr;

}

#endif