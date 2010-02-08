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
#include "SEManagedUtility.h"

using namespace Swing::Tools::ManagedFramework;
using namespace System::Runtime::InteropServices;

//---------------------------------------------------------------------------
const char* ManagedUtility::StringToNativeCharBuffer(String^ thString)
{
    if( !thString )
    {
        return 0;
    }

    // Native heap resource is allocated here.
    IntPtr pBuffer = Marshal::StringToHGlobalAnsi(thString);
    return (const char*)(void*)pBuffer;
}
//---------------------------------------------------------------------------
void ManagedUtility::FreeNativeCharBuffer(const char* acBuffer)
{
    if( !acBuffer )
    {
        return;
    }

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal((IntPtr)(void*)acBuffer);
}
//---------------------------------------------------------------------------
Swing::Node* ManagedUtility::CloneNode(Swing::Node* pSrcNode)
{
    if( !pSrcNode )
    {
        return 0;
    }

    Swing::Node* pClonedObject = SE_NEW Swing::Node;
    pClonedObject->SetName(pSrcNode->GetName());
    pClonedObject->Local = pSrcNode->Local;

    for( int i = 0; i < pSrcNode->GetCount(); i++ )
    {
        Swing::Spatial* pChild = pSrcNode->GetChild(i);

        if( pChild )
        {
            Swing::Spatial* pClonedChild = 0;

            const Swing::RTTI& rType = pChild->GetType();
            if( rType.IsExactly(Node::TYPE) )
            {
                pClonedChild = CloneNode((Node*)pChild);
            }
            else if( rType.IsExactly(TriMesh::TYPE) )
            {
                pClonedChild = CloneTriMesh((TriMesh*)pChild);
            }

            if( pClonedChild )
            {
                pClonedObject->AttachChild(pClonedChild);
            }
        }
    }

    return pClonedObject;
}
//---------------------------------------------------------------------------
Swing::TriMesh* ManagedUtility::CloneTriMesh(Swing::TriMesh* pSrcTriMesh)
{
    if( !pSrcTriMesh )
    {
        return 0;
    }

    Swing::TriMesh* pClonedObject = SE_NEW Swing::TriMesh(
        pSrcTriMesh->VBuffer, pSrcTriMesh->IBuffer);
    pClonedObject->SetName(pSrcTriMesh->GetName());
    pClonedObject->Local = pSrcTriMesh->Local;
    pClonedObject->GenerateNormals();

    for( int i = 0; i < pSrcTriMesh->GetEffectCount(); i++ )
    {
        pClonedObject->AttachEffect(pSrcTriMesh->GetEffect(i));
    }

    return pClonedObject;
}
//---------------------------------------------------------------------------
void ManagedUtility::GenerateNormalsForAll(Swing::Node* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        Swing::Spatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<Swing::Node>(pChild) )
            {
                GenerateNormalsForAll((Swing::Node*)pChild);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                ((Swing::TriMesh*)pChild)->GenerateNormals();
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::DetachAllEffectsForAll(Swing::Node* pNode)
{
    if( !pNode )
    {
        return;
    }

    pNode->DetachAllEffects();

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        Swing::Spatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<Swing::Node>(pChild) )
            {
                DetachAllEffectsForAll((Node*)pChild);
            }
            else
            {
                pChild->DetachAllEffects();
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::ModulateWithLightingEffectForAll(Swing::Node* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        Swing::Spatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<Swing::Node>(pChild) )
            {
                ModulateWithLightingEffectForAll((Node*)pChild);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                if( pChild->GetEffectCount() > 0 )
                {
                    Swing::ShaderEffect* pShaderEffect = 
                        DynamicCast<Swing::ShaderEffect>(
                        pChild->GetEffect(0));

                    if( pShaderEffect )
                    {
                        if( pShaderEffect->GetPassCount() == 0 )
                        {
                            throw gcnew Exception("Pass count is zero");
                        }

                        Swing::AlphaState* pAState = 
                            pShaderEffect->GetBlending(0);
                        pAState->SrcBlend = AlphaState::SBF_DST_COLOR;
                        pAState->DstBlend = AlphaState::DBF_ZERO;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------