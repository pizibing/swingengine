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

#include "SEOpenGLRendererPCH.h"
#include "SEOpenGLRenderer.h"
#include "SEOpenGLResources.h"

using namespace Swing;

GLenum OpenGLRenderer::ms_aeTextureMipmap[Texture::MAX_FILTER_TYPES] =
{
    GL_NEAREST,
    GL_LINEAR,
    GL_NEAREST_MIPMAP_NEAREST,
    GL_NEAREST_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR
};

GLenum OpenGLRenderer::ms_aeWrapMode[Texture::MAX_WRAP_TYPES] =
{
    GL_CLAMP,
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_BORDER,
    GL_CLAMP_TO_EDGE
};

GLenum OpenGLRenderer::ms_aeImageComponents[Image::IT_COUNT] =
{
    GL_RGB8,               // Image::IT_RGB888
    GL_RGBA8,              // Image::IT_RGBA8888
    GL_DEPTH_COMPONENT16,  // Image::IT_DEPTH16
    GL_DEPTH_COMPONENT24,  // Image::IT_DEPTH24
    GL_DEPTH_COMPONENT32,  // Image::IT_DEPTH32
    GL_RGB8,               // Image::IT_CUBE_RGB888
    GL_RGBA8,              // Image::IT_CUBE_RGBA8888
    GL_RGB32F_ARB,         // Image::IT_RGB32
    GL_RGBA32F_ARB,        // Image::IT_RGBA32
    GL_LUMINANCE8,         // Image::IT_L8
    GL_LUMINANCE16,        // Image::IT_L16
    GL_LUMINANCE32F_ARB,   // Image::IT_R32
    GL_RGB16F_ARB,         // Image::IT_RGB16
    GL_RGBA16F_ARB,        // Image::IT_RGBA16
    GL_RGB5,               // Image::IT_RGB565
    GL_RGB5_A1,            // Image::IT_RGBA5551
    GL_RGBA4               // Image::IT_RGBA4444
};

GLenum OpenGLRenderer::ms_aeImageFormats[Image::IT_COUNT] =
{
    GL_RGB,              // Image::IT_RGB888
    GL_RGBA,             // Image::IT_RGBA8888
    GL_DEPTH_COMPONENT,  // Image::IT_DEPTH16
    GL_DEPTH_COMPONENT,  // Image::IT_DEPTH24
    GL_DEPTH_COMPONENT,  // Image::IT_DEPTH32
    GL_RGB,              // Image::IT_CUBE_RGB888
    GL_RGBA,             // Image::IT_CUBE_RGBA8888
    GL_RGB,              // Image::IT_RGB32
    GL_RGBA,             // Image::IT_RGBA32
    GL_LUMINANCE,        // Image::IT_L8
    GL_LUMINANCE,        // Image::IT_L16
    GL_LUMINANCE,        // Image::IT_R32
    GL_RGB,              // Image::IT_RGB16
    GL_RGBA,             // Image::IT_RGBA16
    GL_RGB,              // Image::IT_RGB565
    GL_RGBA,             // Image::IT_RGBA5551
    GL_RGBA              // Image::IT_RGBA4444
};

GLenum OpenGLRenderer::ms_aeImageTypes[Image::IT_COUNT] =
{
    GL_UNSIGNED_BYTE,               // Image::IT_RGB888
    GL_UNSIGNED_BYTE,               // Image::IT_RGBA8888
    GL_FLOAT,                       // Image::IT_DEPTH16
    GL_FLOAT,                       // Image::IT_DEPTH24
    GL_DEPTH_COMPONENT,             // Image::IT_DEPTH32
    GL_UNSIGNED_BYTE,               // Image::IT_CUBE_RGB888
    GL_UNSIGNED_BYTE,               // Image::IT_CUBE_RGBA8888
    GL_FLOAT,                       // Image::IT_RGB32
    GL_FLOAT,                       // Image::IT_RGBA32
    GL_UNSIGNED_BYTE,               // Image::IT_L8
    GL_UNSIGNED_SHORT,              // Image::IT_L16
    GL_FLOAT,                       // Image::IT_R32
    GL_HALF_FLOAT_ARB,              // Image::IT_RGB16
    GL_HALF_FLOAT_ARB,              // Image::IT_RGBA16
    GL_UNSIGNED_SHORT_5_6_5_REV,    // Image::IT_RGB565
    GL_UNSIGNED_SHORT_1_5_5_5_REV,  // Image::IT_RGBA5551
    GL_UNSIGNED_SHORT_4_4_4_4_REV   // Image::IT_RGBA4444
};

