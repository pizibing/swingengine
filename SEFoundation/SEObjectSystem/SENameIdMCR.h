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

#ifndef Swing_NameIdMCR_H
#define Swing_NameIdMCR_H

// 一般情况下,使用者必须实现各自的GetObjectByName,GetAllObjectsByName,
// GetObjectByID函数,且这些函数要首先调用基类的相应函数.
//----------------------------------------------------------------------------
#define SE_DECLARE_NAME_ID \
public: \
    virtual SEObject* GetObjectByName(const std::string& rName); \
    virtual void GetAllObjectsByName(const std::string& rName, \
        std::vector<SEObject*>& rObjects); \
    virtual SEObject* GetObjectByID(unsigned int uiID)
//----------------------------------------------------------------------------
#define SE_IMPLEMENT_DEFAULT_NAME_ID(classname, baseclassname) \
SEObject* classname::GetObjectByName(const std::string& rName) \
{ \
    return baseclassname::GetObjectByName(rName); \
} \
\
void classname::GetAllObjectsByName(const std::string& rName, \
    std::vector<SEObject*>& rObjects) \
{ \
    baseclassname::GetAllObjectsByName(rName, rObjects); \
} \
\
SEObject* classname::GetObjectByID(unsigned int uiID) \
{ \
    return baseclassname::GetObjectByID(uiID); \
}
//----------------------------------------------------------------------------

#endif
