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

#include "SEAudioPCH.h"
#include "SEListener.h"
#include "SEAudioRenderer.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEListener, SEObject);
SE_IMPLEMENT_STREAM(SEListener);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEListener, SEObject);

//SE_REGISTER_STREAM(SEListener);

//----------------------------------------------------------------------------
SEListener::SEListener()
{
    m_fMasterGain = 1.0f;
    m_pAudioRenderer = 0;

    SetFrame(SEVector3f::ZERO, SEVector3f::UNIT_X, SEVector3f::UNIT_Y,
        SEVector3f::UNIT_Z); // 与世界空间坐标系重合
}
//----------------------------------------------------------------------------
SEListener::~SEListener()
{
}
//----------------------------------------------------------------------------
void SEListener::SetFrame(const SEVector3f& rLocation, const SEVector3f& 
    rRVector, const SEVector3f& rUVector, const SEVector3f& rDVector)
{
    m_Location = rLocation;
    SetAxes(rRVector, rUVector, rDVector);
}
//----------------------------------------------------------------------------
void SEListener::SetLocation(const SEVector3f& rLocation)
{
    m_Location = rLocation;

    if( m_pAudioRenderer )
    {
        m_pAudioRenderer->OnFrameChange();
    }
}
//----------------------------------------------------------------------------
void SEListener::SetAxes(const SEVector3f& rRVector, const SEVector3f& 
    rUVector, const SEVector3f& rDVector)
{
    m_RVector = rRVector;
    m_UVector = rUVector;
    m_DVector = rDVector;

    float fADet = SEMathf::FAbs(m_DVector.Dot(m_RVector.Cross(m_UVector)));
    if( SEMathf::FAbs(1.0f-fADet) > 0.01f )
    {
        // R,U,D不构成规范正交基,因此重新正交规范化这组基向量.
        SEVector3f::Orthonormalize(m_RVector, m_UVector, m_DVector);
    }

    if( m_pAudioRenderer )
    {
        m_pAudioRenderer->OnFrameChange();
    }
}
//----------------------------------------------------------------------------
void SEListener::SetMasterGain(float fMasterGain)
{
    m_fMasterGain = fMasterGain;

    if( m_pAudioRenderer )
    {
        m_pAudioRenderer->OnMasterGainChange();
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEListener::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    // native data
    rStream.Read(m_Location);
    rStream.Read(m_RVector);
    rStream.Read(m_UVector);
    rStream.Read(m_DVector);
    rStream.Read(m_fMasterGain);

    SE_END_DEBUG_STREAM_LOAD(SEListener);
}
//----------------------------------------------------------------------------
void SEListener::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEListener::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEListener::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;
    
    SEObject::Save(rStream);

    // native data
    rStream.Write(m_Location);
    rStream.Write(m_RVector);
    rStream.Write(m_UVector);
    rStream.Write(m_DVector);
    rStream.Write(m_fMasterGain);

    SE_END_DEBUG_STREAM_SAVE(SEListener);
}
//----------------------------------------------------------------------------
int SEListener::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEObject::GetDiskUsed(rVersion) +
        sizeof(m_Location) +
        sizeof(m_RVector) +
        sizeof(m_UVector) +
        sizeof(m_DVector) +
        sizeof(m_fMasterGain);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEListener::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("location =", m_Location));
    pTree->Append(Format("r vector =", m_RVector));
    pTree->Append(Format("u vector =", m_UVector));
    pTree->Append(Format("d vector =", m_DVector));
    pTree->Append(Format("master gain =", m_fMasterGain));

    // children
    pTree->Append(SEObject::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
