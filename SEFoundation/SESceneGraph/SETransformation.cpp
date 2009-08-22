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
#include "SETransformation.h"

using namespace Swing;

const Transformation Transformation::IDENTITY;

//----------------------------------------------------------------------------
Transformation::Transformation()
    :
    m_Matrix(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
    m_Translate(0.0f, 0.0f, 0.0f),
    m_Scale(1.0f, 1.0f, 1.0f)
{
    m_bIsIdentity = true;
    m_bIsSRMatrix = true;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
Transformation::~Transformation()
{
}
//----------------------------------------------------------------------------
void Transformation::Identity()
{
    m_Matrix = Matrix3f::IDENTITY;
    m_Translate = Vector3f::ZERO;
    m_Scale = Vector3f(1.0f, 1.0f, 1.0f);
    m_bIsIdentity = true;
    m_bIsSRMatrix = true;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
void Transformation::UnitScale()
{
    SE_ASSERT( m_bIsSRMatrix );

    m_Scale = Vector3f(1.0f, 1.0f, 1.0f);
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
float Transformation::GetNorm() const
{
    if( m_bIsSRMatrix )
    {
        float fMax = Mathf::FAbs(m_Scale.X);
        if( Mathf::FAbs(m_Scale.Y) > fMax )
            fMax = Mathf::FAbs(m_Scale.Y);
        if( Mathf::FAbs(m_Scale.Z) > fMax )
            fMax = Mathf::FAbs(m_Scale.Z);
        return fMax;
    }

    float fMaxColSum =
        Mathf::FAbs(m_Matrix[0][0]) +
        Mathf::FAbs(m_Matrix[1][0]) +
        Mathf::FAbs(m_Matrix[2][0]);

    float fColSum =
        Mathf::FAbs(m_Matrix[0][1]) +
        Mathf::FAbs(m_Matrix[1][1]) +
        Mathf::FAbs(m_Matrix[2][1]);

    if( fColSum > fMaxColSum )
        fMaxColSum = fColSum;

    fColSum =
        Mathf::FAbs(m_Matrix[0][2]) +
        Mathf::FAbs(m_Matrix[1][2]) +
        Mathf::FAbs(m_Matrix[2][2]);

    if( fColSum > fMaxColSum )
        fMaxColSum = fColSum;

    return fMaxColSum;
}
//----------------------------------------------------------------------------
void Transformation::SetRotate(const Matrix3f& rRotate)
{
    m_Matrix = rRotate;
    m_bIsIdentity = false;
    m_bIsSRMatrix = true;
}
//----------------------------------------------------------------------------
void Transformation::SetTranslate(const Vector3f& rTranslate)
{
    m_Translate = rTranslate;
    m_bIsIdentity = false;
}
//----------------------------------------------------------------------------
void Transformation::SetScale(const Vector3f& rScale)
{
    SE_ASSERT( m_bIsSRMatrix && rScale.X != 0.0f && rScale.Y != 0.0f &&
        rScale.Z != 0.0f );

    m_Scale = rScale;
    m_bIsIdentity = false;
    m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
void Transformation::SetUniformScale(float fScale)
{
    SE_ASSERT( m_bIsSRMatrix && fScale != 0.0f );

    m_Scale = Vector3f(fScale, fScale, fScale);
    m_bIsIdentity = false;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
void Transformation::SetMatrix(const Matrix3f& rMatrix)
{
    m_Matrix = rMatrix;
    m_bIsIdentity = false;
    m_bIsSRMatrix = false;
    m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
void Transformation::ApplyForward(const Vector3f& rInput, Vector3f& rOutput)
    const
{
    if( m_bIsIdentity )
    {
        // Y = X
        rOutput = rInput;
        return;
    }

    if( m_bIsSRMatrix )
    {
        // Y = X*S*R + T
		rOutput.X = m_Scale.X * rInput.X;
		rOutput.Y = m_Scale.Y * rInput.Y;
		rOutput.Z = m_Scale.Z * rInput.Z;
        rOutput = rOutput*m_Matrix + m_Translate;
        return;
    }

    // Y = X*M + T
    rOutput = rInput*m_Matrix + m_Translate;
}
//----------------------------------------------------------------------------
void Transformation::ApplyForward(int iCount, const Vector3f* aInput,
    Vector3f* aOutput) const
{
    if( m_bIsIdentity )
    {
        // Y = X
        memcpy(aOutput, aInput, iCount * sizeof(Vector3f));
    }
    else
    {
        int i;
        if( m_bIsSRMatrix )
        {
            // Y = X*S*R + T
            for( i = 0; i < iCount; i++ )
            {
                aOutput[i].X = m_Scale.X * aInput[i].X;
                aOutput[i].Y = m_Scale.Y * aInput[i].Y;
                aOutput[i].Z = m_Scale.Z * aInput[i].Z;
                aOutput[i] = aOutput[i]*m_Matrix + m_Translate;
            }
        }
        else
        {
            // Y = X*M + T
            for( i = 0; i < iCount; i++ )
            {
                aOutput[i] = aInput[i]*m_Matrix + m_Translate;
            }
        }
    }
}
//----------------------------------------------------------------------------
void Transformation::ApplyInverse(const Vector3f& rInput, Vector3f& rOutput)
    const
{
    if( m_bIsIdentity )
    {
        // X = Y
        rOutput = rInput;
        return;
    }

    rOutput = rInput - m_Translate;
    if( m_bIsSRMatrix )
    {
        // X = (Y-T)*R^T*S^{-1}
        rOutput = m_Matrix * rOutput;
        if( m_bIsUniformScale )
        {
            rOutput /= GetUniformScale();
        }
        else
        {
            // 获取非统一缩放变换的逆变换如下
            //   rOutput.X /= m_Scale.X;
            //   rOutput.Y /= m_Scale.Y;
            //   rOutput.Z /= m_Scale.Z;
            // 使用了一个除法替换的技巧,
            // 3次除法被替换成1次除法和9次乘法,
            // 对于Intel Pentium级别CPU来说,
            // 除法将占用39个时钟周期,乘法只需要3个时钟周期.
            float fSXY = m_Scale.X * m_Scale.Y;
            float fSXYZ = fSXY * m_Scale.Z;
            float fInvSXYZ = 1.0f / fSXYZ;
            float fInvSXY = fInvSXYZ * m_Scale.Z;
            float fInvXScale = fInvSXY * m_Scale.Y;
            float fInvYScale = fInvSXY * m_Scale.X;
            float fInvZScale = fInvSXYZ * fSXY;
            rOutput.X *= fInvXScale;
            rOutput.Y *= fInvYScale;
            rOutput.Z *= fInvZScale;
        }
    }
    else
    {
        // X = (Y-T)*M^{-1}
        Matrix3f InvMat;
		m_Matrix.GetInverse(InvMat);
        rOutput = rOutput * InvMat;
    }
}
//----------------------------------------------------------------------------
void Transformation::ApplyInverse(int iCount, const Vector3f* aInput,
    Vector3f* aOutput) const
{
    if( m_bIsIdentity )
    {
        // X = Y
        memcpy(aOutput, aInput, iCount * sizeof(Vector3f));
        return;
    }

    Vector3f tempVec;
    int i;
    if( m_bIsSRMatrix )
    {
        // X = (Y-T)*R^T*S^{-1}
        if( m_bIsUniformScale )
        {
            float fInvScale = 1.0f / GetUniformScale();
            for( i = 0; i < iCount; i++ )
            {
                tempVec = aInput[i] - m_Translate;
				aOutput[i] = fInvScale * (m_Matrix * tempVec);
            }
        }
        else
        {
            float fSXY = m_Scale.X * m_Scale.Y;
            float fSXYZ = fSXY * m_Scale.Z;
            float fInvSXYZ = 1.0f / fSXYZ;
            float fInvSXY = fInvSXYZ * m_Scale.Z;
            float fInvXScale = fInvSXY * m_Scale.Y;
            float fInvYScale = fInvSXY * m_Scale.X;
            float fInvZScale = fInvSXYZ * fSXY;
            for( i = 0; i < iCount; i++ )
            {
                tempVec = aInput[i] - m_Translate;
                aOutput[i] = m_Matrix * tempVec;
                aOutput[i].X *= fInvXScale;
                aOutput[i].Y *= fInvYScale;
                aOutput[i].Z *= fInvZScale;
            }
        }
    }
    else
    {
        // X = (Y-T)*M^{-1}
        Matrix3f InvMat; 
        m_Matrix.GetInverse(InvMat);
        for( i = 0; i < iCount; i++ )
        {
            tempVec = aInput[i] - m_Translate;
            aOutput[i] = tempVec * InvMat;
        }
    }
}
//----------------------------------------------------------------------------
void Transformation::InvertVector(const Vector3f& rInput, Vector3f& rOutput)
    const
{
    if( m_bIsIdentity )
    {
        // X = Y
        rOutput = rInput;
        return;
    }

    if( m_bIsSRMatrix )
    {
        // X = Y*R^T*S^{-1}
        rOutput = m_Matrix * rInput;
        if( m_bIsUniformScale )
        {
            rOutput /= GetUniformScale();
        }
        else
        {
            float fSXY = m_Scale.X * m_Scale.Y;
            float fSXYZ = fSXY * m_Scale.Z;
            float fInvSXYZ = 1.0f / fSXYZ;
            float fInvSXY = fInvSXYZ * m_Scale.Z;
            float fInvXScale = fInvSXY * m_Scale.Y;
            float fInvYScale = fInvSXY * m_Scale.X;
            float fInvZScale = fInvSXYZ * fSXY;
            rOutput.X *= fInvXScale;
            rOutput.Y *= fInvYScale;
            rOutput.Z *= fInvZScale;
        }
    }
    else
    {
        // X = Y*M^{-1}
        Matrix3f InvMat;
        m_Matrix.GetInverse(InvMat);
        rOutput = rInput * InvMat;
    }
}
//----------------------------------------------------------------------------
void Transformation::ApplyForward(const Plane3f& rInput, Plane3f& rOutput)
    const
{
    if( m_bIsIdentity )
    {
        rOutput = rInput;
        return;
    }

    if( m_bIsSRMatrix )
    {
        // 对于SRT情况
        // 设X表示模型空间平面上任意一点,Y = X*S*R + T表示世界空间平面上任意
        // 一点,S是世界缩放变换,R是世界旋转变换,T是世界平移变换.
        // 世界空间到模型空间的逆变换为X = (Y-T)*R^T*S^{-1}.
        // 模型空间的平面方程为dot(N0,X) = C0.将X替换为Y的方程,则可推导出
        // 世界空间的平面方程为dot(N1,Y) = C1.
        // 其中N1 = N0*S^{-1}*R,C1 = C0 + dot(N1,T).如果S不是单位矩阵,
        // 则N1将不是单位向量,因此需要规范化N1并且调整C1:N1' = N1/|N1|,
        // C1' = C1/|N1|.
        if( m_bIsUniformScale )
        {
            // N1 = N0*S^{-1}*R,由于统一缩放变换不会改变向量的空间方向姿态,
            // 因此只需对向量施加旋转变换
            // 此时上式等价为N1 = N0*R
            rOutput.Normal = rInput.Normal * m_Matrix;
            // C1 = (C0 / |N0*S^{-1}*R|) + dot(N1,T) (1)
            // 由于旋转变换不会改变向量长度,因此|N0*S^{-1}*R| = |N0*S^{-1}|,
            // 又因为是统一缩放变换且N0是单位向量,
            // 因此|N0*S^{-1}| = 1.0f / GetUniformScale().
            // 因此式(1)等价为C1 = C0 * GetUniformScale() + dot(N1,T).
            rOutput.Constant = GetUniformScale() * rInput.Constant +
                rOutput.Normal.Dot(m_Translate);

            return;
        }

        rOutput.Normal = rInput.Normal;

        // 如果是非统一缩放变换,则向量的空间方向姿态将会受到影响,
        // 因此需施加非统一缩放变换的逆变换与旋转变换
        float fSXY = m_Scale.X * m_Scale.Y;
        float fSXYZ = fSXY * m_Scale.Z;
        float fInvSXYZ = 1.0f / fSXYZ;
        float fInvSXY = fInvSXYZ * m_Scale.Z;
        float fInvXScale = fInvSXY * m_Scale.Y;
        float fInvYScale = fInvSXY * m_Scale.X;
        float fInvZScale = fInvSXYZ * fSXY;
        rOutput.Normal.X *= fInvXScale;
        rOutput.Normal.Y *= fInvYScale;
        rOutput.Normal.Z *= fInvZScale;
        rOutput.Normal = rOutput.Normal * m_Matrix;
    }
    else
    {
        // 对于一般MT情况,
        // 设X表示模型空间平面上任意一点,
        // Y = X*M + T表示世界空间平面上任意一点,M是任意综合变换,
        // 世界空间到模型空间的逆变换为X = (Y-T)*M^{-1}.
        // 模型空间的平面方程为dot(N0,X) = C0.将X替换为Y的方程,则可推导出
        // 世界空间的平面方程为dot(N1,Y) = C1.
        // 推导过程:
        // (1) dot(N0,X) = C0 => dot(N0,(Y-T)*M^{-1}) = C0
        // (2) dot(N0,(Y-T)*M^{-1}) = C0 => 
        //     dot(N0,Y*M^{-1}) - dot(N0,T*M^{-1}) = C0
        // (3) dot(N0,Y*M^{-1}) - dot(N0,T*M^{-1}) = C0 =>
        //     dot(N0,(M^{-1})^T*Y) = C0 + dot(N0,T*M^{-1})
        // (4) dot(N0,(M^{-1})^T*Y) = C0 + dot(N0,T*M^{-1}) =>
        //     N0*(M^{-1})^T*Y = C0 + N0*M^{-1}^T*T
        // 此时N0*(M^{-1})^T就是世界空间平面的法线,
        // 对等式(4)两边同时除以该法线的模,得到最终N1为单位向量
        // 因此N1 = N0*M^{-T} / |N0*M^{-1}| (-T表示求逆后转置),
        // C1 = (C0 / |N0*M^{-1}|) + dot(N1,T).
        // 注意DirectX中的D3DXPlaneTransform*函数也是基于此数学原理,
        // 因此D3DXPlaneTransform*函数要求传入的综合变换矩阵为:
        // 该矩阵的逆矩阵的转置矩阵.
        Matrix3f InvMat;
        m_Matrix.GetInverse(InvMat);
        rOutput.Normal = InvMat * rInput.Normal;
    }

    float fInvLength = 1.0f / rOutput.Normal.GetLength();
    rOutput.Normal *= fInvLength;
    rOutput.Constant = fInvLength * rInput.Constant +
        rOutput.Normal.Dot(m_Translate);
}
//----------------------------------------------------------------------------
void Transformation::Product(const Transformation& rLhsTrans,
    const Transformation& rRhsTrans)
{
    if( rLhsTrans.IsIdentity() )
    {
        *this = rRhsTrans;
        return;
    }

    if( rRhsTrans.IsIdentity() )
    {
        *this = rLhsTrans;
        return;
    }

    // 如果rLhsTrans和rRhsTrans都是SRT形式,结果变换才能是SRT形式.
    if( rLhsTrans.m_bIsSRMatrix && rRhsTrans.m_bIsSRMatrix )
    {
        if( rRhsTrans.m_bIsUniformScale )
        {
            SetRotate(rLhsTrans.m_Matrix * rRhsTrans.m_Matrix);

            SetTranslate(rRhsTrans.GetUniformScale()*(rLhsTrans.m_Translate *
                rRhsTrans.m_Matrix) + rRhsTrans.m_Translate);

            if( rLhsTrans.IsUniformScale() )
            {
                SetUniformScale(rLhsTrans.GetUniformScale() *
                    rRhsTrans.GetUniformScale());
            }
            else
            {
                SetScale(rRhsTrans.GetUniformScale() * rLhsTrans.GetScale());
            }

            return;
        }
    }

    // 其他情况下结果变换都是MT形式.
    Matrix3f MatA, MatB;

    if( rLhsTrans.m_bIsSRMatrix )
    {
        rLhsTrans.m_Matrix.GetDiagonalTimes(rLhsTrans.m_Scale, MatA);
    }
    else
    {
        MatA = rLhsTrans.m_Matrix;
    }

    if( rRhsTrans.m_bIsSRMatrix )
    {
        rRhsTrans.m_Matrix.GetDiagonalTimes(rRhsTrans.m_Scale, MatB);
    }
    else
    {
        MatB = rRhsTrans.m_Matrix;
    }

    SetMatrix(MatA * MatB);
    SetTranslate(rLhsTrans.m_Translate*MatB + rRhsTrans.m_Translate);
}
//----------------------------------------------------------------------------
void Transformation::GetInverse(Transformation& rInvTrans)
{
    if( m_bIsIdentity )
    {
        rInvTrans = *this;
        return;
    }

    if( m_bIsSRMatrix )
    {
        if( m_bIsUniformScale )
        {
            Matrix3f TranMat;
            GetRotate().GetTranspose(TranMat);
            rInvTrans.m_Matrix = TranMat / GetUniformScale();
        }
        else
        {
            m_Matrix.GetDiagonalTimes(m_Scale, rInvTrans.m_Matrix);
			rInvTrans.m_Matrix.Inverse();
        }
    }
    else
    {
        m_Matrix.GetInverse(rInvTrans.m_Matrix);
    }

    rInvTrans.m_Translate = -(m_Translate * rInvTrans.m_Matrix);
    rInvTrans.m_bIsIdentity = false;
    rInvTrans.m_bIsSRMatrix = false;
    rInvTrans.m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
void Transformation::GetHomogeneous(Matrix4f& rHMatrix) const
{
    if( m_bIsSRMatrix )
    {
        rHMatrix[0][0] = m_Scale[0]*m_Matrix[0][0];
        rHMatrix[0][1] = m_Scale[0]*m_Matrix[0][1];
        rHMatrix[0][2] = m_Scale[0]*m_Matrix[0][2];
        rHMatrix[0][3] = 0.0f;
        rHMatrix[1][0] = m_Scale[1]*m_Matrix[1][0];
        rHMatrix[1][1] = m_Scale[1]*m_Matrix[1][1];
        rHMatrix[1][2] = m_Scale[1]*m_Matrix[1][2];
        rHMatrix[1][3] = 0.0f;
        rHMatrix[2][0] = m_Scale[2]*m_Matrix[2][0];
        rHMatrix[2][1] = m_Scale[2]*m_Matrix[2][1];
        rHMatrix[2][2] = m_Scale[2]*m_Matrix[2][2];
        rHMatrix[2][3] = 0.0f;
    }
    else
    {
        rHMatrix[0][0] = m_Matrix[0][0];
        rHMatrix[0][1] = m_Matrix[0][1];
        rHMatrix[0][2] = m_Matrix[0][2];
        rHMatrix[0][3] = 0.0f;
        rHMatrix[1][0] = m_Matrix[1][0];
        rHMatrix[1][1] = m_Matrix[1][1];
        rHMatrix[1][2] = m_Matrix[1][2];
        rHMatrix[1][3] = 0.0f;
        rHMatrix[2][0] = m_Matrix[2][0];
        rHMatrix[2][1] = m_Matrix[2][1];
        rHMatrix[2][2] = m_Matrix[2][2];
        rHMatrix[2][3] = 0.0f;
    }

    rHMatrix[3][0] = m_Translate[0];
    rHMatrix[3][1] = m_Translate[1];
    rHMatrix[3][2] = m_Translate[2];
    rHMatrix[3][3] = 1.0f;
}
//----------------------------------------------------------------------------
