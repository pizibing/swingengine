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
#include "SENode.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SENode, SESpatial);
SE_IMPLEMENT_STREAM(SENode);

//SE_REGISTER_STREAM(SENode);

//----------------------------------------------------------------------------
SENode::SENode()
{
}
//----------------------------------------------------------------------------
SENode::~SENode()
{
    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatialPtr spChild = DetachChildAt(i);
        spChild = 0;
    }
}
//----------------------------------------------------------------------------
int SENode::AttachChild(SESpatial* pChild)
{
    // 一些开发者希望node节点对象可以有多个父节点,从而使场景视图成为DAG.
    // 实际上不是这样,场景视图结构是一个树型结构.
    // 这个断言的使用,使开发者意识到当前子节点的原有亲子关系正要被破坏,
    // 为了安全考虑,你应该首先调用DetachChild函数使子节点脱离原有亲子关系,
    // 之后再调用AttachChild或SetChild函数.
    // 但是一定要注意到,调用DetachChild时有可能使你的子节点引用计数为0从而自我
    // 析构,安全的做法是,用一个智能指针引用该子节点,然后调用DetachChild,如下
    // 所示:
    //
    //     SENode* pNode0 = SE_NEW SENode;
    //     SESpatial* pChild0 = <...>;
    //     pNode0->AttachChild(pChild0);  // child at index 0
    //     SENode* pNode1 = <...>;
    //
    //     // 这将会产生断言,因为pChild0已经有父节点(pNode0).
    //     pNode1->AttachChild(pChild0);
    //
    //     // 取而代之我们应这样做,同时防止子节点自我析构.
    //     SESpatialPtr spSaveChild = pNode0->GetChild(0);
    //     pNode0->DetachChild(spSaveChild);
    //     pNode1->AttachChild(spSaveChild);

    SE_ASSERT( pChild && !pChild->GetParent() );

    pChild->SetParent(this);

    // 是否有空slot
    int iCount = (int)m_Child.size();
    for( int i = 0; i < iCount; i++ )
    {
        if( m_Child[i] == 0 )
        {
            // 有则插入
            m_Child[i] = pChild;

            return i;
        }
    }

    // 插入在尾部
    m_Child.push_back(pChild);

    return iCount;
}
//----------------------------------------------------------------------------
int SENode::DetachChild(SESpatial* pChild)
{
    if( pChild )
    {
        // 是否存在
        for( int i = 0; i < (int)m_Child.size(); i++ )
        {
            if( m_Child[i] == pChild )
            {
                // 存在则移除
                pChild->SetParent(0);
                m_Child[i] = 0;

                return i;
            }
        }
    }

    return -1;
}
//----------------------------------------------------------------------------
SESpatialPtr SENode::DetachChildAt(int i)
{
    if( 0 <= i && i < (int)m_Child.size() )
    {
        SESpatialPtr spChild = m_Child[i];
        if( spChild )
        {
            // 存在则移除
            spChild->SetParent(0);
            m_Child[i] = 0;
        }

        return spChild;
    }

    return 0;
}
//----------------------------------------------------------------------------
SESpatialPtr SENode::SetChild(int i, SESpatial* pChild)
{
    // 一些开发者希望node节点对象可以有多个父节点,从而使场景视图成为DAG.
    // 实际上不是这样,场景视图结构是一个树型结构.
    // 这个断言的使用,使开发者意识到当前子节点的原有亲子关系正要被破坏,
    // 为了安全考虑,你应该首先调用DetachChild函数使子节点脱离原有亲子关系,
    // 之后再调用AttachChild或SetChild函数.
    // 但是一定要注意到,调用DetachChild时有可能使你的子节点引用计数为0从而自我
    // 析构,安全的做法是,用一个智能指针引用该子节点,然后调用DetachChild,如下
    // 所示:
    //
    //     SENode* pNode0 = SE_NEW SENode;
    //     SESpatial* pChild0 = <...>;
    //     pNode0->AttachChild(pChild0);  // child at index 0
    //     SENode* pNode1 = <...>;
    //
    //     // 这将会产生断言,因为pChild0已经有父节点(pNode0).
    //     pNode1->AttachChild(pChild0);
    //
    //     // 取而代之我们应这样做,同时防止子节点自我析构.
    //     SESpatialPtr spSaveChild = pNode0->GetChild(0);
    //     pNode0->DetachChild(spSaveChild);
    //     pNode1->AttachChild(spSaveChild);

    if( pChild )
    {
        SE_ASSERT( !pChild->GetParent() );
    }

    if( 0 <= i && i < (int)m_Child.size() )
    {
        // 移除slot中旧有子节点
        SESpatialPtr spPreviousChild = m_Child[i];
        if( spPreviousChild )
        {
            spPreviousChild->SetParent(0);
        }

        // 加入新的子节点到slot
        if( pChild )
        {
            pChild->SetParent(this);
        }

        m_Child[i] = pChild;

        return spPreviousChild;
    }

    // 索引超过范围,则加入尾部
    pChild->SetParent(this);
    m_Child.push_back(pChild);

    return 0;
}
//----------------------------------------------------------------------------
SESpatialPtr SENode::GetChild(int i)
{
    if( 0 <= i && i < (int)m_Child.size() )
    {
        return m_Child[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
void SENode::UpdateWorldData(double dAppTime)
{
    SESpatial::UpdateWorldData(dAppTime);

    // SENode节点有责任进行AB递归,从而完成树的遍历.
    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pChild->UpdateGS(dAppTime, false);
        }
    }
}
//----------------------------------------------------------------------------
void SENode::UpdateWorldBound()
{
    if( !WorldBoundIsCurrent )
    {
        // 这是一个贪心算法的BV合并,
        // 最终产生的BV包含所有子节点的BV,但并不能保证是最小BV,
        // 能够产生最小BV的算法时间复杂度较高且极其复杂,因此不予采用.
        bool bFoundFirstBound = false;
        for( int i = 0; i < (int)m_Child.size(); i++ )
        {
            SESpatial* pChild = m_Child[i];
            if( pChild )
            {
                if( bFoundFirstBound )
                {
                    // 用当前world bound与子节点world bound合并
                    WorldBound->GrowToContain(pChild->WorldBound);
                }
                else
                {
                    // 首先把world bound设置为第一个非空子节点的world bound
                    bFoundFirstBound = true;
                    WorldBound->CopyFrom(pChild->WorldBound);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void SENode::UpdateState(std::vector<SEGlobalState*>* aGStack,
    std::vector<SELight*>* pLStack)
{
    // SENode节点有责任进行AB递归,从而完成树的遍历.
    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pChild->UpdateRS(aGStack, pLStack);
        }
    }
}
//----------------------------------------------------------------------------
void SENode::GetUnculledSet(SECuller& rCuller, bool bNoCull)
{
    int i;
    for( i = 0; i < (int)m_Effects.size(); i++ )
    {
        // 这是一个global effect.
        // 在可见对象集中加入一个'开始'标记,表明一个global effect作用域的开始.
        rCuller.Insert(this, m_Effects[i]);
    }

    // SENode节点有责任进行AB递归,从而完成场景视图树的遍历.
    // 所有被加入可见对象集中的SEGeometry子节点都处在当前节点global effect的作
    // 用域中,这些SEGeometry子节点都将使用该global effect进行渲染.
    for( i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pChild->OnGetUnculledSet(rCuller, bNoCull);
        }
    }

    for( i = 0; i < (int)m_Effects.size(); i++ )
    {
        // 在可见对象集中加入一个'结束'标记,表明一个global effect作用域的结束.
        rCuller.Insert(0, 0);
    }
}
//----------------------------------------------------------------------------
void SENode::DoPick(const SERay3f& rRay, PickArray& rResults)
{
    if( WorldBound->TestIntersection(rRay) )
    {
        for( int i = 0; i < (int)m_Child.size(); i++ )
        {
            SESpatial* pChild = m_Child[i];
            if( pChild )
            {
                pChild->DoPick(rRay, rResults);
            }
        }
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SENode::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SESpatial::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pFound = pChild->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SENode::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SESpatial::GetAllObjectsByName(rName, rObjects);

    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pChild->GetAllObjectsByName(rName, rObjects);
        }
    }
}
//----------------------------------------------------------------------------
SEObject* SENode::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SESpatial::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pFound = pChild->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SENode::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SESpatial::Load(rStream, pLink);

    // link data
    int iMaxCount, iGrowBy, iCount;
    rStream.Read(iMaxCount);
    m_Child.resize(iMaxCount);

    // TO DO:  The growby parameter no longer exists, but to remove it
    // requires fixing the streaming system "IsValid" behavior.
    rStream.Read(iGrowBy);

    rStream.Read(iCount);
    for( int i = 0; i < iMaxCount; i++ )
    {
        SEObject* pObject;
        rStream.Read(pObject);
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SENode);
}
//----------------------------------------------------------------------------
void SENode::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SESpatial::SELink(rStream, pLink);

    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        SESpatial* pChild = (SESpatial*)rStream.GetFromMap(pLinkID);
        if( pChild )
        {
            SetChild(i, pChild);
        }
    }
}
//----------------------------------------------------------------------------
bool SENode::Register(SEStream& rStream) const
{
    if( !SESpatial::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        if( m_Child[i] )
        {
            m_Child[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SENode::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SESpatial::Save(rStream);

    // link data
    rStream.Write((int)m_Child.size());  // was maxcount

    // TO DO: Delete these lines once streaming is fixed.
    int iGrowBy = 0;
    rStream.Write(iGrowBy);

    rStream.Write((int)m_Child.size());
    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        rStream.Write(m_Child[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SENode);
}
//----------------------------------------------------------------------------
int SENode::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SESpatial::GetDiskUsed(rVersion) +
        3*sizeof(int) +  // m_Child maxcount, growby, count
        ((int)m_Child.size())*sizeof(m_Child[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SENode::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("child count =", (int)m_Child.size()));

    // children
    pTree->Append(SESpatial::SaveStrings());
    for( int i = 0; i < (int)m_Child.size(); i++ )
    {
        SESpatial* pChild = m_Child[i];
        if( pChild )
        {
            pTree->Append(pChild->SaveStrings());
        }
        else
        {
            SEStringTree* pEmpty = SE_NEW SEStringTree;
            pEmpty->Append(Format("unused slot"));
            pTree->Append(pEmpty);
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
