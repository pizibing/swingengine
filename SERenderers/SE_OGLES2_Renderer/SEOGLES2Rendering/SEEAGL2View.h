#ifndef Swing_EAGL2View_H
#define Swing_EAGL2View_H

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@class EAGL2View;
@protocol EAGL2ViewDelegate <NSObject>
// Called whenever the EAGL surface has been resized.
- (void) didResizeEAGLSurfaceForView:(EAGL2View*)view;
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
// 名称:EAGL2View类
// 说明:This class wraps the CAEAGLLayer from CoreAnimation into a convenient 
//     UIView subclass.the view content is basically an EAGL surface you 
//     render your OpenGL scene into. Note that setting the view non-opaque 
//     will only work if the EAGL surface has an alpha channel.
// 作者:Sun Che
// 时间:20091104
//----------------------------------------------------------------------------
@interface EAGL2View : UIView
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

    id<EAGL2ViewDelegate> _delegate;
}
// These also set the current context.
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
// Set to YES to have the EAGL surface automatically resized when the view
// bounds change, otherwise the EAGL surface contents is rendered scaled.
@property BOOL autoresizesSurface;
@property(readonly, nonatomic) CGSize surfaceSize;

@property(assign) id<EAGL2ViewDelegate> delegate;

- (void) setCurrentContext;
- (BOOL) isCurrentContext;
- (void) clearCurrentContext;

// This also checks the current OpenGL error and logs an error if needed.
- (void) swapBuffers;

- (CGPoint) convertPointFromViewToSurface:(CGPoint)point;
- (CGRect) convertRectFromViewToSurface:(CGRect)rect;
@end

#endif
