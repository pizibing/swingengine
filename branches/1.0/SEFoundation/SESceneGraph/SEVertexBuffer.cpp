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

SE_IMPLEMENT_RTTI(Swing, SEVertexBuffer, SEObject);
SE_IMPLEMENT_STREAM(SEVertexBuffer);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEVertexBuffer, SEObject);

//SE_REGISTER_STREAM(SEVertexBuffer);

//----------------------------------------------------------------------------
SEVertexBuffer::SEVertexBuffer(const SEAttributes& rAttributes,
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
SEVertexBuffer::SEVertexBuffer(const SEVertexBuffer* pVBuffer)
{
    SE_ASSERT( pVBuffer );

    m_Attributes = pVBuffer->m_Attributes;
    m_iVertexCount = pVBuffer->m_iVertexCount;
    m_iVertexSize = m_Attributes.GetChannelCount();
    m_iChannelCount = m_iVertexCount * m_iVertexSize;
    m_pChannel = SE_NEW float[m_iChannelCount];
    size_t uiSize = m_iChannelCount * sizeof(float);
    SESystem::SE_Memcpy(m_pChannel, uiSize, pVBuffer->m_pChannel, uiSize);
}
//----------------------------------------------------------------------------
SEVertexBuffer::SEVertexBuffer()
{
    m_iVertexCount = 0;
    m_iVertexSize = 0;
    m_iChannelCount = 0;
    m_pChannel = 0;
}
//----------------------------------------------------------------------------
SEVertexBuffer::~SEVertexBuffer()
{
    // ֪ͨ��������ʹ�ô�VB��render,����Դ��Ҫ���ͷ�,
    // �����Щrender���Լ�ʱ�ͷŵ����VB�йص�������Դ(VRAM��)
    Release();

    SE_DELETE[] m_pChannel;
}
//----------------------------------------------------------------------------
float* SEVertexBuffer::PositionTuple(int i)
{
    if( m_Attributes.HasPosition() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* SEVertexBuffer::PositionTuple(int i) const
{
    if( m_Attributes.HasPosition() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* SEVertexBuffer::NormalTuple(int i)
{
    if( m_Attributes.HasNormal() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* SEVertexBuffer::NormalTuple (int i) const
{
    if( m_Attributes.HasNormal() && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* SEVertexBuffer::ColorTuple(int iUnit, int i)
{
    if( m_Attributes.HasColor(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* SEVertexBuffer::ColorTuple(int iUnit, int i) const
{
    if( m_Attributes.HasColor(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
float* SEVertexBuffer::TCoordTuple(int iUnit, int i)
{
    if( m_Attributes.HasTCoord(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
const float* SEVertexBuffer::TCoordTuple(int iUnit, int i) const
{
    if( m_Attributes.HasTCoord(iUnit) && 0 <= i && i < m_iVertexCount )
    {
        int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

        return m_pChannel + iIndex;
    }

    return 0;
}
//----------------------------------------------------------------------------
SEVector3f& SEVertexBuffer::Position3(int i)
{
    SE_ASSERT( m_Attributes.GetPositionChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector3f SEVertexBuffer::Position3(int i) const
{
    SE_ASSERT( m_Attributes.GetPositionChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetPositionOffset();

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector3f& SEVertexBuffer::Normal3(int i)
{
    SE_ASSERT( m_Attributes.GetNormalChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector3f SEVertexBuffer::Normal3(int i) const
{
    SE_ASSERT( m_Attributes.GetNormalChannels() == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetNormalOffset();

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEColorRGB& SEVertexBuffer::Color3(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(SEColorRGB*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEColorRGB SEVertexBuffer::Color3(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(SEColorRGB*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEColorRGBA& SEVertexBuffer::Color4(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(SEColorRGBA*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEColorRGBA SEVertexBuffer::Color4(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetColorChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetColorOffset(iUnit);

    return *(SEColorRGBA*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
float& SEVertexBuffer::TCoord1(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 1 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
float SEVertexBuffer::TCoord1(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 1 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector2f& SEVertexBuffer::TCoord2(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 2 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector2f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector2f SEVertexBuffer::TCoord2(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 2 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector2f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector3f& SEVertexBuffer::TCoord3(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector3f SEVertexBuffer::TCoord3(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 3 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector3f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector4f& SEVertexBuffer::TCoord4(int iUnit, int i)
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector4f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
SEVector4f SEVertexBuffer::TCoord4(int iUnit, int i) const
{
    SE_ASSERT( m_Attributes.GetTCoordChannels(iUnit) == 4 );

    int iIndex = m_iVertexSize*i + m_Attributes.GetTCoordOffset(iUnit);

    return *(SEVector4f*)(m_pChannel + iIndex);
}
//----------------------------------------------------------------------------
void SEVertexBuffer::BuildCompatibleArray(const SEAttributes& rIAttributes,
    bool bPackARGB, int& rChannels, float*& rCompatible) const
{
    // ע������ʹ��unsigned int���洢����,
    // �Ӷ�����ͬʱ�洢float��32λARGB��ʽ��unsigned int����,
    // ��floatָ����ʾ����ת��Ϊunsigned intָ��Ȼ��ȡ*����û���κ�����,
    // ����������unsigned intָ����ʾ����ת��Ϊfloatָ�벢ȡ*����,
    // ��ȡ�������ݿ���Ϊ�Ƿ���������,
    // ������ʹ��std::vector<float>�����ܴ������ݷ�����ת��������
    std::vector<unsigned int> tempCompatible;    
    const unsigned int* puiData;
    float fOne = 1.0f;
    unsigned int* puiOne = (unsigned int*)&fOne;
    int iUnit, iIChannels, iVBChannels;

    for( int i = 0, j; i < m_iVertexCount; i++ )
    {
        // ��䶥��
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
                    // ��w�������Ϊ1.0,�Ӷ���Ϊ��οռ䶥��
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

        // ��䷨��
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
                    // ��w�������Ϊ0.0,�Ӷ���Ϊ��οռ�����
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

        // �����������ɫ
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
                        // ��a�������Ϊ1.0,��Ϊ��͸����ɫ
                        tempCompatible.push_back(*puiOne);
                    }
                    if( bPackARGB )
                    {
                        for( j = iIChannels; j < 4; j++ )
                        {
                            // ��a�������Ϊ1.0,��Ϊ��͸����ɫ
                            tempCompatible.push_back(*puiOne);
                        }

                        // ��[0.0f, 1.0f]ӳ�䵽[0,255]
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
                            // ��a�������Ϊ1.0,��Ϊ��͸����ɫ
                            tempCompatible.push_back(*puiOne);
                        }

                        // ��[0.0f, 1.0f]ӳ�䵽[0,255]
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

        // �����������������
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
                        // ���Ϊ0,�Ӷ���ά����������ݵ�ά��������
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
        // �������������ͷŸ��ڴ�
        rCompatible = SE_NEW float[rChannels];
    }
    size_t uiSize = rChannels * sizeof(float);
    SESystem::SE_Memcpy(rCompatible, uiSize, &tempCompatible.front(), uiSize);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEVertexBuffer::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

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

    SE_END_DEBUG_STREAM_LOAD(SEVertexBuffer);
}
//----------------------------------------------------------------------------
void SEVertexBuffer::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEVertexBuffer::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEVertexBuffer::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

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

    SE_END_DEBUG_STREAM_SAVE(SEVertexBuffer);
}
//----------------------------------------------------------------------------
int SEVertexBuffer::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEObject::GetDiskUsed(rVersion) +
        sizeof(m_iVertexSize) +
        sizeof(m_iVertexCount) +
        sizeof(m_iChannelCount) +
        m_iChannelCount*sizeof(m_pChannel[0]) +
        4*sizeof(int) +
        sizeof(int)*m_Attributes.GetMaxColors() +
        sizeof(int)*m_Attributes.GetMaxTCoords();
}
//----------------------------------------------------------------------------
SEStringTree* SEVertexBuffer::SaveStrings(const char* pTitle)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

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
        SESystem::SE_Sprintf(acSubtitle, uiSubtitleSize, "c[%d] channels =", i);
        pTree->Append(Format(acSubtitle, m_Attributes.GetColorChannels(i)));
    }

    pTree->Append(Format("t units =", m_Attributes.GetMaxTCoords()));
    for( i = 0; i < m_Attributes.GetMaxTCoords(); i++ )
    {
        SESystem::SE_Sprintf(acSubtitle, uiSubtitleSize, "t[%d] channels =", i);
        pTree->Append(Format(acSubtitle, m_Attributes.GetTCoordChannels(i)));
    }

    // children
    pTree->Append(SEObject::SaveStrings());
    // this is very slow.
    pTree->Append(Format(pTitle, m_iChannelCount, m_pChannel));

    return pTree;
}
//----------------------------------------------------------------------------