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

#pragma once
//#pragma pack(16)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class vector4;
class mat4x4;

class vector4
{
public:
	float x,y,z,w;

	vector4( void )
	{ 
	}

	vector4( float x0 , float y0 , float z0 , float w0 = 1.0f )
	{
		x = x0;
		y = y0;
		z = z0;
		w = w0;
	}

	void vec( float x0 , float y0 , float z0 , float w0 = 1.0f )
	{
		x = x0;
		y = y0;
		z = z0;
		w = w0;
	}

	void null( void )
	{
		x= y = z = 0.0f;
		w = 1.0f;
	}

	float& operator[]( int i )
	{
		return ( &x )[ i ];
	}

	float length( void )
	{
		return ( float )sqrt( x*x + y*y + z*z ); 
	}

	void negate( void )
	{
		x = -x;
		y = -y;
		z = -z;
	}

	// 单位化
	void normalize( void )
	{
		float len = length();
		if( len == 0.0f )
			return;
		
		x /= len;
		y /= len;
		z /= len;
	}

	// 叉积
	void cross( vector4 & v1 , vector4 & v2 )
	{
#ifdef _SIMD
		__asm
		{
			mov esi , v1
			mov edi , v2
			movaps xmm0 , [ esi ]
			movaps xmm1 , [ edi ]
			movaps xmm2 , xmm0
			movaps xmm3 , xmm1

			shufps xmm0 , xmm0 , 0xc9
			shufps xmm1 , xmm1 , 0xd2
			mulps xmm0 , xmm1

			shufps xmm2 , xmm2 , 0xd2
			shufps xmm3 , xmm3 , 0xc9
			mulps xmm2 , xmm3

			subps xmm0 , xmm2
			mov esi , this
			movaps [ esi ] , xmm0
		}
#else
	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
	w = 1.0f;
#endif
	}

	void operator += ( vector4 &v )
	{
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			addps xmm0 , [ edi ]
			movaps [ esi ] , xmm0
		}

#else
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
#endif
	}

	void operator -= ( vector4 &v )
	{
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			subps xmm0 , [ edi ]
			movaps [ esi ] , xmm0
		}
#else
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
#endif
	}

	void operator *= ( vector4 &v )
	{
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			mulps xmm0 , [ edi ]
			movaps [ esi ] , xmm0
		}
#else
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
#endif

	}

	vector4 operator + ( vector4 &v )
	{
		__declspec( align( 16 ) ) vector4 ret;
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			addps xmm0 , [ edi ]
			movaps ret , xmm0
		}
#else
		ret.x = x + v.x;
		ret.y = y + v.y;
		ret.z = z + v.z;
		ret.w = w + v.w;
#endif
		return ret;
	}

	vector4 operator - ( vector4 &v )
	{
		__declspec( align( 16 ) ) vector4 ret;
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			subps xmm0 , [ edi ]
			movaps ret , xmm0
		}
#else
		ret.x = x - v.x;
		ret.y = y - v.y;
		ret.z = z - v.z;
		ret.w = w - v.w;
#endif
		return ret;
	}

	vector4 operator * ( vector4 &v )
	{
		__declspec( align( 16 ) ) vector4 ret;
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , v
			movaps xmm0 , [ esi ]
			mulps xmm0 , [ edi ]
			movaps ret , xmm0
		}
#else
		ret.x = x * v.x;
		ret.y = y * v.y;
		ret.z = z * v.z;
		ret.w = w * v.w;

#endif
		return ret;
	}

	vector4 operator * ( mat4x4 &m )
	{
		__declspec( align( 16 ) ) vector4 a;
#ifdef _SIMD
		__asm
		{
			mov esi , this
			mov edi , m

			movaps xmm0 , [ esi ]
			movaps xmm1 , xmm0
			movaps xmm2 , xmm0
			movaps xmm3 , xmm0

			shufps xmm0 , xmm2 , 0x00
			shufps xmm1 , xmm2 , 0x55
			shufps xmm2 , xmm2 , 0xaa
			shufps xmm3 , xmm3 , 0xff

			mulps xmm0 , [ edi ]
			mulps xmm1 , [ edi + 16 ]
			mulps xmm2 , [ edi + 32 ]
			mulps xmm3 , [ edi + 48 ]

			addps xmm0 , xmm1
			addps xmm0 , xmm2
			addps xmm0 , xmm3

			movaps a , xmm0
		}
#else
		float *f = ( float * )this;
		a.x = x * f[ 0 ] + y * f[ 4 ] + z * f[ 8 ] + w * f[ 12 ];
		a.y = x * f[ 1 ] + y * f[ 5 ] + z * f[ 9 ] + w * f[ 13 ];
		a.z = x * f[ 2 ] + y * f[ 6 ] + z * f[ 10 ] + w * f[ 14 ];
		a.w = x * f[ 3 ] + y * f[ 7 ] + z * f[ 11 ] + w * f[ 15 ];

#endif
		return a;
	}
};

