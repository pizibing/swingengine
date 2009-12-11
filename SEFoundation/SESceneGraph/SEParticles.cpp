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
#include "SEParticles.h"
#include "SECamera.h"
#include "SECuller.h"
#include "SELight.h"
#include "SEVector2Array.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Particles, TriMesh);
SE_IMPLEMENT_STREAM(Particles);

//SE_REGISTER_STREAM(Particles);

//----------------------------------------------------------------------------
Particles::Particles(const Attributes& rAttr, Vector3fArray* pLocations,
    FloatArray* pSizes)
    :
    Locations(pLocations),
    Sizes(pSizes)
{
    // 分配模型空间顶点存储,每个粒子使用4个顶点构成一个quad广告牌.
    int iLCount = Locations->GetCount();
    int iVCount = 4*iLCount;
    VBuffer = SE_NEW VertexBuffer(rAttr, iVCount);

    // 为这些quad广告牌设置2D纹理坐标.
    int i, j;
    for( int iUnit = 0; iUnit < rAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rAttr.HasTCoord(iUnit) && rAttr.GetTCoordChannels(iUnit) == 2 )
        {
            for( i = 0, j = 0; i < iLCount; i++ )
            {
                VBuffer->TCoord2(iUnit, j++) = Vector2f(0.0f, 1.0f);
                VBuffer->TCoord2(iUnit, j++) = Vector2f(0.0f, 0.0f);
                VBuffer->TCoord2(iUnit, j++) = Vector2f(1.0f, 0.0f);
                VBuffer->TCoord2(iUnit, j++) = Vector2f(1.0f, 1.0f);
            }
        }
    }

    // 为这些quad广告牌创建IB.
    int iICount = 6*iLCount;
    IBuffer = SE_NEW IndexBuffer(iICount);
    int* aiIndex = IBuffer->GetData();
    for( i = 0, j = 0; i < iLCount; i++ )
    {
        int iFI = 4*i, iFIp1 = iFI+1, iFIp2 = iFI+2, iFIp3 = iFI+3;
        aiIndex[j++] = iFI;
        aiIndex[j++] = iFIp1;
        aiIndex[j++] = iFIp3;
        aiIndex[j++] = iFIp1;
        aiIndex[j++] = iFIp2;
        aiIndex[j++] = iFIp3;
    }

    // 根据全部粒子的模型空间位置计算出一个包含这些位置的BV.
    ModelBound->ComputeFromData(Locations);

    SizeAdjust = 1.0f;
    m_iActiveCount = iLCount;
}
//----------------------------------------------------------------------------
Particles::Particles()
{
    SizeAdjust = 0.0f;
    m_iActiveCount = 0;
}
//----------------------------------------------------------------------------
Particles::~Particles()
{
}
//----------------------------------------------------------------------------
void Particles::SetActiveCount(int iActiveCount)
{
    int iLCount = Locations->GetCount();
    if( 0 <= iActiveCount && iActiveCount <= iLCount )
    {
        m_iActiveCount = iActiveCount;
    }
    else
    {
        m_iActiveCount = iLCount;
    }

    IBuffer->SetIndexCount(6*m_iActiveCount);
    IBuffer->Release();

    int iFourActiveCount = 4*m_iActiveCount;
    VBuffer->SetVertexCount(iFourActiveCount);
    VBuffer->Release();
}
//----------------------------------------------------------------------------
void Particles::GenerateParticles(const Camera* pCamera)
{
    int i, j;

    // 把camera的轴向量变换到粒子的模型空间.
    Vector3f vec3fUpR = pCamera->GetUVector() + pCamera->GetRVector();
    vec3fUpR = World.GetRotate() * vec3fUpR;
    Vector3f vec3fUmR = pCamera->GetUVector() - pCamera->GetRVector();
    vec3fUmR = World.GetRotate() * vec3fUmR;

    // 所有法线向量指向观察者.
    if( VBuffer->GetAttributes().HasNormal() )
    {
        Vector3f vec3fDir = World.GetRotate()*(-pCamera->GetDVector());
        for( j = 0; j < 4*m_iActiveCount; j++ )
        {
            VBuffer->Normal3(j) = vec3fDir;
        }
    }

    // 生成粒子,每个都是由两个三角形组成的quad.
    Vector3f* aLocation = Locations->GetData();
    float* afSize = Sizes->GetData();
    for( i = 0, j = 0; i < m_iActiveCount; i++ )
    {
        Vector3f& rCenter = aLocation[i];

        float fTrueSize = SizeAdjust*afSize[i];
        Vector3f vec3fScaledUpR = fTrueSize*vec3fUpR;
        Vector3f vec3fScaledUmR = fTrueSize*vec3fUmR;

        VBuffer->Position3(j++) = rCenter - vec3fScaledUpR;
        VBuffer->Position3(j++) = rCenter + vec3fScaledUmR;
        VBuffer->Position3(j++) = rCenter + vec3fScaledUpR;
        VBuffer->Position3(j++) = rCenter - vec3fScaledUmR;
    }

    UpdateMS(true);
}
//----------------------------------------------------------------------------
void Particles::GetUnculledSet(Culler& rCuller, bool bNoCull)
{
    GenerateParticles(rCuller.GetCamera());
    TriMesh::GetUnculledSet(rCuller, bNoCull);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Particles::GetObjectByName(const std::string& rName)
{
    Object* pFound = TriMesh::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( Locations )
    {
        pFound = Locations->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( Sizes )
    {
        pFound = Sizes->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Particles::GetAllObjectsByName(const std::string& rName,
    std::vector<Object*>& rObjects)
{
    TriMesh::GetAllObjectsByName(rName, rObjects);

    if( Locations )
    {
        Locations->GetAllObjectsByName(rName, rObjects);
    }

    if( Sizes )
    {
        Sizes->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
Object* Particles::GetObjectByID(unsigned int uiID)
{
    Object* pFound = TriMesh::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( Locations )
    {
        pFound = Locations->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( Sizes )
    {
        pFound = Sizes->GetObjectByID(uiID);
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
void Particles::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    TriMesh::Load(rStream, pLink);

    // native data
    rStream.Read(SizeAdjust);
    rStream.Read(m_iActiveCount);

    // link data
    Object* pObject;

    rStream.Read(pObject);  // Locations
    pLink->Add(pObject);

    rStream.Read(pObject);  // Sizes
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(Particles);
}
//----------------------------------------------------------------------------
void Particles::Link(Stream& rStream, Stream::Link* pLink)
{
    TriMesh::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    Locations = (Vector3fArray*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    Sizes = (FloatArray*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool Particles::Register(Stream& rStream) const
{
    if( !TriMesh::Register(rStream) )
    {
        return false;
    }

    if( Locations )
    {
        Locations->Register(rStream);
    }

    if( Sizes )
    {
        Sizes->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void Particles::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    TriMesh::Save(rStream);

    // native data
    rStream.Write(SizeAdjust);
    rStream.Write(m_iActiveCount);

    // link data
    rStream.Write(Locations);
    rStream.Write(Sizes);

    SE_END_DEBUG_STREAM_SAVE(Particles);
}
//----------------------------------------------------------------------------
int Particles::GetDiskUsed(const StreamVersion& rVersion) const
{
    return TriMesh::GetDiskUsed(rVersion) +
        sizeof(SizeAdjust) +
        sizeof(m_iActiveCount) +
        sizeof(Locations) +
        sizeof(Sizes);
}
//----------------------------------------------------------------------------
StringTree* Particles::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("size adjust =", SizeAdjust));
    pTree->Append(Format("active count =", m_iActiveCount));

    // children
    pTree->Append(TriMesh::SaveStrings());
    pTree->Append(Locations->SaveStrings());
    pTree->Append(Sizes->SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
