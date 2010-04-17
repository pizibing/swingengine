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

#ifndef Swing_Object_H
#define Swing_Object_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEMain.h"
#include "SERTTI.h"
#include "SENameIdMCR.h"
#include "SESmartPointer.h"
#include "SEStream.h"
#include "SEStringTree.h"
#include "SEStringHashTable.h"

namespace Swing
{

class SEController;

//----------------------------------------------------------------------------
// 名称:对象基类
// 说明:
// 作者:Sun Che
// 时间:20080329
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEObject
{
public:
    virtual ~SEObject(void);
protected:
    // 禁止被实例化,虚基类
    SEObject(void);

// RTTI系统
public:
    static const SERTTI TYPE;
    virtual const SERTTI& GetType(void) const;
    inline bool IsExactly(const SERTTI& rType) const;
    inline bool IsDerived(const SERTTI& rType) const;
    inline bool IsExactlyTypeOf(const SEObject* pObject) const;
    inline bool IsDerivedTypeOf(const SEObject* pObject) const;

// Controller系统
public:
    int GetControllerCount(void) const;
    SEController* GetController(int i) const;
    void AttachController(SEController* pController);
    void DetachController(SEController* pController);
    void DetachAllControllers(void);
    bool UpdateControllers(double dAppTime);
private:
    std::vector< SESmartPointer<SEObject> > m_Controllers;

// Copying系统
public:
    SESmartPointer<SEObject> Copy(bool bUniqueNames = true) const;
    static char NameAppend;

// Name-ID系统
public:
    inline void SetName(const std::string& rName);
    inline const std::string& GetName(void) const;
    inline unsigned int GetID(void) const;
    inline static unsigned int GetNextID(void);
    virtual SEObject* GetObjectByName(const std::string& rName);
    virtual void GetAllObjectsByName(const std::string& rName, 
        std::vector<SEObject*>& rObjects);
    virtual SEObject* GetObjectByID(unsigned int uiID);
private:
    std::string m_Name;
    unsigned int m_uiID;
    static unsigned int ms_uiNextID;

// Smart pointer系统
public:
    inline void IncrementReferences(void);
    void DecrementReferences(void);
    inline int GetReferences(void) const;
    // SEObject级的内存泄漏跟踪使用此hash表
    static SEHashTable<unsigned int, SEObject*>* InUse;
    static void PrintInUse(const char* pFileName, const char* pMessage);
private:
    int m_iReferences;

// Streaming系统
// 内部使用
public:
    enum { FACTORY_MAP_SIZE = 256 };
    static SEStringHashTable<FactoryFunction>* ms_pFactory;
    static bool RegisterFactory(void);
    static void InitializeFactory(void);
    static void TerminateFactory(void);
    static SEObject* Factory(SEStream& rStream);
    virtual void Load(SEStream& rStream, SEStream::Link* pLink);
    virtual void Link(SEStream& rStream, SEStream::Link* pLink);
    virtual bool Register(SEStream& rStream) const;
    virtual void Save(SEStream& rStream) const;
    virtual int GetDiskUsed(const SEStreamVersion& rVersion) const;
    virtual SEStringTree* SaveStrings(const char* pTitle = 0);
private:
    static bool ms_bStreamRegistered;
};

// 静态,动态类型转换
template <class T> T* StaticCast(SEObject* pObject);
template <class T> const T* StaticCast(const SEObject* pObject);
template <class T> T* DynamicCast(SEObject* pObject);
template <class T> const T* DynamicCast(const SEObject* pObject);

typedef SESmartPointer<SEObject> SEObjectPtr;

#include "SEObject.inl"

}

#endif
