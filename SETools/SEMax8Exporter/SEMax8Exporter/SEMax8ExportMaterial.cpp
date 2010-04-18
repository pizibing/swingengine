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

#include "SEMax8SceneBuilder.h"
#include "SEMax8ExportSettings.h"
#include "bmmlib.h"

using namespace Swing;

const TCHAR* Max8SceneBuilder::ms_aacMapName[NTEXMAPS] =
{
    _T("map_ambient"),             // ID_AM
    _T("map_diffuse"),             // ID_DI
    _T("map_specular"),            // ID_SP
    _T("map_shininess"),           // ID_SH
    _T("map_shininess_strength"),  // ID_SS
    _T("map_selfillumination"),    // ID_SI
    _T("map_opacity"),             // ID_OP
    _T("map_filter_color"),        // ID_FI
    _T("map_bump"),                // ID_BU
    _T("map_reflection"),          // ID_RL
    _T("map_refraction"),          // ID_RR
    _T("map_displacment")          // ID_DP
};

const char* Max8SceneBuilder::ms_aacEnvName[5] =
{
    "env_explicit",
    "env_sphere",
    "env_cylinder",
    "env_shrink",
    "env_screen"
};

const TCHAR* Max8SceneBuilder::ms_acMapEnvironment = _T("map_environment");
const TCHAR* Max8SceneBuilder::ms_acMapGeneric = _T("map_generic");

