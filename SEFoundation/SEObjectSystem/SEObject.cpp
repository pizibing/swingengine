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
#include "SEController.h"
#include "SEStringTree.h"

using namespace Swing;

const SERTTI SEObject::TYPE("Swing.SEObject", 0);
unsigned int SEObject::ms_uiNextID = 0;
SEHashTable<unsigned int, SEObject*>* SEObject::InUse = 0;
char SEObject::NameAppend = '#';
SEStringHashTable<FactoryFunction>* SEObject::ms_pFactory = 0;
bool SEObject::ms_bStreamRegistered = false;

//SE_REGISTER_STREAM(SEObject);

//----------------------------------------------------------------------------
SEObject::SEObject()
{
    m_iReferences = 0;
    m_uiID = ms_uiNextID++;

    if( !InUse )
    {
        InUse = SE_NEW SEHashTable<unsigned int, SEObject*>(FACTORY_MAP_SIZE);
    }

    InUse->Insert(m_uiID, this);
}
//----------------------------------------------------------------------------
SEObject::~SEObject()
{
    SE_ASSERT( InUse );
    bool bFound = InUse->Remove(m_uiID);
    SE_ASSERT( bFound );
    (void)bFound;  // 避免编译器警告
}
//----------------------------------------------------------------------------
void SEObject::DecrementReferences()
{
    if( --m_iReferences == 0 )
    {
        SE_DELETE this;
    }
}
//----------------------------------------------------------------------------
void SEObject::PrintInUse(const char* pFileName, const char* pMessage)
{
    FILE* pFile = SESystem::SE_Fopen(pFileName, "at");
    SE_ASSERT( pFile );

    SESystem::SE_Fprintf(pFile, "%s\n", pMessage);

    SE_ASSERT( InUse );
    unsigned int uiID = 0;
    // 迭代输出所有当前object
    SEObject** ppObject = InUse->GetFirst(&uiID);
    while( ppObject )
    {
        SESystem::SE_Fprintf(pFile, "id = %6d , type = %s\n", uiID,
            (const char*)(*ppObject)->GetType().GetName());
        ppObject = InUse->GetNext(&uiID);
    }

    SESystem::SE_Fprintf(pFile, "\n\n");
    SESystem::SE_Fclose(pFile);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// copying
//----------------------------------------------------------------------------
SEObjectPtr SEObject::Copy(bool bUniqueNames) const
{
    // Save the object to a memory buffer.
    SEStream tempSaveStream;
    tempSaveStream.Insert((SEObject*)this);
    char* pBuffer = 0;
    int iBufferSize = 0;
    bool bSuccessful = tempSaveStream.Save(pBuffer, iBufferSize);
    SE_ASSERT( bSuccessful );
    if( !bSuccessful )
    {
        return 0;
    }

    // Load the object from the memory buffer.
    SEStream tempLoadStream;
    bSuccessful = tempLoadStream.Load(pBuffer, iBufferSize);
    SE_ASSERT( bSuccessful );

    if( !bSuccessful )
    {
        return 0;
    }
    SE_DELETE[] pBuffer;

    if( bUniqueNames )
    {
        // Generate unique names.
        for( int i = 0; i < tempLoadStream.GetOrderedCount(); i++ )
        {
            SEObject* pObject = tempLoadStream.GetOrderedObject(i);
            SE_ASSERT( pObject );

            const std::string& rName = pObject->GetName();
            int iLength = (int)rName.length();
            if( iLength > 0 )
            {
                // Object has a name, append a character to make it unique.
                const char* pName = rName.c_str();
                char* acNewName = SE_NEW char[iLength + 2];
                const size_t uiSize = (size_t)(iLength + 2);
                SESystem::SE_Strcpy(acNewName, uiSize, pName);
                acNewName[iLength] = NameAppend;
                acNewName[iLength+1] = 0;
                pObject->SetName(std::string(acNewName));
                SE_DELETE[] acNewName;
            }
        }
    }

    return tempLoadStream.GetObjectAt(0);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SEObject::GetObjectByName(const std::string& rName)
{
    return (rName == m_Name ? this : 0);
}
//----------------------------------------------------------------------------
void SEObject::GetAllObjectsByName(const std::string& rName, 
    std::vector<SEObject*>& rObjects)
{
    if( rName == m_Name )
    {
        rObjects.push_back(this);
    }
}
//----------------------------------------------------------------------------
SEObject* SEObject::GetObjectByID(unsigned int uiID)
{
    return (uiID == m_uiID ? this : 0);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
bool SEObject::RegisterFactory()
{
    if( !ms_bStreamRegistered )
    {
        SEMain::AddInitializer(SEObject::InitializeFactory);
        SEMain::AddTerminator(SEObject::TerminateFactory);
        ms_bStreamRegistered = true;
    }
    return ms_bStreamRegistered;
}
//----------------------------------------------------------------------------
void SEObject::InitializeFactory()
{
    if( !ms_pFactory )
    {
        ms_pFactory = SE_NEW SEStringHashTable<FactoryFunction>(
            FACTORY_MAP_SIZE);
    }
    ms_pFactory->Insert(TYPE.GetName(), (FactoryFunction)Factory);
}
//----------------------------------------------------------------------------
void SEObject::TerminateFactory()
{
    SE_DELETE ms_pFactory;
    ms_pFactory = 0;
}
//----------------------------------------------------------------------------
SEObject* SEObject::Factory(SEStream&)
{
    SE_ASSERT( false );

    return 0;
}
//----------------------------------------------------------------------------
void SEObject::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    // 获取save时存入的object内存指针,稍后用于link阶段
    SEObject* pLinkID;
    rStream.Read(pLinkID);
    rStream.InsertInMap(pLinkID, pLink);

    // 获取name
    rStream.Read(m_Name);

    SE_END_DEBUG_STREAM_LOAD(SEObject);
}
//----------------------------------------------------------------------------
void SEObject::Link(SEStream&, SEStream::SELink*)
{
    // Stub for derived classes.
}
//----------------------------------------------------------------------------
bool SEObject::Register(SEStream& rStream) const
{
    SEObject* pThis = (SEObject*)this;
    // 该object是否已插入到hash表,确保唯一性
    if( rStream.InsertInMap(pThis, 0) )
    {
        // 所有object按照深度优先的顺序,在遍历场景树时被收集,
        // 该object不能重复被收集
        rStream.InsertInOrdered(pThis);

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void SEObject::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    // RTTI name用于load时的工厂函数表查找
    rStream.Write(std::string(GetType().GetName()));

    // 该内存地址用于load/link时的object unique ID
    rStream.Write((SEObject*)this);

    // 写入name
    rStream.Write(m_Name);

    SE_END_DEBUG_STREAM_SAVE(SEObject);
}
//----------------------------------------------------------------------------
int SEObject::GetDiskUsed(const SEStreamVersion&) const
{
    int iUsed = GetType().GetDiskUsed();
    iUsed += SE_PTRSIZE(this);
    iUsed += sizeof(int) + (int)m_Name.length();

    return iUsed;
}
//----------------------------------------------------------------------------
SEStringTree* SEObject::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("this =", this));
    pTree->Append(Format("ID   =", m_uiID));
    pTree->Append(Format("refs =", m_iReferences));

    return pTree;
}
//----------------------------------------------------------------------------
