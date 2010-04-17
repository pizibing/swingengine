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

#ifndef Swing_Stream_H
#define Swing_Stream_H

#include "SEFoundationLIB.h"
#include "SESystem.h"
#include "SEStreamVersion.h"
#include "SEStreamMCR.h"
#include "SESmartPointer.h"
#include "SEHashTable.h"

// 需要被streaming的class成员
#include "SEColorRGB.h"
#include "SEColorRGBA.h"
#include "SEMatrix2.h"
#include "SEMatrix3.h"
#include "SEMatrix4.h"
#include "SEPlane3.h"
#include "SEQuaternion.h"
#include "SETransformation.h"
#include "SEVector2.h"
#include "SEVector3.h"
#include "SEVector4.h"

namespace Swing
{

class SEObject;

//----------------------------------------------------------------------------
// 名称:串行化类
// 说明:
// 作者:Sun Che
// 时间:20080329
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEStream
{
public:
    SEStream(void);
    ~SEStream(void);

    // top level object操作
    bool Insert(SEObject* pObject);
    bool Remove(SEObject* pObject);
    void RemoveAll(void);
    int GetObjectCount(void);
    SEObject* GetObjectAt(int i) const;
    bool IsTopLevel(const SEObject* pObject);

    // 内存load/save
    bool Load(char* pBuffer, int iSize);
    bool Save(char*& rpBuffer, int& riSize);

    // 文件load/save
    bool Load(const char* pFileName);
    bool Save(const char* pFileName);

    // 对unique object列表的访问,列表元素顺序依据register阶段的深度优先遍历顺序,
    // 可以在load或save调用后访问该列表,
    // 如果在load之后访问,则通过GetOrderedObject对列表元素的修改是有效的,
    // 如果在save之后访问,则通过GetOrderedObject对列表元素的修改将不会影响
    // save结果,而只改变原始对象实例.
    inline int GetOrderedCount(void) const;
    inline SEObject* GetOrderedObject(int i) const;

    // 支持disk usage
    int GetDiskUsed(void) const;

    // file save (ASCII text)
    bool SaveText(const char* pFileName, int iTabSize = 4);

    // 返回最近一次文件load操作的文件版本,
    // 如果没有load过文件,则返回值为-1
    inline SEStreamVersion GetVersion(void) const;

    // link类
    class SE_FOUNDATION_API Link
    {
    public:
        Link(SEObject* pObject);

	public:
        void SetObject(SEObject* pObject);
        SEObject* GetObject(void);

        int GetCount(void) const;
        SEObject* GetLinkID(void);

        void Add(SEObject* pLinkID);

    protected:
        SEObject* m_pObject;
        int m_iCurrent;
        std::vector<SEObject*> m_LinkID;
    };

protected:
    friend class SEObject;

    bool InsertInMap(SEObject* pObject, Link* pLink);
    void InsertInOrdered(SEObject* pObject);

    // 最近一次文件读取的版本
    SEStreamVersion m_Version;

    // top level object列表
    std::vector<SEObject*> m_pTopLevel;

    // save时使用的对象注册表,
    // 使用此表的目的在于快速检索出该对象是否已经注册过
    mutable HashTable<SEObject*, Link*> m_Map;

    // 唯一对象列表,由scene graph在register阶段生成,
    // 用于确保对象基于深度优先的遍历顺序存储,
    // 如果对象基于hash表顺序存储(m_Map),
    // 则对象顺序将会因每次程序运行时内存地址分配问题造成顺序不唯一
    mutable std::vector<SEObject*> m_Ordered;

    // read/write操作总是应用于内存buffer,
    // 目的在于减少磁盘反复读写操作开销
    int m_iBufferSize, m_iBufferNext;
    char* m_pBuffer;

    static const char* ms_pTopLevel;

// 内部使用
public:
    // 支持linking
    SEObject* GetFromMap(SEObject* pLinkID);

    // 支持debugging
    inline int GetBufferSize(void) const;
    inline int GetBufferNext(void) const;

    void Read(SEObject*& rpValue);
    void Read(int iCount, SEObject** ppValue);
    void Read(bool& rValue);
    void Read(int iCount, bool* pValue);
    void Read(char& rValue);
    void Read(int iCount, char* pValue);
    void Read(unsigned char& rValue);
    void Read(int iCount, unsigned char* pValue);
    void Read(short& rValue);
    void Read(int iCount, short* pValue);
    void Read(unsigned short& rValue);
    void Read(int iCount, unsigned short* pValue);
    void Read(int& rValue);
    void Read(int iCount, int* pValue);
    void Read(unsigned int& rValue);
    void Read(int iCount, unsigned int* pValue);
    void Read(long& rValue);
    void Read(int iCount, long* pValue);
    void Read(unsigned long& rValue);
    void Read(int iCount, unsigned long* pValue);
    void Read(float& rValue);
    void Read(int iCount, float* pValue);
    void Read(double& rValue);
    void Read(int iCount, double* pValue);

    void Read(std::string& rValue);
    void Read(int iCount, std::string* pValue);
    void Read(ColorRGB& rValue);
    void Read(int iCount, ColorRGB* pValue);
    void Read(ColorRGBA& rValue);
    void Read(int iCount, ColorRGBA* pValue);
    void Read(Matrix2f& rValue);
    void Read(int iCount, Matrix2f* pValue);
    void Read(Matrix3f& rValue);
    void Read(int iCount, Matrix3f* pValue);
    void Read(Matrix4f& rValue);
    void Read(int iCount, Matrix4f* pValue);
    void Read(Plane3f& rValue);
    void Read(int iCount, Plane3f* pValue);
    void Read(Quaternionf& rValue);
    void Read(int iCount, Quaternionf* pValue);
    void Read(SEVector2f& rValue);
    void Read(int iCount, SEVector2f* pValue);
    void Read(Vector3f& rValue);
    void Read(int iCount, Vector3f* pValue);
    void Read(Vector4f& rValue);
    void Read(int iCount, Vector4f* pValue);
    void Read(Transformation& rValue);
    void Read(int iCount, Transformation* pValue);

    void Write(const SEObject* pValue);
    void Write(int iCount, SEObject** const ppValue);
    void Write(const SESmartPointer<SEObject>& rspValue);
    void Write(int iCount, const SESmartPointer<SEObject>* pspValue);
    void Write(bool bValue);
    void Write(int iCount, const bool* pValue);
    void Write(char cValue);
    void Write(int iCount, const char* pValue);
    void Write(unsigned char ucValue);
    void Write(int iCount, const unsigned char* pValue);
    void Write(short sValue);
    void Write(int iCount, const short* pValue);
    void Write(unsigned short usValue);
    void Write(int iCount, const unsigned short* pValue);
    void Write(int iValue);
    void Write(int iCount, const int* pValue);
    void Write(unsigned int uiValue);
    void Write(int iCount, const unsigned int* pValue);
    void Write(long lValue);
    void Write(int iCount, const long* pValue);
    void Write(unsigned long ulValue);
    void Write(int iCount, const unsigned long* pValue);
    void Write(float fValue);
    void Write(int iCount, const float* pValue);
    void Write(double dValue);
    void Write(int iCount, const double* pValue);

    void Write(const std::string& rValue);
    void Write(int iCount, const std::string* pValue);
    void Write(const ColorRGB& rValue);
    void Write(int iCount, const ColorRGB* pValue);
    void Write(const ColorRGBA& rValue);
    void Write(int iCount, const ColorRGBA* pValue);
    void Write(const Matrix2f& rValue);
    void Write(int iCount, const Matrix2f* pValue);
    void Write(const Matrix3f& rValue);
    void Write(int iCount, const Matrix3f* pValue);
    void Write(const Matrix4f& rValue);
    void Write(int iCount, const Matrix4f* pValue);
    void Write(const Plane3f& rValue);
    void Write(int iCount, const Plane3f* pValue);
    void Write(const Quaternionf& rValue);
    void Write(int iCount, const Quaternionf* pValue);
    void Write(const SEVector2f& rValue);
    void Write(int iCount, const SEVector2f* pValue);
    void Write(const Vector3f& rValue);
    void Write(int iCount, const Vector3f* pValue);
    void Write(const Vector4f& rValue);
    void Write(int iCount, const Vector4f* pValue);
    void Write(const Transformation& rValue);
    void Write(int iCount, const Transformation* pValue);
};

typedef SEObject* (*FactoryFunction)(SEStream&);

#include "SEStream.inl"

}

#endif
