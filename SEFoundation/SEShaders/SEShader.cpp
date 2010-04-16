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

#include "SEFoundationPCH.h"
#include "SEShader.h"
#include "SEImageCatalog.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Shader, Object);
SE_IMPLEMENT_ABSTRACT_STREAM(Shader);
SE_IMPLEMENT_DEFAULT_NAME_ID(Shader, Object);

//SE_REGISTER_STREAM(Shader);

//----------------------------------------------------------------------------
Shader::Shader()
{
}
//----------------------------------------------------------------------------
Shader::Shader(const std::string& rShaderName)
    :
    m_ShaderName(rShaderName)
{
}
//----------------------------------------------------------------------------
Shader::~Shader()
{
}
//----------------------------------------------------------------------------
void Shader::SetTextureCount(int iCount)
{
    m_Textures.clear();
    m_Textures.resize(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        m_Textures[i] = SE_NEW Texture;
    }

    m_ImageNames.clear();
    m_ImageNames.resize(iCount);
}
//----------------------------------------------------------------------------
Texture* Shader::GetTexture(int i)
{
    if( 0 <= i && i < (int)m_Textures.size() )
    {
        return m_Textures[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
Texture* Shader::GetTexture(const std::string& rName)
{
    for( int i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] && m_Textures[i]->GetName() == rName )
        {
            return m_Textures[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
const Texture* Shader::GetTexture(int i) const
{
    if( 0 <= i && i < (int)m_Textures.size() )
    {
        return m_Textures[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
const Texture* Shader::GetTexture(const std::string& rName) const
{
    for( int i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] && m_Textures[i]->GetName() == rName )
        {
            return m_Textures[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Shader::SetTexture(int i, Texture* pTexture)
{
    if( 0 <= i && i < (int)m_Textures.size() )
    {
        m_Textures[i] = pTexture;
    }
    else if( i >= (int)m_Textures.size() )
    {
        m_Textures.resize(i + 1);
        m_Textures[i] = pTexture;
    }
}
//----------------------------------------------------------------------------
void Shader::SetImageName(int i, const std::string& rName)
{
    int iCount = (int)m_ImageNames.size();
    if( i >= iCount )
    {
        m_ImageNames.resize(i+1);
    }

    m_ImageNames[i] = rName;
}
//----------------------------------------------------------------------------
const std::string& Shader::GetImageName(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_ImageNames.size() );

    return m_ImageNames[i];
}
//----------------------------------------------------------------------------
void Shader::OnLoadProgram(Program* pProgram)
{
    SE_ASSERT( !m_spProgram && pProgram );

    m_spProgram = pProgram;

    // 为该程序的所有texture装载各自所需的image,
    // 首先从image资源目录中查找,找不到则试图从磁盘装载,
    // 指定image不存在时,使用默认image.
    int iSICount = m_spProgram->GetSICount();
    m_ImageNames.resize(iSICount);
    m_Textures.resize(iSICount);
    for( int i = 0; i < iSICount; i++ )
    {
        // 之前必须已经通过SetImageName函数设置过image名字.
        Image* pImage = ImageCatalog::GetActive()->Find(m_ImageNames[i]);

        SE_ASSERT( pImage );

        if( !m_Textures[i] )
        {
            m_Textures[i] = SE_NEW Texture(pImage);
        }
        else
        {
            m_Textures[i]->SetImage(pImage);
        }
    }
}
//----------------------------------------------------------------------------
void Shader::OnReleaseProgram()
{
    // 这里只释放shader程序.
    // 稍后shader自身析构时,如果texture image存在,则将会自动释放,
    // shader析构时对texture对象减引用,如果是最后一个引用,
    // 则texture被释放,texture对image减引用,如果是最后一个引用,
    // 则image被从image资源目录中自动删除
    m_spProgram = 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Shader::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // native data
    rStream.Read(m_ShaderName);

    Object* pObject;
    rStream.Read(pObject);  // m_spInterfaces
    pLink->Add(pObject);

    int iCount;
    rStream.Read(iCount);
    m_ImageNames.resize(iCount);
    int i;
    for( i = 0; i < iCount; i++ )
    {
        rStream.Read(m_ImageNames[i]);
    }

    // link data
    rStream.Read(iCount);
    m_Textures.resize(iCount);
    for( i = 0; i < iCount; i++ )
    {
        rStream.Read(pObject);  // m_Textures[i]
        pLink->Add(pObject);
    }

    // The data members m_spProgram and m_UserData are both set during
    // resource loading at program runtime.

    SE_END_DEBUG_STREAM_LOAD(Shader);
}
//----------------------------------------------------------------------------
void Shader::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    m_spInterfaces = (InterfaceDescriptor*)rStream.GetFromMap(pLinkID);

    for( int i = 0; i < (int)m_Textures.size(); i++ )
    {
        pLinkID = pLink->GetLinkID();
        m_Textures[i] = (Texture*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool Shader::Register(Stream& rStream) const
{
    if( !Object::Register(rStream) )
    {
        return false;
    }

    if( m_spInterfaces )
    {
        m_spInterfaces->Register(rStream);
    }

    for( int i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] )
        {
            m_Textures[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void Shader::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // native data
    rStream.Write(m_ShaderName);

    rStream.Write(m_spInterfaces);

    int iCount = (int)m_ImageNames.size();
    rStream.Write(iCount);
    int i;
    for( i = 0; i < iCount; i++ )
    {
        rStream.Write(m_ImageNames[i]);
    }

    // link data
    iCount = (int)m_Textures.size();
    rStream.Write(iCount);
    for( i = 0; i < iCount; i++ )
    {
        rStream.Write(m_Textures[i]);
    }

    // The data members m_spProgram and m_UserData are both set during
    // resource loading at program runtime.

    SE_END_DEBUG_STREAM_SAVE(Shader);
}
//----------------------------------------------------------------------------
int Shader::GetDiskUsed(const StreamVersion& rVersion) const
{
    int iSize = Object::GetDiskUsed(rVersion) +
        sizeof(int) + (int)m_ShaderName.length() + sizeof(m_spInterfaces);

    int iCount = (int)m_ImageNames.size();
    iSize += sizeof(int);
    int i;
    for( i = 0; i < iCount; i++ )
    {
        iSize += sizeof(int) + (int)m_ImageNames[i].length();
    }

    iCount = (int)m_Textures.size();
    iSize += sizeof(int) + iCount*sizeof(m_Textures[0]);

    return iSize;
}
//----------------------------------------------------------------------------
StringTree* Shader::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("shader name =", m_ShaderName.c_str()));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    int i;
    for( i = 0; i < (int)m_ImageNames.size(); i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "image[%d] =", i);
        pTree->Append(Format(acTitle, m_ImageNames[i].c_str()));
    }

    // children
    pTree->Append(Object::SaveStrings());

    if( m_spProgram )
    {
        pTree->Append(m_spProgram->SaveStrings());
    }

    if( m_spInterfaces )
    {
        pTree->Append(m_spInterfaces->SaveStrings());
    }

    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        pTree->Append(m_Textures[i]->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
