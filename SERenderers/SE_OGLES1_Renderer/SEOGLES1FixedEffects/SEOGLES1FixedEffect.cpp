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
#include "SEOGLES1FixedEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEOGLES1FixedEffect, SEEffect);
SE_IMPLEMENT_STREAM(SEOGLES1FixedEffect);

//SE_REGISTER_STREAM(SEOGLES1FixedEffect);

//----------------------------------------------------------------------------
SEOGLES1FixedEffect::SEOGLES1FixedEffect()
{
}
//----------------------------------------------------------------------------
SEOGLES1FixedEffect::SEOGLES1FixedEffect(int iTextureCount, int iLightCount)
{
    SE_ASSERT( iTextureCount >= 0 && iLightCount >= 0 );

    m_ImageNames.resize(iTextureCount);
    m_Textures.resize(iTextureCount);
    m_Lights.resize(iLightCount);
}
//----------------------------------------------------------------------------
SEOGLES1FixedEffect::~SEOGLES1FixedEffect()
{
}
//----------------------------------------------------------------------------
int SEOGLES1FixedEffect::GetTextureCount() const
{
    return (int)m_Textures.size();
}
//----------------------------------------------------------------------------
SETexture* SEOGLES1FixedEffect::GetTexture(int i)
{
    if( 0 <= i && i < (int)m_Textures.size() )
    {
        return m_Textures[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
const SETexture* SEOGLES1FixedEffect::GetTexture(int i) const
{
    if( 0 <= i && i < (int)m_Textures.size() )
    {
        return m_Textures[i];
    }
	
    return 0;
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::SetTexture(int i, SETexture* pTexture)
{
    SE_ASSERT( 0 <= i && i < (int)m_Textures.size() );

    m_Textures[i] = pTexture;
}
//----------------------------------------------------------------------------
const std::string& SEOGLES1FixedEffect::GetImageName(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_ImageNames.size() );

    return m_ImageNames[i];
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::SetImageName(int i, const std::string& rName)
{
    SE_ASSERT( 0 <= i && i < (int)m_ImageNames.size() );

    m_ImageNames[i] = rName;
}
//----------------------------------------------------------------------------
int SEOGLES1FixedEffect::GetLightCount() const
{
    return (int)m_Lights.size();
}
//----------------------------------------------------------------------------
SELight* SEOGLES1FixedEffect::GetLight(int i)
{
    if( 0 <= i && i < (int)m_Lights.size() )
    {
        return m_Lights[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
const SELight* SEOGLES1FixedEffect::GetLight(int i) const
{
    if( 0 <= i && i < (int)m_Lights.size() )
    {
        return m_Lights[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::SetLight(int i, SELight* pLight)
{
    SE_ASSERT( 0 <= i && i < (int)m_Lights.size() );

    m_Lights[i] = pLight;
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::LoadResources(SERenderer*, SEGeometry*)
{
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::ReleaseResources(SERenderer*, SEGeometry*)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SEOGLES1FixedEffect::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SEEffect::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    int i;
    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] )
        {
            pFound = m_Textures[i]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    for( i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( m_Lights[i] )
        {
            pFound = m_Lights[i]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SEEffect::GetAllObjectsByName(rName, rObjects);
}
//----------------------------------------------------------------------------
SEObject* SEOGLES1FixedEffect::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SEEffect::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    int i;
    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] )
        {
            pFound = m_Textures[i]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    for( i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( m_Lights[i] )
        {
            pFound = m_Lights[i]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEEffect::Load(rStream, pLink);

    // native data
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
        SEObject* pObject;
        rStream.Read(pObject);  // m_Textures[i]
        pLink->Add(pObject);
    }

    rStream.Read(iCount);
    m_Lights.resize(iCount);
    for( i = 0; i < iCount; i++ )
    {
        SEObject* pObject;
        rStream.Read(pObject);  // m_Lights[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SEOGLES1FixedEffect);
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEEffect::SELink(rStream, pLink);

    int i;
    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        m_Textures[i] = (SETexture*)rStream.GetFromMap(pLinkID);
    }

    for( i = 0; i < (int)m_Lights.size(); i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        m_Lights[i] = (SELight*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SEOGLES1FixedEffect::Register(SEStream& rStream) const
{
    if( !SEEffect::Register(rStream) )
    {
        return false;
    }

    int i;
    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] )
        {
            m_Textures[i]->Register(rStream);
        }
    }

    for( i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( m_Lights[i] )
        {
            m_Lights[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SEOGLES1FixedEffect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEEffect::Save(rStream);

    // native data
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

    iCount = (int)m_Lights.size();
    rStream.Write(iCount);
    for( i = 0; i < iCount; i++ )
    {
        rStream.Write(m_Lights[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SEOGLES1FixedEffect);
}
//----------------------------------------------------------------------------
int SEOGLES1FixedEffect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEEffect::GetDiskUsed(rVersion);

    int iCount = (int)m_ImageNames.size();
    iSize += sizeof(int);
    int i;
    for( i = 0; i < iCount; i++ )
    {
        iSize += sizeof(int) + (int)m_ImageNames[i].length();
    }

    iCount = (int)m_Textures.size();
    iSize += sizeof(int) + iCount*sizeof(m_Textures[0]);

    iCount = (int)m_Lights.size();
    iSize += sizeof(int) + iCount*sizeof(m_Lights[0]);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEOGLES1FixedEffect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    int i;
    for( i = 0; i < (int)m_ImageNames.size(); i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "image[%d] =", i);
        pTree->Append(Format(acTitle, m_ImageNames[i].c_str()));
    }

    // children
    pTree->Append(SEEffect::SaveStrings());

    for( i = 0; i < (int)m_Textures.size(); i++ )
    {
        if( m_Textures[i] )
        {
            pTree->Append(m_Textures[i]->SaveStrings());
        }
    }

    for( i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( m_Lights[i] )
        {
            pTree->Append(m_Lights[i]->SaveStrings());
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
