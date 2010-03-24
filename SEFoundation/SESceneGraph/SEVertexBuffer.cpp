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
#include "SEVertexBuffer.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, VertexBuffer, Object);
SE_IMPLEMENT_STREAM(VertexBuffer);
SE_IMPLEMENT_DEFAULT_NAME_ID(VertexBuffer, Object);

//SE_REGISTER_STREAM(VertexBuffer);

//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer(const Attributes& rAttributes,
    int iVertexCount)
    :
    m_Attributes(rAttributes)
{
    SE_ASSERT( iVertexCount > 0 );

    m_iVertexCount = iVertexCount;
    m_iVertexSize = m_Attributes.GetChannelCount();
    m_iChannelCount = m_iVertexCount * m_iVertexSize;
    m_pChannel = SE_NEW float[m_iChannelCount];
    memset(m_pChannel, 0, m_iChannelCount*sizeof(float));
}
//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer(const VertexBuffer* pVBuffer)
{
    SE_ASSERT( pVBuffer );

    m_Attributes = pVBuffer->m_Attributes;
    m_iVertexCount = pVBuffer->m_iVertexCount;
    m_iVertexSize = m_Attributes.GetChannelCount();
    m_iChannelCount = m_iVertexCount * m_iVertexSize;
    m_pChannel = SE_NEW float[m_iChannelCount];
    size_t uiSize = m_iChannelCount * sizeof(float);
    System::SE_Memcpy(m_pChannel, uiSize, pVBuffer->m_pChannel, uiSize);
}
//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer()
{
    m_iVertexCount = 0;
    m_iVertexSize = 0;
    m_iChannelCount = 0;
    m_pChannel = 0;
}
//----------------------------------------------------------------------------
VertexBuffer::~VertexBuffer()
{
    // 通知所有正在使用此VB的render,此资源正要被释放,
    // 因此这些render可以及时释放掉与此VB有关的其他资源(VRAM中)
    Release();

    SE_DELETE[] m_pChannel;
}
//----------------------------------------------------------------------------
float* VertexBuffer::PositionTuple(int i)
{
    if( m_Attributes.HasPosition() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* VertexBuffer::PositionTuple(int i) const
{
    if( m_Attributes.HasPosition() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* VertexBuffer::NormalTuple(int i)
{
    if( m_Attributes.HasNormal() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* VertexBuffer::NormalTuple (int i) const
{
    if( m_Attributes.HasNormal() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* VertexBuffer::ColorTuple(int iUnit, int i)
{
    if( m_Attributes.HasColor(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* VertexBuffer::ColorTuple(int iUnit, int i) const
{
    if( m_Attributes.HasColor(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* VertexBuffer::TCoordTuple(int iUnit, int i)
{
    if( m_Attributes.HasTCoord(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* VertexBuffer::TCoordTuple(int iUnit, int i) const
{
    if( m_Attributes.HasTCoord(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
Vector3f& VertexBuffer::Position3(int i)
{
    SE_ASSERT( m_Attributes.GetPositionChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector3f VertexBuffer::Position3(int i) const
{
    SE_ASSERT( m_Attributes.GetPositionChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector3f& VertexBuffer::Normal3(int i)
{
    SE_ASSERT( m_Attributes.GetNormalChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector3f VertexBuffer::Normal3(int i) const
{
    SE_ASSERT( m_Attributes.GetNormalChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
ColorRGB& VertexBuffer::Color3(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(ColorRGB*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
ColorRGB VertexBuffer::Color3(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(ColorRGB*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
ColorRGBA& VertexBuffer::Color4(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(ColorRGBA*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
ColorRGBA VertexBuffer::Color4(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(ColorRGBA*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
float& VertexBuffer::TCoord1(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 1 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
float VertexBuffer::TCoord1(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 1 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector2f& VertexBuffer::TCoord2(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 2 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector2f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector2f VertexBuffer::TCoord2(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 2 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector2f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector3f& VertexBuffer::TCoord3(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector3f VertexBuffer::TCoord3(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector4f& VertexBuffer::TCoord4(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector4f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
Vector4f VertexBuffer::TCoord4(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(Vector4f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
void VertexBuffer::BuildCompatibleArray(const Attributes& rIAttributes,
    bool bPackARGB, int& rChannels, float*& rCompatible) const
{
    // 注意这里使用unsigned int来存储数据,
    // 从而允许同时存储float和32位ARGB格式的unsigned int数据,
    // 把float指针显示类型转换为unsigned int指针然后取*操作没有任何问题,
    // 但反过来把unsigned int指针显示类型转换为float指针并取*操作,
    // 则取出的数据可能为非法浮点数据,
    // 因此如果使用std::vector<float>将可能存在数据非正常转换的问题
    std::vector<unsigned int> tempCompatible;    
    const unsigned int* puiData;
    float fOne = 1.0f;
    unsigned int* puiOne = (unsigned int*)&fOne;
    int iUnit, iIChannels, iVBChannels;

    for( int i = 0, j; i < m_iVertexCount; i++ )
    {
        // 填充顶点
        if( rIAttributes.HasPosition() )
        {
            iIChannels = rIAttributes.GetPositionChannels();
            iVBChannels = m_Attributes.GetPositionChannels();
            puiData = (unsigned int*)PositionTuple(i);
            if( iVBChannels < iIChannels )
            {
                for( j = 0; j < iVBChannels; j++ )
                {
                    tempCompatible.push_back(*puiData++);
                }
                for( j = iVBChannels; j < iIChannels; j++ )
                {
                    // 将w分量填充为1.0,从而成为齐次空间顶点
                    tempCompatible.push_back(*puiOne);
                }
            }
            else
            {
                for( j = 0; j < iIChannels; j++ )
                {
                    tempCompatible.push_back(*puiData++);
                }
            }
        }

        // 填充法线
        if( rIAttributes.HasNormal() )
        {
            iIChannels = rIAttributes.GetNormalChannels();
            iVBChannels = m_Attributes.GetNormalChannels();
            puiData = (unsigned int*)NormalTuple(i);
            if( iVBChannels < iIChannels )
            {
                for( j = 0; j < iVBChannels; j++ )
                {
                    tempCompatible.push_back(*puiData++);
                }
                for( j = iVBChannels; j < iIChannels; j++ )
                {
                    // 将w分量填充为0.0,从而成为齐次空间向量
                    tempCompatible.push_back(0);
                }
            }
            else
            {
                for( j = 0; j < iIChannels; j++ )
                {
                    tempCompatible.push_back(*puiData++);
                }
            }
        }

        // 填充若干组颜色
        for( iUnit = 0; iUnit < (int)rIAttributes.GetMaxColors(); iUnit++ )
        {
            if( rIAttributes.HasColor(iUnit) )
            {
                unsigned int auiColor[4], uiPackColor, uiValue;
                float fValue;

                iIChannels = rIAttributes.GetColorChannels(iUnit);
                iVBChannels = m_Attributes.GetColorChannels(iUnit);
                puiData = (unsigned int*)ColorTuple(iUnit, i);
                if( iVBChannels < iIChannels )
                {
                    for( j = 0; j < iVBChannels; j++ )
                    {
                        tempCompatible.push_back(*puiData++);
                    }
                    for( j = iVBChannels; j < iIChannels; j++ )
                    {
                        // 将a分量填充为1.0,成为不透明颜色
                        tempCompatible.push_back(*puiOne);
                    }
                    if( bPackARGB )
                    {
                        for( j = iIChannels; j < 4; j++ )
                        {
                            // 将a分量填充为1.0,成为不透明颜色
                            tempCompatible.push_back(*puiOne);
                        }

                        // 从[0.0f, 1.0f]映射到[0,255]
                        for( j = 3; j >= 0; j-- )
                        {
                            uiValue = tempCompatible.back();
                            fValue = *(float*)&uiValue;
                            auiColor[j] = (unsigned int)(255.0f * fValue);
                            tempCompatible.pop_back();
                        }

                        uiPackColor =
                            (auiColor[2]      ) |  // blue
                            (auiColor[1] <<  8) |  // green
                            (auiColor[0] << 16) |  // red
                            (auiColor[3] << 24);   // alpha

                        tempCompatible.push_back(uiPackColor);
                    }
                }
                else
                {
                    for( j = 0; j < iIChannels; j++ )
                    {
                        tempCompatible.push_back(*puiData++);
                    }
                    if( bPackARGB )
                    {
                        for( j = iIChannels; j < 4; j++ )
                        {
                            // 将a分量填充为1.0,成为不透明颜色
                            tempCompatible.push_back(*puiOne);
                        }

                        // 从[0.0f, 1.0f]映射到[0,255]
                        for( j = 3; j >= 0; j-- )
                        {
                            uiValue = tempCompatible.back();
                            fValue = *(float*)&uiValue;
                            auiColor[j] = (unsigned int)(255.0f * fValue);
                            tempCompatible.pop_back();
                        }

                        uiPackColor =
                            (auiColor[2]      ) |  // blue
                            (auiColor[1] <<  8) |  // green
                            (auiColor[0] << 16) |  // red
                            (auiColor[3] << 24);   // alpha

                        tempCompatible.push_back(uiPackColor);
                    }
                }
            }
        }

        // 填充若干组纹理坐标
        for( iUnit = 0; iUnit < (int)rIAttributes.GetMaxTCoords(); iUnit++ )
        {
            if( rIAttributes.HasTCoord(iUnit) )
            {
                iIChannels = rIAttributes.GetTCoordChannels(iUnit);
                iVBChannels = m_Attributes.GetTCoordChannels(iUnit);
                puiData = (unsigned int*)TCoordTuple(iUnit, i);
                if( iVBChannels < iIChannels )
                {
                    for( j = 0; j < iVBChannels; j++ )
                    {
                        tempCompatible.push_back(*puiData++);
                    }
                    for( j = iVBChannels; j < iIChannels; j++ )
                    {
                        // 填充为0,从而高维纹理坐标兼容低维纹理坐标
                        tempCompatible.push_back(0);
                    }
                }
                else
                {
                    for( j = 0; j < iIChannels; j++ )
                    {
                        tempCompatible.push_back(*puiData++);
                    }
                }
            }
        }
    }

    rChannels = (int)tempCompatible.size();
    if( !rCompatible )
    {
        // 调用者有责任释放该内存
        rCompatible = SE_NEW float[rChannels];
    }
    size_t uiSize = rChannels * sizeof(float);
    System::SE_Memcpy(rCompatible, uiSize, &tempCompatible.front(), uiSize);

    //FILE* pFile = System::SE_Fopen("VB.txt", "at");
    //System::SE_Fprintf(pFile, "VB ID: %d\n", GetID());
    //for( int i = 0; i < rChannels; i++ )
    //{
    //    System::SE_Fprintf(pFile, "%d: %f\n", i, *((float*)&rCompatible[i]));
    //}
    //System::SE_Fprintf(pFile, "\n");
    //System::SE_Fclose(pFile);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void VertexBuffer::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    rStream.Read(m_iVertexSize);
    rStream.Read(m_iVertexCount);
    rStream.Read(m_iChannelCount);
    m_pChannel = SE_NEW float[m_iChannelCount];
    rStream.Read(m_iChannelCount, m_pChannel);

    int iPChannels;
    rStream.Read(iPChannels);
    m_Attributes.SetPositionChannels(iPChannels);

    int iNChannels;
    rStream.Read(iNChannels);
    m_Attributes.SetNormalChannels(iNChannels);

    int iMaxColors;
    rStream.Read(iMaxColors);
    int i;
    for( i = 0; i < iMaxColors; i++ )
    {
        int iCChannels;
        rStream.Read(iCChannels);
        m_Attributes.SetColorChannels(i, iCChannels);
    }

    int iMaxTCoords;
    rStream.Read(iMaxTCoords);
    for( i = 0; i < iMaxTCoords; i++ )
    {
        int iTChannels;
        rStream.Read(iTChannels);
        m_Attributes.SetTCoordChannels(i, iTChannels);
    }

    SE_END_DEBUG_STREAM_LOAD(VertexBuffer);
}
//----------------------------------------------------------------------------
void VertexBuffer::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool VertexBuffer::Register(Stream& rStream) const
{
    return Object::Register(rStream);
}
//----------------------------------------------------------------------------
void VertexBuffer::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    rStream.Write(m_iVertexSize);
    rStream.Write(m_iVertexCount);
    rStream.Write(m_iChannelCount);
    rStream.Write(m_iChannelCount, m_pChannel);

    rStream.Write(m_Attributes.GetPositionChannels());
    rStream.Write(m_Attributes.GetNormalChannels());
    rStream.Write(m_Attributes.GetMaxColors());
    int i;
    for( i = 0; i < m_Attributes.GetMaxColors(); i++ )
    {
        rStream.Write(m_Attributes.GetColorChannels(i));
    }
    rStream.Write(m_Attributes.GetMaxTCoords());
    for( i = 0; i < m_Attributes.GetMaxTCoords(); i++ )
    {
        rStream.Write(m_Attributes.GetTCoordChannels(i));
    }

    SE_END_DEBUG_STREAM_SAVE(VertexBuffer);
}
//----------------------------------------------------------------------------
int VertexBuffer::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Object::GetDiskUsed(rVersion) +
        sizeof(m_iVertexSize) +
        sizeof(m_iVertexCount) +
        sizeof(m_iChannelCount) +
        m_iChannelCount*sizeof(m_pChannel[0]) +
        4*sizeof(int) +
        sizeof(int)*m_Attributes.GetMaxColors() +
        sizeof(int)*m_Attributes.GetMaxTCoords();
}
//----------------------------------------------------------------------------
StringTree* VertexBuffer::SaveStrings(const char* pTitle)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
	pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("vertex count = ", m_iVertexCount));
    pTree->Append(Format("vertex size = ", m_iVertexSize));

    pTree->Append(Format("p channels =", m_Attributes.GetPositionChannels()));
    pTree->Append(Format("n channels =", m_Attributes.GetNormalChannels()));

    pTree->Append(Format("c units =", m_Attributes.GetMaxColors()));
    const size_t uiSubtitleSize = 16;
    char acSubtitle[uiSubtitleSize];
    int i;
    for( i = 0; i < m_Attributes.GetMaxColors(); i++ )
    {
        System::SE_Sprintf(acSubtitle, uiSubtitleSize, "c[%d] channels =", i);
        pTree->Append(Format(acSubtitle, m_Attributes.GetColorChannels(i)));
    }

    pTree->Append(Format("t units =", m_Attributes.GetMaxTCoords()));
    for( i = 0; i < m_Attributes.GetMaxTCoords(); i++ )
    {
        System::SE_Sprintf(acSubtitle, uiSubtitleSize, "t[%d] channels =", i);
        pTree->Append(Format(acSubtitle, m_Attributes.GetTCoordChannels(i)));
    }

    // children
    pTree->Append(Object::SaveStrings());
    // this is very slow.
    pTree->Append(Format(pTitle, m_iChannelCount, m_pChannel));

    return pTree;
}
//----------------------------------------------------------------------------
