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

#ifndef Swing_DescriptorItem_H
#define Swing_DescriptorItem_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"
#include "SEObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20090420
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEDescriptorItem : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SEDescriptorItem(void);
    ~SEDescriptorItem(void);

    inline void SetInstanceName(const std::string& rInstName);
    inline const std::string& GetInstanceName(void) const;

    inline int GetTypeCount(void) const;
    void AttachTypeName(const std::string& rTypeName);
    void DetachTypeName(const std::string& rTypeName);
    void DetachTypeName(int i);
    const std::string& GetTypeName(int i) const;

    void GetDescription(std::string& rDesc) const;

    bool IsArray;

private:
    std::string m_InstanceName;
    std::vector<std::string> m_TypeNames;
};

typedef SESmartPointer<SEDescriptorItem> SEDescriptorItemPtr;

#include "SEDescriptorItem.inl"

}

#endif
