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

class Image;

//----------------------------------------------------------------------------
// 名称:image资源管理类
// 说明:只索引资源,不释放
// 作者:Sun Che
// 时间:20080629
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ImageCatalog
{
public:
    ImageCatalog(const std::string& rName);
    ~ImageCatalog(void);

    const std::string& GetName(void) const;
    bool Insert(Image* pImage);
    bool Remove(Image* pImage);
    Image* Find(const std::string& rImageName);
    bool PrintContents(const std::string& rFileName) const;

    static void SetActive(ImageCatalog* pActive);
    static ImageCatalog* GetActive(void);

private:
    enum { IMAGE_MAP_SIZE = 256 };
    std::string m_Name;
    StringHashTable<Image*> m_Entry;
    SEObjectPtr m_spDefaultImage;

    static const std::string ms_NullString;
    static const std::string ms_DefaultString;
    static ImageCatalog* ms_pActive;
};

}

#endif
