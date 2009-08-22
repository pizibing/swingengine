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

#include "BloodCellController.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, BloodCellController, ParticleController);
SE_IMPLEMENT_STREAM(BloodCellController);
SE_IMPLEMENT_DEFAULT_NAME_ID(BloodCellController, ParticleController);

SE_REGISTER_STREAM(BloodCellController);

//----------------------------------------------------------------------------
BloodCellController::BloodCellController()
{
}
//----------------------------------------------------------------------------
void BloodCellController::UpdatePointMotion(float)
{
    Particles* pParticle = StaticCast<Particles>(m_pObject);

    int iLCount = pParticle->Locations->GetCount();
    Vector3f* aLocation = pParticle->Locations->GetData();
    float* afSize = pParticle->Sizes->GetData();
    for( int i = 0; i < iLCount; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            aLocation[i][j] += 0.01f*Mathf::SymmetricRandom();
            if( aLocation[i][j] > 1.0f )
            {
                aLocation[i][j] = 1.0f;
            }
            else if( aLocation[i][j] < -1.0f )
            {
                aLocation[i][j] = -1.0f;
            }
        }

        afSize[i] *= (1.0f + 0.05f*Mathf::SymmetricRandom());
        if( afSize[i] > 0.25f )
        {
            afSize[i] = 0.25f;
        }
    }

    pParticle->VBuffer->Release();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void BloodCellController::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    ParticleController::Load(rStream, pLink);

    SE_END_DEBUG_STREAM_LOAD(BloodCellController);
}
//----------------------------------------------------------------------------
void BloodCellController::Link(Stream& rStream, Stream::Link* pLink)
{
    ParticleController::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool BloodCellController::Register(Stream& rStream) const
{
    return ParticleController::Register(rStream);
}
//----------------------------------------------------------------------------
void BloodCellController::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    ParticleController::Save(rStream);

    SE_END_DEBUG_STREAM_SAVE(BloodCellController);
}
//----------------------------------------------------------------------------
int BloodCellController::GetDiskUsed(const StreamVersion& rVersion) const
{
    return ParticleController::GetDiskUsed(rVersion);
}
//----------------------------------------------------------------------------
StringTree* BloodCellController::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(ParticleController::SaveStrings());
    return pTree;
}
//----------------------------------------------------------------------------
