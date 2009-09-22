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

#ifndef Swing_ColladaInputArray_H
#define Swing_ColladaInputArray_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Input Array class
// Description:a helper class
// Author:Sun Che
// Date:20090922
//----------------------------------------------------------------------------
class ColladaInputArray
{
public:
    ColladaInputArray(domInputLocalOffset_Array& rDomInputs);
    ~ColladaInputArray(void);

    inline int GetMaxOffset(void) const;
    inline int GetPositionOffset(void) const;
    inline int GetNormalOffset(void) const;
    inline int GetTexCoord0Offset(void) const;

    inline domListOfFloats* GetPositionData(void);
    inline domListOfFloats* GetNormalData(void);
    inline domListOfFloats* GetTexCoord0Data(void);

private:
    ColladaInputArray(void);

    // Initialization of member data.
    void SetInputs(domInputLocalOffset_Array& rDomInputs);

    int m_iMaxOffset;
    int m_iPosition;
    int m_iNormal;
    int m_iTexCoord0;

    domListOfFloats* m_pDomPositionData;
    domListOfFloats* m_pDomNormalData;
    domListOfFloats* m_pDomTexCoord0Data;
};

#include "SEColladaInputArray.inl"

}

#endif