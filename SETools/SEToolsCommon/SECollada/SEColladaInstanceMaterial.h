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

#ifndef Swing_ColladaInstanceMaterial_H
#define Swing_ColladaInstanceMaterial_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SEColladaMaterial.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Instance Material class
// Description: A helper class that holds a symbolic name used by a sub-mesh
//     as a material name, the class also holds a target which is pointing to
//     a COLLADA material object.
// Author:Sun Che
// Date:20090928
//----------------------------------------------------------------------------
class ColladaInstanceMaterial : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    ColladaInstanceMaterial(void);
    ~ColladaInstanceMaterial(void);

    // We store symbol attribute of <instance_material> as 
    // the name of ColladaInstanceMaterial object.  

    // These represent the material we are referencing from.
    std::string	TargetName;
    ColladaMaterial* TargetMaterial;
};

typedef SmartPointer<ColladaInstanceMaterial> ColladaInstanceMaterialPtr;

}

#endif