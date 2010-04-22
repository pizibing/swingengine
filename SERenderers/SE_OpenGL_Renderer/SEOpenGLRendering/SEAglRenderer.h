#ifndef Swing_Agl_Renderer_H
#define Swing_Agl_Renderer_H

#include "SEOpenGLRendererLIB.h"
#include "SEOpenGLRenderer.h"
#include <AGL/agl.h>
#include <Carbon/Carbon.h>
#include <DrawSprocket/DrawSprocket.h>

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20081009
//----------------------------------------------------------------------------
class SE_RENDERER_API SEAglRenderer : public SEOpenGLRenderer
{
public:
    SEAglRenderer(AGLDevice hDevice, WindowRef pWindow,
        SEFrameBuffer::FormatType eFormat, SEFrameBuffer::DepthType eDepth,
        SEFrameBuffer::StencilType eStencil,
        SEFrameBuffer::BufferingType eBuffering,
        SEFrameBuffer::MultisamplingType eMultisampling, int iX, int iY,
        int iWidth, int iHeight);

    virtual ~SEAglRenderer(void);

    virtual void Resize(int iWidth, int iHeight);
    virtual void ToggleFullscreen(void);

    virtual bool BeginScene(void);
    virtual void DisplayBackBuffer(void);

    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic);

    // 窗体参数.
    AGLDevice GetDevice(void);
    WindowRef GetWindow(void);
    AGLDrawable GetDrawable(void);
    AGLContext GetContext(void);

private:
    // 建立绘图区域.
    void SetUpBufferRect(void);

    // 显示错误信息并终止.
    void FatalErrorMessage(const char* acMessage);

    // 窗体参数.
    AGLDevice m_hAglDevice;
    WindowRef m_pAglWindow;
    AGLDrawable m_pAglDrawable;
    AGLContext m_pAglContext;
    AGLDrawable m_pFullScreenDrawable;
    DSpContextReference m_pDSpContext;
    Boolean m_bFullScreen;

    // 字体管理.
    GWorldPtr m_pBack;

    // 用于支持fullscreen/window.
    int m_iX, m_iY;
    int m_iSaveWidth, m_iSaveHeight;

    static Boolean ms_bDSpStarted;
};

}

#endif

