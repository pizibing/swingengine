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

#ifndef Swing_Image_H
#define Swing_Image_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEColorRGBA.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:支持1D,2D,3D图像.
//     注意,图像的每一个维度的长度都必须是2^n,其中n>=0.
// Author:Sun Che
// Date:20080629
// 更新时间:20090305
// 更新说明:为了支持任意width,height的render target纹理,
//     取消纹理维度必须是power of two的限制.
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEImage : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    enum FormatMode
    {
        IT_RGB888,
        IT_RGBA8888,
        IT_DEPTH16,
        IT_DEPTH24,
        IT_DEPTH32,
        IT_CUBE_RGB888,
        IT_CUBE_RGBA8888,
        IT_RGB32,
        IT_RGBA32,
        IT_L8,
        IT_L16,
        IT_R32,
        IT_RGB16,
        IT_RGBA16,
        IT_RGB565,   // (high)   B G R (low)
        IT_RGBA5551, // (high) A B G R (low)
        IT_RGBA4444, // (high) A B G R (low)
        IT_PVRTC,
        IT_COUNT
    };

    // 颜色图数据的内存存储方式为r,g,b,a依次排列在内存低地址到高地址.
    // 例如,第一个像素的内存排列顺序:
    //
    //   IT_RGB888:
    //     r = pData[0];
    //     g = pData[1];
    //     b = pData[2];
    //
    //   IT_RGBA8888:
    //     r = pData[0];
    //     g = pData[1];
    //     b = pData[2];
    //     a = pData[3];
    //
    // 深度图数据使用在[0,1]区间上的float数据存储.
    // 指定的16,24,或32位位信息是用来正确设置硬件的depth buffer的.
    // 如果有必要的话,从depth buffer读取到深度图上的数据,
    // 将会被转换为[0,1]区间float值.

    // 构造和析构.
    // SEImage有责任删除传入的数组数据.
    // pImageName用于image共享时的唯一ID.
    // 构造函数的调用者可以提供一个image name.
    // 如果没有提供,则构造函数将自动创建一个叫做"imageN.seif"的唯一ID,
    // 其中N是其SEObject::m_uiID.
    // 出于image共享的目的,系统维护着一个全局image map.
    // 默认情况下,image被成功创建后,将被插入到全局image map,
    // 供稍后索引该资源时使用.然而用户也可以设置bInsert参数为false,
    // 从而该image不会被插入全局image map(比如在没有全局image map时).

    // 1D image.
    SEImage(FormatMode eFormat, int iBound0, unsigned char* pData, 
        const char* pImageName, bool bInsert = true);

    // 2D image.
    SEImage(FormatMode eFormat, int iBound0, int iBound1,
        unsigned char* pData, const char* pImageName, bool bInsert = true);

    // 3D image.
    SEImage(FormatMode eFormat, int iBound0, int iBound1, int iBound2,
        unsigned char* pData, const char* pImageName, bool bInsert = true);

    virtual ~SEImage(void);

    inline FormatMode GetFormat(void) const;
    inline const std::string& GetFormatName(void) const;
    inline static std::string GetFormatName(int eFormat);
    inline bool IsDepthImage(void) const;
    inline bool IsCubeImage(void) const;
    inline int GetBytesPerPixel(void) const;
    inline static int GetBytesPerPixel(int eFormat);
    inline int GetDimension(void) const;
    inline int GetBound(int i) const;
    inline int GetCount(void) const;
    inline unsigned char* GetData(void) const;
    inline unsigned char* operator() (int i);

    // 创建一个数据类型为SEColorRGBA的image.
    // 函数返回与当前image具有同样width和height的SEColorRGBA数据.
    // 由于该数据是动态分配的,因此调用者有责任释放该数据.
    SEColorRGBA* CreateRGBA(void) const;

    // 把数据复制给一个已经存在的SEColorRGBA数据区.
    // 传入的数据数组必须和当前image有同样的维度信息.
    void CopyRGBA(SEColorRGBA* pColorImage) const;

    // Streaming support.当这些函数被调用时,共享系统将被自动调用.
    // 对于Load函数,如果具有filename的image已经载入内存,
    // 则该image被找到并作为返回值(例如,出于共享的目的).
    // 否则,创建一个新的image并返回.filename被用作image name.
    // 参考SEImageCatalog::Find函数中对这个函数的调用.
    static SEImage* Load(const char* pImageName);

    // 这个函数用来支持保存程序生成的image数据,
    // 或者可以用来支持把其他类型的image格式的数据转换为seif格式.
    // 传入的filename不会替代原有的image name,只是用于生成的文件名.
    bool Save(const char* pFileName);

    // 创建一个2D random image.
    static SEImage* GenerateRandomImage(FormatMode eFormat, int iBound0, 
        int iBound1, unsigned int uiSeed, const char* acImageName, 
        bool bInsert = true);

    // 创建一个2D color image.
    static SEImage* GenerateColorImage(FormatMode eFormat, int iBound0, 
        int iBound1, const SEColorRGBA& rColor, const char* acImageName, 
        bool bInsert = true);

protected:
    // support for streaming.
    SEImage(void);

    FormatMode m_eFormat;
    int m_iDimension;
    int m_Bound[3];
    int m_iCount;  // 像素个数
    unsigned char* m_pData;

    bool m_bIsInCatalog;

    static int ms_BytesPerPixel[IT_COUNT];
    static std::string ms_FormatName[IT_COUNT];
};

typedef SESmartPointer<SEImage> SEImagePtr;

#include "SEImage.inl"

}

#endif
