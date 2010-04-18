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

#ifndef Swing_Query2Filtered_H
#define Swing_Query2Filtered_H

#include "SEFoundationLIB.h"
#include "SEQuery2TRational.h"
#include "SEVector2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081202
//----------------------------------------------------------------------------
class SEQuery2Filteredf : public SEQuery2f
{
public:
    // The base class handles floating-point queries.  Each query involves
    // comparing a determinant to zero.  If the determinant is sufficiently
    // close to zero, numerical round-off errors may cause the determinant
    // sign to be misclassified.  To avoid this, the query is repeated with
    // exact rational arithmetic.  You specify the closeness to zero for the
    // switch to rational arithmetic via fUncertainty, a value in the
    // interval [0,1].  The uncertainty of 0 causes the class to behave
    // as if it were SEQuery2f.  The uncertainty of 1 causes the class to
    // behave as if it were SEQuery2TRationalf.
    SEQuery2Filteredf(int iVCount, const SEVector2f* aVertex, float 
        fUncertainty);
    virtual ~SEQuery2Filteredf(void);

    // run-time type information
    virtual SEQuery::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToLine(const SEVector2f& rP, int iV0, int iV1) const;

    virtual int ToCircumcircle(const SEVector2f& rP, int iV0, int iV1,
        int iV2) const;

private:
    SEQuery2TRationalf m_RQuery;
    float m_fUncertainty;
};

}

#endif
