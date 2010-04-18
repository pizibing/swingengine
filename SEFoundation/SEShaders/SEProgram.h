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

#ifndef Swing_Program_H
#define Swing_Program_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEAttributes.h"
#include "SEBindable.h"
#include "SERendererConstant.h"
#include "SEUserConstant.h"
#include "SESamplerInformation.h"
#include "SERenderer.h"
#include "SEInterfaceDescriptor.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080623
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEProgram : public SEObject, public SEBindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类.
    virtual ~SEProgram(void);

    enum ProgramType
    {
        PT_VERTEX,
        PT_PIXEL,
        PT_GEOMETRY,
        PT_COUNT
    };
    inline ProgramType GetProgramType(void) const;

    inline const SEAttributes& GetInputAttributes(void) const;
    inline const SEAttributes& GetOutputAttributes(void) const;

    // 访问renderer constants.
    inline int GetRCCount(void) const;
    SERendererConstant* GetRC(int i);
    SERendererConstant* GetRC(SERendererConstant::Type eType);

    // 访问user constants.
    inline int GetUCCount(void) const;
    SEUserConstant* GetUC(int i);
    SEUserConstant* GetUC(const std::string& rName);

    // 访问samplers.
    inline int GetSICount(void) const;
    SESamplerInformation* GetSI(int i);
    SESamplerInformation* GetSI(const std::string& rName);

    // 用户必须实现这个代理函数,用于创建一个shader program对象并填充其数据.
    typedef bool (*LoadProgram)(SERenderer*, const std::string&, SEProgram*, 
        ProgramType, SEInterfaceDescriptor*);

    // 用户必须实现这个代理函数,用于释放shader program自定义数据.
    typedef void (*ReleaseUserData)(void*);

    // 用户必须为这些静态函数指针赋值,使其能够完成用户所希望的自定义行为.
    static LoadProgram OnLoadProgram;
    static ReleaseUserData OnReleaseUserData;

    // 用户必须定义并填充这个自定义数据.
    // 主要用于储存program针对具体平台API的handle及其他相关数据.
    void* UserData;

protected:
    static bool Load(SERenderer* pRenderer, const std::string& rProgramName,
        SEProgram* pProgram, ProgramType eType, 
        SEInterfaceDescriptor* pInterfaceDesc);

    SEProgram(void);

    ProgramType m_eProgramType;

    // shader程序的输入输出数据格式.
    SEAttributes m_InputAttributes;
    SEAttributes m_OutputAttributes;

    // 该程序所需的渲染器常量.
    std::vector<SERendererConstant> m_RendererConstants;

    // 该程序所需的用户定义常量,
    // 用户定义常量由应用程序自由设置.
    std::vector<SEUserConstant> m_UserConstants;

    // 该程序所需的采样器单元信息.
    std::vector<SESamplerInformation> m_SamplerInformation;

    // parsing shader程序时使用.
    static const std::string ms_PositionStr;
    static const std::string ms_Position0Str;
    static const std::string ms_NormalStr;
    static const std::string ms_Normal0Str;
    static const std::string ms_ColorStr;
    static const std::string ms_Color0Str;
    static const std::string ms_Color1Str;
    static const std::string ms_Color2Str;
    static const std::string ms_Color3Str;
    static const std::string ms_TexCoordStr;
};

typedef SESmartPointer<SEProgram> SEProgramPtr;

#include "SEProgram.inl"

}

#endif
