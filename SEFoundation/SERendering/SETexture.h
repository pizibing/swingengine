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

#ifndef Swing_Texture_H
#define Swing_Texture_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEBindable.h"
#include "SEColorRGBA.h"
#include "SEImage.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:纹理类
// 说明:支持1D,2D,3D纹理
// 作者:Sun Che
// 时间:20080630
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Texture : public SEObject, public Bindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    enum FilterType
    {
        NEAREST,          // nearest neighbor
        LINEAR,           // linear filtering
        NEAREST_NEAREST,  // nearest within image, nearest across images
        NEAREST_LINEAR,   // nearest within image, linear across images
        LINEAR_NEAREST,   // linear within image, nearest across images
        LINEAR_LINEAR,    // linear within image, linear across images
        MAX_FILTER_TYPES
    };

    enum WrapType
    {
        CLAMP,
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_BORDER,
        CLAMP_EDGE,
        MAX_WRAP_TYPES
    };

    enum DepthCompare
    {
        DC_NEVER,
        DC_LESS,
        DC_EQUAL,
        DC_LEQUAL,
        DC_GREATER,
        DC_NOTEQUAL,
        DC_GEQUAL,
        DC_ALWAYS,
        DC_COUNT
    };

    Texture(Image* pImage = 0);
    Texture(Image* pDepthImage, DepthCompare eCompare);
    virtual ~Texture(void);

    // 访问image
    inline void SetImage(Image* pImage);
    inline Image* GetImage(void);
    inline const Image* GetImage(void) const;

    // 访问纹理采样模式,默认是LINEAR
    inline void SetFilterType(FilterType eFType);
    inline FilterType GetFilterType(void) const;

    // 访问wrap模式,其中0 <= i < GetDimension(),默认都是CLAMP_TO_EDGE
    inline void SetWrapType(int i, WrapType eWType);
    inline WrapType GetWrapType(int i) const;

    // border color是采样发生在纹理图像边界时,纹理图像边界外的边界颜色,
    // 默认是SEColorRGBA(0,0,0,1)
    inline void SetBorderColor(const SEColorRGBA& rBorderColor);
    inline SEColorRGBA GetBorderColor(void) const;

    // 支持离屏纹理(render target)
    inline bool IsOffscreenTexture(void) const;
    inline void SetOffscreenTexture(bool bOffscreenTexture);

protected:
    ImagePtr m_spImage;
    FilterType m_eFType;       // default = LINEAR
    WrapType m_eWrapTypes[3];  // default = CLAMP_EDGE
    SEColorRGBA m_BorderColor;   // default = BLACK

    // 支持深度图纹理,默认是DC_COUNT,
    // 此时表明不是深度图纹理
    DepthCompare m_eCompare;

    // 支持离屏纹理,默认是false
    bool m_bOffscreenTexture;

private:
    static const char* ms_pFilterType[MAX_FILTER_TYPES];
    static const char* ms_pWrapType[MAX_WRAP_TYPES];
    static const char* ms_pDepthCompare[DC_COUNT];
};

typedef SESmartPointer<Texture> TexturePtr;

#include "SETexture.inl"

}

#endif
