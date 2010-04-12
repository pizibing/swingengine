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

    for( int i = 0; i < pSrcNode->GetControllerCount(); i++ )
    {
        pClonedObject->AttachController(pSrcNode->GetController(i));
    }

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
    pClonedObject->LightingMode = pSrcTriMesh->LightingMode;
    pClonedObject->GenerateNormals();

    for( int i = 0; i < pSrcTriMesh->GetControllerCount(); i++ )
    {
        pClonedObject->AttachController(pSrcTriMesh->GetController(i));
    }

    for( int i = 0; i < pSrcTriMesh->GetEffectCount(); i++ )
    {
        ObjectPtr spCopiedEffect = pSrcTriMesh->GetEffect(i)->Copy();
        pClonedObject->AttachEffect((Effect*)(Swing::Object*)spCopiedEffect);
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
void ManagedUtility::MaterialTextureConditioner(Swing::Node* pNode)
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
                MaterialTextureConditioner((Node*)pChild);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                Swing::TriMesh* pMesh = (TriMesh*)pChild;
                pMesh->GenerateNormals();
                pMesh->LightingMode = Swing::Geometry::GLM_USER;

                std::string tempSubName = pMesh->GetName().substr(0, 4);

                if( pMesh->GetEffectCount() > 0 )
                {
                    Swing::SkinMaterialTextureEffect* pEffect = 
                        DynamicCast<Swing::SkinMaterialTextureEffect>(
                        pMesh->GetEffect(0));
                    if( pEffect )
                    {
                        std::string tempBaseName = pEffect->GetPImageName(0, 0);
                        int iBoneCount = pEffect->GetBoneCount();
                        Swing::Node** apBones = SE_NEW Swing::Node*[iBoneCount];
                        Swing::Transformation* aOffset = 
                            SE_NEW Swing::Transformation[iBoneCount];
                        for( int i = 0; i < iBoneCount; i++ )
                        {
                            apBones[i] = pEffect->GetBones()[i];
                            aOffset[i] = pEffect->GetOffsets()[i];
                        }

                        Effect* pNewEffect = 0;
                        if( tempSubName == "Part" )
                        {
                            pNewEffect = SE_NEW SkinMaterialTexture2L1Effect(
                                tempBaseName, "wood_01", iBoneCount, apBones, 
                                aOffset);
                        }
                        else
                        {
                            pNewEffect = SE_NEW SkinMaterialTextureL1Effect(
                                tempBaseName, iBoneCount, apBones, aOffset);
                        }


                        pMesh->DetachAllEffects();
                        pMesh->AttachEffect(pNewEffect);
                    }

                    MaterialTextureEffect* pEffect2 = 
                        DynamicCast<MaterialTextureEffect>(
                        ((TriMesh*)pChild)->GetEffect(0));
                    if( pEffect2 )
                    {
                        std::string tempBaseName = pEffect2->GetPImageName(0, 0);

                        Effect* pNewEffect = 0;
                        if( tempSubName == "Part" || tempSubName == "Trun" )
                        {
                            pNewEffect = SE_NEW MaterialTexture2L1Effect(
                                tempBaseName, "wood_01");
                        }
                        else if( tempSubName == "Wall" )
                        {
                            pNewEffect = SE_NEW TextureTileL1Effect("wall_01");
                            ((TextureTileL1Effect*)pNewEffect)->TileX = 8.0f;
                            ((TextureTileL1Effect*)pNewEffect)->TileY = 8.0f;
                            ((TextureTileL1Effect*)pNewEffect)->AmbientWeight = 0.65f;
                            ((TextureTileL1Effect*)pNewEffect)->DiffuseWeight = 0.2f;
                            ((TextureTileL1Effect*)pNewEffect)->SpecularWeight = 0.01f;

                        }
                        else
                        {
                            pNewEffect = SE_NEW MaterialTextureL1Effect(
                                tempBaseName);
                        }

                        pChild->DetachAllEffects();
                        pChild->AttachEffect(pNewEffect);
                    }
                }

                if( tempSubName == "Bone" || tempSubName == "join" )
                {
                    pMesh->DetachAllEffects();
                    pMesh->Culling = Swing::Spatial::CULL_ALWAYS;
                }
                else if( tempSubName == "Glas" )
                {
                    AlphaState* pAS = SE_NEW Swing::AlphaState;
                    pAS->BlendEnabled = true;
                    pMesh->AttachGlobalState(pAS);

                    ZBufferState* pZS = SE_NEW Swing::ZBufferState;
                    pZS->Writable = false;
                    pMesh->AttachGlobalState(pZS);

                    Swing::MaterialState* pMS = 
                        (MaterialState*)pMesh->GetGlobalState(
                        Swing::GlobalState::MATERIAL);
                    if( pMS )
                    {
                        pMS->Ambient = Swing::ColorRGB(0.1f, 0.1f, 0.1f);
                        pMS->Diffuse = Swing::ColorRGB(0.1f, 0.1f, 0.1f);
                        pMS->Specular = Swing::ColorRGB(1.0f, 1.0f, 1.0f);
                        pMS->Shininess = 100.0f;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::DisableLightingConditioner(Swing::Node* pNode)
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
                DisableLightingConditioner((Node*)pChild);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                Swing::TriMesh* pMesh = (TriMesh*)pChild;
                pMesh->LightingMode = Swing::Geometry::GLM_USER;
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::ImageConditioner(Swing::Node* pNode, 
    Swing::Image* pImage)
{
    if( !pNode || !pImage )
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
                ImageConditioner((Node*)pChild, pImage);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                Swing::TriMesh* pMesh = (TriMesh*)pChild;
                if( pMesh->GetEffectCount() > 0 )
                {
                    std::string tempSubName = pMesh->GetName().substr(0, 4);

                    if( tempSubName == "Part" || tempSubName == "Trun" )
                    {
                        MaterialTexture2L1Effect* pEffect = 
                            DynamicCast<MaterialTexture2L1Effect>(
                            ((TriMesh*)pMesh)->GetEffect(0));
                        if( pEffect )
                        {
                            PixelShader* pPS = pEffect->GetPShader(0);
                            Texture* pTexture = pPS->GetTexture(1);
                            if( pTexture )
                            {
                                pPS->SetImageName(1, pImage->GetName());
                                pTexture->SetImage(pImage);
                                pTexture->Release();
                            }
                        }

                        SkinMaterialTexture2L1Effect* pEffect2 = 
                            DynamicCast<SkinMaterialTexture2L1Effect>(
                            ((TriMesh*)pMesh)->GetEffect(0));
                        if( pEffect2 )
                        {
                            PixelShader* pPS = pEffect2->GetPShader(0);
                            Texture* pTexture = pPS->GetTexture(1);
                            if( pTexture )
                            {
                                pPS->SetImageName(1, pImage->GetName());
                                pTexture->SetImage(pImage);
                                pTexture->Release();
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::WallConditioner(Swing::Node* pNode, 
    Swing::TextureTileL1Effect* pEffect)
{
    if( !pNode || !pEffect )
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
                WallConditioner((Node*)pChild, pEffect);
            }
            else if( DynamicCast<Swing::TriMesh>(pChild) )
            {
                Swing::TriMesh* pMesh = (TriMesh*)pChild;
                if( pMesh->GetEffectCount() > 0 )
                {
                    std::string tempSubName = pMesh->GetName().substr(0, 4);

                    if( tempSubName == "Wall" )
                    {
                        pMesh->DetachAllEffects();
                        pMesh->AttachEffect(pEffect);
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------