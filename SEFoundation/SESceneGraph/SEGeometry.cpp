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
#include "SEGeometry.h"
#include "SECuller.h"
#include "SELight.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Geometry, Spatial);
SE_IMPLEMENT_ABSTRACT_STREAM(Geometry);

//SE_REGISTER_STREAM(Geometry);

//----------------------------------------------------------------------------
Geometry::Geometry()
    :
    ModelBound(BoundingVolume::Create())
{
    RStateBlock = SE_NEW RenderStateBlock;
    LightingMode = GLM_PIPELINE_PIXEL;
}
//----------------------------------------------------------------------------
Geometry::Geometry(VertexBuffer* pVBuffer, IndexBuffer* pIBuffer)
    :
    VBuffer(pVBuffer),
    IBuffer(pIBuffer),
    ModelBound(BoundingVolume::Create())
{
    RStateBlock = SE_NEW RenderStateBlock;
    LightingMode = GLM_PIPELINE_PIXEL;
    UpdateModelBound();
}
//----------------------------------------------------------------------------
Geometry::~Geometry()
{
}
//----------------------------------------------------------------------------
void Geometry::UpdateMS(bool bUpdateNormals)
{
    UpdateModelBound();
    if( bUpdateNormals )
    {
        UpdateModelNormals();
    }
}
//----------------------------------------------------------------------------
void Geometry::UpdateModelBound()
{
    ModelBound->ComputeFromData(VBuffer);
}
//----------------------------------------------------------------------------
void Geometry::UpdateWorldBound()
{
    ModelBound->TransformBy(World, WorldBound);
}
//----------------------------------------------------------------------------
void Geometry::UpdateState(std::vector<GlobalState*>* aGStack,
    std::vector<Light*>* pLStack)
{
    // 更新当前几何体的render state block.
    // 收集到影响当前节点的所有栈顶元素.
    if( RStateBlock )
    {
        // 如果之前state block绑定了设备资源,则释放掉.
        // 目前只用于支持DirectX 10的render state objects资源.
        RStateBlock->Release();
    }
    else
    {
        RStateBlock = SE_NEW RenderStateBlock;
    }

    int i;
    for( i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        GlobalState* pGState = 0;
        pGState = aGStack[i].back();
        RStateBlock->States[i] = pGState;
    }

    // 更新lighting effect.
    // 收集到影响当前节点的所有light对象.
    Lights.clear();
    int iLCount = (int)pLStack->size();
    if( LightingMode < GLM_USER )
	{
        // 创建系统默认lighting effect.

        if( iLCount > 0 )
        {
            if( m_spLEffect )
            {
                m_spLEffect->DetachAllLights();

                if( m_Effects.size() == 0 )
                {
                    m_Effects.push_back(StaticCast<Effect>(m_spLEffect));
                }
                else if( m_Effects[0] != m_spLEffect )
                {
                    m_Effects.insert(m_Effects.begin(), StaticCast<Effect>(
                        m_spLEffect));
                }
            }
            else
            {
                m_spLEffect = SE_NEW LightingEffect;
                m_Effects.insert(m_Effects.begin(), StaticCast<Effect>(
                    m_spLEffect));
            }

            for( i = 0; i < iLCount; i++ )
            {
                m_spLEffect->AttachLight((*pLStack)[i]);
                Lights.push_back((*pLStack)[i]);
            }

            // 只要枚举顺序一致,则我们可以确保这个类型转换是安全的.
            m_spLEffect->Configure(
                (LightingEffect::LightingMode)LightingMode);
        }
        else
        {
            if( m_spLEffect )
            {
                SE_ASSERT( *m_Effects.begin() == m_spLEffect );

                m_Effects.erase(m_Effects.begin());
                m_spLEffect = 0;
            }
        }
    }
    else if( LightingMode == GLM_USER )
    {
        // 用户自定义lighting effect.
        // 所有自定义lighting effect都可以使用渲染器提供的灯光数组.

        if( m_spLEffect )
        {
            SE_ASSERT( *m_Effects.begin() == m_spLEffect );

            m_Effects.erase(m_Effects.begin());
            m_spLEffect = 0;
        }

        for( i = 0; i < iLCount; i++ )
        {
            Lights.push_back((*pLStack)[i]);
        }
    }
    else
    {
        // 禁止光照效果.

        if( m_spLEffect )
        {
            SE_ASSERT( *m_Effects.begin() == m_spLEffect );

            m_Effects.erase(m_Effects.begin());
            m_spLEffect = 0;
        }
    }

    // 待实现.
    // 目前只支持effect pass携带的alpha state.
    // 更新effects的render state blocks.
    int iECount = (int)m_Effects.size();
    for( int i = 0; i < iECount; i++ )
    {
        m_Effects[i]->OnUpdateData((void*)RStateBlock);
    }
}
//----------------------------------------------------------------------------
void Geometry::GetUnculledSet(Culler& rCuller, bool)
{
    rCuller.Insert(this, 0);
}
//----------------------------------------------------------------------------
Geometry::PickRecord::PickRecord(Geometry* pIObject, float fT)
    :
    Spatial::PickRecord(pIObject, fT)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Geometry::GetObjectByName(const std::string& rName)
{
    Object* pFound = Spatial::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( ModelBound )
    {
        pFound = ModelBound->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( VBuffer )
    {
        pFound = VBuffer->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( IBuffer )
    {
        pFound = IBuffer->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Geometry::GetAllObjectsByName(const std::string& rName,
    std::vector<Object*>& rObjects)
{
    Spatial::GetAllObjectsByName(rName, rObjects);

    if( ModelBound )
    {
        ModelBound->GetAllObjectsByName(rName, rObjects);
    }

    if( VBuffer )
    {
        VBuffer->GetAllObjectsByName(rName, rObjects);
    }

    if( IBuffer )
    {
        IBuffer->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
Object* Geometry::GetObjectByID(unsigned int uiID)
{
    Object* pFound = Spatial::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( ModelBound )
    {
        pFound = ModelBound->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( VBuffer )
    {
        pFound = VBuffer->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( IBuffer )
    {
        pFound = IBuffer->GetObjectByID(uiID);
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
void Geometry::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Spatial::Load(rStream, pLink);

    // native data
    rStream.Read((int&)LightingMode);

    // link data
    Object* pObject;
    rStream.Read(pObject);  // ModelBound
    pLink->Add(pObject);

    rStream.Read(pObject);  // VBuffer
    pLink->Add(pObject);

    rStream.Read(pObject);  // IBuffer
    pLink->Add(pObject);

    rStream.Read(pObject);  // m_spLEffect
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(Geometry);
}
//----------------------------------------------------------------------------
void Geometry::Link(Stream& rStream, Stream::Link* pLink)
{
    Spatial::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    ModelBound = (BoundingVolume*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    VBuffer = (VertexBuffer*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    IBuffer = (IndexBuffer*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    m_spLEffect = (LightingEffect*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool Geometry::Register(Stream& rStream) const
{
    if( !Spatial::Register(rStream) )
    {
        return false;
    }

    if( ModelBound )
    {
        ModelBound->Register(rStream);
    }

    if( VBuffer )
    {
        VBuffer->Register(rStream);
    }

    if( IBuffer )
    {
        IBuffer->Register(rStream);
    }

    if( m_spLEffect )
    {
        m_spLEffect->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void Geometry::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Spatial::Save(rStream);

    // native data
    rStream.Write((int)LightingMode);

    // link data
    rStream.Write(ModelBound);
    rStream.Write(VBuffer);
    rStream.Write(IBuffer);
    rStream.Write(m_spLEffect);

    SE_END_DEBUG_STREAM_SAVE(Geometry);
}
//----------------------------------------------------------------------------
int Geometry::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Spatial::GetDiskUsed(rVersion) +
        sizeof(LightingMode) +
        sizeof(ModelBound) +
        sizeof(VBuffer) +
        sizeof(IBuffer) +
        sizeof(m_spLEffect);
}
//----------------------------------------------------------------------------
StringTree* Geometry::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("lighting mode =", (int)LightingMode));

    // children
    pTree->Append(Spatial::SaveStrings());

    if( ModelBound )
    {
        pTree->Append(ModelBound->SaveStrings());
    }

    if( VBuffer )
    {
        pTree->Append(VBuffer->SaveStrings("vertices"));
    }

    if( IBuffer )
    {
        pTree->Append(IBuffer->SaveStrings("indices"));
    }

    return pTree;
}
//----------------------------------------------------------------------------
