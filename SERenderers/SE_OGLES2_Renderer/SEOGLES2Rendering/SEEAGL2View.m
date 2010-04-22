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

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import "SEEAGL2View.h"

@implementation SEEAGL2View
//----------------------------------------------------------------------------
@synthesize onTouchesBegan;
@synthesize onTouchesMoved;
@synthesize onTouchesEnded;
@synthesize onTouchesCancelled;
@synthesize userData;
//----------------------------------------------------------------------------
@synthesize delegate = _delegate;
@synthesize autoresizesSurface = _autoresize;
@synthesize surfaceSize = _size;
@synthesize framebuffer = _framebuffer;
@synthesize pixelFormat = _format;
@synthesize depthFormat = _depthFormat;
@synthesize context = _context;
//----------------------------------------------------------------------------
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}
//----------------------------------------------------------------------------
- (BOOL) _createSurface
{
    CAEAGLLayer* eaglLayer = (CAEAGLLayer*)[self layer];
    CGSize newSize;
    GLuint oldRenderbuffer;
    GLuint oldFramebuffer;

    if( ![EAGLContext setCurrentContext:_context] )
    {
        return NO;
    }

    newSize = [eaglLayer bounds].size;
    newSize.width = roundf(newSize.width);
    newSize.height = roundf(newSize.height);

    glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint *)&oldRenderbuffer);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&oldFramebuffer);

    glGenRenderbuffers(1, &_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);

    if( ![_context renderbufferStorage:GL_RENDERBUFFER 
        fromDrawable:(id<EAGLDrawable>)eaglLayer] )
    {
        glDeleteRenderbuffers(1, &_renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER_BINDING, oldRenderbuffer);
        return NO;
    }

    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
        GL_RENDERBUFFER, _renderbuffer);
    if( _depthFormat )
    {
        glGenRenderbuffers(1, &_depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, _depthFormat, 
            newSize.width, newSize.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
            GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    }

    _size = newSize;
    if( !_hasBeenCurrent )
    {
        glViewport(0, 0, newSize.width, newSize.height);
        glScissor(0, 0, newSize.width, newSize.height);
        _hasBeenCurrent = YES;
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, oldFramebuffer);
    }
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderbuffer);
    
    // Error handling here.

    [_delegate didResizeEAGLSurfaceForView:self];

    return YES;
}
//----------------------------------------------------------------------------
- (void) _destroySurface
{
    EAGLContext *oldContext = [EAGLContext currentContext];

    if( oldContext != _context )
    {
        [EAGLContext setCurrentContext:_context];
    }

    if(_depthFormat)
    {
        glDeleteRenderbuffers(1, &_depthBuffer);
        _depthBuffer = 0;
    }

    glDeleteRenderbuffers(1, &_renderbuffer);
    _renderbuffer = 0;

    glDeleteFramebuffers(1, &_framebuffer);
    _framebuffer = 0;

    if( oldContext != _context )
    {
        [EAGLContext setCurrentContext:oldContext];
    }
}
//----------------------------------------------------------------------------
- (id) initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame pixelFormat:GL_RGB565 depthFormat:0 
        preserveBackbuffer:NO];
}
//----------------------------------------------------------------------------
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format 
{
    return [self initWithFrame:frame pixelFormat:format depthFormat:0 
        preserveBackbuffer:NO];
}
//----------------------------------------------------------------------------
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format depthFormat:
    (GLuint)depth preserveBackbuffer:(BOOL)retained
{
    if( (self = [super initWithFrame:frame]) )
    {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)[self layer];

        eaglLayer.drawableProperties = 
            [NSDictionary dictionaryWithObjectsAndKeys:
            [NSNumber numberWithBool:YES], 
            kEAGLDrawablePropertyRetainedBacking,
            kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

        _format = format;
        _depthFormat = depth;

        // Create an ES2 context.
        _context = [[EAGLContext alloc] initWithAPI:
            kEAGLRenderingAPIOpenGLES2];
        if( _context == nil )
        {
            [self release];
            return nil;
        }

        if( ![self _createSurface] )
        {
            [self release];
            return nil;
        }
    }

    return self;
}
//----------------------------------------------------------------------------
- (void) dealloc
{
    [self _destroySurface];

    [_context release];
    _context = nil;

    [super dealloc];
}
//----------------------------------------------------------------------------
- (void) layoutSubviews
{
    CGRect bounds = [self bounds];

    if( _autoresize && ((roundf(bounds.size.width) != _size.width) || 
        (roundf(bounds.size.height) != _size.height)) )
    {
        [self _destroySurface];
        [self _createSurface];
    }
}
//----------------------------------------------------------------------------
- (void) setAutoresizesEAGLSurface:(BOOL)autoresizesEAGLSurface;
{
    _autoresize = autoresizesEAGLSurface;
    if(_autoresize)
    [self layoutSubviews];
}
//----------------------------------------------------------------------------
- (void) setCurrentContext
{
    if( ![EAGLContext setCurrentContext:_context] )
    {
        printf("failed to set current context %p in %s\n", _context, 
            __FUNCTION__);
    }
}
//----------------------------------------------------------------------------
- (BOOL) isCurrentContext
{
    return ([EAGLContext currentContext] == _context ? YES : NO);
}
//----------------------------------------------------------------------------
- (void) clearCurrentContext
{
    if( ![EAGLContext setCurrentContext:nil] )
    {
        printf("failed to clear current context in %s\n", __FUNCTION__);
    }
}
//----------------------------------------------------------------------------
- (void) swapBuffers
{
    EAGLContext *oldContext = [EAGLContext currentContext];
    GLuint oldRenderbuffer;

    if( oldContext != _context )
    {
        [EAGLContext setCurrentContext:_context];
    }

    glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint *) &oldRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);

    if( ![_context presentRenderbuffer:GL_RENDERBUFFER] )
    {
        printf("failed to swap renderbuffer in %s\n", __FUNCTION__);
    }

    if( oldContext != _context )
    {
        [EAGLContext setCurrentContext:oldContext];
    }
}
//----------------------------------------------------------------------------
- (CGPoint) convertPointFromViewToSurface:(CGPoint)point
{
    CGRect bounds = [self bounds];

    return CGPointMake((point.x - bounds.origin.x) / bounds.size.width * 
        _size.width, (point.y - bounds.origin.y) / bounds.size.height * 
        _size.height);
}
//----------------------------------------------------------------------------
- (CGRect) convertRectFromViewToSurface:(CGRect)rect
{
    CGRect bounds = [self bounds];

    return CGRectMake((rect.origin.x - bounds.origin.x) / bounds.size.width * 
        _size.width, (rect.origin.y - bounds.origin.y) / bounds.size.height * 
        _size.height, rect.size.width / bounds.size.width * _size.width, 
        rect.size.height / bounds.size.height * _size.height);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Touches event handlers.
//----------------------------------------------------------------------------
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if( onTouchesBegan )
    {
        onTouchesBegan(self, touches, event, userData);
    }
}
//----------------------------------------------------------------------------
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if( onTouchesMoved )
    {
        onTouchesMoved(self, touches, event, userData);
    }
}
//----------------------------------------------------------------------------
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if( onTouchesEnded )
    {
        onTouchesEnded(self, touches, event, userData);
    }
}
//----------------------------------------------------------------------------
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    if( onTouchesCancelled )
    {
        onTouchesCancelled(self, touches, event, userData);
    }
}
//----------------------------------------------------------------------------
@end