//----------------------------------------------------------------------------
void Max8SceneBuilder::ConvertMaterials(INode* pTopNode)
{
    // 每个INode节点都可能带有一个材质树,
    // 遍历所有INode节点,收集到所有节点的顶层材质树,
    // 产生Max顶层材质树数组.
    CollectMaterials(pTopNode);

    if( !m_pSettings->IncludeMaterials )
    {
        return;
    }

    int iCount = m_MtlList.GetCount();
    m_MtlTree.resize(iCount);
    for( int i = 0; i < m_MtlList.GetCount(); i++ )
    {
        // 一次处理一个Max顶层材质树.
        Mtl* pMtl = m_MtlList.Get(i);
        if( pMtl )
        {
            ConvertMaterialTree(*pMtl, i, -1, m_MtlTree[i]);
        }
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::CollectMaterials(INode* pNode)
{
    Mtl* pMtl = pNode->GetMtl();
    if( pMtl )
    {
        m_MtlList.Add(pMtl);
    }

    for( int i = 0; i < pNode->NumberOfChildren(); i++ )
    {
        CollectMaterials(pNode->GetChildNode(i));
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::ConvertMaterialTree(Mtl& rMtl, int iMtlID, int iSubNo,
    Max8MaterialTree& rTree)
{
    // 根据Max材质创建一个Swing Engine材质.
    SEMaterialStatePtr spSEMaterialState = new SEMaterialState;
    Color tempColor = rMtl.GetAmbient();
    float fAlpha = 1.0f - rMtl.GetXParency();
    spSEMaterialState->Ambient = SEColorRGB(tempColor.r, tempColor.g, tempColor.b);
    tempColor = rMtl.GetDiffuse();
    spSEMaterialState->Diffuse = SEColorRGB(tempColor.r, tempColor.g, tempColor.b);
    tempColor = rMtl.GetSpecular();
    spSEMaterialState->Specular = SEColorRGB(tempColor.r, tempColor.g, tempColor.b);
    spSEMaterialState->Shininess = 128.0f * rMtl.GetShininess();
	spSEMaterialState->Alpha = fAlpha; // 待检查

    const char* acName = (const char*)rMtl.GetName();
    spSEMaterialState->SetName(acName);
    rTree.SetMaterial(spSEMaterialState);

    // 获取子纹理(建立该材质的子纹理树).
    int iTCount = rMtl.NumSubTexmaps();
    if( iTCount > 0 )
    {
        rTree.SetTChildCount(iTCount);
        for( int i = 0; i < iTCount; i++ )
        {
            Texmap* pSubTex = rMtl.GetSubTexmap(i);
            if( pSubTex )
            {
                // 检查材质是否为"标准"材质且是否开启子纹理.
                // 如果以上条件不满足,则不处理该子纹理.
                if( rMtl.ClassID() == Class_ID(DMTL_CLASS_ID, 0)
                &&   !((StdMat&)rMtl).MapEnabled(i) )
                {
                    continue;
                }

                ConvertTextureTree(*pSubTex, rMtl.ClassID(), i, rTree.GetTChild(i));
            }
        }
    }

    // 获取子材质(建立该材质的子材质树).
    int iMCount = rMtl.NumSubMtls();
    if( iMCount > 0 )
    {
        rTree.SetMChildCount(iMCount);
        for( int i = 0; i < iMCount; i++ )
        {
            Mtl* pSubMtl = rMtl.GetSubMtl(i);
            if( pSubMtl )
                ConvertMaterialTree(*pSubMtl, 0, i, rTree.GetMChild(i));
        }
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::ConvertTextureTree(Texmap& rTex, Class_ID ClassID,
    int iSubNo, Max8TextureTree& rTree)
{
    if( rTex.ClassID() == Class_ID(BMTEX_CLASS_ID, 0) )
    {
        // 纹理是一个位图数据.
        SETexture* pSETexture = new SETexture;
        rTree.SetTexture(pSETexture);

        const TCHAR* acTexName = rTex.GetName(); // 纹理名
        const TCHAR* acMapName;                  // 纹理用途名
        if( ClassID == Class_ID(0, 0) )
            acMapName = ms_acMapEnvironment;
        else if( ClassID == Class_ID(DMTL_CLASS_ID, 0) )
            acMapName = ms_aacMapName[iSubNo];
        else
            acMapName = ms_acMapGeneric;

        int iCombineLength = _tcslen(acTexName) + _tcslen(acMapName) + 3;
        TCHAR* acCombineName = new TCHAR[iCombineLength];
        _stprintf(acCombineName, "%s: %s", acTexName, acMapName);
        const char* acName = (const char*)acCombineName;
        pSETexture->SetName(acName);

        BitmapTex& rBmpTex = (BitmapTex&)rTex;
        Bitmap* pBmp = rBmpTex.GetBitmap(m_iTimeStart);
        if( !pBmp )
        {
            // 没有找到位图数据
            assert( false );

            return;
        }

        int iWidth = pBmp->Width();
        int iHeight = pBmp->Height();

        TSTR tempFileName = rBmpTex.GetMapName();
        char acDrive[_MAX_DRIVE];
        char acDir[_MAX_DIR];
        char acFName[_MAX_FNAME];
        char acExt[_MAX_EXT];
        _splitpath(tempFileName.data(), acDrive, acDir, acFName, acExt);
        SESystem::SE_Strcat(acFName, _MAX_FNAME, ".seif");
        
        SEImage* pSEImage;
        int eFormat;
        int iBytesPerPixel;
        BOOL bHasAlpha = pBmp->HasAlpha();
        if( bHasAlpha )
        {
            eFormat =  SEImage::IT_RGBA8888;
            iBytesPerPixel = 4;
        }
        else
        {
            eFormat = SEImage::IT_RGB888;
            iBytesPerPixel = 3;
        }

        WIN32_FIND_DATA tempFindData;
        HANDLE hFile = FindFirstFile(acFName, &tempFindData);
        FindClose(hFile);

        if( hFile == INVALID_HANDLE_VALUE || m_pSettings->GenerateMaps )
        {
            int iCount = iWidth * iHeight * iBytesPerPixel;
            unsigned char* aucDst = new unsigned char[iCount];
            unsigned char* pucDst = aucDst;
            BMM_Color_64* pScanLine = new BMM_Color_64[iWidth];
            BMM_Color_64* pPixel;
            BMM_Color_32 tempScaledColor;
            for( int iY = iHeight - 1; iY >= 0; iY-- )
            {
                pBmp->GetLinearPixels(0, iY, iWidth, pScanLine);
                pPixel = pScanLine;
                for( int iX = 0; iX < iWidth; iX++ )
                {
                    AColor tempColor(*pPixel);
                    tempScaledColor = (BMM_Color_32)tempColor;
                    *pucDst++ = (unsigned char)tempScaledColor.r;
                    *pucDst++ = (unsigned char)tempScaledColor.g;
                    *pucDst++ = (unsigned char)tempScaledColor.b;
                    if( bHasAlpha )
                        *pucDst++ = (unsigned char)tempScaledColor.a;
                    pPixel++;
                }
            }
            delete[] pScanLine;
			pSEImage = new SEImage((SEImage::FormatMode)eFormat, 
                iWidth, iHeight, aucDst, acFName, false);
            pSEImage->Save(acFName);
        }
        else
        {
            pSEImage = new SEImage((SEImage::FormatMode)eFormat, 
                pBmp->Width(), pBmp->Height(), NULL, acFName, false);
        }

        pSETexture->SetImage(pSEImage);
    
        StdUVGen* pUVGen = rBmpTex.GetUVGen();
        if( pUVGen )
        {
            pSETexture->SetName(ms_aacEnvName[pUVGen->GetCoordMapping(0)]);

            // TO DO.  Need to handle animated texture coordinates.  What to
            // do when the UV parameters are not the standard ones?  The
            // functions below are called through pUVGen.  The "noise"
            // parameters appear to be for procedural generation of textures.
            //
            // U offset:      GetUOffs(time)
            // V offset:      GetVOffs(time)
            // U tiling:      GetUScl(time)
            // V tiling:      GetVScl(time)
            // angle:         GetAng(time)
            // blur:          GetBlur(time)
            // blur offset:   GetBlurOffs(time)
            // noise amount:  GetNoiseAmt(time)
            // noise size:    GetNoiseSize(time)
            // noise level:   GetNoiseLev(time)
            // noise phase:   GetNoisePhs(time)

            // Apparently Max always uses wrapping?
			pSETexture->SetWrapType(0, SETexture::REPEAT);
            pSETexture->SetWrapType(0, SETexture::REPEAT);
        }

        switch( rBmpTex.GetFilterType() )
        {
        case FILTER_PYR:
            // bilinear filter, trilinear mipmap
            pSETexture->SetFilterType(SETexture::LINEAR_LINEAR);

            break;
        case FILTER_SAT:
            // 待实现.
            // 这是什么?如何转换?
            pSETexture->SetFilterType(SETexture::NEAREST_NEAREST);

            break;
        default:
            pSETexture->SetFilterType(SETexture::NEAREST_NEAREST);

            break;
        }
    }

    int iTCount = rTex.NumSubTexmaps();
    if( iTCount > 0 )
    {
        rTree.SetChildCount(iTCount);
        for( int i = 0; i < iTCount; i++ )
        {
            Texmap* pSubTex = rTex.GetSubTexmap(i);
            if( pSubTex )
            {
                ConvertTextureTree(*pSubTex, rTex.ClassID(), i, rTree.GetChild(i));
            }
        }
    }
}
//----------------------------------------------------------------------------