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

#ifndef Swing_ImageCatalog_H
#define Swing_ImageCatalog_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEMainMCR.h"
#include "SEStringHashTable.h"

namespace Swing
{

class SEImage;

//----------------------------------------------------------------------------
// Description:只索引资源,不释放
// Author:Sun Che
// Date:20080629
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEImageCatalog
{
public:
    SEImageCatalog(const std::string& rName);
    ~SEImageCatalog(void);

    const std::string& GetName(void) const;
    bool Insert(SEImage* pImage);
    bool Remove(SEImage* pImage);
    SEImage* Find(const std::string& rImageName);
    bool PrintContents(const std::string& rFileName) const;

    static void SetActive(SEImageCatalog* pActive);
    static SEImageCatalog* GetActive(void);

private:
    enum { IMAGE_MAP_SIZE = 256 };
    std::string m_Name;
    SEStringHashTable<SEImage*> m_Entry;
    SEObjectPtr m_spDefaultImage;

    static const std::string ms_NullString;
    static const std::string ms_DefaultString;
    static SEImageCatalog* ms_pActive;
};

}

#endif
