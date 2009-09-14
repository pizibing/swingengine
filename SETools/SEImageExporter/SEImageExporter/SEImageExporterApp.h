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

#ifndef Swing_ImageExporterApp_H
#define Swing_ImageExporterApp_H

//----------------------------------------------------------------------------
// 名称:ImageExporterApp类
// 说明:
// 作者:Sun Che
// 时间:20090211
//----------------------------------------------------------------------------
class ImageExporterApp
{
public:
    ImageExporterApp(void);
    ~ImageExporterApp(void);

    void OnIdle(void);
    void CreateScene(void);
    void DestroyScene(void);
    void OnOpenFile(const char* acFilename);
    void OnSave(const char* acFilename);

    Swing::FrameBuffer::FormatType m_eFormat;
    Swing::FrameBuffer::DepthType m_eDepth;
    Swing::FrameBuffer::StencilType m_eStencil;
    Swing::FrameBuffer::BufferingType m_eBuffering;
    Swing::FrameBuffer::MultisamplingType m_eMultisampling;

    int Handle;

    Swing::Renderer* AppRenderer;
    Swing::CameraPtr m_spCamera;
    Swing::Culler m_Culler;

    Swing::NodePtr m_spScene;
    Swing::TriMeshPtr m_spMesh;
    Swing::WireframeStatePtr m_spWireframe;

    Swing::ImagePtr m_spImage;

    bool m_bOpenFile;
    char m_acFilename[256];
    void OpenFile(const char* acFilename);
};

#endif