#ifndef Swing_EAGLView_H
#define Swing_EAGLView_H

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@class EAGLView;
@protocol EAGLViewDelegate <NSObject>
// called whenever the EAGL surface has been resized.
- (void) didResizeEAGLSurfaceForView:(EAGLView*)view;
@end

//----------------------------------------------------------------------------
// 名称:EAGLView类
// 说明:this class wraps the CAEAGLLayer from CoreAnimation into a convenient 
//     UIView subclass.the view content is basically an EAGL surface you 
//     render your OpenGL scene into.note that setting the view non-opaque 
//     will only work if the EAGL surface has an alpha channel.
// 作者:Sun Che
// 时间:20090607
//----------------------------------------------------------------------------
@interface EAGLView : UIView
{
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
