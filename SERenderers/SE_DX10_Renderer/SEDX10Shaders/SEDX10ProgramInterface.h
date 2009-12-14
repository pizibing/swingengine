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

#ifndef Swing_DX10ProgramInterface_H
#define Swing_DX10ProgramInterface_H

#include "SEDX10RendererLIB.h"
#include "SEDX10Utility.h"
#include "SEObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:DirectX10 shader program interface class
// Description:
// Author:Sun Che
// Date:20091202
//----------------------------------------------------------------------------
class SE_RENDERER_API DX10ProgramInterface : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // Instance must be created by this function.
    static DX10ProgramInterface* Load(CGprogram hCgProgram, 
        CGcontext hCgContext, const std::string& rPInterfaceName);
    ~DX10ProgramInterface(void);

    inline CGtype GetProgramInterfaceType(void) const;
    inline CGparameter GetParam(void) const;
    inline CGprogram GetProgram(void) const;

protected:
    DX10ProgramInterface(void);

    CGtype m_eCgType;
    CGparameter m_hCgParam;
    CGprogram m_hCgProgram;
};

typedef SmartPointer<DX10ProgramInterface> DX10ProgramInterfacePtr;

#include "SEDX10ProgramInterface.inl"

}

#endif
