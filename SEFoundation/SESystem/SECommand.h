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

#ifndef Swing_Command_H
#define Swing_Command_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080804
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SECommand
{
public:
    SECommand(int iCount, char** apcArgument);
    SECommand(char* acCmdline);
    ~SECommand(void);

    // return value is index of first excess argument
    int ExcessArguments(void);

    // Set bounds for numerical arguments.  If bounds are required, they must
    // be set for each argument.
    SECommand& Min(double dValue);
    SECommand& Max(double dValue);
    SECommand& Inf(double dValue);
    SECommand& Sup(double dValue);

    // The return value of the following methods is the option index within
    // the argument array.

    // Use the boolean methods for options which take no argument, for
    // example in
    //           myprogram -debug -x 10 -y 20 filename
    // the option -debug has no argument.

    int Boolean(char* acName);  // returns existence of option
    int Boolean(char* acName, bool& rbValue);
    int Integer(char* acName, int& riValue);
    int Float(char* acName, float& rfValue);
    int Double(char* acName, double& rdValue);
    int String(char* acName, char*& racValue);
    int Filename(char*& racName);

    // last error reporting
    const char* GetLastError(void);

protected:
    // constructor support
    void Initialize(void);

    // command line information
    int m_iCount;       // number of arguments
    char** m_apcArgument;  // argument list (array of strings)
    char* m_acCmdline;     // argument list (single string)
    bool* m_abUsed;        // keeps track of arguments already processed

    // parameters for bounds checking
    double m_dSmall;   // lower bound for numerical argument (min or inf)
    double m_dLarge;   // upper bound for numerical argument (max or sup)
    bool m_bMinSet;    // if true, compare:  small <= arg
    bool m_bMaxSet;    // if true, compare:  arg <= large
    bool m_bInfSet;    // if true, compare:  small < arg
    bool m_bSupSet;    // if true, compare:  arg < large

    // last error strings
    const char* m_acLastError;
    static char ms_acOptionNotFound[];
    static char ms_acArgumentRequired[];
    static char ms_acArgumentOutOfRange[];
    static char ms_acFilenameNotFound[];
};

}

#endif
