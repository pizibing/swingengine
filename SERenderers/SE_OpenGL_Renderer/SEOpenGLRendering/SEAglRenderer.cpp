#include "SEOpenGLBitmapFont.h"
#include "SEOpenGLRenderer.h"
#include "SEOpenGLResources.h"
#include "SEOpenGLFrameBuffer.h"
#include "SEAglRenderer.h"

using namespace Swing;

Boolean SEAglRenderer::ms_bDSpStarted = false;

//----------------------------------------------------------------------------
SEAglRenderer::SEAglRenderer(AGLDevice hDevice, WindowRef pWindow,
    SEFrameBuffer::FormatType eFormat, SEFrameBuffer::DepthType eDepth,
    SEFrameBuffer::StencilType eStencil, SEFrameBuffer::BufferingType eBuffering,
    SEFrameBuffer::MultisamplingType eMultisampling, int iX, int iY, int iWidth,
    int iHeight)
    :
    SEOpenGLRenderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, iWidth,
        iHeight)
{
    assert( m_iWidth > 0 && m_iHeight > 0 );
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_iX = iX;
    m_iY = iY;
    m_hAglDevice = hDevice;
    m_pAglWindow = pWindow;
    m_pAglDrawable = (AGLDrawable)GetWindowPort(pWindow);
    m_pFullScreenDrawable = 0;
    m_bFullScreen = false;
    m_pDSpContext = 0;
    
    // See if we have a renderer available.
    AGLRendererInfo tempAGLInfo = aglQueryRendererInfo(&m_hAglDevice, 1);
    if( !tempAGLInfo )
    {
        tempAGLInfo = aglQueryRendererInfo(0, 0);
    }
    if( !tempAGLInfo )
    {
        FatalErrorMessage("Cannot obtain information about the renderer.");
    }

    // Set the desired attributes for the renderer's pixel format.
    int aiAttributes[256];
    int iPos = 0;

    aiAttributes[iPos++] = AGL_ACCELERATED;
    aiAttributes[iPos++] = AGL_NO_RECOVERY;

    // The color buffer is RGBA8888.
    aiAttributes[iPos++] = AGL_RGBA;
    aiAttributes[iPos++] = AGL_RED_SIZE;
    aiAttributes[iPos++] = 8;
    aiAttributes[iPos++] = AGL_GREEN_SIZE;
    aiAttributes[iPos++] = 8;
    aiAttributes[iPos++] = AGL_BLUE_SIZE;
    aiAttributes[iPos++] = 8;
    aiAttributes[iPos++] = AGL_ALPHA_SIZE;
    aiAttributes[iPos++] = 8;

    // Request a depth buffer.
    if( m_eDepth != SEFrameBuffer::DT_DEPTH_NONE )
    {
        aiAttributes[iPos++] = AGL_DEPTH_SIZE;
        if( m_eDepth == SEFrameBuffer::DT_DEPTH_16 )
        {
            aiAttributes[iPos++] = 16;
        }
        else if( m_eDepth == SEFrameBuffer::DT_DEPTH_24 )
        {
            aiAttributes[iPos++] = 24;
        }
        else // m_eDepth == FrameBuffer::DT_DEPTH_32
        {
            aiAttributes[iPos++] = 32;
        }
    }

    // Request a stencil buffer.
    if( m_eStencil == SEFrameBuffer::ST_STENCIL_8 )
    {
        aiAttributes[iPos++] = AGL_STENCIL_SIZE;
        aiAttributes[iPos++] = 8;
    }

    // Request buffering.
    if( m_eBuffering == SEFrameBuffer::BT_BUFFERED_DOUBLE )
    {
        aiAttributes[iPos++] = AGL_DOUBLEBUFFER;
    }

    // Request sampling.
    if( m_eMultisampling != SEFrameBuffer::MT_SAMPLING_NONE )
    {
        aiAttributes[iPos++] = AGL_SAMPLE_BUFFERS_ARB;
        aiAttributes[iPos++] = 1;
        aiAttributes[iPos++] = AGL_SAMPLES_ARB;
        if( m_eMultisampling == SEFrameBuffer::MT_SAMPLING_2 )
        {
            aiAttributes[iPos++] = 2;
        }
        else  // m_eMultisampling == FrameBuffer::MT_SAMPLING_4
        {
            aiAttributes[iPos++] = 4;
        }
    }

    // The list is zero terminated.
    aiAttributes[iPos] = AGL_NONE;

    AGLPixelFormat pPixelFormat = aglChoosePixelFormat(&m_hAglDevice, 1, 
        aiAttributes);
    if( !pPixelFormat )
    {
        // Retry without specifying a device.
        pPixelFormat = aglChoosePixelFormat(0, 0, aiAttributes);
        if( !pPixelFormat )
        {
            FatalErrorMessage("Cannot choose pixel format.");
        }
    }
    
    // Create an OpenGL context.
    m_pAglContext = aglCreateContext(pPixelFormat, 0);
    if( !m_pAglContext || aglGetError() != noErr )
    {
        FatalErrorMessage("Cannot create rendering context.");
    }
    if( !aglSetDrawable(m_pAglContext,m_pAglDrawable )
    ||   aglGetError() != noErr)
    {
        FatalErrorMessage("Cannot set the current drawable.");
    }
    if( !aglSetCurrentContext(m_pAglContext) || aglGetError() != noErr )
    {
        FatalErrorMessage("Cannot set the current rendering context.");
    }
    aglDestroyPixelFormat(pPixelFormat);
    SetUpBufferRect();

    // Create default screen text font.
    const char* acDefaultName = "Monaco";
    int iDefaultSize = 9;
    int iFontID = LoadFont(acDefaultName, iDefaultSize, false, false);
    assert( iFontID == 0 );
    (void)iFontID;  // avoid warning in release build
    
    // Complete initialization.
    // Load the function pointers for the OpenGL extensions.  This only
    // needs to occur once.  If you want a file to be created that stores
    // the OpenGL driver information, change the input filename to a
    // valid string; for example, "OpenGLDriverInfo.txt".
    const char* acInfoFile = 0;
    SE_GL_Initialize(acInfoFile);
    InitializeState();

    // Disable vertical sync.  If you want to enable this, change the value
    // of iVSValue to 1.
    int iVSValue = 0;
    aglSetInteger(m_pAglContext, AGL_SWAP_INTERVAL, &iVSValue);

    // Allocate temporary back buffer to be used for font management.
    PixMapHandle hPixmap = (**(GDHandle)hDevice).gdPMap;
    Rect tempArea = { 0, 0, 32, 32 };
    int iDepth = GetPixDepth(hPixmap);
    
    OSErr iError = NewGWorld(&m_pBack, iDepth, &tempArea, 0, 0, 
        useTempMem | pixPurge);
    if( iError != noErr || !m_pBack )
    {
        FatalErrorMessage("Cannot initialize font management.");
    }

    // Assign desired font settings to back buffer.
    GWorldPtr pCurrentWorld;
    GDHandle tempCurrentDevice;
    GetGWorld(&pCurrentWorld, &tempCurrentDevice);
    SetGWorld(m_pBack, 0);

    Str255 tempFontName;
    tempFontName[0] = (int)strlen(acDefaultName);
    strcpy((char*)tempFontName+1, acDefaultName);
    short usFNum;
    GetFNum(tempFontName, &usFNum);
    TextFont(usFNum);
    TextSize(iDefaultSize);

    SetGWorld(pCurrentWorld, tempCurrentDevice);
}
//----------------------------------------------------------------------------
SEAglRenderer::~SEAglRenderer()
{
    if( m_bFullScreen )
    {
        ToggleFullscreen();
    }

    for( int i = 0; i < (int)m_DLInfo.size(); i++ )
    {
        DisplayListInfo tempInfo = m_DLInfo[i];
        glDeleteLists(tempInfo.Start, tempInfo.Count);
    }

    DisposeGWorld(m_pBack);
    aglSetDrawable(m_pAglContext, 0);
    aglDestroyContext(m_pAglContext);
}
//----------------------------------------------------------------------------
void SEAglRenderer::Resize(int iWidth, int iHeight)
{
    AGLContext tempAglContext = aglGetCurrentContext();
    if( tempAglContext != m_pAglContext )
    {
        aglSetCurrentContext(m_pAglContext);
    }

    SEOpenGLRenderer::Resize(iWidth, iHeight);
    SetUpBufferRect();

    if( tempAglContext != m_pAglContext )
    {
        aglSetCurrentContext(tempAglContext);
    }
}
//----------------------------------------------------------------------------
void SEAglRenderer::ToggleFullscreen()
{
    SEOpenGLRenderer::ToggleFullscreen();
    glFinish();

    if( m_bFullScreen )
    {
        PixMapHandle hPixmap = (**(GDHandle)m_hAglDevice).gdPMap;
        Rect tempArea;
        GetPixBounds(hPixmap, &tempArea);
        int iWidth = tempArea.right - tempArea.left;
        int iHeight = tempArea.bottom - tempArea.top;
        int iDepth = GetPixDepth(hPixmap);

        if( !ms_bDSpStarted )
        {
            if( DSpStartup() != noErr )
            {
                FatalErrorMessage("FullScreen: Cannot start DrawSprocket.");
            }
            ms_bDSpStarted = true;
        }

        DSpContextAttributes tempContextAttributes;
        BlockZero(&tempContextAttributes, sizeof(DSpContextAttributes));
        tempContextAttributes.displayWidth = iWidth;
        tempContextAttributes.displayHeight = iHeight;
        tempContextAttributes.displayBestDepth = iDepth;
        tempContextAttributes.backBufferBestDepth = iDepth;
        tempContextAttributes.colorNeeds = kDSpColorNeeds_Require;
        tempContextAttributes.displayDepthMask =
            (OptionBits)(kDSpDepthMask_All);
        tempContextAttributes.backBufferDepthMask =
            (OptionBits)(kDSpDepthMask_All);
        tempContextAttributes.pageCount = 1;
        OSStatus eErr = DSpFindBestContext(&tempContextAttributes,
            &m_pDSpContext);
        if( eErr != noErr || !m_pDSpContext )
        {
            FatalErrorMessage("FullScreen: Cannot find best context.");
        }
        if( tempContextAttributes.gameMustConfirmSwitch )
        {
            FatalErrorMessage("FullScreen: Must confirm switch.");
        }
        eErr = DSpContext_Reserve(m_pDSpContext, &tempContextAttributes);
        if( eErr != noErr )
        {
            FatalErrorMessage("FullScreen: Cannot reserve context.");
        }
        eErr = DSpContext_SetState(m_pDSpContext, kDSpContextState_Active);
        if( eErr != noErr )
        {
            FatalErrorMessage("FullScreen: Cannot activate context.");
        }
        eErr = DSpContext_GetFrontBuffer(m_pDSpContext,
            &m_pFullScreenDrawable);
        if( eErr != noErr || !m_pFullScreenDrawable )
        {
            FatalErrorMessage("FullScreen: Cannot get front buffer.");
        }

        if( !aglSetDrawable(m_pAglContext, m_pFullScreenDrawable)
        ||   aglGetError() != noErr )
        {
            FatalErrorMessage("FullScreen: Cannot set new drawable.");
        }
        aglUpdateContext(m_pAglContext);

        // TO DO.  Why do we need to save these?
        m_iSaveWidth = iWidth;
        m_iSaveHeight = iHeight;
    }
    else
    {
        aglSetDrawable(m_pAglContext, 0);
        if( m_pDSpContext )
        {
            OSStatus eErr = DSpContext_SetState(m_pDSpContext,
                kDSpContextState_Inactive);
            if( eErr != noErr )
            {
                FatalErrorMessage("FullScreen: Cannot deactivate context.");
            }
            eErr = DSpContext_Release(m_pDSpContext);
            if( eErr != noErr )
            {
                FatalErrorMessage("FullScreen: Cannot release context.");
            }
            m_pDSpContext = 0;
            m_pFullScreenDrawable = 0;
        }
        
        aglSetDrawable(m_pAglContext, m_pAglDrawable);
        aglUpdateContext(m_pAglContext);
        
        // TO DO.  Why do we need the tempArea dimensions?
        CGrafPtr tempPtrPort = (CGrafPtr)m_pAglDrawable;
        Rect tempArea;
        GetPortBounds(tempPtrPort, &tempArea);
        m_iSaveWidth = tempArea.right - tempArea.left;
        m_iSaveHeight = tempArea.bottom - tempArea.top;
    }
}
//----------------------------------------------------------------------------
bool SEAglRenderer::BeginScene()
{
    if( aglGetCurrentContext() != m_pAglContext )
    {
        return aglSetCurrentContext(m_pAglContext);
    }

    return true;
}
//----------------------------------------------------------------------------
void SEAglRenderer::DisplayBackBuffer()
{
    if( aglGetDrawable(m_pAglContext) )
    {
        aglSwapBuffers(m_pAglContext);
    }
}
//----------------------------------------------------------------------------
int SEAglRenderer::LoadFont(const char* acFace, int iSize, bool bBold,
    bool bItalic)
{
    DisplayListInfo tempInfo;
    tempInfo.Count = 256;
    tempInfo.Start = glGenLists(256);
    tempInfo.Base = 1;
    m_DLInfo.push_back(tempInfo);

    Str255 tempFontName;
    tempFontName[0] = (int)strlen(acFace);
    strcpy((char*)tempFontName+1, acFace);

    short usFNum;
    GetFNum(tempFontName, &usFNum);

    Style cStyle = normal;
    if( bBold )
    {
        cStyle |= bold;
    }
    if( bItalic )
    {
        cStyle |= italic;
    }

    if( !aglUseFont(m_pAglContext, usFNum, cStyle, iSize, 0, tempInfo.Count,
        tempInfo.Start) )
    {
        glDeleteLists(tempInfo.Start, tempInfo.Count);
        m_DLInfo.pop_back();
    }
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    return (int)m_DLInfo.size() - 1;
}
//----------------------------------------------------------------------------
AGLDevice SEAglRenderer::GetDevice()
{
    return m_hAglDevice;
}
//----------------------------------------------------------------------------
WindowRef SEAglRenderer::GetWindow()
{
    return m_pAglWindow;
}
//----------------------------------------------------------------------------
AGLDrawable SEAglRenderer::GetDrawable()
{
    return m_pAglDrawable;
}
//----------------------------------------------------------------------------
AGLContext SEAglRenderer::GetContext()
{
    return m_pAglContext;
}
//----------------------------------------------------------------------------
void SEAglRenderer::SetUpBufferRect()
{
    // If the context is smaller than the underlying surface, we clip it.
    CGrafPtr tempPtrPort = aglGetDrawable(m_pAglContext);
    Rect tempPortRect = { 0 };
    GetPortBounds(tempPtrPort, &tempPortRect);
    int iPortWidth = tempPortRect.right - tempPortRect.left;
    int iPortHeight = tempPortRect.bottom - tempPortRect.top;
    if( iPortWidth != m_iWidth || iPortHeight != m_iHeight )
    {
        int iHeight = iPortHeight + 1;
        int iY = iHeight - m_iY;
        if( --iY < 0 )
        {
            iY = 0;
        }
        GLint aiRect[4] = { m_iX, iY - m_iHeight, m_iWidth, m_iHeight };
        if( !aglSetInteger(m_pAglContext, AGL_BUFFER_RECT, aiRect) )
        {
            FatalErrorMessage("Cannot assign AGL_BUFFER_RECT.");
        }
        if( !aglEnable(m_pAglContext, AGL_BUFFER_RECT) )
        {
            FatalErrorMessage("Cannot enable AGL_BUFFER_RECT.");
        }
        aglUpdateContext(m_pAglContext);
    }
    else
    {
        if( !aglDisable(m_pAglContext, AGL_BUFFER_RECT) )
        {
            FatalErrorMessage("Cannot disable AGL_BUFFER_RECT.");
        }
        aglUpdateContext(m_pAglContext);
    }
}
//----------------------------------------------------------------------------
void SEAglRenderer::FatalErrorMessage(const char* acMessage)
{
    if( m_pDSpContext )
    {
        DSpContextState tempContextState;
        if( DSpContext_GetState(m_pDSpContext, &tempContextState) == noErr
        &&  tempContextState == kDSpContextState_Active )
        {
            DSpContext_SetState(m_pDSpContext, kDSpContextState_Inactive);
            DSpContext_Release(m_pDSpContext);
        }
    }
    
    char acHeader[256];
    GLenum eAglError = aglGetError();
    sprintf(acHeader, "AglRenderer encountered error %ld.", (long)eAglError);
    Str255 tempHeader;
    tempHeader[0] = strlen(acHeader);
    strncpy((char*)tempHeader+1, acHeader, tempHeader[0]);

    int iLength = strlen(acMessage);
    Str255 tempMessage;
    tempMessage[0] = iLength;
    strncpy((char*)tempMessage+1, acMessage, iLength);
    SInt16 siItem;
    StandardAlert(kAlertStopAlert, tempHeader, tempMessage, 0, &siItem);
    ExitToShell();
}
//----------------------------------------------------------------------------

