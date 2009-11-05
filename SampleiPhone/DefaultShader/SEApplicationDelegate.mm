#import "SEApplicationDelegate.h"
#include "SEWindowApplication.h"
#include "SEiPhoneOES2Renderer.h"

using namespace Swing;

static const float gs_fFPS = 60.0f;

@implementation ApplicationDelegate
//----------------------------------------------------------------------------
- (void) update
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    // 应用程序实时逻辑/渲染入口函数.
    pTheApp->OnIdle();
}
//----------------------------------------------------------------------------
- (void) applicationDidFinishLaunching:(UIApplication*)application
{
    // 确保application实例已经创建.
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );	

    // 待实现.
    // 目前只支持全屏幕窗体.
    // 申请所需大小的窗体.	
    CGRect rect = [[UIScreen mainScreen] bounds];

    // 创建窗体.
    AppWindow = [[UIWindow alloc] initWithFrame:rect];

    pTheApp->SetWindowID((int)AppWindow);

    // 创建渲染器.
    pTheApp->SetRenderer(SE_NEW iPhoneOES2Renderer(AppWindow, 
        pTheApp->GetFormat(), pTheApp->GetDepth(), pTheApp->GetStencil(), 
        pTheApp->GetBuffering(), pTheApp->GetMultisampling(), 0, 0, 
        rect.size.width, rect.size.height));

    // 应用程序初始化入口函数,用于分配应用程序生存周期内的相关资源.
    // 所有派生自Swing::Object类的派生类实例应在这里初始化.	
    pTheApp->OnInitialize();

    // 显示窗体.
    [AppWindow makeKeyAndVisible];

    // 创建用于渲染的timer,定时回调代理类的update函数.
    [NSTimer scheduledTimerWithTimeInterval:(1.0 / gs_fFPS) target:self 
        selector:@selector(update) userInfo:nil repeats:YES];
}
//----------------------------------------------------------------------------
- (void) dealloc
{
    WindowApplication* pTheApp = 
        (WindowApplication*)Application::TheApplication;
    SE_ASSERT( pTheApp );

    // 应用程序结束运行入口函数,用于释放应用程序生存周期内的相关资源.
    // 所有派生自Swing::Object类的派生类实例应在这里释放.
    // 最后应用程序将释放renderer.
    pTheApp->OnTerminate();	

    // 释放主窗体.
    [AppWindow release];

    [super dealloc];
}
//----------------------------------------------------------------------------
@end



