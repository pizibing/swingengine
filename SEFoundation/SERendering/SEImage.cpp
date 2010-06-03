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
#include "SEImage.h"
#include "SEImageCatalog.h"
#include "SEImageVersion.h"
#include "SEBitHacks.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEImage, SEObject);
SE_IMPLEMENT_STREAM(SEImage);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEImage, SEObject);

//SE_REGISTER_STREAM(SEImage);

int SEImage::ms_BytesPerPixel[SEImage::IT_COUNT] =
{
    3,  // IT_RGB888
    4,  // IT_RGBA8888
    4,  // IT_DEPTH16
    4,  // IT_DEPTH24
    4,  // IT_DEPTH32
    3,  // IT_CUBE_RGB888
    4,  // IT_CUBE_RGBA8888
    12, // IT_RGB32
    16, // IT_RGBA32
    1,  // IT_L8
    2,  // IT_L16
    4,  // IT_R32
    6,  // IT_RGB16
    8,  // IT_RGBA16
    2,  // IT_RGB565
    2,  // IT_RGBA5551
    2   // IT_RGBA4444
};

std::string SEImage::ms_FormatName[SEImage::IT_COUNT] =
{
    "IT_RGB888",
    "IT_RGBA8888",
    "IT_DEPTH16",
    "IT_DEPTH24",
    "IT_DEPTH32",
    "IT_CUBE_RGB888",
    "IT_CUBE_RGBA8888",
    "IT_RGB32",
    "IT_RGBA32",
    "IT_L8",
    "IT_L16",
    "IT_R32",
    "IT_RGB16",
    "IT_RGBA16",
    "IT_RGB565",
    "IT_RGBA5551",
    "IT_RGBA4444"
};

