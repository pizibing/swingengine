#import "SEiPhoneOES1ApplicationDelegate.h"
#include "SEWindowApplication.h"
#include "SEiPhoneOES1Renderer.h"
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
    
    SEWindowApplication* pTheApp = (SEWindowApplication*)pUserData;
    pTheApp->OnTouchBegan((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesMoved(UIView* owner, NSSet* pTouches, UIEvent* pEvent, 
                           void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    SEWindowApplication* pTheApp = (SEWindowApplication*)pUserData;
    pTheApp->OnTouchMoved((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesEnded(UIView* owner, NSSet* pTouches, UIEvent* pEvent, 
                           void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    SEWindowApplication* pTheApp = (SEWindowApplication*)pUserData;
    pTheApp->OnTouchEnded((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------
static void OnTouchesCancelled(UIView* owner, NSSet* pTouches, 
                               UIEvent* pEvent, void* pUserData)
{
    UITouch* pAnyTouch = [pTouches anyObject];
    CGPoint curTouchLoc = [pAnyTouch locationInView:owner];
    
    SEWindowApplication* pTheApp = (SEWindowApplication*)pUserData;
    pTheApp->OnTouchCancelled((int)curTouchLoc.x, (int)curTouchLoc.y);
}
//----------------------------------------------------------------------------

@implementation SEApplicationDelegate
//----------------------------------------------------------------------------
- (void) update
{
    SEWindowApplication* pTheApp = 
        (SEWindowApplication*)SEApplication::TheApplication;
    SE_ASSERT( pTheApp );

    // Application's real-time logic/rendering entry point.
    pTheApp->OnIdle();
}
//----------------------------------------------------------------------------
- (void) applicationDidFinishLaunching:(UIApplication*)application
{
    // The application instance should already been created.
    SEWindowApplication* pTheApp = 
        (SEWindowApplication*)SEApplication::TheApplication;
    SE_ASSERT( pTheApp );   

    // Create application window.
    // We only support a fullscreen window for now.
    CGRect rect = [[UIScreen mainScreen] bounds];
    AppWindow = [[UIWindow alloc] initWithFrame:rect];
    pTheApp->SetWindowID((int)AppWindow);

    // Create OpenGL ES1 renderer.
    SEiPhoneOES1Renderer* pRenderer = SE_NEW SEiPhoneOES1Renderer(AppWindow, 
        pTheApp->GetFormat(), pTheApp->GetDepth(), pTheApp->GetStencil(), 
        pTheApp->GetBuffering(), pTheApp->GetMultisampling(), 0, 0, 
        rect.size.width, rect.size.height);
    pTheApp->SetRenderer(pRenderer);

    // Create OpenAL audio renderer.
    SEiPhoneOpenALRenderer* pAudioRenderer = SE_NEW SEiPhoneOpenALRenderer;
    pTheApp->SetAudioRenderer(pAudioRenderer);

    // Set up touches event handlers.
    SEEAGLView* pView = pRenderer->GetView();
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
    SEWindowApplication* pTheApp = 
        (SEWindowApplication*)SEApplication::TheApplication;
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



