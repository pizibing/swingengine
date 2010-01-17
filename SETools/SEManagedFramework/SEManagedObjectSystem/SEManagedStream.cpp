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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedStream.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedStream::ManagedStream()
{
    m_pStream = SE_NEW Stream;
}
//---------------------------------------------------------------------------
ManagedStream::~ManagedStream()
{
    SE_DELETE m_pStream;
    m_pStream = 0;
}
//---------------------------------------------------------------------------
bool ManagedStream::InsertNode(ManagedNode^ thNode)
{
    SE_NULL_ARGUMENT_CHECK(thNode, "thNode");
    Swing::Object* pObject = thNode->GetNativeNode();

    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    return m_pStream->Insert(pObject);
}
//---------------------------------------------------------------------------
bool ManagedStream::RemoveNode(ManagedNode^ thNode)
{
    SE_NULL_ARGUMENT_CHECK(thNode, "thNode");
    Swing::Object* pObject = thNode->GetNativeNode();

    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    return m_pStream->Remove(pObject);
}
//---------------------------------------------------------------------------
void ManagedStream::RemoveAll()
{
    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    m_pStream->RemoveAll();
}
//---------------------------------------------------------------------------
int ManagedStream::GetObjectCount()
{
    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    return m_pStream->GetObjectCount();
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedStream::GetNodeAt(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    Node* pNode = DynamicCast<Node>(m_pStream->GetObjectAt(i));
    if( !pNode )
    {
        return nullptr;
    }

    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
bool ManagedStream::IsTopLevelNode(ManagedNode^ thNode)
{
    SE_NULL_ARGUMENT_CHECK(thNode, "thNode");
    Swing::Object* pObject = thNode->GetNativeNode();

    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    return m_pStream->IsTopLevel(pObject);
}
//---------------------------------------------------------------------------
bool ManagedStream::Load(String^ thFileName)
{
    SE_NULL_ARGUMENT_CHECK(thFileName, "thFileName");

    const char* acFileName = ManagedUtility::StringToNativeCharBuffer(
        thFileName);
    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    bool bRes = m_pStream->Load(acFileName);
    ManagedUtility::FreeNativeCharBuffer(acFileName);

    return bRes;
}
//---------------------------------------------------------------------------
bool ManagedStream::Save(String^ thFileName)
{
    SE_NULL_ARGUMENT_CHECK(thFileName, "thFileName");

    const char* acFileName = ManagedUtility::StringToNativeCharBuffer(
        thFileName);
    SE_NULL_REFERENCE_CHECK(m_pStream, "Native pointer is null");
    bool bRes = m_pStream->Save(acFileName);
    ManagedUtility::FreeNativeCharBuffer(acFileName);

    return bRes;
}
//---------------------------------------------------------------------------
Swing::Stream* ManagedStream::GetNativeStream()
{
    return m_pStream;
}
//---------------------------------------------------------------------------