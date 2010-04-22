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

#ifndef Swing_EAGLView_H
#define Swing_EAGLView_H

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@class SEEAGLView;
@protocol EAGLViewDelegate <NSObject>
// called whenever the EAGL surface has been resized.
- (void) didResizeEAGLSurfaceForView:(SEEAGLView*)view;
@end

// Prototypes of touches event handlers's callback functions.
typedef void (*TouchesBegan)(UIView* owner, NSSet* touches, UIEvent* event, 
							 void* userData);
typedef void (*TouchesMoved)(UIView* owner, NSSet* touches, UIEvent* event, 
							 void* userData);
typedef void (*TouchesEnded)(UIView* owner, NSSet* touches, UIEvent* event, 
							 void* userData);
typedef void (*TouchesCancelled)(UIView* owner, NSSet* touches, 
								 UIEvent* event, void* userData);

//----------------------------------------------------------------------------
// 说明:this class wraps the CAEAGLLayer from CoreAnimation into a convenient 
//     UIView subclass.the view content is basically an EAGL surface you 
//     render your OpenGL scene into.note that setting the view non-opaque 
//     will only work if the EAGL surface has an alpha channel.
// 作者:Sun Che
// 时间:20090607
//----------------------------------------------------------------------------
@interface SEEAGLView : UIView
{
@public
    TouchesBegan onTouchesBegan;
    TouchesMoved onTouchesMoved;
    TouchesEnded onTouchesEnded;
    TouchesCancelled onTouchesCancelled;
    void* userData;

@private
    EAGLContext* _context;

    GLuint _format;
    GLuint _depthFormat;

    BOOL _autoresize;

    GLuint _framebuffer;
    GLuint _renderbuffer;
    GLuint _depthBuffer;

    CGSize _size;
    BOOL _hasBeenCurrent;

    id<EAGLViewDelegate> _delegate;
}
// these also set the current context.
- (id) initWithFrame:(CGRect)frame;
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format;
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format 
    depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained;

@property(readwrite, assign) TouchesBegan onTouchesBegan;
@property(readwrite, assign) TouchesMoved onTouchesMoved;
@property(readwrite, assign) TouchesEnded onTouchesEnded;
@property(readwrite, assign) TouchesCancelled onTouchesCancelled;
@property(readwrite, assign) void* userData;

@property(readonly) GLuint framebuffer;
@property(readonly) GLuint pixelFormat;
@property(readonly) GLuint depthFormat;
@property(readonly) EAGLContext* context;

// NO by default.
// set to YES to have the EAGL surface automatically resized when the view
// bounds change, otherwise the EAGL surface contents is rendered scaled.
@property BOOL autoresizesSurface;
@property(readonly, nonatomic) CGSize surfaceSize;

@property(assign) id<EAGLViewDelegate> delegate;

- (void) setCurrentContext;
- (BOOL) isCurrentContext;
- (void) clearCurrentContext;

// this also checks the current OpenGL error and logs an error if needed.
- (void) swapBuffers;

- (CGPoint) convertPointFromViewToSurface:(CGPoint)point;
- (CGRect) convertRectFromViewToSurface:(CGRect)rect;
@end

#endif
