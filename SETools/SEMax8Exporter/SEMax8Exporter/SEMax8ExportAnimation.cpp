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

#include "SEMax8SceneBuilder.h"
#include "decomp.h"
#include <algorithm>

using namespace std;
using namespace Swing;

//----------------------------------------------------------------------------
bool Max8SceneBuilder::AreEqual(const Point3& rPoint1, const Point3& rPoint2)
{   
    // 在指定精确度下的模糊比较.

    return fabsf(rPoint1.x - rPoint2.x) <= MIN_DIFFERENCE
        && fabsf(rPoint1.y - rPoint2.y) <= MIN_DIFFERENCE
        && fabsf(rPoint1.z - rPoint2.z) <= MIN_DIFFERENCE;
}
//----------------------------------------------------------------------------
bool Max8SceneBuilder::AreEqual(const Quat& rQuat1, const Quat& rQuat2)
{
    // 在指定精确度下的模糊比较.

    return fabsf(rQuat1.x - rQuat2.x) <= MIN_DIFFERENCE
        && fabsf(rQuat1.y - rQuat2.y) <= MIN_DIFFERENCE
        && fabsf(rQuat1.z - rQuat2.z) <= MIN_DIFFERENCE
        && fabsf(rQuat1.w - rQuat2.w) <= MIN_DIFFERENCE;
}
//----------------------------------------------------------------------------
bool Max8SceneBuilder::CompareKeyTimes(KeyInfo* pFirst, KeyInfo* pSecond)
{
    return pFirst->Time < pSecond->Time;
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::BuildKeyFrameController(INode* pMaxNode,
    SESpatial* pSENode)
{
    // 为一个具备关键桢动画的节点添加一个key frame controller.
    // 注意我们不支持非统一缩放的动画.
    //
    // pMaxNode:
    //     具备关键桢动画的Max节点指针.
    // pSENode:
    //     将被添加关键桢动画的Swing Engine场景视图节点指针.

    assert( pSENode );
    assert( pMaxNode );

    // 检查该Max节点是否带有关键桢动画.
    Control* pTMC = pMaxNode->GetTMController();

    assert( pTMC );

    if( !pTMC->IsKeyable() )
    {
        // 节点不具备关键桢动画,但仍可能含有动画信息,
        // 比如有可能是一个IK节点.
        // 那样的话,导出节点动画的所有桢.
        BuildFrameController(pMaxNode, pSENode);

        return;
    }

    // 出于优化的目的,检查该节点的平移,旋转和缩放是否在我们选定的区间上发生了变化.
    AnimationTiming tempTrnTiming, tempRotTiming, tempScaTiming;
    if( !GetAnimationTiming(pMaxNode, tempTrnTiming, tempRotTiming, tempScaTiming) )
    {
        return;
    }

    vector<KeyInfo*> tempKeyInfo;

    // 处理平移关键桢
    int iNumTrnKeys = 0;
    if( tempTrnTiming.Active )
    {
        Control* pPC = pTMC->GetPositionController();
        if( pPC )
        {		
            IKeyControl* pKeyCon = GetKeyControlInterface(pPC);
            if( pKeyCon )
            {
                iNumTrnKeys = pKeyCon->GetNumKeys();
                GetTrnKeyInfo(iNumTrnKeys, pPC->ClassID(), pKeyCon, tempTrnTiming,
                    tempKeyInfo);
            }
        }
    }

    // 处理旋转关键桢
    int iNumRotKeys = 0;
    if( tempRotTiming.Active )
    {
        Control* pRC = pTMC->GetRotationController();
        if( pRC )
        {
            IKeyControl* pKeyCon = GetKeyControlInterface(pRC);
            if( pKeyCon )
            {
                iNumRotKeys = pKeyCon->GetNumKeys();
                GetRotKeyInfo(iNumRotKeys, pRC->ClassID(), pKeyCon, tempRotTiming,
                    tempKeyInfo);
            }
        }
    }

    // 处理缩放关键桢
    int iNumScaKeys = 0;
    if( tempScaTiming.Active )
    {
        Control* pSC = pTMC->GetScaleController();
        if( pSC )
        {
            IKeyControl* pKeyCon = GetKeyControlInterface(pSC);
            if( pKeyCon )
            {
                iNumScaKeys = pKeyCon->GetNumKeys();
                GetScaleKeyInfo(iNumScaKeys, pSC->ClassID(), pKeyCon, tempScaTiming,
                    tempKeyInfo);
            }
        }
    }

    // 如果一个对象使用了程序控制器,而没有使用关键桢控制器,
    // 则以上所有的GetKeyControlInterface函数都会返回NULL,
    // 因为程序控制器中没有"关键桢"的概念.
    // 那样的话,将会没有关键桢信息.
    if( !iNumTrnKeys && !iNumRotKeys && !iNumScaKeys )
    {
        BuildFrameController(pMaxNode, pSENode);

        return;
    }

    // 根据获得的Max关键桢信息,创建相应的Swing Engine关键桢控制器分量空间.
    SEKeyframeController* pSEKFC = new SEKeyframeController;
    if( iNumTrnKeys > 0 )
    {
        pSEKFC->TranslationTimes = new SEFloatArray(iNumTrnKeys,
            new float[iNumTrnKeys]);
        pSEKFC->TranslationData = new SEVector3fArray(iNumTrnKeys,
            new SEVector3f[iNumTrnKeys]);
    }
    if( iNumRotKeys > 0 )
    {
        pSEKFC->RotationTimes = new SEFloatArray(iNumRotKeys,
            new float[iNumRotKeys]);
        pSEKFC->RotationData = new SEQuaternionfArray(iNumRotKeys,
            new SEQuaternionf[iNumRotKeys]);
    }
    if( iNumScaKeys > 0 )
    {
        pSEKFC->ScaleTimes = new SEFloatArray(iNumScaKeys,
            new float[iNumScaKeys]);
        pSEKFC->ScaleData = new SEFloatArray(iNumScaKeys,
            new float[iNumScaKeys]);
    }

    // 根据时间值进行升序排序.
    sort(tempKeyInfo.begin(), tempKeyInfo.end(), CompareKeyTimes);

    SEVector3f* pTKey = (pSEKFC->TranslationData ? 
        pSEKFC->TranslationData->GetData() : NULL);
    float* pfTTime = (pSEKFC->TranslationTimes ?
        pSEKFC->TranslationTimes->GetData() : NULL);

    SEQuaternionf* pRKey = (pSEKFC->RotationData ?
        pSEKFC->RotationData->GetData() : NULL);
    float* pfRTime = (pSEKFC->RotationTimes ?
        pSEKFC->RotationTimes->GetData() : NULL);

    float* pfSKey = (pSEKFC->ScaleData ?
        pSEKFC->ScaleData->GetData() : NULL);
    float* pfSTime = (pSEKFC->ScaleTimes ?
        pSEKFC->ScaleTimes->GetData() : NULL);

    TimeValue iTimeNow = -1;
    SETransformation tempTransform;
    for( int i = 0; i < (int)tempKeyInfo.size(); i++ )
    {
        KeyInfo* pInfo = tempKeyInfo[i];

        if( iTimeNow != pInfo->Time )
        {
            iTimeNow = pInfo->Time;
            tempTransform = GetLocalTransform(pMaxNode, iTimeNow);
        }

        switch( pInfo->Type )
        {
        case KT_TRANSLATION:
            assert( pTKey );
            assert( pfTTime );

            *pTKey++ = tempTransform.GetTranslate();
            *pfTTime++ = TicksToSec(iTimeNow - m_iTimeOffset);

            break;
        case KT_ROTATION:
            // 待实现.
            // 尚未支持非SR变换.
            if( tempTransform.IsSRMatrix() )
            {
                assert( pRKey );
                assert( pfRTime );

                // 待检查.
                // q和-q表示同样的旋转变换.
                // 但为了保持q和next q之间的最小夹角,因此使其保持符号一致.
                pRKey->FromRotationMatrix(tempTransform.GetRotate());
                if( pRKey->W < 0.0f )
                {
                    *pRKey = -*pRKey;
                }
                pRKey++;
                *pfRTime++ = TicksToSec(iTimeNow - m_iTimeOffset);
            }

            break;
        case KT_SCALE:
        {
            // 待实现.
            // 尚未支持非统一缩放变换或负缩放系数变换.
            float fMax;
            if( tempTransform.IsUniformScale() )
            {
                fMax = tempTransform.GetUniformScale();
            }
            else
            {
                fMax = SEMathf::FAbs(tempTransform.GetScale().X);
                float fAbs = SEMathf::FAbs(tempTransform.GetScale().Y);
                if( fAbs > fMax )
                {
                    fMax = fAbs;
                }
                fAbs = SEMathf::FAbs(tempTransform.GetScale().Z);
                if( fAbs > fMax )
                {
                    fMax = fAbs;
                }
            }

            assert( pfSKey );
            assert( pfSTime );

            *pfSKey++ = fMax;
            *pfSTime++ = TicksToSec(iTimeNow - m_iTimeOffset);

            break;
        }
        }

        delete pInfo;
    }

    pSEKFC->Repeat = SEController::RT_WRAP;
    pSEKFC->MinTime = TicksToSec(m_iTimeStart - m_iTimeOffset);
    pSEKFC->MaxTime = TicksToSec(m_iTimeEnd - m_iTimeOffset);
    pSENode->AttachController(pSEKFC);
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::BuildFrameController(INode* pNode,
    SESpatial* pSENode)
{
    // 为一个具备动画信息的节点添加一个"桢控制器".
    // 这个函数导出该节点的所有桢,而不仅仅是关键桢.
    // 为该节点所创建的SEKeyframeController带有该节点每桢的SRT变换信息.
    // 这显然不是最优的,在Swing Engine场景中,该节点相邻的两桢变换之间依然要被插值,
    // 然而,在动画师使用IK动画时,它将会有用,尽管导出器目前还不支持IK控制器.
    // 注意我们不支持非统一缩放变换的动画.
    //
    // pNode:
    //     带有动画信息的Max节点指针.
    // pSENode:
    //     Swing Engine场景视图中的带有动画信息的节点.

    // 存储所有唯一的桢数据(使用模糊比较).
    vector<int> tempTTime, tempRTime, tempSTime;
    vector<Point3> tempTData, tempSData;
    vector<Quat> tempRData;

    // 获取初始变换分量.
    // 每个后继的变换分量都与之前的变换分量进行比较,从而判断是否发生了变化.
    // 如果发生了变化,则新的变换分量被加入列表.否则忽略掉.
    // 最后,如果一个数组只有一个元素,则不创建任何keyframe数据.
    int iTime = m_iTimeStart;
    Matrix3 tempLocal = pNode->GetNodeTM(iTime) * Inverse(pNode->GetParentTM(iTime));
    AffineParts tempAffParts;
    decomp_affine(tempLocal, &tempAffParts);
    tempTTime.push_back(iTime);
    tempRTime.push_back(iTime);
    tempSTime.push_back(iTime);
    tempTData.push_back(tempAffParts.t);
    tempRData.push_back(tempAffParts.q);
    tempSData.push_back(tempAffParts.k);

    // 待实现.
    // 判断tempAffParts.f是否为负.
    // 这表示负缩放系数或反射变换.

    // 创建动画采样桢数据.
    for( iTime += m_iTicksPerFrame; iTime <= m_iTimeEnd; iTime += m_iTicksPerFrame )
    {
        tempLocal = pNode->GetNodeTM(iTime) * Inverse(pNode->GetParentTM(iTime));
        decomp_affine(tempLocal, &tempAffParts);

        if( !AreEqual(tempAffParts.t, tempTData.back()) )
        {
            tempTTime.push_back(iTime);
            tempTData.push_back(tempAffParts.t);
        }

        if( !AreEqual(tempAffParts.q, tempRData.back()) )
        {
            // q和-q表示同样的旋转变换.
            if( !AreEqual(-tempAffParts.q, tempRData.back()) )
            {
                tempRTime.push_back(iTime);

                // 总是储存连续的四元数,从而使它们之间的夹角保持最小化.
                float fDot = tempAffParts.q % tempRData.back();
                if( fDot > 0.0f )
                    tempRData.push_back(tempAffParts.q);
                else
                    tempRData.push_back(-tempAffParts.q);
            }
        }

        if( !AreEqual(tempAffParts.k, tempSData.back()) )
        {
            tempSTime.push_back(iTime);
            tempSData.push_back(tempAffParts.f*tempAffParts.k);
        }

        // 判断是否为统一缩放变换.
        bool bScaleIsUniform =
            fabsf(tempAffParts.k.x - tempAffParts.k.y) < MIN_DIFFERENCE &&
            fabsf(tempAffParts.k.y - tempAffParts.k.z) < MIN_DIFFERENCE;

        // 判断缩放系数是否都为1.
        bool bScaleIsUnity = bScaleIsUniform &&
            fabsf(tempAffParts.k.x - 1.0f) < MIN_DIFFERENCE;

        // 判断scale-orientation是否为单位变换.
        if( tempAffParts.u.w < 0.0f )
            tempAffParts.u = -tempAffParts.u;

        bool bOrientIsIdentity = bScaleIsUniform || (
            fabsf(tempAffParts.u.w - 1.0f) < MIN_DIFFERENCE &&
            fabsf(tempAffParts.u.x) < MIN_DIFFERENCE &&
            fabsf(tempAffParts.u.y) < MIN_DIFFERENCE &&
            fabsf(tempAffParts.u.z) < MIN_DIFFERENCE);

        int iStopHere = 0;
    }

    if( tempTData.size() == 1 && tempRData.size() == 1 && tempSData.size() == 1 )
    {
        // 这个节点没有动画信息
        return;
    }

    // 待实现.
    // 判断是否有完全相同的数组,从而它们可以被共享.

    SEKeyframeController* pSEKFCtrl = new SEKeyframeController;
    pSEKFCtrl->MinTime = TicksToSec(m_iTimeStart - m_iTimeOffset);
    pSEKFCtrl->MaxTime = TicksToSec(m_iTimeEnd - m_iTimeOffset);
    pSEKFCtrl->Repeat = SEController::RT_WRAP;

    if( tempTData.size() > 1 )
    {
        int iNumTKeys = (int)tempTData.size();
        float* afTTime = new float[iNumTKeys];
        SEVector3f* aTData = new SEVector3f[iNumTKeys];
        for( int i = 0; i < iNumTKeys; i++ )
        {
            afTTime[i] = TicksToSec(tempTTime[i] - m_iTimeOffset);
            aTData[i].X = tempTData[i].x;
            aTData[i].Y = tempTData[i].z;
            aTData[i].Z = tempTData[i].y;
        }

        pSEKFCtrl->TranslationTimes = new SEFloatArray(iNumTKeys, afTTime);
        pSEKFCtrl->TranslationData = new SEVector3fArray(iNumTKeys, aTData);
    }

    if( tempRData.size() > 1 )
    {
        int iNumRKeys = (int)tempRData.size();
        float* afRTime = new float[iNumRKeys];
        SEQuaternionf* aRData = new SEQuaternionf[iNumRKeys];
        for( int i = 0; i < iNumRKeys; i++ )
        {
            afRTime[i] = TicksToSec(tempRTime[i] - m_iTimeOffset);
            aRData[i].W = tempRData[i].w;
            aRData[i].X = +tempRData[i].x;
            aRData[i].Y = +tempRData[i].z;
            aRData[i].Z = +tempRData[i].y;

            // DEBUGGING
            SEVector3f tempAxis;
            float fAngle;
            aRData[i].ToAxisAngle(tempAxis, fAngle);
            int iStopHere = 0;
        }

        pSEKFCtrl->RotationTimes = new SEFloatArray(iNumRKeys, afRTime);
        pSEKFCtrl->RotationData = new SEQuaternionfArray(iNumRKeys, aRData);
    }

    if( tempSData.size() > 1 )
    {
        int iNumSKeys = (int)tempSData.size();
        float* afSTime = new float[iNumSKeys];
        float* afSData = new float[iNumSKeys];
        for( int i = 0; i < iNumSKeys; i++ )
        {
            afSTime[i] = TicksToSec(tempSTime[i] - m_iTimeOffset);
            afSData[i] = tempSData[i].x;
        }

        pSEKFCtrl->ScaleTimes = new SEFloatArray(iNumSKeys, afSTime);
        pSEKFCtrl->ScaleData = new SEFloatArray(iNumSKeys, afSData);
    }

    pSENode->AttachController(pSEKFCtrl);
}
//----------------------------------------------------------------------------
bool Max8SceneBuilder::GetAnimationTiming(INode* pNode,
    AnimationTiming& rTTiming, AnimationTiming& rRTiming,
    AnimationTiming& rSTiming)
{
    // 通过检查一个节点在指定时间区间上是否发生了较大的变换(忽略小误差),
    // 从而决定该节点是否有动画信息.

    int iTicksPerFrame = GetTicksPerFrame();
    Matrix3 tempNodeTM;
    AffineParts tempAffParts;
    Point3 tempPrevTrans, tempRotAxis, tempPrevRotAxis, tempPrevScaleFactor;
    float fRotAngle, fPrevRotAngle;
    rTTiming.Active = FALSE;
    rRTiming.Active = FALSE;
    rSTiming.Active = FALSE;

    // 获取节点的初始变换各分量.
    tempNodeTM = pNode->GetNodeTM(m_iTimeStart) * Inverse(pNode->GetParentTM(
        m_iTimeStart));
    decomp_affine(tempNodeTM, &tempAffParts);
    AngAxisFromQ(tempAffParts.q, &fPrevRotAngle, tempPrevRotAxis);
    tempPrevTrans = tempAffParts.t;
    tempPrevScaleFactor = tempAffParts.k;

    // 循环访问所有桢,确认节点某变换分量是否发生改变.
    TimeValue iTimeNow = m_iTimeStart + iTicksPerFrame;
    for( /**/; iTimeNow <= m_iTimeEnd; iTimeNow += iTicksPerFrame )
    {
        tempNodeTM = pNode->GetNodeTM(iTimeNow) * Inverse(pNode->GetParentTM(iTimeNow));
        decomp_affine(tempNodeTM, &tempAffParts);
        AngAxisFromQ(tempAffParts.q, &fRotAngle, tempRotAxis);

        if( !rTTiming.Active )
        {
            // 比较当前桢和之前桢的平移分量是否相等.
            if( !AreEqual(tempAffParts.t, tempPrevTrans) )
            {
                // 平移分量改变,记录改变前的桢时间.
                rTTiming.Active = TRUE;
                rTTiming.Start = iTimeNow - iTicksPerFrame;
                rTTiming.End = iTimeNow;
            }
        }
        else
        {
            // 如果平移分量仍在改变,则更新平移动画的结束时间.
            if( !AreEqual(tempAffParts.t, tempPrevTrans) )
            {
                rTTiming.End = iTimeNow;
            }
        }

        if( !rRTiming.Active )
        {
            // 比较当前桢和之前桢的旋转分量是否相等.
            if( fabsf(fRotAngle - fPrevRotAngle) > MIN_DIFFERENCE
            ||   !AreEqual(tempRotAxis, tempPrevRotAxis) )
            {
                // 旋转分量改变,记录改变前的桢时间.
                rRTiming.Active = TRUE;
                rRTiming.Start = iTimeNow - iTicksPerFrame;
                rRTiming.End = iTimeNow;
            }
        }
        else
        {
            // 如果旋转分量仍在改变,则更新旋转动画的结束时间.
            if( fabsf(fRotAngle - fPrevRotAngle) > MIN_DIFFERENCE
            ||   !AreEqual(tempRotAxis, tempPrevRotAxis) )
            {
                rRTiming.End = iTimeNow;
            }
        }

        if( !rSTiming.Active )
        {
            // 比较当前桢和之前桢的缩放分量是否相等.
            if( !AreEqual(tempAffParts.k, tempPrevScaleFactor) )
            {
                // 缩放分量改变,记录改变前的桢时间.
                rSTiming.Active = TRUE;
                rSTiming.Start = iTimeNow - iTicksPerFrame;
                rSTiming.End = iTimeNow;
            }
        }
        else
        {
            // 如果缩放分量仍在改变,则更新缩放动画的结束时间.
            if( !AreEqual(tempAffParts.k, tempPrevScaleFactor) )
            {
                rSTiming.End = iTimeNow;
            }
        }

        fPrevRotAngle = fRotAngle;
        tempPrevRotAxis = tempRotAxis;
        tempPrevTrans = tempAffParts.t;
        tempPrevScaleFactor = tempAffParts.k;
    }

    return rTTiming.Active || rRTiming.Active || rSTiming.Active;
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::GetTrnKeyInfo(int& riNumKeys, Class_ID& rClassID, 
    IKeyControl* pKeyCon, AnimationTiming& rTTiming,
    vector<KeyInfo*>& rKeyInfo)
{       
    // 从Max节点的平移变换关键桢控制器获取平移变换关键桢.
    //
    // riNumKeys:
    //     作为输入参数时,体现要处理的关键桢数目.
    //     作为输出参数时,体现所需的Swing Engine关键桢数目.
    // class_ID:
    //     平移变换关键桢控制器的Max class ID.
    // pKeyCon:
    //     Max节点的平移变换关键桢控制器指针.
    // rTTiming:
    //     节点的平移动画发生时间的详细信息.
    // rKeyInfo:
    //     KeyInfo指针数组用来存储关键桢类型和时间信息.

    int i, iKeys = riNumKeys;
    riNumKeys = 0;

    if( rClassID == Class_ID(TCBINTERP_POSITION_CLASS_ID, 0) )
    {
        // 处理Tension/Continuity/Bias控制器
        ITCBPoint3Key tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rTTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rTTiming.End )
            {
                break;
            }
    
            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_TRANSLATION));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(HYBRIDINTERP_POSITION_CLASS_ID, 0) )
    {
        // 处理Bezier控制器
        IBezPoint3Key tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rTTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rTTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_TRANSLATION));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(LININTERP_POSITION_CLASS_ID, 0) )
    {
        // 处理Linear控制器
        ILinPoint3Key tempKey;
        for( int i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rTTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rTTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_TRANSLATION));
            riNumKeys++;
        }   
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::GetRotKeyInfo(int& riNumKeys, Class_ID& rClassID, 
    IKeyControl* pKeyCon, AnimationTiming& rRTiming,
    vector<KeyInfo*>& rKeyInfo)
{
    // 从Max节点的旋转变换关键桢控制器获取旋转变换关键桢.
    //
    // riNumKeys:
    //     作为输入参数时,体现要处理的关键桢数目.
    //     作为输出参数时,体现所需的Swing Engine关键桢数目.
    // class_ID:
    //     旋转变换关键桢控制器的Max class ID.
    // pKeyCon:
    //     Max节点的旋转变换关键桢控制器指针.
    // rRTiming:
    //     节点的旋转动画发生时间的详细信息.
    // rKeyInfo:
    //     KeyInfo指针数组用来存储关键桢类型和时间信息.

    int i, iKeys = riNumKeys;
    riNumKeys = 0;

    if( rClassID == Class_ID(TCBINTERP_ROTATION_CLASS_ID, 0) )
    {
        // 处理Tension/Continuity/Bias控制器
        ITCBRotKey tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rRTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rRTiming.End )
            {
                break;
            }
            
            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_ROTATION));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(HYBRIDINTERP_ROTATION_CLASS_ID, 0) )
    {
        // 处理Bezier控制器
        IBezQuatKey tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rRTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rRTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_ROTATION));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(LININTERP_ROTATION_CLASS_ID, 0) )
    {
        // 处理Linear控制器
        ILinRotKey tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rRTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rRTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_ROTATION));
            riNumKeys++;
        }   
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::GetScaleKeyInfo(int& riNumKeys, Class_ID& rClassID,
    IKeyControl* pKeyCon, AnimationTiming& rSTiming,
    vector<KeyInfo*>& rKeyInfo)
{
    // 从Max节点的缩放变换关键桢控制器获取缩放变换关键桢.
    //
    // riNumKeys:
    //     作为输入参数时,体现要处理的关键桢数目.
    //     作为输出参数时,体现所需的Swing Engine关键桢数目.
    // class_ID:
    //     缩放变换关键桢控制器的Max class ID.
    // pKeyCon:
    //     Max节点的缩放变换关键桢控制器指针.
    // rTTiming:
    //     节点的缩放动画发生时间的详细信息.
    // rKeyInfo:
    //     KeyInfo指针数组用来存储关键桢类型和时间信息.

    int i, iKeys = riNumKeys;
    riNumKeys = 0;

    if( rClassID == Class_ID(TCBINTERP_SCALE_CLASS_ID, 0) )
    {
        // 处理Tension/Continuity/Bias控制器
        ITCBScaleKey tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rSTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rSTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_SCALE));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(HYBRIDINTERP_SCALE_CLASS_ID, 0) )
    {
        // 处理Bezier控制器
        IBezScaleKey tempKey;
        for( i = 0; i < iKeys; i++ )
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rSTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rSTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_SCALE));
            riNumKeys++;
        }
    }
    else if( rClassID == Class_ID(LININTERP_SCALE_CLASS_ID, 0) )
    {
        // 处理Linear控制器
        ILinScaleKey tempKey;
        for( i = 0; i < iKeys; i++ ) 
        {
            pKeyCon->GetKey(i, &tempKey);
            if( tempKey.time < rSTiming.Start )
            {
                continue;
            }
            else if( tempKey.time > rSTiming.End )
            {
                break;
            }

            rKeyInfo.push_back(new KeyInfo(tempKey.time, KT_SCALE));
            riNumKeys++;
        }
    }
}
//----------------------------------------------------------------------------
