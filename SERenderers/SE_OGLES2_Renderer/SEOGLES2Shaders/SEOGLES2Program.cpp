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

#include "SEOGLES2RendererPCH.h"
#include "SEOGLES2Resources.h"
#include "SEOGLES2Program.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(SEOGLES2Program);

//SE_REGISTER_INITIALIZE(SEOGLES2Program);

const std::string SEOGLES2Program::ms_PositionStr("SE_ModelPosition");
const std::string SEOGLES2Program::ms_NormalStr("SE_ModelNormal");
const std::string SEOGLES2Program::ms_ColorStr("SE_Color");
const std::string SEOGLES2Program::ms_Color0Str("SE_Color0");
const std::string SEOGLES2Program::ms_Color1Str("SE_Color1");
const std::string SEOGLES2Program::ms_TexCoordStr("SE_TexCoord");

//----------------------------------------------------------------------------
void SEOGLES2Program::Initialize()
{
    SEProgram::OnLoadProgram = &SEOGLES2Program::OnLoadProgram;
    SEProgram::OnReleaseUserData = &SEOGLES2Program::OnReleaseUserData;
    SELightingEffect::OnConfigureLighting = 
        &SEOGLES2Program::OnConfigureLighting;
}
//----------------------------------------------------------------------------
SEOGLES2Program::SEOGLES2Program()
{
}
//----------------------------------------------------------------------------
bool SEOGLES2Program::OnLoadProgram(SERenderer* pRenderer, 
    const std::string& rProgramName, SEProgram* pProgram, 
    SEProgram::ProgramType eType, SEInterfaceDescriptor*)
{
    if( !pRenderer || !pProgram )
    {
        SE_ASSERT( false );
        return false;
    }

    // 获取file name和entry name.
	size_t uiLen = strlen(rProgramName.c_str()) + 1;
    char* acProgramName = SE_NEW char[uiLen];
	SESystem::SE_Strcpy(acProgramName, uiLen, rProgramName.c_str());
    char* pNextToken;
    char* acFileName = SESystem::SE_Strtok(acProgramName, ".", pNextToken);
    char* acEntryName = SESystem::SE_Strtok(0, ".", pNextToken);
    if( !acFileName || !acEntryName )
    {
        // 获取file name和entry name失败.
        SE_DELETE[] acProgramName;
        return false;
    }

    std::string tempType;
    GLenum eShaderType;
    if( eType == SEProgram::PT_VERTEX )
    {
        tempType = ".vs";
        eShaderType = GL_VERTEX_SHADER;
    }
    else if( eType == SEProgram::PT_PIXEL )
    {
        tempType = ".ps";
        eShaderType = GL_FRAGMENT_SHADER;
    }
    else
    {
        // OpenGL ES2 only support for vs/ps programs.
        SE_DELETE[] acProgramName;
        return false;
    }

    std::string tempFileName = std::string(acFileName) + tempType + 
        std::string(".essl");
    const char* acDecorated = SESystem::SE_GetPath(tempFileName.c_str(), 
        SESystem::SM_READ);
    SE_DELETE[] acProgramName;
    acProgramName = 0;

    if( !acDecorated )
    {
        // 没有找到指定ESSL文件.
        return false;
    }

    // 为了在代理类的静态函数中访问基类的保护成员,我们必须转换指针类型,
    // 由于我们能确保只访问基类成员,因此这样做是安全的.
    SEOGLES2Program* pOGLES2Program = (SEOGLES2Program*)pProgram;
    SEProgram::ProgramType& rProgramType = pOGLES2Program->m_eProgramType;
    pProgram->UserData = SE_NEW SEProgramData;
    unsigned int& ruiID = ((SEProgramData*)pProgram->UserData)->ID;

    rProgramType = eType;
    ruiID = 0;
    ((SEProgramData*)pProgram->UserData)->Owner = 0;

    SEOGLES2Renderer* pOGLES2Renderer = (SEOGLES2Renderer*)pRenderer;
    if( pOGLES2Renderer->HasShaderCompiler() )
    {
        std::ifstream tempIStr(acDecorated);
        if( !tempIStr )
        {
            return false;
        }

        std::string tempProgramText, tempLine;
        std::string tempEOL = "\n";
        while( !tempIStr.eof() )
        {
#if defined(SE_USING_VC6) || defined(SE_USING_VC70)
            const int iBufferSize = 1024;
            char acBuffer[iBufferSize];
            tempIStr.getline(acBuffer, iBufferSize);
            tempLine = std::string(acBuffer);
#else
            getline(tempIStr, tempLine);

            // Depending on the platform that *.essl files are compiled on, 
            // the newline may consist of a line feed '\n' (10), a carriage 
            // return '\r' (13), or a carriage return followed by a line feed.
            if( tempLine.length() > 0 )
            {
                if( 10 == (int)tempLine[tempLine.length()-1] )
                {
                    if( tempLine.length() > 1 && 13 == 
                        (int)tempLine[tempLine.length()-2] )
                    {
                        tempLine.resize(tempLine.length()-2);
                    }
                    else
                    {
                        tempLine.resize(tempLine.length()-1);
                    }
                }
                else if( 13 == (int)tempLine[tempLine.length()-1] )
                {
                    tempLine.resize(tempLine.length()-1);
                }
            }
#endif
            tempProgramText += tempLine + tempEOL;
        }

        const char* acProgramText = tempProgramText.c_str();

        // Create the shader object.
        ruiID = glCreateShader(eShaderType);
        SE_ASSERT( ruiID != 0 );

        // Load the shader source.
        glShaderSource(ruiID, 1, &acProgramText, 0);
   
        // Compile the shader.
        glCompileShader(ruiID);

        // Check the compile status.
        GLint iCompiled;
        glGetShaderiv(ruiID, GL_COMPILE_STATUS, &iCompiled);
        if( !iCompiled ) 
        {
            GLint iInfoLen = 0;
            glGetShaderiv(ruiID, GL_INFO_LOG_LENGTH, &iInfoLen);
            if( iInfoLen > 1 )
            {
                char* acInfoLog = SE_NEW char[iInfoLen];
                glGetShaderInfoLog(ruiID, iInfoLen, 0, acInfoLog); 
                SE_ASSERT( false );
                SE_DELETE[] acInfoLog;
            }

            glDeleteShader(ruiID);
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SEOGLES2Program::ParseLinkedProgram(unsigned int uiProgram, 
    SEProgram* pVProgram, SEProgram* pPProgram)
{
    // 为了在代理类的静态函数中访问基类的保护成员,我们必须转换指针类型,
    // 由于我们能确保只访问基类成员,因此这样做是安全的.
    SEOGLES2Program* pOGLES2VProgram = (SEOGLES2Program*)pVProgram;
    SEOGLES2Program* pOGLES2PProgram = (SEOGLES2Program*)pPProgram;
    SEAttributes& rIAttributes = pOGLES2VProgram->m_InputAttributes;
    SEProgramData* pVProgramData = (SEProgramData*)pOGLES2VProgram->UserData;
    std::vector<SERendererConstant>& rRCs = 
        pOGLES2VProgram->m_RendererConstants;
    std::vector<SEUserConstant>& rVUCs = pOGLES2VProgram->m_UserConstants;
    std::vector<SEUserConstant>& rPUCs = pOGLES2PProgram->m_UserConstants;
    std::vector<SESamplerInformation>& rVSIs = 
        pOGLES2VProgram->m_SamplerInformation;
    std::vector<SESamplerInformation>& rPSIs = 
        pOGLES2PProgram->m_SamplerInformation;

    GLint iCount, iMaxLen;
    char* acName = 0;

    // Parse attributes.
    glGetProgramiv(uiProgram, GL_ACTIVE_ATTRIBUTES, &iCount);
    glGetProgramiv(uiProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &iMaxLen);
    if( iMaxLen > 0 )
    {
        acName = SE_NEW char[iMaxLen];

        for( int i = 0; i < iCount; i++ )
        {
            GLint iSize;
            GLenum eType;
            int iNumFloats, iUnit;

            // Get attribute info.
            glGetActiveAttrib(uiProgram, i, iMaxLen, 0, &iSize, &eType,
                acName);

            // Get attribute location, this will be used as a binding id.
            GLint iAttribID = glGetAttribLocation(uiProgram, acName);
            SE_ASSERT( iAttribID > -1 );

            iNumFloats = 0;
            switch( eType )
            {
            case GL_FLOAT:
                iNumFloats = 1;
                break;
            case GL_FLOAT_VEC2:
                iNumFloats = 2;
                break;
            case GL_FLOAT_VEC3:
                iNumFloats = 3;
                break;
            case GL_FLOAT_VEC4:
                iNumFloats = 4;
                break;
            default:
                SE_ASSERT( false );
                break;
            }

            std::string tempName = acName;
            if( tempName == SEOGLES2Program::ms_PositionStr )
            {
                // 只支持(x,y,z) position.
                rIAttributes.SetPositionChannels(3);
                pVProgramData->SetPositionAttribID((unsigned int)iAttribID);
            }
            else if( tempName == SEOGLES2Program::ms_NormalStr )
            {
                // 只支持(x,y,z) normals.
                rIAttributes.SetNormalChannels(3);
                pVProgramData->SetNormalAttribID((unsigned int)iAttribID);
            }
            else if( tempName == SEOGLES2Program::ms_ColorStr
                || tempName == SEOGLES2Program::ms_Color0Str )
            {
                rIAttributes.SetColorChannels(0, iNumFloats);
                pVProgramData->SetColorAttribID(0, (unsigned int)iAttribID);
            }
            else if( tempName == SEOGLES2Program::ms_Color1Str )
            {
                rIAttributes.SetColorChannels(1, iNumFloats);
                pVProgramData->SetColorAttribID(1, (unsigned int)iAttribID);
            }
            else if( tempName.substr(0, 11) == SEOGLES2Program::ms_TexCoordStr )
            {
                iUnit = (int)tempName[11] - '0';
                rIAttributes.SetTCoordChannels(iUnit, iNumFloats);
                pVProgramData->SetTCoordAttribID(iUnit, 
                    (unsigned int)iAttribID);
            }
            else
            {
                // 用户没有按照引擎规定方式命名attribute.
                SE_ASSERT( false );
            }
        }

        SE_DELETE acName;
    }

    // Parse uniforms.
    glGetProgramiv(uiProgram, GL_ACTIVE_UNIFORMS, &iCount);
    glGetProgramiv(uiProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &iMaxLen);
    if( iMaxLen > 0 )
    {
        acName = SE_NEW char[iMaxLen];

        for( int i = 0; i < iCount; i++ )
        {
            GLint iSize;
            GLenum eType;
            GLint iLoc;
            int iNumFloats;
            SESamplerInformation::Type eSType;
            SERendererConstant::Type eRCType;
            std::string tempName;

            // Get the uniform info.
            glGetActiveUniform(uiProgram, i, iMaxLen, 0, &iSize, &eType,
                acName);

            iNumFloats = 0;
            eSType = SESamplerInformation::MAX_SAMPLER_TYPES;
            switch( eType )
            {
            case GL_FLOAT:
                iNumFloats = 1;
                break;
            case GL_FLOAT_VEC2:
                iNumFloats = 2;
                break;
            case GL_FLOAT_VEC3:
                iNumFloats = 3;
                break;
            case GL_FLOAT_VEC4:
                iNumFloats = 4;
                break;
            case GL_FLOAT_MAT4:
                iNumFloats = 16;
                break;
            case GL_SAMPLER_2D:
                eSType = SESamplerInformation::SAMPLER_2D;
                break;
            case GL_SAMPLER_CUBE:
                eSType = SESamplerInformation::SAMPLER_CUBE;
                break;
            default:
                // 引擎尚未支持的变量数据类型.
                SE_ASSERT( false );
                break;
            }

            tempName = acName;
            iLoc = glGetUniformLocation(uiProgram, acName);

            // 获取采样器信息(如果当前uniform是采样器声明).
            if( eSType != SESamplerInformation::MAX_SAMPLER_TYPES )
            {
                SESamplerInformationID* pSIID = SE_NEW SESamplerInformationID;
                pSIID->ID = iLoc;
                SESamplerInformation tempSU(tempName.c_str(), eSType, 
                (void*)pSIID);

                if( tempName.substr(0, 2) == "v_" )
                {
                    rVSIs.push_back(tempSU);
                }
                else
                {
                    rPSIs.push_back(tempSU);
                }

                continue;
            }

            // 变量必定是一个renderer constant或者user-defined constant.
            eRCType = SERendererConstant::GetType(tempName.c_str());
            if( eRCType != SERendererConstant::MAX_TYPES )
            {
                // renderer constant.
                SERendererConstantID* pRCID = SE_NEW SERendererConstantID;
                pRCID->ID = iLoc;
                SERendererConstant tempRC(eRCType, (void*)pRCID, 
                    iNumFloats);
                rRCs.push_back(tempRC);
            }
            else
            {
                // user-defined constant.
                SEUserConstantID* pUCID = SE_NEW SEUserConstantID;
                pUCID->ID = iLoc;
                SEUserConstant tempUC(tempName.c_str(), (void*)pUCID, 
                    iNumFloats);

                if( tempName.substr(0, 2) == "p_" )
                {
                    rPUCs.push_back(tempUC);
                }
                else
                {
                    // 其他命名方式的user-defined constant都加入到VProgram中.
                    rVUCs.push_back(tempUC);
                }
            }
        }

        SE_DELETE acName;
    }
}
//----------------------------------------------------------------------------
void SEOGLES2Program::OnReleaseUserData(void* pUserData)
{
    SEProgramData* pData = (SEProgramData*)pUserData;

    SE_DELETE pData;
}
//----------------------------------------------------------------------------
void SEOGLES2Program::OnConfigureLighting(SELightingEffect* pLEffect)
{
    SEVertexShader* pVShader;
    SEPixelShader* pPShader;

    int iLCount = pLEffect->GetLightCount();
    SELightingEffect::LightingMode eMode = pLEffect->GetLightingMode();

    if( iLCount == 0 )
    {
        // 待实现.
        // 实现这两个ESSL shader.
        pVShader = SE_NEW SEVertexShader("Material.main");
        pPShader = SE_NEW SEPixelShader("Material.main");
        pLEffect->SetVShader(0, pVShader);
        pLEffect->SetPShader(0, pPShader);
    }
    else
    {
        if( eMode == SELightingEffect::LM_VERTEX )
        {
            pVShader = SE_NEW SEVertexShader("VertexLighting.main");
            pPShader = SE_NEW SEPixelShader(
                "VertexLighting.main");
            pLEffect->SetVShader(0, pVShader);
            pLEffect->SetPShader(0, pPShader);
        }
        else if( eMode == SELightingEffect::LM_PIXEL )
        {
            pVShader = SE_NEW SEVertexShader(
                "PixelLighting.main");
            pPShader = SE_NEW SEPixelShader("PixelLighting.main");
            pLEffect->SetVShader(0, pVShader);
            pLEffect->SetPShader(0, pPShader);
        }
        else
        {
            SE_ASSERT( false );
        }
    }
}
//----------------------------------------------------------------------------