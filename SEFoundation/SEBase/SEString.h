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

#ifndef Swing_String_H
#define Swing_String_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:string类
// 说明:
// 作者:Sun Che
// 时间:20080308
//----------------------------------------------------------------------------
class SE_FOUNDATION_API String
{
public:
    String(const char* pText = 0);
    String(int iLength, const char* pText);
    String(const String& rString);
    ~String(void);

    inline int GetLength(void) const;
    inline operator const char*(void) const;

    char operator [] (int i) const;
    char& operator [] (int i);

    String& operator = (const String& rString);
    String& operator += (const String& rString);
    String operator + (const String& rString);

    bool operator == (const String& rString) const;
    bool operator != (const String& rString) const;
    bool operator < (const String& rString) const;
    bool operator <= (const String& rString) const;
    bool operator > (const String& rString) const;
    bool operator >= (const String& rString) const;

    operator unsigned int(void) const;// 隐式类型转换,支持hash

    // support for streaming
    inline int GetMemoryUsed(void) const;
    inline int GetDiskUsed(void) const;

    // Case-related
    String ToUpper(void) const;
    String ToLower(void) const;

private:
    inline int CompareData(const String& rString) const;

    // 字符串在内存中以空字符结尾,在写入磁盘时不保存该空字符
    int m_iLength;
    char* m_pText;
};

#include "SEString.inl"

}

#endif



