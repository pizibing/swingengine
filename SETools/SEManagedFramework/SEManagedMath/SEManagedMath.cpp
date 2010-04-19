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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedMath.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
float ManagedMathf::EPSILON::get()
{
    return SEMathf::EPSILON;
}
//---------------------------------------------------------------------------
float ManagedMathf::ZERO_TOLERANCE::get()
{
    return SEMathf::ZERO_TOLERANCE;
}
//---------------------------------------------------------------------------
float ManagedMathf::MAX_REAL::get()
{
    return SEMathf::MAX_REAL;
}
//---------------------------------------------------------------------------
float ManagedMathf::PI::get()
{
    return SEMathf::PI;
}
//---------------------------------------------------------------------------
float ManagedMathf::TWO_PI::get()
{
    return SEMathf::TWO_PI;
}
//---------------------------------------------------------------------------
float ManagedMathf::HALF_PI::get()
{
    return SEMathf::HALF_PI;
}
//---------------------------------------------------------------------------
float ManagedMathf::INV_PI::get()
{
    return SEMathf::INV_PI;
}
//---------------------------------------------------------------------------
float ManagedMathf::INV_TWO_PI::get()
{
    return SEMathf::INV_TWO_PI;
}
//---------------------------------------------------------------------------
float ManagedMathf::DEG_TO_RAD::get()
{
    return SEMathf::DEG_TO_RAD;
}
//---------------------------------------------------------------------------
float ManagedMathf::RAD_TO_DEG::get()
{
    return SEMathf::RAD_TO_DEG;
}
//---------------------------------------------------------------------------