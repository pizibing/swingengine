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

#include "SEFoundationPCH.h"
#include "SEObject.h"
#include "SEStream.h"

using namespace Swing;

const char* SEStream::ms_pTopLevel = "Top Level";

//----------------------------------------------------------------------------
SEStream::SEStream()
    :
    m_Map(1024)
{
    m_iBufferSize = 0;
    m_iBufferNext = 0;
    m_pBuffer = 0;
}
//----------------------------------------------------------------------------
SEStream::~SEStream()
{
    m_Map.RemoveAll();
    m_Ordered.clear();
    RemoveAll();
}
//----------------------------------------------------------------------------
bool SEStream::Insert(SEObject* pObject)
{
    if( pObject )
    {
        // 只能插入一次
        for( int i = 0; i < (int)m_pTopLevel.size(); i++ )
        {
            if( pObject == m_pTopLevel[i] )
            {
                return false;
            }
        }

        m_pTopLevel.push_back(pObject);
        pObject->IncrementReferences();

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
bool SEStream::Remove(SEObject* pObject)
{
    if( pObject )
    {
        std::vector<SEObject*>::iterator pIter = m_pTopLevel.begin();
        for( /**/; pIter != m_pTopLevel.end(); pIter++ )
        {
            if( pObject == *pIter )
            {
                m_pTopLevel.erase(pIter);
                pObject->DecrementReferences();

                return true;
            }
        }
    }

    return false;
}
//----------------------------------------------------------------------------
void SEStream::RemoveAll()
{
    for( int i = 0; i < (int)m_pTopLevel.size(); i++ )
    {
        m_pTopLevel[i]->DecrementReferences();
    }

    m_pTopLevel.clear();
}
//----------------------------------------------------------------------------
int SEStream::GetObjectCount()
{
    return (int)m_pTopLevel.size();
}
//----------------------------------------------------------------------------
SEObject* SEStream::GetObjectAt(int i) const
{
    if( 0 <= i && i < (int)m_pTopLevel.size() )
    {
        return m_pTopLevel[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
bool SEStream::IsTopLevel(const SEObject* pObject)
{
    for( int i = 0; i < (int)m_pTopLevel.size(); i++ )
    {
        if( pObject == m_pTopLevel[i] )
        {
            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
bool SEStream::Load(char* pBuffer, int iSize)
{
    if( !SEObject::ms_pFactory )
    {
        // 必须首先创建工厂函数表
        SE_ASSERT( false );

        return false;
    }

    m_Map.RemoveAll();
    m_Ordered.clear();
    // 清除之前所有top level object
    RemoveAll();

    // 初始化内部stream buffer,m_iBufferNext已经初始化为0
    m_iBufferSize = iSize;
    m_pBuffer = pBuffer;

    // 装载unique object列表
    std::string StrTopLevel(ms_pTopLevel);
    SEObject* pObject;
    while( m_iBufferNext < m_iBufferSize )
    {
        // 期望遇到"Top Level"或SERTTI name
        std::string StrTemp;
        Read(StrTemp);
        bool bTopLevel = (StrTemp == StrTopLevel);
        if( bTopLevel )
        {
            // 期望读取SERTTI name
            Read(StrTemp);
        }

        // SERTTI name必须是"Swing.xxx"
        SE_ASSERT( ((int)StrTemp.length()) >= 7 );

        // 根据SERTTI name,找到即将读取的object的工厂函数
        FactoryFunction* pFactory = SEObject::ms_pFactory->Find(StrTemp);
        if( !pFactory )
        {
            // 无法找到该类型的工厂函数,
            // 必须确保该类调用过SE_REGISTER_STREAM(someclass)
            SE_ASSERT( false );

            return false;
        }

        // 装载该object
        pObject = (*pFactory)(*this);

        // 为应用程序使用而追踪所有top level object,
        // 加入top level对象表
        if( bTopLevel )
        {
            Insert(pObject);
        }
    }

    // link阶段,为所有载入的对象建立连接关系,构成原始scene graph,
    // 维护一个允许应用程序使用的对象列表,
    // 线性迭代唯一对象hash表,为所有对象建立连接关系
    Link** ppLink = m_Map.GetFirst(&pObject);
    while( ppLink )
    {
        pObject = (*ppLink)->GetObject();  // 获取该对象当前内存地址
        pObject->Link(*this, *ppLink);     // 为该对象建立连接关系
        m_Ordered.push_back(pObject);      // 此时的顺序为迭代hash表的访问顺序
        ppLink = m_Map.GetNext(&pObject);
    }

    // 不再需要link数据
    ppLink = m_Map.GetFirst(&pObject);
    while( ppLink )
    {
        SE_DELETE *ppLink;
        ppLink = m_Map.GetNext(&pObject);
    }

    // 重置内部数据
    m_pBuffer = 0;
    m_iBufferSize = 0;
    m_iBufferNext = 0;

    return true;
}
//----------------------------------------------------------------------------
bool SEStream::Save(char*& rpBuffer, int& riSize)
{
    m_Map.RemoveAll();
    m_Ordered.clear();

    // register阶段,
    // 建立唯一对象列表
    int i;
    for( i = 0; i < (int)m_pTopLevel.size(); i++ )
    {
        m_pTopLevel[i]->Register(*this);
    }

    // 统计所有对象的磁盘字节数
    std::string StrTopLevel(ms_pTopLevel);
    int iTLGetDiskUsed = sizeof(int) + (int)StrTopLevel.length();
    m_iBufferSize = ((int)m_pTopLevel.size())*iTLGetDiskUsed;
    for( i = 0; i < (int)m_Ordered.size(); i++ )
    {
        m_iBufferSize += m_Ordered[i]->GetDiskUsed(SEStreamVersion::CURRENT);
    }

    // 申请所需内存buffer
    m_pBuffer = SE_NEW char[m_iBufferSize];
    m_iBufferNext = 0;

    // 保存唯一对象列表到内存buffer中
    for( i = 0; i < (int)m_Ordered.size(); i++ )
    {
        const SEObject* pObject = m_Ordered[i];
        if( IsTopLevel(pObject) )
        {
            Write(StrTopLevel);
        }
        pObject->Save(*this);
    }

    // 确保内存buffer填充字节总数与对象报告总数吻合
    SE_ASSERT( m_iBufferNext == m_iBufferSize );
    if( m_iBufferNext != m_iBufferSize )
    {
        // 出现不吻合,
        // 要么是某对象错误报告了所需磁盘字节数(通过GetDiskUsed函数),
        // 要么是某对象写入成员数据时出错
        SE_ASSERT( false );

        SE_DELETE[] m_pBuffer;
        rpBuffer = 0;
        riSize = 0;

        return false;
    }

    // 把内存buffer所属权传递给本函数调用者
    rpBuffer = m_pBuffer;
    riSize = m_iBufferSize;

    // 重置内部数据
    m_pBuffer = 0;
    m_iBufferSize = 0;
    m_iBufferNext = 0;

    return true;
}
//----------------------------------------------------------------------------
bool SEStream::Load(const char* pFileName)
{
    // 从磁盘载入到内存
    char* pBuffer;
    int iSize;
    if( !SESystem::SE_Load(pFileName, pBuffer, iSize) )
    {
        return false;
    }

    // 获取文件版本
    if( iSize < SEStreamVersion::LENGTH )
    {
        // 文件不存在或没有足够大小
        SE_DELETE[] pBuffer;

        return false;
    }
    m_Version = SEStreamVersion(pBuffer);
    if( !m_Version.IsValid() )
    {
        // TO DO.  This should not abort if the input stream version is less
        // than current version.

        SE_DELETE[] pBuffer;

        return false;
    }

    // 偏移到数据区,重构scene graph
    iSize -= SEStreamVersion::LENGTH;
    if( !Load(pBuffer+SEStreamVersion::LENGTH, iSize) )
    {
        SE_DELETE[] pBuffer;

        return false;
    }

    SE_DELETE[] pBuffer;

    return true;
}
//----------------------------------------------------------------------------
bool SEStream::Save(const char* pFileName)
{
    // 保存文件版本到磁盘
    if( !SESystem::SE_Save(pFileName, SEStreamVersion::LABEL, SEStreamVersion::LENGTH) )
    {
        return false;
    }

    // 分解scene graph并存储到内存buffer
    char* pBuffer;
    int iSize;
    if( !Save(pBuffer, iSize) )
    {
        return false;
    }

    // 把scene graph从内存存储到磁盘
    if( !SESystem::SE_Append(pFileName, pBuffer, iSize) )
    {
        SE_DELETE[] pBuffer;

        return false;
    }

    SE_DELETE[] pBuffer;

    return true;
}
//----------------------------------------------------------------------------
bool SEStream::SaveText(const char* pFileName, int iTabSize)
{
    SEStringTree Root;
    Root.Append(Format(pFileName));

    const int iCount = GetObjectCount();
    for( int i = 0; i < iCount; i++ )
    {
        SEObject* pObject = m_pTopLevel[i];
        SE_ASSERT( pObject );
        Root.Append(pObject->SaveStrings());
    }

    return Root.Save(pFileName, iTabSize);
}
//----------------------------------------------------------------------------
bool SEStream::InsertInMap(SEObject* pObject, Link* pLink)
{
    return m_Map.Insert(pObject, pLink);
}
//----------------------------------------------------------------------------
SEObject* SEStream::GetFromMap(SEObject* pLinkID)
{
    Link** ppLink = m_Map.Find(pLinkID);

    return (ppLink ? (*ppLink)->GetObject() : 0);
}
//----------------------------------------------------------------------------
void SEStream::InsertInOrdered(SEObject* pObject)
{
    m_Ordered.push_back(pObject);
}
//----------------------------------------------------------------------------
int SEStream::GetDiskUsed() const
{
    int i;
    for( i = 0; i < (int)m_pTopLevel.size(); i++ )
    {
        m_pTopLevel[i]->Register((SEStream&)*this);
    }

    int iSize = 0;
    for( i = 0; i < (int)m_Ordered.size(); i++ )
    {
        iSize += m_Ordered[i]->GetDiskUsed(SEStreamVersion::CURRENT);
    }

    m_Map.RemoveAll();
    m_Ordered.clear();

    return iSize;
}
//----------------------------------------------------------------------------
SEStream::Link::Link(SEObject* pObject)
{
    m_pObject = pObject;
    m_iCurrent = 0;
}
//----------------------------------------------------------------------------
void SEStream::Link::Add(SEObject* pLinkID)
{
    m_LinkID.push_back(pLinkID);
}
//----------------------------------------------------------------------------
void SEStream::Link::SetObject(SEObject* pObject)
{
    m_pObject = pObject;
}
//----------------------------------------------------------------------------
SEObject* SEStream::Link::GetObject()
{
    return m_pObject;
}
//----------------------------------------------------------------------------
int SEStream::Link::GetCount() const
{
    return (int)m_LinkID.size();
}
//----------------------------------------------------------------------------
SEObject* SEStream::Link::GetLinkID()
{
    SE_ASSERT( m_iCurrent < (int)m_LinkID.size() );

    return m_LinkID[m_iCurrent++];
}
//----------------------------------------------------------------------------
void SEStream::Read(SEObject*& rpValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rpValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, SEObject** ppValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount,
        ppValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(bool& rValue)
{
    char* pSrc = m_pBuffer + m_iBufferNext;
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    rValue = (*pSrc != 0 ? true : false);
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, bool* pValue)
{
    if( iCount > 0 )
    {
        char* pSrc = m_pBuffer + m_iBufferNext;
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        for( int i = 0; i < iCount; i++ )
        {
            pValue[i] = (pSrc[i] != 0 ? true : false);
        }
    }
}
//----------------------------------------------------------------------------
void SEStream::Read(char& rValue)
{
    char* pSrc = m_pBuffer + m_iBufferNext;
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    rValue = *pSrc;
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, char* pValue)
{
    if( iCount > 0 )
    {
        char* pSrc = m_pBuffer + m_iBufferNext;
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        size_t uiSize = (size_t)iCount;
        SESystem::SE_Memcpy(pValue, uiSize, pSrc, uiSize);
    }
}
//----------------------------------------------------------------------------
void SEStream::Read(unsigned char& rValue)
{
    unsigned char* pSrc = (unsigned char*)(m_pBuffer + m_iBufferNext);
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    rValue = *pSrc;
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, unsigned char* pValue)
{
    if( iCount > 0 )
    {
        unsigned char* pSrc = (unsigned char*)(m_pBuffer + m_iBufferNext);
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        size_t uiSize = (size_t)iCount;
        SESystem::SE_Memcpy(pValue, uiSize, pSrc, uiSize);
    }
}
//----------------------------------------------------------------------------
void SEStream::Read (short& rValue)
{
    m_iBufferNext += SESystem::SE_Read2le(m_pBuffer+m_iBufferNext,1,&rValue);
    SE_ASSERT(m_iBufferNext <= m_iBufferSize);
}
//----------------------------------------------------------------------------
void SEStream::Read (int iCount, short* pValue)
{
    m_iBufferNext += SESystem::SE_Read2le(m_pBuffer+m_iBufferNext,iCount,
        pValue);
    SE_ASSERT(m_iBufferNext <= m_iBufferSize);
}
//----------------------------------------------------------------------------
void SEStream::Read(unsigned short& rValue)
{
    m_iBufferNext += SESystem::SE_Read2le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, unsigned short* pValue)
{
    m_iBufferNext += SESystem::SE_Read2le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, int* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(unsigned int& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, unsigned int* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(long& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, long* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(unsigned long& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, unsigned long* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(float& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, float* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(double& rValue)
{
    m_iBufferNext += SESystem::SE_Read8le(m_pBuffer+m_iBufferNext, 1, &rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, double* pValue)
{
    m_iBufferNext += SESystem::SE_Read8le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(std::string& rValue)
{
    int iLength;
    Read(iLength);

    if( iLength > 0 )
    {
        char* pText = m_pBuffer + m_iBufferNext;
        m_iBufferNext += iLength;
        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        rValue.assign(pText, iLength);
    }
    else
    {
        rValue.clear();
    }
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, std::string* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Read(pValue[i]);
    }
}
//----------------------------------------------------------------------------
void SEStream::Read(ColorRGB& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 3, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, ColorRGB* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 3*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(ColorRGBA& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, ColorRGBA* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Matrix2f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Matrix2f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Matrix3f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, /*12*/9, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Matrix3f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, /*12*/9*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Matrix4f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 16, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Matrix4f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 16*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Plane3f& rValue)
{
    Read(rValue.Normal);
    Read(rValue.Constant);
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Plane3f* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Read(pValue[i].Normal);
        Read(pValue[i].Constant);
    }
}
//----------------------------------------------------------------------------
void SEStream::Read(Quaternionf& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Quaternionf* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Vector2f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 2, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Vector2f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 2*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Vector3f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 3, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Vector3f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 3*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Vector4f& rValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4, 
        (float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Vector4f* pValue)
{
    m_iBufferNext += SESystem::SE_Read4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Read(Transformation& rValue)
{
    Read(rValue.m_Matrix);
    Read(rValue.m_Translate);
    Read(rValue.m_Scale);
    Read(rValue.m_bIsIdentity);
    Read(rValue.m_bIsSRMatrix);
    Read(rValue.m_bIsUniformScale);
}
//----------------------------------------------------------------------------
void SEStream::Read(int iCount, Transformation* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Read(pValue[i].m_Matrix);
        Read(pValue[i].m_Translate);
        Read(pValue[i].m_Scale);
        Read(pValue[i].m_bIsIdentity);
        Read(pValue[i].m_bIsSRMatrix);
        Read(pValue[i].m_bIsUniformScale);
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(const SEObject* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, SEObject** const ppValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        ppValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const SESmartPointer<SEObject>& rspValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &rspValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const SESmartPointer<SEObject>* pspValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pspValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(bool bValue)
{
    char* pDst = m_pBuffer + m_iBufferNext;
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    *pDst = (bValue ? 1 : 0);
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const bool* pValue)
{
    if( iCount > 0 )
    {
        char* pDst = m_pBuffer + m_iBufferNext;
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        for( int i = 0; i < iCount; i++ )
        {
            pDst[i] = (pValue[i] ? 1 : 0);
        }
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(char cValue)
{
    char* pDst = m_pBuffer + m_iBufferNext;
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    *pDst = cValue;
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const char* pValue)
{
    if( iCount > 0 )
    {
        char* pDst = m_pBuffer + m_iBufferNext;
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        size_t uiSize = (size_t)iCount;
        SESystem::SE_Memcpy(pDst, uiSize, pValue, uiSize);
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(unsigned char ucValue)
{
    unsigned char* pDst = (unsigned char*)(m_pBuffer + m_iBufferNext);
    m_iBufferNext++;

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );

    *pDst = ucValue;
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const unsigned char* pValue)
{
    if( iCount > 0 )
    {
        unsigned char* pDst = (unsigned char*)(m_pBuffer + m_iBufferNext);
        m_iBufferNext += iCount;

        SE_ASSERT( m_iBufferNext <= m_iBufferSize );

        size_t uiSize = (size_t)iCount;
        SESystem::SE_Memcpy(pDst, uiSize, pValue, uiSize);
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(short sValue)
{
    m_iBufferNext += SESystem::SE_Write2le(m_pBuffer+m_iBufferNext, 1, &sValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const short* pValue)
{
    m_iBufferNext += SESystem::SE_Write2le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(unsigned short usValue)
{
    m_iBufferNext += SESystem::SE_Write2le(m_pBuffer+m_iBufferNext, 1, &usValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const unsigned short* pValue)
{
    m_iBufferNext += SESystem::SE_Write2le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &iValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const int* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(unsigned int uiValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &uiValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const unsigned int* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(long lValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &lValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const long* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(unsigned long ulValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &ulValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const unsigned long* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(float fValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 1, &fValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const float* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(double dValue)
{
    m_iBufferNext += SESystem::SE_Write8le(m_pBuffer+m_iBufferNext, 1, &dValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const double* pValue)
{
    m_iBufferNext += SESystem::SE_Write8le(m_pBuffer+m_iBufferNext, iCount, 
        pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const std::string& rValue)
{
    Write((int)rValue.length());
    Write((int)rValue.length(), rValue.c_str());
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const std::string* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Write(pValue[i]);
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(const ColorRGB& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 3, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const ColorRGB* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 3*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const ColorRGBA& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const ColorRGBA* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Matrix2f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Matrix2f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Matrix3f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, /*12*/9, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Matrix3f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, /*12*/9*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Matrix4f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 16, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Matrix4f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 16*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Plane3f& rValue)
{
    Write(rValue.Normal);
    Write(rValue.Constant);
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Plane3f* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Write(pValue[i].Normal);
        Write(pValue[i].Constant);
    }
}
//----------------------------------------------------------------------------
void SEStream::Write(const Quaternionf& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Quaternionf* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Vector2f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 2, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Vector2f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 2*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Vector3f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 3, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Vector3f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 3*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Vector4f& rValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4, 
        (const float*)rValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Vector4f* pValue)
{
    m_iBufferNext += SESystem::SE_Write4le(m_pBuffer+m_iBufferNext, 4*iCount, 
        (const float*)pValue);

    SE_ASSERT( m_iBufferNext <= m_iBufferSize );
}
//----------------------------------------------------------------------------
void SEStream::Write(const Transformation& rValue)
{
    Write(rValue.m_Matrix);
    Write(rValue.m_Translate);
    Write(rValue.m_Scale);
    Write(rValue.m_bIsIdentity);
    Write(rValue.m_bIsSRMatrix);
    Write(rValue.m_bIsUniformScale);
}
//----------------------------------------------------------------------------
void SEStream::Write(int iCount, const Transformation* pValue)
{
    for( int i = 0; i < iCount; i++ )
    {
        Write(pValue[i].m_Matrix);
        Write(pValue[i].m_Translate);
        Write(pValue[i].m_Scale);
        Write(pValue[i].m_bIsIdentity);
        Write(pValue[i].m_bIsSRMatrix);
        Write(pValue[i].m_bIsUniformScale);
    }
}
//----------------------------------------------------------------------------
