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

#import <UIKit/UIKit.h>
#include "SEWindowApplication.h"

#if defined(SE_USING_OES2)
#include "SEiPhoneOES2Renderer.h"
#else
#include "SEiPhoneOES1Renderer.h"
#endif

using namespace Swing;

//----------------------------------------------------------------------------
int SEWindowApplication::Main(int iCount, char** apcArgument)
{
    SEWindowApplication* pTheApp = (SEWindowApplication*)TheApplication;

    // 允许在窗体创建之前做一些工作.
    if( !pTheApp->OnPrecreate() )
    {
        return -1;
    }

    // 创建窗体及其renderer,进入主循环.	
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    UIApplicationMain(iCount, apcArgument, nil, @"SEApplicationDelegate");
    [pool release];

    return 0;
}
//----------------------------------------------------------------------------
void SEApplication::LaunchTreeControl(SESpatial*, int, int, int, int)
{
}
//----------------------------------------------------------------------------
void SEApplication::ShutdownTreeControl()
{
}
//----------------------------------------------------------------------------
