#ifndef Swing_iPhoneOES1_Renderer_H
#define Swing_iPhoneOES1_Renderer_H

#include "SEOGLES1RendererLIB.h"
#include "SEOGLES1Renderer.h"
#include "SEEAGLView.h"

// 注意:
// 这个文件包含了含有cocoa代码的头文件,因此只能被.mm文件所包含.

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:iPhone OpenGL ES1 Renderer类
// 说明:
// 作者:Sun Che
// 时间:20090607
//----------------------------------------------------------------------------
class SE_RENDERER_API iPhoneOES1Renderer : public OGLES1Renderer
{
public:
    iPhoneOES1Renderer(UIWindow* pWindow, FrameBuffer::FormatType eFormat,
        FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling, int iX, int iY,
        int iWidth, int iHeight);

    virtual ~iPhoneOES1Renderer(void);

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

