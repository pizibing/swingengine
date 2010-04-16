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
template <class T>
void Allocate(int iCols, int iRows, T**& raatArray)
{
    raatArray = SE_NEW T*[iRows];
    raatArray[0] = SE_NEW T[iRows*iCols];
    for( int iRow = 1; iRow < iRows; iRow++ )
    {
        raatArray[iRow] = &raatArray[0][iCols*iRow];
    }
}
//----------------------------------------------------------------------------
template <class T>
void Deallocate(T**& raatArray)
{
    if( raatArray )
    {
        SE_DELETE[] raatArray[0];
        SE_DELETE[] raatArray;
        raatArray = 0;
    }
}
//----------------------------------------------------------------------------
template <class T>
void Allocate(int iCols, int iRows, int iSlices, T***& raaatArray)
{
    raaatArray = SE_NEW T**[iSlices];
    raaatArray[0] = SE_NEW T*[iSlices*iRows];
    raaatArray[0][0] = SE_NEW T[iSlices*iRows*iCols];
    for( int iSlice = 0; iSlice < iSlices; iSlice++ )
    {
        raaatArray[iSlice] = &raaatArray[0][iRows*iSlice];
        for( int iRow = 0; iRow < iRows; iRow++ )
        {
            raaatArray[iSlice][iRow] = &raaatArray[0][0][iCols*(iRow+
                iRows*iSlice)];
        }
    }
}
//----------------------------------------------------------------------------
template <class T>
void Deallocate(T***& raaatArray)
{
    if( raaatArray )
    {
        SE_DELETE[] raaatArray[0][0];
        SE_DELETE[] raaatArray[0];
        SE_DELETE[] raaatArray;
        raaatArray = 0;
    }
}
//----------------------------------------------------------------------------
