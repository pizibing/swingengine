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

#include <Carbon/Carbon.h>
#include <unistd.h>

using namespace std;

#include "SEWindowApplication.h"
#include "SEAglRenderer.h"
#include "SEAalRenderer.h"

using namespace Swing;

const int SEWindowApplication::KEY_ESCAPE = kEscapeCharCode;
const int SEWindowApplication::KEY_LEFT_ARROW = kLeftArrowCharCode;
const int SEWindowApplication::KEY_RIGHT_ARROW = kRightArrowCharCode;
const int SEWindowApplication::KEY_UP_ARROW = kUpArrowCharCode;
const int SEWindowApplication::KEY_DOWN_ARROW = kDownArrowCharCode;
const int SEWindowApplication::KEY_HOME = kHomeCharCode;
const int SEWindowApplication::KEY_END = kEndCharCode;
const int SEWindowApplication::KEY_PAGE_UP = kPageUpCharCode;
const int SEWindowApplication::KEY_PAGE_DOWN = kPageDownCharCode;
const int SEWindowApplication::KEY_INSERT = kHelpCharCode;
const int SEWindowApplication::KEY_DELETE = kDeleteCharCode;
const int SEWindowApplication::KEY_BACKSPACE = kBackspaceCharCode;
const int SEWindowApplication::KEY_TAB = kTabCharCode;
const int SEWindowApplication::KEY_ENTER = kEnterCharCode;
const int SEWindowApplication::KEY_RETURN = kReturnCharCode;

// Function key values are actually key codes rather than char codes because
// MacOS passes all function key values as kFunctionKeyCharCode.
const int SEWindowApplication::KEY_F1 = 122;
const int SEWindowApplication::KEY_F2 = 120;
const int SEWindowApplication::KEY_F3 = 99;
const int SEWindowApplication::KEY_F4 = 118;
const int SEWindowApplication::KEY_F5 = 96;
const int SEWindowApplication::KEY_F6 = 97;
const int SEWindowApplication::KEY_F7 = 98;
const int SEWindowApplication::KEY_F8 = 100;
const int SEWindowApplication::KEY_F9 = 101;
const int SEWindowApplication::KEY_F10 = 109;
const int SEWindowApplication::KEY_F11 = 103;
const int SEWindowApplication::KEY_F12 = 111;

const int SEWindowApplication::KEY_SHIFT = shiftKey | rightShiftKey;
const int SEWindowApplication::KEY_CONTROL = controlKey | rightControlKey;
const int SEWindowApplication::KEY_ALT = optionKey | rightOptionKey;
const int SEWindowApplication::KEY_COMMAND = cmdKey;

const int SEWindowApplication::MOUSE_LEFT_BUTTON = kEventMouseButtonPrimary;
const int SEWindowApplication::MOUSE_MIDDLE_BUTTON = kEventMouseButtonTertiary;
const int SEWindowApplication::MOUSE_RIGHT_BUTTON = kEventMouseButtonSecondary;
const int SEWindowApplication::MOUSE_UP = 0;
const int SEWindowApplication::MOUSE_DOWN = 1;

const int SEWindowApplication::MODIFIER_CONTROL = controlKey | rightControlKey;
const int SEWindowApplication::MODIFIER_LBUTTON = kEventMouseButtonPrimary;
const int SEWindowApplication::MODIFIER_MBUTTON = kEventMouseButtonTertiary;
const int SEWindowApplication::MODIFIER_RBUTTON = kEventMouseButtonSecondary;
const int SEWindowApplication::MODIFIER_SHIFT   = shiftKey | rightShiftKey;

// Indices into the extra data storage for some system data.
#define AGLAPP_BACK   0
#define AGLAPP_FONT   AGLAPP_BACK + sizeof(GWorldPtr)
#define AGLAPP_SYSTEM AGLAPP_FONT + sizeof(SInt32)

