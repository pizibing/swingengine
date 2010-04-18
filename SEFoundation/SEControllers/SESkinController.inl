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

//----------------------------------------------------------------------------
inline int SESkinController::GetVertexCount() const
{
    return m_iVertexCount;
}
//----------------------------------------------------------------------------
inline int SESkinController::GetBoneCount() const
{
    return m_iBoneCount;
}
//----------------------------------------------------------------------------
inline SENode* SESkinController::GetBone(int iBone) const
{
    SE_ASSERT( 0 <= iBone && iBone < m_iBoneCount );

    return m_apBones[iBone];
}
//----------------------------------------------------------------------------
inline float& SESkinController::Weight(int iVertex, int iBone)
{
    SE_ASSERT( 0 <= iVertex && iVertex < m_iVertexCount );
    SE_ASSERT( 0 <= iBone && iBone < m_iBoneCount );

    return m_aafWeight[iVertex][iBone];
}
//----------------------------------------------------------------------------
inline SEVector3f& SESkinController::Offset(int iVertex, int iBone)
{
    SE_ASSERT( 0 <= iVertex && iVertex < m_iVertexCount );
    SE_ASSERT( 0 <= iBone && iBone < m_iBoneCount );

    return m_aaOffset[iVertex][iBone];
}
//----------------------------------------------------------------------------
