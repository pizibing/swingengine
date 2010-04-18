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

#ifndef Swing_StringTree_H
#define Swing_StringTree_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SELine3.h"
#include "SEMatrix2.h"
#include "SEMatrix3.h"
#include "SEMatrix4.h"
#include "SEPlane3.h"
#include "SEQuaternion.h"

namespace Swing
{

class SEBoundingVolume;
class SEColorRGB;
class SEColorRGBA;
class SERTTI;

//----------------------------------------------------------------------------
// 名称:字符串树类
// 说明:
// 作者:Sun Che
// 时间:20080311
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEStringTree
{
public:
    SEStringTree(void);
    ~SEStringTree(void);

    // 自己的strings
    inline int GetStringCount(void) const;
    inline void SetString(int i, char* pString);
    inline char* GetString(int i);
    inline void Append(char* pString);

    // 子节点
    inline int GetChildCount(void) const;
    inline void SetChild(int i, SEStringTree* pChild);
    inline SEStringTree* GetChild(int i);
    inline void Append(SEStringTree* pChild);

    // streaming
    bool Save(const char* pFileName, int iTabSize = 4); // iTabSize是每行缩进的步进量

    static void FormatFloat(float fValue, size_t uiStringSize, char* pString);
    static void FormatDouble(double dValue, size_t uiStringSize, 
        char* pString);

private:
    // streaming(递归)
    void Save(FILE* pFile, int iLevel, int iTabSize);

    std::vector<char*> m_Strings;
    std::vector<SEStringTree*> m_Children;
};

// 内置变量类型的字符串生成函数
SE_FOUNDATION_API char* Format(const SERTTI* pRTTI, const char* pName);
SE_FOUNDATION_API char* Format(const char* pString);
SE_FOUNDATION_API char* Format(const char* pPrefix, bool);
SE_FOUNDATION_API char* Format(const char* pPrefix, char);
SE_FOUNDATION_API char* Format(const char* pPrefix, unsigned char);
SE_FOUNDATION_API char* Format(const char* pPrefix, short);
SE_FOUNDATION_API char* Format(const char* pPrefix, unsigned short);
SE_FOUNDATION_API char* Format(const char* pPrefix, int);
SE_FOUNDATION_API char* Format(const char* pPrefix, unsigned int);
SE_FOUNDATION_API char* Format(const char* pPrefix, long);
SE_FOUNDATION_API char* Format(const char* pPrefix, unsigned long);
SE_FOUNDATION_API char* Format(const char* pPrefix, float);
SE_FOUNDATION_API char* Format(const char* pPrefix, double);
SE_FOUNDATION_API char* Format(const char* pPrefix, void*);
SE_FOUNDATION_API char* Format(const char* pPrefix, const char*);

// 非内置变量类型的字符串生成函数
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEBoundingVolume*);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEColorRGBA&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEColorRGB&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SELine3f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEMatrix2f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEMatrix3f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEMatrix4f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEPlane3f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEQuaternionf&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEVector2f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEVector3f&);
SE_FOUNDATION_API char* Format(const char* pPrefix, const SEVector4f&);

template <class T>
SEStringTree* Format(const char* pTitle, int iCount, const T* pValue);

#include "SEStringTree.inl"

}

#endif
