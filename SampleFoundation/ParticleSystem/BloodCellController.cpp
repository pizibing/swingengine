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

SE_IMPLEMENT_RTTI(Swing, BloodCellController, SEParticleController);
SE_IMPLEMENT_STREAM(BloodCellController);
SE_IMPLEMENT_DEFAULT_NAME_ID(BloodCellController, SEParticleController);

SE_REGISTER_STREAM(BloodCellController);

//----------------------------------------------------------------------------
BloodCellController::BloodCellController()
{
}
//----------------------------------------------------------------------------
void BloodCellController::UpdatePointMotion(float)
{
    SEParticles* pParticle = StaticCast<SEParticles>(m_pObject);

    int iLCount = pParticle->Locations->GetCount();
    SEVector3f* aLocation = pParticle->Locations->GetData();
    float* afSize = pParticle->Sizes->GetData();
    for( int i = 0; i < iLCount; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            aLocation[i][j] += 0.01f*SEMathf::SymmetricRandom();
            if( aLocation[i][j] > 1.0f )
            {
                aLocation[i][j] = 1.0f;
            }
            else if( aLocation[i][j] < -1.0f )
            {
                aLocation[i][j] = -1.0f;
            }
        }

        afSize[i] *= (1.0f + 0.05f*SEMathf::SymmetricRandom());
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
void BloodCellController::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEParticleController::Load(rStream, pLink);

    SE_END_DEBUG_STREAM_LOAD(BloodCellController);
}
//----------------------------------------------------------------------------
void BloodCellController::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEParticleController::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool BloodCellController::Register(SEStream& rStream) const
{
    return SEParticleController::Register(rStream);
}
//----------------------------------------------------------------------------
void BloodCellController::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEParticleController::Save(rStream);

    SE_END_DEBUG_STREAM_SAVE(BloodCellController);
}
//----------------------------------------------------------------------------
int BloodCellController::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEParticleController::GetDiskUsed(rVersion);
}
//----------------------------------------------------------------------------
SEStringTree* BloodCellController::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(SEParticleController::SaveStrings());
    return pTree;
}
//----------------------------------------------------------------------------
