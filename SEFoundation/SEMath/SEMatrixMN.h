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
// 说明:
// 作者:Sun Che
// 时间:20070706
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEMatrixMNf
{
public:
    SEMatrixMNf(int iRows = 0, int iCols = 0);
    SEMatrixMNf(int iRows, int iCols, const float* afData);
    SEMatrixMNf(int iRows, int iCols, const float** aafEntry);
    SEMatrixMNf(const SEMatrixMNf& rMat);
    ~SEMatrixMNf(void);

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
    
    inline void SetRow(int iDesRow, const SEVectorNf& rSrcVec);
    inline void GetRow(int iSrcRow, SEVectorNf& rDesVec) const;
    inline void SetCol(int iDesCol, const SEVectorNf& rSrcVec);
    inline void GetCol(int iSrcCol, SEVectorNf& rDesVec) const;

    void SetMatrix(int iRows, int iCols, const float* pData);
    void SetMatrix(int iRows, int iCols, const float** ppData);

    SEMatrixMNf& operator = (const SEMatrixMNf& rMat);

    bool operator == (const SEMatrixMNf& rMat) const;
    bool operator != (const SEMatrixMNf& rMat) const;
    bool operator <  (const SEMatrixMNf& rMat) const;
    bool operator <= (const SEMatrixMNf& rMat) const;
    bool operator >  (const SEMatrixMNf& rMat) const;
    bool operator >= (const SEMatrixMNf& rMat) const;

    SEMatrixMNf operator + (const SEMatrixMNf& rRhsMat) const;
    SEMatrixMNf operator - (const SEMatrixMNf& rRhsMat) const;
    SEMatrixMNf operator * (const SEMatrixMNf& rRhsMat) const;
    SEMatrixMNf operator * (float fScalar) const;
    SEMatrixMNf operator / (float fScalar) const;
    SEMatrixMNf operator - (void) const;

    SEMatrixMNf& operator += (const SEMatrixMNf& rRhsMat);
    SEMatrixMNf& operator -= (const SEMatrixMNf& rRhsMat);
    SEMatrixMNf& operator *= (float fScalar);
    SEMatrixMNf& operator /= (float fScalar);

    // 获取转置矩阵
    inline void GetTranspose(SEMatrixMNf& rDesMat) const;
    // 获取逆矩阵,矩阵必须是方阵,可逆方阵返回true
    bool GetInverse(SEMatrixMNf& rDesMat) const;

    // 乘以列向量
    SEVectorNf operator * (const SEVectorNf& rRhsVec) const;

    SE_FOUNDATION_API friend SEMatrixMNf operator * (float fLhsScalar,
        const SEMatrixMNf& rRhsMat);
    SE_FOUNDATION_API friend SEVectorNf operator * (const SEVectorNf& rLhsVec,
        const SEMatrixMNf& rMRhsat);

private:
    inline void Allocate(bool bSetToZero);
    inline void Deallocate(void);

    inline int CompareData(const SEMatrixMNf& rMat) const;

    int m_iRows, m_iCols, m_iCount;

    float* m_pData;

    // 每个指针指向矩阵数据的一行,用于解线性方程组时的行变换
    float** m_ppData;
};

#include "SEMatrixMN.inl"

}

#endif