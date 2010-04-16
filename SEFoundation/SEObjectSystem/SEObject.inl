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
inline const SERTTI& SEObject::GetType() const
{
    return TYPE;
}
//----------------------------------------------------------------------------
inline bool SEObject::IsExactly(const SERTTI& rType) const
{
    return GetType().IsExactly(rType);
}
//----------------------------------------------------------------------------
inline bool SEObject::IsDerived(const SERTTI& rType) const
{
    return GetType().IsDerived(rType);
}
//----------------------------------------------------------------------------
inline bool SEObject::IsExactlyTypeOf(const SEObject* pObject) const
{
    return pObject && GetType().IsExactly(pObject->GetType());
}
//----------------------------------------------------------------------------
inline bool SEObject::IsDerivedTypeOf(const SEObject* pObject) const
{
    return pObject && GetType().IsDerived(pObject->GetType());
}
//----------------------------------------------------------------------------
template <class T>
T* StaticCast(SEObject* pObject)
{
    return (T*)pObject;
}
//----------------------------------------------------------------------------
template <class T>
const T* StaticCast(const SEObject* pObject)
{
    return (const T*)pObject;
}
//----------------------------------------------------------------------------
template <class T>
T* DynamicCast(SEObject* pObject)
{
    return pObject && pObject->IsDerived(T::TYPE) ? (T*)pObject : 0;
}
//----------------------------------------------------------------------------
template <class T>
const T* DynamicCast(const SEObject* pObject)
{
    return pObject && pObject->IsDerived(T::TYPE) ? (const T*)pObject : 0;
}
//----------------------------------------------------------------------------
inline void SEObject::SetName(const std::string& rName)
{
    m_Name = rName;
}
//----------------------------------------------------------------------------
inline const std::string& SEObject::GetName() const
{
    return m_Name;
}
//----------------------------------------------------------------------------
inline unsigned int SEObject::GetID() const
{
    return m_uiID;
}
//----------------------------------------------------------------------------
inline unsigned int SEObject::GetNextID()
{
    return ms_uiNextID;
}
//----------------------------------------------------------------------------
inline void SEObject::IncrementReferences()
{
    m_iReferences++;
}
//----------------------------------------------------------------------------
inline int SEObject::GetReferences() const
{
    return m_iReferences;
}
//----------------------------------------------------------------------------