class mat4x4
{
public:
	mat4x4(){}
	mat4x4( float m11 , float m12 , float m13 , float m14 ,
			float m21 , float m22 , float m23 , float m24 ,
			float m31 , float m32 , float m33 , float m34 ,
			float m41 , float m42 , float m43 , float m44 )
	{
		m[0][0] = m11;
		m[0][1] = m12;
		m[0][2] = m13;
		m[0][3] = m14;

		m[1][0] = m21;
		m[1][1] = m22;
		m[1][2] = m23;
		m[1][3] = m24;

		m[2][0] = m31;
		m[2][1] = m32;
		m[2][2] = m33;
		m[2][3] = m34;

		m[3][0] = m41;
		m[3][1] = m42;
		m[3][2] = m43;
		m[3][3] = m44;
	}

public:
	float m[ 4 ][ 4 ];

public:
	void null( void )
	{
		memset( &m , 0 , sizeof( m ) );
	}

	void load_identity( void )
	{
		memset( m , 0 , sizeof( m ) );
		m[ 0 ][ 0 ] = m[ 1 ][ 1 ] = m[ 2 ][ 2 ] = m[ 3 ][ 3 ] = 1.0;
	}

	void set_rotation( vector4 &dir , float rad );

	inline mat4x4 operator * ( mat4x4 & m1 )
	{
		__declspec(align(16)) mat4x4 m2;

#ifdef _SIMD
	__asm
	{
		mov edi,m1				// 把右操作数矩阵的首地址指针保存到edi
		//movaps xmm4,[edi]		// 保存右操作数矩阵的第1行到xmm4
		//movaps xmm5,[edi+16]	// 保存右操作数矩阵的第2行到xmm5
		//movaps xmm6,[edi+32]	// 保存右操作数矩阵的第3行到xmm6
		//movaps xmm7,[edi+48]	// 保存右操作数矩阵的第4行到xmm7

		mov esi,this			// 把左操作数矩阵的首地址指针保存到esi
		mov	eax,0				// eax用于循环累加指针偏移变量

		LOOP_1:
		movaps xmm0,[esi+eax]	// 保存左操作数矩阵的第i行到xmm0,xmm1,xmm2,xmm3
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm0,xmm2,0x00	// xmm0变为4个重复的左操作数矩阵第i行第1个元素,aaaa
		shufps xmm1,xmm2,0x55	// xmm1变为4个重复的左操作数矩阵第i行第2个元素,bbbb
		shufps xmm2,xmm2,0xAA	// xmm2变为4个重复的左操作数矩阵第i行第3个元素,cccc
		shufps xmm3,xmm3,0xFF	// xmm3变为4个重复的左操作数矩阵第i行第4个元素,dddd

		mulps xmm0,[edi]
		mulps xmm1,[edi+16]
		mulps xmm2,[edi+32]
		mulps xmm3,[edi+48]

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3

		movaps m2[eax],xmm0

		add eax, 16
		cmp	eax, 48
		jle LOOP_1
	}
#else
		int i , j , k;
		float ab;
		for( i = 0; i < 4; i++ )
		{
			for( j = 0; j < 4; j++ )
			{
				ab = 0.0f;
				for( k = 0; k < 4; k++ )
				{
					ab += m[ i ][ k ] * m1.m[ k ][ j ];
				}
				m2.m[ i ][ j ] = ab;
			}
		}
#endif
		return m2;
	}

	vector4 operator * ( vector4& v )
	{
		__declspec ( align( 16 ) ) vector4 a;
#ifdef _SIMD

		__asm
		{
			mov esi , v
			mov edi , this
			movaps xmm0 , [ esi ]
			movaps xmm1 , xmm0
			movaps xmm2 , xmm0
			movaps xmm3 , xmm0
			shufps xmm0 , xmm2 , 0x00
			shufps xmm1 , xmm2 , 0x55
			shufps xmm2 , xmm2 , 0xAA
			shufps xmm3 , xmm3 , 0xFF

			mulps xmm0 , [ edi ]
			mulps xmm1 , [ edi + 16 ]
			mulps xmm2 , [ edi + 32 ]
			mulps xmm3 , [ edi + 48 ]

			addps xmm0 , xmm1
			addps xmm0 , xmm2
			addps xmm0 , xmm3

			movaps a , xmm0
		}
#else
		float *f = ( float* )this;
		a.x = v.x * f[ 0 ] + v.y * f[ 4 ] + v.z * f[ 8 ] + v.w * f[ 12 ];
		a.y = v.x * f[ 1 ] + v.y * f[ 5 ] + v.z * f[ 9 ] + v.w * f[ 13 ];
		a.z = v.x * f[ 2 ] + v.y * f[ 6 ] + v.z * f[ 10 ] + v.w * f[ 14 ];
		a.w = v.x * f[ 3 ] + v.y * f[ 7 ] + v.z * f[ 11 ] + v.w * f[ 15 ];
#endif
		return a;
	}
};


