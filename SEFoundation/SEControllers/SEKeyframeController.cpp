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
#include "SEKeyframeController.h"
#include "SESpatial.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, KeyframeController, Controller);
SE_IMPLEMENT_STREAM(KeyframeController);

//SE_REGISTER_STREAM(KeyframeController);

//----------------------------------------------------------------------------
KeyframeController::KeyframeController()
{
    m_iTLastIndex = 0;
    m_iRLastIndex = 0;
    m_iSLastIndex = 0;
}
//----------------------------------------------------------------------------
KeyframeController::~KeyframeController()
{
}
//----------------------------------------------------------------------------
void KeyframeController::GetKeyInfo(float fCtrlTime, int iCount,
    float* afTime, int& riLastIndex, float& rfTime, int& ri0, int& ri1)
{
    if( fCtrlTime <= afTime[0] )
    {
        rfTime = 0.0f;
        riLastIndex = 0;
        ri0 = 0;
        ri1 = 0;

        return;
    }

    if( fCtrlTime >= afTime[iCount-1] )
    {
        rfTime = 0.0f;
        riLastIndex = iCount - 1;
        ri0 = riLastIndex;
        ri1 = riLastIndex;

        return;
    }

    int iNextIndex;
    if( fCtrlTime > afTime[riLastIndex] )
    {
        iNextIndex = riLastIndex + 1;
        while( fCtrlTime >= afTime[iNextIndex] )
        {
            riLastIndex = iNextIndex;
            iNextIndex++;
        }

        ri0 = riLastIndex;
        ri1 = iNextIndex;
        rfTime = (fCtrlTime - afTime[ri0])/(afTime[ri1] - afTime[ri0]);
    }
    else if( fCtrlTime < afTime[riLastIndex] )
    {
        iNextIndex = riLastIndex - 1;
        while( fCtrlTime <= afTime[iNextIndex] )
        {
            riLastIndex = iNextIndex;
            iNextIndex--;
        }

        ri0 = iNextIndex;
        ri1 = riLastIndex;
        rfTime = (fCtrlTime - afTime[ri0])/(afTime[ri1] - afTime[ri0]);
    }
    else
    {
        rfTime = 0.0f;
        ri0 = riLastIndex;
        ri1 = riLastIndex;
    }
}
//----------------------------------------------------------------------------
SEVector3f KeyframeController::GetTranslate(float fNormTime, int i0, int i1)
{
    SEVector3f* aTData = TranslationData->GetData();

    return aTData[i0] + fNormTime*(aTData[i1] - aTData[i0]);
}
//----------------------------------------------------------------------------
SEMatrix3f KeyframeController::GetRotate(float fNormTime, int i0, int i1)
{
    SEQuaternionf* aRData = RotationData->GetData();
    SEQuaternionf tempQuat;
    tempQuat.Slerp(fNormTime, aRData[i0], aRData[i1]);

    SEMatrix3f tempRot;
    tempQuat.ToRotationMatrix(tempRot);

    return tempRot;
}
//----------------------------------------------------------------------------
float KeyframeController::GetScale(float fNormTime, int i0, int i1)
{
    float* afSData = ScaleData->GetData();

    return afSData[i0] + fNormTime*(afSData[i1] - afSData[i0]);
}
//----------------------------------------------------------------------------
bool KeyframeController::Update(double dAppTime)
{
    if( !Controller::Update(dAppTime) )
    {
        return false;
    }

    Spatial* pSpatial = StaticCast<Spatial>(m_pObject);
    float fCtrlTime = (float)GetControlTime(dAppTime);
    float fNormTime = 0.0f;
    int i0 = 0, i1 = 0;

    // 检查各自所用的时间数组是否相等,从而可以最小化GetKeyInfo的调用次数.
    if( TranslationTimes == RotationTimes )
    {
        if( TranslationTimes )
        {
            GetKeyInfo(fCtrlTime, TranslationTimes->GetCount(),
                TranslationTimes->GetData(), m_iTLastIndex, fNormTime, i0, i1);
        }

        if( TranslationData )
        {
            pSpatial->Local.SetTranslate(GetTranslate(fNormTime, i0, i1));
        }

        if( RotationData )
        {
            pSpatial->Local.SetRotate(GetRotate(fNormTime, i0, i1));
        }

        if( TranslationTimes == ScaleTimes )
        {
            // T == R == S
            if( ScaleData )
            {
                pSpatial->Local.SetUniformScale(GetScale(fNormTime, i0, i1));
            }
        }
        else
        {
            // T == R != S
            if( ScaleTimes && ScaleData )
            {
                GetKeyInfo(fCtrlTime, ScaleTimes->GetCount(),
                    ScaleTimes->GetData(), m_iSLastIndex, fNormTime, i0, i1);
                pSpatial->Local.SetUniformScale(GetScale(fNormTime, i0, i1));
            }
        }
    }
    else if( TranslationTimes == ScaleTimes )
    {
        // R != T == S
        if( TranslationTimes )
        {
            GetKeyInfo(fCtrlTime, TranslationTimes->GetCount(),
                TranslationTimes->GetData(), m_iTLastIndex, fNormTime, i0, i1);
        }

        if( TranslationData )
        {
            pSpatial->Local.SetTranslate(GetTranslate(fNormTime, i0, i1));
        }

        if( ScaleData )
        {
            pSpatial->Local.SetUniformScale(GetScale(fNormTime, i0, i1));
        }

        if( RotationTimes && RotationData )
        {
            GetKeyInfo(fCtrlTime, RotationTimes->GetCount(),
                RotationTimes->GetData(), m_iRLastIndex, fNormTime, i0, i1);
            pSpatial->Local.SetRotate(GetRotate(fNormTime, i0, i1));
        }
    }
    else if( RotationTimes == ScaleTimes )
    {
        // S == R != T
        if( RotationTimes )
        {
            GetKeyInfo(fCtrlTime, RotationTimes->GetCount(),
                RotationTimes->GetData(), m_iRLastIndex, fNormTime, i0, i1);
        }

        if( RotationData )
        {
            pSpatial->Local.SetRotate(GetRotate(fNormTime, i0, i1));
        }

        if( ScaleData )
        {
            pSpatial->Local.SetUniformScale(GetScale(fNormTime, i0, i1));
        }

        if( TranslationTimes && TranslationData )
        {
            GetKeyInfo(fCtrlTime, TranslationTimes->GetCount(),
                TranslationTimes->GetData(), m_iTLastIndex, fNormTime, i0, i1);
            pSpatial->Local.SetTranslate(GetTranslate(fNormTime, i0, i1));
        }
    }
    else
    {
        // S != R, T != R, R != T
        if( TranslationTimes && TranslationData )
        {
            GetKeyInfo(fCtrlTime, TranslationTimes->GetCount(),
                TranslationTimes->GetData(), m_iTLastIndex, fNormTime, i0, i1);
            pSpatial->Local.SetTranslate(GetTranslate(fNormTime, i0, i1));
        }

        if( RotationTimes && RotationData )
        {
            GetKeyInfo(fCtrlTime, RotationTimes->GetCount(),
                RotationTimes->GetData(), m_iRLastIndex, fNormTime, i0, i1);
            pSpatial->Local.SetRotate(GetRotate(fNormTime, i0, i1));
        }

        if( ScaleTimes && ScaleData )
        {
            GetKeyInfo(fCtrlTime, ScaleTimes->GetCount(),
                ScaleTimes->GetData(), m_iSLastIndex, fNormTime, i0, i1);
            pSpatial->Local.SetUniformScale(GetScale(fNormTime, i0, i1));
        }
    }

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* KeyframeController::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = Controller::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( TranslationTimes )
    {
        pFound = TranslationTimes->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( TranslationData )
    {
        pFound = TranslationData->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( RotationTimes )
    {
        pFound = RotationTimes->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( RotationData )
    {
        pFound = RotationData->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( ScaleTimes )
    {
        pFound = ScaleTimes->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( ScaleData )
    {
        pFound = ScaleData->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void KeyframeController::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    Controller::GetAllObjectsByName(rName, rObjects);

    if( TranslationTimes )
    {
        TranslationTimes->GetAllObjectsByName(rName, rObjects);
    }

    if( TranslationData )
    {
        TranslationData->GetAllObjectsByName(rName, rObjects);
    }

    if( RotationTimes )
    {
        RotationTimes->GetAllObjectsByName(rName, rObjects);
    }

    if( RotationData )
    {
        RotationData->GetAllObjectsByName(rName, rObjects);
    }

    if( ScaleTimes )
    {
        ScaleTimes->GetAllObjectsByName(rName, rObjects);
    }

    if( ScaleData )
    {
        ScaleData->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
SEObject* KeyframeController::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = Controller::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( TranslationTimes )
    {
        pFound = TranslationTimes->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( TranslationData )
    {
        pFound = TranslationData->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( RotationTimes )
    {
        pFound = RotationTimes->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( RotationData )
    {
        pFound = RotationData->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( ScaleTimes )
    {
        pFound = ScaleTimes->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( ScaleData )
    {
        pFound = ScaleData->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void KeyframeController::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Controller::Load(rStream, pLink);

    // link data
    SEObject* pObject;
    rStream.Read(pObject);  // TranslationTimes
    pLink->Add(pObject);

    rStream.Read(pObject);  // TranslationData
    pLink->Add(pObject);

    rStream.Read(pObject);  // RotationTimes
    pLink->Add(pObject);

    rStream.Read(pObject);  // RotationData
    pLink->Add(pObject);

    rStream.Read(pObject);  // ScaleTimes
    pLink->Add(pObject);

    rStream.Read(pObject);  // ScaleData
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(KeyframeController);
}
//----------------------------------------------------------------------------
void KeyframeController::Link(SEStream& rStream, SEStream::Link* pLink)
{
    Controller::Link(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    TranslationTimes = (FloatArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    TranslationData = (Vector3fArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    RotationTimes = (FloatArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    RotationData = (QuaternionfArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    ScaleTimes = (FloatArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    ScaleData = (FloatArray*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool KeyframeController::Register(SEStream& rStream) const
{
    if( !Controller::Register(rStream) )
    {
        return false;
    }

    if( TranslationTimes )
    {
        TranslationTimes->Register(rStream);
    }

    if( TranslationData )
    {
        TranslationData->Register(rStream);
    }

    if( RotationTimes )
    {
        RotationTimes->Register(rStream);
    }

    if( RotationData )
    {
        RotationData->Register(rStream);
    }

    if( ScaleTimes )
    {
        ScaleTimes->Register(rStream);
    }

    if( ScaleData )
    {
        ScaleData->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void KeyframeController::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Controller::Save(rStream);

    // link data
    rStream.Write(TranslationTimes);
    rStream.Write(TranslationData);
    rStream.Write(RotationTimes);
    rStream.Write(RotationData);
    rStream.Write(ScaleTimes);
    rStream.Write(ScaleData);

    SE_END_DEBUG_STREAM_SAVE(KeyframeController);
}
//----------------------------------------------------------------------------
int KeyframeController::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return Controller::GetDiskUsed(rVersion) +
        sizeof(TranslationTimes) +
        sizeof(TranslationData) +
        sizeof(RotationTimes) +
        sizeof(RotationData) +
        sizeof(ScaleTimes) +
        sizeof(ScaleData);
}
//----------------------------------------------------------------------------
SEStringTree* KeyframeController::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Controller::SaveStrings());
    if( TranslationTimes )
    {
        pTree->Append(TranslationTimes->SaveStrings("trn times"));
    }
    if( TranslationData )
    {
        pTree->Append(TranslationData->SaveStrings("trn data"));
    }
    if( RotationTimes )
    {
        pTree->Append(RotationTimes->SaveStrings("rot times"));
    }
    if( RotationData )
    {
        pTree->Append(RotationData->SaveStrings("rot data"));
    }
    if( ScaleTimes )
    {
        pTree->Append(ScaleTimes->SaveStrings("sca times"));
    }
    if( ScaleData )
    {
        pTree->Append(ScaleData->SaveStrings("sca data"));
    }

    return pTree;
}
//----------------------------------------------------------------------------
