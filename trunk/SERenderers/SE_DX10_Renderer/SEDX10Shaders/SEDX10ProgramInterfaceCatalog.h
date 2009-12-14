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

#ifndef Swing_DX10ProgramInterfaceCatalog_H
#define Swing_DX10ProgramInterfaceCatalog_H

#include "SEDX10RendererLIB.h"
#include "SEDX10Utility.h"
#include "SEStringHashTable.h"

namespace Swing
{

class DX10ProgramInterface;

//----------------------------------------------------------------------------
// Name:DirectX10 shader program interface catalog class
// Description:
// Author:Sun Che
// Date:20091202
//----------------------------------------------------------------------------
class SE_RENDERER_API DX10ProgramInterfaceCatalog
{
public:
    DX10ProgramInterfaceCatalog(const std::string& rName);
    ~DX10ProgramInterfaceCatalog(void);

    // 开始时我们不知道渲染器类型,
    // 在应用程序层创建了一个渲染器后,才能调用此函数来设置catalog所属渲染器,
    // 应用程序层的相关函数为WindowApplication::SetRenderer
    void SetRenderer(DX10Renderer* pRenderer);

    const std::string& GetName(void) const;
    bool Insert(DX10ProgramInterface* pProgramInterface);
    bool Remove(DX10ProgramInterface* pProgramInterface);
    DX10ProgramInterface* Find(CGprogram hCgProgram, 
        const std::string& rPInterfaceName);
    bool PrintContents(const std::string& rFileName) const;

    static void SetActive(DX10ProgramInterfaceCatalog* pActive);
    static DX10ProgramInterfaceCatalog* GetActive(void);

private:
    enum { PROGRAM_MAP_SIZE = 256 };
    std::string m_Name;
    StringHashTable<DX10ProgramInterface*> m_Entry;

    DX10Renderer* m_pRenderer;

    static DX10ProgramInterfaceCatalog* ms_pActive;
};

}

#endif
