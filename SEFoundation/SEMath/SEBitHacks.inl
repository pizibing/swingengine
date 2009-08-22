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
inline bool IsOdd(int iValue)
{
    return iValue & 1;
}
//----------------------------------------------------------------------------
inline bool IsEven(int iValue)
{
    return !(iValue & 1);
}
//----------------------------------------------------------------------------
inline bool IsPowerOfTwo(unsigned int uiValue)
{
    return (uiValue > 0) && ((uiValue & (uiValue - 1)) == 0);
}
//----------------------------------------------------------------------------
inline unsigned int Log2OfPowerOfTwo(unsigned int uiPowerOfTwo)
{
    unsigned int uiLog2 = (uiPowerOfTwo & 0xAAAAAAAA) != 0;
    uiLog2 |= ((uiPowerOfTwo & 0xFFFF0000) != 0) << 4;
    uiLog2 |= ((uiPowerOfTwo & 0xFF00FF00) != 0) << 3;
    uiLog2 |= ((uiPowerOfTwo & 0xF0F0F0F0) != 0) << 2;
    uiLog2 |= ((uiPowerOfTwo & 0xCCCCCCCC) != 0) << 1;

    return uiLog2;
}
//----------------------------------------------------------------------------
inline void SetBitToOne(unsigned int& rValue, int i)
{
    rValue |= (1 << i);
}
//----------------------------------------------------------------------------
inline void SetBitToZero(unsigned int& rValue, int i)
{
    rValue &= ~(1 << i);
}
//----------------------------------------------------------------------------