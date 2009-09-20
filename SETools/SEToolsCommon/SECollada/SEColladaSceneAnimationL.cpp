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

using namespace Swing;

//----------------------------------------------------------------------------
bool ColladaScene::LoadAnimationLibrary(domLibrary_animationsRef spLib)
{
    ToolSystem::SE_DebugOutput("ColladaScene::Loading Animation Library");

    int iAnimationCount = (int)spLib->getAnimation_array().getCount();
    for( int i = 0; i < iAnimationCount; i++ )
    {
        LoadAnimation(spLib->getAnimation_array()[i]);
    }

    return true;
}
//----------------------------------------------------------------------------
ColladaAnimationSource* ColladaScene::LoadAnimationSource(
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

    ColladaAnimationSource* pSource = SE_NEW ColladaAnimationSource;
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

        pSource->Source = SE_NEW FloatArray(iCount, afData);
    }
    else 
    {
        ToolSystem::SE_DebugOutput("Animation source %s is not support", 
            strSourceID);
    }

    return pSource;
}
//----------------------------------------------------------------------------
ColladaAnimationSampler* ColladaScene::LoadAnimationSampler(
    ColladaAnimation* pAnimation, domSamplerRef spDomSampler)
{
    if( !spDomSampler )
    {
        return 0;
    }

    ColladaAnimationSampler* pSampler = SE_NEW ColladaAnimationSampler;
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
        ColladaAnimationSource* pSource = pAnimation->Sources[strSourceID];
        pSampler->Inputs[(const char*)strInputSemantic] = pSource;
    }

    return pSampler;
}
//----------------------------------------------------------------------------
ColladaAnimationChannel* ColladaScene::LoadAnimationChannel(
    ColladaAnimation* pAnimation, domChannelRef spDomChannel)
{
    if( !spDomChannel )
    {
        return 0;
    }

    ColladaAnimationChannel* pChannel = SE_NEW ColladaAnimationChannel;
    domSampler* pDomSampler = 
        (domSampler*)(domElement*)spDomChannel->getSource().getElement();
    const char* acTargetName = spDomChannel->getTarget();
    pChannel->Sampler = pAnimation->Samplers[pDomSampler->getId()];
    
    // Get a pointer to the input source.
    const String& rInputSourceID = 
        pChannel->Sampler->Inputs["INPUT"]->GetName();
    ColladaAnimationSource* pInputSource = 
        pAnimation->Sources[(const char*)rInputSourceID];

    // Get a pointer to the output source.
    const String& rOutputSourceID = 
        pChannel->Sampler->Inputs["OUTPUT"]->GetName();
    ColladaAnimationSource* pOutputSource = 
        pAnimation->Sources[(const char*)rOutputSourceID];
    
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
        System::SE_Strncpy(tempTargetID, iBufferSize, acTargetName, 
            (int)(acIDSep - acTargetName));
        pChannel->TargetID = tempTargetID;
    }
    if( acIDSep && acSIDSep && acSIDSep > acIDSep )
    {
        System::SE_Strncpy(tempTargetSID, iBufferSize, acIDSep + 1, 
            (int)(acSIDSep - acIDSep - 1));
        pChannel->TargetSID = tempTargetSID;
    }
    if( acSIDSep && (*acSIDSep) != '\0' )
    {
        System::SE_Strcpy(tempTargetMember, iBufferSize, acSIDSep + 1);
        pChannel->TargetMember = tempTargetMember;
    }

    // Resolve target by using DAE functions.
    domElement* pDomElement = 0;
    domElement* pDomRootNode = spDomChannel->getDocument()->getDomRoot();
    daeSIDResolver tempDomSIDResolver(pDomRootNode, acTargetName);
    pDomElement = tempDomSIDResolver.getElement();
    if( !pDomElement )
    {
        ToolSystem::SE_DebugOutput("Animation target = %s not found", 
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
        pChannel->TargetType = AT_T;
        pChannel->NumElementTargets = 3; 
        break;

    case COLLADA_TYPE::ROTATE:
        pAnimation->HasRotation = true;
        pChannel->TargetType = AT_R;
        pChannel->NumElementTargets = 4; 
        break;

    case COLLADA_TYPE::SCALE:
        pAnimation->HasScale = true;
        pChannel->TargetType = AT_S;
        pChannel->NumElementTargets = 3; 
        break;

    case COLLADA_TYPE::SOURCE:
        pAnimation->HasSource = true;
        pChannel->TargetType = AT_SOURCE;
        pChannel->NumElementTargets = 1; 
        break;

    case COLLADA_TYPE::MATRIX:
        pAnimation->HasMatrix = true;
        pChannel->TargetType = AT_MATRIX;
        pChannel->NumElementTargets = 16; 
        break;

    default:
        ToolSystem::SE_DebugOutput("Animation target = %s not supported", 
            acTargetName);
        SE_DELETE pChannel;
        return 0;
    }

    // Parse target member type.
    if( pChannel->TargetMember != String("") )
    {
        const char* acTargetMember = pChannel->TargetMember;
        if( strcmp(acTargetMember, "AXIS") == 0 ||
            strcmp(acTargetMember, "ANGLE") == 0 )
        {
            domRotate* pDomRotate = (domRotate*)pDomElement;
            if( pDomRotate->getValue()[0] == 1 )
            {
                // Rotate x axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = AT_R_X_AXIS;
                pChannel->NumElementTargets = 1;
            }
            else if( pDomRotate->getValue()[1] == 1 ) 
            {
                // Rotate y axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = AT_R_Y_AXIS;
                pChannel->NumElementTargets = 1; 
            }
            else if( pDomRotate->getValue()[2] == 1 ) 
            {
                // Rotate z axis.
                pAnimation->HasRotation = true;
                pChannel->TargetType = AT_R_Z_AXIS;
                pChannel->NumElementTargets = 1; 
            }
        }
        else if( strcmp(acTargetMember, "X") == 0 )
        {
            pChannel->TargetType = AT_TARGET_X;
            pChannel->NumElementTargets = 1;
        }
        else if( strcmp(acTargetMember, "Y") == 0 ) 
        {
            pChannel->TargetType = AT_TARGET_Y;
            pChannel->NumElementTargets = 1;
        }
        else if( strcmp(acTargetMember, "Z") == 0 )
        {
            pChannel->TargetType = AT_TARGET_Z;
            pChannel->NumElementTargets = 1;
        }
        else if( (*acTargetMember) >= '0' && (*acTargetMember) <= '9' )
        {
            pChannel->TargetType = AT_SOURCE;
            pChannel->NumElementTargets = 1;
        }
        else
        {
            pChannel->TargetType = AT_TARGET_XYZ;
            pChannel->NumElementTargets = 3;
        }
    }
    pAnimation->NumAnimChannels = pChannel->NumElementTargets;

    return pChannel;
}
//----------------------------------------------------------------------------
ColladaAnimation* ColladaScene::LoadAnimation(domAnimationRef spDomAnimation)
{
    if( !spDomAnimation )
    {
        return 0;
    }

    xsID strAnimationID = spDomAnimation->getId();

    ToolSystem::SE_DebugOutput("Add new Animation %s", strAnimationID);  

    domAnimation* pDomAnimation = (domAnimation*)spDomAnimation;
    if( pDomAnimation )
    {
        ColladaAnimation* pAnimation = SE_NEW ColladaAnimation;
        pAnimation->SetName(strAnimationID);

        // Get the number of sources and store them in animation's hash map.
        domSource_Array& rDomSourceArray = pDomAnimation->getSource_array();
        int iSourceCount = (int)rDomSourceArray.getCount();
        for( int i = 0; i < iSourceCount; i++ )
        {
            ColladaAnimationSource* pSource = 
                LoadAnimationSource(rDomSourceArray[i]);
            if( pSource )
            {
                const char* acSourceName = (const char*)pSource->GetName();
                pAnimation->Sources[acSourceName] = pSource;
            }
        }

        // Get the number of samplers and store them in animation's hash map.
        domSampler_Array& rDomSamplerArray = 
            pDomAnimation->getSampler_array();
        int iSamplerCount = (int)rDomSamplerArray.getCount();
        for( int i = 0; i < iSamplerCount; i++ )
        {
            ColladaAnimationSampler* pSampler = 
                LoadAnimationSampler(pAnimation, rDomSamplerArray[i]);
            if( pSampler )
            {
                const char* acSamplerName = (const char*)pSampler->GetName();
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
            ColladaAnimationChannel* pChannel = 
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

            //// Also get it's last key time and first key time.
            //if( pAnimation->EndTime > LastKeyTime )
            //{
            //    LastKeyTime = pAnimation->EndTime;
            //}
        }
        else
        {
            ToolSystem::SE_DebugOutput("No Channel found in this animation");
            SE_DELETE pAnimation;

            return 0;
        }

        return pAnimation;
    }

    return 0;
}
//----------------------------------------------------------------------------