//----------------------------------------------------------------------------
void SEWindowApplication::SetMousePosition(int iX, int iY)
{
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    Point tempMouseLoc;
    tempMouseLoc.h = (short)iX;
    tempMouseLoc.v = (short)iY;
    LocalToGlobal(&tempMouseLoc);
    SetPort(tempPtrPort);

    CGPoint tempPoint = CGPointMake((float)tempMouseLoc.h, 
        (float)tempMouseLoc.v);
    CGPostMouseEvent(tempPoint, true, 1, false, 0);
}
//----------------------------------------------------------------------------
void SEWindowApplication::GetMousePosition(int& riX, int& riY) const
{
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    ::Point tempMouseLoc;
    GetMouse(&tempMouseLoc);
    SetPort(tempPtrPort);
    
    riX = (int)tempMouseLoc.h;
    riY = (int)tempMouseLoc.v;
}
//----------------------------------------------------------------------------
int SEWindowApplication::GetStringWidth(const char* acText) const
{
    GWorldPtr tempPtrWorld;
    GDHandle tempDevice;
    GetGWorld(&tempPtrWorld, &tempDevice);

    GWorldPtr tempPtrBack;
    GetExtraData(AGLAPP_BACK, sizeof(GWorldPtr), &tempPtrBack);
    SetGWorld(tempPtrBack, 0);

    int iWidth = TextWidth(acText, 0, strlen(acText));

    SetGWorld(tempPtrWorld, tempDevice);
    return iWidth;
}
//----------------------------------------------------------------------------
int SEWindowApplication::GetCharacterWidth(const char cCharacter) const
{
    GWorldPtr tempPtrWorld;
    GDHandle tempDevice;
    GetGWorld(&tempPtrWorld, &tempDevice);

    GWorldPtr tempPtrBack;
    GetExtraData(AGLAPP_BACK, sizeof(GWorldPtr), &tempPtrBack);
    SetGWorld(tempPtrBack, 0);

    int iWidth = ::CharWidth(cCharacter);

    SetGWorld(tempPtrWorld, tempDevice);
    return iWidth;
}
//----------------------------------------------------------------------------
int SEWindowApplication::GetFontHeight() const
{
    GWorldPtr tempPtrWorld;
    GDHandle tempDevice;
    GetGWorld(&tempPtrWorld, &tempDevice);

    GWorldPtr tempPtrBack;
    GetExtraData(AGLAPP_BACK, sizeof(GWorldPtr), &tempPtrBack);
    SetGWorld(tempPtrBack, 0);
    
    FontInfo tempFontInfo;
    GetFontInfo(&tempFontInfo);
    
    SetGWorld(tempPtrWorld, tempDevice);
    return tempFontInfo.ascent + tempFontInfo.descent + tempFontInfo.leading;
}
//----------------------------------------------------------------------------
static OSErr MacApplicationAEGetDescData(const AEDesc* pDesc, 
    DescType* piTypeCode, void* pvDataBuffer, ByteCount iMaximumSize, 
    ByteCount* piActualSize)
{
    OSErr iTheErr = noErr;
    ByteCount iDataSize;

    if( piTypeCode && pDesc )
    {
        *piTypeCode = pDesc->descriptorType;
    }

    iDataSize = AEGetDescDataSize(pDesc);
    if( piActualSize )
    {
        *piActualSize = iDataSize;
    }

    if( iDataSize > 0 && iMaximumSize > 0 )
    {
        iTheErr = AEGetDescData(pDesc, pvDataBuffer, iMaximumSize);
    }

    return iTheErr;
}
//----------------------------------------------------------------------------
static OSErr MacApplicationNavGetFile(FSSpecPtr pTheFileP, 
    Boolean* pbGotFile)
{   
    NavDialogOptions tempDialogOptions; 
    OSErr iTheErr = NavGetDefaultDialogOptions(&tempDialogOptions);
    tempDialogOptions.dialogOptionFlags =
        (kNavDefaultNavDlogOptions | kNavNoTypePopup) &
        ~kNavAllowPreviews & ~kNavAllowMultipleFiles;

    NavReplyRecord tempTheReply;
    NavEventUPP pEventProc = 0;
    iTheErr = NavGetFile(0, &tempTheReply, &tempDialogOptions, pEventProc, 0, 
        0, 0, (NavCallBackUserData)0);

    if( tempTheReply.validRecord && iTheErr == noErr )
    {
        long lCount;
        iTheErr = AECountItems(&tempTheReply.selection, &lCount);
        if( iTheErr == noErr )
        {
            long lIndex = 1;
            AEDesc tempResultDesc;
            AEKeyword tempKeyWord;
            iTheErr = AEGetNthDesc(&tempTheReply.selection, lIndex, typeFSS, 
                &tempKeyWord, &tempResultDesc);

            if( iTheErr == noErr )
            {
                DescType iTypeCode = typeFSS;
                ByteCount iC;

                iTheErr = MacApplicationAEGetDescData(&tempResultDesc, 
                    &iTypeCode, pTheFileP, sizeof(FSSpec), &iC);
                *pbGotFile = true;
                iTheErr = AEDisposeDesc(&tempResultDesc);
            }
        }

        iTheErr = NavDisposeReply(&tempTheReply);
    }
    else
    {
        *pbGotFile = false;
    }

    return iTheErr;
}
//----------------------------------------------------------------------------
static Boolean MacApplicationOpenFile(FSSpecPtr pDesFile)
{
    FSSpec tempTheFile;
    Boolean bGotFile = false;
    OSErr iErr = MacApplicationNavGetFile(&tempTheFile, &bGotFile);
    if( iErr == noErr && bGotFile )
    {
        *pDesFile = tempTheFile;
    }

    return bGotFile;
}
//----------------------------------------------------------------------------
static string GetStringPathname(FSSpec& rSrcFile)
{
    FSRef tempFileRef;
    FSpMakeFSRef(&rSrcFile, &tempFileRef);

    CFURLRef tempPtrURL = CFURLCreateFromFSRef(0, &tempFileRef);
    CFStringRef tempString = CFURLCopyFileSystemPath(tempPtrURL, 
        kCFURLPOSIXPathStyle);
    char acPath[256];
    CFStringGetCString(tempString, acPath, 256, CFStringGetSystemEncoding());
    CFRelease(tempString);
    CFRelease(tempPtrURL);
    std::string tempFileName(acPath);

    return tempFileName;
}
//----------------------------------------------------------------------------
static char* GetCommandLine()
{
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    OSErr iErr = noErr;
    SInt32 iSystemVersion;
    iErr = Gestalt(gestaltSystemVersion, &iSystemVersion);
    pTheApp->SetExtraData(AGLAPP_SYSTEM, sizeof(SInt32), &iSystemVersion);
    if( iErr != noErr )
    {
        return 0;
    }

    FILE* pTempFile = fopen("cmdline.txt", "rb");
    if( pTempFile == 0 )
    {
        FSSpec tempFile;
        if( MacApplicationOpenFile(&tempFile) )
        {
            string tempName = GetStringPathname(tempFile);
            char* pcTheFile = SE_NEW char[tempName.length()+1];
            strcpy(pcTheFile, tempName.c_str());

            return pcTheFile;
        }

        return 0;
    }

    // get size of file
    unsigned int uiFileSize = 0;
    while( fgetc(pTempFile) != EOF )
    {
        uiFileSize++;
    }
    
    if( uiFileSize == 0 )
    {
        fclose(pTempFile);
        return 0;
    }
    
    // read file
    fseek(pTempFile, 0, SEEK_SET);
    char* pcCmdLine = SE_NEW char[uiFileSize+1];
    char* pcIterator = pcCmdLine;
    char c;
    while( (c = (char)fgetc(pTempFile)) != EOF )
    {
        // cull out non-printable characters
       *pcIterator++ = (isprint(c) ? c : ' ');
            
    }
    *pcIterator = '\0';
    
    fclose(pTempFile);
    return pcCmdLine;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessWindowClose(EventHandlerCallRef pNextHandler, 
    EventRef pEvent, void*)
{
    // allow standard handler to run
    OSStatus eResult = CallNextEventHandler(pNextHandler, pEvent);

    // quit the application
    QuitApplicationEventLoop();
    
    return eResult;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessWindowBoundsChange(EventHandlerCallRef, 
    EventRef pEvent, void*)
{
    UInt32 uiAttributes;
    GetEventParameter(pEvent, kEventParamAttributes, typeUInt32, 0, 
        sizeof(uiAttributes), 0, &uiAttributes);

    Rect tempRect;
    GetEventParameter(pEvent, kEventParamCurrentBounds, typeQDRectangle, 0, 
        sizeof(tempRect), 0, &tempRect);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    if( uiAttributes & kWindowBoundsChangeUserDrag
    ||  uiAttributes & kWindowBoundsChangeOriginChanged )
    {
        // bounds are changing due to window moving
        pTheApp->OnMove(tempRect.top, tempRect.left);
    }
    else if( uiAttributes & kWindowBoundsChangeUserResize
    ||  uiAttributes & kWindowBoundsChangeSizeChanged )
    {
        // bounds are changing due to window resizing
        pTheApp->OnResize(tempRect.right-tempRect.left, 
            tempRect.bottom-tempRect.top);
    }

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessWindowZoomed(EventHandlerCallRef, 
    EventRef pEvent, void*)
{
    WindowRef tempWindow;
    GetEventParameter(pEvent, kEventParamDirectObject, typeWindowRef, 0, 
        sizeof(tempWindow) , 0, &tempWindow);

    Rect tempRect;
    GetWindowBounds(tempWindow, kWindowContentRgn, &tempRect);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    pTheApp->OnResize(tempRect.right-tempRect.left, 
        tempRect.bottom-tempRect.top);

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessWindowRedraw(EventHandlerCallRef, EventRef, 
    void*)
{
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    pTheApp->OnDisplay();

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessKeyDown(EventHandlerCallRef, EventRef pEvent, 
    void*)
{
    char cCharCode;
    GetEventParameter(pEvent, kEventParamKeyMacCharCodes, typeChar, 0, 
        sizeof(cCharCode), 0, &cCharCode);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;
    
    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    ::Point tempMouseLoc;
    GetMouse(&tempMouseLoc);
    SetPort(tempPtrPort);
    
    if( cCharCode == kEscapeCharCode )
    {
        // quit the application when 'esc' is pressed
        QuitApplicationEventLoop();
        return eventNotHandledErr;
    }

    if( isalnum(cCharCode) || isprint(cCharCode) )
    {
        pTheApp->OnKeyDown(cCharCode, tempMouseLoc.h, tempMouseLoc.v);
    }
    else
    {
       if( cCharCode == kFunctionKeyCharCode )
       {
           // function key - get key identity
           UInt32 uiKeyCode;
           GetEventParameter(pEvent, kEventParamKeyCode, typeUInt32, 0, 
               sizeof(uiKeyCode), 0, &uiKeyCode);
           
           cCharCode = uiKeyCode & 0x000000FF; 
       }

       // Do not filter for specific keys.  This allows for keys such as tab, 
       // delete, enter.
       pTheApp->OnSpecialKeyDown(cCharCode, tempMouseLoc.h, tempMouseLoc.v);
    }

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessKeyUp(EventHandlerCallRef, EventRef pEvent, 
    void*)
{
    char cCharCode;
    GetEventParameter(pEvent, kEventParamKeyMacCharCodes, typeChar, 0, 
        sizeof(cCharCode), 0, &cCharCode);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;
    
    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    ::Point tempMouseLoc;
    GetMouse(&tempMouseLoc);
    SetPort(tempPtrPort);
    
    if( isalnum(cCharCode) || isprint(cCharCode) )
    {
        pTheApp->OnKeyUp(cCharCode, tempMouseLoc.h, tempMouseLoc.v);
    }
    else
    {
        if( cCharCode == kFunctionKeyCharCode )
        {
            // function key - get key identity
            UInt32 uiKeyCode;
            GetEventParameter(pEvent, kEventParamKeyCode, typeUInt32, 0, 
                sizeof(uiKeyCode), 0, &uiKeyCode);
            
            cCharCode = uiKeyCode & 0x000000FF; 
        }
        
        // Do not filter for specific keys.  This allows for keys such as tab, 
        // delete, enter.
        pTheApp->OnSpecialKeyUp(cCharCode, tempMouseLoc.h, tempMouseLoc.v);
    }

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessMouseDown(EventHandlerCallRef, 
    EventRef pEvent, void*)
{
    ::Point tempMouseLoc;    
    GetEventParameter(pEvent, kEventParamMouseLocation, typeQDPoint, 0, 
        sizeof(tempMouseLoc), 0, &tempMouseLoc);

    EventMouseButton eMouseButton;
    GetEventParameter(pEvent, kEventParamMouseButton, typeMouseButton, 0, 
        sizeof(eMouseButton), 0, &eMouseButton);

    UInt32 uiModifiers;
    GetEventParameter(pEvent, kEventParamKeyModifiers, typeUInt32, 0, 
        sizeof(uiModifiers), 0, &uiModifiers);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    GlobalToLocal(&tempMouseLoc);
    SetPort(tempPtrPort);

    pTheApp->OnMouseClick(eMouseButton, SEWindowApplication::MOUSE_DOWN, 
        tempMouseLoc.h, tempMouseLoc.v, uiModifiers);

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessMouseUp(EventHandlerCallRef, EventRef pEvent, 
    void*)
{
    ::Point tempMouseLoc;    
    GetEventParameter(pEvent, kEventParamMouseLocation, typeQDPoint, 0, 
        sizeof(tempMouseLoc), 0, &tempMouseLoc);

    EventMouseButton eMouseButton;
    GetEventParameter(pEvent, kEventParamMouseButton, typeMouseButton, 0, 
        sizeof(eMouseButton), 0, &eMouseButton);

    UInt32 uiModifiers;
    GetEventParameter(pEvent, kEventParamKeyModifiers, typeUInt32, 0, 
        sizeof(uiModifiers), 0, &uiModifiers);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    GlobalToLocal(&tempMouseLoc);
    SetPort(tempPtrPort);

    pTheApp->OnMouseClick(eMouseButton, SEWindowApplication::MOUSE_UP, 
        tempMouseLoc.h, tempMouseLoc.v, uiModifiers);

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessMouseDragged(EventHandlerCallRef, 
    EventRef pEvent, void*)
{
    ::Point tempMouseLoc;    
    GetEventParameter(pEvent, kEventParamMouseLocation, typeQDPoint, 0, 
        sizeof(tempMouseLoc), 0, &tempMouseLoc);

    EventMouseButton eMouseButton;
    GetEventParameter(pEvent, kEventParamMouseButton, typeMouseButton, 0, 
        sizeof(eMouseButton), 0, &eMouseButton);

    UInt32 uiModifiers;
    GetEventParameter(pEvent, kEventParamKeyModifiers, typeUInt32, 0, 
        sizeof(uiModifiers), 0, &uiModifiers);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    GlobalToLocal(&tempMouseLoc);
    SetPort(tempPtrPort);

    pTheApp->OnMotion(eMouseButton, tempMouseLoc.h, tempMouseLoc.v, 
        uiModifiers);

    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal OSStatus ProcessMouseMoved(EventHandlerCallRef, 
    EventRef pEvent, void*)
{
    ::Point tempMouseLoc;    
    GetEventParameter(pEvent, kEventParamMouseLocation, typeQDPoint, 0, 
        sizeof(tempMouseLoc), 0, &tempMouseLoc);

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    CGrafPtr tempPtrPort;
    GetPort(&tempPtrPort);
    SetPortWindowPort((WindowRef)(pTheApp->GetWindowID()));
    GlobalToLocal(&tempMouseLoc);
    SetPort(tempPtrPort);

    pTheApp->OnPassiveMotion(tempMouseLoc.h, tempMouseLoc.v);
    
    // allow standard handler to run
    return eventNotHandledErr;
}
//----------------------------------------------------------------------------
static pascal void ProcessTimer(EventLoopTimerRef, void*)
{
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    pTheApp->OnIdle();
}
//----------------------------------------------------------------------------
static OSErr QuitAppleEventHandler(const AppleEvent*, AppleEvent*, UInt32)
{
    QuitApplicationEventLoop();

    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;

    GWorldPtr tempPtrBack;
    pTheApp->GetExtraData(AGLAPP_BACK, sizeof(GWorldPtr), &tempPtrBack);
    DisposeGWorld(tempPtrBack);

    return noErr;
}
//----------------------------------------------------------------------------
int SEWindowApplication::Main(int, char**)
{
    InitCursor();
    
    SEWindowApplication* pTheApp =
        (SEWindowApplication*)SEApplication::TheApplication;
    assert( pTheApp );
    if( !pTheApp )
    {
        return -1;
    }
    
    // allocate temporary back buffer to be used for font management    
    GDHandle tempDevice = GetGDevice();
    PixMapHandle tempPixmap = (**tempDevice).gdPMap;
    Rect tempArea;
    GetPixBounds(tempPixmap, &tempArea);
    int iDepth = GetPixDepth(tempPixmap);
    GWorldPtr tempPtrBack;
    OSErr iError = NewGWorld(&tempPtrBack, iDepth, &tempArea, 0, 0, 
        useTempMem | pixPurge);
    if( iError != noErr || !tempPtrBack )
    {
        assert( false );
        return -2;
    }

    SetExtraData(AGLAPP_BACK, sizeof(GWorldPtr), &tempPtrBack);
    
    // assign desired font settings to back buffer
    unsigned char aucFontName[256];
    strcpy((char*)&aucFontName[1], "Monaco");
    aucFontName[0] = 6;
    short sFont;
    GetFNum(aucFontName, &sFont);
    SetExtraData(AGLAPP_FONT, sizeof(short), &sFont);

    GWorldPtr tempPtrCurrentWorld;
    GDHandle tempCurrentDevice;
    GetGWorld(&tempPtrCurrentWorld, &tempCurrentDevice);
    SetGWorld(tempPtrBack, 0);

    TextFont(sFont);
    TextSize(9);
    TextFace(normal);
    SetGWorld(tempPtrCurrentWorld, tempCurrentDevice);
    
    // add standard window menu
    MenuRef tempPtrMenu = 0;
    CreateStandardWindowMenu(0, &tempPtrMenu);
    InsertMenu(tempPtrMenu, 0);
    
    // change current directory into application bundle.
    FSRef tempProcessRef;
    FSCatalogInfo tempProcessInfo;
    ProcessSerialNumber tempPSN = { 0, kCurrentProcess };
    GetProcessBundleLocation(&tempPSN, &tempProcessRef);
    FSSpec tempFileSpec;
    FSGetCatalogInfo(&tempProcessRef, kFSCatInfoNodeFlags, &tempProcessInfo, 0, 
        &tempFileSpec, 0);
    string tempStrAppFile = GetStringPathname(tempFileSpec);
    const int iMaxPathLen = 1024;
    char acPath[iMaxPathLen];
    strcpy(acPath, tempStrAppFile.c_str());
    char* pcLast = strrchr(acPath, '/');
    *pcLast = 0;
    int iResult = chdir(acPath);
    assert( iResult == 0 );
    
    // If the application is packaged, we have to get back up a couple of
    // levels such as the current working directory is the same as the
    // application's.    
    char acBuf[iMaxPathLen];
    char* acCurDir = getcwd(acBuf, iMaxPathLen);
    if( strstr(acCurDir, "/Contents/MacOS") )
    {
        iResult = chdir("../../..");
        assert(iResult == 0);
        acCurDir = getcwd(acBuf, iMaxPathLen);
    }

    // Launch a file dialog, if requested, when the application needs to
    // select an input file.  The derived-class application should set
    // m_bLaunchFileDialog to 'true' in its constructor when the dialog is
    // needed.
    if( pTheApp->LaunchFileDialog() )
    {
        char* acArgument = GetCommandLine();
        if( acArgument )
        {
            SE_DELETE pTheApp->TheCommand;
            pTheApp->TheCommand = SE_NEW SECommand(acArgument);
            SE_DELETE[] acArgument;
        }
    }

    if( !pTheApp->OnPrecreate() )
    {
        return -3;
    }
    
    // require the window to have the specified client area
    short sWindowTop = 60, sWindowLeft = 40;
    Rect tempRect = { sWindowTop, sWindowLeft, 
        pTheApp->GetHeight() + sWindowTop-1, 
        pTheApp->GetWidth() + sWindowLeft-1 };

    // create the application window
    WindowRef tempPtrWindow = 0;
    OSStatus eErr = CreateNewWindow(kDocumentWindowClass, 
        kWindowStandardDocumentAttributes | kWindowStandardHandlerAttribute, 
        &tempRect, &tempPtrWindow);
    if( eErr != noErr )
    {
        fprintf(stderr, "Create window error\n");
        return -4;
    }
    
    // Grab GD from tempRect - based on FindGDHandleFromRect in Carbon SetupGL
    GDHandle hGD = 0;
    GDHandle hgdNthDevice = GetDeviceList();
    unsigned int uiGreatestArea = 0;

    // Check window against all gdRects in gDevice list and remember which
    // gdRect contains largest area of window.
    while( hgdNthDevice )
    {
        if( TestDeviceAttribute(hgdNthDevice, screenDevice)
        &&  TestDeviceAttribute(hgdNthDevice, screenActive) )
        {
            // The SectRect routine calculates the intersection of the window
            // rectangle and this gDevice rectangle and returns TRUE if the
            // rectangles intersect, FALSE if they don't.
            Rect tempRectSect;
            SectRect(&tempRect, &(**hgdNthDevice).gdRect, &tempRectSect);

            // Determine which screen holds greatest window area first, 
            // calculate area of rectangle on current device.
            unsigned int uiSectArea = 
                (unsigned int)(tempRectSect.right - tempRectSect.left) * 
                (tempRectSect.bottom - tempRectSect.top);
            if( uiSectArea > uiGreatestArea )
            {
                uiGreatestArea = uiSectArea; // set greatest area so far
                hGD = hgdNthDevice; // set zoom device
            }
            hgdNthDevice = GetNextDevice(hgdNthDevice);
        }
    }

    // set window title
    CFStringRef tempPtrWindowTitle = CFStringCreateWithCString(0, 
        pTheApp->GetWindowTitle(), kCFStringEncodingASCII);
    SetWindowTitleWithCFString(tempPtrWindow, tempPtrWindowTitle);
    CFRelease(tempPtrWindowTitle);

    pTheApp->SetWindowID((int)tempPtrWindow);

    SetPortWindowPort(tempPtrWindow);
    pTheApp->SetRenderer(SE_NEW SEAglRenderer((AGLDevice)hGD, tempPtrWindow, 
        m_eFormat, m_eDepth, m_eStencil, m_eBuffering, m_eMultisampling, 0, 0, 
        pTheApp->GetWidth(), pTheApp->GetHeight()));

    // install quit apple event handler
    eErr = AEInstallEventHandler(kCoreEventClass, kAEQuitApplication, 
        NewAEEventHandlerUPP((AEEventHandlerProcPtr)QuitAppleEventHandler), 0, 
        false);
    if( eErr != noErr )
    {
        ExitToShell();
    }

    // install window close handler
    EventTypeSpec tempEventType;
    tempEventType.eventClass = kEventClassWindow;
    tempEventType.eventKind = kEventWindowClose;
    EventHandlerUPP pfnHandlerUPP = NewEventHandlerUPP(ProcessWindowClose); 
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install window bounds change handler
    tempEventType.eventKind = kEventWindowBoundsChanged;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessWindowBoundsChange);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install window zoomed handler
    tempEventType.eventKind = kEventWindowZoomed;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessWindowZoomed);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install window redraw handler
    tempEventType.eventKind = kEventWindowDrawContent;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessWindowRedraw);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install key down handler
    EventTypeSpec aEventType[2];
    aEventType[0].eventClass = kEventClassKeyboard;
    aEventType[0].eventKind = kEventRawKeyDown;
    aEventType[1].eventClass = kEventClassKeyboard;
    aEventType[1].eventKind = kEventRawKeyRepeat;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessKeyDown);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 2, aEventType, 0, 0);

    // install key up handler
    tempEventType.eventClass = kEventClassKeyboard;
    tempEventType.eventKind = kEventRawKeyUp;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessKeyUp);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install mouse down handler
    tempEventType.eventClass = kEventClassMouse;
    tempEventType.eventKind = kEventMouseDown;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessMouseDown);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install mouse up handler
    tempEventType.eventKind = kEventMouseUp;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessMouseUp);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install mouse drag handler
    tempEventType.eventKind = kEventMouseDragged;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessMouseDragged);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // install mouse move handler
    tempEventType.eventKind = kEventMouseMoved;
    pfnHandlerUPP = NewEventHandlerUPP(ProcessMouseMoved);
    InstallWindowEventHandler(tempPtrWindow, pfnHandlerUPP, 1, &tempEventType, 
        0, 0);

    // create timer
    EventLoopTimerRef tempPtrTimer;
    InstallEventLoopTimer(GetMainEventLoop(), 0, kEventDurationMillisecond, 
        NewEventLoopTimerUPP(ProcessTimer), 0, &tempPtrTimer);

    // create audio renderer
    pTheApp->SetAudioRenderer(SE_NEW SEAalRenderer);

    if( !pTheApp->OnInitialize() )
    {
        return -5;
    }

    // set auto-repeat key timing
    short sKeyRepeatThresh = LMGetKeyRepThresh();
    short sKeyThresh = LMGetKeyThresh();
    LMSetKeyRepThresh(1);
    LMSetKeyThresh(30);

    // display the window
    ShowWindow(tempPtrWindow);

    // run event loop
    RunApplicationEventLoop();

    // reset auto-repeat key timing to initial value
    LMSetKeyRepThresh(sKeyRepeatThresh);
    LMSetKeyThresh(sKeyThresh);

    pTheApp->OnTerminate();

    RemoveEventLoopTimer(tempPtrTimer);
    DisposeMenu(tempPtrMenu);

    return 0;
}
//----------------------------------------------------------------------------
void SEApplication::LaunchTreeControl(SESpatial*, int, int, int, int)
{
    // TO DO
}
//----------------------------------------------------------------------------
void SEApplication::ShutdownTreeControl()
{
    // TO DO
}
//----------------------------------------------------------------------------
