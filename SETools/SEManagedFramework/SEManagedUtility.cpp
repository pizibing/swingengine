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

using namespace Swing;
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
SENode* ManagedUtility::CloneNode(SENode* pSrcNode)
{
    if( !pSrcNode )
    {
        return 0;
    }

    SENode* pClonedObject = SE_NEW SENode;
    pClonedObject->SetName(pSrcNode->GetName());
    pClonedObject->Local = pSrcNode->Local;

    for( int i = 0; i < pSrcNode->GetControllerCount(); i++ )
    {
        pClonedObject->AttachController(pSrcNode->GetController(i));
    }

    for( int i = 0; i < pSrcNode->GetGlobalStateCount(); i++ )
    {
        pClonedObject->AttachGlobalState(pSrcNode->GetGlobalState(i));
    }

    for( int i = 0; i < pSrcNode->GetCount(); i++ )
    {
        SESpatial* pChild = pSrcNode->GetChild(i);

        if( pChild )
        {
            SESpatial* pClonedChild = 0;

            const SERTTI& rType = pChild->GetType();
            if( rType.IsExactly(SENode::TYPE) )
            {
                pClonedChild = CloneNode((SENode*)pChild);
            }
            else if( rType.IsExactly(SETriMesh::TYPE) )
            {
                pClonedChild = CloneTriMesh((SETriMesh*)pChild);
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
SETriMesh* ManagedUtility::CloneTriMesh(SETriMesh* pSrcTriMesh)
{
    if( !pSrcTriMesh )
    {
        return 0;
    }

    SETriMesh* pClonedObject = SE_NEW SETriMesh(pSrcTriMesh->VBuffer, 
        pSrcTriMesh->IBuffer);
    pClonedObject->SetName(pSrcTriMesh->GetName());
    pClonedObject->Local = pSrcTriMesh->Local;
    pClonedObject->LightingMode = pSrcTriMesh->LightingMode;
    pClonedObject->GenerateNormals();

    for( int i = 0; i < pSrcTriMesh->GetControllerCount(); i++ )
    {
        pClonedObject->AttachController(pSrcTriMesh->GetController(i));
    }

    for( int i = 0; i < pSrcTriMesh->GetGlobalStateCount(); i++ )
    {
        pClonedObject->AttachGlobalState(pSrcTriMesh->GetGlobalState(i));
    }

    for( int i = 0; i < pSrcTriMesh->GetEffectCount(); i++ )
    {
        SEObjectPtr spCopiedEffect = pSrcTriMesh->GetEffect(i)->Copy();
        pClonedObject->AttachEffect((SEEffect*)(SEObject*)spCopiedEffect);
    }

    return pClonedObject;
}
//---------------------------------------------------------------------------
void ManagedUtility::GenerateNormalsForAll(SENode* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                GenerateNormalsForAll((SENode*)pChild);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                ((SETriMesh*)pChild)->GenerateNormals();
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::DetachAllEffectsForAll(SENode* pNode)
{
    if( !pNode )
    {
        return;
    }

    pNode->DetachAllEffects();

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                DetachAllEffectsForAll((SENode*)pChild);
            }
            else
            {
                pChild->DetachAllEffects();
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::ModulateWithLightingEffectForAll(SENode* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                ModulateWithLightingEffectForAll((SENode*)pChild);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                if( pChild->GetEffectCount() > 0 )
                {
                    SEShaderEffect* pShaderEffect = DynamicCast<
                        SEShaderEffect>(pChild->GetEffect(0));

                    if( pShaderEffect )
                    {
                        if( pShaderEffect->GetPassCount() == 0 )
                        {
                            throw gcnew Exception("Pass count is zero");
                        }

                        SEAlphaState* pAState = 
                            pShaderEffect->GetBlending(0);
                        pAState->SrcBlend = SEAlphaState::SBF_DST_COLOR;
                        pAState->DstBlend = SEAlphaState::DBF_ZERO;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::MaterialTextureConditioner(SENode* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                MaterialTextureConditioner((SENode*)pChild);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                SETriMesh* pMesh = (SETriMesh*)pChild;
                pMesh->GenerateNormals();
                pMesh->LightingMode = SEGeometry::GLM_USER;

                std::string tempSubName = pMesh->GetName().substr(0, 4);

                if( pMesh->GetEffectCount() > 0 )
                {
                    SESkinMaterialTextureEffect* pEffect = 
                        DynamicCast<SESkinMaterialTextureEffect>(
                        pMesh->GetEffect(0));
                    if( pEffect )
                    {
                        std::string tempBaseName = pEffect->GetPImageName(
                            0, 0);
                        int iBoneCount = pEffect->GetBoneCount();
                        SENode** apBones = SE_NEW SENode*[iBoneCount];
                        SETransformation* aOffset = 
                            SE_NEW SETransformation[iBoneCount];
                        for( int i = 0; i < iBoneCount; i++ )
                        {
                            apBones[i] = pEffect->GetBones()[i];
                            aOffset[i] = pEffect->GetOffsets()[i];
                        }

                        SEEffect* pNewEffect = 0;
                        if( tempSubName == "Part" )
                        {
                            pNewEffect = SE_NEW SESkinMaterialTexture2L1Effect(
                                tempBaseName, "wood_01", iBoneCount, apBones, 
                                aOffset);
                        }
                        else
                        {
                            pNewEffect = SE_NEW SESkinMaterialTextureL1Effect(
                                tempBaseName, iBoneCount, apBones, aOffset);
                        }


                        pMesh->DetachAllEffects();
                        pMesh->AttachEffect(pNewEffect);
                    }

                    SEMaterialTextureEffect* pEffect2 = 
                        DynamicCast<SEMaterialTextureEffect>(
                        ((SETriMesh*)pChild)->GetEffect(0));
                    if( pEffect2 )
                    {
                        std::string tempBaseName = pEffect2->GetPImageName(0, 0);

                        SEEffect* pNewEffect = 0;
                        if( tempSubName == "Part" || tempSubName == "Trun" )
                        {
                            pNewEffect = SE_NEW SEMaterialTexture2L1Effect(
                                tempBaseName, "wood_01");
                        }
                        else if( tempSubName == "Wall" )
                        {
                            pNewEffect = SE_NEW SETextureTileL1Effect("wall_01");
                            ((SETextureTileL1Effect*)pNewEffect)->TileX = 8.0f;
                            ((SETextureTileL1Effect*)pNewEffect)->TileY = 8.0f;
                            ((SETextureTileL1Effect*)pNewEffect)->AmbientWeight 
                                = 0.65f;
                            ((SETextureTileL1Effect*)pNewEffect)->DiffuseWeight 
                                = 0.2f;
                            ((SETextureTileL1Effect*)pNewEffect)->SpecularWeight 
                                = 0.01f;

                        }
                        else
                        {
                            pNewEffect = SE_NEW SEMaterialTextureL1Effect(
                                tempBaseName);
                        }

                        pChild->DetachAllEffects();
                        pChild->AttachEffect(pNewEffect);
                    }
                }

                if( tempSubName == "Bone" || tempSubName == "join" )
                {
                    pMesh->DetachAllEffects();
                    pMesh->Culling = SESpatial::CULL_ALWAYS;
                }
                else if( tempSubName == "Glas" )
                {
                    SEAlphaState* pAS = SE_NEW SEAlphaState;
                    pAS->BlendEnabled = true;
                    pMesh->AttachGlobalState(pAS);

                    SEZBufferState* pZS = SE_NEW SEZBufferState;
                    pZS->Writable = false;
                    pMesh->AttachGlobalState(pZS);

                    SEMaterialState* pMS = 
                        (SEMaterialState*)pMesh->GetGlobalState(
                        SEGlobalState::MATERIAL);
                    if( pMS )
                    {
                        pMS->Ambient = SEColorRGB(0.1f, 0.1f, 0.1f);
                        pMS->Diffuse = SEColorRGB(0.1f, 0.1f, 0.1f);
                        pMS->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
                        pMS->Shininess = 100.0f;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::DisableLightingConditioner(SENode* pNode)
{
    if( !pNode )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                DisableLightingConditioner((SENode*)pChild);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                SETriMesh* pMesh = (SETriMesh*)pChild;
                pMesh->LightingMode = SEGeometry::GLM_USER;
            }
        }
    }
}
//---------------------------------------------------------------------------
void ManagedUtility::ImageConditioner(SENode* pNode, SEImage* pImage)
{
    if( !pNode || !pImage )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                ImageConditioner((SENode*)pChild, pImage);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                SETriMesh* pMesh = (SETriMesh*)pChild;
                if( pMesh->GetEffectCount() > 0 )
                {
                    std::string tempSubName = pMesh->GetName().substr(0, 4);

                    if( tempSubName == "Part" || tempSubName == "Trun" )
                    {
                        SEMaterialTexture2L1Effect* pEffect = 
                            DynamicCast<SEMaterialTexture2L1Effect>(
                            ((SETriMesh*)pMesh)->GetEffect(0));
                        if( pEffect )
                        {
                            SEPixelShader* pPS = pEffect->GetPShader(0);
                            SETexture* pTexture = pPS->GetTexture(1);
                            if( pTexture )
                            {
                                pPS->SetImageName(1, pImage->GetName());
                                pTexture->SetImage(pImage);
                                pTexture->Release();
                            }
                        }

                        SESkinMaterialTexture2L1Effect* pEffect2 = 
                            DynamicCast<SESkinMaterialTexture2L1Effect>(
                            ((SETriMesh*)pMesh)->GetEffect(0));
                        if( pEffect2 )
                        {
                            SEPixelShader* pPS = pEffect2->GetPShader(0);
                            SETexture* pTexture = pPS->GetTexture(1);
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
void ManagedUtility::WallConditioner(SENode* pNode, SETextureTileL1Effect* 
    pEffect)
{
    if( !pNode || !pEffect )
    {
        return;
    }

    for( int i = 0; i < pNode->GetCount(); i++ )
    {
        SESpatial* pChild = pNode->GetChild(i);

        if( pChild )
        {
            if( DynamicCast<SENode>(pChild) )
            {
                WallConditioner((SENode*)pChild, pEffect);
            }
            else if( DynamicCast<SETriMesh>(pChild) )
            {
                SETriMesh* pMesh = (SETriMesh*)pChild;
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