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
#include "SEOpenGLResources.h"
#include "SEOpenGLProgram.h"
#include "SEOpenGLProgramInterfaceCatalog.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(OpenGLProgram);

//SE_REGISTER_INITIALIZE(OpenGLProgram);

//----------------------------------------------------------------------------
void OpenGLProgram::Initialize()
{
    Program::OnLoadProgram = &OpenGLProgram::OnLoadProgram;
    Program::OnReleaseUserData = &OpenGLProgram::OnReleaseUserData;
    LightingEffect::OnConfigureLighting = &OpenGLProgram::OnConfigureLighting;
}
//----------------------------------------------------------------------------
OpenGLProgram::OpenGLProgram()
{
}
//----------------------------------------------------------------------------
bool OpenGLProgram::OnLoadProgram(Renderer* pRenderer, 
    const std::string& rProgramName, Program* pProgram, Program::ProgramType eType, 
    InterfaceDescriptor* pInterfaceDesc)
{
    if( !pRenderer || !pProgram )
    {
        SE_ASSERT( false );
        return false;
    }

    // 获取file name和entry name.
    size_t uiLen = strlen(rProgramName.c_str()) + 1;
    char* acProgramName = SE_NEW char[uiLen];
    System::SE_Strcpy(acProgramName, uiLen, rProgramName.c_str());
    char* pNextToken;
    char* acFileName = System::SE_Strtok(acProgramName, ".", pNextToken);
    char* acEntryName = System::SE_Strtok(0, ".", pNextToken);
    if( !acFileName || !acEntryName )
    {
        // 获取file name和entry name失败.
        SE_DELETE[] acProgramName;
        return false;
    }

    std::string tempFileName = std::string(acFileName) + std::string(".cg");
    const char* pDecorated = System::SE_GetPath(tempFileName.c_str(), 
        System::SM_READ);
    if( !pDecorated )
    {
        // 没有找到指定Cg文件.
        SE_DELETE[] acProgramName;
        return false;
    }

    // 为了在代理类的静态函数中访问基类的保护成员,我们必须转换指针类型,
    // 由于我们能确保只访问基类成员,因此这样做是安全的.
    OpenGLProgram* pOpenGLProgram = (OpenGLProgram*)pProgram;
    Program::ProgramType& rProgramType = pOpenGLProgram->m_eProgramType;
    pProgram->UserData = SE_NEW ProgramData;
    CGprogram& rCgProgram = ((ProgramData*)pProgram->UserData)->ID;
    CGcontext hCgContext;
    CGprofile hCgProfile;
    CGparameter hCgParam;

    OpenGLRenderer* pOpenGLRenderer = (OpenGLRenderer*)pRenderer;
    hCgContext = pOpenGLRenderer->GetCgContext();
    rProgramType = eType;
    switch( eType )
    {
    case Program::PT_VERTEX:
        hCgProfile = pOpenGLRenderer->GetCgLatestVertexProfile();
        break;
    case Program::PT_PIXEL:
        hCgProfile = pOpenGLRenderer->GetCgLatestPixelProfile();
        break;
    case Program::PT_GEOMETRY:
        hCgProfile = pOpenGLRenderer->GetCgLatestGeometryProfile();
        break;
    default:
        SE_ASSERT( false );
        SE_DELETE[] acProgramName;
        return false;
    }

    // 含有shader interface的program此时无法正确编译,应在inteface对接后编译.
    cgSetAutoCompile(hCgContext, CG_COMPILE_MANUAL);
    SE_GL_DEBUG_CG_PROGRAM;

    // 创建Cg program,稍后手动编译.
    rCgProgram = cgCreateProgramFromFile(hCgContext, CG_SOURCE,
        pDecorated, hCgProfile, acEntryName, 0);
    SE_GL_DEBUG_CG_PROGRAM;

    // 如果有用户定义的shader interface描述信息,则需对接这些interface.
    if( pInterfaceDesc )
    {
        ProgramData* pData = (ProgramData*)pProgram->UserData;
        std::vector<OpenGLProgramInterfacePtr>& rProgramInterfaces = 
            pData->Interfaces;
        DescriptorItem* pDescriptorItem = 0;

        int iItemCount = pInterfaceDesc->GetCount();
        for( int i = 0; i < iItemCount; i++ )
        {
            pDescriptorItem = pInterfaceDesc->GetItem(i);

            CGparameter hCgUserTypeParam;
            CGparameter hCgUserInstParam = cgGetNamedParameter(rCgProgram, 
                pDescriptorItem->GetInstanceName().c_str());
            SE_GL_DEBUG_CG_PROGRAM;
            SE_ASSERT( hCgUserInstParam );

            int iTypeCount = pDescriptorItem->GetTypeCount();
            SE_ASSERT( iTypeCount >= 1 );

            if( pDescriptorItem->IsArray )
            {
                cgSetArraySize(hCgUserInstParam, iTypeCount);
                SE_GL_DEBUG_CG_PROGRAM;
			
                for( int j = 0; j < iTypeCount; j++ )
                {
                    OpenGLProgramInterface* pInterface = 
                        OpenGLProgramInterfaceCatalog::GetActive()->Find(rCgProgram,
                        pDescriptorItem->GetTypeName(j));
                    SE_ASSERT( pInterface );
                    hCgUserTypeParam = pInterface->GetParam();

                    CGparameter hCgArrayElementParam = 
                        cgGetArrayParameter(hCgUserInstParam, j);
                    cgConnectParameter(hCgUserTypeParam, hCgArrayElementParam);
                    SE_GL_DEBUG_CG_PROGRAM;

                    rProgramInterfaces.push_back(pInterface);
                }
            }
            else
            {
                OpenGLProgramInterface* pInterface = 
                    OpenGLProgramInterfaceCatalog::GetActive()->Find(rCgProgram,
                    pDescriptorItem->GetTypeName(0));
                    SE_ASSERT( pInterface );
                    hCgUserTypeParam = pInterface->GetParam();

                cgConnectParameter(hCgUserTypeParam, hCgUserInstParam);
                SE_GL_DEBUG_CG_PROGRAM;

                rProgramInterfaces.push_back(pInterface);
            }
        }
    }

    // 延迟的编译.
    cgCompileProgram(rCgProgram);
    SE_GL_DEBUG_CG_PROGRAM;

    // 解析shader constant和sampler.
    hCgParam = cgGetFirstParameter(rCgProgram, CG_PROGRAM);
    SE_GL_DEBUG_CG_PROGRAM;
    if( !hCgParam )
    {
        SE_ASSERT( false );
        SE_DELETE[] acProgramName;
        return false;
    }
    if( !RecursParams(hCgParam, pProgram) )
    {
        SE_DELETE[] acProgramName;
        return false;
    }

    SE_DELETE[] acProgramName;
    return true;
}
//----------------------------------------------------------------------------
bool OpenGLProgram::RecursParams(CGparameter hCgParam, Program* pProgram)
{
    if( !hCgParam )
        return true;

    do
    {
        switch( cgGetParameterType(hCgParam) )
        {
        case CG_STRUCT :
            if( !RecursParams(cgGetFirstStructParameter(hCgParam), pProgram) )
                return false;
            break;

        case CG_ARRAY :
            {
                int iArraySize = cgGetArraySize(hCgParam, 0);
                for( int i = 0; i < iArraySize; i++ )
                {
                    if( !RecursParams(cgGetArrayParameter(hCgParam, i), pProgram) )
                        return false;
                }
            }
            break;

        default :
            if( !ParseParam(hCgParam, pProgram) )
                return false;
        }
    }while( (hCgParam = cgGetNextParameter(hCgParam)) != 0 );

    return true;
}
//----------------------------------------------------------------------------
bool OpenGLProgram::ParseParam(CGparameter hCgParam, Program* pProgram)
{
    if( !hCgParam || !pProgram )
        return false;

    // 待填充数据.
    // 为了在代理类的静态函数中访问基类的保护成员,我们必须转换指针类型,
    // 由于我们能确保只访问基类成员,因此这样做是安全的.
    OpenGLProgram* pOpenGLProgram = (OpenGLProgram*)pProgram;
    Attributes& rIAttributes = pOpenGLProgram->m_InputAttributes;
    Attributes& rOAttributes = pOpenGLProgram->m_OutputAttributes;
    std::vector<RendererConstant>& rRCs = pOpenGLProgram->m_RendererConstants;
    std::vector<UserConstant>& rUCs = pOpenGLProgram->m_UserConstants;
    std::vector<SamplerInformation>& rSIs = 
        pOpenGLProgram->m_SamplerInformation;

    std::string StrParamName, StrParamSemantic;
    int iNumFloats, iUnit;
    SamplerInformation::Type eSType;
    RendererConstant::Type eRCType;

    CGtype eCgParamType;
    CGenum eCgParamDir;
    const char* acParamSemantic;
    const char* acParamName;

    eCgParamType = cgGetParameterType(hCgParam);
    SE_GL_DEBUG_CG_PROGRAM;
    eCgParamDir = cgGetParameterDirection(hCgParam);
    SE_GL_DEBUG_CG_PROGRAM;
    acParamSemantic = cgGetParameterSemantic(hCgParam);
    SE_GL_DEBUG_CG_PROGRAM;
    acParamName = cgGetParameterName(hCgParam);
    SE_GL_DEBUG_CG_PROGRAM;

    // 获取parameter名字.
    StrParamName = acParamName;

    // 获取parameter数据类型.
    iNumFloats = 0;
    eSType = SamplerInformation::MAX_SAMPLER_TYPES;
    if( eCgParamType == CG_FLOAT )
    {
        iNumFloats = 1;
    }
    else if( eCgParamType == CG_FLOAT2 )
    {
        iNumFloats = 2;
    }
    else if( eCgParamType == CG_FLOAT3 )
    {
        iNumFloats = 3;
    }
    else if( eCgParamType == CG_FLOAT4 )
    {
        iNumFloats = 4;
    }
    else if( eCgParamType == CG_FLOAT4x4 )
    {
        iNumFloats = 16;
    }
    else if( eCgParamType == CG_SAMPLER1D )
    {
        eSType = SamplerInformation::SAMPLER_1D;
    }
    else if( eCgParamType == CG_SAMPLER2D )
    {
        eSType = SamplerInformation::SAMPLER_2D;
    }
    else if( eCgParamType == CG_SAMPLER3D )
    {
        eSType = SamplerInformation::SAMPLER_3D;
    }
    else if( eCgParamType == CG_SAMPLERCUBE )
    {
        eSType = SamplerInformation::SAMPLER_CUBE;
    }
    else
    {
        // 引擎尚未支持的变量数据类型.
        SE_ASSERT( false );
        return false;
    }

    // 获取采样器信息(如果当前parameter是采样器声明).
    if( eSType != SamplerInformation::MAX_SAMPLER_TYPES )
    {
        SamplerInformation TempSU(StrParamName.c_str(), eSType, 
            (void*)hCgParam);
        rSIs.push_back(TempSU);
        return true;
    }

    StrParamSemantic = acParamSemantic;
    if( eCgParamDir == CG_IN )
    {
        if( StrParamSemantic == Program::ms_PositionStr 
         || StrParamSemantic == Program::ms_Position0Str )
        {
            // 只支持(x,y,z) position.
            rIAttributes.SetPositionChannels(3);
        }
        else if( StrParamSemantic == Program::ms_NormalStr 
              || StrParamSemantic == Program::ms_Normal0Str )
        {
            // 只支持(x,y,z) normals.
            rIAttributes.SetNormalChannels(3);
        }
        else if( StrParamSemantic == Program::ms_ColorStr
              || StrParamSemantic == Program::ms_Color0Str )
        {
            rIAttributes.SetColorChannels(0, iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_Color1Str )
        {
            rIAttributes.SetColorChannels(1, iNumFloats);
        }
        else if( StrParamSemantic.substr(0, 8) == Program::ms_TexCoordStr )
        {
            iUnit = (int)StrParamSemantic[8] - '0';
            rIAttributes.SetTCoordChannels(iUnit, iNumFloats);
        }
        else
        {
            // 变量必定是一个renderer constant或者user-defined constant.
            eRCType = RendererConstant::GetType(StrParamName.c_str());
            if( eRCType != RendererConstant::MAX_TYPES )
            {
                // renderer constant.
                RendererConstant TempRC(eRCType, (void*)hCgParam, 
                    iNumFloats);
                rRCs.push_back(TempRC);
            }
            else
            {
                // user-defined constant.
                UserConstant TempUC(StrParamName.c_str(), (void*)hCgParam, 
                    iNumFloats);
                rUCs.push_back(TempUC);
            }
        }
    }
    else if( eCgParamDir == CG_OUT )
    {
        if( StrParamSemantic == Program::ms_PositionStr 
         || StrParamSemantic == Program::ms_Position0Str )
        {
            rOAttributes.SetPositionChannels(iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_NormalStr 
              || StrParamSemantic == Program::ms_Normal0Str )
        {
            rOAttributes.SetNormalChannels(iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_ColorStr
              || StrParamSemantic == Program::ms_Color0Str )
        {
            rOAttributes.SetColorChannels(0, iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_Color1Str )
        {
            rOAttributes.SetColorChannels(1, iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_Color2Str )
        {
            rOAttributes.SetColorChannels(2, iNumFloats);
        }
        else if( StrParamSemantic == Program::ms_Color3Str )
        {
            rOAttributes.SetColorChannels(3, iNumFloats);
        }
        else
        {
            if( StrParamSemantic.substr(0, 8) != Program::ms_TexCoordStr )
            {
                // 引擎尚未支持的变量semantic类型.
                SE_ASSERT( false );
                return false;
            }
            iUnit = (int)StrParamSemantic[8] - '0';
            rOAttributes.SetTCoordChannels(iUnit, iNumFloats);
        }
    }
    else
    {
        // 待实现.
        // 引擎尚未支持的变量IO类型,如CG_INOUT.
        SE_ASSERT( false );
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void OpenGLProgram::OnReleaseUserData(void* pUserData)
{
    ProgramData* pData = (ProgramData*)pUserData;

    if( pData )
    {
        if( pData->ID )
        {
            cgDestroyProgram(pData->ID);
            SE_GL_DEBUG_CG_PROGRAM;
        }

        SE_DELETE pData;
    }
}
//----------------------------------------------------------------------------
void OpenGLProgram::OnConfigureLighting(LightingEffect* pLEffect)
{
    VertexShader* pVShader;
    PixelShader* pPShader;

    int iLCount = pLEffect->GetLightCount();
    LightingEffect::LightingMode eMode = pLEffect->GetLightingMode();

    if( iLCount == 0 )
    {
        pVShader = SE_NEW VertexShader("Material.v_Material");
        pPShader = SE_NEW PixelShader("PassThrough.p_PassThrough4");
        pLEffect->SetVShader(0, pVShader);
        pLEffect->SetPShader(0, pPShader);

        return;
    }
    else
    {
        if( eMode == LightingEffect::LM_VERTEX )
        {
            pVShader = SE_NEW VertexShader("ILighting.v_ILighting");
            pPShader = SE_NEW PixelShader(
                "ILighting.p_LightingPassThrough4");
            pLEffect->SetVShader(0, pVShader);
            pLEffect->SetPShader(0, pPShader);
        }
        else if( eMode == LightingEffect::LM_PIXEL )
        {
            pVShader = SE_NEW VertexShader(
                "ILighting.v_LightingPassThrough");
            pPShader = SE_NEW PixelShader("ILighting.p_ILighting");
            pLEffect->SetVShader(0, pVShader);
            pLEffect->SetPShader(0, pPShader);
        }
        else
        {
            SE_ASSERT( false );
            return;
        }
    }

    std::string aLightTypes[4] = {"AmbientLight", "DirectionalLight", "PointLight", 
        "SpotLight"};
    int iLightType;

    InterfaceDescriptor* pInterfaceDesc = SE_NEW InterfaceDescriptor;
    if( eMode == LightingEffect::LM_VERTEX )
    {
        pVShader->SetInterfaceDescriptor(pInterfaceDesc);
    }
    else
    {
        pPShader->SetInterfaceDescriptor(pInterfaceDesc);
    }

    DescriptorItem* pDescItem = SE_NEW DescriptorItem;
    pInterfaceDesc->AttachItem(pDescItem);
    pDescItem->IsArray = true;
    pDescItem->SetInstanceName("LightArray");
    for( int i = 0; i < iLCount; i++ )
    {
        iLightType = (int)pLEffect->GetLight(i)->Type;
        pDescItem->AttachTypeName(aLightTypes[iLightType]);
    }
}
//----------------------------------------------------------------------------