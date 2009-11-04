#ifndef Swing_iPhoneOES2_Renderer_H
#define Swing_iPhoneOES2_Renderer_H

#include "SEOGLES2RendererLIB.h"
#include "SEOGLES2Renderer.h"
#include "SEEAGLView.h"

// 注意:
// 这个文件包含了含有cocoa代码的头文件,因此只能被.mm文件所包含.

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:iPhone OpenGL ES2 Renderer类
// 说明:
// 作者:Sun Che
// 时间:20091104
//----------------------------------------------------------------------------
class SE_RENDERER_API iPhoneOES2Renderer : public OGLES2Renderer
{
public:
    iPhoneOES2Renderer(UIWindow* pWindow, FrameBuffer::FormatType eFormat,
        FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling, int iX, int iY,
        int iWidth, int iHeight);

    virtual ~iPhoneOES2Renderer(void);

    virtual void Resize(int iWidth, int iHeight);
    virtual void ToggleFullscreen(void);

    virtual void DisplayBackBuffer(void);

    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic);

    // 窗体和view访问.
    EAGLView* GetView(void);
    UIWindow* GetWindow(void);

private:
    // 窗体和view参数.
    EAGLView* m_pEAGLView;
    UIWindow* m_pWindow;
    Boolean m_bFullScreen;

    // 待实现.
    // 字体管理.

    // 用于支持fullscreen/window.
    int m_iX, m_iY;
    int m_iSaveWidth, m_iSaveHeight;
};

}

#endif

