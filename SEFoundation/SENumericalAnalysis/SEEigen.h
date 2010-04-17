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

#ifndef Swing_Eigen_H
#define Swing_Eigen_H

#include "SEFoundationLIB.h"
#include "SEMatrix2.h"
#include "SEMatrix3.h"
#include "SEMatrix4.h"
#include "SEMatrixMN.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:矩阵特征向量特征值类
// 说明:参考自Wild Magic4
// 作者:Sun Che
// 时间:20070706
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Eigen
{
public:
    Eigen(int iSize);
    Eigen(const Matrix2f& rMat);
    Eigen(const Matrix3f& rMat);
    Eigen(const MatrixMNf& rMat);
    ~Eigen(void);

public:
    float& operator () (int iRow, int iCol);
    Eigen& operator = (const Matrix2f& rMat);
    Eigen& operator = (const Matrix3f& rMat);
    Eigen& operator = (const MatrixMNf& rMat);

    // 特征向量是特征矩阵的列
    float GetEigenvalue(int i) const;
    const float* GetEigenvalues(void) const;
    void GetEigenvector(int i, SEVector2f& rVec) const;
    void GetEigenvector(int i, Vector3f& rVec) const;
    VectorNf GetEigenvector(int i) const;
    const MatrixMNf& GetEigenvectors(void) const;

    void EigenStuff2(void);
    void EigenStuff3(void);
    void EigenStuffN(void);
    void EigenStuff(void);

    void DecrSortEigenStuff2(void);
    void DecrSortEigenStuff3(void);
    void DecrSortEigenStuffN(void);
    void DecrSortEigenStuff (void);

    void IncrSortEigenStuff2(void);
    void IncrSortEigenStuff3(void);
    void IncrSortEigenStuffN(void);
    void IncrSortEigenStuff(void);

private:
    int m_iSize;
    MatrixMNf m_Mat;
    float* m_pDiag;
    float* m_pSubd;

    // For odd size matrices, the Householder reduction involves an odd
    // number of reflections.  The product of these is a reflection.  The
    // QL algorithm uses rotations for further reductions.  The final
    // orthogonal matrix whose columns are the eigenvectors is a reflection,
    // so its determinant is -1.  For even size matrices, the Householder
    // reduction involves an even number of reflections whose product is a
    // rotation.  The final orthogonal matrix has determinant +1.  Many
    // algorithms that need an eigendecomposition want a rotation matrix.
    // We want to guarantee this is the case, so m_bRotation keeps track of
    // this.  The DecrSort and IncrSort further complicate the issue since
    // they swap columns of the orthogonal matrix, causing the matrix to
    // toggle between rotation and reflection.  The value m_bRotation must
    // be toggled accordingly.
    bool m_bIsRotation;
    void GuaranteeRotation(void);

    // Householder reduction to tridiagonal form
    void Tridiagonal2(void);
    void Tridiagonal3(void);
    void TridiagonalN(void);

    // QL algorithm with implicit shifting, applies to tridiagonal matrices
    bool QLAlgorithm(void);

    // sort eigenvalues from largest to smallest
    void DecreasingSort(void);

    // sort eigenvalues from smallest to largest
    void IncreasingSort(void);
};

}

#endif
