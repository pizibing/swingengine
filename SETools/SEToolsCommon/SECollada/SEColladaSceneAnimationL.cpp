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
ColladaAnimation* ColladaScene::LoadAnimation(domAnimationRef spDomAnimation)
{
	//if (animation==NULL) 
	//	return 0;

	//CrtPrint( "Add new Animation %s \n", animation->getId() );  

	//if ( animation )
	//{
	//	CrtAnimation * newAnim = CrtNew(CrtAnimation ); 
	//	CrtAssert("No memory\n", newAnim!=NULL);
	//	// get the animation name - target - keys and time 
	//	newAnim->SetName( animation->getId() );
	//	newAnim->SetDocURI( animation->getDocumentURI()->getURI() ); 

	//	// get the number of sources and store sources in animation's hash map
	//	domSource_Array & source_array = animation->getSource_array();
	//	size_t uiSourceCount = source_array.getCount();
	//	for (CrtUInt i = 0; i < uiSourceCount; i++)
	//	{
	//		CrtAnimSrc * source = ReadAnimationSource(source_array[i]);
	//		if (source) 
	//			newAnim->Sources[source->ID] = source;
	//	}

	//	// get the number of samplers and store samplers in animation's hash map
	//	domSampler_Array & sampler_array = animation->getSampler_array();
	//	size_t uiSamplerCount = sampler_array.getCount(); 
	//	for (CrtUInt s = 0; s < uiSamplerCount; s++)
	//	{
	//		CrtAnimSampler * anim_sampler = ReadAnimationSampler(newAnim, sampler_array[s]);
	//		if (anim_sampler) 
	//			newAnim->Samplers[sampler_array[s]->getID()] = anim_sampler;
	//	}

	//	// get the number of channels and store channels in animation's channel array
	//	domChannel_Array & channel_array = animation->getChannel_array();
	//	size_t uiChannelCount = channel_array.getCount(); 
	//	for (CrtUInt i = 0; i < uiChannelCount; i++)
	//	{
	//		CrtAnimChannel * channel = ReadAnimationChannel(newAnim, channel_array[i]);
	//		if (channel) 
	//			newAnim->Channels.push_back(channel);
	//	}

	//	if (newAnim->Channels.size() > 0)
	//	{
	//		newAnim->GenerateKeys(); 
	//		Animations.push_back(newAnim);
	//		// also get it's last key time and first key time 
	//		if( newAnim->GetEndTime() > LastKeyTime )
	//			LastKeyTime = newAnim->GetEndTime(); 
	//	} 
	//	else
	//	{
	//		CrtPrint("No Channel found in this animation\n");
	//		CrtDelete(newAnim);

	//		return 0;
	//	}

	//	return newAnim;
	//}

	return 0;
}
//----------------------------------------------------------------------------