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
#include "SEiPhoneOES1Renderer.h"

using namespace Swing;

const int WindowApplication::KEY_ESCAPE = 0;
const int WindowApplication::KEY_LEFT_ARROW = 0;
const int WindowApplication::KEY_RIGHT_ARROW = 0;
const int WindowApplication::KEY_UP_ARROW = 0;
const int WindowApplication::KEY_DOWN_ARROW = 0;
const int WindowApplication::KEY_HOME = 0;
const int WindowApplication::KEY_END = 0;
const int WindowApplication::KEY_PAGE_UP = 0;
const int WindowApplication::KEY_PAGE_DOWN = 0;
const int WindowApplication::KEY_INSERT = 0;
const int WindowApplication::KEY_DELETE = 0;
const int WindowApplication::KEY_BACKSPACE = 0;
const int WindowApplication::KEY_TAB = 0;
const int WindowApplication::KEY_ENTER = 0;
const int WindowApplication::KEY_RETURN = 0;

const int WindowApplication::KEY_F1 = 0;
const int WindowApplication::KEY_F2 = 0;
const int WindowApplication::KEY_F3 = 0;
const int WindowApplication::KEY_F4 = 0;
const int WindowApplication::KEY_F5 = 0;
const int WindowApplication::KEY_F6 = 0;
const int WindowApplication::KEY_F7 = 0;
const int WindowApplication::KEY_F8 = 0;
const int WindowApplication::KEY_F9 = 0;
const int WindowApplication::KEY_F10 = 0;
const int WindowApplication::KEY_F11 = 0;
const int WindowApplication::KEY_F12 = 0;

const int WindowApplication::KEY_SHIFT = 0;
const int WindowApplication::KEY_CONTROL = 0;
const int WindowApplication::KEY_ALT = 0;
const int WindowApplication::KEY_COMMAND = 0;

const int WindowApplication::MOUSE_LEFT_BUTTON = 0;
const int WindowApplication::MOUSE_MIDDLE_BUTTON = 0;
const int WindowApplication::MOUSE_RIGHT_BUTTON = 0;
const int WindowApplication::MOUSE_UP = 0;
const int WindowApplication::MOUSE_DOWN = 0;

const int WindowApplication::MODIFIER_CONTROL = 0;
const int WindowApplication::MODIFIER_LBUTTON = 0;
const int WindowApplication::MODIFIER_MBUTTON = 0;
const int WindowApplication::MODIFIER_RBUTTON = 0;
const int WindowApplication::MODIFIER_SHIFT = 0;

//----------------------------------------------------------------------------
void WindowApplication::SetMousePosition(int iX, int iY)
{
}
//----------------------------------------------------------------------------
void WindowApplication::GetMousePosition(int& riX, int& riY) const
{
}
//----------------------------------------------------------------------------
int WindowApplication::GetStringWidth(const char* acText) const
{
    return 0;	
}
//----------------------------------------------------------------------------
int WindowApplication::GetCharacterWidth(const char cCharacter) const
{
    return 0;	
}
//----------------------------------------------------------------------------
int WindowApplication::GetFontHeight() const
{
    return 0;	
}
//----------------------------------------------------------------------------
int WindowApplication::Main(int iCount, char** apcArgument)
{
    WindowApplication* pTheApp = (WindowApplication*)TheApplication;

    // 允许在窗体创建之前做一些工作.
    if( !pTheApp->OnPrecreate() )
    {
        return -1;
    }

    // 创建窗体及其renderer,进入主循环.	
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    UIApplicationMain(iCount, apcArgument, nil, @"ApplicationDelegate");
    [pool release];

    return 0;
}
//----------------------------------------------------------------------------
void Application::LaunchTreeControl(Spatial*, int, int, int, int)
{
}
//----------------------------------------------------------------------------
void Application::ShutdownTreeControl()
{
}
//----------------------------------------------------------------------------
