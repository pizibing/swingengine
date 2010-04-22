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

#ifndef Swing_TreeControl_H
#define Swing_TreeControl_H

#include <windows.h>
#include <commctrl.h>
#include "SEApplication.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20080809
//----------------------------------------------------------------------------
class SETreeControl
{
public:
    SETreeControl(SEApplication* pTheApp, int iExtraData, HINSTANCE hInstance,
        HWND hParentWnd, SEStream& rStream, const char* acName, int iX,
        int iY, int iW, int iH);

    SETreeControl(SEApplication* pTheApp, int iExtraData, HINSTANCE hInstance,
        HWND hParentWnd, SESpatial* pScene, int iX, int iY, int iW, int iH);

    ~SETreeControl(void);

protected:
    void CreateWindows(int iX, int iY, int iW, int iH);
    void CreateImageList(void);
    void CreateTree(SEStream& rStream);
    void CreateTree(SESpatial* pScene);

    enum NodeType
    {
        NT_CLASS,
        NT_SUBCLASS,
        NT_DATA
    };

    void CreateTreeRecursive(HTREEITEM hParent, SEStringTree* pTree,
        NodeType eType);

    void DestroyWindows(void);
    void DestroyImageList(void);
    void DestroyTree(void);

    static LRESULT CALLBACK HandleMessage(HWND hWnd, UINT uiMsg,
        WPARAM wParam, LPARAM lParam);

    SEApplication* m_pTheApp;
    int m_iExtraData;
    HINSTANCE m_hInstance;
    HWND m_hParentWnd;
    HWND m_hTreeWnd;
    HWND m_hTreeView;
    HTREEITEM m_hTreeRoot;
    HIMAGELIST m_hImageList;
    char* m_acName;
    int m_iClosedB, m_iClosedY, m_iClosedP, m_iAttribute;

    static unsigned int ms_auiBmpClosedB[240];
    static unsigned int ms_auiBmpClosedP[240];
    static unsigned int ms_auiBmpClosedY[240];
    static unsigned int ms_auiBmpAttribute[240];

    static std::map<HWND, std::pair<SEApplication*, int> > ms_WndAppMap;
};

}

#endif