//----------------------------------------------------------------------------
SEImage::SEImage(FormatMode eFormat, int iBound0, unsigned char* pData,
    const char* pImageName, bool bInsert)
{
    // 20090305更新.
    //SE_ASSERT( IsPowerOfTwo((unsigned int)iBound0) );
    SE_ASSERT( pImageName );

    m_eFormat = eFormat;
    m_iDimension = 1;
    m_Bound[0] = iBound0;
    m_Bound[1] = 1;
    m_Bound[2] = 1;
    m_iCount = iBound0;
    m_pData = pData;
    SetName(pImageName);
    m_bIsInCatalog = bInsert;
    if( bInsert )
    {
        SEImageCatalog::GetActive()->Insert(this);
    }
}
//----------------------------------------------------------------------------
SEImage::SEImage(FormatMode eFormat, int iBound0, int iBound1,
    unsigned char* pData, const char* pImageName, bool bInsert)
{
    // 20090305更新.
    //SE_ASSERT( IsPowerOfTwo((unsigned int)iBound0)
    //     && IsPowerOfTwo((unsigned int)iBound1) );
    SE_ASSERT( pImageName );

    m_eFormat = eFormat;
    m_iDimension = 2;
    m_Bound[0] = iBound0;
    m_Bound[1] = iBound1;
    m_Bound[2] = 1;
    m_iCount = iBound0 * iBound1;
    m_pData = pData;
    SetName(pImageName);
    m_bIsInCatalog = bInsert;
    if( bInsert )
    {
        SEImageCatalog::GetActive()->Insert(this);
    }
}
//----------------------------------------------------------------------------
SEImage::SEImage(FormatMode eFormat, int iBound0, int iBound1, int iBound2,
    unsigned char* pData, const char* pImageName, bool bInsert)
{
    // 20090305更新.
    //SE_ASSERT( IsPowerOfTwo((unsigned int)iBound0)
    //     && IsPowerOfTwo((unsigned int)iBound1)
    //     && IsPowerOfTwo((unsigned int)iBound2) );
    SE_ASSERT( pImageName );

    m_eFormat = eFormat;
    m_iDimension = 3;
    m_Bound[0] = iBound0;
    m_Bound[1] = iBound1;
    m_Bound[2] = iBound2;
    m_iCount = iBound0 * iBound1 * iBound2;
    m_pData = pData;
    SetName(pImageName);
    m_bIsInCatalog = bInsert;
    if( bInsert )
    {
        SEImageCatalog::GetActive()->Insert(this);
    }
}
//----------------------------------------------------------------------------
SEImage::SEImage()
{
    m_eFormat = IT_COUNT;
    m_iDimension = 0;
    m_Bound[0] = 0;
    m_Bound[1] = 0;
    m_Bound[2] = 0;
    m_iCount = 0;
    m_pData = 0;
}
//----------------------------------------------------------------------------
SEImage::~SEImage()
{
    SE_DELETE[] m_pData;
    if( m_bIsInCatalog )
    {
        SEImageCatalog::GetActive()->Remove(this);
    }
}
//----------------------------------------------------------------------------
SEColorRGBA* SEImage::CreateRGBA() const
{
    if( !IsCubeImage() )
    {
        SEColorRGBA* pColorImage = SE_NEW SEColorRGBA[m_iCount];
        CopyRGBA(pColorImage);

        return pColorImage;
    }

    // cube map被当作6个2D image来处理,因此没有必要创建RGBA image
    return 0;
}
//----------------------------------------------------------------------------
void SEImage::CopyRGBA(SEColorRGBA* pColorImage) const
{
    const float fInv255 = 1.0f / 255.0f;
    SEColorRGBA* pColorValue;
    const unsigned char* pucValue;
    int i;

    if( m_eFormat == IT_RGB888 )
    {
        pColorValue = pColorImage;
        pucValue = (const unsigned char*)m_pData;
        for( i = 0; i < m_iCount; i++, pColorValue++ )
        {
            pColorValue->R = fInv255*(float)(*pucValue++);
            pColorValue->G = fInv255*(float)(*pucValue++);
            pColorValue->B = fInv255*(float)(*pucValue++);
            pColorValue->A = 1.0f;
        }
    }
    else if( m_eFormat == IT_RGBA8888 )
    {
        pColorValue = pColorImage;
        pucValue = (const unsigned char*)m_pData;
        for( i = 0; i < m_iCount; i++, pColorValue++ )
        {
            pColorValue->R = fInv255*(float)(*pucValue++);
            pColorValue->G = fInv255*(float)(*pucValue++);
            pColorValue->B = fInv255*(float)(*pucValue++);
            pColorValue->A = fInv255*(float)(*pucValue++);
        }
    }
    else if( IsDepthImage() )
    {
        // 待实现.
        // 目前只支持IT_DEPTH32.
        pColorValue = pColorImage;
        const float* pfValue = (const float*)m_pData;
        for( i = 0; i < m_iCount; i++, pColorValue++, pfValue++ )
        {
            float fValue = *pfValue;
            pColorValue->R = fValue;
            pColorValue->G = fValue;
            pColorValue->B = fValue;
            pColorValue->A = 1.0f;
        }
    }
    else
    {
        // cube map被当作6个2D image来处理,因此没有必要转换为RGBA image
    }
}
//----------------------------------------------------------------------------
SEImage* SEImage::Load(const char* pImageName)
{
    SE_ASSERT( pImageName );

    std::string strFileName = std::string(pImageName) + std::string(".seif");
    const char* pDecorated = SESystem::SE_GetPath(strFileName.c_str(), 
        SESystem::SM_READ);
    if( !pDecorated )
    {
        return 0;
    }

    char* acBuffer;
    int iSize;
    bool bLoaded = SESystem::SE_Load(pDecorated, acBuffer, iSize);
    if( !bLoaded )
    {
        // 文件读取失败
        return 0;
    }
    if( iSize < SEImageVersion::LENGTH )
    {
        // 文件太小
        SE_DELETE[] acBuffer;

        return 0;
    }

    // 获取文件版本
    SEImageVersion TempVersion(acBuffer);
    if( !TempVersion.IsValid() )
    {
        SE_DELETE[] acBuffer;

        return 0;
    }

    char* pcCurrent = acBuffer + SEImageVersion::LENGTH;

    // 获取image format和dimensions
    int iFormat, iDimension, aiBound[3];
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &iFormat);
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &iDimension);
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &aiBound[0]);
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &aiBound[1]);
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &aiBound[2]);
    FormatMode eFormat = (FormatMode)iFormat;
    int iCount = aiBound[0] * aiBound[1] * aiBound[2];

    // 获取image data
    int iDataSize = ms_BytesPerPixel[eFormat] * iCount;
    unsigned char* pData = SE_NEW unsigned char[iDataSize];
    SESystem::SE_Read1(pcCurrent, iDataSize, pData);

    SEImage* pImage = 0;
    switch( iDimension )
    {
    case 1:
        pImage = SE_NEW SEImage(eFormat, aiBound[0], pData, pImageName);
        break;
    case 2:
        pImage = SE_NEW SEImage(eFormat, aiBound[0], aiBound[1], pData,
            pImageName);
        break;
    case 3:
        pImage = SE_NEW SEImage(eFormat, aiBound[0], aiBound[1], aiBound[2],
            pData, pImageName);
        break;
    default:
        SE_ASSERT( false );
    }

    SE_DELETE[] acBuffer;

    return pImage;
}
//----------------------------------------------------------------------------
bool SEImage::Save(const char* pFileName)
{
    if( !pFileName )
    {
        return false;
    }

    FILE* pFile = SESystem::SE_Fopen(pFileName, "wb");
    if( !pFile )
    {
        return false;
    }

    // 写文件版本
    SESystem::SE_Write1(pFile, SEImageVersion::LENGTH, SEImageVersion::LABEL);

    // 写image format和dimensions
    int iFormat = (int)m_eFormat;
    SESystem::SE_Write4le(pFile, 1, &iFormat);
    SESystem::SE_Write4le(pFile, 1, &m_iDimension);
    SESystem::SE_Write4le(pFile, 1, &m_Bound[0]);
    SESystem::SE_Write4le(pFile, 1, &m_Bound[1]);
    SESystem::SE_Write4le(pFile, 1, &m_Bound[2]);

    // 写image data
    int iDataSize = ms_BytesPerPixel[m_eFormat] * m_iCount;
    SESystem::SE_Write1(pFile, iDataSize, m_pData);

    SESystem::SE_Fclose(pFile);

    return true;
}
//----------------------------------------------------------------------------
SEImage* SEImage::GenerateRandomImage(FormatMode eFormat, int iBound0, 
    int iBound1, unsigned int uiSeed, const char* acImageName, bool bInsert)
{
    //SE_ASSERT( IsPowerOfTwo((unsigned int)iBound0)
    //     && IsPowerOfTwo((unsigned int)iBound1) );
    SE_ASSERT( acImageName );

    // 待实现.
    // 当前只支持IT_RGBA8888格式.
    eFormat = SEImage::IT_RGBA8888;
    int iDataSize = iBound0 * iBound1 * ms_BytesPerPixel[eFormat];

    unsigned char* aucData = SE_NEW unsigned char[iDataSize];
    unsigned char* pucData = aucData;
    SEMathf::SymmetricRandom(uiSeed);
    for( int i = 0; i < iBound0*iBound1; i++ )
    {
        SEVector4f vec4fRandom;
        vec4fRandom.X = SEMathf::SymmetricRandom();
        vec4fRandom.Y = SEMathf::SymmetricRandom();
        vec4fRandom.Z = SEMathf::SymmetricRandom();
        vec4fRandom.W = SEMathf::SymmetricRandom();
        vec4fRandom.Normalize();
        vec4fRandom *= 0.5f;
        vec4fRandom += 0.5f;
		
        int iR = (int)(vec4fRandom.X * 255.0f);
        int iG = (int)(vec4fRandom.Y * 255.0f);
        int iB = (int)(vec4fRandom.Z * 255.0f);
        int iA = (int)(vec4fRandom.W * 255.0f);
        *pucData++ = (unsigned char)iR;
        *pucData++ = (unsigned char)iG;
        *pucData++ = (unsigned char)iB;
        *pucData++ = (unsigned char)iA;
    }
    SEImage* pImage = SE_NEW SEImage(SEImage::IT_RGBA8888, iBound0, iBound1,
        aucData, acImageName, bInsert);

    return pImage;
}
//----------------------------------------------------------------------------
SEImage* SEImage::GenerateColorImage(FormatMode eFormat, int iBound0, int 
    iBound1, const SEColorRGBA& rColor, const char* acImageName, bool bInsert)
{
    //SE_ASSERT( IsPowerOfTwo((unsigned int)iBound0)
    //     && IsPowerOfTwo((unsigned int)iBound1) );
    SE_ASSERT( acImageName );

    // 待实现.
    // 当前只支持IT_RGBA8888,IT_R32格式.
    SE_ASSERT( eFormat == SEImage::IT_RGBA8888 || eFormat == SEImage::IT_R32 ); 
    int iDataSize = iBound0 * iBound1 * ms_BytesPerPixel[eFormat];

    unsigned char* aucData = SE_NEW unsigned char[iDataSize];
    unsigned char* pucData = aucData;
    for( int i = 0; i < iBound0*iBound1; i++ )
    {		
        int iR = (int)(rColor.R * 255.0f);
        int iG = (int)(rColor.G * 255.0f);
        int iB = (int)(rColor.B * 255.0f);
        int iA = (int)(rColor.A * 255.0f);
        *pucData++ = (unsigned char)iR;
        *pucData++ = (unsigned char)iG;
        *pucData++ = (unsigned char)iB;
        *pucData++ = (unsigned char)iA;
    }
    SEImage* pImage = SE_NEW SEImage(eFormat, iBound0, iBound1,
        aucData, acImageName, bInsert);

    return pImage;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEImage::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(iTemp);
    m_eFormat = (FormatMode)iTemp;
    rStream.Read(m_iDimension);
    rStream.Read(m_Bound[0]);
    rStream.Read(m_Bound[1]);
    rStream.Read(m_Bound[2]);
    rStream.Read(m_iCount);

    int iBytes = ms_BytesPerPixel[m_eFormat]*m_iCount;
    m_pData = SE_NEW unsigned char[iBytes];
    rStream.Read(iBytes, m_pData);

    m_bIsInCatalog = true;
    SEImageCatalog::GetActive()->Insert(this);

    SE_END_DEBUG_STREAM_LOAD(SEImage);
}
//----------------------------------------------------------------------------
void SEImage::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEImage::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEImage::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

    // native data
    rStream.Write((int)m_eFormat);
    rStream.Write(m_iDimension);
    rStream.Write(m_Bound[0]);
    rStream.Write(m_Bound[1]);
    rStream.Write(m_Bound[2]);
    rStream.Write(m_iCount);

    int iBytes = ms_BytesPerPixel[m_eFormat]*m_iCount;
    rStream.Write(iBytes, m_pData);

    SE_END_DEBUG_STREAM_SAVE(SEImage);
}
//----------------------------------------------------------------------------
int SEImage::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEObject::GetDiskUsed(rVersion) +
        sizeof(int); // m_eFormat

    iSize +=
        sizeof(m_iDimension) +
        sizeof(m_Bound[0]) +
        sizeof(m_Bound[1]) +
        sizeof(m_Bound[2]) +
        sizeof(m_iCount);

    int iBytes = ms_BytesPerPixel[m_eFormat]*m_iCount;
    iSize += iBytes*sizeof(m_pData[0]);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEImage::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("format =", ms_FormatName[m_eFormat].c_str()));
    pTree->Append(Format("dimension = ", m_iDimension));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    for( int i = 0; i < m_iDimension; i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "bound[%d] =",i);
        pTree->Append(Format(acTitle, m_Bound[i]));
    }

    // children
    pTree->Append(SEObject::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
