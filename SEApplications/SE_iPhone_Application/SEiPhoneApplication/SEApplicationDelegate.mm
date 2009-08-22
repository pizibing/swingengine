#import "SEApplicationDelegate.h"
#include "SEWindowApplication.h"

using namespace Swing;

static const float gs_fFPS = 60.0f;

@implementation ApplicationDelegate
//----------------------------------------------------------------------------
- (void) update
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    pTheApp->OnIdle();	
}
//----------------------------------------------------------------------------
- (void) applicationDidFinishLaunching:(UIApplication*)application
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );	

    // 申请所需大小的窗体.	
    CGRect rect = [[UIScreen mainScreen] bounds];
	
    // 创建窗体.
    AppWindow = [[UIWindow alloc] initWithFrame:rect];

    pTheApp->SetWindowID((int)AppWindow);

    // 待实现.
    // 创建渲染器.
    pTheApp->SetRenderer(0);

    pTheApp->OnInitialize();

    // 显示窗体.
    [AppWindow makeKeyAndVisible];

    // 创建用于渲染的timer.
    [NSTimer scheduledTimerWithTimeInterval:(1.0 / gs_fFPS) target:self 
        selector:@selector(update) userInfo:nil repeats:YES];
}
//----------------------------------------------------------------------------
- (void) dealloc
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    pTheApp->OnTerminate();	

    [AppWindow release];

    [super dealloc];
}
//----------------------------------------------------------------------------
@end



