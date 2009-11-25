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

#import "SEiPhoneOES2ApplicationDelegate.h"
#include "SEWindowApplication.h"
#include "SEiPhoneOES2Renderer.h"
#include "SEiPhoneOpenALRenderer.h"

using namespace Swing;

static const float gs_fFPS = 60.0f;

//----------------------------------------------------------------------------
// Touches event handlers's callback functions.
//----------------------------------------------------------------------------
static void OnTouchesBegan(UIView* owner, NSSet* pTouches, UIEvent* pEvent, 
    void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    WindowApplication* pTheApp = (WindowApplication*)pUserData;
    pTheApp->OnTouchBegan((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesMoved(UIView* owner, NSSet* pTouches, UIEvent* pEvent, 
    void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    WindowApplication* pTheApp = (WindowApplication*)pUserData;
    pTheApp->OnTouchMoved((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesEnded(UIView* owner, NSSet* pTouches, UIEvent* pEvent, 
    void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    WindowApplication* pTheApp = (WindowApplication*)pUserData;
    pTheApp->OnTouchEnded((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesCancelled(UIView* owner, NSSet* pTouches, 
    UIEvent* pEvent, void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    WindowApplication* pTheApp = (WindowApplication*)pUserData;
    pTheApp->OnTouchCancelled((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------

@implementation ApplicationDelegate
//----------------------------------------------------------------------------
- (void) update
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    // Application's real-time logic/rendering entry point.
    pTheApp->OnIdle();
}
//----------------------------------------------------------------------------
- (void) applicationDidFinishLaunching:(UIApplication*)application
{
    // The application instance should already been created.
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );   

    // Create application window.
    // We only support a fullscreen window for now.
    CGRect rect = [[UIScreen mainScreen] bounds];
    AppWindow = [[UIWindow alloc] initWithFrame:rect];
    pTheApp->SetWindowID((int)AppWindow);

    // Create OpenGL ES2 renderer.
    iPhoneOES2Renderer* pRenderer = SE_NEW iPhoneOES2Renderer(AppWindow, 
        pTheApp->GetFormat(), pTheApp->GetDepth(), pTheApp->GetStencil(), 
        pTheApp->GetBuffering(), pTheApp->GetMultisampling(), 0, 0, 
        rect.size.width, rect.size.height);
    pTheApp->SetRenderer(pRenderer);

    // Create OpenAL audio renderer.
    iPhoneOpenALRenderer* pAudioRenderer = SE_NEW iPhoneOpenALRenderer;
    pTheApp->SetAudioRenderer(pAudioRenderer);

    // Set up touches event handlers.
    EAGL2View* pView = pRenderer->GetView();
    [pView setUserData:(void*)pTheApp];
    [pView setOnTouchesBegan:&OnTouchesBegan];
    [pView setOnTouchesMoved:&OnTouchesMoved];
    [pView setOnTouchesEnded:&OnTouchesEnded];
    [pView setOnTouchesCancelled:&OnTouchesCancelled];

    // Application's initialization entry point, all classes's instances 
    // derived from Swing::Object class should be created here(or after that).
    // This is the beginning of their life cycles.
    pTheApp->OnInitialize();

    // Show the window.
    [AppWindow makeKeyAndVisible];

    // Create a timer as the trigger of real-time updating.
    [NSTimer scheduledTimerWithTimeInterval:(1.0 / gs_fFPS) target:self 
        selector:@selector(update) userInfo:nil repeats:YES];
}
//----------------------------------------------------------------------------
- (void) dealloc
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    // Application's termination entry point, all classes's instances 
    // derived from Swing::Object class should be released here(or before that).
    // This is the ending of their life cycles.
    pTheApp->OnTerminate(); 

    // Release the window.
    [AppWindow release];

    [super dealloc];
}
//----------------------------------------------------------------------------
@end



