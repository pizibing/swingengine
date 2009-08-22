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

#include "SEFoundationPCH.h"
#include "SEController.h"
#include "SEMath.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Controller, Object);
SE_IMPLEMENT_ABSTRACT_STREAM(Controller);
SE_IMPLEMENT_DEFAULT_NAME_ID(Controller, Object);

//SE_REGISTER_STREAM(Controller);

const char* Controller::ms_pRepeatType[Controller::RT_COUNT] =
{
    "RT_CLAMP",
    "RT_WRAP",
    "RT_CYCLE"
};

//----------------------------------------------------------------------------
Controller::Controller()
{
    m_pObject = 0;
    Repeat = RT_CLAMP;
    MinTime = 0.0;
    MaxTime = 0.0;
    Phase = 0.0;
    Frequency = 1.0;
    Active = true;
    m_dLastAppTime = -DBL_MAX;
}
//----------------------------------------------------------------------------
Controller::~Controller()
{
}
//----------------------------------------------------------------------------
double Controller::GetControlTime(double dAppTime)
{
    double dCtrlTime = Frequency*dAppTime + Phase;

    if( Repeat == RT_CLAMP )
    {
        if( dCtrlTime < MinTime )
        {
            return MinTime;
        }
        if( dCtrlTime > MaxTime )
        {
            return MaxTime;
        }

        return dCtrlTime;
    }

    double dRange = MaxTime - MinTime;
    if( dRange > 0.0 )
    {
        double dMultiples = (dCtrlTime - MinTime)/dRange;
        double dIntTime = Mathd::Floor(dMultiples);
        double dFrcTime = dMultiples - dIntTime;
        if( Repeat == RT_WRAP )
        {
            return MinTime + dFrcTime*dRange;
        }

        // Repeat == RT_CYCLE
        if( ((int)dIntTime) & 1 )
        {
            // backward time
            return MaxTime - dFrcTime*dRange;
        }
        else
        {
            // forward time
            return MinTime + dFrcTime*dRange;
        }
    }
    else
    {
        return MinTime;
    }
}
//----------------------------------------------------------------------------
bool Controller::Update(double dAppTime)
{
    if( Active &&  
        (dAppTime == -Mathd::MAX_REAL || dAppTime != m_dLastAppTime) )
    {
        m_dLastAppTime = dAppTime;

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Controller::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // native data
    int iRepeat;
    rStream.Read(iRepeat);
    Repeat = (RepeatType)iRepeat;

    rStream.Read(MinTime);
    rStream.Read(MaxTime);
    rStream.Read(Phase);
    rStream.Read(Frequency);
    rStream.Read(Active);
    // m_dLastAppTime is not streamed

    // link data
    Object* pObject;
    rStream.Read(pObject);
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(Controller);
}
//----------------------------------------------------------------------------
void Controller::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    m_pObject = rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool Controller::Register(Stream& rStream) const
{
    if( !Object::Register(rStream) )
    {
        return false;
    }

    if( m_pObject )
    {
        m_pObject->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void Controller::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // native data
    rStream.Write((int)Repeat);
    rStream.Write(MinTime);
    rStream.Write(MaxTime);
    rStream.Write(Phase);
    rStream.Write(Frequency);
    rStream.Write(Active);

    // link data
    rStream.Write(m_pObject);

    SE_END_DEBUG_STREAM_SAVE(Controller);
}
//----------------------------------------------------------------------------
int Controller::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Object::GetDiskUsed(rVersion) +
        sizeof(int) +  // Repeat
        sizeof(MinTime) +
        sizeof(MaxTime) +
        sizeof(Phase) +
        sizeof(Frequency) +
        sizeof(char) +  // Active
        sizeof(m_pObject);
}
//----------------------------------------------------------------------------
StringTree* Controller::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE,(const char*)GetName()));
    pTree->Append(Format("repeat type = ",ms_pRepeatType[Repeat]));
    pTree->Append(Format("min time =",MinTime));
    pTree->Append(Format("max time =",MaxTime));
    pTree->Append(Format("phase =",Phase));
    pTree->Append(Format("frequency =",Frequency));
    pTree->Append(Format("active =",Active));

    // children
    pTree->Append(Object::SaveStrings());

    // Object will iterate over controllers to save strings
    return pTree;
}
//----------------------------------------------------------------------------
