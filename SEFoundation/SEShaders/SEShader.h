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
#include "SEString.h"
#include "SEInterfaceDescriptor.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:shader类
// 说明:管理shader程序及渲染所需资源
// 作者:Sun Che
// 时间:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Shader : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类
    virtual ~Shader(void);

    inline const String& GetShaderName(void) const;

    // 访问textures和image names
    void SetTextureCount(int iCount);
    inline int GetTextureCount(void) const;
    Texture* GetTexture(int i);
    Texture* GetTexture(const String& rName);
    const Texture* GetTexture(int i) const;
    const Texture* GetTexture(const String& rName) const;
    void SetTexture(int i, Texture* pTexture);  // 用于纹理资源共享
    void SetImageName(int i, const String& rName);
    const String& GetImageName(int i) const;

    // 访问interface descriptor.
    inline void SetInterfaceDescriptor(InterfaceDescriptor* pDescriptor);
    inline InterfaceDescriptor* GetInterfaceDescriptor(void) const;

protected:
    // Support for streaming.
    Shader(void);

    // 构造函数由派生类调用
    Shader(const String& rShaderName);

protected:
    // shader名字是shader程序的唯一标识
    String m_ShaderName;

    // shader程序,依赖于具体图形API(DirectX,OpenGL)
    ProgramPtr m_spProgram;

    // shader程序所需interfaces.
    InterfaceDescriptorPtr m_spInterfaces;

    // 每一个shader程序实例都可以有自己的user-defined变量数据,
    // program对象只解析出并保存着这些变量的名字,寄存器编号,寄存器数量,
    // 这里提供的存储空间是为了给shader派生类提供方便,
    // 当然,shader派生类完全可以通过UserConstant::SetDataSource函数,
    // 另给user-defined变量指定数据存储位置
    std::vector<float> m_UserData;

    // 该shader程序实例所使用的image名字,
    // 这些texture对象存储着实际的images和samplers
    std::vector<String> m_ImageNames;
    std::vector<TexturePtr> m_Textures;

// 内部使用
public:
    void OnLoadProgram(Program* pProgram);
    void OnReleaseProgram(void);
};

typedef SmartPointer<Shader> ShaderPtr;

#include "SEShader.inl"

}

#endif
