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

#ifndef Swing_Shader_H
#define Swing_Shader_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEProgram.h"
#include "SETexture.h"
#include "SEInterfaceDescriptor.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:管理shader程序及渲染所需资源
// Author:Sun Che
// Date:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEShader : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类
    virtual ~SEShader(void);

    inline const std::string& GetShaderName(void) const;

    // 访问textures和image names
    void SetTextureCount(int iCount);
    inline int GetTextureCount(void) const;
    SETexture* GetTexture(int i);
    SETexture* GetTexture(const std::string& rName);
    const SETexture* GetTexture(int i) const;
    const SETexture* GetTexture(const std::string& rName) const;
    void SetTexture(int i, SETexture* pTexture);  // 用于纹理资源共享
    void SetImageName(int i, const std::string& rName);
    const std::string& GetImageName(int i) const;

    // 访问interface descriptor.
    inline void SetInterfaceDescriptor(SEInterfaceDescriptor* pDescriptor);
    inline SEInterfaceDescriptor* GetInterfaceDescriptor(void) const;

protected:
    // Support for streaming.
    SEShader(void);

    // 构造函数由派生类调用
    SEShader(const std::string& rShaderName);

protected:
    // shader名字是shader程序的唯一标识
    std::string m_ShaderName;

    // shader程序,依赖于具体图形API(DirectX,OpenGL)
    SEProgramPtr m_spProgram;

    // shader程序所需interfaces.
    SEInterfaceDescriptorPtr m_spInterfaces;

    // 每一个shader程序实例都可以有自己的user-defined变量数据,
    // program对象只解析出并保存着这些变量的名字,寄存器编号,寄存器数量,
    // 这里提供的存储空间是为了给shader派生类提供方便,
    // 当然,shader派生类完全可以通过SEUserConstant::SetDataSource函数,
    // 另给user-defined变量指定数据存储位置
    std::vector<float> m_UserData;

    // 该shader程序实例所使用的image名字,
    // 这些texture对象存储着实际的images和samplers
    std::vector<std::string> m_ImageNames;
    std::vector<SETexturePtr> m_Textures;

// 内部使用
public:
    void OnLoadProgram(SEProgram* pProgram);
    void OnReleaseProgram(void);
};

typedef SESmartPointer<SEShader> SEShaderPtr;

#include "SEShader.inl"

}

#endif