GLenum OpenGLRenderer::ms_aeSamplerTypes[
    SamplerInformation::MAX_SAMPLER_TYPES] =
{
    GL_TEXTURE_1D,        // SamplerInformation::SAMPLER_1D
    GL_TEXTURE_2D,        // SamplerInformation::SAMPLER_2D
    GL_TEXTURE_3D,        // SamplerInformation::SAMPLER_3D
    GL_TEXTURE_CUBE_MAP,  // SamplerInformation::SAMPLER_CUBE
    GL_TEXTURE_2D,        // SamplerInformation::SAMPLER_PROJ
};

GLenum OpenGLRenderer::ms_aeDepthCompare[Texture::DC_COUNT] =
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
void OpenGLRenderer::OnLoadVProgram(ResourceIdentifier*& rpID,
    VertexProgram* pVProgram)
{
    VProgramID* pResource = SE_NEW VProgramID;
    ProgramData* pData = (ProgramData*)pVProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    cgGLLoadProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnReleaseVProgram(ResourceIdentifier* pID)
{
    VProgramID* pResource = (VProgramID*)pID;
    cgGLUnloadProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnLoadPProgram(ResourceIdentifier*& rpID,
    PixelProgram* pPProgram)
{
    PProgramID* pResource = SE_NEW PProgramID;
    ProgramData* pData = (ProgramData*)pPProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    cgGLLoadProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnReleasePProgram(ResourceIdentifier* pID)
{
    PProgramID* pResource = (PProgramID*)pID;
    cgGLUnloadProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnLoadTexture(ResourceIdentifier*& rpID,
    Texture* pTexture)
{
    // Activate the texture unit in hardware that will manage this texture.
    TextureID* pResource = SE_NEW TextureID;
    pResource->TextureObject = pTexture;
    rpID = pResource;

    // Get the texture image and its information.
    const Image* pImage = pTexture->GetImage();
    SE_ASSERT( pImage );
    int iDimension = pImage->GetDimension();
    unsigned char* aucData = pImage->GetData();
    int iComponent = ms_aeImageComponents[pImage->GetFormat()];
    int eFormat = ms_aeImageFormats[pImage->GetFormat()];
    int eIType = ms_aeImageTypes[pImage->GetFormat()];

    bool bIsRegularImage = !pImage->IsCubeImage();
    int eTarget;
    if( bIsRegularImage )
    {
        eTarget = ms_aeSamplerTypes[iDimension-1];
    }
    else
    {
        eTarget = GL_TEXTURE_CUBE_MAP;
    }

    // Generate the name and binding information.
    glGenTextures((GLsizei)1, &pResource->ID);
    glBindTexture(eTarget, pResource->ID);

    // Set the filter mode.
    Texture::FilterType eFType = pTexture->GetFilterType();
    if( eFType == Texture::NEAREST
    ||  iComponent == GL_RGB32F_ARB
    ||  iComponent == GL_RGBA32F_ARB )
    {
        glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        // TO DO.  Support anisotropic filtering.  To query for the maximum
        // allowed anisotropy, use
        //   float fMax;
        //   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&fMax);
        // To enable filtering, use
        //   glTexParameterf(eTarget,GL_TEXTURE_MAX_ANISOTROPY_EXT,fValue);
        // where 1 <= fValue <= fMax.

        glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Set the mipmap mode.
    if( iComponent == GL_RGB32F_ARB || iComponent == GL_RGBA32F_ARB )
    {
        glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    else
    {
        glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER,
            ms_aeTextureMipmap[eFType]);
    }

    // Set the border color (for clamp to border).
    glTexParameterfv(eTarget, GL_TEXTURE_BORDER_COLOR,
        (const float*)pTexture->GetBorderColor());

    // Copy the image data from system memory to video memory.
    bool bNoMip =
        (eFType == Texture::NEAREST || eFType == Texture::LINEAR);

    switch( iDimension )
    {
    case 1:
        if( bNoMip )
        {
            glTexImage1D(eTarget, 0, iComponent, pImage->GetBound(0), 0,
                eFormat, eIType, aucData);
        }
        else
        {
            gluBuild1DMipmaps(eTarget, iComponent, pImage->GetBound(0),
                eFormat, eIType, aucData);
        }
        glTexParameteri(eTarget, GL_TEXTURE_WRAP_S,
            ms_aeWrapMode[pTexture->GetWrapType(0)]);
        break;

    case 2:
        if( bIsRegularImage )
        {
            if( bNoMip )
            {
                glTexImage2D(eTarget, 0, iComponent, pImage->GetBound(0),
                    pImage->GetBound(1), 0, eFormat, eIType, aucData);
            }
            else
            {
                gluBuild2DMipmaps(eTarget, iComponent, pImage->GetBound(0),
                    pImage->GetBound(1), eFormat, eIType, aucData);
            }
        }
        else
        {
            // A cube map image has 6 subimages (+x,-x,+y,-y,+z,-z).
            int iDelta = pImage->GetBytesPerPixel()*pImage->GetCount();
            int i;

            if( bNoMip )
            {
                for( i = 0; i < 6; i++, aucData += iDelta )
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0,
                        iComponent, pImage->GetBound(0), pImage->GetBound(1),
                        0, eFormat, eIType, aucData);
                }
            }
            else
            {
                for( i = 0; i < 6; i++, aucData += iDelta )
                {
                    gluBuild2DMipmaps(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
                        iComponent, pImage->GetBound(0), pImage->GetBound(1),
                        eFormat, eIType, aucData);
                }
            }
        }

        glTexParameteri(eTarget, GL_TEXTURE_WRAP_S,
            ms_aeWrapMode[pTexture->GetWrapType(0)]);
        glTexParameteri(eTarget, GL_TEXTURE_WRAP_T,
            ms_aeWrapMode[pTexture->GetWrapType(1)]);
        break;

    case 3:
        // TO DO.  Microsoft's GLU library does not implement the function
        // gluBuild3DMipmaps.  DirectX9 SDK does not support automatic
        // generation of mipmaps for volume textures.  For now, do not
        // support mipmaps of 3D textures.  However, manually generated
        // mipmaps can be added later.
        glTexImage3D(eTarget, 0, iComponent, pImage->GetBound(0),
            pImage->GetBound(1), pImage->GetBound(2), 0, eFormat, eIType,
            aucData);

        glTexParameteri(eTarget, GL_TEXTURE_WRAP_S,
            ms_aeWrapMode[pTexture->GetWrapType(0)]);
        glTexParameteri(eTarget, GL_TEXTURE_WRAP_T,
            ms_aeWrapMode[pTexture->GetWrapType(1)]);
        glTexParameteri(eTarget, GL_TEXTURE_WRAP_R,
            ms_aeWrapMode[pTexture->GetWrapType(2)]);
        break;

    default:
        SE_ASSERT( false );
        break;
    }
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnReleaseTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;
    glDeleteTextures((GLsizei)1, (GLuint*)&pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnLoadVBuffer(ResourceIdentifier*& rpID,
    const Attributes& rIAttr, const Attributes& rOAttr,
    VertexBuffer* pVBuffer, VertexProgram*)
{
    VBufferID* pResource = SE_NEW VBufferID;
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
void OpenGLRenderer::OnReleaseVBuffer(ResourceIdentifier* pID)
{
    VBufferID* pResource = (VBufferID*)pID;
    glDeleteBuffers(1, &pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnLoadIBuffer(ResourceIdentifier*& rpID,
    IndexBuffer* pIBuffer)
{
    IBufferID* pResource = SE_NEW IBufferID;
    rpID = pResource;

    // 创建buffer id并绑定index buffer.
    glGenBuffers(1, &pResource->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);

    // 把index buffer数据从系统内存拷入显存.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        pIBuffer->GetIndexCount()*sizeof(int), pIBuffer->GetData(),
        GL_STATIC_DRAW);
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnReleaseIBuffer(ResourceIdentifier* pID)
{
    IBufferID* pResource = (IBufferID*)pID;
    glDeleteBuffers(1, &pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
