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

#ifndef Swing_DX9ProgramInterfaceCatalog_H
#define Swing_DX9ProgramInterfaceCatalog_H

#include "SEDX9RendererLIB.h"
#include "SEDX9Utility.h"
#include "SEStringHashTable.h"

namespace Swing
{

class DX9ProgramInterface;

//----------------------------------------------------------------------------
// 名称:DirectX9 shader program interface资源管理类
// 说明:
// 作者:Sun Che
// 时间:20090417
//----------------------------------------------------------------------------
class SE_RENDERER_API DX9ProgramInterfaceCatalog
{
public:
    DX9ProgramInterfaceCatalog(const std::string& rName);
    ~DX9ProgramInterfaceCatalog(void);

    // 开始时我们不知道渲染器类型,
    // 在应用程序层创建了一个渲染器后,才能调用此函数来设置catalog所属渲染器,
    // 应用程序层的相关函数为WindowApplication::SetRenderer
    void SetRenderer(DX9Renderer* pRenderer);

    const std::string& GetName(void) const;
    bool Insert(DX9ProgramInterface* pProgramInterface);
    bool Remove(DX9ProgramInterface* pProgramInterface);
    DX9ProgramInterface* Find(CGprogram hCgProgram, 
        const std::string& rPInterfaceName);
    bool PrintContents(const std::string& rFileName) const;

    static void SetActive(DX9ProgramInterfaceCatalog* pActive);
    static DX9ProgramInterfaceCatalog* GetActive(void);

private:
    enum { PROGRAM_MAP_SIZE = 256 };
    std::string m_Name;
    SEStringHashTable<DX9ProgramInterface*> m_Entry;

    DX9Renderer* m_pRenderer;

    static DX9ProgramInterfaceCatalog* ms_pActive;
};

}

#endif
