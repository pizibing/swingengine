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

#ifndef Swing_ConsoleAppliCation_H
#define Swing_ConsoleAppliCation_H

#include "SEApplication.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:for iPhone application
// 作者:jazzboysc
// 时间:20090604
//----------------------------------------------------------------------------
class SEConsoleApplication : public SEApplication
{
public:
    SEConsoleApplication(void);
    virtual ~SEConsoleApplication(void);

    // 应用程序负责实现入口函数,返回值为exit code.
    virtual int Main(int iArgCount, char** apcArgument) = 0;

protected:
    // 钩子函数调用入口函数Main.
    static int Run(int iArgCount, char** apcArgument);
};

}

#endif
