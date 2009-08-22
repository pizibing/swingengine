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

#include "SEOpenGLApplicationPCH.h"
#include "SETreeControl.h"

using namespace Swing;

//----------------------------------------------------------------------------
unsigned int TreeControl::ms_auiBmpClosedB[240] =
{
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xff0000ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff8080ff,
0xff8080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff8080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff8080ff,
0xff00ffff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff8080ff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff80ffff,
0xff00ffff,
0xff0080ff,
0xff000000,
0xffffffff,
0xff0000ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0080ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xff0000ff,
0xff80ffff,
0xff80ffff,
0xff00ffff,
0xff00ffff,
0xff00ffff,
0xff0000ff,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff0000ff,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff
};
//----------------------------------------------------------------------------
unsigned int TreeControl::ms_auiBmpClosedP[240] =
{
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xff800080,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xff8080ff,
0xff8080ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xff8080ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff8080ff,
0xffff00ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff8080ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffc0c0c0,
0xffff00ff,
0xff804000,
0xff000000,
0xffffffff,
0xff800080,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff804000,
0xff800080,
0xff800080,
0xff800080,
0xff800080,
0xff800080,
0xff800080,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xff800080,
0xffc0c0c0,
0xffc0c0c0,
0xffff00ff,
0xffff00ff,
0xffff00ff,
0xff800080,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xff800080,
0xff800080,
0xff800080,
0xff800080,
0xff800080,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff
};
//----------------------------------------------------------------------------
unsigned int TreeControl::ms_auiBmpClosedY[240] =
{
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xff909000,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xffffc890,
0xffffc890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xffffc890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffffc890,
0xfffff890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xfffff890,
0xffffc890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff8cf,
0xfffff890,
0xffcfc860,
0xff000000,
0xffffffff,
0xff909000,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xffcfc860,
0xff909000,
0xff909000,
0xff909000,
0xff909000,
0xff909000,
0xff909000,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xff909000,
0xfffff8cf,
0xfffff8cf,
0xfffff890,
0xfffff890,
0xfffff890,
0xff909000,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xff909000,
0xff909000,
0xff909000,
0xff909000,
0xff909000,
0xff000000,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff,
0xfffff8ff
};
//----------------------------------------------------------------------------
unsigned int TreeControl::ms_auiBmpAttribute[240] =
{
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xff000000,
0xff000000,
0xff000000,
0xff000000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff
};
//----------------------------------------------------------------------------
std::map<HWND, std::pair<Application*, int> > TreeControl::ms_WndAppMap;
//----------------------------------------------------------------------------
TreeControl::TreeControl(Application* pTheApp, int iExtraData,
    HINSTANCE hInstance, HWND hParentWnd, Stream& rStream,
    const char* acName, int iX, int iY, int iW, int iH)
{
    m_pTheApp = pTheApp;
    m_iExtraData = iExtraData;
    m_hInstance = hInstance;
    m_hParentWnd = hParentWnd;

    size_t uiSize = strlen(acName) + 1;
    m_acName = SE_NEW char[uiSize];
    System::SE_Strcpy(m_acName, uiSize, acName);

    CreateWindows(iX, iY, iW, iH);
    CreateImageList();
    CreateTree(rStream);

    ShowWindow(m_hTreeWnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hTreeWnd);
}
//----------------------------------------------------------------------------
TreeControl::TreeControl(Application* pTheApp, int iExtraData,
    HINSTANCE hInstance, HWND hParentWnd, Spatial* pScene, int iX, int iY,
    int iW, int iH)
{
    m_pTheApp = pTheApp;
    m_iExtraData = iExtraData;
    m_hInstance = hInstance;
    m_hParentWnd = hParentWnd;

    const char* acName = pScene->GetName();
    if( acName )
    {
        size_t uiSize = strlen(acName) + 1;
        m_acName = SE_NEW char[uiSize];
        System::SE_Strcpy(m_acName, uiSize, acName);
    }
    else
    {
        m_acName = SE_NEW char[8];
        System::SE_Strcpy(m_acName, 8, "unnamed");
    }

    CreateWindows(iX, iY, iW, iH);
    CreateImageList();
    CreateTree(pScene);

    ShowWindow(m_hTreeWnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hTreeWnd);
}
//----------------------------------------------------------------------------
TreeControl::~TreeControl()
{
    SE_DELETE[] m_acName;

    DestroyTree();
    DestroyImageList();
    DestroyWindows();
}
//----------------------------------------------------------------------------
void TreeControl::CreateWindows(int iX, int iY, int iW, int iH)
{
    static char s_acWindowClassName[] = "SETreeControl";

    // initialize tree view classes
#ifdef MINGW
    InitCommonControls();  // MINGW 4.1.0 does not support the "Ex" version.
#else
    INITCOMMONCONTROLSEX tempInitCC;
    tempInitCC.dwSize = sizeof(INITCOMMONCONTROLSEX);
    tempInitCC.dwICC = ICC_TREEVIEW_CLASSES;
    InitCommonControlsEx(&tempInitCC);
#endif

    // register the window class
    WNDCLASS tempWClass;
    tempWClass.style = CS_HREDRAW | CS_VREDRAW;
    tempWClass.lpfnWndProc = HandleMessage;
    tempWClass.cbClsExtra = 0;
    tempWClass.cbWndExtra = 0;
    tempWClass.hInstance = m_hInstance;
    tempWClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    tempWClass.hCursor = LoadCursor(NULL,IDC_ARROW);
    tempWClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    tempWClass.lpszClassName = s_acWindowClassName;
    tempWClass.lpszMenuName = NULL;
    RegisterClass(&tempWClass);

    // create the tree view window
    DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
        | WS_SIZEBOX;
    m_hTreeWnd = CreateWindow(s_acWindowClassName,m_acName,dwStyle,iX,iY,iW,
        iH,0,0,m_hInstance,NULL);

    // create the tree view
    dwStyle = WS_VISIBLE | WS_TABSTOP | WS_CHILD |
        TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;

    RECT tempRect;
    GetClientRect(m_hTreeWnd, &tempRect);

    m_hTreeView = CreateWindow(WC_TREEVIEW, "", dwStyle, 0, 0,
        tempRect.right-tempRect.left+1, tempRect.bottom-tempRect.top+1, m_hTreeWnd, 0,
        m_hInstance, NULL);

    ms_WndAppMap[m_hTreeWnd] = std::make_pair(m_pTheApp, m_iExtraData);
}
//----------------------------------------------------------------------------
void TreeControl::CreateImageList()
{
    HDC hWindowDC = GetDC(m_hTreeView);
    HDC hMemoryDC = CreateCompatibleDC(hWindowDC);

    const size_t uiLength = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD*);
    char* acBitMapInfo = SE_NEW char[uiLength];
    memset(acBitMapInfo, 0, uiLength);
    BITMAPINFOHEADER& bmih = *(BITMAPINFOHEADER*)acBitMapInfo;
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = 16;
    bmih.biHeight = 15;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 240;
    bmih.biXPelsPerMeter = 0;
    bmih.biYPelsPerMeter = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    unsigned int* auiColorBuffer = 0;
    HBITMAP hBitmap = 0;
    size_t uiSize = 240 * sizeof(unsigned int);

    m_hImageList = ImageList_Create(16, 15, ILC_COLOR32, 4, 1);

    hBitmap = CreateDIBSection(hMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
        DIB_RGB_COLORS, (void**)&auiColorBuffer, 0, 0);
    System::SE_Memcpy(auiColorBuffer, uiSize, ms_auiBmpClosedB, uiSize);
    m_iClosedB = ImageList_Add(m_hImageList, hBitmap, 0);
    DeleteObject(hBitmap);

    hBitmap = CreateDIBSection(hMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
        DIB_RGB_COLORS, (void**)&auiColorBuffer, 0, 0);
    System::SE_Memcpy(auiColorBuffer, uiSize, ms_auiBmpClosedY, uiSize);
    m_iClosedY = ImageList_Add(m_hImageList, hBitmap, 0);
    DeleteObject(hBitmap);

    hBitmap = CreateDIBSection(hMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
        DIB_RGB_COLORS, (void**)&auiColorBuffer, 0, 0);
    System::SE_Memcpy(auiColorBuffer, uiSize, ms_auiBmpClosedP, uiSize);
    m_iClosedP = ImageList_Add(m_hImageList, hBitmap, 0);
    DeleteObject(hBitmap);

    hBitmap = CreateDIBSection(hMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
        DIB_RGB_COLORS, (void**)&auiColorBuffer, 0, 0);
    System::SE_Memcpy(auiColorBuffer, uiSize, ms_auiBmpAttribute, uiSize);
    m_iAttribute = ImageList_Add(m_hImageList, hBitmap, 0);
    DeleteObject(hBitmap);

    SE_DELETE[] acBitMapInfo;
    DeleteDC(hMemoryDC);
    ReleaseDC(m_hTreeView, hWindowDC);
}
//----------------------------------------------------------------------------
void TreeControl::CreateTree(Stream& rStream)
{
    TreeView_SetImageList(m_hTreeView, m_hImageList, TVSIL_NORMAL);

    // items are to be inserted in-order
    TV_INSERTSTRUCT tvs;
    tvs.hInsertAfter = TVI_LAST;
    tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    // add root item (name is the input filename)
    tvs.hParent = TVI_ROOT;
    tvs.item.pszText = m_acName;
    tvs.item.iImage = m_iClosedB;
    tvs.item.iSelectedImage = m_iClosedB;
    m_hTreeRoot = TreeView_InsertItem(m_hTreeView, &tvs);

    for( int i = 0; i < rStream.GetObjectCount(); i++ )
    {
        SpatialPtr spObject = DynamicCast<Spatial>(rStream.GetObjectAt(i));
        if( spObject )
        {
            spObject->UpdateGS();
            spObject->UpdateRS();
            StringTree* pRoot = spObject->SaveStrings();
            CreateTreeRecursive(m_hTreeRoot, pRoot, NT_CLASS);
            SE_DELETE pRoot;
        }
    }
}
//----------------------------------------------------------------------------
void TreeControl::CreateTree(Spatial* pScene)
{
    TreeView_SetImageList(m_hTreeView, m_hImageList, TVSIL_NORMAL);

    // items are to be inserted in-order
    TV_INSERTSTRUCT tvs;
    tvs.hInsertAfter = TVI_LAST;
    tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    // add root item (name is the input filename)
    tvs.hParent = TVI_ROOT;
    tvs.item.pszText = m_acName;
    tvs.item.iImage = m_iClosedB;
    tvs.item.iSelectedImage = m_iClosedB;
    m_hTreeRoot = TreeView_InsertItem(m_hTreeView, &tvs);

    if( pScene )
    {
        pScene->UpdateGS();
        pScene->UpdateRS();
        StringTree* pRoot = pScene->SaveStrings();
        CreateTreeRecursive(m_hTreeRoot, pRoot, NT_CLASS);
        SE_DELETE pRoot;
    }
}
//----------------------------------------------------------------------------
void TreeControl::CreateTreeRecursive(HTREEITEM hParent,
    StringTree* pTree, NodeType eType)
{
    // ´ý¼ì²é
    // items are to be inserted in-order
    TV_INSERTSTRUCT tvs;
    tvs.hInsertAfter = TVI_LAST;
    tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    SE_ASSERT( pTree->GetStringCount() > 0 );
    if( strncmp(pTree->GetString(0), "Swing", 5) == 0 )
    {
        // string tree rooted at an Object-derived object

        // Add object.  Strip off the "Swing." prefix (the "+ 6" term).
        tvs.hParent = hParent;
        tvs.item.pszText = pTree->GetString(0) + 6;
        if( eType == NT_CLASS )
        {
            tvs.item.iImage = m_iClosedB;
            tvs.item.iSelectedImage = m_iClosedB;
        }
        else if( eType == NT_SUBCLASS )
        {
            tvs.item.iImage = m_iClosedY;
            tvs.item.iSelectedImage = m_iClosedY;
        }
        else
        {
            SE_ASSERT( false );
        }

        tvs.hParent = TreeView_InsertItem(m_hTreeView, &tvs);

        // add subclass of object
        int iStart;
        if( strncmp(pTree->GetString(0), "Swing.Object", 12) != 0)
        {
            CreateTreeRecursive(tvs.hParent, pTree->GetChild(0), NT_SUBCLASS);
            iStart = 1;
        }
        else
        {
            iStart = 0;
        }

        // add strings
        int i;
        for( i = 1; i < pTree->GetStringCount(); i++ )
        {
            tvs.item.pszText = pTree->GetString(i);
            tvs.item.iImage = m_iAttribute;
            tvs.item.iSelectedImage = m_iAttribute;
            TreeView_InsertItem(m_hTreeView, &tvs);
        }

        // add children
        for( i = iStart; i < pTree->GetChildCount(); i++ )
        {
            StringTree* pCTree = pTree->GetChild(i);
            SE_ASSERT( pCTree->GetStringCount() > 0 );

            if( strncmp(pCTree->GetString(0), "Swing", 5) == 0 )
            {
                eType = NT_CLASS;
            }
            else
            {
                eType = NT_DATA;
            }

            CreateTreeRecursive(tvs.hParent, pCTree, eType);
        }
    }
    else
    {
        // string tree represents a native type (for example, an array)

        // add object
        tvs.hParent = hParent;
        tvs.item.pszText = pTree->GetString(0);
        tvs.item.iImage = m_iClosedP;
        tvs.item.iSelectedImage = m_iClosedP;
        tvs.hParent = TreeView_InsertItem(m_hTreeView, &tvs);

        // add strings
        int i;
        for( i = 1; i < pTree->GetStringCount(); i++ )
        {
            tvs.item.pszText = pTree->GetString(i);
            tvs.item.iImage = m_iAttribute;
            tvs.item.iSelectedImage = m_iAttribute;
            TreeView_InsertItem(m_hTreeView, &tvs);
        }

        // add children
        for( i = 0; i < pTree->GetChildCount(); i++ )
        {
            StringTree* pCTree = pTree->GetChild(i);
            SE_ASSERT( pCTree->GetStringCount() > 0 );

            if( strncmp(pCTree->GetString(0), "Swing", 5) == 0 )
            {
                eType = NT_CLASS;
            }
            else
            {
                eType = NT_DATA;
            }

            CreateTreeRecursive(tvs.hParent, pCTree, eType);
        }
    }
}
//----------------------------------------------------------------------------
void TreeControl::DestroyWindows()
{
    DestroyWindow(m_hTreeView);
    DestroyWindow(m_hTreeWnd);
}
//----------------------------------------------------------------------------
void TreeControl::DestroyImageList()
{
    ImageList_Destroy(m_hImageList);
}
//----------------------------------------------------------------------------
void TreeControl::DestroyTree()
{
    TreeView_DeleteAllItems(m_hTreeView);
}
//----------------------------------------------------------------------------
LRESULT CALLBACK TreeControl::HandleMessage(HWND hWnd, UINT uiMsg,
    WPARAM wParam, LPARAM lParam)
{
    if( uiMsg == WM_DESTROY )
    {
        std::pair<Application*, int> tempPair = ms_WndAppMap[hWnd];
        Application* pTheApp = tempPair.first;
        if( pTheApp )
        {
            int iExtraData = tempPair.second;
            TreeControl* pControl = 0;
            pTheApp->SetExtraData(iExtraData, sizeof(TreeControl*),
                &pControl);
        }

        return 0;
    }

    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}
//----------------------------------------------------------------------------
