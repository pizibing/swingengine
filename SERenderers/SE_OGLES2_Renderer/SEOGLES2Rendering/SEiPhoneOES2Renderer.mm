#include "SEiPhoneOES2Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
iPhoneOES2Renderer::iPhoneOES2Renderer(UIWindow* pWindow,
    FrameBuffer::FormatType eFormat, FrameBuffer::DepthType eDepth,
    FrameBuffer::StencilType eStencil, FrameBuffer::BufferingType eBuffering,
    FrameBuffer::MultisamplingType eMultisampling, int iX, int iY, int iWidth,
    int iHeight)
    :
    OGLES2Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        iWidth, iHeight)
{
    SE_ASSERT( m_iWidth > 0 && m_iHeight > 0 );
    SE_ASSERT( pWindow );
    
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_iX = iX;
    m_iY = iY;
    // 稍后创建EAGL2View.
    m_pEAGL2View = 0;
    m_pWindow = pWindow;
    m_bFullScreen = false;

    // Request a depth buffer.
    if( m_eDepth != FrameBuffer::DT_DEPTH_NONE )
    {
        // 待实现.
        // 目前只支持GL_DEPTH_COMPONENT16_OES.
    }

    // Request a stencil buffer.
    if( m_eStencil == FrameBuffer::ST_STENCIL_8 )
    {
        // 待实现.
    }

    // Request buffering.
    if( m_eBuffering == FrameBuffer::BT_BUFFERED_DOUBLE )
    {
        // 待实现.
    }

    // Request sampling.
    if( m_eMultisampling != FrameBuffer::MT_SAMPLING_NONE )
    {
        // 待实现.
    }

    // 创建EAGL2View及其EAGLContext.
    CGRect tempRect = [[UIScreen mainScreen] bounds];
    m_pEAGL2View = [[EAGL2View alloc] initWithFrame:tempRect 
        pixelFormat:GL_RGB565 depthFormat:GL_DEPTH_COMPONENT16 
        preserveBackbuffer:NO];

    // 把EAGL2View绑定给UIWindow.
    [m_pWindow addSubview:m_pEAGL2View];

    // 初始化OpenGL管线,获取设备能力.
    InitializeState();
}
//----------------------------------------------------------------------------
iPhoneOES2Renderer::~iPhoneOES2Renderer()
{
    [m_pEAGL2View release];
}
//----------------------------------------------------------------------------
void iPhoneOES2Renderer::Resize(int iWidth, int iHeight)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void iPhoneOES2Renderer::ToggleFullscreen()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void iPhoneOES2Renderer::DisplayBackBuffer()
{
    [m_pEAGL2View swapBuffers];
}
//----------------------------------------------------------------------------
int iPhoneOES2Renderer::LoadFont(const char*, int, bool, bool)
{
    // 待实现.
    return 0;
}
//----------------------------------------------------------------------------
EAGL2View* iPhoneOES2Renderer::GetView()
{
    return m_pEAGL2View;
}
//----------------------------------------------------------------------------
UIWindow* iPhoneOES2Renderer::GetWindow()
{
    return m_pWindow;
}
//----------------------------------------------------------------------------