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
SmartPointer<T>::SmartPointer(T* pObject)
{
    m_pObject = pObject;

    if( m_pObject )
        m_pObject->IncrementReferences();
}
//----------------------------------------------------------------------------
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& rSmartPointer)
{
    m_pObject = rSmartPointer.m_pObject;

    if( m_pObject )
        m_pObject->IncrementReferences();
}
//----------------------------------------------------------------------------
template <class T>
SmartPointer<T>::~SmartPointer()
{
    if( m_pObject )
        m_pObject->DecrementReferences();
}
//----------------------------------------------------------------------------
template <class T>
SmartPointer<T>::operator T*() const
{
    return m_pObject;
}
//----------------------------------------------------------------------------
template <class T>
T& SmartPointer<T>::operator*() const
{
    return *m_pObject;
}
//----------------------------------------------------------------------------
template <class T>
T* SmartPointer<T>::operator->() const
{
    return m_pObject;
}
//----------------------------------------------------------------------------
template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(T* pObject)
{
    if( m_pObject != pObject )
    {
        if( pObject )
            pObject->IncrementReferences();

        if( m_pObject )
            m_pObject->DecrementReferences();

        m_pObject = pObject;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& rSmartPointer)
{
    if( m_pObject != rSmartPointer.m_pObject )
    {
        if( rSmartPointer.m_pObject )
            rSmartPointer.m_pObject->IncrementReferences();

        if( m_pObject )
            m_pObject->DecrementReferences();

        m_pObject = rSmartPointer.m_pObject;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <class T>
bool SmartPointer<T>::operator==(T* pObject) const
{
    return (m_pObject == pObject);
}
//----------------------------------------------------------------------------
template <class T>
bool SmartPointer<T>::operator!=(T* pObject) const
{
    return (m_pObject != pObject);
}
//----------------------------------------------------------------------------
template <class T>
bool SmartPointer<T>::operator==(const SmartPointer& rSmartPointer) const
{
    return (m_pObject == rSmartPointer.m_pObject);
}
//----------------------------------------------------------------------------
template <class T>
bool SmartPointer<T>::operator!=(const SmartPointer& rSmartPointer) const
{
    return (m_pObject != rSmartPointer.m_pObject);
}
//----------------------------------------------------------------------------



