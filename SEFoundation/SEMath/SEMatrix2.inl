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
// 单精度2阶方阵类
//----------------------------------------------------------------------------
inline int Matrix2f::CompareData(const Matrix2f& rMat) const
{
    return memcmp(m_fData, rMat.m_fData, 4*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix2f::Zero()
{
    memset(m_fData, 0, 4*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix2f::Identity()
{
    m_fData[0][0] = 1.0f;
    m_fData[0][1] = 0.0f;
    m_fData[1][0] = 0.0f;
    m_fData[1][1] = 1.0f;
}
//----------------------------------------------------------------------------
inline void Matrix2f::Diagonal(float fM11, float fM22)
{
    m_fData[0][0] = fM11;
    m_fData[0][1] = 0.0f;
    m_fData[1][0] = 0.0f;
    m_fData[1][1] = fM22;
}
//----------------------------------------------------------------------------
inline void Matrix2f::FromAngle(float fAngle)
{
    m_fData[0][0] = Math<float>::Cos(fAngle);
    m_fData[1][0] = -Math<float>::Sin(fAngle);
    m_fData[0][1] = -m_fData[1][0];
    m_fData[1][1] =  m_fData[0][0];
}
//----------------------------------------------------------------------------
inline void Matrix2f::TensorProduct(const SEVector2f& rVecU, const SEVector2f& rVecV)
{
    m_fData[0][0] = rVecU[0] * rVecV[0];
    m_fData[0][1] = rVecU[0] * rVecV[1];
    m_fData[1][0] = rVecU[1] * rVecV[0];
    m_fData[1][1] = rVecU[1] * rVecV[1];
}
//----------------------------------------------------------------------------
inline void Matrix2f::SetRow(int iDesRow, const SEVector2f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 2 );

	m_fData[iDesRow][0] = rSrcVec.m_fData[0];
    m_fData[iDesRow][1] = rSrcVec.m_fData[1];
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetRow(int iSrcRow, SEVector2f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 2 );

    rDesVec.m_fData[0] = m_fData[iSrcRow][0];
    rDesVec.m_fData[1] = m_fData[iSrcRow][1];
}
//----------------------------------------------------------------------------
inline void Matrix2f::SetColumn(int iDesCol, const SEVector2f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 2 );

	m_fData[0][iDesCol] = rSrcVec.m_fData[0];
	m_fData[1][iDesCol] = rSrcVec.m_fData[1];
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetColumn(int iSrcCol, SEVector2f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 2 );

	rDesVec.m_fData[0] = m_fData[0][iSrcCol];
    rDesVec.m_fData[1] = m_fData[1][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetTranspose(Matrix2f& rDesMat) const
{
    rDesMat.M11 = M11;
    rDesMat.M12 = M21;

    rDesMat.M21 = M12;
    rDesMat.M22 = M22;
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetInverse(Matrix2f& rDesMat) const
{
    float fDet = m_fData[0][0]*m_fData[1][1] - m_fData[0][1]*m_fData[1][0];

    if( Math<float>::FAbs(fDet) > Math<float>::ZERO_TOLERANCE )
    {
        float fInvDet = 1.0f / fDet;

        rDesMat[0][0] =  m_fData[1][1] * fInvDet;
        rDesMat[0][1] = -m_fData[0][1] * fInvDet;
        rDesMat[1][0] = -m_fData[1][0] * fInvDet;
        rDesMat[1][1] =  m_fData[0][0] * fInvDet;
    }
    else
    {
        rDesMat.Zero();
    }
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetAdjoint(Matrix2f& rDesMat) const
{
    rDesMat[0][0] = m_fData[1][1];
    rDesMat[0][1] = -m_fData[0][1];
    rDesMat[1][0] = -m_fData[1][0];
    rDesMat[1][1] = m_fData[0][0];
}
//----------------------------------------------------------------------------
inline float Matrix2f::GetDeterminant() const
{
    return m_fData[0][0]*m_fData[1][1] - m_fData[0][1]*m_fData[1][0];
}
//----------------------------------------------------------------------------
inline void Matrix2f::ToAngle(float& rfAngle) const
{
    rfAngle = Math<float>::ATan2(m_fData[1][0], m_fData[0][0]);
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetTransposeTimes(const Matrix2f& rRhsMat, Matrix2f& rDesMat) const
{
    // C = A^T * B
    rDesMat.M11 = M11*rRhsMat.M11 + M21*rRhsMat.M21;
    rDesMat.M12 = M11*rRhsMat.M12 + M21*rRhsMat.M22;

    rDesMat.M21 = M12*rRhsMat.M11 + M22*rRhsMat.M21;
    rDesMat.M22 = M12*rRhsMat.M12 + M22*rRhsMat.M22;
}
//----------------------------------------------------------------------------
inline void Matrix2f::GetTimesTranspose(const Matrix2f& rRhsMat, Matrix2f& rDesMat) const
{
    // C = A * B^T
    rDesMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M12;
    rDesMat.M12 = M11*rRhsMat.M21 + M12*rRhsMat.M22;

    rDesMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M12;
    rDesMat.M22 = M21*rRhsMat.M21 + M22*rRhsMat.M22;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度2阶方阵类
//----------------------------------------------------------------------------
inline int Matrix2d::CompareData(const Matrix2d& rMat) const
{
    return memcmp(m_dData, rMat.m_dData, 4*sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix2d::Zero()
{
    memset(m_dData, 0, 4*sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix2d::Identity()
{
    m_dData[0][0] = 1.0;
    m_dData[0][1] = 0.0;
    m_dData[1][0] = 0.0;
    m_dData[1][1] = 1.0;
}
//----------------------------------------------------------------------------
inline void Matrix2d::Diagonal(double dM11, double dM22)
{
    m_dData[0][0] = dM11;
    m_dData[0][1] = 0.0;
    m_dData[1][0] = 0.0;
    m_dData[1][1] = dM22;
}
//----------------------------------------------------------------------------
inline void Matrix2d::FromAngle(double dAngle)
{
    m_dData[0][0] = Math<double>::Cos(dAngle);
    m_dData[1][0] = -Math<double>::Sin(dAngle);
    m_dData[0][1] = -m_dData[1][0];
    m_dData[1][1] =  m_dData[0][0];
}
//----------------------------------------------------------------------------
inline void Matrix2d::TensorProduct(const SEVector2d& rVecU, 
    const SEVector2d& rVecV)
{
    m_dData[0][0] = rVecU[0] * rVecV[0];
    m_dData[0][1] = rVecU[0] * rVecV[1];
    m_dData[1][0] = rVecU[1] * rVecV[0];
    m_dData[1][1] = rVecU[1] * rVecV[1];
}
//----------------------------------------------------------------------------
inline void Matrix2d::SetRow(int iDesRow, const SEVector2d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 2 );

	m_dData[iDesRow][0] = rSrcVec.m_dData[0];
    m_dData[iDesRow][1] = rSrcVec.m_dData[1];
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetRow(int iSrcRow, SEVector2d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 2 );

    rDesVec.m_dData[0] = m_dData[iSrcRow][0];
    rDesVec.m_dData[1] = m_dData[iSrcRow][1];
}
//----------------------------------------------------------------------------
inline void Matrix2d::SetColumn(int iDesCol, const SEVector2d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 2 );

	m_dData[0][iDesCol] = rSrcVec.m_dData[0];
	m_dData[1][iDesCol] = rSrcVec.m_dData[1];
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetColumn(int iSrcCol, SEVector2d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 2 );

	rDesVec.m_dData[0] = m_dData[0][iSrcCol];
    rDesVec.m_dData[1] = m_dData[1][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetTranspose(Matrix2d& rDesMat) const
{
    rDesMat.M11 = M11;
    rDesMat.M12 = M21;

    rDesMat.M21 = M12;
    rDesMat.M22 = M22;
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetInverse(Matrix2d& rDesMat) const
{
    double dDet = m_dData[0][0]*m_dData[1][1] - m_dData[0][1]*m_dData[1][0];

    if( Math<double>::FAbs(dDet) > Math<double>::ZERO_TOLERANCE )
    {
        double dInvDet = 1.0 / dDet;

        rDesMat[0][0] =  m_dData[1][1] * dInvDet;
        rDesMat[0][1] = -m_dData[0][1] * dInvDet;
        rDesMat[1][0] = -m_dData[1][0] * dInvDet;
        rDesMat[1][1] =  m_dData[0][0] * dInvDet;
    }
    else
    {
        rDesMat.Zero();
    }
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetAdjoint(Matrix2d& rDesMat) const
{
    rDesMat[0][0] = m_dData[1][1];
    rDesMat[0][1] = -m_dData[0][1];
    rDesMat[1][0] = -m_dData[1][0];
    rDesMat[1][1] = m_dData[0][0];
}
//----------------------------------------------------------------------------
inline double Matrix2d::GetDeterminant() const
{
    return m_dData[0][0]*m_dData[1][1] - m_dData[0][1]*m_dData[1][0];
}
//----------------------------------------------------------------------------
inline void Matrix2d::ToAngle(double& rdAngle) const
{
    rdAngle = Math<double>::ATan2(m_dData[1][0], m_dData[0][0]);
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetTransposeTimes(const Matrix2d& rRhsMat, 
    Matrix2d& rDesMat) const
{
    // C = A^T * B
    rDesMat.M11 = M11*rRhsMat.M11 + M21*rRhsMat.M21;
    rDesMat.M12 = M11*rRhsMat.M12 + M21*rRhsMat.M22;

    rDesMat.M21 = M12*rRhsMat.M11 + M22*rRhsMat.M21;
    rDesMat.M22 = M12*rRhsMat.M12 + M22*rRhsMat.M22;
}
//----------------------------------------------------------------------------
inline void Matrix2d::GetTimesTranspose(const Matrix2d& rRhsMat, 
    Matrix2d& rDesMat) const
{
    // C = A * B^T
    rDesMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M12;
    rDesMat.M12 = M11*rRhsMat.M21 + M12*rRhsMat.M22;

    rDesMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M12;
    rDesMat.M22 = M21*rRhsMat.M21 + M22*rRhsMat.M22;
}
//----------------------------------------------------------------------------