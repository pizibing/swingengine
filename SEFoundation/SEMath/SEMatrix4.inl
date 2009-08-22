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
// 单精度4阶方阵类
//----------------------------------------------------------------------------
inline int Matrix4f::CompareData(const Matrix4f& rMat) const
{
    return memcmp(m_fData, rMat.m_fData, 16 * sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix4f::Zero()
{
    memset(m_fData, 0, 16*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix4f::Identity()
{
    M11 = 1.0f;
    M12 = 0.0f;
    M13 = 0.0f;
    M14 = 0.0f;

    M21 = 0.0f;
    M22 = 1.0f;
    M23 = 0.0f;
    M24 = 0.0f;

    M31 = 0.0f;
    M32 = 0.0f;
    M33 = 1.0f;
    M34 = 0.0f;

    M41 = 0.0f;
    M42 = 0.0f;
    M43 = 0.0f;
    M44 = 1.0f;
}
//----------------------------------------------------------------------------
inline void Matrix4f::SetRow(int iDesRow, const Vector4f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 4 );

	m_fData[iDesRow][0] = rSrcVec.m_fData[0];
    m_fData[iDesRow][1] = rSrcVec.m_fData[1];
    m_fData[iDesRow][2] = rSrcVec.m_fData[2];
    m_fData[iDesRow][3] = rSrcVec.m_fData[3];
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetRow(int iSrcRow, Vector4f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 4 );

    rDesVec.m_fData[0] = m_fData[iSrcRow][0];
    rDesVec.m_fData[1] = m_fData[iSrcRow][1];
    rDesVec.m_fData[2] = m_fData[iSrcRow][2];
    rDesVec.m_fData[3] = m_fData[iSrcRow][3];
}
//----------------------------------------------------------------------------
inline void Matrix4f::SetColumn(int iDesCol, const Vector4f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 4 );

	m_fData[0][iDesCol] = rSrcVec.m_fData[0];
	m_fData[1][iDesCol] = rSrcVec.m_fData[1];
	m_fData[2][iDesCol] = rSrcVec.m_fData[2];
	m_fData[3][iDesCol] = rSrcVec.m_fData[3];
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetColumn(int iSrcCol, Vector4f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 4 );

	rDesVec.m_fData[0] = m_fData[0][iSrcCol];
    rDesVec.m_fData[1] = m_fData[1][iSrcCol];
    rDesVec.m_fData[2] = m_fData[2][iSrcCol];
    rDesVec.m_fData[3] = m_fData[3][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetTranspose(Matrix4f& rDesMat) const
{
    rDesMat.M11 = M11;
    rDesMat.M12 = M21;
    rDesMat.M13 = M31;
    rDesMat.M14 = M41;

    rDesMat.M21 = M12;
    rDesMat.M22 = M22;
    rDesMat.M23 = M32;
    rDesMat.M24 = M42;

    rDesMat.M31 = M13;
    rDesMat.M32 = M23;
    rDesMat.M33 = M33;
    rDesMat.M34 = M43;

    rDesMat.M41 = M14;
    rDesMat.M42 = M24;
    rDesMat.M43 = M34;
    rDesMat.M44 = M44;
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetInverse(Matrix4f& rDesMat) const
{
    float fA0 = M11*M22 - M12*M21;
    float fA1 = M11*M23 - M13*M21;
    float fA2 = M11*M24 - M14*M21;
    float fA3 = M12*M23 - M13*M22;
    float fA4 = M12*M24 - M14*M22;
    float fA5 = M13*M24 - M14*M23;
    float fB0 = M31*M42 - M32*M41;
    float fB1 = M31*M43 - M33*M41;
    float fB2 = M31*M44 - M34*M41;
    float fB3 = M32*M43 - M33*M42;
    float fB4 = M32*M44 - M34*M42;
    float fB5 = M33*M44 - M34*M43;

    // 如果行列式的值足够接近0,则当前矩阵不可逆,返回0矩阵
    float fDet = fA0*fB5 - fA1*fB4 + fA2*fB3 + fA3*fB2 - fA4*fB1 + fA5*fB0;
    if( Math<float>::FAbs(fDet) <= Math<float>::ZERO_TOLERANCE )
    {
		rDesMat.Zero();
        return;
	}

	rDesMat.M11 = + M22*fB5 - M23*fB4 + M24*fB3;
	rDesMat.M21 = - M21*fB5 + M23*fB2 - M24*fB1;
	rDesMat.M31 = + M21*fB4 - M22*fB2 + M24*fB0;
	rDesMat.M41 = - M21*fB3 + M22*fB1 - M23*fB0;
	rDesMat.M12 = - M12*fB5 + M13*fB4 - M14*fB3;
	rDesMat.M22 = + M11*fB5 - M13*fB2 + M14*fB1;
	rDesMat.M32 = - M11*fB4 + M12*fB2 - M14*fB0;
	rDesMat.M42 = + M11*fB3 - M12*fB1 + M13*fB0;
	rDesMat.M13 = + M42*fA5 - M43*fA4 + M44*fA3;
	rDesMat.M23 = - M41*fA5 + M43*fA2 - M44*fA1;
	rDesMat.M33 = + M41*fA4 - M42*fA2 + M44*fA0;
	rDesMat.M43 = - M41*fA3 + M42*fA1 - M43*fA0;
    rDesMat.M14 = - M32*fA5 + M33*fA4 - M34*fA3;
	rDesMat.M24 = + M31*fA5 - M33*fA2 + M34*fA1;
	rDesMat.M34 = - M31*fA4 + M32*fA2 - M34*fA0;
	rDesMat.M44 = + M31*fA3 - M32*fA1 + M33*fA0;

    float fInvDet = 1.0f / fDet;

    rDesMat.M11 *= fInvDet;
    rDesMat.M12 *= fInvDet;
    rDesMat.M13 *= fInvDet;
    rDesMat.M14 *= fInvDet;

    rDesMat.M21 *= fInvDet;
    rDesMat.M22 *= fInvDet;
    rDesMat.M23 *= fInvDet;
    rDesMat.M24 *= fInvDet;

    rDesMat.M31 *= fInvDet;
    rDesMat.M32 *= fInvDet;
    rDesMat.M33 *= fInvDet;
    rDesMat.M34 *= fInvDet;

    rDesMat.M41 *= fInvDet;
    rDesMat.M42 *= fInvDet;
    rDesMat.M43 *= fInvDet;
    rDesMat.M44 *= fInvDet;
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetAdjoint(Matrix4f& rDesMat) const
{
    float fA0 = M11*M22 - M12*M21;
    float fA1 = M11*M23 - M13*M21;
    float fA2 = M11*M24 - M14*M21;
    float fA3 = M12*M23 - M13*M22;
    float fA4 = M12*M24 - M14*M22;
    float fA5 = M13*M24 - M14*M23;
    float fB0 = M31*M42 - M32*M41;
    float fB1 = M31*M43 - M33*M41;
    float fB2 = M31*M44 - M34*M41;
    float fB3 = M32*M43 - M33*M42;
    float fB4 = M32*M44 - M34*M42;
    float fB5 = M33*M44 - M34*M43;

    rDesMat[0][0] = + M22*fB5 - M23*fB4 + M24*fB3;
    rDesMat[1][0] = - M21*fB5 + M23*fB2 - M24*fB1;
    rDesMat[2][0] = + M21*fB4 - M22*fB2 + M24*fB0;
    rDesMat[3][0] = - M21*fB3 + M22*fB1 - M23*fB0;
    rDesMat[0][1] = - M12*fB5 + M13*fB4 - M14*fB3;
    rDesMat[1][1] = + M11*fB5 - M13*fB2 + M14*fB1;
    rDesMat[2][1] = - M11*fB4 + M12*fB2 - M14*fB0;
    rDesMat[3][1] = + M11*fB3 - M12*fB1 + M13*fB0;
    rDesMat[0][2] = + M42*fA5 - M43*fA4 + M44*fA3;
    rDesMat[1][2] = - M41*fA5 + M43*fA2 - M44*fA1;
    rDesMat[2][2] = + M41*fA4 - M42*fA2 + M44*fA0;
    rDesMat[3][2] = - M41*fA3 + M42*fA1 - M43*fA0;
    rDesMat[0][3] = - M32*fA5 + M33*fA4 - M34*fA3;
    rDesMat[1][3] = + M31*fA5 - M33*fA2 + M34*fA1;
    rDesMat[2][3] = - M31*fA4 + M32*fA2 - M34*fA0;
    rDesMat[3][3] = + M31*fA3 - M32*fA1 + M33*fA0;
}
//----------------------------------------------------------------------------
inline float Matrix4f::GetDeterminant() const
{
    float fA0 = M11*M22 - M12*M21;
    float fA1 = M11*M23 - M13*M21;
    float fA2 = M11*M24 - M14*M21;
    float fA3 = M12*M23 - M13*M22;
    float fA4 = M12*M24 - M14*M22;
    float fA5 = M13*M24 - M14*M23;
    float fB0 = M31*M42 - M32*M41;
    float fB1 = M31*M43 - M33*M41;
    float fB2 = M31*M44 - M34*M41;
    float fB3 = M32*M43 - M33*M42;
    float fB4 = M32*M44 - M34*M42;
    float fB5 = M33*M44 - M34*M43;
    float fDet = fA0*fB5 - fA1*fB4 + fA2*fB3 + fA3*fB2 - fA4*fB1 + fA5*fB0;

    return fDet;
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetTransposeTimes(const Matrix4f& rRhsMat, 
    Matrix4f& rDesMat) const
{
    // C = A^T * B
	rDesMat.M11 = M11*rRhsMat.M11 + M21*rRhsMat.M21 + M31*rRhsMat.M31 + 
        M41*rRhsMat.M41;
    rDesMat.M12 = M11*rRhsMat.M12 + M21*rRhsMat.M22 + M31*rRhsMat.M32 + 
        M41*rRhsMat.M42;
    rDesMat.M13 = M11*rRhsMat.M13 + M21*rRhsMat.M23 + M31*rRhsMat.M33 + 
        M41*rRhsMat.M43;
    rDesMat.M14 = M11*rRhsMat.M14 + M21*rRhsMat.M24 + M31*rRhsMat.M34 + 
        M41*rRhsMat.M44;

    rDesMat.M21 = M12*rRhsMat.M11 + M22*rRhsMat.M21 + M32*rRhsMat.M31 + 
        M42*rRhsMat.M41;
    rDesMat.M22 = M12*rRhsMat.M12 + M22*rRhsMat.M22 + M32*rRhsMat.M32 + 
        M42*rRhsMat.M42;
    rDesMat.M23 = M12*rRhsMat.M13 + M22*rRhsMat.M23 + M32*rRhsMat.M33 + 
        M42*rRhsMat.M43;
    rDesMat.M24 = M12*rRhsMat.M14 + M22*rRhsMat.M24 + M32*rRhsMat.M34 + 
        M42*rRhsMat.M44;

    rDesMat.M31 = M13*rRhsMat.M11 + M23*rRhsMat.M21 + M33*rRhsMat.M31 + 
        M43*rRhsMat.M41;
    rDesMat.M32 = M13*rRhsMat.M12 + M23*rRhsMat.M22 + M33*rRhsMat.M32 + 
        M43*rRhsMat.M42;
    rDesMat.M33 = M13*rRhsMat.M13 + M23*rRhsMat.M23 + M33*rRhsMat.M33 + 
        M43*rRhsMat.M43;
    rDesMat.M34 = M13*rRhsMat.M14 + M23*rRhsMat.M24 + M33*rRhsMat.M34 + 
        M43*rRhsMat.M44;

    rDesMat.M41 = M14*rRhsMat.M11 + M24*rRhsMat.M21 + M34*rRhsMat.M31 + 
        M44*rRhsMat.M41;
    rDesMat.M42 = M14*rRhsMat.M12 + M24*rRhsMat.M22 + M34*rRhsMat.M32 + 
        M44*rRhsMat.M42;
    rDesMat.M43 = M14*rRhsMat.M13 + M24*rRhsMat.M23 + M34*rRhsMat.M33 + 
        M44*rRhsMat.M43;
    rDesMat.M44 = M14*rRhsMat.M14 + M24*rRhsMat.M24 + M34*rRhsMat.M34 + 
        M44*rRhsMat.M44;
}
//----------------------------------------------------------------------------
inline void Matrix4f::GetTimesTranspose(const Matrix4f& rRhsMat, 
    Matrix4f& rDesMat) const
{
    // C = A * B^T
    rDesMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M12 + M13*rRhsMat.M13 + 
        M14*rRhsMat.M14;
    rDesMat.M12 = M11*rRhsMat.M21 + M12*rRhsMat.M22 + M13*rRhsMat.M23 + 
        M14*rRhsMat.M24;
    rDesMat.M13 = M11*rRhsMat.M31 + M12*rRhsMat.M32 + M13*rRhsMat.M33 + 
        M14*rRhsMat.M34;
    rDesMat.M14 = M11*rRhsMat.M41 + M12*rRhsMat.M42 + M13*rRhsMat.M43 + 
        M14*rRhsMat.M44;

    rDesMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M12 + M23*rRhsMat.M13 + 
        M24*rRhsMat.M14;
    rDesMat.M22 = M21*rRhsMat.M21 + M22*rRhsMat.M22 + M23*rRhsMat.M23 + 
        M24*rRhsMat.M24;
    rDesMat.M23 = M21*rRhsMat.M31 + M22*rRhsMat.M32 + M23*rRhsMat.M33 + 
        M24*rRhsMat.M34;
    rDesMat.M24 = M21*rRhsMat.M41 + M22*rRhsMat.M42 + M23*rRhsMat.M43 + 
        M24*rRhsMat.M44;

    rDesMat.M31 = M31*rRhsMat.M11 + M32*rRhsMat.M12 + M33*rRhsMat.M13 + 
        M34*rRhsMat.M14;
    rDesMat.M32 = M31*rRhsMat.M21 + M32*rRhsMat.M22 + M33*rRhsMat.M23 + 
        M34*rRhsMat.M24;
    rDesMat.M33 = M31*rRhsMat.M31 + M32*rRhsMat.M32 + M33*rRhsMat.M33 + 
        M34*rRhsMat.M34;
    rDesMat.M34 = M31*rRhsMat.M41 + M32*rRhsMat.M42 + M33*rRhsMat.M43 + 
        M34*rRhsMat.M44;

    rDesMat.M41 = M41*rRhsMat.M11 + M42*rRhsMat.M12 + M43*rRhsMat.M13 + 
        M44*rRhsMat.M14;
    rDesMat.M42 = M41*rRhsMat.M21 + M42*rRhsMat.M22 + M43*rRhsMat.M23 + 
        M44*rRhsMat.M24;
    rDesMat.M43 = M41*rRhsMat.M31 + M42*rRhsMat.M32 + M43*rRhsMat.M33 + 
        M44*rRhsMat.M34;
    rDesMat.M44 = M41*rRhsMat.M41 + M42*rRhsMat.M42 + M43*rRhsMat.M43 + 
        M44*rRhsMat.M44;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度4阶方阵类
//----------------------------------------------------------------------------
inline int Matrix4d::CompareData(const Matrix4d& rMat) const
{
    return memcmp(m_dData, rMat.m_dData, 16 * sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix4d::Zero()
{
    memset(m_dData, 0, 16*sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix4d::Identity()
{
    M11 = 1.0;
    M12 = 0.0;
    M13 = 0.0;
    M14 = 0.0;

    M21 = 0.0;
    M22 = 1.0;
    M23 = 0.0;
    M24 = 0.0;

    M31 = 0.0;
    M32 = 0.0;
    M33 = 1.0;
    M34 = 0.0;

    M41 = 0.0;
    M42 = 0.0;
    M43 = 0.0;
    M44 = 1.0;
}
//----------------------------------------------------------------------------
inline void Matrix4d::SetRow(int iDesRow, const Vector4d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 4 );

	m_dData[iDesRow][0] = rSrcVec.m_dData[0];
    m_dData[iDesRow][1] = rSrcVec.m_dData[1];
    m_dData[iDesRow][2] = rSrcVec.m_dData[2];
    m_dData[iDesRow][3] = rSrcVec.m_dData[3];
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetRow(int iSrcRow, Vector4d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 4 );

    rDesVec.m_dData[0] = m_dData[iSrcRow][0];
    rDesVec.m_dData[1] = m_dData[iSrcRow][1];
    rDesVec.m_dData[2] = m_dData[iSrcRow][2];
    rDesVec.m_dData[3] = m_dData[iSrcRow][3];
}
//----------------------------------------------------------------------------
inline void Matrix4d::SetColumn(int iDesCol, const Vector4d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 4 );

	m_dData[0][iDesCol] = rSrcVec.m_dData[0];
	m_dData[1][iDesCol] = rSrcVec.m_dData[1];
	m_dData[2][iDesCol] = rSrcVec.m_dData[2];
	m_dData[3][iDesCol] = rSrcVec.m_dData[3];
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetColumn(int iSrcCol, Vector4d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 4 );

	rDesVec.m_dData[0] = m_dData[0][iSrcCol];
    rDesVec.m_dData[1] = m_dData[1][iSrcCol];
    rDesVec.m_dData[2] = m_dData[2][iSrcCol];
    rDesVec.m_dData[3] = m_dData[3][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetTranspose(Matrix4d& rDesMat) const
{
    rDesMat.M11 = M11;
    rDesMat.M12 = M21;
    rDesMat.M13 = M31;
    rDesMat.M14 = M41;

    rDesMat.M21 = M12;
    rDesMat.M22 = M22;
    rDesMat.M23 = M32;
    rDesMat.M24 = M42;

    rDesMat.M31 = M13;
    rDesMat.M32 = M23;
    rDesMat.M33 = M33;
    rDesMat.M34 = M43;

    rDesMat.M41 = M14;
    rDesMat.M42 = M24;
    rDesMat.M43 = M34;
    rDesMat.M44 = M44;
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetInverse(Matrix4d& rDesMat) const
{
    double dA0 = M11*M22 - M12*M21;
    double dA1 = M11*M23 - M13*M21;
    double dA2 = M11*M24 - M14*M21;
    double dA3 = M12*M23 - M13*M22;
    double dA4 = M12*M24 - M14*M22;
    double dA5 = M13*M24 - M14*M23;
    double dB0 = M31*M42 - M32*M41;
    double dB1 = M31*M43 - M33*M41;
    double dB2 = M31*M44 - M34*M41;
    double dB3 = M32*M43 - M33*M42;
    double dB4 = M32*M44 - M34*M42;
    double dB5 = M33*M44 - M34*M43;

    // 如果行列式的值足够接近0,则当前矩阵不可逆,返回0矩阵
    double dDet = dA0*dB5 - dA1*dB4 + dA2*dB3 + dA3*dB2 - dA4*dB1 + dA5*dB0;
    if( Math<double>::FAbs(dDet) <= Math<double>::ZERO_TOLERANCE )
    {
		rDesMat.Zero();
        return;
	}

	rDesMat.M11 = + M22*dB5 - M23*dB4 + M24*dB3;
	rDesMat.M21 = - M21*dB5 + M23*dB2 - M24*dB1;
	rDesMat.M31 = + M21*dB4 - M22*dB2 + M24*dB0;
	rDesMat.M41 = - M21*dB3 + M22*dB1 - M23*dB0;
	rDesMat.M12 = - M12*dB5 + M13*dB4 - M14*dB3;
	rDesMat.M22 = + M11*dB5 - M13*dB2 + M14*dB1;
	rDesMat.M32 = - M11*dB4 + M12*dB2 - M14*dB0;
	rDesMat.M42 = + M11*dB3 - M12*dB1 + M13*dB0;
	rDesMat.M13 = + M42*dA5 - M43*dA4 + M44*dA3;
	rDesMat.M23 = - M41*dA5 + M43*dA2 - M44*dA1;
	rDesMat.M33 = + M41*dA4 - M42*dA2 + M44*dA0;
	rDesMat.M43 = - M41*dA3 + M42*dA1 - M43*dA0;
    rDesMat.M14 = - M32*dA5 + M33*dA4 - M34*dA3;
	rDesMat.M24 = + M31*dA5 - M33*dA2 + M34*dA1;
	rDesMat.M34 = - M31*dA4 + M32*dA2 - M34*dA0;
	rDesMat.M44 = + M31*dA3 - M32*dA1 + M33*dA0;

    double dInvDet = 1.0 / dDet;

    rDesMat.M11 *= dInvDet;
    rDesMat.M12 *= dInvDet;
    rDesMat.M13 *= dInvDet;
    rDesMat.M14 *= dInvDet;

    rDesMat.M21 *= dInvDet;
    rDesMat.M22 *= dInvDet;
    rDesMat.M23 *= dInvDet;
    rDesMat.M24 *= dInvDet;

    rDesMat.M31 *= dInvDet;
    rDesMat.M32 *= dInvDet;
    rDesMat.M33 *= dInvDet;
    rDesMat.M34 *= dInvDet;

    rDesMat.M41 *= dInvDet;
    rDesMat.M42 *= dInvDet;
    rDesMat.M43 *= dInvDet;
    rDesMat.M44 *= dInvDet;
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetAdjoint(Matrix4d& rDesMat) const
{
    double dA0 = M11*M22 - M12*M21;
    double dA1 = M11*M23 - M13*M21;
    double dA2 = M11*M24 - M14*M21;
    double dA3 = M12*M23 - M13*M22;
    double dA4 = M12*M24 - M14*M22;
    double dA5 = M13*M24 - M14*M23;
    double dB0 = M31*M42 - M32*M41;
    double dB1 = M31*M43 - M33*M41;
    double dB2 = M31*M44 - M34*M41;
    double dB3 = M32*M43 - M33*M42;
    double dB4 = M32*M44 - M34*M42;
    double dB5 = M33*M44 - M34*M43;

    rDesMat[0][0] = + M22*dB5 - M23*dB4 + M24*dB3;
    rDesMat[1][0] = - M21*dB5 + M23*dB2 - M24*dB1;
    rDesMat[2][0] = + M21*dB4 - M22*dB2 + M24*dB0;
    rDesMat[3][0] = - M21*dB3 + M22*dB1 - M23*dB0;
    rDesMat[0][1] = - M12*dB5 + M13*dB4 - M14*dB3;
    rDesMat[1][1] = + M11*dB5 - M13*dB2 + M14*dB1;
    rDesMat[2][1] = - M11*dB4 + M12*dB2 - M14*dB0;
    rDesMat[3][1] = + M11*dB3 - M12*dB1 + M13*dB0;
    rDesMat[0][2] = + M42*dA5 - M43*dA4 + M44*dA3;
    rDesMat[1][2] = - M41*dA5 + M43*dA2 - M44*dA1;
    rDesMat[2][2] = + M41*dA4 - M42*dA2 + M44*dA0;
    rDesMat[3][2] = - M41*dA3 + M42*dA1 - M43*dA0;
    rDesMat[0][3] = - M32*dA5 + M33*dA4 - M34*dA3;
    rDesMat[1][3] = + M31*dA5 - M33*dA2 + M34*dA1;
    rDesMat[2][3] = - M31*dA4 + M32*dA2 - M34*dA0;
    rDesMat[3][3] = + M31*dA3 - M32*dA1 + M33*dA0;
}
//----------------------------------------------------------------------------
inline double Matrix4d::GetDeterminant() const
{
    double dA0 = M11*M22 - M12*M21;
    double dA1 = M11*M23 - M13*M21;
    double dA2 = M11*M24 - M14*M21;
    double dA3 = M12*M23 - M13*M22;
    double dA4 = M12*M24 - M14*M22;
    double dA5 = M13*M24 - M14*M23;
    double dB0 = M31*M42 - M32*M41;
    double dB1 = M31*M43 - M33*M41;
    double dB2 = M31*M44 - M34*M41;
    double dB3 = M32*M43 - M33*M42;
    double dB4 = M32*M44 - M34*M42;
    double dB5 = M33*M44 - M34*M43;
    double dDet = dA0*dB5 - dA1*dB4 + dA2*dB3 + dA3*dB2 - dA4*dB1 + dA5*dB0;

    return dDet;
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetTransposeTimes(const Matrix4d& rRhsMat, 
    Matrix4d& rDesMat) const
{
    // C = A^T * B
	rDesMat.M11 = M11*rRhsMat.M11 + M21*rRhsMat.M21 + M31*rRhsMat.M31 + 
        M41*rRhsMat.M41;
    rDesMat.M12 = M11*rRhsMat.M12 + M21*rRhsMat.M22 + M31*rRhsMat.M32 + 
        M41*rRhsMat.M42;
    rDesMat.M13 = M11*rRhsMat.M13 + M21*rRhsMat.M23 + M31*rRhsMat.M33 + 
        M41*rRhsMat.M43;
    rDesMat.M14 = M11*rRhsMat.M14 + M21*rRhsMat.M24 + M31*rRhsMat.M34 + 
        M41*rRhsMat.M44;

    rDesMat.M21 = M12*rRhsMat.M11 + M22*rRhsMat.M21 + M32*rRhsMat.M31 + 
        M42*rRhsMat.M41;
    rDesMat.M22 = M12*rRhsMat.M12 + M22*rRhsMat.M22 + M32*rRhsMat.M32 + 
        M42*rRhsMat.M42;
    rDesMat.M23 = M12*rRhsMat.M13 + M22*rRhsMat.M23 + M32*rRhsMat.M33 + 
        M42*rRhsMat.M43;
    rDesMat.M24 = M12*rRhsMat.M14 + M22*rRhsMat.M24 + M32*rRhsMat.M34 + 
        M42*rRhsMat.M44;

    rDesMat.M31 = M13*rRhsMat.M11 + M23*rRhsMat.M21 + M33*rRhsMat.M31 + 
        M43*rRhsMat.M41;
    rDesMat.M32 = M13*rRhsMat.M12 + M23*rRhsMat.M22 + M33*rRhsMat.M32 + 
        M43*rRhsMat.M42;
    rDesMat.M33 = M13*rRhsMat.M13 + M23*rRhsMat.M23 + M33*rRhsMat.M33 + 
        M43*rRhsMat.M43;
    rDesMat.M34 = M13*rRhsMat.M14 + M23*rRhsMat.M24 + M33*rRhsMat.M34 + 
        M43*rRhsMat.M44;

    rDesMat.M41 = M14*rRhsMat.M11 + M24*rRhsMat.M21 + M34*rRhsMat.M31 + 
        M44*rRhsMat.M41;
    rDesMat.M42 = M14*rRhsMat.M12 + M24*rRhsMat.M22 + M34*rRhsMat.M32 + 
        M44*rRhsMat.M42;
    rDesMat.M43 = M14*rRhsMat.M13 + M24*rRhsMat.M23 + M34*rRhsMat.M33 + 
        M44*rRhsMat.M43;
    rDesMat.M44 = M14*rRhsMat.M14 + M24*rRhsMat.M24 + M34*rRhsMat.M34 + 
        M44*rRhsMat.M44;
}
//----------------------------------------------------------------------------
inline void Matrix4d::GetTimesTranspose(const Matrix4d& rRhsMat, 
    Matrix4d& rDesMat) const
{
    // C = A * B^T
    rDesMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M12 + M13*rRhsMat.M13 + 
        M14*rRhsMat.M14;
    rDesMat.M12 = M11*rRhsMat.M21 + M12*rRhsMat.M22 + M13*rRhsMat.M23 + 
        M14*rRhsMat.M24;
    rDesMat.M13 = M11*rRhsMat.M31 + M12*rRhsMat.M32 + M13*rRhsMat.M33 + 
        M14*rRhsMat.M34;
    rDesMat.M14 = M11*rRhsMat.M41 + M12*rRhsMat.M42 + M13*rRhsMat.M43 + 
        M14*rRhsMat.M44;

    rDesMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M12 + M23*rRhsMat.M13 + 
        M24*rRhsMat.M14;
    rDesMat.M22 = M21*rRhsMat.M21 + M22*rRhsMat.M22 + M23*rRhsMat.M23 + 
        M24*rRhsMat.M24;
    rDesMat.M23 = M21*rRhsMat.M31 + M22*rRhsMat.M32 + M23*rRhsMat.M33 + 
        M24*rRhsMat.M34;
    rDesMat.M24 = M21*rRhsMat.M41 + M22*rRhsMat.M42 + M23*rRhsMat.M43 + 
        M24*rRhsMat.M44;

    rDesMat.M31 = M31*rRhsMat.M11 + M32*rRhsMat.M12 + M33*rRhsMat.M13 + 
        M34*rRhsMat.M14;
    rDesMat.M32 = M31*rRhsMat.M21 + M32*rRhsMat.M22 + M33*rRhsMat.M23 + 
        M34*rRhsMat.M24;
    rDesMat.M33 = M31*rRhsMat.M31 + M32*rRhsMat.M32 + M33*rRhsMat.M33 + 
        M34*rRhsMat.M34;
    rDesMat.M34 = M31*rRhsMat.M41 + M32*rRhsMat.M42 + M33*rRhsMat.M43 + 
        M34*rRhsMat.M44;

    rDesMat.M41 = M41*rRhsMat.M11 + M42*rRhsMat.M12 + M43*rRhsMat.M13 + 
        M44*rRhsMat.M14;
    rDesMat.M42 = M41*rRhsMat.M21 + M42*rRhsMat.M22 + M43*rRhsMat.M23 + 
        M44*rRhsMat.M24;
    rDesMat.M43 = M41*rRhsMat.M31 + M42*rRhsMat.M32 + M43*rRhsMat.M33 + 
        M44*rRhsMat.M34;
    rDesMat.M44 = M41*rRhsMat.M41 + M42*rRhsMat.M42 + M43*rRhsMat.M43 + 
        M44*rRhsMat.M44;
}
//----------------------------------------------------------------------------