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

#include "SEMax8Materials.h"
#include "max.h"

using namespace std;

//----------------------------------------------------------------------------
Max8Materials::Max8Materials()
{
}
//----------------------------------------------------------------------------
bool Max8Materials::Add(Mtl* pMtl)
{
    if( pMtl == NULL ) 
        return false;

    for( int i = 0; i < (int)m_Materials.size(); i++ )
    {
        if( m_Materials[i] == pMtl )
            return false;
    }
    
    m_Materials.push_back(pMtl);

    return true;
}
//----------------------------------------------------------------------------
void Max8Materials::SetCount(int iCount)
{
    m_Materials.resize(iCount);
}
//----------------------------------------------------------------------------
int Max8Materials::GetCount() const
{
    return (int)m_Materials.size();
}
//----------------------------------------------------------------------------
Mtl* Max8Materials::Get(int iMtlID) const
{
    if( 0 <= iMtlID && iMtlID < (int)m_Materials.size() )
        return m_Materials[iMtlID];

    return NULL;
}
//----------------------------------------------------------------------------
int Max8Materials::GetID(Mtl* pMtl) const
{
    for( int i = 0; i < (int)m_Materials.size(); i++ )
    {
        if( m_Materials[i] == pMtl )
            return i;
    }

    return -1;
}
//----------------------------------------------------------------------------



