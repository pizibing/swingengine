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

//----------------------------------------------------------------------------
template <class T>
SharedArray<T>::SharedArray(int iCount, T* pArray)
{
    m_iCount = iCount;
    m_pArray = pArray;
}
//----------------------------------------------------------------------------
template <class T>
SharedArray<T>::SharedArray(const SharedArray& rShared)
{
    m_pArray = 0;
    *this = rShared;
}
//----------------------------------------------------------------------------
template <class T>
SharedArray<T>::~SharedArray()
{
    SE_DELETE[] m_pArray;
}
//----------------------------------------------------------------------------
template <class T>
SharedArray<T>& SharedArray<T>::operator=(const SharedArray& rShared)
{
    SE_DELETE[] m_pArray;
    m_iCount = rShared.m_iCount;
    if( rShared.m_pArray )
    {
        m_pArray = SE_NEW T[m_iCount];
        for( int i = 0; i < m_iCount; i++ )
        {
            m_pArray[i] = rShared.m_pArray[i];
        }
    }
    else
    {
        m_pArray = 0;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <class T>
int SharedArray<T>::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
template <class T>
T* SharedArray<T>::GetData() const
{
    return m_pArray;
}
//----------------------------------------------------------------------------
template <class T>
SharedArray<T>::operator const T*() const
{
    return m_pArray;
}
//----------------------------------------------------------------------------
template <class T>
SharedArray<T>::operator T*()
{
    return m_pArray;
}
//----------------------------------------------------------------------------
template <class T>
const T& SharedArray<T>::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_pArray[i];
}
//----------------------------------------------------------------------------
template <class T>
T& SharedArray<T>::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_pArray[i];
}
//----------------------------------------------------------------------------
template <class T>
void SharedArray<T>::SetActiveCount(int iActiveCount)
{
    SE_ASSERT( iActiveCount >= 0 );

    m_iCount = iActiveCount;
}
//----------------------------------------------------------------------------
template <class T> 
Object* SharedArray<T>::Factory(Stream& rStream) 
{ 
    SharedArray<T>* pObject = SE_NEW SharedArray<T>; 
    Stream::Link* pLink = SE_NEW Stream::Link(pObject);
    pObject->Load(rStream, pLink);

    return pObject; 
} 
//----------------------------------------------------------------------------
template <class T> 
void SharedArray<T>::InitializeFactory() 
{ 
    if( !ms_pFactory )
    { 
        ms_pFactory = SE_NEW StringHashTable<FactoryFunction>(FACTORY_MAP_SIZE);
    } 
    ms_pFactory->Insert(TYPE.GetName(), (FactoryFunction)SharedArray<T>::Factory);
} 
//----------------------------------------------------------------------------
template <class T> 
bool SharedArray<T>::RegisterFactory() 
{ 
    if( !ms_bStreamRegistered ) 
    { 
        Main::AddInitializer(SharedArray<T>::InitializeFactory); 
        ms_bStreamRegistered = true; 
    }

    return ms_bStreamRegistered;
}
//----------------------------------------------------------------------------
template <class T>
Object* SharedArray<T>::GetObjectByName(const std::string& rName)
{
    return Object::GetObjectByName(rName);
}
//----------------------------------------------------------------------------
template <class T>
void SharedArray<T>::GetAllObjectsByName(const std::string& rName,
    std::vector<Object*>& rObjects)
{
    Object::GetAllObjectsByName(rName,rObjects);
}
//----------------------------------------------------------------------------
template <class T>
Object* SharedArray<T>::GetObjectByID(unsigned int uiID)
{
    return Object::GetObjectByID(uiID);
}
//----------------------------------------------------------------------------
template <class T>
void SharedArray<T>::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);
    rStream.Read(m_iCount);
    m_pArray = SE_NEW T[m_iCount];
    rStream.Read(m_iCount, m_pArray);

    SE_END_DEBUG_STREAM_LOAD(SharedArray<T>);
}
//----------------------------------------------------------------------------
template <class T>
void SharedArray<T>::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream,pLink);
}
//----------------------------------------------------------------------------
template <class T>
bool SharedArray<T>::Register(Stream& rStream) const
{
    return Object::Register(rStream);
}
//----------------------------------------------------------------------------
template <class T>
void SharedArray<T>::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);
    rStream.Write(m_iCount);
    rStream.Write(m_iCount, m_pArray);

    SE_END_DEBUG_STREAM_SAVE(SharedArray<T>);
}
//----------------------------------------------------------------------------
template <class T>
int SharedArray<T>::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Object::GetDiskUsed(rVersion) + sizeof(m_iCount) + m_iCount*sizeof(T);
}
//----------------------------------------------------------------------------
template <class T>
StringTree* SharedArray<T>::SaveStrings(const char* pTitle)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Object::SaveStrings());
    pTree->Append(Format(pTitle, m_iCount, m_pArray));

    return pTree;
}
//----------------------------------------------------------------------------
