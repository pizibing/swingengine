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

using namespace Swing::Tools::ManagedFramework;
using namespace System::Runtime::InteropServices;

//---------------------------------------------------------------------------
ManagedStream::ManagedStream()
{
    m_pStream = SE_NEW Swing::Stream;
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
    Swing::Object* pObject = thNode->GetNativeNode();

    return m_pStream->Insert(pObject);
}
//---------------------------------------------------------------------------
bool ManagedStream::RemoveNode(ManagedNode^ thNode)
{
    Swing::Object* pObject = thNode->GetNativeNode();

    return m_pStream->Remove(pObject);
}
//---------------------------------------------------------------------------
void ManagedStream::RemoveAll()
{
    m_pStream->RemoveAll();
}
//---------------------------------------------------------------------------
int ManagedStream::GetObjectCount()
{
    return m_pStream->GetObjectCount();
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedStream::GetNodeAt(int i)
{
    Swing::Node* pNode = DynamicCast<Swing::Node>(m_pStream->GetObjectAt(i));
    if( !pNode )
    {
        return nullptr;
    }

    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
bool ManagedStream::IsTopLevelNode(ManagedNode^ thNode)
{
    Swing::Object* pObject = thNode->GetNativeNode();

    return m_pStream->IsTopLevel(pObject);
}
//---------------------------------------------------------------------------
bool ManagedStream::Load(String^ thFileName)
{
    if( !thFileName )
    {
        throw gcnew ArgumentNullException("thFileName");
    }

    // Native heap resource is allocated here.
    IntPtr pFileName = Marshal::StringToHGlobalAnsi(thFileName);

    bool bRes = m_pStream->Load((const char*)(void*)pFileName);

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal(pFileName);

    return bRes;
}
//---------------------------------------------------------------------------
bool ManagedStream::Save(String^ thFileName)
{
    if( !thFileName )
    {
        throw gcnew ArgumentNullException("thFileName");
    }

    // Native heap resource is allocated here.
    IntPtr pFileName = Marshal::StringToHGlobalAnsi(thFileName);

    bool bRes = m_pStream->Save((const char*)(void*)pFileName);

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal(pFileName);

    return bRes;
}
//---------------------------------------------------------------------------
Swing::Stream* ManagedStream::GetNativeStream()
{
    return m_pStream;
}
//---------------------------------------------------------------------------