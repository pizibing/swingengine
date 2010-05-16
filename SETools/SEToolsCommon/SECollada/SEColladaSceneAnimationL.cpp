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

#include "SEToolsCommonPCH.h"
#include "SEColladaScene.h"
#include <set>

using namespace Swing;
using namespace std;

//----------------------------------------------------------------------------
bool SEColladaScene::LoadAnimationLibrary(domLibrary_animationsRef spLib)
{
    ToolSystem::DebugOutput("SEColladaScene::Loading Animation Library");

    int iAnimationCount = (int)spLib->getAnimation_array().getCount();
    for( int i = 0; i < iAnimationCount; i++ )
    {
        LoadAnimation(spLib->getAnimation_array()[i]);
    }

    return true;
}
//----------------------------------------------------------------------------
SEColladaAnimationSource* SEColladaScene::LoadAnimationSource(
    domSourceRef spDomSource)
{
    if( !spDomSource )
    {
        return 0;
    }

    xsID strSourceID = spDomSource->getId();
    if( !strSourceID )
    {
        return 0;
    }

    SEColladaAnimationSource* pSource = SE_NEW SEColladaAnimationSource;
    pSource->SetName((const char*)strSourceID);

    // Copy the float array data if any.
    domFloat_array* pDomFloatArray = spDomSource->getFloat_array();
    if( pDomFloatArray )
    {
        int iCount = (int)pDomFloatArray->getCount();
        float* afData = SE_NEW float[iCount];

        // Copy the array data.
        daeDoubleArray& rDomFloatArray = pDomFloatArray->getValue();
        for( int i = 0; i < iCount; i++ )
        {
            afData[i] = (float)rDomFloatArray[i];
        }

        pSource->Source = SE_NEW SEFloatArray(iCount, afData);
    }
    else 
    {
        ToolSystem::DebugOutput("Animation source %s is not support", 
            strSourceID);
    }

    return pSource;
}
//----------------------------------------------------------------------------
SEColladaAnimationSampler* SEColladaScene::LoadAnimationSampler(
    SEColladaAnimation* pAnimation, domSamplerRef spDomSampler)
{
    if( !spDomSampler )
    {
        return 0;
    }

    SEColladaAnimationSampler* pSampler = SE_NEW SEColladaAnimationSampler;
    pSampler->SetName((const char*)spDomSampler->getId());

    domInputLocal_Array& rDomInputArray = spDomSampler->getInput_array();
    int iInputCount = (int)rDomInputArray.getCount();
    for( int i = 0; i < iInputCount; i++ )
    {
        domInputLocal* pInput = rDomInputArray[i];
        domSource* pDomSource = 
            (domSource*)(domElement*)pInput->getSource().getElement();

        xsNMTOKEN strInputSemantic = pInput->getSemantic();
        xsID strSourceID = pDomSource->getId();
        SEColladaAnimationSource* pSource = pAnimation->Sources[strSourceID];
        pSampler->Inputs[(const char*)strInputSemantic] = pSource;
    }

    return pSampler;
}
//----------------------------------------------------------------------------
SEColladaAnimationChannel* SEColladaScene::LoadAnimationChannel(
    SEColladaAnimation* pAnimation, domChannelRef spDomChannel)
{
    if( !spDomChannel )
    {
        return 0;
    }

    SEColladaAnimationChannel* pChannel = SE_NEW SEColladaAnimationChannel;
    domSampler* pDomSampler = 
        (domSampler*)(domElement*)spDomChannel->getSource().getElement();
    const char* acTargetName = spDomChannel->getTarget();
    pChannel->Sampler = pAnimation->Samplers[pDomSampler->getId()];
    
    // Get a pointer to the input source.
    const std::string& rInputSourceID = 
        pChannel->Sampler->Inputs["INPUT"]->GetName();
    SEColladaAnimationSource* pInputSource = 
        pAnimation->Sources[rInputSourceID.c_str()];

    // Get a pointer to the output source.
    const std::string& rOutputSourceID = 
        pChannel->Sampler->Inputs["OUTPUT"]->GetName();
    SEColladaAnimationSource* pOutputSource = 
        pAnimation->Sources[rOutputSourceID.c_str()];
    
    pChannel->InputSource = pInputSource;
    pChannel->OutputSource = pOutputSource;

    // Parse target.
    // Get a pointer to the target element. 
    const char* acIDSep = strstr(acTargetName, "/");
    if( !acIDSep )
    {
        // Failed, try this.
        acIDSep = strstr(acTargetName, "(");
    }
    if( !acIDSep )
    {
        // Failed again, try this.
        acIDSep = strstr(acTargetName, ".");
    }

    // Get a pointer to the final element.
    const char* acSIDSep = strstr(acTargetName, ".");
    if( !acSIDSep )
    {
        acSIDSep = strstr(acTargetName, "(");
    }
    if( !acSIDSep )
    {
        // Nothing else matches, then there is no member.
        acSIDSep = acTargetName + strlen(acTargetName);
    }
    
    const int iBufferSize = 512;
    char tempTargetID[iBufferSize];
    char tempTargetSID[iBufferSize];
    char tempTargetMember[iBufferSize];
    if( acIDSep )
    {
        SESystem::SE_Strncpy(tempTargetID, iBufferSize, acTargetName, 
            (int)(acIDSep - acTargetName));
        pChannel->TargetID = tempTargetID;
    }
    if( acIDSep && acSIDSep && acSIDSep > acIDSep )
    {
        SESystem::SE_Strncpy(tempTargetSID, iBufferSize, acIDSep + 1, 
            (int)(acSIDSep - acIDSep - 1));
        pChannel->TargetSID = tempTargetSID;
    }
    if( acSIDSep && (*acSIDSep) != '\0' )
    {
        SESystem::SE_Strcpy(tempTargetMember, iBufferSize, acSIDSep + 1);
        pChannel->TargetMember = tempTargetMember;
    }

    // Resolve target by using DAE functions.
    domElement* pDomElement = 0;
    domElement* pDomRootNode = spDomChannel->getDocument()->getDomRoot();
    daeSIDResolver tempDomSIDResolver(pDomRootNode, acTargetName);
    pDomElement = tempDomSIDResolver.getElement();
    if( !pDomElement )
    {
        ToolSystem::DebugOutput("Animation target = %s not found", 
            acTargetName);
        SE_DELETE pChannel;

        return 0;
    }

    // Set channel info.
    COLLADA_TYPE::TypeEnum eType = pDomElement->getElementType();
    switch( eType )
    {
    case COLLADA_TYPE::TRANSLATE:
        pAnimation->HasTranslation = true;
        pChannel->TargetType = SEColladaAnimationChannel::AT_T;
        pChannel->NumElementTargets = 3; 
        break;

    case COLLADA_TYPE::ROTATE:
        pAnimation->HasRotation = true;
        pChannel->TargetType = SEColladaAnimationChannel::AT_R;
        pChannel->NumElementTargets = 4; 
        break;

    case COLLADA_TYPE::SCALE:
        pAnimation->HasScale = true;
        pChannel->TargetType = SEColladaAnimationChannel::AT_S;
        pChannel->NumElementTargets = 3; 
        break;

    case COLLADA_TYPE::SOURCE:
        pAnimation->HasSource = true;
        pChannel->TargetType = SEColladaAnimationChannel::AT_SOURCE;
        pChannel->NumElementTargets = 1; 
        break;

    case COLLADA_TYPE::MATRIX:
        pAnimation->HasMatrix = true;
        pChannel->TargetType = SEColladaAnimationChannel::AT_MATRIX;
        pChannel->NumElementTargets = 16; 
        break;

    default:
        ToolSystem::DebugOutput("Animation target = %s not supported", 
            acTargetName);
        SE_DELETE pChannel;
        return 0;
    }

    // Parse target member type.
    if( pChannel->TargetMember != std::string("") )
    {
        const char* acTargetMember = pChannel->TargetMember.c_str();
        if( strcmp(acTargetMember, "AXIS") == 0 ||
            strcmp(acTargetMember, "ANGLE") == 0 )
        {
            domRotate* pDomRotate = (domRotate*)pDomElement;
            if( pDomRotate->getValue()[0] == 1 )
            {
                // Rotate x axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = SEColladaAnimationChannel::AT_R_X_AXIS;
                pChannel->NumElementTargets = 1;
            }
            else if( pDomRotate->getValue()[1] == 1 ) 
            {
                // Rotate y axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = SEColladaAnimationChannel::AT_R_Y_AXIS;
                pChannel->NumElementTargets = 1; 
            }
            else if( pDomRotate->getValue()[2] == 1 ) 
            {
                // Rotate z axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = SEColladaAnimationChannel::AT_R_Z_AXIS;
                pChannel->NumElementTargets = 1; 
            }
        }
        else if( strcmp(acTargetMember, "X") == 0 )
        {
            pChannel->TargetType = SEColladaAnimationChannel::AT_TARGET_X;
            pChannel->NumElementTargets = 1;
        }
        else if( strcmp(acTargetMember, "Y") == 0 ) 
        {
            pChannel->TargetType = SEColladaAnimationChannel::AT_TARGET_Y;
            pChannel->NumElementTargets = 1;
        }
        else if( strcmp(acTargetMember, "Z") == 0 )
        {
            pChannel->TargetType = SEColladaAnimationChannel::AT_TARGET_Z;
            pChannel->NumElementTargets = 1;
        }
        else if( (*acTargetMember) >= '0' && (*acTargetMember) <= '9' )
        {
            pChannel->TargetType = SEColladaAnimationChannel::AT_SOURCE;
            pChannel->NumElementTargets = 1;
        }
        else
        {
            pChannel->TargetType = SEColladaAnimationChannel::AT_TARGET_XYZ;
            pChannel->NumElementTargets = 3;
        }
    }
    pAnimation->NumAnimChannels += pChannel->NumElementTargets;

    return pChannel;
}
//----------------------------------------------------------------------------
SEColladaAnimation* SEColladaScene::LoadAnimation(domAnimationRef 
    spDomAnimation)
{
    if( !spDomAnimation )
    {
        return 0;
    }

    xsID strAnimationID = spDomAnimation->getId();

    ToolSystem::DebugOutput("Add new Animation %s", strAnimationID);

    domAnimation* pDomAnimation = (domAnimation*)spDomAnimation;
    if( pDomAnimation )
    {
        SEColladaAnimation* pAnimation = SE_NEW SEColladaAnimation;
        pAnimation->SetName(strAnimationID);

        // Get the number of sources and store them in animation's hash map.
        domSource_Array& rDomSourceArray = pDomAnimation->getSource_array();
        int iSourceCount = (int)rDomSourceArray.getCount();
        for( int i = 0; i < iSourceCount; i++ )
        {
            SEColladaAnimationSource* pSource = 
                LoadAnimationSource(rDomSourceArray[i]);
            if( pSource )
            {
                const char* acSourceName = pSource->GetName().c_str();
                pAnimation->Sources[acSourceName] = pSource;
            }
        }

        // Get the number of samplers and store them in animation's hash map.
        domSampler_Array& rDomSamplerArray = 
            pDomAnimation->getSampler_array();
        int iSamplerCount = (int)rDomSamplerArray.getCount();
        for( int i = 0; i < iSamplerCount; i++ )
        {
            SEColladaAnimationSampler* pSampler = 
                LoadAnimationSampler(pAnimation, rDomSamplerArray[i]);
            if( pSampler )
            {
                const char* acSamplerName = pSampler->GetName().c_str();
                pAnimation->Samplers[acSamplerName] = pSampler;
            }
        }

        // Get the number of channels and store them in animation's channel 
        // array.
        domChannel_Array& rDomChannelArray = 
            pDomAnimation->getChannel_array();
        int iChannelCount = (int)rDomChannelArray.getCount();
        for( int i = 0; i < iChannelCount; i++ )
        {
            SEColladaAnimationChannel* pChannel = 
                LoadAnimationChannel(pAnimation, rDomChannelArray[i]);
            if( pChannel )
            {
                pAnimation->Channels.push_back(pChannel);
            }
        }

        if( pAnimation->Channels.size() > 0 )
        {
            pAnimation->GenerateKeys();
            m_Animations.push_back(pAnimation);
        }
        else
        {
            ToolSystem::DebugOutput("No Channel found in this animation");
            SE_DELETE pAnimation;

            return 0;
        }

        return pAnimation;
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEColladaScene::BuildKeyFrameController(SENode* pNode,
    std::vector<SEColladaTransformation*>& rColladaTransSequence)
{
    // Get a keyframe information set.
    set<KeyInfo> tempKeyInfoSet;
    float fEndTime = 0.0f;
    int iTransCount = (int)rColladaTransSequence.size();
    for( int i = 0; i < iTransCount; i++ )
    {
        SEColladaAnimation* pAnimation = rColladaTransSequence[i]->Animation;
        if( pAnimation )
        {
            // Swing Engine only support SRT keyframe animation.
            SEColladaTransformation::TransformType eTType = 
                rColladaTransSequence[i]->TransType;
            SE_ASSERT( eTType == SEColladaTransformation::TT_SCALE || 
                eTType == SEColladaTransformation::TT_ROTATE || 
                eTType == SEColladaTransformation::TT_TRANSLATE );

            // A single transform may have serveral animated channels attached.
            int iChannelCount = rColladaTransSequence[i]->GetChannelCount();
            for( int j = 0; j < iChannelCount; j++ )
            {
                int iChannelID = rColladaTransSequence[i]->GetChannel(j);
                SEColladaKeySet& rKeySet = pAnimation->AnimKeySets[iChannelID];
                for( int k = 0; k < rKeySet.NumKeys; k++ )
                {
                    KeyInfo tempKeyInfo;
                    tempKeyInfo.Time = rKeySet.Time[k];
                    tempKeyInfo.Type = eTType;
                    tempKeyInfoSet.insert(tempKeyInfo);
                }
            }

            if( pAnimation->EndTime > fEndTime )
            {
                fEndTime = pAnimation->EndTime;
            }
        }
    }

    if( (int)tempKeyInfoSet.size() <= 0 )
    {
        // This node doesn't contain any keyframe animation data.
        return;
    }

    int iScaKeyCount = 0;
    int iRotKeyCount = 0;
    int iTrnKeyCount = 0;

    set<KeyInfo>::iterator tempIter = tempKeyInfoSet.begin();
    for( int i = 0; i < (int)tempKeyInfoSet.size(); i++, tempIter++ )
    {
        switch( (*tempIter).Type )
        {
        case SEColladaTransformation::TT_SCALE:
            iScaKeyCount++;
            break;

        case SEColladaTransformation::TT_ROTATE:
            iRotKeyCount++;
            break;

        case SEColladaTransformation::TT_TRANSLATE:
            iTrnKeyCount++;
            break;

        default:
            SE_ASSERT( false );
            break;
        }
    }

    // Create a keyframe controller that will be attached to the node,
    // and allocate memory for it's member.
    SEKeyframeController* pKFController = SE_NEW SEKeyframeController;
    if( iScaKeyCount > 0 )
    {
        pKFController->ScaleTimes = SE_NEW SEFloatArray(iScaKeyCount,
            SE_NEW float[iScaKeyCount]);
        pKFController->ScaleData = SE_NEW SEFloatArray(iScaKeyCount,
            SE_NEW float[iScaKeyCount]);
    }
    if( iRotKeyCount > 0 )
    {
        pKFController->RotationTimes = SE_NEW SEFloatArray(iRotKeyCount,
            SE_NEW float[iRotKeyCount]);
        pKFController->RotationData = SE_NEW SEQuaternionfArray(iRotKeyCount,
            SE_NEW SEQuaternionf[iRotKeyCount]);
    }
    if( iTrnKeyCount > 0 )
    {
        pKFController->TranslationTimes = SE_NEW SEFloatArray(iTrnKeyCount,
            SE_NEW float[iTrnKeyCount]);
        pKFController->TranslationData = SE_NEW SEVector3fArray(iTrnKeyCount,
            SE_NEW SEVector3f[iTrnKeyCount]);
    }

    float* pfSKey = (pKFController->ScaleData ?
        pKFController->ScaleData->GetData() : 0);
    float* pfSTime = (pKFController->ScaleTimes ?
        pKFController->ScaleTimes->GetData() : 0);

    SEQuaternionf* pRKey = (pKFController->RotationData ?
        pKFController->RotationData->GetData() : 0);
    float* pfRTime = (pKFController->RotationTimes ?
        pKFController->RotationTimes->GetData() : 0);

    SEVector3f* pTKey = (pKFController->TranslationData ? 
        pKFController->TranslationData->GetData() : 0);
    float* pfTTime = (pKFController->TranslationTimes ?
        pKFController->TranslationTimes->GetData() : 0);

    float fTimeNow = -1.0f;
    SETransformation tempTransform;
    tempIter = tempKeyInfoSet.begin();
    for( int i = 0; i < (int)tempKeyInfoSet.size(); i++, tempIter++ )
    {
        KeyInfo& rInfo = *tempIter;

        if( fTimeNow != rInfo.Time )
        {
            fTimeNow = rInfo.Time;
            tempTransform = GetLocalTransformation(rColladaTransSequence,
                fTimeNow);
        }

        switch( rInfo.Type )
        {
        case SEColladaTransformation::TT_SCALE:
            {
                // TODO:
                // We only support uniform scale and postive scale factor.
                float fMax;
                if( tempTransform.IsUniformScale() )
                {
                    fMax = tempTransform.GetUniformScale();
                }
                else
                {
                    fMax = SEMath<float>::FAbs(tempTransform.GetScale().X);
                    float fAbs = SEMath<float>::FAbs(tempTransform.GetScale(
                        ).Y);
                    if( fAbs > fMax )
                    {
                        fMax = fAbs;
                    }
                    fAbs = SEMath<float>::FAbs(tempTransform.GetScale().Z);
                    if( fAbs > fMax )
                    {
                        fMax = fAbs;
                    }
                }

                SE_ASSERT( pfSKey );
                SE_ASSERT( pfSTime );

                *pfSKey++ = fMax;
                *pfSTime++ = fTimeNow;
            }
            break;

        case SEColladaTransformation::TT_ROTATE:
            // TODO:
            // We only support SR form.
            if( tempTransform.IsSRMatrix() )
            {
                SE_ASSERT( pRKey );
                SE_ASSERT( pfRTime );

                // 待检查.
                // q和-q表示同样的旋转变换.
                // 但为了保持q和next q之间的最小夹角,因此使其保持符号一致.
                pRKey->FromRotationMatrix(tempTransform.GetRotate());
                if( pRKey->W < 0.0f )
                {
                    *pRKey = -*pRKey;
                }
                pRKey++;
                *pfRTime++ = fTimeNow;
            }
            break;

        case SEColladaTransformation::TT_TRANSLATE:
            SE_ASSERT( pTKey );
            SE_ASSERT( pfTTime );
            *pTKey++ = tempTransform.GetTranslate();
            *pfTTime++ = fTimeNow;
            break;

        default:
            break;
        }
    }

    pKFController->Repeat = SEController::RT_WRAP;
    pKFController->MinTime = 0.0f;
    pKFController->MaxTime = fEndTime;
    pNode->AttachController(pKFController);
}
//----------------------------------------------------------------------------