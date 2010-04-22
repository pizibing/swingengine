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

#include "SEOGLES1RendererPCH.h"
#include "SEOGLES1Renderer.h"
#include "SEOGLES1Resources.h"

using namespace Swing;

GLenum SEOGLES1Renderer::ms_aeTextureMipmap[SETexture::MAX_FILTER_TYPES] =
{
    GL_NEAREST,
    GL_LINEAR,
    GL_NEAREST_MIPMAP_NEAREST,
    GL_NEAREST_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR
};

// 注意:
// OpenGL ES1只支持有限能力的texture wrap mode,对于其他不支持的模式,
// 相关的引擎层参数常量映射均为0，用户有责任避免使用这些引擎层参数常量.

GLenum SEOGLES1Renderer::ms_aeWrapMode[SETexture::MAX_WRAP_TYPES] =
{
    0,
    GL_REPEAT,
    0,
    0,
    GL_CLAMP_TO_EDGE
};

// 注意:
// OpenGL ES1只支持有限能力的texture pixel format,对于其他不支持的模式,
// 相关的引擎层参数常量映射均为0，用户有责任避免使用这些引擎层参数常量.

GLenum SEOGLES1Renderer::ms_aeImageComponents[SEImage::IT_COUNT] =
{
    GL_RGB,                    // SEImage::IT_RGB888
    GL_RGBA,                   // SEImage::IT_RGBA8888

    // 待实现.尚未测试.
    GL_DEPTH_COMPONENT16_OES,  // SEImage::IT_DEPTH16
    GL_DEPTH_COMPONENT24_OES,  // SEImage::IT_DEPTH24
    0,                         // SEImage::IT_DEPTH32
    GL_RGB,                    // SEImage::IT_CUBE_RGB888
    GL_RGBA,                   // SEImage::IT_CUBE_RGBA8888

    0,                         // SEImage::IT_RGB32
    0,                         // SEImage::IT_RGBA32

    // 待实现.尚未测试.
    GL_LUMINANCE,              // SEImage::IT_L8
    GL_LUMINANCE,              // SEImage::IT_L16

    0,                         // SEImage::IT_R32
    0,                         // SEImage::IT_RGB16
    0                          // SEImage::IT_RGBA16
};

GLenum SEOGLES1Renderer::ms_aeImageFormats[SEImage::IT_COUNT] =
{
    GL_RGB,                    // SEImage::IT_RGB888
    GL_RGBA,                   // SEImage::IT_RGBA8888

    // 待实现.尚未测试.
    GL_DEPTH_COMPONENT16_OES,  // SEImage::IT_DEPTH16
    GL_DEPTH_COMPONENT24_OES,  // SEImage::IT_DEPTH24
    0,                         // SEImage::IT_DEPTH32
    GL_RGB,                    // SEImage::IT_CUBE_RGB888
    GL_RGBA,                   // SEImage::IT_CUBE_RGBA8888

    0,                         // SEImage::IT_RGB32
    0,                         // SEImage::IT_RGBA32

    // 待实现.尚未测试.
    GL_LUMINANCE,              // SEImage::IT_L8
    GL_LUMINANCE,              // SEImage::IT_L16

    0,                         // SEImage::IT_R32
    0,                         // SEImage::IT_RGB16
    0                          // SEImage::IT_RGBA16
};

GLenum SEOGLES1Renderer::ms_aeImageTypes[SEImage::IT_COUNT] =
{
    GL_UNSIGNED_BYTE,    // SEImage::IT_RGB888
    GL_UNSIGNED_BYTE,    // SEImage::IT_RGBA8888

    // 待实现.尚未测试.
    GL_FLOAT,            // SEImage::IT_DEPTH16
    GL_FLOAT,            // SEImage::IT_DEPTH24
    0,                   // SEImage::IT_DEPTH32
    GL_UNSIGNED_BYTE,    // SEImage::IT_CUBE_RGB888
    GL_UNSIGNED_BYTE,    // SEImage::IT_CUBE_RGBA8888

    0,                   // SEImage::IT_RGB32
    0,                   // SEImage::IT_RGBA32

    // 待实现.尚未测试.
    GL_UNSIGNED_BYTE,    // SEImage::IT_L8
    GL_UNSIGNED_BYTE,    // SEImage::IT_L16

    0,                   // SEImage::IT_R32
    0,                   // SEImage::IT_RGB16
    0                    // SEImage::IT_RGBA16
};

GLenum SEOGLES1Renderer::ms_aeSamplerTypes[
    SESamplerInformation::MAX_SAMPLER_TYPES] =
{
    0,                    // SESamplerInformation::SAMPLER_1D
    GL_TEXTURE_2D,        // SESamplerInformation::SAMPLER_2D
    0,                    // SESamplerInformation::SAMPLER_3D
    0,                    // SESamplerInformation::SAMPLER_CUBE
    GL_TEXTURE_2D,        // SESamplerInformation::SAMPLER_PROJ
};

GLenum SEOGLES1Renderer::ms_aeDepthCompare[SETexture::DC_COUNT] =
{
    GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS
};

