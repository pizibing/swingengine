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
inline bool SETransformation::IsIdentity() const
{
    return m_bIsIdentity;
}
//----------------------------------------------------------------------------
inline bool SETransformation::IsSRMatrix() const
{
    return m_bIsSRMatrix;
}
//----------------------------------------------------------------------------
inline bool SETransformation::IsUniformScale() const
{
    return m_bIsSRMatrix && m_bIsUniformScale;
}
//----------------------------------------------------------------------------
inline const SEMatrix3f& SETransformation::GetRotate() const
{
    SE_ASSERT( m_bIsSRMatrix );

    return m_Matrix;
}
//----------------------------------------------------------------------------
inline const SEMatrix3f& SETransformation::GetMatrix() const
{
    return m_Matrix;
}
//----------------------------------------------------------------------------
inline const SEVector3f& SETransformation::GetTranslate() const
{
    return m_Translate;
}
//----------------------------------------------------------------------------
inline const SEVector3f& SETransformation::GetScale() const
{
    SE_ASSERT( m_bIsSRMatrix );

    return m_Scale;
}
//----------------------------------------------------------------------------
inline float SETransformation::GetUniformScale() const
{
    SE_ASSERT( m_bIsSRMatrix && m_bIsUniformScale );

	return m_Scale.X;
}
//----------------------------------------------------------------------------



