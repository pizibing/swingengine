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

#ifndef Swing_ColladaInstanceLight_H
#define Swing_ColladaInstanceLight_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SENode.h"
#include "SELight.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description: A helper class that holds a Swing Engine light and a Swing 
//     Engine node which the light is instantiated from, the light uses
//     transformation of the node.
// Author:Sun Che
// Date:20091006
//----------------------------------------------------------------------------
class ColladaInstanceLight : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    ColladaInstanceLight(SENode* pParentNode, SELight* pLight);
    ~ColladaInstanceLight(void);

    // member access.
    SENode* GetParentNode(void);
    SELight* GetLight(void);

private:
    ColladaInstanceLight(void);

    SENodePtr m_spParentNode;
    SELightPtr m_spLight;
};

typedef SESmartPointer<ColladaInstanceLight> ColladaInstanceLightPtr;

}

#endif