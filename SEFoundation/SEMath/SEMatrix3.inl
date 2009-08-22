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
// 单精度3阶方阵类
//----------------------------------------------------------------------------
inline float Matrix3f::M11(void) const
{
    return m_fData[0][0];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M11(void)
{
    return m_fData[0][0];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M12(void) const
{
    return m_fData[0][1];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M12(void)
{
    return m_fData[0][1];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M13(void) const
{
    return m_fData[0][2];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M13(void)
{
    return m_fData[0][2];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M21(void) const
{
    return m_fData[1][0];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M21(void)
{
    return m_fData[1][0];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M22(void) const
{
    return m_fData[1][1];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M22(void)
{
    return m_fData[1][1];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M23(void) const
{
    return m_fData[1][2];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M23(void)
{
    return m_fData[1][2];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M31(void) const
{
    return m_fData[2][0];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M31(void)
{
    return m_fData[2][0];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M32(void) const
{
    return m_fData[2][1];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M32(void)
{
    return m_fData[2][1];
}
//----------------------------------------------------------------------------
inline float Matrix3f::M33(void) const
{
    return m_fData[2][2];
}
//----------------------------------------------------------------------------
inline float& Matrix3f::M33(void)
{
    return m_fData[2][2];
}
//----------------------------------------------------------------------------
inline int Matrix3f::CompareData(const Matrix3f& rMat) const
{
    return memcmp(m_fData, rMat.m_fData, /*12*/9*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix3f::Zero()
{
    memset(m_fData, 0, /*12*/9*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix3f::Identity()
{
    m_fData[0][0] = 1.0f;
    m_fData[0][1] = 0.0f;
    m_fData[0][2] = 0.0f;
    m_fData[1][0] = 0.0f;
    m_fData[1][1] = 1.0f;
    m_fData[1][2] = 0.0f;
    m_fData[2][0] = 0.0f;
    m_fData[2][1] = 0.0f;
    m_fData[2][2] = 1.0f;
}
//----------------------------------------------------------------------------
inline void Matrix3f::Diagonal(float fM11, float fM22, float fM33)
{
    m_fData[0][0] = fM11;
    m_fData[0][1] = 0.0f;
    m_fData[0][2] = 0.0f;
    m_fData[1][0] = 0.0f;
    m_fData[1][1] = fM22;
    m_fData[1][2] = 0.0f;
    m_fData[2][0] = 0.0f;
    m_fData[2][1] = 0.0f;
    m_fData[2][2] = fM33;
}
//----------------------------------------------------------------------------
inline void Matrix3f::FromAxisAngle(const Vector3f& rAxisVec, float fAngle)
{
    // 旋转轴向量为W(w0,w1,w2),且w0^2 + w1^2 + w2^2 = 1,
    // R = I + sin(theta)S + (1 - cos(theta))S^2,
    // I为单位矩阵,
    // S为反对称矩阵:
    // S =   0,   w2,   -w1,
    //     -w2,    0,    w0,
    //      w1,  -w0,     0,

    float fCos = Math<float>::Cos(fAngle);
    float fSin = Math<float>::Sin(fAngle);
    float fOneMinusCos = 1.0f - fCos;

    float fX2 = rAxisVec[0] * rAxisVec[0];
    float fY2 = rAxisVec[1] * rAxisVec[1];
    float fZ2 = rAxisVec[2] * rAxisVec[2];
    float fXYM = rAxisVec[0] * rAxisVec[1] * fOneMinusCos;
    float fXZM = rAxisVec[0] * rAxisVec[2] * fOneMinusCos;
    float fYZM = rAxisVec[1] * rAxisVec[2] * fOneMinusCos;
    float fXSin = rAxisVec[0] * fSin;
    float fYSin = rAxisVec[1] * fSin;
    float fZSin = rAxisVec[2] * fSin;
    
    m_fData[0][0] = fX2*fOneMinusCos + fCos;
    m_fData[1][0] = fXYM - fZSin;
    m_fData[2][0] = fXZM + fYSin;

    m_fData[0][1] = fXYM + fZSin;
    m_fData[1][1] = fY2*fOneMinusCos + fCos;
    m_fData[2][1] = fYZM - fXSin;

    m_fData[0][2] = fXZM - fYSin;
    m_fData[1][2] = fYZM + fXSin;
    m_fData[2][2] = fZ2*fOneMinusCos + fCos;
}
//----------------------------------------------------------------------------
inline void Matrix3f::ToAxisAngle(Vector3f& rAxisVec, float& rfAngle) const
{
    // 旋转轴向量为W(w0,w1,w2),且w0^2 + w1^2 + w2^2 = 1,
    // R = I + sin(theta)S + (1 - cos(theta))S^2,
    // I为单位矩阵,
    // S为反对称矩阵:
    // S =   0,   w2,   -w1,
    //     -w2,    0,    w0,
    //      w1,  -w0,     0,
    //
    // cos(theta) = (trace(R) - 1) / 2,且R - R^T = 2 * sin(theta) * S
    // theta = acos((trace(R) - 1) / 2)
    //
    // (1) theta = 0,则R = R^T,因此任何单位向量都可以作为旋转轴
    // (2) theta > 0,则R - R^T = 2sin(theta)S,
    //     W = (S12,S20,S01) / |(S12,S20,S01)|
    // (3) theta = pi,则S^2 = (R - I) / 2,
    //     S^2的对角元素为w0^2 - 1, w1^2 - 1,w2^2 - 1,因此可以解出w0,w1,w2

    float fTrace = m_fData[0][0] + m_fData[1][1] + m_fData[2][2];
    float fCos = 0.5f * (fTrace - 1.0f);
    rfAngle = Math<float>::ACos(fCos);  // [0,PI]

    if( rfAngle > 0.0f )
    {
        if( rfAngle < Math<float>::PI )
        {
            // W = (S12,S20,S01) / |(S12,S20,S01)| 
            rAxisVec[0] = m_fData[1][2] - m_fData[2][1];
            rAxisVec[1] = m_fData[2][0] - m_fData[0][2];
            rAxisVec[2] = m_fData[0][1] - m_fData[1][0];

            rAxisVec.Normalize();
        }
        else
        {
            // theta = pi
            // 为减小误差和避免除0问题,
            // 从r00,r11,r22中最大者解出旋转轴最大分量,进而获取剩余分量

            float fHalfInverse;
            if( m_fData[0][0] >= m_fData[1][1] )
            {
                // r00 >= r11
                if( m_fData[0][0] >= m_fData[2][2] )
                {
                    // r00是最大对角元素
                    rAxisVec[0] = 0.5f*Math<float>::Sqrt(m_fData[0][0] - 
                        m_fData[1][1] - m_fData[2][2] + 1.0f);
                    fHalfInverse = 0.5f / rAxisVec[0];
                    rAxisVec[1] = fHalfInverse * m_fData[0][1];
                    rAxisVec[2] = fHalfInverse * m_fData[0][2];
                }
                else
                {
                    // r22是最大对角元素
                    rAxisVec[2] = 0.5f*Math<float>::Sqrt(m_fData[2][2] - 
                        m_fData[0][0] - m_fData[1][1] + 1.0f);
                    fHalfInverse = 0.5f / rAxisVec[2];
                    rAxisVec[0] = fHalfInverse*m_fData[0][2];
                    rAxisVec[1] = fHalfInverse*m_fData[1][2];
                }
            }
            else
            {
                // r11 > r00
                if( m_fData[1][1] >= m_fData[2][2] )
                {
                    // r11是最大对角元素
                    rAxisVec[1] = 0.5f*Math<float>::Sqrt(m_fData[1][1] - 
                        m_fData[0][0] - m_fData[2][2] + 1.0f);
                    fHalfInverse  = 0.5f / rAxisVec[1];
                    rAxisVec[0] = fHalfInverse * m_fData[0][1];
                    rAxisVec[2] = fHalfInverse * m_fData[1][2];
                }
                else
                {
                    // r22是最大对角元素
                    rAxisVec[2] = 0.5f*Math<float>::Sqrt(m_fData[2][2] - 
                        m_fData[0][0] - m_fData[1][1] + 1.0f);
                    fHalfInverse = 0.5f / rAxisVec[2];
                    rAxisVec[0] = fHalfInverse * m_fData[0][2];
                    rAxisVec[1] = fHalfInverse * m_fData[1][2];
                }
            }
        }
    }
    else
    {
        // theta = 0时,任何旋转轴都可以

        rAxisVec[0] = 1.0f;
        rAxisVec[1] = 0.0f;
        rAxisVec[2] = 0.0f;
    }
}
//----------------------------------------------------------------------------
inline void Matrix3f::TensorProduct(const Vector3f& rVecU, 
    const Vector3f& rVecV)
{
    m_fData[0][0] = rVecU[0] * rVecV[0];
    m_fData[0][1] = rVecU[0] * rVecV[1];
    m_fData[0][2] = rVecU[0] * rVecV[2];
    m_fData[1][0] = rVecU[1] * rVecV[0];
    m_fData[1][1] = rVecU[1] * rVecV[1];
    m_fData[1][2] = rVecU[1] * rVecV[2];
    m_fData[2][0] = rVecU[2] * rVecV[0];
    m_fData[2][1] = rVecU[2] * rVecV[1];
    m_fData[2][2] = rVecU[2] * rVecV[2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::SetRow(int iDesRow, const Vector3f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 3 );

	m_fData[iDesRow][0] = rSrcVec.m_fData[0];
    m_fData[iDesRow][1] = rSrcVec.m_fData[1];
    m_fData[iDesRow][2] = rSrcVec.m_fData[2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetRow(int iSrcRow, Vector3f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 3 );

    rDesVec.m_fData[0] = m_fData[iSrcRow][0];
    rDesVec.m_fData[1] = m_fData[iSrcRow][1];
    rDesVec.m_fData[2] = m_fData[iSrcRow][2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::SetColumn(int iDesCol, const Vector3f& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 3 );

	m_fData[0][iDesCol] = rSrcVec.m_fData[0];
	m_fData[1][iDesCol] = rSrcVec.m_fData[1];
	m_fData[2][iDesCol] = rSrcVec.m_fData[2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetColumn(int iSrcCol, Vector3f& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 3 );

	rDesVec.m_fData[0] = m_fData[0][iSrcCol];
    rDesVec.m_fData[1] = m_fData[1][iSrcCol];
    rDesVec.m_fData[2] = m_fData[2][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetTranspose(Matrix3f& rDesMat) const
{
    rDesMat.m_fData[0][0] = m_fData[0][0];
    rDesMat.m_fData[0][1] = m_fData[1][0];
    rDesMat.m_fData[0][2] = m_fData[2][0];

    rDesMat.m_fData[1][0] = m_fData[0][1];
    rDesMat.m_fData[1][1] = m_fData[1][1];
    rDesMat.m_fData[1][2] = m_fData[2][1];

    rDesMat.m_fData[2][0] = m_fData[0][2];
    rDesMat.m_fData[2][1] = m_fData[1][2];
    rDesMat.m_fData[2][2] = m_fData[2][2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetInverse(Matrix3f& rDesMat) const
{
    rDesMat[0][0] = m_fData[1][1]*m_fData[2][2] - m_fData[1][2]*m_fData[2][1];
    rDesMat[0][1] = m_fData[0][2]*m_fData[2][1] - m_fData[0][1]*m_fData[2][2];
    rDesMat[0][2] = m_fData[0][1]*m_fData[1][2] - m_fData[0][2]*m_fData[1][1];
    rDesMat[1][0] = m_fData[1][2]*m_fData[2][0] - m_fData[1][0]*m_fData[2][2];
    rDesMat[1][1] = m_fData[0][0]*m_fData[2][2] - m_fData[0][2]*m_fData[2][0];
    rDesMat[1][2] = m_fData[0][2]*m_fData[1][0] - m_fData[0][0]*m_fData[1][2];
    rDesMat[2][0] = m_fData[1][0]*m_fData[2][1] - m_fData[1][1]*m_fData[2][0];
    rDesMat[2][1] = m_fData[0][1]*m_fData[2][0] - m_fData[0][0]*m_fData[2][1];
    rDesMat[2][2] = m_fData[0][0]*m_fData[1][1] - m_fData[0][1]*m_fData[1][0];

    float fDet = m_fData[0][0]*rDesMat[0][0] + m_fData[0][1]*rDesMat[1][0] + 
        m_fData[0][2]*rDesMat[2][0];

    if( Math<float>::FAbs(fDet) <= Math<float>::ZERO_TOLERANCE )
	{
		rDesMat.Zero();
        return;
	}

    float fInvDet = 1.0f / fDet;

    rDesMat[0][0] *= fInvDet;
    rDesMat[0][1] *= fInvDet;
    rDesMat[0][2] *= fInvDet;
    rDesMat[1][0] *= fInvDet;
    rDesMat[1][1] *= fInvDet;
    rDesMat[1][2] *= fInvDet;
    rDesMat[2][0] *= fInvDet;
    rDesMat[2][1] *= fInvDet;
    rDesMat[2][2] *= fInvDet;
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetAdjoint(Matrix3f& rDesMat) const
{
    rDesMat[0][0] = m_fData[1][1]*m_fData[2][2] - m_fData[1][2]*m_fData[2][1];
    rDesMat[0][1] = m_fData[0][2]*m_fData[2][1] - m_fData[0][1]*m_fData[2][2];
    rDesMat[0][2] = m_fData[0][1]*m_fData[1][2] - m_fData[0][2]*m_fData[1][1];
    rDesMat[1][0] = m_fData[1][2]*m_fData[2][0] - m_fData[1][0]*m_fData[2][2];
    rDesMat[1][1] = m_fData[0][0]*m_fData[2][2] - m_fData[0][2]*m_fData[2][0];
    rDesMat[1][2] = m_fData[0][2]*m_fData[1][0] - m_fData[0][0]*m_fData[1][2];
    rDesMat[2][0] = m_fData[1][0]*m_fData[2][1] - m_fData[1][1]*m_fData[2][0];
    rDesMat[2][1] = m_fData[0][1]*m_fData[2][0] - m_fData[0][0]*m_fData[2][1];
    rDesMat[2][2] = m_fData[0][0]*m_fData[1][1] - m_fData[0][1]*m_fData[1][0];
}
//----------------------------------------------------------------------------
inline float Matrix3f::GetDeterminant() const
{
    float fCo00 = m_fData[1][1]*m_fData[2][2] - m_fData[1][2]*m_fData[2][1];
    float fCo10 = m_fData[1][2]*m_fData[2][0] - m_fData[1][0]*m_fData[2][2];
    float fCo20 = m_fData[1][0]*m_fData[2][1] - m_fData[1][1]*m_fData[2][0];
    float fDet = m_fData[0][0]*fCo00 + m_fData[0][1]*fCo10 + 
        m_fData[0][2]*fCo20;
    
    return fDet;
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetTimesDiagonal(const Vector3f& rDiag, 
    Matrix3f& rDesMat) const
{
    rDesMat[0][0] = m_fData[0][0] * rDiag[0];
    rDesMat[0][1] = m_fData[0][1] * rDiag[1];
    rDesMat[0][2] = m_fData[0][2] * rDiag[2];
    rDesMat[1][0] = m_fData[1][0] * rDiag[0];
    rDesMat[1][1] = m_fData[1][1] * rDiag[1];
    rDesMat[1][2] = m_fData[1][2] * rDiag[2];
    rDesMat[2][0] = m_fData[2][0] * rDiag[0];
    rDesMat[2][1] = m_fData[2][1] * rDiag[1];
    rDesMat[2][2] = m_fData[2][2] * rDiag[2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetDiagonalTimes(const Vector3f& rDiag, 
    Matrix3f& rDesMat) const
{
    rDesMat[0][0] = m_fData[0][0] * rDiag[0];
    rDesMat[0][1] = m_fData[0][1] * rDiag[0];
    rDesMat[0][2] = m_fData[0][2] * rDiag[0];
    rDesMat[1][0] = m_fData[1][0] * rDiag[1];
    rDesMat[1][1] = m_fData[1][1] * rDiag[1];
    rDesMat[1][2] = m_fData[1][2] * rDiag[1];
    rDesMat[2][0] = m_fData[2][0] * rDiag[2];
    rDesMat[2][1] = m_fData[2][1] * rDiag[2];
    rDesMat[2][2] = m_fData[2][2] * rDiag[2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetTransposeTimes(const Matrix3f& rRhsMat, 
    Matrix3f& rDesMat) const
{
    // C = A^T * B
    rDesMat.m_fData[0][0] = m_fData[0][0]*rRhsMat.m_fData[0][0] + 
                            m_fData[1][0]*rRhsMat.m_fData[1][0] + 
                            m_fData[2][0]*rRhsMat.m_fData[2][0];
    rDesMat.m_fData[0][1] = m_fData[0][0]*rRhsMat.m_fData[0][1] + 
                            m_fData[1][0]*rRhsMat.m_fData[1][1] + 
                            m_fData[2][0]*rRhsMat.m_fData[2][1];
    rDesMat.m_fData[0][2] = m_fData[0][0]*rRhsMat.m_fData[0][2] + 
                            m_fData[1][0]*rRhsMat.m_fData[1][2] + 
                            m_fData[2][0]*rRhsMat.m_fData[2][2];

    rDesMat.m_fData[1][0] = m_fData[0][1]*rRhsMat.m_fData[0][0] + 
                            m_fData[1][1]*rRhsMat.m_fData[1][0] + 
                            m_fData[2][1]*rRhsMat.m_fData[2][0];
    rDesMat.m_fData[1][1] = m_fData[0][1]*rRhsMat.m_fData[0][1] + 
                            m_fData[1][1]*rRhsMat.m_fData[1][1] + 
                            m_fData[2][1]*rRhsMat.m_fData[2][1];
    rDesMat.m_fData[1][2] = m_fData[0][1]*rRhsMat.m_fData[0][2] + 
                            m_fData[1][1]*rRhsMat.m_fData[1][2] + 
                            m_fData[2][1]*rRhsMat.m_fData[2][2];

    rDesMat.m_fData[2][0] = m_fData[0][2]*rRhsMat.m_fData[0][0] + 
                            m_fData[1][2]*rRhsMat.m_fData[1][0] + 
                            m_fData[2][2]*rRhsMat.m_fData[2][0];
    rDesMat.m_fData[2][1] = m_fData[0][2]*rRhsMat.m_fData[0][1] + 
                            m_fData[1][2]*rRhsMat.m_fData[1][1] + 
                            m_fData[2][2]*rRhsMat.m_fData[2][1];
    rDesMat.m_fData[2][2] = m_fData[0][2]*rRhsMat.m_fData[0][2] + 
                            m_fData[1][2]*rRhsMat.m_fData[1][2] + 
                            m_fData[2][2]*rRhsMat.m_fData[2][2];
}
//----------------------------------------------------------------------------
inline void Matrix3f::GetTimesTranspose(const Matrix3f& rRhsMat, 
    Matrix3f& rDesMat) const
{
    // C = A * B^T
    rDesMat.m_fData[0][0] = m_fData[0][0]*rRhsMat.m_fData[0][0] + 
                            m_fData[0][1]*rRhsMat.m_fData[0][1] + 
                            m_fData[0][2]*rRhsMat.m_fData[0][2];
    rDesMat.m_fData[0][1] = m_fData[0][0]*rRhsMat.m_fData[1][0] + 
                            m_fData[0][1]*rRhsMat.m_fData[1][1] + 
                            m_fData[0][2]*rRhsMat.m_fData[1][2];
    rDesMat.m_fData[0][2] = m_fData[0][0]*rRhsMat.m_fData[2][0] + 
                            m_fData[0][1]*rRhsMat.m_fData[2][1] + 
                            m_fData[0][2]*rRhsMat.m_fData[2][2];

    rDesMat.m_fData[1][0] = m_fData[1][0]*rRhsMat.m_fData[0][0] + 
                            m_fData[1][1]*rRhsMat.m_fData[0][1] + 
                            m_fData[1][2]*rRhsMat.m_fData[0][2];
    rDesMat.m_fData[1][1] = m_fData[1][0]*rRhsMat.m_fData[1][0] + 
                            m_fData[1][1]*rRhsMat.m_fData[1][1] + 
                            m_fData[1][2]*rRhsMat.m_fData[1][2];
    rDesMat.m_fData[1][2] = m_fData[1][0]*rRhsMat.m_fData[2][0] + 
                            m_fData[1][1]*rRhsMat.m_fData[2][1] + 
                            m_fData[1][2]*rRhsMat.m_fData[2][2];

    rDesMat.m_fData[2][0] = m_fData[2][0]*rRhsMat.m_fData[0][0] + 
                            m_fData[2][1]*rRhsMat.m_fData[0][1] + 
                            m_fData[2][2]*rRhsMat.m_fData[0][2];
    rDesMat.m_fData[2][1] = m_fData[2][0]*rRhsMat.m_fData[1][0] + 
                            m_fData[2][1]*rRhsMat.m_fData[1][1] + 
                            m_fData[2][2]*rRhsMat.m_fData[1][2];
    rDesMat.m_fData[2][2] = m_fData[2][0]*rRhsMat.m_fData[2][0] + 
                            m_fData[2][1]*rRhsMat.m_fData[2][1] + 
                            m_fData[2][2]*rRhsMat.m_fData[2][2];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度3阶方阵类
//----------------------------------------------------------------------------
inline double Matrix3d::M11(void) const
{
    return m_dData[0][0];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M11(void)
{
    return m_dData[0][0];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M12(void) const
{
    return m_dData[0][1];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M12(void)
{
    return m_dData[0][1];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M13(void) const
{
    return m_dData[0][2];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M13(void)
{
    return m_dData[0][2];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M21(void) const
{
    return m_dData[1][0];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M21(void)
{
    return m_dData[1][0];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M22(void) const
{
    return m_dData[1][1];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M22(void)
{
    return m_dData[1][1];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M23(void) const
{
    return m_dData[1][2];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M23(void)
{
    return m_dData[1][2];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M31(void) const
{
    return m_dData[2][0];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M31(void)
{
    return m_dData[2][0];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M32(void) const
{
    return m_dData[2][1];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M32(void)
{
    return m_dData[2][1];
}
//----------------------------------------------------------------------------
inline double Matrix3d::M33(void) const
{
    return m_dData[2][2];
}
//----------------------------------------------------------------------------
inline double& Matrix3d::M33(void)
{
    return m_dData[2][2];
}
//----------------------------------------------------------------------------
inline int Matrix3d::CompareData(const Matrix3d& rMat) const
{
    return memcmp(m_dData, rMat.m_dData, /*12*/9*sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix3d::Zero()
{
    memset(m_dData, 0, /*12*/9*sizeof(double));
}
//----------------------------------------------------------------------------
inline void Matrix3d::Identity()
{
    m_dData[0][0] = 1.0;
    m_dData[0][1] = 0.0;
    m_dData[0][2] = 0.0;
    m_dData[1][0] = 0.0;
    m_dData[1][1] = 1.0;
    m_dData[1][2] = 0.0;
    m_dData[2][0] = 0.0;
    m_dData[2][1] = 0.0;
    m_dData[2][2] = 1.0;
}
//----------------------------------------------------------------------------
inline void Matrix3d::Diagonal(double dM11, double dM22, double dM33)
{
    m_dData[0][0] = dM11;
    m_dData[0][1] = 0.0;
    m_dData[0][2] = 0.0;
    m_dData[1][0] = 0.0;
    m_dData[1][1] = dM22;
    m_dData[1][2] = 0.0;
    m_dData[2][0] = 0.0;
    m_dData[2][1] = 0.0;
    m_dData[2][2] = dM33;
}
//----------------------------------------------------------------------------
inline void Matrix3d::FromAxisAngle(const Vector3d& rAxisVec, double dAngle)
{
    // 旋转轴向量为W(w0,w1,w2),且w0^2 + w1^2 + w2^2 = 1,
    // R = I + sin(theta)S + (1 - cos(theta))S^2,
    // I为单位矩阵,
    // S为反对称矩阵:
    // S =   0,   w2,   -w1,
    //     -w2,    0,    w0,
    //      w1,  -w0,     0,

    double dCos = Math<double>::Cos(dAngle);
    double dSin = Math<double>::Sin(dAngle);
    double dOneMinusCos = 1.0 - dCos;

    double dX2 = rAxisVec[0] * rAxisVec[0];
    double dY2 = rAxisVec[1] * rAxisVec[1];
    double dZ2 = rAxisVec[2] * rAxisVec[2];
    double dXYM = rAxisVec[0] * rAxisVec[1] * dOneMinusCos;
    double dXZM = rAxisVec[0] * rAxisVec[2] * dOneMinusCos;
    double dYZM = rAxisVec[1] * rAxisVec[2] * dOneMinusCos;
    double dXSin = rAxisVec[0] * dSin;
    double dYSin = rAxisVec[1] * dSin;
    double dZSin = rAxisVec[2] * dSin;
    
    m_dData[0][0] = dX2*dOneMinusCos + dCos;
    m_dData[1][0] = dXYM - dZSin;
    m_dData[2][0] = dXZM + dYSin;

    m_dData[0][1] = dXYM + dZSin;
    m_dData[1][1] = dY2*dOneMinusCos + dCos;
    m_dData[2][1] = dYZM - dXSin;

    m_dData[0][2] = dXZM - dYSin;
    m_dData[1][2] = dYZM + dXSin;
    m_dData[2][2] = dZ2*dOneMinusCos + dCos;
}
//----------------------------------------------------------------------------
inline void Matrix3d::ToAxisAngle(Vector3d& rAxisVec, double& rdAngle) const
{
    // 旋转轴向量为W(w0,w1,w2),且w0^2 + w1^2 + w2^2 = 1,
    // R = I + sin(theta)S + (1 - cos(theta))S^2,
    // I为单位矩阵,
    // S为反对称矩阵:
    // S =   0,   w2,   -w1,
    //     -w2,    0,    w0,
    //      w1,  -w0,     0,
    //
    // cos(theta) = (trace(R) - 1) / 2,且R - R^T = 2 * sin(theta) * S
    // theta = acos((trace(R) - 1) / 2)
    //
    // (1) theta = 0,则R = R^T,因此任何单位向量都可以作为旋转轴
    // (2) theta > 0,则R - R^T = 2sin(theta)S,
    //     W = (S12,S20,S01) / |(S12,S20,S01)|
    // (3) theta = pi,则S^2 = (R - I) / 2,
    //     S^2的对角元素为w0^2 - 1, w1^2 - 1,w2^2 - 1,因此可以解出w0,w1,w2

    double dTrace = m_dData[0][0] + m_dData[1][1] + m_dData[2][2];
    double dCos = 0.5 * (dTrace - 1.0);
    rdAngle = Math<double>::ACos(dCos);  // [0,PI]

    if( rdAngle > 0.0 )
    {
        if( rdAngle < Math<double>::PI )
        {
            // W = (S12,S20,S01) / |(S12,S20,S01)| 
            rAxisVec[0] = m_dData[1][2] - m_dData[2][1];
            rAxisVec[1] = m_dData[2][0] - m_dData[0][2];
            rAxisVec[2] = m_dData[0][1] - m_dData[1][0];

            rAxisVec.Normalize();
        }
        else
        {
            // theta = pi
            // 为减小误差和避免除0问题,
            // 从r00,r11,r22中最大者解出旋转轴最大分量,进而获取剩余分量

            double dHalfInverse;
            if( m_dData[0][0] >= m_dData[1][1] )
            {
                // r00 >= r11
                if( m_dData[0][0] >= m_dData[2][2] )
                {
                    // r00是最大对角元素
                    rAxisVec[0] = 0.5*Math<double>::Sqrt(m_dData[0][0] - 
                        m_dData[1][1] - m_dData[2][2] + 1.0);
                    dHalfInverse = 0.5 / rAxisVec[0];
                    rAxisVec[1] = dHalfInverse * m_dData[0][1];
                    rAxisVec[2] = dHalfInverse * m_dData[0][2];
                }
                else
                {
                    // r22是最大对角元素
                    rAxisVec[2] = 0.5*Math<double>::Sqrt(m_dData[2][2] - 
                        m_dData[0][0] - m_dData[1][1] + 1.0);
                    dHalfInverse = 0.5 / rAxisVec[2];
                    rAxisVec[0] = dHalfInverse*m_dData[0][2];
                    rAxisVec[1] = dHalfInverse*m_dData[1][2];
                }
            }
            else
            {
                // r11 > r00
                if( m_dData[1][1] >= m_dData[2][2] )
                {
                    // r11是最大对角元素
                    rAxisVec[1] = 0.5*Math<double>::Sqrt(m_dData[1][1] - 
                        m_dData[0][0] - m_dData[2][2] + 1.0);
                    dHalfInverse  = 0.5 / rAxisVec[1];
                    rAxisVec[0] = dHalfInverse * m_dData[0][1];
                    rAxisVec[2] = dHalfInverse * m_dData[1][2];
                }
                else
                {
                    // r22是最大对角元素
                    rAxisVec[2] = 0.5*Math<double>::Sqrt(m_dData[2][2] - 
                        m_dData[0][0] - m_dData[1][1] + 1.0);
                    dHalfInverse = 0.5 / rAxisVec[2];
                    rAxisVec[0] = dHalfInverse * m_dData[0][2];
                    rAxisVec[1] = dHalfInverse * m_dData[1][2];
                }
            }
        }
    }
    else
    {
        // theta = 0时,任何旋转轴都可以

        rAxisVec[0] = 1.0;
        rAxisVec[1] = 0.0;
        rAxisVec[2] = 0.0;
    }
}
//----------------------------------------------------------------------------
inline void Matrix3d::TensorProduct(const Vector3d& rVecU, 
    const Vector3d& rVecV)
{
    m_dData[0][0] = rVecU[0] * rVecV[0];
    m_dData[0][1] = rVecU[0] * rVecV[1];
    m_dData[0][2] = rVecU[0] * rVecV[2];
    m_dData[1][0] = rVecU[1] * rVecV[0];
    m_dData[1][1] = rVecU[1] * rVecV[1];
    m_dData[1][2] = rVecU[1] * rVecV[2];
    m_dData[2][0] = rVecU[2] * rVecV[0];
    m_dData[2][1] = rVecU[2] * rVecV[1];
    m_dData[2][2] = rVecU[2] * rVecV[2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::SetRow(int iDesRow, const Vector3d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesRow && iDesRow < 3 );

	m_dData[iDesRow][0] = rSrcVec.m_dData[0];
    m_dData[iDesRow][1] = rSrcVec.m_dData[1];
    m_dData[iDesRow][2] = rSrcVec.m_dData[2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetRow(int iSrcRow, Vector3d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcRow && iSrcRow < 3 );

    rDesVec.m_dData[0] = m_dData[iSrcRow][0];
    rDesVec.m_dData[1] = m_dData[iSrcRow][1];
    rDesVec.m_dData[2] = m_dData[iSrcRow][2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::SetColumn(int iDesCol, const Vector3d& rSrcVec)
{
    SE_ASSERT( 0 <= iDesCol && iDesCol < 3 );

	m_dData[0][iDesCol] = rSrcVec.m_dData[0];
	m_dData[1][iDesCol] = rSrcVec.m_dData[1];
	m_dData[2][iDesCol] = rSrcVec.m_dData[2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetColumn(int iSrcCol, Vector3d& rDesVec) const
{
    SE_ASSERT( 0 <= iSrcCol && iSrcCol < 3 );

	rDesVec.m_dData[0] = m_dData[0][iSrcCol];
    rDesVec.m_dData[1] = m_dData[1][iSrcCol];
    rDesVec.m_dData[2] = m_dData[2][iSrcCol];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetTranspose(Matrix3d& rDesMat) const
{
    rDesMat.m_dData[0][0] = m_dData[0][0];
    rDesMat.m_dData[0][1] = m_dData[1][0];
    rDesMat.m_dData[0][2] = m_dData[2][0];

    rDesMat.m_dData[1][0] = m_dData[0][1];
    rDesMat.m_dData[1][1] = m_dData[1][1];
    rDesMat.m_dData[1][2] = m_dData[2][1];

    rDesMat.m_dData[2][0] = m_dData[0][2];
    rDesMat.m_dData[2][1] = m_dData[1][2];
    rDesMat.m_dData[2][2] = m_dData[2][2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetInverse(Matrix3d& rDesMat) const
{
    rDesMat[0][0] = m_dData[1][1]*m_dData[2][2] - m_dData[1][2]*m_dData[2][1];
    rDesMat[0][1] = m_dData[0][2]*m_dData[2][1] - m_dData[0][1]*m_dData[2][2];
    rDesMat[0][2] = m_dData[0][1]*m_dData[1][2] - m_dData[0][2]*m_dData[1][1];
    rDesMat[1][0] = m_dData[1][2]*m_dData[2][0] - m_dData[1][0]*m_dData[2][2];
    rDesMat[1][1] = m_dData[0][0]*m_dData[2][2] - m_dData[0][2]*m_dData[2][0];
    rDesMat[1][2] = m_dData[0][2]*m_dData[1][0] - m_dData[0][0]*m_dData[1][2];
    rDesMat[2][0] = m_dData[1][0]*m_dData[2][1] - m_dData[1][1]*m_dData[2][0];
    rDesMat[2][1] = m_dData[0][1]*m_dData[2][0] - m_dData[0][0]*m_dData[2][1];
    rDesMat[2][2] = m_dData[0][0]*m_dData[1][1] - m_dData[0][1]*m_dData[1][0];

    double dDet = m_dData[0][0]*rDesMat[0][0] + m_dData[0][1]*rDesMat[1][0] + 
        m_dData[0][2]*rDesMat[2][0];

    if( Math<double>::FAbs(dDet) <= Math<double>::ZERO_TOLERANCE )
	{
		rDesMat.Zero();
        return;
	}

    double dInvDet = 1.0 / dDet;

    rDesMat[0][0] *= dInvDet;
    rDesMat[0][1] *= dInvDet;
    rDesMat[0][2] *= dInvDet;
    rDesMat[1][0] *= dInvDet;
    rDesMat[1][1] *= dInvDet;
    rDesMat[1][2] *= dInvDet;
    rDesMat[2][0] *= dInvDet;
    rDesMat[2][1] *= dInvDet;
    rDesMat[2][2] *= dInvDet;
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetAdjoint(Matrix3d& rDesMat) const
{
    rDesMat[0][0] = m_dData[1][1]*m_dData[2][2] - m_dData[1][2]*m_dData[2][1];
    rDesMat[0][1] = m_dData[0][2]*m_dData[2][1] - m_dData[0][1]*m_dData[2][2];
    rDesMat[0][2] = m_dData[0][1]*m_dData[1][2] - m_dData[0][2]*m_dData[1][1];
    rDesMat[1][0] = m_dData[1][2]*m_dData[2][0] - m_dData[1][0]*m_dData[2][2];
    rDesMat[1][1] = m_dData[0][0]*m_dData[2][2] - m_dData[0][2]*m_dData[2][0];
    rDesMat[1][2] = m_dData[0][2]*m_dData[1][0] - m_dData[0][0]*m_dData[1][2];
    rDesMat[2][0] = m_dData[1][0]*m_dData[2][1] - m_dData[1][1]*m_dData[2][0];
    rDesMat[2][1] = m_dData[0][1]*m_dData[2][0] - m_dData[0][0]*m_dData[2][1];
    rDesMat[2][2] = m_dData[0][0]*m_dData[1][1] - m_dData[0][1]*m_dData[1][0];
}
//----------------------------------------------------------------------------
inline double Matrix3d::GetDeterminant() const
{
    double dCo00 = m_dData[1][1]*m_dData[2][2] - m_dData[1][2]*m_dData[2][1];
    double dCo10 = m_dData[1][2]*m_dData[2][0] - m_dData[1][0]*m_dData[2][2];
    double dCo20 = m_dData[1][0]*m_dData[2][1] - m_dData[1][1]*m_dData[2][0];
    double dDet = m_dData[0][0]*dCo00 + m_dData[0][1]*dCo10 + 
        m_dData[0][2]*dCo20;
    
    return dDet;
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetTimesDiagonal(const Vector3d& rDiag, 
    Matrix3d& rDesMat) const
{
    rDesMat[0][0] = m_dData[0][0] * rDiag[0];
    rDesMat[0][1] = m_dData[0][1] * rDiag[1];
    rDesMat[0][2] = m_dData[0][2] * rDiag[2];
    rDesMat[1][0] = m_dData[1][0] * rDiag[0];
    rDesMat[1][1] = m_dData[1][1] * rDiag[1];
    rDesMat[1][2] = m_dData[1][2] * rDiag[2];
    rDesMat[2][0] = m_dData[2][0] * rDiag[0];
    rDesMat[2][1] = m_dData[2][1] * rDiag[1];
    rDesMat[2][2] = m_dData[2][2] * rDiag[2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetDiagonalTimes(const Vector3d& rDiag, 
    Matrix3d& rDesMat) const
{
    rDesMat[0][0] = m_dData[0][0] * rDiag[0];
    rDesMat[0][1] = m_dData[0][1] * rDiag[0];
    rDesMat[0][2] = m_dData[0][2] * rDiag[0];
    rDesMat[1][0] = m_dData[1][0] * rDiag[1];
    rDesMat[1][1] = m_dData[1][1] * rDiag[1];
    rDesMat[1][2] = m_dData[1][2] * rDiag[1];
    rDesMat[2][0] = m_dData[2][0] * rDiag[2];
    rDesMat[2][1] = m_dData[2][1] * rDiag[2];
    rDesMat[2][2] = m_dData[2][2] * rDiag[2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetTransposeTimes(const Matrix3d& rRhsMat, 
    Matrix3d& rDesMat) const
{
    // C = A^T * B
    rDesMat.m_dData[0][0] = m_dData[0][0]*rRhsMat.m_dData[0][0] + 
                            m_dData[1][0]*rRhsMat.m_dData[1][0] + 
                            m_dData[2][0]*rRhsMat.m_dData[2][0];
    rDesMat.m_dData[0][1] = m_dData[0][0]*rRhsMat.m_dData[0][1] + 
                            m_dData[1][0]*rRhsMat.m_dData[1][1] + 
                            m_dData[2][0]*rRhsMat.m_dData[2][1];
    rDesMat.m_dData[0][2] = m_dData[0][0]*rRhsMat.m_dData[0][2] + 
                            m_dData[1][0]*rRhsMat.m_dData[1][2] + 
                            m_dData[2][0]*rRhsMat.m_dData[2][2];

    rDesMat.m_dData[1][0] = m_dData[0][1]*rRhsMat.m_dData[0][0] + 
                            m_dData[1][1]*rRhsMat.m_dData[1][0] + 
                            m_dData[2][1]*rRhsMat.m_dData[2][0];
    rDesMat.m_dData[1][1] = m_dData[0][1]*rRhsMat.m_dData[0][1] + 
                            m_dData[1][1]*rRhsMat.m_dData[1][1] + 
                            m_dData[2][1]*rRhsMat.m_dData[2][1];
    rDesMat.m_dData[1][2] = m_dData[0][1]*rRhsMat.m_dData[0][2] + 
                            m_dData[1][1]*rRhsMat.m_dData[1][2] + 
                            m_dData[2][1]*rRhsMat.m_dData[2][2];

    rDesMat.m_dData[2][0] = m_dData[0][2]*rRhsMat.m_dData[0][0] + 
                            m_dData[1][2]*rRhsMat.m_dData[1][0] + 
                            m_dData[2][2]*rRhsMat.m_dData[2][0];
    rDesMat.m_dData[2][1] = m_dData[0][2]*rRhsMat.m_dData[0][1] + 
                            m_dData[1][2]*rRhsMat.m_dData[1][1] + 
                            m_dData[2][2]*rRhsMat.m_dData[2][1];
    rDesMat.m_dData[2][2] = m_dData[0][2]*rRhsMat.m_dData[0][2] + 
                            m_dData[1][2]*rRhsMat.m_dData[1][2] + 
                            m_dData[2][2]*rRhsMat.m_dData[2][2];
}
//----------------------------------------------------------------------------
inline void Matrix3d::GetTimesTranspose(const Matrix3d& rRhsMat, 
    Matrix3d& rDesMat) const
{
    // C = A * B^T
    rDesMat.m_dData[0][0] = m_dData[0][0]*rRhsMat.m_dData[0][0] + 
                            m_dData[0][1]*rRhsMat.m_dData[0][1] + 
                            m_dData[0][2]*rRhsMat.m_dData[0][2];
    rDesMat.m_dData[0][1] = m_dData[0][0]*rRhsMat.m_dData[1][0] + 
                            m_dData[0][1]*rRhsMat.m_dData[1][1] + 
                            m_dData[0][2]*rRhsMat.m_dData[1][2];
    rDesMat.m_dData[0][2] = m_dData[0][0]*rRhsMat.m_dData[2][0] + 
                            m_dData[0][1]*rRhsMat.m_dData[2][1] + 
                            m_dData[0][2]*rRhsMat.m_dData[2][2];

    rDesMat.m_dData[1][0] = m_dData[1][0]*rRhsMat.m_dData[0][0] + 
                            m_dData[1][1]*rRhsMat.m_dData[0][1] + 
                            m_dData[1][2]*rRhsMat.m_dData[0][2];
    rDesMat.m_dData[1][1] = m_dData[1][0]*rRhsMat.m_dData[1][0] + 
                            m_dData[1][1]*rRhsMat.m_dData[1][1] + 
                            m_dData[1][2]*rRhsMat.m_dData[1][2];
    rDesMat.m_dData[1][2] = m_dData[1][0]*rRhsMat.m_dData[2][0] + 
                            m_dData[1][1]*rRhsMat.m_dData[2][1] + 
                            m_dData[1][2]*rRhsMat.m_dData[2][2];

    rDesMat.m_dData[2][0] = m_dData[2][0]*rRhsMat.m_dData[0][0] + 
                            m_dData[2][1]*rRhsMat.m_dData[0][1] + 
                            m_dData[2][2]*rRhsMat.m_dData[0][2];
    rDesMat.m_dData[2][1] = m_dData[2][0]*rRhsMat.m_dData[1][0] + 
                            m_dData[2][1]*rRhsMat.m_dData[1][1] + 
                            m_dData[2][2]*rRhsMat.m_dData[1][2];
    rDesMat.m_dData[2][2] = m_dData[2][0]*rRhsMat.m_dData[2][0] + 
                            m_dData[2][1]*rRhsMat.m_dData[2][1] + 
                            m_dData[2][2]*rRhsMat.m_dData[2][2];
}
//----------------------------------------------------------------------------