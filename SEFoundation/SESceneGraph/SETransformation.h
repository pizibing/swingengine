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

#ifndef Swing_Transformation_H
#define Swing_Transformation_H

#include "SEFoundationLIB.h"
#include "SEMatrix3.h"
#include "SEMatrix4.h"
#include "SEPlane3.h"

// 顶点变换采用Y = X*M + T的形式,其中M是3*3矩阵,T是3维平移向量.
// M通常为R或者SR的乘积,S是用于缩放的对角矩阵,R是旋转矩阵.
// Y = X*M + T的形式可以支持建模工具的镜像变换和非统一缩放变换.
// Y = X*M + T的逆变换的一般形式为X = (Y-T)*M^{-1}.如果M = S*R,
// 则逆变换可转换为X = (Y-T)*R^T*S^{-1}.
//
// SETransformation和矩阵运算的连接方式一致,也采用向右连接.
//
// 执行效能分析(基于AMD Athlon64 3000+,1G,ATI X800).
// 1000000次乘积运算,release模式,执行时间约为260ms(统一缩放SRT),
// 440ms(非统一缩放SRT),DirectX齐次矩阵约为50ms.
// 10000次乘积运算,release模式,执行时间 < 0ms,DirectX齐次矩阵 < 0ms.
// 因此SETransformation类可用于引擎应用层,针对场景节点树进行10000为数量级的矩
// 阵运算,与DirectX齐次矩阵没有明显差异.
// 而运用于引擎管线层(光栅器,绘图管线)则将明显落后于DirectX齐次矩阵.
// 采用SETransformation封装矩阵运算的优点:
//     (1) 在能够直接获取SRT分量的情况下,逆变换将得到加速.
//     (2) 矩阵运算,空间变换是API无关的.
// 采用SETransformation封装矩阵运算的缺点:如果用于软件光栅器则速度较慢.

namespace Swing
{

//----------------------------------------------------------------------------
// Description:封装SRT矩阵变换
// Author:Sun Che
// Date:20070523
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SETransformation
{
public:
    SETransformation(void);
    ~SETransformation(void);

    // 将变换设为单位矩阵变换.
    void Identity(void);
    // 将缩放变换设为统一缩放变换.
    void UnitScale(void);

    // 提示变换信息中所包含的变换类型.
    inline bool IsIdentity(void) const;
    inline bool IsSRMatrix(void) const;
    inline bool IsUniformScale(void) const;

    // (1) 所有Set*函数会设置m_bIsIdentity为false.
    // (2) SetRotate函数会设置m_bIsSRMatrix为true.如果该标志为false,
    //     则GetRotate会产生断言.
    // (3) SetMatrix函数会设置m_bIsSRMatrix,m_bIsUniformScale为false.
    // (4) SetScale函数会设置m_bIsUniformScale为false.SetUniformScale函数设置
    //     m_bIsUniformScale为true.如果m_bIsUniformScale为false,
    //     则GetUniformScale会产生断言.
    void SetRotate(const SEMatrix3f& rRotate);
    inline const SEMatrix3f& GetRotate(void) const;
    void SetMatrix(const SEMatrix3f& rMatrix);
    inline const SEMatrix3f& GetMatrix(void) const;
    void SetTranslate(const SEVector3f& rTranslate);
    inline const SEVector3f& GetTranslate(void) const;
    void SetScale(const SEVector3f& rScale);
    inline const SEVector3f& GetScale(void) const;
    void SetUniformScale(float fScale);
    inline float GetUniformScale(void) const;

    // 对于M = S*R的情况,此函数返回S中的最大值的绝对值.
    // 对于一般情况的M,返回矩阵列元素绝对值之和的最大值.
    // 对BV球进行缩放变换时用到此函数,用返回值缩放BV球半径.
    float GetNorm(void) const;

    // 正向顶点变换,计算Y = X*M + T.
    void ApplyForward(const SEVector3f& rInput, SEVector3f& rOutput) const;
    // 正向顶点数组变换,变换一组顶点.
    void ApplyForward(int iCount, const SEVector3f* aInput, SEVector3f* 
        aOutput) const;

    // 逆向顶点变换,计算X = (Y-T)*M^{-1}.
    void ApplyInverse(const SEVector3f& rInput, SEVector3f& rOutput) const;
    // 逆向顶点变换,变换一组顶点.
    void ApplyInverse(int iCount, const SEVector3f* aInput, SEVector3f* 
        aOutput) const;

    // 逆向向量变换,输入值是一个空间向量,因此不需要对其施加T变换.
    // V1 = V0*M^{-1}.
    void InvertVector(const SEVector3f& rInput, SEVector3f& rOutput) const;

    // 对平面进行正向变换,平面法线必须为单位向量.
    void ApplyForward(const SEPlane3f& rInput, SEPlane3f& rOutput) const;

    // 计算*this = rLhsTrans*rRhsTrans.
    void Product(const SETransformation& rLhsTrans,
        const SETransformation& rRhsTrans);

    // 设当前变换为Y = X*M + T,则当前变换的逆变换为X = (Y-T)*M^{-1}.
    // 如果当前变换为Y = X*S*R + T,则当前变换的逆变换为X = (Y-T)*R^T*S^{-1}.
    // 也就是M' = M^{-1} = R^T*S^{-1},T' = -T*M^{-1} = -T*R^T*S^{-1}.
    void GetInverse(SETransformation& rInvTrans);

    // 构造4x4Homogeneous矩阵,供1x4行向量左乘使用.
    void GetHomogeneous(SEMatrix4f& rHMatrix) const;

    static const SETransformation IDENTITY;

    // stream操作时用到,此类写入磁盘的字节数.
    enum
    {
        DISK_USED = sizeof(SEMatrix3f) + 2*sizeof(SEVector3f) + 3
    };

private:
	friend class SEStream;
    friend class SESpatial;

    SEMatrix3f m_Matrix;
    SEVector3f m_Translate;
    SEVector3f m_Scale;

    bool m_bIsIdentity;
    bool m_bIsSRMatrix;
    bool m_bIsUniformScale;
};

#include "SETransformation.inl"

}

#endif