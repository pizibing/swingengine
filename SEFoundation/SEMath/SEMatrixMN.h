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

#ifndef Swing_MatrixMN_H
#define Swing_MatrixMN_H

#include "SEFoundationLIB.h"
#include "SEVectorN.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:M*N矩阵类
// 说明:
// 作者:Sun Che
// 时间:20070706
//----------------------------------------------------------------------------
class SE_FOUNDATION_API MatrixMNf
{
public:
    MatrixMNf(int iRows = 0, int iCols = 0);
    MatrixMNf(int iRows, int iCols, const float* afData);
    MatrixMNf(int iRows, int iCols, const float** aafEntry);
    MatrixMNf(const MatrixMNf& rMat);
    ~MatrixMNf(void);

public:
    inline void SetSize(int iRows, int iCols);
    inline void GetSize(int& riRows, int& riCols) const;
    inline int GetRows(void) const;
    inline int GetCols(void) const;
    inline int GetCount(void) const;

    operator float* (void);
    operator const float* (void) const;
    float* operator [] (int iRow);
    const float* operator [] (int iRow) const;
    void SwapRows(int iRow0, int iRow1);
    float operator () (int iRow, int iCol) const;
    float& operator () (int iRow, int iCol);
    
    inline void SetRow(int iDesRow, const VectorNf& rSrcVec);
    inline void GetRow(int iSrcRow, VectorNf& rDesVec) const;
    inline void SetCol(int iDesCol, const VectorNf& rSrcVec);
    inline void GetCol(int iSrcCol, VectorNf& rDesVec) const;

    void SetMatrix(int iRows, int iCols, const float* pData);
    void SetMatrix(int iRows, int iCols, const float** ppData);

    MatrixMNf& operator = (const MatrixMNf& rMat);

    bool operator == (const MatrixMNf& rMat) const;
    bool operator != (const MatrixMNf& rMat) const;
    bool operator <  (const MatrixMNf& rMat) const;
    bool operator <= (const MatrixMNf& rMat) const;
    bool operator >  (const MatrixMNf& rMat) const;
    bool operator >= (const MatrixMNf& rMat) const;

    MatrixMNf operator + (const MatrixMNf& rRhsMat) const;
    MatrixMNf operator - (const MatrixMNf& rRhsMat) const;
    MatrixMNf operator * (const MatrixMNf& rRhsMat) const;
    MatrixMNf operator * (float fScalar) const;
    MatrixMNf operator / (float fScalar) const;
    MatrixMNf operator - (void) const;

    MatrixMNf& operator += (const MatrixMNf& rRhsMat);
    MatrixMNf& operator -= (const MatrixMNf& rRhsMat);
    MatrixMNf& operator *= (float fScalar);
    MatrixMNf& operator /= (float fScalar);

    // 获取转置矩阵
    inline void GetTranspose(MatrixMNf& rDesMat) const;
    // 获取逆矩阵,矩阵必须是方阵,可逆方阵返回true
    bool GetInverse(MatrixMNf& rDesMat) const;

    // 乘以列向量
    VectorNf operator * (const VectorNf& rRhsVec) const;

    SE_FOUNDATION_API friend MatrixMNf operator * (float fLhsScalar,
        const MatrixMNf& rRhsMat);
    SE_FOUNDATION_API friend VectorNf operator * (const VectorNf& rLhsVec,
        const MatrixMNf& rMRhsat);

private:
    inline void Allocate(bool bSetToZero);
    inline void Deallocate(void);

    inline int CompareData(const MatrixMNf& rMat) const;

    int m_iRows, m_iCols, m_iCount;

    float* m_pData;

    // 每个指针指向矩阵数据的一行,用于解线性方程组时的行变换
    float** m_ppData;
};

#include "SEMatrixMN.inl"

}

#endif