//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnLoadVProgram(SEResourceIdentifier*&, 
    SEVertexProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleaseVProgram(SEResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnLoadPProgram(SEResourceIdentifier*&, SEPixelProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleasePProgram(SEResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnLoadTexture(SEResourceIdentifier*& rpID,
    SETexture* pTexture)
{
    SETextureID* pResource = SE_NEW SETextureID;
    pResource->TextureObject = pTexture;
    rpID = pResource;

    // Get the texture image and its information.
    const SEImage* pImage = pTexture->GetImage();
    SE_ASSERT( pImage );
    int iDimension = pImage->GetDimension();
    SE_ASSERT( iDimension == 2 );
    unsigned char* aucData = pImage->GetData();
    int iComponent = ms_aeImageComponents[pImage->GetFormat()];
    int eFormat = ms_aeImageFormats[pImage->GetFormat()];
    int eIType = ms_aeImageTypes[pImage->GetFormat()];

    bool bIsRegularImage = !pImage->IsCubeImage();
    int eTarget = 0;
    if( bIsRegularImage )
    {
        eTarget = ms_aeSamplerTypes[iDimension-1];
    }
    else
    {
        // 待实现.
        SE_ASSERT( false );
    }

    // Generate the name and binding information.
    glGenTextures((GLsizei)1, &pResource->ID);
    glBindTexture(eTarget, pResource->ID);

    // Set the filter mode.
    SETexture::FilterType eFType = pTexture->GetFilterType();
    if( eFType == SETexture::NEAREST )
    {
        glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Set the mipmap mode.
    glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER,
					ms_aeTextureMipmap[eFType]);

    // Copy the image data from system memory to video memory.
    bool bNoMip =
        (eFType == SETexture::NEAREST || eFType == SETexture::LINEAR);

    // OpenGL ES2 only support 2D texture and cube texture,
    // (unless there is an 3D EXT type).
    switch( iDimension )
    {
    case 2:
        if( bIsRegularImage )
        {
            glTexImage2D(eTarget, 0, iComponent, pImage->GetBound(0),
                pImage->GetBound(1), 0, eFormat, eIType, aucData);

            if( !bNoMip )
            {
                glGenerateMipmapOES(eTarget);
			}
        }
        else
        {
		    // 待实现.
            // OpenGL ES1是否支持cube map?
            SE_ASSERT( false );
        }

        glTexParameteri(eTarget, GL_TEXTURE_WRAP_S,
            ms_aeWrapMode[pTexture->GetWrapType(0)]);
        glTexParameteri(eTarget, GL_TEXTURE_WRAP_T,
            ms_aeWrapMode[pTexture->GetWrapType(1)]);
        break;

    default:
        SE_ASSERT( false );
        break;
    }	
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleaseTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    glDeleteTextures((GLsizei)1, (GLuint*)&pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnLoadVBuffer(SEResourceIdentifier*& rpID,
    const SEAttributes& rIAttr, const SEAttributes& rOAttr,
    SEVertexBuffer* pVBuffer, SEVertexProgram*)
{
    SEVBufferID* pResource = SE_NEW SEVBufferID;
    rpID = pResource;
    pResource->IAttr = rIAttr;
    pResource->OAttr = rOAttr;

    int iChannels;
    float* afCompatible = 0;  // 由BuildCompatibleArray函数分配数据
    pVBuffer->BuildCompatibleArray(rIAttr, false, iChannels, afCompatible);

    // 创建buffer id并绑定vertex buffer.
    glGenBuffers(1, &pResource->ID);
    glBindBuffer(GL_ARRAY_BUFFER, pResource->ID);

    // 把vertex buffer数据从系统内存拷入显存.
    glBufferData(GL_ARRAY_BUFFER, iChannels*sizeof(float), afCompatible,
        GL_STATIC_DRAW);

    SE_DELETE[] afCompatible;
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleaseVBuffer(SEResourceIdentifier* pID)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    glDeleteBuffers(1, &pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnLoadIBuffer(SEResourceIdentifier*& rpID,
    SEIndexBuffer* pIBuffer)
{
    SEIBufferID* pResource = SE_NEW SEIBufferID;
    rpID = pResource;

    // 创建buffer id并绑定index buffer.
    glGenBuffers(1, &pResource->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);

    // 注意:	
    // OpenGL ES1只支持16位索引缓冲区,用户有责任确保所使用的引擎层32位索引缓冲区,
    // 与16位索引缓冲区兼容,也就是索引顶点的范围只能在区间[0,65535]上.
    // 在这个使用前提下,我们才能确保下面的数据创建过程是安全的.	
    int iICount = pIBuffer->GetIndexCount();
    size_t uiSize = iICount*sizeof(unsigned short);
    unsigned short* ausDstData = SE_NEW unsigned short[iICount];
    unsigned short* pDstData = ausDstData;
    int* pSrcData = pIBuffer->GetData();
    for( int i = 0; i < iICount; i++ )
    {
        *pDstData++ = (unsigned short)*pSrcData++;
    }

    // 把index buffer数据从系统内存拷入显存.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, ausDstData, GL_STATIC_DRAW);

    SE_DELETE[] ausDstData;
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleaseIBuffer(SEResourceIdentifier* pID)
{
    SEIBufferID* pResource = (SEIBufferID*)pID;
    glDeleteBuffers(1, &pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
