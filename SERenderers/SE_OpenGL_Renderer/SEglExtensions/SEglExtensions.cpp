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

/*--------------------------------------------------------------------------*/
/* Swing Engine OpenGL Encapsulator, Version 1 */
/*--------------------------------------------------------------------------*/

#include "SEglExtensions.h"
#include "SEglUtility.h"

#if defined(_MSC_VER)
#pragma warning(disable:4127)
#endif

/*--------------------------------------------------------------------------*/
/* OpenGL 1.1 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL11 = 1;

#undef glAccum
#undef glAlphaFunc
#undef glAreTexturesResident
#undef glArrayElement
#undef glBegin
#undef glBindTexture
#undef glBitmap
#undef glBlendFunc
#undef glCallList
#undef glCallLists
#undef glClear
#undef glClearAccum
#undef glClearColor
#undef glClearDepth
#undef glClearIndex
#undef glClearStencil
#undef glClipPlane
#undef glColor3b
#undef glColor3bv
#undef glColor3d
#undef glColor3dv
#undef glColor3f
#undef glColor3fv
#undef glColor3i
#undef glColor3iv
#undef glColor3s
#undef glColor3sv
#undef glColor3ub
#undef glColor3ubv
#undef glColor3ui
#undef glColor3uiv
#undef glColor3us
#undef glColor3usv
#undef glColor4b
#undef glColor4bv
#undef glColor4d
#undef glColor4dv
#undef glColor4f
#undef glColor4fv
#undef glColor4i
#undef glColor4iv
#undef glColor4s
#undef glColor4sv
#undef glColor4ub
#undef glColor4ubv
#undef glColor4ui
#undef glColor4uiv
#undef glColor4us
#undef glColor4usv
#undef glColorMask
#undef glColorMaterial
#undef glColorPointer
#undef glCopyPixels
#undef glCopyTexImage1D
#undef glCopyTexImage2D
#undef glCopyTexSubImage1D
#undef glCopyTexSubImage2D
#undef glCullFace
#undef glDeleteLists
#undef glDeleteTextures
#undef glDepthFunc
#undef glDepthMask
#undef glDepthRange
#undef glDisable
#undef glDisableClientState
#undef glDrawArrays
#undef glDrawBuffer
#undef glDrawElements
#undef glDrawPixels
#undef glEdgeFlag
#undef glEdgeFlagPointer
#undef glEdgeFlagv
#undef glEnable
#undef glEnableClientState
#undef glEnd
#undef glEndList
#undef glEvalCoord1d
#undef glEvalCoord1dv
#undef glEvalCoord1f
#undef glEvalCoord1fv
#undef glEvalCoord2d
#undef glEvalCoord2dv
#undef glEvalCoord2f
#undef glEvalCoord2fv
#undef glEvalMesh1
#undef glEvalMesh2
#undef glEvalPoint1
#undef glEvalPoint2
#undef glFeedbackBuffer
#undef glFinish
#undef glFlush
#undef glFogf
#undef glFogfv
#undef glFogi
#undef glFogiv
#undef glFrontFace
#undef glFrustum
#undef glGenLists
#undef glGenTextures
#undef glGetBooleanv
#undef glGetClipPlane
#undef glGetDoublev
#undef glGetError
#undef glGetFloatv
#undef glGetIntegerv
#undef glGetLightfv
#undef glGetLightiv
#undef glGetMapdv
#undef glGetMapfv
#undef glGetMapiv
#undef glGetMaterialfv
#undef glGetMaterialiv
#undef glGetPixelMapfv
#undef glGetPixelMapuiv
#undef glGetPixelMapusv
#undef glGetPointerv
#undef glGetPolygonStipple
#undef glGetString
#undef glGetTexEnvfv
#undef glGetTexEnviv
#undef glGetTexGendv
#undef glGetTexGenfv
#undef glGetTexGeniv
#undef glGetTexImage
#undef glGetTexLevelParameterfv
#undef glGetTexLevelParameteriv
#undef glGetTexParameterfv
#undef glGetTexParameteriv
#undef glHint
#undef glIndexMask
#undef glIndexPointer
#undef glIndexd
#undef glIndexdv
#undef glIndexf
#undef glIndexfv
#undef glIndexi
#undef glIndexiv
#undef glIndexs
#undef glIndexsv
#undef glIndexub
#undef glIndexubv
#undef glInitNames
#undef glInterleavedArrays
#undef glIsEnabled
#undef glIsList
#undef glIsTexture
#undef glLightModelf
#undef glLightModelfv
#undef glLightModeli
#undef glLightModeliv
#undef glLightf
#undef glLightfv
#undef glLighti
#undef glLightiv
#undef glLineStipple
#undef glLineWidth
#undef glListBase
#undef glLoadIdentity
#undef glLoadMatrixd
#undef glLoadMatrixf
#undef glLoadName
#undef glLogicOp
#undef glMap1d
#undef glMap1f
#undef glMap2d
#undef glMap2f
#undef glMapGrid1d
#undef glMapGrid1f
#undef glMapGrid2d
#undef glMapGrid2f
#undef glMaterialf
#undef glMaterialfv
#undef glMateriali
#undef glMaterialiv
#undef glMatrixMode
#undef glMultMatrixd
#undef glMultMatrixf
#undef glNewList
#undef glNormal3b
#undef glNormal3bv
#undef glNormal3d
#undef glNormal3dv
#undef glNormal3f
#undef glNormal3fv
#undef glNormal3i
#undef glNormal3iv
#undef glNormal3s
#undef glNormal3sv
#undef glNormalPointer
#undef glOrtho
#undef glPassThrough
#undef glPixelMapfv
#undef glPixelMapuiv
#undef glPixelMapusv
#undef glPixelStoref
#undef glPixelStorei
#undef glPixelTransferf
#undef glPixelTransferi
#undef glPixelZoom
#undef glPointSize
#undef glPolygonMode
#undef glPolygonOffset
#undef glPolygonStipple
#undef glPopAttrib
#undef glPopClientAttrib
#undef glPopMatrix
#undef glPopName
#undef glPrioritizeTextures
#undef glPushAttrib
#undef glPushClientAttrib
#undef glPushMatrix
#undef glPushName
#undef glRasterPos2d
#undef glRasterPos2dv
#undef glRasterPos2f
#undef glRasterPos2fv
#undef glRasterPos2i
#undef glRasterPos2iv
#undef glRasterPos2s
#undef glRasterPos2sv
#undef glRasterPos3d
#undef glRasterPos3dv
#undef glRasterPos3f
#undef glRasterPos3fv
#undef glRasterPos3i
#undef glRasterPos3iv
#undef glRasterPos3s
#undef glRasterPos3sv
#undef glRasterPos4d
#undef glRasterPos4dv
#undef glRasterPos4f
#undef glRasterPos4fv
#undef glRasterPos4i
#undef glRasterPos4iv
#undef glRasterPos4s
#undef glRasterPos4sv
#undef glReadBuffer
#undef glReadPixels
#undef glRectd
#undef glRectdv
#undef glRectf
#undef glRectfv
#undef glRecti
#undef glRectiv
#undef glRects
#undef glRectsv
#undef glRenderMode
#undef glRotated
#undef glRotatef
#undef glScaled
#undef glScalef
#undef glScissor
#undef glSelectBuffer
#undef glShadeModel
#undef glStencilFunc
#undef glStencilMask
#undef glStencilOp
#undef glTexCoord1d
#undef glTexCoord1dv
#undef glTexCoord1f
#undef glTexCoord1fv
#undef glTexCoord1i
#undef glTexCoord1iv
#undef glTexCoord1s
#undef glTexCoord1sv
#undef glTexCoord2d
#undef glTexCoord2dv
#undef glTexCoord2f
#undef glTexCoord2fv
#undef glTexCoord2i
#undef glTexCoord2iv
#undef glTexCoord2s
#undef glTexCoord2sv
#undef glTexCoord3d
#undef glTexCoord3dv
#undef glTexCoord3f
#undef glTexCoord3fv
#undef glTexCoord3i
#undef glTexCoord3iv
#undef glTexCoord3s
#undef glTexCoord3sv
#undef glTexCoord4d
#undef glTexCoord4dv
#undef glTexCoord4f
#undef glTexCoord4fv
#undef glTexCoord4i
#undef glTexCoord4iv
#undef glTexCoord4s
#undef glTexCoord4sv
#undef glTexCoordPointer
#undef glTexEnvf
#undef glTexEnvfv
#undef glTexEnvi
#undef glTexEnviv
#undef glTexGend
#undef glTexGendv
#undef glTexGenf
#undef glTexGenfv
#undef glTexGeni
#undef glTexGeniv
#undef glTexImage1D
#undef glTexImage2D
#undef glTexParameterf
#undef glTexParameterfv
#undef glTexParameteri
#undef glTexParameteriv
#undef glTexSubImage1D
#undef glTexSubImage2D
#undef glTranslated
#undef glTranslatef
#undef glVertex2d
#undef glVertex2dv
#undef glVertex2f
#undef glVertex2fv
#undef glVertex2i
#undef glVertex2iv
#undef glVertex2s
#undef glVertex2sv
#undef glVertex3d
#undef glVertex3dv
#undef glVertex3f
#undef glVertex3fv
#undef glVertex3i
#undef glVertex3iv
#undef glVertex3s
#undef glVertex3sv
#undef glVertex4d
#undef glVertex4dv
#undef glVertex4f
#undef glVertex4fv
#undef glVertex4i
#undef glVertex4iv
#undef glVertex4s
#undef glVertex4sv
#undef glVertexPointer
#undef glViewport

extern "C" {

EXTERN void STDCALL glAccum(GLenum, GLfloat);
EXTERN void STDCALL glAlphaFunc(GLenum, GLclampf);
EXTERN GLboolean STDCALL glAreTexturesResident(GLsizei, const GLuint*,
    GLboolean*);
EXTERN void STDCALL glArrayElement(GLint);
EXTERN void STDCALL glBegin(GLenum);
EXTERN void STDCALL glBindTexture(GLenum, GLuint);
EXTERN void STDCALL glBitmap(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat,
    GLfloat, const GLubyte*);
EXTERN void STDCALL glBlendFunc(GLenum, GLenum);
EXTERN void STDCALL glCallList(GLuint);
EXTERN void STDCALL glCallLists(GLsizei, GLenum, const GLvoid*);
EXTERN void STDCALL glClear(GLbitfield);
EXTERN void STDCALL glClearAccum(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glClearColor(GLclampf, GLclampf, GLclampf, GLclampf);
EXTERN void STDCALL glClearDepth(GLclampd);
EXTERN void STDCALL glClearIndex(GLfloat);
EXTERN void STDCALL glClearStencil(GLint);
EXTERN void STDCALL glClipPlane(GLenum, const GLdouble*);
EXTERN void STDCALL glColor3b(GLbyte, GLbyte, GLbyte);
EXTERN void STDCALL glColor3bv(const GLbyte*);
EXTERN void STDCALL glColor3d(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glColor3dv(const GLdouble*);
EXTERN void STDCALL glColor3f(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glColor3fv(const GLfloat*);
EXTERN void STDCALL glColor3i(GLint, GLint, GLint);
EXTERN void STDCALL glColor3iv(const GLint*);
EXTERN void STDCALL glColor3s(GLshort, GLshort, GLshort);
EXTERN void STDCALL glColor3sv(const GLshort*);
EXTERN void STDCALL glColor3ub(GLubyte, GLubyte, GLubyte);
EXTERN void STDCALL glColor3ubv(const GLubyte*);
EXTERN void STDCALL glColor3ui(GLuint, GLuint, GLuint);
EXTERN void STDCALL glColor3uiv(const GLuint*);
EXTERN void STDCALL glColor3us(GLushort, GLushort, GLushort);
EXTERN void STDCALL glColor3usv(const GLushort*);
EXTERN void STDCALL glColor4b(GLbyte, GLbyte, GLbyte, GLbyte);
EXTERN void STDCALL glColor4bv(const GLbyte*);
EXTERN void STDCALL glColor4d(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glColor4dv(const GLdouble*);
EXTERN void STDCALL glColor4f(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glColor4fv(const GLfloat*);
EXTERN void STDCALL glColor4i(GLint, GLint, GLint, GLint);
EXTERN void STDCALL glColor4iv(const GLint*);
EXTERN void STDCALL glColor4s(GLshort, GLshort, GLshort, GLshort);
EXTERN void STDCALL glColor4sv(const GLshort*);
EXTERN void STDCALL glColor4ub(GLubyte, GLubyte, GLubyte, GLubyte);
EXTERN void STDCALL glColor4ubv(const GLubyte*);
EXTERN void STDCALL glColor4ui(GLuint, GLuint, GLuint, GLuint);
EXTERN void STDCALL glColor4uiv(const GLuint*);
EXTERN void STDCALL glColor4us(GLushort, GLushort, GLushort, GLushort);
EXTERN void STDCALL glColor4usv(const GLushort*);
EXTERN void STDCALL glColorMask(GLboolean, GLboolean, GLboolean, GLboolean);
EXTERN void STDCALL glColorMaterial(GLenum, GLenum);
EXTERN void STDCALL glColorPointer(GLint, GLenum, GLsizei, const GLvoid*);
EXTERN void STDCALL glCopyPixels(GLint, GLint, GLsizei, GLsizei, GLenum);
EXTERN void STDCALL glCopyTexImage1D(GLenum, GLint, GLenum, GLint, GLint,
    GLsizei, GLint);
EXTERN void STDCALL glCopyTexImage2D(GLenum, GLint, GLenum, GLint, GLint,
    GLsizei, GLsizei, GLint);
EXTERN void STDCALL glCopyTexSubImage1D(GLenum, GLint, GLint, GLint, GLint,
    GLsizei);
EXTERN void STDCALL glCopyTexSubImage2D(GLenum, GLint, GLint, GLint, GLint,
    GLint, GLsizei, GLsizei);
EXTERN void STDCALL glCullFace(GLenum);
EXTERN void STDCALL glDeleteLists(GLuint, GLsizei);
EXTERN void STDCALL glDeleteTextures(GLsizei, const GLuint*);
EXTERN void STDCALL glDepthFunc(GLenum);
EXTERN void STDCALL glDepthMask(GLboolean);
EXTERN void STDCALL glDepthRange(GLclampd, GLclampd);
EXTERN void STDCALL glDisable(GLenum);
EXTERN void STDCALL glDisableClientState(GLenum);
EXTERN void STDCALL glDrawArrays(GLenum, GLint, GLsizei);
EXTERN void STDCALL glDrawBuffer(GLenum);
EXTERN void STDCALL glDrawElements(GLenum, GLsizei, GLenum, const GLvoid*);
EXTERN void STDCALL glDrawPixels(GLsizei, GLsizei, GLenum, GLenum,
    const GLvoid*);
EXTERN void STDCALL glEdgeFlag(GLboolean);
EXTERN void STDCALL glEdgeFlagPointer(GLsizei, const GLvoid*);
EXTERN void STDCALL glEdgeFlagv(const GLboolean*);
EXTERN void STDCALL glEnable(GLenum);
EXTERN void STDCALL glEnableClientState(GLenum);
EXTERN void STDCALL glEnd(void);
EXTERN void STDCALL glEndList(void);
EXTERN void STDCALL glEvalCoord1d(GLdouble);
EXTERN void STDCALL glEvalCoord1dv(const GLdouble*);
EXTERN void STDCALL glEvalCoord1f(GLfloat);
EXTERN void STDCALL glEvalCoord1fv(const GLfloat*);
EXTERN void STDCALL glEvalCoord2d(GLdouble, GLdouble);
EXTERN void STDCALL glEvalCoord2dv(const GLdouble*);
EXTERN void STDCALL glEvalCoord2f(GLfloat, GLfloat);
EXTERN void STDCALL glEvalCoord2fv(const GLfloat*);
EXTERN void STDCALL glEvalMesh1(GLenum, GLint, GLint);
EXTERN void STDCALL glEvalMesh2(GLenum, GLint, GLint, GLint, GLint);
EXTERN void STDCALL glEvalPoint1(GLint);
EXTERN void STDCALL glEvalPoint2(GLint, GLint);
EXTERN void STDCALL glFeedbackBuffer(GLsizei, GLenum, GLfloat*);
EXTERN void STDCALL glFinish(void);
EXTERN void STDCALL glFlush(void);
EXTERN void STDCALL glFogf(GLenum, GLfloat);
EXTERN void STDCALL glFogfv(GLenum, const GLfloat*);
EXTERN void STDCALL glFogi(GLenum, GLint);
EXTERN void STDCALL glFogiv(GLenum, const GLint*);
EXTERN void STDCALL glFrontFace(GLenum);
EXTERN void STDCALL glFrustum(GLdouble, GLdouble, GLdouble, GLdouble,
    GLdouble, GLdouble);
EXTERN GLuint STDCALL glGenLists(GLsizei);
EXTERN void STDCALL glGenTextures(GLsizei, GLuint*);
EXTERN void STDCALL glGetBooleanv(GLenum, GLboolean*);
EXTERN void STDCALL glGetClipPlane(GLenum, GLdouble*);
EXTERN void STDCALL glGetDoublev(GLenum, GLdouble*);
EXTERN GLenum STDCALL glGetError(void);
EXTERN void STDCALL glGetFloatv(GLenum, GLfloat*);
EXTERN void STDCALL glGetIntegerv(GLenum, GLint*);
EXTERN void STDCALL glGetLightfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetLightiv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glGetMapdv(GLenum, GLenum, GLdouble*);
EXTERN void STDCALL glGetMapfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetMapiv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glGetMaterialfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetMaterialiv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glGetPixelMapfv(GLenum, GLfloat*);
EXTERN void STDCALL glGetPixelMapuiv(GLenum, GLuint*);
EXTERN void STDCALL glGetPixelMapusv(GLenum, GLushort*);
EXTERN void STDCALL glGetPointerv(GLenum, GLvoid**);
EXTERN void STDCALL glGetPolygonStipple(GLubyte*);
EXTERN const GLubyte* STDCALL glGetString(GLenum);
EXTERN void STDCALL glGetTexEnvfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetTexEnviv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glGetTexGendv(GLenum, GLenum, GLdouble*);
EXTERN void STDCALL glGetTexGenfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetTexGeniv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glGetTexImage(GLenum, GLint, GLenum, GLenum, GLvoid*);
EXTERN void STDCALL glGetTexLevelParameterfv(GLenum, GLint, GLenum,
    GLfloat*);
EXTERN void STDCALL glGetTexLevelParameteriv(GLenum, GLint, GLenum, GLint*);
EXTERN void STDCALL glGetTexParameterfv(GLenum, GLenum, GLfloat*);
EXTERN void STDCALL glGetTexParameteriv(GLenum, GLenum, GLint*);
EXTERN void STDCALL glHint(GLenum, GLenum);
EXTERN void STDCALL glIndexMask(GLuint);
EXTERN void STDCALL glIndexPointer(GLenum, GLsizei, const GLvoid*);
EXTERN void STDCALL glIndexd(GLdouble);
EXTERN void STDCALL glIndexdv(const GLdouble*);
EXTERN void STDCALL glIndexf(GLfloat);
EXTERN void STDCALL glIndexfv(const GLfloat*);
EXTERN void STDCALL glIndexi(GLint);
EXTERN void STDCALL glIndexiv(const GLint*);
EXTERN void STDCALL glIndexs(GLshort);
EXTERN void STDCALL glIndexsv(const GLshort*);
EXTERN void STDCALL glIndexub(GLubyte);
EXTERN void STDCALL glIndexubv(const GLubyte*);
EXTERN void STDCALL glInitNames(void);
EXTERN void STDCALL glInterleavedArrays(GLenum, GLsizei, const GLvoid*);
EXTERN GLboolean STDCALL glIsEnabled(GLenum);
EXTERN GLboolean STDCALL glIsList(GLuint);
EXTERN GLboolean STDCALL glIsTexture(GLuint);
EXTERN void STDCALL glLightModelf(GLenum, GLfloat);
EXTERN void STDCALL glLightModelfv(GLenum, const GLfloat*);
EXTERN void STDCALL glLightModeli(GLenum, GLint);
EXTERN void STDCALL glLightModeliv(GLenum, const GLint*);
EXTERN void STDCALL glLightf(GLenum, GLenum, GLfloat);
EXTERN void STDCALL glLightfv(GLenum, GLenum, const GLfloat*);
EXTERN void STDCALL glLighti(GLenum, GLenum, GLint);
EXTERN void STDCALL glLightiv(GLenum, GLenum, const GLint*);
EXTERN void STDCALL glLineStipple(GLint, GLushort);
EXTERN void STDCALL glLineWidth(GLfloat);
EXTERN void STDCALL glListBase(GLuint);
EXTERN void STDCALL glLoadIdentity(void);
EXTERN void STDCALL glLoadMatrixd(const GLdouble*);
EXTERN void STDCALL glLoadMatrixf(const GLfloat*);
EXTERN void STDCALL glLoadName(GLuint);
EXTERN void STDCALL glLogicOp(GLenum);
EXTERN void STDCALL glMap1d(GLenum, GLdouble, GLdouble, GLint, GLint,
    const GLdouble*);
EXTERN void STDCALL glMap1f(GLenum, GLfloat, GLfloat, GLint, GLint,
    const GLfloat*);
EXTERN void STDCALL glMap2d(GLenum, GLdouble, GLdouble, GLint, GLint,
    GLdouble, GLdouble, GLint, GLint, const GLdouble*);
EXTERN void STDCALL glMap2f(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat,
    GLfloat, GLint, GLint, const GLfloat*);
EXTERN void STDCALL glMapGrid1d(GLint, GLdouble, GLdouble);
EXTERN void STDCALL glMapGrid1f(GLint, GLfloat, GLfloat);
EXTERN void STDCALL glMapGrid2d(GLint, GLdouble, GLdouble, GLint, GLdouble,
    GLdouble);
EXTERN void STDCALL glMapGrid2f(GLint, GLfloat, GLfloat, GLint, GLfloat,
    GLfloat);
EXTERN void STDCALL glMaterialf(GLenum, GLenum, GLfloat);
EXTERN void STDCALL glMaterialfv(GLenum, GLenum, const GLfloat*);
EXTERN void STDCALL glMateriali(GLenum, GLenum, GLint);
EXTERN void STDCALL glMaterialiv(GLenum, GLenum, const GLint*);
EXTERN void STDCALL glMatrixMode(GLenum);
EXTERN void STDCALL glMultMatrixd(const GLdouble*);
EXTERN void STDCALL glMultMatrixf(const GLfloat*);
EXTERN void STDCALL glNewList(GLuint, GLenum);
EXTERN void STDCALL glNormal3b(GLbyte, GLbyte, GLbyte);
EXTERN void STDCALL glNormal3bv(const GLbyte*);
EXTERN void STDCALL glNormal3d(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glNormal3dv(const GLdouble*);
EXTERN void STDCALL glNormal3f(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glNormal3fv(const GLfloat*);
EXTERN void STDCALL glNormal3i(GLint, GLint, GLint);
EXTERN void STDCALL glNormal3iv(const GLint*);
EXTERN void STDCALL glNormal3s(GLshort, GLshort, GLshort);
EXTERN void STDCALL glNormal3sv(const GLshort*);
EXTERN void STDCALL glNormalPointer(GLenum, GLsizei, const GLvoid*);
EXTERN void STDCALL glOrtho(GLdouble, GLdouble, GLdouble, GLdouble,
    GLdouble, GLdouble);
EXTERN void STDCALL glPassThrough(GLfloat);
EXTERN void STDCALL glPixelMapfv(GLenum, GLsizei, const GLfloat*);
EXTERN void STDCALL glPixelMapuiv(GLenum, GLsizei, const GLuint*);
EXTERN void STDCALL glPixelMapusv(GLenum, GLsizei, const GLushort*);
EXTERN void STDCALL glPixelStoref(GLenum, GLfloat);
EXTERN void STDCALL glPixelStorei(GLenum, GLint);
EXTERN void STDCALL glPixelTransferf(GLenum, GLfloat);
EXTERN void STDCALL glPixelTransferi(GLenum, GLint);
EXTERN void STDCALL glPixelZoom(GLfloat, GLfloat);
EXTERN void STDCALL glPointSize(GLfloat);
EXTERN void STDCALL glPolygonMode(GLenum, GLenum);
EXTERN void STDCALL glPolygonOffset(GLfloat, GLfloat);
EXTERN void STDCALL glPolygonStipple(const GLubyte*);
EXTERN void STDCALL glPopAttrib(void);
EXTERN void STDCALL glPopClientAttrib(void);
EXTERN void STDCALL glPopMatrix(void);
EXTERN void STDCALL glPopName(void);
EXTERN void STDCALL glPrioritizeTextures(GLsizei, const GLuint*,
    const GLclampf*);
EXTERN void STDCALL glPushAttrib(GLbitfield);
EXTERN void STDCALL glPushClientAttrib(GLbitfield);
EXTERN void STDCALL glPushMatrix(void);
EXTERN void STDCALL glPushName(GLuint);
EXTERN void STDCALL glRasterPos2d(GLdouble, GLdouble);
EXTERN void STDCALL glRasterPos2dv(const GLdouble*);
EXTERN void STDCALL glRasterPos2f(GLfloat, GLfloat);
EXTERN void STDCALL glRasterPos2fv(const GLfloat*);
EXTERN void STDCALL glRasterPos2i(GLint, GLint);
EXTERN void STDCALL glRasterPos2iv(const GLint*);
EXTERN void STDCALL glRasterPos2s(GLshort, GLshort);
EXTERN void STDCALL glRasterPos2sv(const GLshort *);
EXTERN void STDCALL glRasterPos3d(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glRasterPos3dv(const GLdouble*);
EXTERN void STDCALL glRasterPos3f(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glRasterPos3fv(const GLfloat*);
EXTERN void STDCALL glRasterPos3i(GLint, GLint, GLint);
EXTERN void STDCALL glRasterPos3iv(const GLint*);
EXTERN void STDCALL glRasterPos3s(GLshort, GLshort, GLshort);
EXTERN void STDCALL glRasterPos3sv(const GLshort*);
EXTERN void STDCALL glRasterPos4d(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glRasterPos4dv(const GLdouble*);
EXTERN void STDCALL glRasterPos4f(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glRasterPos4fv(const GLfloat*);
EXTERN void STDCALL glRasterPos4i(GLint, GLint, GLint, GLint);
EXTERN void STDCALL glRasterPos4iv(const GLint*);
EXTERN void STDCALL glRasterPos4s(GLshort, GLshort, GLshort, GLshort);
EXTERN void STDCALL glRasterPos4sv(const GLshort*);
EXTERN void STDCALL glReadBuffer(GLenum);
EXTERN void STDCALL glReadPixels(GLint, GLint, GLsizei, GLsizei, GLenum,
    GLenum, GLvoid*);
EXTERN void STDCALL glRectd(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glRectdv(const GLdouble*, const GLdouble*);
EXTERN void STDCALL glRectf(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glRectfv(const GLfloat*, const GLfloat*);
EXTERN void STDCALL glRecti(GLint, GLint, GLint, GLint);
EXTERN void STDCALL glRectiv(const GLint*, const GLint*);
EXTERN void STDCALL glRects(GLshort, GLshort, GLshort, GLshort);
EXTERN void STDCALL glRectsv(const GLshort*, const GLshort*);
EXTERN GLint STDCALL glRenderMode(GLenum);
EXTERN void STDCALL glRotated(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glRotatef(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glScaled(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glScalef(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glScissor(GLint, GLint, GLsizei, GLsizei);
EXTERN void STDCALL glSelectBuffer(GLsizei, GLuint*);
EXTERN void STDCALL glShadeModel(GLenum);
EXTERN void STDCALL glStencilFunc(GLenum, GLint, GLuint);
EXTERN void STDCALL glStencilMask(GLuint);
EXTERN void STDCALL glStencilOp(GLenum, GLenum, GLenum);
EXTERN void STDCALL glTexCoord1d(GLdouble);
EXTERN void STDCALL glTexCoord1dv(const GLdouble*);
EXTERN void STDCALL glTexCoord1f(GLfloat);
EXTERN void STDCALL glTexCoord1fv(const GLfloat*);
EXTERN void STDCALL glTexCoord1i(GLint);
EXTERN void STDCALL glTexCoord1iv(const GLint*);
EXTERN void STDCALL glTexCoord1s(GLshort);
EXTERN void STDCALL glTexCoord1sv(const GLshort*);
EXTERN void STDCALL glTexCoord2d(GLdouble, GLdouble);
EXTERN void STDCALL glTexCoord2dv(const GLdouble*);
EXTERN void STDCALL glTexCoord2f(GLfloat, GLfloat);
EXTERN void STDCALL glTexCoord2fv(const GLfloat*);
EXTERN void STDCALL glTexCoord2i(GLint, GLint);
EXTERN void STDCALL glTexCoord2iv(const GLint*);
EXTERN void STDCALL glTexCoord2s(GLshort, GLshort);
EXTERN void STDCALL glTexCoord2sv(const GLshort*);
EXTERN void STDCALL glTexCoord3d(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glTexCoord3dv(const GLdouble*);
EXTERN void STDCALL glTexCoord3f(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glTexCoord3fv(const GLfloat*);
EXTERN void STDCALL glTexCoord3i(GLint, GLint, GLint);
EXTERN void STDCALL glTexCoord3iv(const GLint*);
EXTERN void STDCALL glTexCoord3s(GLshort, GLshort, GLshort);
EXTERN void STDCALL glTexCoord3sv(const GLshort*);
EXTERN void STDCALL glTexCoord4d(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glTexCoord4dv(const GLdouble*);
EXTERN void STDCALL glTexCoord4f(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glTexCoord4fv(const GLfloat*);
EXTERN void STDCALL glTexCoord4i(GLint, GLint, GLint, GLint);
EXTERN void STDCALL glTexCoord4iv(const GLint*);
EXTERN void STDCALL glTexCoord4s(GLshort, GLshort, GLshort, GLshort);
EXTERN void STDCALL glTexCoord4sv(const GLshort*);
EXTERN void STDCALL glTexCoordPointer(GLint, GLenum, GLsizei, const GLvoid*);
EXTERN void STDCALL glTexEnvf(GLenum, GLenum, GLfloat);
EXTERN void STDCALL glTexEnvfv(GLenum, GLenum, const GLfloat*);
EXTERN void STDCALL glTexEnvi(GLenum, GLenum, GLint);
EXTERN void STDCALL glTexEnviv(GLenum, GLenum, const GLint*);
EXTERN void STDCALL glTexGend(GLenum, GLenum, GLdouble);
EXTERN void STDCALL glTexGendv(GLenum, GLenum, const GLdouble*);
EXTERN void STDCALL glTexGenf(GLenum, GLenum, GLfloat);
EXTERN void STDCALL glTexGenfv(GLenum, GLenum, const GLfloat*);
EXTERN void STDCALL glTexGeni(GLenum, GLenum, GLint);
EXTERN void STDCALL glTexGeniv(GLenum, GLenum, const GLint*);
EXTERN void STDCALL glTexImage1D(GLenum, GLint, GLint, GLsizei, GLint,
    GLenum, GLenum, const GLvoid*);
EXTERN void STDCALL glTexImage2D(GLenum, GLint, GLint, GLsizei, GLsizei,
    GLint, GLenum, GLenum, const GLvoid*);
EXTERN void STDCALL glTexParameterf(GLenum, GLenum, GLfloat);
EXTERN void STDCALL glTexParameterfv(GLenum, GLenum, const GLfloat*);
EXTERN void STDCALL glTexParameteri(GLenum, GLenum, GLint);
EXTERN void STDCALL glTexParameteriv(GLenum, GLenum, const GLint*);
EXTERN void STDCALL glTexSubImage1D(GLenum, GLint, GLint, GLsizei, GLenum,
    GLenum, const GLvoid*);
EXTERN void STDCALL glTexSubImage2D(GLenum, GLint, GLint, GLint, GLsizei,
    GLsizei, GLenum, GLenum, const GLvoid*);
EXTERN void STDCALL glTranslated(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glTranslatef(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glVertex2d(GLdouble, GLdouble);
EXTERN void STDCALL glVertex2dv(const GLdouble*);
EXTERN void STDCALL glVertex2f(GLfloat, GLfloat);
EXTERN void STDCALL glVertex2fv(const GLfloat*);
EXTERN void STDCALL glVertex2i(GLint, GLint);
EXTERN void STDCALL glVertex2iv(const GLint*);
EXTERN void STDCALL glVertex2s(GLshort, GLshort);
EXTERN void STDCALL glVertex2sv(const GLshort*);
EXTERN void STDCALL glVertex3d(GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glVertex3dv(const GLdouble*);
EXTERN void STDCALL glVertex3f(GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glVertex3fv(const GLfloat*);
EXTERN void STDCALL glVertex3i(GLint, GLint, GLint);
EXTERN void STDCALL glVertex3iv(const GLint*);
EXTERN void STDCALL glVertex3s(GLshort, GLshort, GLshort);
EXTERN void STDCALL glVertex3sv(const GLshort*);
EXTERN void STDCALL glVertex4d(GLdouble, GLdouble, GLdouble, GLdouble);
EXTERN void STDCALL glVertex4dv(const GLdouble*);
EXTERN void STDCALL glVertex4f(GLfloat, GLfloat, GLfloat, GLfloat);
EXTERN void STDCALL glVertex4fv(const GLfloat*);
EXTERN void STDCALL glVertex4i(GLint, GLint, GLint, GLint);
EXTERN void STDCALL glVertex4iv(const GLint*);
EXTERN void STDCALL glVertex4s(GLshort, GLshort, GLshort, GLshort);
EXTERN void STDCALL glVertex4sv(const GLshort*);
EXTERN void STDCALL glVertexPointer(GLint, GLenum, GLsizei, const GLvoid*);
EXTERN void STDCALL glViewport(GLint, GLint, GLsizei, GLsizei);

}  /* extern "C" */

/*--------------------------------------------------------------------------*/
void SE_glAccum(GLenum eOperation, GLfloat fValue)
{
    SE_PRE_BODY_A2(glAccum, eOperation, fValue);
}
/*--------------------------------------------------------------------------*/
void SE_glAlphaFunc(GLenum eFunction, GLclampf fReference)
{
    SE_PRE_BODY_A2(glAlphaFunc, eFunction, fReference);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glAreTexturesResident(GLsizei iNumTextures,
    const GLuint* auiTextures, GLboolean* aucResidences)
{
    SE_PRE_BODY_A3_RET(glAreTexturesResident, iNumTextures, auiTextures,
        aucResidences, GLboolean);
}
/*--------------------------------------------------------------------------*/
void SE_glArrayElement(GLint i)
{
    SE_PRE_BODY_A1(glArrayElement, i);
}
/*--------------------------------------------------------------------------*/
void SE_glBegin(GLenum eMode)
{
    SE_PRE_BODY_A1(glBegin, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glBindTexture(GLenum eTarget, GLuint uiTexture)
{
    SE_PRE_BODY_A2(glBindTexture, eTarget, uiTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glBitmap(GLsizei iWidth, GLsizei iHeight, GLfloat fXOrigin,
    GLfloat fYOrigin, GLfloat fXMove, GLfloat fYMove,
    const GLubyte* aucBitmap)
{
    SE_PRE_BODY_A7(glBitmap, iWidth, iHeight, fXOrigin, fYOrigin, fXMove, fYMove,
        aucBitmap);
}
/*--------------------------------------------------------------------------*/
void SE_glBlendFunc(GLenum eSrcFunction, GLenum eDstFunction)
{
    SE_PRE_BODY_A2(glBlendFunc, eSrcFunction, eDstFunction);
}
/*--------------------------------------------------------------------------*/
void SE_glCallList(GLuint uiList)
{
    SE_PRE_BODY_A1(glCallList,uiList);
}
/*--------------------------------------------------------------------------*/
void SE_glCallLists(GLsizei iNumLists, GLenum eType, const GLvoid* pvLists)
{
    SE_PRE_BODY_A3(glCallLists, iNumLists, eType, pvLists);
}
/*--------------------------------------------------------------------------*/
void SE_glClear(GLbitfield uiMask)
{
    SE_PRE_BODY_A1(glClear, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glClearAccum(GLfloat fRed, GLfloat fGreen, GLfloat fBlue,
    GLfloat fAlpha)
{
    SE_PRE_BODY_A4(glClearAccum, fRed, fGreen, fBlue, fAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glClearColor(GLclampf fRed, GLclampf fGreen, GLclampf fBlue,
    GLclampf fAlpha)
{
    SE_PRE_BODY_A4(glClearColor, fRed, fGreen, fBlue, fAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glClearDepth(GLclampd dDepth)
{
    SE_PRE_BODY_A1(glClearDepth, dDepth);
}
/*--------------------------------------------------------------------------*/
void SE_glClearIndex(GLfloat fIndex)
{
    SE_PRE_BODY_A1(glClearIndex, fIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glClearStencil(GLint iStencil)
{
    SE_PRE_BODY_A1(glClearStencil, iStencil);
}
/*--------------------------------------------------------------------------*/
void SE_glClipPlane(GLenum ePlane, const GLdouble* adEquation)
{
    SE_PRE_BODY_A2(glClipPlane, ePlane, adEquation);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3b(GLbyte cRed, GLbyte cGreen, GLbyte cBlue)
{
    SE_PRE_BODY_A3(glColor3b, cRed, cGreen, cBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3bv(const GLbyte* acRGB)
{
    SE_PRE_BODY_A1(glColor3bv, acRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3d(GLdouble dRed, GLdouble dGreen, GLdouble dBlue)
{
    SE_PRE_BODY_A3(glColor3d, dRed, dGreen, dBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3dv(const GLdouble* adRGB)
{
    SE_PRE_BODY_A1(glColor3dv, adRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3f(GLfloat fRed, GLfloat fGreen, GLfloat fBlue)
{
    SE_PRE_BODY_A3(glColor3f, fRed, fGreen, fBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3fv(const GLfloat* afRGB)
{
    SE_PRE_BODY_A1(glColor3fv, afRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3i(GLint iRed, GLint iGreen, GLint iBlue)
{
    SE_PRE_BODY_A3(glColor3i, iRed, iGreen, iBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3iv(const GLint* aiRGB)
{
    SE_PRE_BODY_A1(glColor3iv, aiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3s(GLshort sRed, GLshort sGreen, GLshort sBlue)
{
    SE_PRE_BODY_A3(glColor3s, sRed, sGreen, sBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3sv(const GLshort* asColor)
{
    SE_PRE_BODY_A1(glColor3sv, asColor);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3ub(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue)
{
    SE_PRE_BODY_A3(glColor3ub, ucRed, ucGreen, ucBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3ubv(const GLubyte* aucRGB)
{
    SE_PRE_BODY_A1(glColor3ubv, aucRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3ui(GLuint uiRed, GLuint uiGreen, GLuint uiBlue)
{
    SE_PRE_BODY_A3(glColor3ui, uiRed, uiGreen, uiBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3uiv(const GLuint* auiRGB)
{
    SE_PRE_BODY_A1(glColor3uiv, auiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3us(GLushort usRed, GLushort usGreen, GLushort usBlue)
{
    SE_PRE_BODY_A3(glColor3us, usRed, usGreen, usBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glColor3usv(const GLushort* ausRGB)
{
    SE_PRE_BODY_A1(glColor3usv, ausRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4b(GLbyte cRed, GLbyte cGreen, GLbyte cBlue, GLbyte cAlpha)
{
    SE_PRE_BODY_A4(glColor4b, cRed, cGreen, cBlue, cAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4bv(const GLbyte* acRGBA)
{
    SE_PRE_BODY_A1(glColor4bv, acRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4d(GLdouble dRed, GLdouble dGreen, GLdouble dBlue,
    GLdouble dAlpha)
{
    SE_PRE_BODY_A4(glColor4d, dRed, dGreen, dBlue, dAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4dv(const GLdouble* adRGBA)
{
    SE_PRE_BODY_A1(glColor4dv, adRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4f(GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha)
{
    SE_PRE_BODY_A4(glColor4f, fRed, fGreen, fBlue, fAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4fv(const GLfloat* afRGBA)
{
    SE_PRE_BODY_A1(glColor4fv, afRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4i(GLint iRed, GLint iGreen, GLint iBlue, GLint iAlpha)
{
    SE_PRE_BODY_A4(glColor4i, iRed, iGreen, iBlue, iAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4iv(const GLint* aiRGBA)
{
    SE_PRE_BODY_A1(glColor4iv, aiRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4s(GLshort sRed, GLshort sGreen, GLshort sBlue, GLshort sAlpha)
{
    SE_PRE_BODY_A4(glColor4s, sRed, sGreen, sBlue, sAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4sv(const GLshort* asRGBA)
{
    SE_PRE_BODY_A1(glColor4sv, asRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4ub(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue,
    GLubyte ucAlpha)
{
    SE_PRE_BODY_A4(glColor4ub, ucRed, ucGreen, ucBlue, ucAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4ubv(const GLubyte* aucRGBA)
{
    SE_PRE_BODY_A1(glColor4ubv, aucRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4ui(GLuint uiRed, GLuint uiGreen, GLuint uiBlue,
    GLuint uiAlpha)
{
    SE_PRE_BODY_A4(glColor4ui, uiRed, uiGreen, uiBlue, uiAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4uiv(const GLuint* auiRGBA)
{
    SE_PRE_BODY_A1(glColor4uiv, auiRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4us(GLushort usRed, GLushort usGreen, GLushort usBlue,
    GLushort usAlpha)
{
    SE_PRE_BODY_A4(glColor4us, usRed, usGreen, usBlue, usAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColor4usv(const GLushort* ausRGBA)
{
    SE_PRE_BODY_A1(glColor4usv, ausRGBA);
}
/*--------------------------------------------------------------------------*/
void SE_glColorMask(GLboolean ucRed, GLboolean ucGreen, GLboolean ucBlue,
    GLboolean ucAlpha)
{
    SE_PRE_BODY_A4(glColorMask, ucRed, ucGreen, ucBlue, ucAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glColorMaterial(GLenum eFace, GLenum eMode)
{
    SE_PRE_BODY_A2(glColorMaterial, eFace, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glColorPointer(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_PRE_BODY_A4(glColorPointer, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyPixels(GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight,
    GLenum eType)
{
    SE_PRE_BODY_A5(glCopyPixels, iX, iY, iWidth, iHeight, eType);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexImage1D(GLenum eTarget, GLint iLevel, GLenum eInternalFormat,
    GLint iX, GLint iY, GLsizei iWidth, GLint iBorder)
{
    SE_PRE_BODY_A7(glCopyTexImage1D, eTarget, iLevel, eInternalFormat, iX, iY,
        iWidth, iBorder);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexImage2D(GLenum eTarget, GLint iLevel, GLenum eInternalFormat,
    GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight, GLint iBorder)
{
    SE_PRE_BODY_A8(glCopyTexImage2D, eTarget, iLevel, eInternalFormat, iX, iY,
        iWidth, iHeight, iBorder);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage1D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iX, GLint iY, GLsizei iWidth)
{
    SE_PRE_BODY_A6(glCopyTexSubImage1D, eTarget, iLevel, iXOffset, iX, iY, iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage2D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_PRE_BODY_A8(glCopyTexSubImage2D, eTarget, iLevel, iXOffset, iYOffset, iX, iY,
        iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glCullFace(GLenum eMode)
{
    SE_PRE_BODY_A1(glCullFace, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteLists(GLuint uiList, GLsizei iRange)
{
    SE_PRE_BODY_A2(glDeleteLists, uiList, iRange);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteTextures(GLsizei iNumTextures, const GLuint* auiTextures)
{
    SE_PRE_BODY_A2(glDeleteTextures, iNumTextures, auiTextures);
}
/*--------------------------------------------------------------------------*/
void SE_glDepthFunc(GLenum eFunction)
{
    SE_PRE_BODY_A1(glDepthFunc, eFunction);
}
/*--------------------------------------------------------------------------*/
void SE_glDepthMask(GLboolean ucMask)
{
    SE_PRE_BODY_A1(glDepthMask, ucMask);
}
/*--------------------------------------------------------------------------*/
void SE_glDepthRange(GLclampd dZNear, GLclampd dZFar)
{
    SE_PRE_BODY_A2(glDepthRange, dZNear, dZFar);
}
/*--------------------------------------------------------------------------*/
void SE_glDisable(GLenum eCapability)
{
    SE_PRE_BODY_A1(glDisable, eCapability);
}
/*--------------------------------------------------------------------------*/
void SE_glDisableClientState(GLenum eArray)
{
    SE_PRE_BODY_A1(glDisableClientState, eArray);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawArrays(GLenum eMode, GLint iFirst, GLsizei iCount)
{
    SE_PRE_BODY_A3(glDrawArrays, eMode, iFirst, iCount);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawBuffer(GLenum eMode)
{
    SE_PRE_BODY_A1(glDrawBuffer, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawElements(GLenum eMode, GLsizei iCount, GLenum eType,
    const GLvoid* pvIndices)
{
    SE_PRE_BODY_A4(glDrawElements, eMode, iCount, eType, pvIndices);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawPixels(GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvPixels)
{
    SE_PRE_BODY_A5(glDrawPixels, iWidth, iHeight, eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glEdgeFlag(GLboolean ucFlag)
{
    SE_PRE_BODY_A1(glEdgeFlag, ucFlag);
}
/*--------------------------------------------------------------------------*/
void SE_glEdgeFlagv(const GLboolean* aucFlag)
{
    SE_PRE_BODY_A1(glEdgeFlagv, aucFlag);
}
/*--------------------------------------------------------------------------*/
void SE_glEdgeFlagPointer(GLsizei iStride, const GLvoid* pvPointer)
{
    SE_PRE_BODY_A2(glEdgeFlagPointer, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glEnable(GLenum eCapability)
{
    SE_PRE_BODY_A1(glEnable, eCapability);
}
/*--------------------------------------------------------------------------*/
void SE_glEnableClientState(GLenum eArray)
{
    SE_PRE_BODY_A1(glEnableClientState, eArray);
}
/*--------------------------------------------------------------------------*/
void SE_glEnd()
{
    SE_PRE_BODY_A0(glEnd);
}
/*--------------------------------------------------------------------------*/
void SE_glEndList()
{
    SE_PRE_BODY_A0(glEndList);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord1f(GLfloat fU)
{
    SE_PRE_BODY_A1(glEvalCoord1f, fU);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord1fv(const GLfloat* pfU)
{
    SE_PRE_BODY_A1(glEvalCoord1fv, pfU);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord1d(GLdouble dU)
{
    SE_PRE_BODY_A1(glEvalCoord1d, dU);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord1dv(const GLdouble* pdU)
{
    SE_PRE_BODY_A1(glEvalCoord1dv, pdU);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord2f(GLfloat fU, GLfloat fV)
{
    SE_PRE_BODY_A2(glEvalCoord2f, fU, fV);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord2fv(const GLfloat* afUV)
{
    SE_PRE_BODY_A1(glEvalCoord2fv, afUV);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord2d(GLdouble dU, GLdouble dV)
{
    SE_PRE_BODY_A2(glEvalCoord2d, dU, dV);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalCoord2dv(const GLdouble* adUV)
{
    SE_PRE_BODY_A1(glEvalCoord2dv, adUV);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalMesh1(GLenum eMode, GLint i1, GLint i2)
{
    SE_PRE_BODY_A3(glEvalMesh1, eMode, i1, i2);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalMesh2(GLenum eMode, GLint i1, GLint i2, GLint j1, GLint j2)
{
    SE_PRE_BODY_A5(glEvalMesh2, eMode, i1, i2, j1, j2);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalPoint1(GLint i)
{
    SE_PRE_BODY_A1(glEvalPoint1, i);
}
/*--------------------------------------------------------------------------*/
void SE_glEvalPoint2(GLint i, GLint j)
{
    SE_PRE_BODY_A2(glEvalPoint2, i, j);
}
/*--------------------------------------------------------------------------*/
void SE_glFeedbackBuffer(GLsizei iSize, GLenum eType, GLfloat* afBuffer)
{
    SE_PRE_BODY_A3(glFeedbackBuffer, iSize, eType, afBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glFinish()
{
    SE_PRE_BODY_A0(glFinish);
}
/*--------------------------------------------------------------------------*/
void SE_glFlush()
{
    SE_PRE_BODY_A0(glFlush);
}
/*--------------------------------------------------------------------------*/
void SE_glFogf(GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A2(glFogf, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glFogfv(GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A2(glFogfv, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glFogi(GLenum ePName, int iParam)
{
    SE_PRE_BODY_A2(glFogi, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glFogiv(GLenum ePName, const int* aiParam)
{
    SE_PRE_BODY_A2(glFogiv, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glFrontFace(GLenum eMode)
{
    SE_PRE_BODY_A1(glFrontFace, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glFrustum(GLdouble dLeft, GLdouble dRight, GLdouble dBottom,
    GLdouble dTop, GLdouble dZNear, GLdouble dZFar)
{
    SE_PRE_BODY_A6(glFrustum, dLeft, dRight, dBottom, dTop, dZNear, dZFar);
}
/*--------------------------------------------------------------------------*/
GLuint SE_glGenLists(GLsizei iRange)
{
    SE_PRE_BODY_A1_RET(glGenLists, iRange, GLuint);
}
/*--------------------------------------------------------------------------*/
void SE_glGenTextures(GLsizei iNumTextures, GLuint* auiTexture)
{
    SE_PRE_BODY_A2(glGenTextures, iNumTextures, auiTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBooleanv(GLenum ePName, GLboolean* aucParam)
{
    SE_PRE_BODY_A2(glGetBooleanv, ePName, aucParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetClipPlane(GLenum ePlane, GLdouble* adEquation)
{
    SE_PRE_BODY_A2(glGetClipPlane, ePlane, adEquation);
}
/*--------------------------------------------------------------------------*/
void SE_glGetDoublev(GLenum ePName, GLdouble* adParam)
{
    SE_PRE_BODY_A2(glGetDoublev, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
GLenum SE_glGetError()
{
    SE_PRE_BODY_A0_RET(glGetError, GLenum);
}
/*--------------------------------------------------------------------------*/
void SE_glGetFloatv(GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A2(glGetFloatv, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetIntegerv(GLenum ePName, int* aiParam)
{
    SE_PRE_BODY_A2(glGetIntegerv, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetLightfv(GLenum eLight, GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A3(glGetLightfv, eLight, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetLightiv(GLenum eLight, GLenum ePName, int* aiParam)
{
    SE_PRE_BODY_A3(glGetLightiv, eLight, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMapdv(GLenum eTarget, GLenum eQuery, GLdouble* adValue)
{
    SE_PRE_BODY_A3(glGetMapdv, eTarget, eQuery, adValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMapfv(GLenum eTarget, GLenum eQuery, GLfloat* afValue)
{
    SE_PRE_BODY_A3(glGetMapfv, eTarget, eQuery, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMapiv(GLenum eTarget, GLenum eQuery, GLint* aiValue)
{
    SE_PRE_BODY_A3(glGetMapiv, eTarget, eQuery, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMaterialfv(GLenum eFace, GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A3(glGetMaterialfv, eFace, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMaterialiv(GLenum eFace, GLenum ePName, GLint* aiParam)
{
    SE_PRE_BODY_A3(glGetMaterialiv, eFace, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPixelMapfv(GLenum eMap, GLfloat* afValue)
{
    SE_PRE_BODY_A2(glGetPixelMapfv, eMap, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPixelMapuiv(GLenum eMap, GLuint* auiValue)
{
    SE_PRE_BODY_A2(glGetPixelMapuiv, eMap, auiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPixelMapusv(GLenum eMap, GLushort* ausValue)
{
    SE_PRE_BODY_A2(glGetPixelMapusv, eMap, ausValue);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPointerv(GLenum ePName, GLvoid** apvParam)
{
    SE_PRE_BODY_A2(glGetPointerv, ePName, apvParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPolygonStipple(GLubyte* aucPattern)
{
    SE_PRE_BODY_A1(glGetPolygonStipple, aucPattern);
}
/*--------------------------------------------------------------------------*/
const GLubyte* SE_glGetString(GLenum eName)
{
    SE_PRE_BODY_A1_RET(glGetString, eName, const GLubyte*);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexEnvfv(GLenum eTarget, GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A3(glGetTexEnvfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexEnviv(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_PRE_BODY_A3(glGetTexEnviv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexGendv(GLenum eCoord, GLenum ePName, GLdouble* adParam)
{
    SE_PRE_BODY_A3(glGetTexGendv, eCoord, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexGenfv(GLenum eCoord, GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A3(glGetTexGenfv, eCoord, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexGeniv(GLenum eCoord, GLenum ePName, GLint* aiParam)
{
    SE_PRE_BODY_A3(glGetTexGeniv, eCoord, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexImage(GLenum eTarget, GLint iLevel, GLenum eFormat,
    GLenum eType, GLvoid* pvPixels)
{
    SE_PRE_BODY_A5(glGetTexImage, eTarget, iLevel,eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexLevelParameterfv(GLenum eTarget, GLint iLevel, GLenum ePName,
    GLfloat* afParam)
{
    SE_PRE_BODY_A4(glGetTexLevelParameterfv, eTarget, iLevel, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexLevelParameteriv(GLenum eTarget, GLint iLevel, GLenum ePName,
    GLint* aiParam)
{
    SE_PRE_BODY_A4(glGetTexLevelParameteriv, eTarget, iLevel, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexParameterfv(GLenum eTarget, GLenum ePName, GLfloat* afParam)
{
    SE_PRE_BODY_A3(glGetTexParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetTexParameteriv(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_PRE_BODY_A3(glGetTexParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glHint(GLenum eTarget, GLenum eMode)
{
    SE_PRE_BODY_A2(glHint, eTarget, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexMask(GLuint uiMask)
{
    SE_PRE_BODY_A1(glIndexMask, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexPointer(GLenum eType, GLsizei iStride, const GLvoid* pvPointer)
{
    SE_PRE_BODY_A3(glIndexPointer, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexd(GLdouble dIndex)
{
    SE_PRE_BODY_A1(glIndexd, dIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexdv(const GLdouble* pdIndex)
{
    SE_PRE_BODY_A1(glIndexdv, pdIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexf(GLfloat fIndex)
{
    SE_PRE_BODY_A1(glIndexf, fIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexfv(const GLfloat* pfIndex)
{
    SE_PRE_BODY_A1(glIndexfv, pfIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexi(GLint iIndex)
{
    SE_PRE_BODY_A1(glIndexi, iIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexiv(const GLint* piIndex)
{
    SE_PRE_BODY_A1(glIndexiv, piIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexs(GLshort sIndex)
{
    SE_PRE_BODY_A1(glIndexs, sIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexsv(const GLshort* psIndex)
{
    SE_PRE_BODY_A1(glIndexsv, psIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexub(GLubyte ucIndex)
{
    SE_PRE_BODY_A1(glIndexub, ucIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexubv(const GLubyte* pucIndex)
{
    SE_PRE_BODY_A1(glIndexubv, pucIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glInitNames()
{
    SE_PRE_BODY_A0(glInitNames);
}
/*--------------------------------------------------------------------------*/
void SE_glInterleavedArrays(GLenum eFormat, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_PRE_BODY_A3(glInterleavedArrays, eFormat, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsEnabled(GLenum eCapability)
{
    SE_PRE_BODY_A1_RET(glIsEnabled, eCapability, GLboolean);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsList(GLuint uiList)
{
    SE_PRE_BODY_A1_RET(glIsList, uiList, GLboolean);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsTexture(GLuint uiTexture)
{
    SE_PRE_BODY_A1_RET(glIsTexture, uiTexture, GLboolean);
}
/*--------------------------------------------------------------------------*/
void SE_glLightModelf(GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A2(glLightModelf, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightModelfv(GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A2(glLightModelfv, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightModeli(GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A2(glLightModeli, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightModeliv(GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A2(glLightModeliv, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightf(GLenum eLight, GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A3(glLightf, eLight, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightfv(GLenum eLight, GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A3(glLightfv, eLight, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLighti(GLenum eLight, GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A3(glLighti, eLight, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLightiv(GLenum eLight, GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A3(glLightiv, eLight, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLineStipple(GLint iFactor, GLushort usPattern)
{
    SE_PRE_BODY_A2(glLineStipple, iFactor, usPattern);
}
/*--------------------------------------------------------------------------*/
void SE_glLineWidth(GLfloat fWidth)
{
    SE_PRE_BODY_A1(glLineWidth, fWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glListBase(GLuint uiBase)
{
    SE_PRE_BODY_A1(glListBase, uiBase);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadIdentity()
{
    SE_PRE_BODY_A0(glLoadIdentity);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadMatrixd(const GLdouble* adMatrix)
{
    SE_PRE_BODY_A1(glLoadMatrixd, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadMatrixf(const GLfloat* afMatrix)
{
    SE_PRE_BODY_A1(glLoadMatrixf, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadName(GLuint uiName)
{
    SE_PRE_BODY_A1(glLoadName, uiName);
}
/*--------------------------------------------------------------------------*/
void SE_glLogicOp(GLenum eOpCode)
{
    SE_PRE_BODY_A1(glLogicOp, eOpCode);
}
/*--------------------------------------------------------------------------*/
void SE_glMap1d(GLenum eTarget, GLdouble dU1, GLdouble dU2, GLint iStride,
    GLint iOrder, const GLdouble* adPoints)
{
    SE_PRE_BODY_A6(glMap1d, eTarget, dU1, dU2, iStride, iOrder, adPoints);
}
/*--------------------------------------------------------------------------*/
void SE_glMap1f(GLenum eTarget, GLfloat fU1, GLfloat fU2, GLint iStride,
    GLint iOrder, const GLfloat* afPoints)
{
    SE_PRE_BODY_A6(glMap1f, eTarget, fU1, fU2, iStride, iOrder, afPoints);
}
/*--------------------------------------------------------------------------*/
void SE_glMap2d(GLenum eTarget, GLdouble dU1, GLdouble dU2, GLint iUStride,
    GLint iUOrder, GLdouble dV1, GLdouble dV2, GLint iVStride, GLint iVOrder,
    const GLdouble* adPoints)
{
    SE_PRE_BODY_A10(glMap2d, eTarget, dU1, dU2, iUStride, iUOrder, dV1, dV2,
        iVStride, iVOrder, adPoints);
}
/*--------------------------------------------------------------------------*/
void SE_glMap2f(GLenum eTarget, GLfloat fU1, GLfloat fU2, GLint iUStride,
    GLint iUOrder, GLfloat fV1, GLfloat fV2, GLint iVStride, GLint iVOrder,
    const GLfloat* afPoints)
{
    SE_PRE_BODY_A10(glMap2f, eTarget, fU1, fU2, iUStride, iUOrder, fV1, fV2,
        iVStride, iVOrder, afPoints);
}
/*--------------------------------------------------------------------------*/
void SE_glMapGrid1d(GLint iNumUPartitions, GLdouble dU1, GLdouble dU2)
{
    SE_PRE_BODY_A3(glMapGrid1d, iNumUPartitions, dU1, dU2);
}
/*--------------------------------------------------------------------------*/
void SE_glMapGrid1f(GLint iNumUPartitions, GLfloat fU1, GLfloat fU2)
{
    SE_PRE_BODY_A3(glMapGrid1f, iNumUPartitions, fU1, fU2);
}
/*--------------------------------------------------------------------------*/
void SE_glMapGrid2d(GLint iNumUPartitions, GLdouble dU1, GLdouble dU2,
    GLint iNumVPartitions, GLdouble dV1, GLdouble dV2)
{
    SE_PRE_BODY_A6(glMapGrid2d, iNumUPartitions, dU1, dU2, iNumVPartitions, dV1,
        dV2);
}
/*--------------------------------------------------------------------------*/
void SE_glMapGrid2f(GLint iNumUPartitions, GLfloat fU1, GLfloat fU2,
    GLint iNumVPartitions, GLfloat fV1, GLfloat fV2)
{
    SE_PRE_BODY_A6(glMapGrid2f, iNumUPartitions, fU1, fU2, iNumVPartitions, fV1,
        fV2);
}
/*--------------------------------------------------------------------------*/
void SE_glMaterialf(GLenum eFace, GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A3(glMaterialf, eFace, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glMaterialfv(GLenum eFace, GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A3(glMaterialfv, eFace, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glMateriali(GLenum eFace, GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A3(glMateriali, eFace, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glMaterialiv(GLenum eFace, GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A3(glMaterialiv, eFace, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glMatrixMode(GLenum eMode)
{
    SE_PRE_BODY_A1(glMatrixMode, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glMultMatrixd(const GLdouble* adMatrix)
{
    SE_PRE_BODY_A1(glMultMatrixd, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glMultMatrixf(const GLfloat* afMatrix)
{
    SE_PRE_BODY_A1(glMultMatrixf, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glNewList(GLuint uiList, GLenum eMode)
{
    SE_PRE_BODY_A2(glNewList, uiList, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3b(GLbyte bX, GLbyte bY, GLbyte bZ)
{
    SE_PRE_BODY_A3(glNormal3b, bX, bY, bZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3bv(const GLbyte* abXYZ)
{
    SE_PRE_BODY_A1(glNormal3bv, abXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3d(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A3(glNormal3d, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3dv(const GLdouble* adXYZ)
{
    SE_PRE_BODY_A1(glNormal3dv, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3f(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A3(glNormal3f, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3fv(const GLfloat* afXYZ)
{
    SE_PRE_BODY_A1(glNormal3fv, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3i(GLint iX, GLint iY, GLint iZ)
{
    SE_PRE_BODY_A3(glNormal3i, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3iv(const GLint* aiXYZ)
{
    SE_PRE_BODY_A1(glNormal3iv, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3s(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_PRE_BODY_A3(glNormal3s, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormal3sv(const GLshort* asXYZ)
{
    SE_PRE_BODY_A1(glNormal3sv, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glNormalPointer(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_PRE_BODY_A3(glNormalPointer, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glOrtho(GLdouble dLeft, GLdouble dRight, GLdouble dBottom,
    GLdouble dTop, GLdouble dZNear, GLdouble dZFar)
{
    SE_PRE_BODY_A6(glOrtho, dLeft, dRight, dBottom, dTop, dZNear, dZFar);
}
/*--------------------------------------------------------------------------*/
void SE_glPassThrough(GLfloat fToken)
{
    SE_PRE_BODY_A1(glPassThrough, fToken);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelMapfv(GLenum eMap, GLsizei iSize, const GLfloat* afValue)
{
    SE_PRE_BODY_A3(glPixelMapfv, eMap, iSize, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelMapuiv(GLenum eMap, GLsizei iSize, const GLuint* auiValue)
{
    SE_PRE_BODY_A3(glPixelMapuiv, eMap, iSize, auiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelMapusv(GLenum eMap, GLsizei iSize, const GLushort* ausValue)
{
    SE_PRE_BODY_A3(glPixelMapusv, eMap, iSize, ausValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelStoref(GLenum ePName, GLfloat fValue)
{
    SE_PRE_BODY_A2(glPixelStoref, ePName, fValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelStorei(GLenum ePName, GLint iValue)
{
    SE_PRE_BODY_A2(glPixelStorei, ePName, iValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelTransferf(GLenum ePName, GLfloat fValue)
{
    SE_PRE_BODY_A2(glPixelTransferf, ePName, fValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelTransferi(GLenum ePName, GLint iValue)
{
    SE_PRE_BODY_A2(glPixelTransferi, ePName, iValue);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelZoom(GLfloat fXFactor, GLfloat fYFactor)
{
    SE_PRE_BODY_A2(glPixelZoom, fXFactor, fYFactor);
}
/*--------------------------------------------------------------------------*/
void SE_glPointSize(GLfloat fSize)
{
    SE_PRE_BODY_A1(glPointSize, fSize);
}
/*--------------------------------------------------------------------------*/
void SE_glPolygonMode(GLenum eFace, GLenum eMode)
{
    SE_PRE_BODY_A2(glPolygonMode, eFace, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glPolygonOffset(GLfloat fScale, GLfloat fBias)
{
    SE_PRE_BODY_A2(glPolygonOffset, fScale, fBias);
}
/*--------------------------------------------------------------------------*/
void SE_glPolygonStipple(const GLubyte* aucMask)
{
    SE_PRE_BODY_A1(glPolygonStipple, aucMask);
}
/*--------------------------------------------------------------------------*/
void SE_glPopAttrib()
{
    SE_PRE_BODY_A0(glPopAttrib);
}
/*--------------------------------------------------------------------------*/
void SE_glPopClientAttrib()
{
    SE_PRE_BODY_A0(glPopClientAttrib);
}
/*--------------------------------------------------------------------------*/
void SE_glPopMatrix()
{
    SE_PRE_BODY_A0(glPopMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glPopName()
{
    SE_PRE_BODY_A0(glPopName);
}
/*--------------------------------------------------------------------------*/
void SE_glPrioritizeTextures(GLsizei iNumTextures, const GLuint* auiTextures,
    const GLclampf* afPriorities)
{
    SE_PRE_BODY_A3(glPrioritizeTextures, iNumTextures, auiTextures,
        afPriorities);
}
/*--------------------------------------------------------------------------*/
void SE_glPushAttrib(GLbitfield uiMask)
{
    SE_PRE_BODY_A1(glPushAttrib, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glPushClientAttrib(GLbitfield uiMask)
{
    SE_PRE_BODY_A1(glPushClientAttrib, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glPushMatrix()
{
    SE_PRE_BODY_A0(glPushMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glPushName(GLuint uiName)
{
    SE_PRE_BODY_A1(glPushName, uiName);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2d(GLdouble dX, GLdouble dY)
{
    SE_PRE_BODY_A2(glRasterPos2d, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2dv(const GLdouble* adXY)
{
    SE_PRE_BODY_A1(glRasterPos2dv, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2f(GLfloat fX, GLfloat fY)
{
    SE_PRE_BODY_A2(glRasterPos2f, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2fv(const GLfloat* afXY)
{
    SE_PRE_BODY_A1(glRasterPos2fv, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2i(GLint iX, GLint iY)
{
    SE_PRE_BODY_A2(glRasterPos2i, iX, iY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2iv(const GLint* aiXY)
{
    SE_PRE_BODY_A1(glRasterPos2iv, aiXY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2s(GLshort sX, GLshort sY)
{
    SE_PRE_BODY_A2(glRasterPos2s, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos2sv(const GLshort* asXY)
{
    SE_PRE_BODY_A1(glRasterPos2sv, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3d(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A3(glRasterPos3d, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3dv(const GLdouble* adXYZ)
{
    SE_PRE_BODY_A1(glRasterPos3dv, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3f(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A3(glRasterPos3f, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3fv(const GLfloat* afXYZ)
{
    SE_PRE_BODY_A1(glRasterPos3fv, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3i(GLint iX, GLint iY, GLint iZ)
{
    SE_PRE_BODY_A3(glRasterPos3i, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3iv(const GLint* aiXYZ)
{
    SE_PRE_BODY_A1(glRasterPos3iv, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3s(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_PRE_BODY_A3(glRasterPos3s, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos3sv(const GLshort* asXYZ)
{
    SE_PRE_BODY_A1(glRasterPos3sv, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4d(GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW)
{
    SE_PRE_BODY_A4(glRasterPos4d, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4dv(const GLdouble* adXYZW)
{
    SE_PRE_BODY_A1(glRasterPos4dv, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4f(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW)
{
    SE_PRE_BODY_A4(glRasterPos4f, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4fv(const GLfloat* afXYZW)
{
    SE_PRE_BODY_A1(glRasterPos4fv, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4i(GLint iX, GLint iY, GLint iZ, GLint iW)
{
    SE_PRE_BODY_A4(glRasterPos4i, iX, iY, iZ, iW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4iv(const GLint* aiXYZW)
{
    SE_PRE_BODY_A1(glRasterPos4iv, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4s(GLshort sX, GLshort sY, GLshort sZ, GLshort sW)
{
    SE_PRE_BODY_A4(glRasterPos4s, sX, sY, sZ, sW);
}
/*--------------------------------------------------------------------------*/
void SE_glRasterPos4sv(const GLshort* asXYZW)
{
    SE_PRE_BODY_A1(glRasterPos4sv, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glReadBuffer(GLenum eMode)
{
    SE_PRE_BODY_A1(glReadBuffer, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glReadPixels(GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLenum eType, GLvoid* pvPixels)
{
    SE_PRE_BODY_A7(glReadPixels, iX, iY, iWidth, iHeight, eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glRectd(GLdouble dX1, GLdouble dY1, GLdouble dX2, GLdouble dY2)
{
    SE_PRE_BODY_A4(glRectd, dX1, dY1, dX2, dY2);
}
/*--------------------------------------------------------------------------*/
void SE_glRectdv(const GLdouble* adX1Y1, const GLdouble* adX2Y2)
{
    SE_PRE_BODY_A2(glRectdv, adX1Y1, adX2Y2);
}
/*--------------------------------------------------------------------------*/
void SE_glRectf(GLfloat fX1, GLfloat fY1, GLfloat fX2, GLfloat fY2)
{
    SE_PRE_BODY_A4(glRectf, fX1, fY1, fX2, fY2);
}
/*--------------------------------------------------------------------------*/
void SE_glRectfv(const GLfloat* afX1Y1, const GLfloat* afX2Y2)
{
    SE_PRE_BODY_A2(glRectfv, afX1Y1, afX2Y2);
}
/*--------------------------------------------------------------------------*/
void SE_glRecti(GLint iX1, GLint iY1, GLint iX2, GLint iY2)
{
    SE_PRE_BODY_A4(glRecti, iX1, iY1, iX2, iY2);
}
/*--------------------------------------------------------------------------*/
void SE_glRectiv(const GLint* aiX1Y1, const GLint* aiX2Y2)
{
    SE_PRE_BODY_A2(glRectiv, aiX1Y1, aiX2Y2);
}
/*--------------------------------------------------------------------------*/
void SE_glRects(GLshort sX1, GLshort sY1, GLshort sX2, GLshort sY2)
{
    SE_PRE_BODY_A4(glRects, sX1, sY1, sX2, sY2);
}
/*--------------------------------------------------------------------------*/
void SE_glRectsv(const GLshort* asX1Y1, const GLshort* asX2Y2)
{
    SE_PRE_BODY_A2(glRectsv, asX1Y1, asX2Y2);
}
/*--------------------------------------------------------------------------*/
GLint SE_glRenderMode(GLenum eMode)
{
    SE_PRE_BODY_A1_RET(glRenderMode, eMode, GLint);
}
/*--------------------------------------------------------------------------*/
void SE_glRotated(GLdouble dAngle, GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A4(glRotated, dAngle, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glRotatef(GLfloat fAngle, GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A4(glRotatef, fAngle, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glScaled(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A3(glScaled, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glScalef(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A3(glScalef, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glScissor(GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_PRE_BODY_A4(glScissor, iX, iY, iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glSelectBuffer(GLsizei iSize, GLuint* auiBuffer)
{
    SE_PRE_BODY_A2(glSelectBuffer, iSize, auiBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glShadeModel(GLenum eMode)
{
    SE_PRE_BODY_A1(glShadeModel, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilFunc(GLenum eFunction, GLint iReference, GLuint uiMask)
{
    SE_PRE_BODY_A3(glStencilFunc, eFunction, iReference, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilMask(GLuint uiMask)
{
    SE_PRE_BODY_A1(glStencilMask, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilOp(GLenum eFail, GLenum eZFail, GLenum eZPass)
{
    SE_PRE_BODY_A3(glStencilOp, eFail, eZFail, eZPass);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1d(GLdouble dS)
{
    SE_PRE_BODY_A1(glTexCoord1d, dS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1dv(const GLdouble* pdS)
{
    SE_PRE_BODY_A1(glTexCoord1dv, pdS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1f(GLfloat fS)
{
    SE_PRE_BODY_A1(glTexCoord1f, fS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1fv(const GLfloat* pfS)
{
    SE_PRE_BODY_A1(glTexCoord1fv, pfS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1i(GLint iS)
{
    SE_PRE_BODY_A1(glTexCoord1i, iS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1iv(const GLint* piS)
{
    SE_PRE_BODY_A1(glTexCoord1iv, piS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1s(GLshort sS)
{
    SE_PRE_BODY_A1(glTexCoord1s, sS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord1sv(const GLshort* psS)
{
    SE_PRE_BODY_A1(glTexCoord1sv, psS);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2d(GLdouble dS, GLdouble dT)
{
    SE_PRE_BODY_A2(glTexCoord2d, dS, dT);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2dv(const GLdouble* adST)
{
    SE_PRE_BODY_A1(glTexCoord2dv, adST);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2f(GLfloat fS, GLfloat fT)
{
    SE_PRE_BODY_A2(glTexCoord2f, fS, fT);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2fv(const GLfloat* afST)
{
    SE_PRE_BODY_A1(glTexCoord2fv, afST);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2i(GLint iS, GLint iT)
{
    SE_PRE_BODY_A2(glTexCoord2i, iS, iT);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2iv(const GLint* aiST)
{
    SE_PRE_BODY_A1(glTexCoord2iv, aiST);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2s(GLshort sS, GLshort sT)
{
    SE_PRE_BODY_A2(glTexCoord2s, sS, sT);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord2sv(const GLshort* asST)
{
    SE_PRE_BODY_A1(glTexCoord2sv, asST);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3d(GLdouble dS, GLdouble dT, GLdouble dR)
{
    SE_PRE_BODY_A3(glTexCoord3d, dS, dT, dR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3dv(const GLdouble* adSTR)
{
    SE_PRE_BODY_A1(glTexCoord3dv, adSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3f(GLfloat fS, GLfloat fT, GLfloat fR)
{
    SE_PRE_BODY_A3(glTexCoord3f, fS, fT, fR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3fv(const GLfloat* afSTR)
{
    SE_PRE_BODY_A1(glTexCoord3fv, afSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3i(GLint iS, GLint iT, GLint iR)
{
    SE_PRE_BODY_A3(glTexCoord3i, iS, iT, iR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3iv(const GLint* aiSTR)
{
    SE_PRE_BODY_A1(glTexCoord3iv, aiSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3s(GLshort sS, GLshort sT, GLshort sR)
{
    SE_PRE_BODY_A3(glTexCoord3s, sS, sT, sR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord3sv(const GLshort* asSTR)
{
    SE_PRE_BODY_A1(glTexCoord3sv, asSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4d(GLdouble dS, GLdouble dT, GLdouble dR, GLdouble dQ)
{
    SE_PRE_BODY_A4(glTexCoord4d, dS, dT, dR, dQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4dv(const GLdouble* adSTRQ)
{
    SE_PRE_BODY_A1(glTexCoord4dv, adSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4f(GLfloat fS, GLfloat fT, GLfloat fR, GLfloat fQ)
{
    SE_PRE_BODY_A4(glTexCoord4f, fS, fT, fR, fQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4fv(const GLfloat* afSTRQ)
{
    SE_PRE_BODY_A1(glTexCoord4fv, afSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4i(GLint iS, GLint iT, GLint iR, GLint iQ)
{
    SE_PRE_BODY_A4(glTexCoord4i, iS, iT, iR, iQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4iv(const GLint* aiSTRQ)
{
    SE_PRE_BODY_A1(glTexCoord4iv, aiSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4s(GLshort sS, GLshort sT, GLshort sR, GLshort sQ)
{
    SE_PRE_BODY_A4(glTexCoord4s, sS, sT, sR, sQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoord4sv(const GLshort* asSTRQ)
{
    SE_PRE_BODY_A1(glTexCoord4sv, asSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoordPointer(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_PRE_BODY_A4(glTexCoordPointer, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glTexEnvf(GLenum eTarget, GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A3(glTexEnvf, eTarget, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexEnvfv(GLenum eTarget, GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A3(glTexEnvfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexEnvi(GLenum eTarget, GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A3(glTexEnvi, eTarget, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexEnviv(GLenum eTarget, GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A3(glTexEnviv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGend(GLenum eCoord, GLenum ePName, GLdouble dParam)
{
    SE_PRE_BODY_A3(glTexGend, eCoord, ePName, dParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGendv(GLenum eCoord, GLenum ePName, const GLdouble* adParam)
{
    SE_PRE_BODY_A3(glTexGendv, eCoord, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGenf(GLenum eCoord, GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A3(glTexGenf, eCoord, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGenfv(GLenum eCoord, GLenum ePName, const GLfloat* afParam)
{
    SE_PRE_BODY_A3(glTexGenfv, eCoord, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGeni(GLenum eCoord, GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A3(glTexGeni, eCoord, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexGeniv(GLenum eCoord, GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A3(glTexGeniv, eCoord, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexImage1D(GLenum eTarget, GLint iLevel, GLint iInternalFormat,
    GLsizei iWidth, GLint iBorder, GLenum eFormat, GLenum eType,
    const GLvoid* pvPixels)
{
    SE_PRE_BODY_A8(glTexImage1D, eTarget, iLevel, iInternalFormat, iWidth,
        iBorder, eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glTexImage2D(GLenum eTarget, GLint iLevel, GLint iInternalFormat,
    GLsizei iWidth, GLsizei iHeight, GLint iBorder, GLenum eFormat,
    GLenum eType, const GLvoid* pvPixels)
{
    SE_PRE_BODY_A9(glTexImage2D, eTarget, iLevel, iInternalFormat, iWidth,
        iHeight, iBorder, eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glTexParameterf(GLenum eTarget, GLenum ePName, GLfloat fParam)
{
    SE_PRE_BODY_A3(glTexParameterf, eTarget, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexParameterfv(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam)
{
    SE_PRE_BODY_A3(glTexParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexParameteri(GLenum eTarget, GLenum ePName, GLint iParam)
{
    SE_PRE_BODY_A3(glTexParameteri, eTarget, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexParameteriv(GLenum eTarget, GLenum ePName, const GLint* aiParam)
{
    SE_PRE_BODY_A3(glTexParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glTexSubImage1D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvPixels)
{
    SE_PRE_BODY_A7(glTexSubImage1D, eTarget, iLevel, iXOffset, iWidth, eFormat,
        eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glTexSubImage2D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvPixels)
{
    SE_PRE_BODY_A9(glTexSubImage2D, eTarget, iLevel, iXOffset, iYOffset, iWidth,
        iHeight, eFormat, eType, pvPixels);
}
/*--------------------------------------------------------------------------*/
void SE_glTranslated(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A3(glTranslated, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTranslatef(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A3(glTranslatef, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2d(GLdouble dX, GLdouble dY)
{
    SE_PRE_BODY_A2(glVertex2d, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2dv(const GLdouble* adXY)
{
    SE_PRE_BODY_A1(glVertex2dv, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2f(GLfloat fX, GLfloat fY)
{
    SE_PRE_BODY_A2(glVertex2f, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2fv(const GLfloat* afXY)
{
    SE_PRE_BODY_A1(glVertex2fv, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2i(GLint iX, GLint iY)
{
    SE_PRE_BODY_A2(glVertex2i, iX, iY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2iv(const GLint* aiXY)
{
    SE_PRE_BODY_A1(glVertex2iv, aiXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2s(GLshort sX, GLshort sY)
{
    SE_PRE_BODY_A2(glVertex2s, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex2sv(const GLshort* asXY)
{
    SE_PRE_BODY_A1(glVertex2sv, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3d(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_PRE_BODY_A3(glVertex3d, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3dv(const GLdouble* adXYZ)
{
    SE_PRE_BODY_A1(glVertex3dv, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3f(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_PRE_BODY_A3(glVertex3f, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3fv(const GLfloat* afXYZ)
{
    SE_PRE_BODY_A1(glVertex3fv, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3i(GLint iX, GLint iY, GLint iZ)
{
    SE_PRE_BODY_A3(glVertex3i, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3iv(const GLint* aiXYZ)
{
    SE_PRE_BODY_A1(glVertex3iv, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3s(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_PRE_BODY_A3(glVertex3s, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex3sv(const GLshort* asXYZ)
{
    SE_PRE_BODY_A1(glVertex3sv, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4d(GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW)
{
    SE_PRE_BODY_A4(glVertex4d, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4dv(const GLdouble* adXYZW)
{
    SE_PRE_BODY_A1(glVertex4dv, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4f(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW)
{
    SE_PRE_BODY_A4(glVertex4f, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4fv(const GLfloat* afXYZW)
{
    SE_PRE_BODY_A1(glVertex4fv, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4i(GLint iX, GLint iY, GLint iZ, GLint iW)
{
    SE_PRE_BODY_A4(glVertex4i, iX, iY, iZ, iW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4iv(const GLint* aiXYZW)
{
    SE_PRE_BODY_A1(glVertex4iv, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4s(GLshort sX, GLshort sY, GLshort sZ, GLshort sW)
{
    SE_PRE_BODY_A4(glVertex4s, sX, sY, sZ, sW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertex4sv(const GLshort* asXYZW)
{
    SE_PRE_BODY_A1(glVertex4sv, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexPointer(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_PRE_BODY_A4(glVertexPointer, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glViewport(GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_PRE_BODY_A4(glViewport, iX, iY, iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.2 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL12 = 0;

typedef void (STDCALL* PsglCopyTexSubImage3D)(GLenum, GLint, GLint,
    GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (STDCALL* PsglDrawRangeElements)(GLenum, GLuint, GLuint,
    GLsizei, GLenum, const GLvoid*);
typedef void (STDCALL* PsglTexImage3D)(GLenum, GLint, GLint, GLsizei,
    GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (STDCALL* PsglTexSubImage3D)(GLenum, GLint, GLint, GLint,
    GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*);

static PsglCopyTexSubImage3D sglCopyTexSubImage3D = 0;
static PsglDrawRangeElements sglDrawRangeElements = 0;
static PsglTexImage3D sglTexImage3D = 0;
static PsglTexSubImage3D sglTexSubImage3D = 0;
/*--------------------------------------------------------------------------*/
void SE_glDrawRangeElements(GLenum eMode, GLuint uiStart, GLuint uiEnd,
    GLsizei iCount, GLenum eType, const GLvoid* pvIndices)
{
    SE_BODY_A6(sglDrawRangeElements, eMode, uiStart, uiEnd, iCount, eType,
        pvIndices);
}
/*--------------------------------------------------------------------------*/
void SE_glTexImage3D(GLenum eTarget, GLint iLevel, GLint iInternalFormat,
    GLsizei iWidth, GLsizei iHeight, GLsizei iDepth, GLint iBorder,
    GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A10(sglTexImage3D, eTarget, iLevel, iInternalFormat, iWidth, iHeight,
        iDepth, iBorder, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glTexSubImage3D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLint iZOffset, GLsizei iWidth, GLsizei iHeight,
    GLsizei iDepth, GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A11(sglTexSubImage3D, eTarget, iLevel, iXOffset, iYOffset, iZOffset,
        iWidth, iHeight, iDepth, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage3D(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLint iZOffset, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight)
{
    SE_BODY_A9(sglCopyTexSubImage3D, eTarget, iLevel, iXOffset, iYOffset,
        iZOffset, iX, iY, iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_InitOpenGL12()
{
    if( SE_GL_GetVersion() >= SE_GL_VERSION_1_2 )
    {
        SE_ExistsOpenGL12 = 1;

        /*
        GL_ARB_imaging
            GL_EXT_blend_color
            GL_EXT_blend_minmax
            GL_EXT_color_subtable
            GL_EXT_convolution
            GL_EXT_histogram
            GL_EXT_paletted_texture
            GL_SGI_color_table
        */

        /* GL_EXT_copy_texture */
        SE_GET_FUNCTION(sglCopyTexSubImage3D);

        /* GL_EXT_draw_range_elements */
        SE_GET_FUNCTION(sglDrawRangeElements);

        /* GL_EXT_texture3D */
        SE_GET_FUNCTION(sglTexImage3D);
        SE_GET_FUNCTION(sglTexSubImage3D);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Imaging Subset (GL_ARB_imaging) */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbImaging = 0;

typedef void (STDCALL* PsglBlendColor)(GLclampf, GLclampf, GLclampf,
    GLclampf);
typedef void (STDCALL* PsglBlendEquation)(GLenum);
typedef void (STDCALL* PsglColorTable)(GLenum, GLenum, GLsizei, GLenum,
    GLenum, const GLvoid*);
typedef void (STDCALL* PsglColorTableParameterfv)(GLenum, GLenum,
    const GLfloat*);
typedef void (STDCALL* PsglColorTableParameteriv)(GLenum, GLenum,
    const GLint*);
typedef void (STDCALL* PsglCopyColorTable)(GLenum, GLenum, GLint, GLint,
    GLsizei);
typedef void (STDCALL* PsglGetColorTable)(GLenum, GLenum, GLenum,
    GLvoid*);
typedef void (STDCALL* PsglGetColorTableParameterfv)(GLenum, GLenum,
    GLfloat*);
typedef void (STDCALL* PsglGetColorTableParameteriv)(GLenum, GLenum,
    GLint*);
typedef void (STDCALL* PsglColorSubTable)(GLenum, GLsizei, GLsizei,
    GLenum, GLenum, const GLvoid*);
typedef void (STDCALL* PsglCopyColorSubTable)(GLenum, GLsizei, GLint,
    GLint, GLsizei);
typedef void (STDCALL* PsglConvolutionFilter1D)(GLenum, GLenum, GLsizei,
    GLenum, GLenum, const GLvoid*);
typedef void (STDCALL* PsglConvolutionFilter2D)(GLenum, GLenum, GLsizei,
    GLsizei, GLenum, GLenum, const GLvoid*);
typedef void (STDCALL* PsglConvolutionParameterf)(GLenum, GLenum,
    GLfloat);
typedef void (STDCALL* PsglConvolutionParameterfv)(GLenum, GLenum,
    const GLfloat*);
typedef void (STDCALL* PsglConvolutionParameteri)(GLenum, GLenum, GLint);
typedef void (STDCALL* PsglConvolutionParameteriv)(GLenum, GLenum,
    const GLint*);
typedef void (STDCALL* PsglCopyConvolutionFilter1D)(GLenum, GLenum, GLint,
    GLint, GLsizei);
typedef void (STDCALL* PsglCopyConvolutionFilter2D)(GLenum, GLenum, GLint,
    GLint, GLsizei, GLsizei);
typedef void (STDCALL* PsglGetConvolutionFilter)(GLenum, GLenum, GLenum,
    GLvoid*);
typedef void (STDCALL* PsglGetConvolutionParameterfv)(GLenum, GLenum,
    GLfloat*);
typedef void (STDCALL* PsglGetConvolutionParameteriv)(GLenum, GLenum,
    GLint*);
typedef void (STDCALL* PsglGetSeparableFilter)(GLenum, GLenum, GLenum,
    GLvoid*, GLvoid*, GLvoid*);
typedef void (STDCALL* PsglSeparableFilter2D)(GLenum, GLenum, GLsizei,
    GLsizei, GLenum, GLenum, const GLvoid*, const GLvoid*);
typedef void (STDCALL* PsglGetHistogram)(GLenum, GLboolean, GLenum,
    GLenum, GLvoid*);
typedef void (STDCALL* PsglGetHistogramParameterfv)(GLenum, GLenum,
    GLfloat*);
typedef void (STDCALL* PsglGetHistogramParameteriv)(GLenum, GLenum,
    GLint*);
typedef void (STDCALL* PsglGetMinmax)(GLenum, GLboolean, GLenum, GLenum,
    GLvoid*);
typedef void (STDCALL* PsglGetMinmaxParameterfv)(GLenum, GLenum,
    GLfloat*);
typedef void (STDCALL* PsglGetMinmaxParameteriv)(GLenum, GLenum, GLint*);
typedef void (STDCALL* PsglHistogram)(GLenum, GLsizei, GLenum, GLboolean);
typedef void (STDCALL* PsglMinmax)(GLenum, GLenum, GLboolean);
typedef void (STDCALL* PsglResetHistogram)(GLenum);
typedef void (STDCALL* PsglResetMinmax)(GLenum);

static PsglBlendColor sglBlendColor = 0;
static PsglBlendEquation sglBlendEquation = 0;
static PsglColorTable sglColorTable = 0;
static PsglColorTableParameterfv sglColorTableParameterfv = 0;
static PsglColorTableParameteriv sglColorTableParameteriv = 0;
static PsglCopyColorTable sglCopyColorTable = 0;
static PsglGetColorTable sglGetColorTable = 0;
static PsglGetColorTableParameterfv sglGetColorTableParameterfv = 0;
static PsglGetColorTableParameteriv sglGetColorTableParameteriv = 0;
static PsglColorSubTable sglColorSubTable = 0;
static PsglCopyColorSubTable sglCopyColorSubTable = 0;
static PsglConvolutionFilter1D sglConvolutionFilter1D = 0;
static PsglConvolutionFilter2D sglConvolutionFilter2D = 0;
static PsglConvolutionParameterf sglConvolutionParameterf = 0;
static PsglConvolutionParameterfv sglConvolutionParameterfv = 0;
static PsglConvolutionParameteri sglConvolutionParameteri = 0;
static PsglConvolutionParameteriv sglConvolutionParameteriv = 0;
static PsglCopyConvolutionFilter1D sglCopyConvolutionFilter1D = 0;
static PsglCopyConvolutionFilter2D sglCopyConvolutionFilter2D = 0;
static PsglGetConvolutionFilter sglGetConvolutionFilter = 0;
static PsglGetConvolutionParameterfv sglGetConvolutionParameterfv = 0;
static PsglGetConvolutionParameteriv sglGetConvolutionParameteriv = 0;
static PsglGetSeparableFilter sglGetSeparableFilter = 0;
static PsglSeparableFilter2D sglSeparableFilter2D = 0;
static PsglGetHistogram sglGetHistogram = 0;
static PsglGetHistogramParameterfv sglGetHistogramParameterfv = 0;
static PsglGetHistogramParameteriv sglGetHistogramParameteriv = 0;
static PsglGetMinmax sglGetMinmax = 0;
static PsglGetMinmaxParameterfv sglGetMinmaxParameterfv = 0;
static PsglGetMinmaxParameteriv sglGetMinmaxParameteriv = 0;
static PsglHistogram sglHistogram = 0;
static PsglMinmax sglMinmax = 0;
static PsglResetHistogram sglResetHistogram = 0;
static PsglResetMinmax sglResetMinmax = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendColor(GLclampf fRed, GLclampf fGreen, GLclampf fBlue, 
    GLclampf fAlpha)
{
    SE_BODY_A4(sglBlendColor, fRed, fGreen, fBlue, fAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glBlendEquation(GLenum eMode)
{
    SE_BODY_A1(sglBlendEquation, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glColorTable(GLenum eTarget, GLenum eInternalFormat, GLsizei iWidth, 
    GLenum eFormat, GLenum eType, const GLvoid* pvTable)
{
    SE_BODY_A6(sglColorTable, eTarget, eInternalFormat, iWidth, eFormat, eType, 
        pvTable);
}
/*--------------------------------------------------------------------------*/
void SE_glColorTableParameterfv(GLenum eTarget, GLenum ePName, 
    const GLfloat* afParam)
{
    SE_BODY_A3(sglColorTableParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glColorTableParameteriv(GLenum eTarget, GLenum ePName, 
    const GLint* aiParam)
{
    SE_BODY_A3(sglColorTableParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyColorTable(GLenum eTarget, GLenum eInternalFormat, GLint iX, 
    GLint iY, GLsizei iWidth)
{
    SE_BODY_A5(sglCopyColorTable, eTarget, eInternalFormat, iX, iY, iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTable(GLenum eTarget, GLenum eFormat, GLenum eType, 
    GLvoid* pvTable)
{
    SE_BODY_A4(sglGetColorTable, eTarget, eFormat, eType, pvTable);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTableParameterfv(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetColorTableParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTableParameteriv(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetColorTableParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glColorSubTable(GLenum eTarget, GLsizei iStart, GLsizei iCount, 
    GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A6(sglColorSubTable, eTarget, iStart, iCount, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyColorSubTable(GLenum eTarget, GLsizei iStart, GLint iX, 
    GLint iY, GLsizei iWidth)
{
    SE_BODY_A5(sglCopyColorSubTable, eTarget, iStart, iX, iY, iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionFilter1D(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvImage)
{
    SE_BODY_A6(sglConvolutionFilter1D, eTarget, eInternalFormat, iWidth, eFormat, 
        eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionFilter2D(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLsizei iHeight, GLenum eFormat, GLenum eType, 
    const GLvoid* pvImage)
{
    SE_BODY_A7(sglConvolutionFilter2D, eTarget, eInternalFormat, iWidth, iHeight, 
        eFormat, eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameterf(GLenum eTarget, GLenum ePName, GLfloat fParam)
{
    SE_BODY_A3(sglConvolutionParameterf, eTarget, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameterfv(GLenum eTarget, GLenum ePName, 
    const GLfloat* afParam)
{
    SE_BODY_A3(sglConvolutionParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameteri(GLenum eTarget, GLenum ePName, GLint iParam)
{
    SE_BODY_A3(sglConvolutionParameteri, eTarget, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameteriv(GLenum eTarget, GLenum ePName, 
    const GLint* aiParam)
{
    SE_BODY_A3(sglConvolutionParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyConvolutionFilter1D(GLenum eTarget, GLenum eInternalFormat, 
    GLint iX, GLint iY, GLsizei iWidth)
{
    SE_BODY_A5(sglCopyConvolutionFilter1D, eTarget, eInternalFormat, iX, iY, 
        iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyConvolutionFilter2D(GLenum eTarget, GLenum eInternalFormat, 
    GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_BODY_A6(sglCopyConvolutionFilter2D, eTarget, eInternalFormat, iX, iY, 
        iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionFilter(GLenum eTarget, GLenum eFormat, GLenum eType, 
    GLvoid* pvImage)
{
    SE_BODY_A4(sglGetConvolutionFilter, eTarget, eFormat, eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionParameterfv(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetConvolutionParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionParameteriv(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetConvolutionParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetSeparableFilter(GLenum eTarget, GLenum eFormat, GLenum eType, 
    GLvoid* pvRow, GLvoid* pvColumn, GLvoid* pvSpan)
{
    SE_BODY_A6(sglGetSeparableFilter, eTarget, eFormat, eType, pvRow, pvColumn, 
        pvSpan);
}
/*--------------------------------------------------------------------------*/
void SE_glSeparableFilter2D(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLsizei iHeight, GLenum eFormat, GLenum eType, 
    const GLvoid* pvRow, const GLvoid* pvColumn)
{
    SE_BODY_A8(sglSeparableFilter2D, eTarget, eInternalFormat, iWidth, iHeight, 
        eFormat, eType, pvRow, pvColumn);
}
/*--------------------------------------------------------------------------*/
void SE_glGetHistogram(GLenum eTarget, GLboolean ucReset, GLenum eFormat, 
    GLenum eType, GLvoid* pvValues)
{
    SE_BODY_A5(sglGetHistogram, eTarget, ucReset, eFormat, eType, pvValues);
}
/*--------------------------------------------------------------------------*/
void SE_glGetHistogramParameterfv(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetHistogramParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetHistogramParameteriv(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetHistogramParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmax(GLenum eTarget, GLboolean ucReset, GLenum eFormat, 
    GLenum eType, GLvoid* pvValues)
{
    SE_BODY_A5(sglGetMinmax, eTarget, ucReset, eFormat, eType, pvValues);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmaxParameterfv(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetMinmaxParameterfv, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmaxParameteriv(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetMinmaxParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glHistogram(GLenum eTarget, GLsizei iWidth, GLenum eInternalFormat, 
    GLboolean ucSink)
{
    SE_BODY_A4(sglHistogram, eTarget, iWidth, eInternalFormat, ucSink);
}
/*--------------------------------------------------------------------------*/
void SE_glMinmax(GLenum eTarget, GLenum eInternalFormat, GLboolean ucSink)
{
    SE_BODY_A3(sglMinmax, eTarget, eInternalFormat, ucSink);
}
/*--------------------------------------------------------------------------*/
void SE_glResetHistogram(GLenum eTarget)
{
    SE_BODY_A1(sglResetHistogram, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_glResetMinmax(GLenum eTarget)
{
    SE_BODY_A1(sglResetMinmax, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbImaging()
{
    if( SE_GL_SupportsExtension("GL_ARB_imaging") )
    {
        SE_ExistsGlArbImaging = 1;

        /* GL_SGI_color_table */
        SE_GET_FUNCTION(sglColorTableParameterfv);
        SE_GET_FUNCTION(sglColorTableParameteriv);
        SE_GET_FUNCTION(sglCopyColorTable);

        /* GL_SGI_color_table and GL_EXT_paletted_texture */
        SE_GET_FUNCTION(sglColorTable);
        SE_GET_FUNCTION(sglGetColorTable);
        SE_GET_FUNCTION(sglGetColorTableParameterfv);
        SE_GET_FUNCTION(sglGetColorTableParameteriv);

        /* GL_EXT_color_subtable */
        SE_GET_FUNCTION(sglColorSubTable);
        SE_GET_FUNCTION(sglCopyColorSubTable);

        /* GL_EXT_convolution */
        SE_GET_FUNCTION(sglConvolutionFilter1D);
        SE_GET_FUNCTION(sglConvolutionFilter2D);
        SE_GET_FUNCTION(sglConvolutionParameterf);
        SE_GET_FUNCTION(sglConvolutionParameterfv);
        SE_GET_FUNCTION(sglConvolutionParameteri);
        SE_GET_FUNCTION(sglConvolutionParameteriv);
        SE_GET_FUNCTION(sglCopyConvolutionFilter1D);
        SE_GET_FUNCTION(sglCopyConvolutionFilter2D);
        SE_GET_FUNCTION(sglGetConvolutionFilter);
        SE_GET_FUNCTION(sglGetConvolutionParameterfv);
        SE_GET_FUNCTION(sglGetConvolutionParameteriv);
        SE_GET_FUNCTION(sglGetSeparableFilter);
        SE_GET_FUNCTION(sglSeparableFilter2D);

        /* GL_EXT_histogram */
        SE_GET_FUNCTION(sglGetHistogram);
        SE_GET_FUNCTION(sglGetHistogramParameterfv);
        SE_GET_FUNCTION(sglGetHistogramParameteriv);
        SE_GET_FUNCTION(sglGetMinmax);
        SE_GET_FUNCTION(sglGetMinmaxParameterfv);
        SE_GET_FUNCTION(sglGetMinmaxParameteriv);
        SE_GET_FUNCTION(sglHistogram);
        SE_GET_FUNCTION(sglMinmax);
        SE_GET_FUNCTION(sglResetHistogram);
        SE_GET_FUNCTION(sglResetMinmax);

        /* GL_EXT_blend_color */
        SE_GET_FUNCTION(sglBlendColor);

        /* GL_EXT_blend_minmax */
        SE_GET_FUNCTION(sglBlendEquation);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.3 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL13 = 0;

typedef void (STDCALL* PsglActiveTexture)(GLenum);
typedef void (STDCALL* PsglClientActiveTexture)(GLenum);
typedef void (STDCALL* PsglMultiTexCoord1d)(GLenum, GLdouble);
typedef void (STDCALL* PsglMultiTexCoord1dv)(GLenum, const GLdouble*);
typedef void (STDCALL* PsglMultiTexCoord1f)(GLenum, GLfloat);
typedef void (STDCALL* PsglMultiTexCoord1fv)(GLenum, const GLfloat*);
typedef void (STDCALL* PsglMultiTexCoord1i)(GLenum, int);
typedef void (STDCALL* PsglMultiTexCoord1iv)(GLenum, const GLint*);
typedef void (STDCALL* PsglMultiTexCoord1s)(GLenum, GLshort);
typedef void (STDCALL* PsglMultiTexCoord1sv)(GLenum, const GLshort*);
typedef void (STDCALL* PsglMultiTexCoord2d)(GLenum, GLdouble, GLdouble);
typedef void (STDCALL* PsglMultiTexCoord2dv)(GLenum, const GLdouble*);
typedef void (STDCALL* PsglMultiTexCoord2f)(GLenum, GLfloat, GLfloat);
typedef void (STDCALL* PsglMultiTexCoord2fv)(GLenum, const GLfloat*);
typedef void (STDCALL* PsglMultiTexCoord2i)(GLenum, GLint, GLint);
typedef void (STDCALL* PsglMultiTexCoord2iv)(GLenum, const GLint*);
typedef void (STDCALL* PsglMultiTexCoord2s)(GLenum, GLshort, GLshort);
typedef void (STDCALL* PsglMultiTexCoord2sv)(GLenum, const GLshort*);
typedef void (STDCALL* PsglMultiTexCoord3d)(GLenum, GLdouble, GLdouble,
    GLdouble);
typedef void (STDCALL* PsglMultiTexCoord3dv)(GLenum, const GLdouble*);
typedef void (STDCALL* PsglMultiTexCoord3f)(GLenum, GLfloat, GLfloat,
    GLfloat);
typedef void (STDCALL* PsglMultiTexCoord3fv)(GLenum, const GLfloat*);
typedef void (STDCALL* PsglMultiTexCoord3i)(GLenum, GLint, GLint, GLint);
typedef void (STDCALL* PsglMultiTexCoord3iv)(GLenum, const GLint*);
typedef void (STDCALL* PsglMultiTexCoord3s)(GLenum, GLshort, GLshort,
    GLshort);
typedef void (STDCALL* PsglMultiTexCoord3sv)(GLenum, const GLshort*);
typedef void (STDCALL* PsglMultiTexCoord4d)(GLenum, GLdouble, GLdouble,
    GLdouble, GLdouble);
typedef void (STDCALL* PsglMultiTexCoord4dv)(GLenum, const GLdouble*);
typedef void (STDCALL* PsglMultiTexCoord4f)(GLenum, GLfloat, GLfloat,
    GLfloat, GLfloat);
typedef void (STDCALL* PsglMultiTexCoord4fv)(GLenum, const GLfloat*);
typedef void (STDCALL* PsglMultiTexCoord4i)(GLenum, GLint, GLint, GLint,
    GLint);
typedef void (STDCALL* PsglMultiTexCoord4iv)(GLenum, const int*);
typedef void (STDCALL* PsglMultiTexCoord4s)(GLenum, GLshort, GLshort,
    GLshort, GLshort);
typedef void (STDCALL* PsglMultiTexCoord4sv)(GLenum, const GLshort*);
typedef void (STDCALL* PsglLoadTransposeMatrixd)(const GLdouble*);
typedef void (STDCALL* PsglLoadTransposeMatrixf)(const GLfloat*);
typedef void (STDCALL* PsglMultTransposeMatrixd)(const GLdouble*);
typedef void (STDCALL* PsglMultTransposeMatrixf)(const GLfloat*);
typedef void (STDCALL* PsglSampleCoverage)(GLclampf, GLboolean);
typedef void (STDCALL* PsglCompressedTexImage1D)(GLenum, GLint, GLenum,
    GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglCompressedTexImage2D)(GLenum, GLint, GLenum,
    GLsizei, GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglCompressedTexImage3D)(GLenum, GLint, GLenum,
    GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglCompressedTexSubImage1D)(GLenum, GLint, GLint,
    GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglCompressedTexSubImage2D)(GLenum, GLint, GLint,
    GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglCompressedTexSubImage3D)(GLenum, GLint, GLint,
    GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (STDCALL* PsglGetCompressedTexImage)(GLenum, GLint, GLvoid*);

static PsglActiveTexture sglActiveTexture = 0;
static PsglClientActiveTexture sglClientActiveTexture = 0;
static PsglMultiTexCoord1d sglMultiTexCoord1d = 0;
static PsglMultiTexCoord1dv sglMultiTexCoord1dv = 0;
static PsglMultiTexCoord1f sglMultiTexCoord1f = 0;
static PsglMultiTexCoord1fv sglMultiTexCoord1fv = 0;
static PsglMultiTexCoord1i sglMultiTexCoord1i = 0;
static PsglMultiTexCoord1iv sglMultiTexCoord1iv = 0;
static PsglMultiTexCoord1s sglMultiTexCoord1s = 0;
static PsglMultiTexCoord1sv sglMultiTexCoord1sv = 0;
static PsglMultiTexCoord2d sglMultiTexCoord2d = 0;
static PsglMultiTexCoord2dv sglMultiTexCoord2dv = 0;
static PsglMultiTexCoord2f sglMultiTexCoord2f = 0;
static PsglMultiTexCoord2fv sglMultiTexCoord2fv = 0;
static PsglMultiTexCoord2i sglMultiTexCoord2i = 0;
static PsglMultiTexCoord2iv sglMultiTexCoord2iv = 0;
static PsglMultiTexCoord2s sglMultiTexCoord2s = 0;
static PsglMultiTexCoord2sv sglMultiTexCoord2sv = 0;
static PsglMultiTexCoord3d sglMultiTexCoord3d = 0;
static PsglMultiTexCoord3dv sglMultiTexCoord3dv = 0;
static PsglMultiTexCoord3f sglMultiTexCoord3f = 0;
static PsglMultiTexCoord3fv sglMultiTexCoord3fv = 0;
static PsglMultiTexCoord3i sglMultiTexCoord3i = 0;
static PsglMultiTexCoord3iv sglMultiTexCoord3iv = 0;
static PsglMultiTexCoord3s sglMultiTexCoord3s = 0;
static PsglMultiTexCoord3sv sglMultiTexCoord3sv = 0;
static PsglMultiTexCoord4d sglMultiTexCoord4d = 0;
static PsglMultiTexCoord4dv sglMultiTexCoord4dv = 0;
static PsglMultiTexCoord4f sglMultiTexCoord4f = 0;
static PsglMultiTexCoord4fv sglMultiTexCoord4fv = 0;
static PsglMultiTexCoord4i sglMultiTexCoord4i = 0;
static PsglMultiTexCoord4iv sglMultiTexCoord4iv = 0;
static PsglMultiTexCoord4s sglMultiTexCoord4s = 0;
static PsglMultiTexCoord4sv sglMultiTexCoord4sv = 0;
static PsglLoadTransposeMatrixf sglLoadTransposeMatrixf = 0;
static PsglLoadTransposeMatrixd sglLoadTransposeMatrixd = 0;
static PsglMultTransposeMatrixf sglMultTransposeMatrixf = 0;
static PsglMultTransposeMatrixd sglMultTransposeMatrixd = 0;
static PsglSampleCoverage sglSampleCoverage = 0;
static PsglCompressedTexImage3D sglCompressedTexImage3D = 0;
static PsglCompressedTexImage2D sglCompressedTexImage2D = 0;
static PsglCompressedTexImage1D sglCompressedTexImage1D = 0;
static PsglCompressedTexSubImage3D sglCompressedTexSubImage3D = 0;
static PsglCompressedTexSubImage2D sglCompressedTexSubImage2D = 0;
static PsglCompressedTexSubImage1D sglCompressedTexSubImage1D = 0;
static PsglGetCompressedTexImage sglGetCompressedTexImage = 0;
/*--------------------------------------------------------------------------*/
void SE_glActiveTexture(GLenum eTexture)
{
    SE_BODY_A1(sglActiveTexture, eTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glClientActiveTexture(GLenum eTexture)
{
    SE_BODY_A1(sglClientActiveTexture, eTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1d(GLenum eTarget, GLdouble dS)
{
    SE_BODY_A2(sglMultiTexCoord1d, eTarget, dS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1dv(GLenum eTarget, const GLdouble* pdS)
{
    SE_BODY_A2(sglMultiTexCoord1dv, eTarget, pdS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1f(GLenum eTarget, GLfloat fS)
{
    SE_BODY_A2(sglMultiTexCoord1f, eTarget, fS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1fv(GLenum eTarget, const GLfloat* pfS)
{
    SE_BODY_A2(sglMultiTexCoord1fv, eTarget, pfS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1i(GLenum eTarget, GLint iS)
{
    SE_BODY_A2(sglMultiTexCoord1i, eTarget, iS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1iv(GLenum eTarget, const GLint* piS)
{
    SE_BODY_A2(sglMultiTexCoord1iv, eTarget, piS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1s(GLenum eTarget, GLshort sS)
{
    SE_BODY_A2(sglMultiTexCoord1s, eTarget, sS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1sv(GLenum eTarget, const GLshort* psS)
{
    SE_BODY_A2(sglMultiTexCoord1sv, eTarget, psS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2d(GLenum eTarget, GLdouble dS, GLdouble dT)
{
    SE_BODY_A3(sglMultiTexCoord2d, eTarget, dS, dT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2dv(GLenum eTarget, const GLdouble* adST)
{
    SE_BODY_A2(sglMultiTexCoord2dv, eTarget, adST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2f(GLenum eTarget, GLfloat fS, GLfloat fT)
{
    SE_BODY_A3(sglMultiTexCoord2f, eTarget, fS, fT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2fv(GLenum eTarget, const GLfloat* afST)
{
    SE_BODY_A2(sglMultiTexCoord2fv, eTarget, afST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2i(GLenum eTarget, GLint iS, GLint iT)
{
    SE_BODY_A3(sglMultiTexCoord2i, eTarget, iS, iT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2iv(GLenum eTarget, const GLint* aiST)
{
    SE_BODY_A2(sglMultiTexCoord2iv, eTarget, aiST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2s(GLenum eTarget, GLshort sS, GLshort sT)
{
    SE_BODY_A3(sglMultiTexCoord2s, eTarget, sS, sT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2sv(GLenum eTarget, const GLshort* asST)
{
    SE_BODY_A2(sglMultiTexCoord2sv, eTarget, asST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3d(GLenum eTarget, GLdouble dS, GLdouble dT, 
    GLdouble dR)
{
    SE_BODY_A4(sglMultiTexCoord3d, eTarget, dS, dT, dR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3dv(GLenum eTarget, const GLdouble* adSTR)
{
    SE_BODY_A2(sglMultiTexCoord3dv, eTarget, adSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3f(GLenum eTarget, GLfloat fS, GLfloat fT, GLfloat fR)
{
    SE_BODY_A4(sglMultiTexCoord3f, eTarget, fS, fT, fR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3fv(GLenum eTarget, const GLfloat* afSTR)
{
    SE_BODY_A2(sglMultiTexCoord3fv, eTarget, afSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3i(GLenum eTarget, GLint iS, GLint iT, GLint iR)
{
    SE_BODY_A4(sglMultiTexCoord3i, eTarget, iS, iT, iR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3iv(GLenum eTarget, const GLint* aiSTR)
{
    SE_BODY_A2(sglMultiTexCoord3iv, eTarget, aiSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3s(GLenum eTarget, GLshort sS, GLshort sT, GLshort sR)
{
    SE_BODY_A4(sglMultiTexCoord3s, eTarget, sS, sT, sR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3sv(GLenum eTarget, const GLshort* asSTR)
{
    SE_BODY_A2(sglMultiTexCoord3sv, eTarget, asSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4d(GLenum eTarget, GLdouble dS, GLdouble dT, 
    GLdouble dR, GLdouble dQ)
{
    SE_BODY_A5(sglMultiTexCoord4d, eTarget, dS, dT, dR, dQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4dv(GLenum eTarget, const GLdouble* adSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4dv, eTarget, adSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4f(GLenum eTarget, GLfloat fS, GLfloat fT, GLfloat fR, 
    GLfloat fQ)
{
    SE_BODY_A5(sglMultiTexCoord4f, eTarget, fS, fT, fR, fQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4fv(GLenum eTarget, const GLfloat* afSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4fv, eTarget, afSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4i(GLenum eTarget, GLint iS, GLint iT, GLint iR, 
    GLint iQ)
{
    SE_BODY_A5(sglMultiTexCoord4i, eTarget, iS, iT, iR, iQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4iv(GLenum eTarget, const GLint* aiSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4iv, eTarget, aiSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4s(GLenum eTarget, GLshort sS, GLshort sT, GLshort sR, 
    GLshort sQ)
{
    SE_BODY_A5(sglMultiTexCoord4s, eTarget, sS, sT, sR, sQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4sv(GLenum eTarget, const GLshort* asSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4sv, eTarget, asSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadTransposeMatrixd(const GLdouble* adMatrix)
{
    SE_BODY_A1(sglLoadTransposeMatrixd, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadTransposeMatrixf(const GLfloat* afMatrix)
{
    SE_BODY_A1(sglLoadTransposeMatrixf, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glMultTransposeMatrixd(const GLdouble* adMatrix)
{
    SE_BODY_A1(sglMultTransposeMatrixd, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glMultTransposeMatrixf(const GLfloat* afMatrix)
{
    SE_BODY_A1(sglMultTransposeMatrixf, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glSampleCoverage(GLclampf fValue, GLboolean ucInvert)
{
    SE_BODY_A2(sglSampleCoverage, fValue, ucInvert);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage1D(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLint iBorder, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A7(sglCompressedTexImage1D, eTarget, iLevel, eInternalFormat, iWidth, 
        iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage2D(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLint iBorder, 
    GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A8(sglCompressedTexImage2D, eTarget, iLevel, eInternalFormat, iWidth, 
        iHeight, iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage3D(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth, 
    GLint iBorder, GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A9(sglCompressedTexImage3D, eTarget, iLevel, eInternalFormat, iWidth, 
        iHeight, iDepth, iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage1D(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A7(sglCompressedTexSubImage1D, eTarget, iLevel, iXOffset, iWidth, 
        eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage2D(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight, 
    GLenum eFormat, GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A9(sglCompressedTexSubImage2D, eTarget, iLevel, iXOffset, iYOffset, 
        iWidth, iHeight, eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage3D(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth, 
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A11(sglCompressedTexSubImage3D, eTarget, iLevel, iXOffset, iYOffset, 
        iZOffset, iWidth, iHeight, iDepth, eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glGetCompressedTexImage(GLenum eTarget, GLint iLevel, GLvoid* pvData)
{
    SE_BODY_A3(sglGetCompressedTexImage, eTarget, iLevel, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_InitOpenGL13()
{
    if( SE_GL_GetVersion() >= SE_GL_VERSION_1_3 )
    {
        SE_ExistsOpenGL13 = 1;

        /* GL_ARB_multisample */
        SE_GET_FUNCTION(sglSampleCoverage);

        /* GL_ARB_multitexture */
        SE_GET_FUNCTION(sglActiveTexture);
        SE_GET_FUNCTION(sglClientActiveTexture);
        SE_GET_FUNCTION(sglMultiTexCoord1d);
        SE_GET_FUNCTION(sglMultiTexCoord1dv);
        SE_GET_FUNCTION(sglMultiTexCoord1f);
        SE_GET_FUNCTION(sglMultiTexCoord1fv);
        SE_GET_FUNCTION(sglMultiTexCoord1i);
        SE_GET_FUNCTION(sglMultiTexCoord1iv);
        SE_GET_FUNCTION(sglMultiTexCoord1s);
        SE_GET_FUNCTION(sglMultiTexCoord1sv);
        SE_GET_FUNCTION(sglMultiTexCoord2d);
        SE_GET_FUNCTION(sglMultiTexCoord2dv);
        SE_GET_FUNCTION(sglMultiTexCoord2f);
        SE_GET_FUNCTION(sglMultiTexCoord2fv);
        SE_GET_FUNCTION(sglMultiTexCoord2i);
        SE_GET_FUNCTION(sglMultiTexCoord2iv);
        SE_GET_FUNCTION(sglMultiTexCoord2s);
        SE_GET_FUNCTION(sglMultiTexCoord2sv);
        SE_GET_FUNCTION(sglMultiTexCoord3d);
        SE_GET_FUNCTION(sglMultiTexCoord3dv);
        SE_GET_FUNCTION(sglMultiTexCoord3f);
        SE_GET_FUNCTION(sglMultiTexCoord3fv);
        SE_GET_FUNCTION(sglMultiTexCoord3i);
        SE_GET_FUNCTION(sglMultiTexCoord3iv);
        SE_GET_FUNCTION(sglMultiTexCoord3s);
        SE_GET_FUNCTION(sglMultiTexCoord3sv);
        SE_GET_FUNCTION(sglMultiTexCoord4d);
        SE_GET_FUNCTION(sglMultiTexCoord4dv);
        SE_GET_FUNCTION(sglMultiTexCoord4f);
        SE_GET_FUNCTION(sglMultiTexCoord4fv);
        SE_GET_FUNCTION(sglMultiTexCoord4i);
        SE_GET_FUNCTION(sglMultiTexCoord4iv);
        SE_GET_FUNCTION(sglMultiTexCoord4s);
        SE_GET_FUNCTION(sglMultiTexCoord4sv);

        /* GL_ARB_texture_compression */
        SE_GET_FUNCTION(sglCompressedTexImage3D);
        SE_GET_FUNCTION(sglCompressedTexImage2D);
        SE_GET_FUNCTION(sglCompressedTexImage1D);
        SE_GET_FUNCTION(sglCompressedTexSubImage3D);
        SE_GET_FUNCTION(sglCompressedTexSubImage2D);
        SE_GET_FUNCTION(sglCompressedTexSubImage1D);
        SE_GET_FUNCTION(sglGetCompressedTexImage);

        /* GL_ARB_transpose_matrix */
        SE_GET_FUNCTION(sglLoadTransposeMatrixf);
        SE_GET_FUNCTION(sglLoadTransposeMatrixd);
        SE_GET_FUNCTION(sglMultTransposeMatrixf);
        SE_GET_FUNCTION(sglMultTransposeMatrixd);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.4 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL14 = 0;

typedef void (STDCALL* PsglBlendFuncSeparate)(GLenum, GLenum, GLenum,
    GLenum);
typedef void (STDCALL* PsglFogCoordd)(GLdouble);
typedef void (STDCALL* PsglFogCoorddv)(const GLdouble*);
typedef void (STDCALL* PsglFogCoordf)(GLfloat);
typedef void (STDCALL* PsglFogCoordfv)(const GLfloat*);
typedef void (STDCALL* PsglFogCoordPointer)(GLenum, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglMultiDrawArrays)(GLenum, GLint*, GLsizei*,
    GLsizei);
typedef void (STDCALL* PsglMultiDrawElements)(GLenum, const GLsizei*,
    GLenum, const GLvoid**, GLsizei);
typedef void (STDCALL* PsglPointParameterf)(GLenum, GLfloat);
typedef void (STDCALL* PsglPointParameterfv)(GLenum, const GLfloat*);
typedef void (STDCALL* PsglPointParameteri)(GLenum, GLint);
typedef void (STDCALL* PsglPointParameteriv)(GLenum, const GLint*);
typedef void (STDCALL* PsglSecondaryColor3b)(GLbyte, GLbyte, GLbyte);
typedef void (STDCALL* PsglSecondaryColor3bv)(const GLbyte*);
typedef void (STDCALL* PsglSecondaryColor3d)(GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglSecondaryColor3dv)(const GLdouble*);
typedef void (STDCALL* PsglSecondaryColor3f)(GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglSecondaryColor3fv)(const GLfloat*);
typedef void (STDCALL* PsglSecondaryColor3i)(GLint, GLint, GLint);
typedef void (STDCALL* PsglSecondaryColor3iv)(const GLint*);
typedef void (STDCALL* PsglSecondaryColor3s)(GLshort, GLshort, GLshort);
typedef void (STDCALL* PsglSecondaryColor3sv)(const GLshort*);
typedef void (STDCALL* PsglSecondaryColor3ub)(GLubyte, GLubyte, GLubyte);
typedef void (STDCALL* PsglSecondaryColor3ubv)(const GLubyte*);
typedef void (STDCALL* PsglSecondaryColor3ui)(GLuint, GLuint, GLuint);
typedef void (STDCALL* PsglSecondaryColor3uiv)(const GLuint*);
typedef void (STDCALL* PsglSecondaryColor3us)(GLushort, GLushort,
    GLushort);
typedef void (STDCALL* PsglSecondaryColor3usv)(const GLushort*);
typedef void (STDCALL* PsglSecondaryColorPointer)(GLint, GLenum, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglWindowPos2d)(GLdouble, GLdouble);
typedef void (STDCALL* PsglWindowPos2dv)(const GLdouble*);
typedef void (STDCALL* PsglWindowPos2f)(GLfloat, GLfloat);
typedef void (STDCALL* PsglWindowPos2fv)(const GLfloat*);
typedef void (STDCALL* PsglWindowPos2i)(GLint, GLint);
typedef void (STDCALL* PsglWindowPos2iv)(const GLint*);
typedef void (STDCALL* PsglWindowPos2s)(GLshort, GLshort);
typedef void (STDCALL* PsglWindowPos2sv)(const GLshort*);
typedef void (STDCALL* PsglWindowPos3d)(GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglWindowPos3dv)(const GLdouble*);
typedef void (STDCALL* PsglWindowPos3f)(GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglWindowPos3fv)(const GLfloat*);
typedef void (STDCALL* PsglWindowPos3i)(GLint, GLint, GLint);
typedef void (STDCALL* PsglWindowPos3iv)(const GLint*);
typedef void (STDCALL* PsglWindowPos3s)(GLshort, GLshort, GLshort);
typedef void (STDCALL* PsglWindowPos3sv)(const GLshort*);

static PsglBlendFuncSeparate sglBlendFuncSeparate = 0;
static PsglFogCoordf sglFogCoordf = 0;
static PsglFogCoordfv sglFogCoordfv = 0;
static PsglFogCoordd sglFogCoordd = 0;
static PsglFogCoorddv sglFogCoorddv = 0;
static PsglFogCoordPointer sglFogCoordPointer = 0;
static PsglMultiDrawArrays sglMultiDrawArrays = 0;
static PsglMultiDrawElements sglMultiDrawElements = 0;
static PsglPointParameterf sglPointParameterf = 0;
static PsglPointParameterfv sglPointParameterfv = 0;
static PsglPointParameteri sglPointParameteri = 0;
static PsglPointParameteriv sglPointParameteriv = 0;
static PsglSecondaryColor3b sglSecondaryColor3b = 0;
static PsglSecondaryColor3bv sglSecondaryColor3bv = 0;
static PsglSecondaryColor3d sglSecondaryColor3d = 0;
static PsglSecondaryColor3dv sglSecondaryColor3dv = 0;
static PsglSecondaryColor3f sglSecondaryColor3f = 0;
static PsglSecondaryColor3fv sglSecondaryColor3fv = 0;
static PsglSecondaryColor3i sglSecondaryColor3i = 0;
static PsglSecondaryColor3iv sglSecondaryColor3iv = 0;
static PsglSecondaryColor3s sglSecondaryColor3s = 0;
static PsglSecondaryColor3sv sglSecondaryColor3sv = 0;
static PsglSecondaryColor3ub sglSecondaryColor3ub = 0;
static PsglSecondaryColor3ubv sglSecondaryColor3ubv = 0;
static PsglSecondaryColor3ui sglSecondaryColor3ui = 0;
static PsglSecondaryColor3uiv sglSecondaryColor3uiv = 0;
static PsglSecondaryColor3us sglSecondaryColor3us = 0;
static PsglSecondaryColor3usv sglSecondaryColor3usv = 0;
static PsglSecondaryColorPointer sglSecondaryColorPointer = 0;
static PsglWindowPos2d sglWindowPos2d = 0;
static PsglWindowPos2dv sglWindowPos2dv = 0;
static PsglWindowPos2f sglWindowPos2f = 0;
static PsglWindowPos2fv sglWindowPos2fv = 0;
static PsglWindowPos2i sglWindowPos2i = 0;
static PsglWindowPos2iv sglWindowPos2iv = 0;
static PsglWindowPos2s sglWindowPos2s = 0;
static PsglWindowPos2sv sglWindowPos2sv = 0;
static PsglWindowPos3d sglWindowPos3d = 0;
static PsglWindowPos3dv sglWindowPos3dv = 0;
static PsglWindowPos3f sglWindowPos3f = 0;
static PsglWindowPos3fv sglWindowPos3fv = 0;
static PsglWindowPos3i sglWindowPos3i = 0;
static PsglWindowPos3iv sglWindowPos3iv = 0;
static PsglWindowPos3s sglWindowPos3s = 0;
static PsglWindowPos3sv sglWindowPos3sv = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendFuncSeparate(GLenum eSrcFactorRGB, GLenum eDstFactorRGB, 
    GLenum eSrcFactorA, GLenum eDstFactorA)
{
    SE_BODY_A4(sglBlendFuncSeparate, eSrcFactorRGB, eDstFactorRGB, eSrcFactorA, 
        eDstFactorA);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordd(GLdouble dCoord)
{
    SE_BODY_A1(sglFogCoordd, dCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoorddv(const GLdouble* pdCoord)
{
    SE_BODY_A1(sglFogCoorddv, pdCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordf(GLfloat fCoord)
{
    SE_BODY_A1(sglFogCoordf, fCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordfv(const GLfloat* pfCoord)
{
    SE_BODY_A1(sglFogCoordfv, pfCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordPointer(GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A3(sglFogCoordPointer, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiDrawArrays(GLenum eMode, GLint* aiFirst, GLsizei* aiCount, 
    GLsizei iPrimitiveCount)
{
    SE_BODY_A4(sglMultiDrawArrays, eMode, aiFirst, aiCount, iPrimitiveCount);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiDrawElements(GLenum eMode, const GLsizei* aiCount, 
    GLenum eType, const GLvoid** apvIndices, GLsizei iPrimitiveCount)
{
    SE_BODY_A5(sglMultiDrawElements, eMode, aiCount, eType, apvIndices, 
        iPrimitiveCount);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameterf(GLenum ePName, GLfloat fParam)
{
    SE_BODY_A2(sglPointParameterf, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameterfv(GLenum ePName, const GLfloat* afParam)
{
    SE_BODY_A2(sglPointParameterfv, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameteri(GLenum ePName, int iParam)
{
    SE_BODY_A2(sglPointParameteri, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameteriv(GLenum ePName, const int* aiParam)
{
    SE_BODY_A2(sglPointParameteriv, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3b(GLbyte cRed, GLbyte cGreen, GLbyte cBlue)
{
    SE_BODY_A3(sglSecondaryColor3b, cRed, cGreen, cBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3bv(const GLbyte* acRGB)
{
    SE_BODY_A1(sglSecondaryColor3bv, acRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3d(GLdouble dRed, GLdouble dGreen, GLdouble dBlue)
{
    SE_BODY_A3(sglSecondaryColor3d, dRed, dGreen, dBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3dv(const GLdouble* adRGB)
{
    SE_BODY_A1(sglSecondaryColor3dv, adRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3f(GLfloat fRed, GLfloat fGreen, GLfloat fBlue)
{
    SE_BODY_A3(sglSecondaryColor3f, fRed, fGreen, fBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3fv(const GLfloat* afRGB)
{
    SE_BODY_A1(sglSecondaryColor3fv, afRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3i(GLint iRed, GLint iGreen, GLint iBlue)
{
    SE_BODY_A3(sglSecondaryColor3i, iRed, iGreen, iBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3iv(const GLint* aiRGB)
{
    SE_BODY_A1(sglSecondaryColor3iv, aiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3s(GLshort sRed, GLshort sGreen, GLshort sBlue)
{
    SE_BODY_A3(sglSecondaryColor3s, sRed, sGreen, sBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3sv(const GLshort* asRGB)
{
    SE_BODY_A1(sglSecondaryColor3sv, asRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ub(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue)
{
    SE_BODY_A3(sglSecondaryColor3ub, ucRed, ucGreen, ucBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ubv(const GLubyte* aucRGB)
{
    SE_BODY_A1(sglSecondaryColor3ubv, aucRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ui(GLuint uiRed, GLuint uiGreen, GLuint uiBlue)
{
    SE_BODY_A3(sglSecondaryColor3ui, uiRed, uiGreen, uiBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3uiv(const GLuint* auiRGB)
{
    SE_BODY_A1(sglSecondaryColor3uiv, auiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3us(GLushort usRed, GLushort usGreen, GLushort usBlue)
{
    SE_BODY_A3(sglSecondaryColor3us, usRed, usGreen, usBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3usv(const GLushort* ausRGB)
{
    SE_BODY_A1(sglSecondaryColor3usv, ausRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColorPointer(GLint iSize, GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglSecondaryColorPointer, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2d(GLdouble dX, GLdouble dY)
{
    SE_BODY_A2(sglWindowPos2d, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2dv(const GLdouble* adXY)
{
    SE_BODY_A1(sglWindowPos2dv, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2f(GLfloat fX, GLfloat fY)
{
    SE_BODY_A2(sglWindowPos2f, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2fv(const GLfloat* afXY)
{
    SE_BODY_A1(sglWindowPos2fv, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2i(GLint iX, GLint iY)
{
    SE_BODY_A2(sglWindowPos2i, iX, iY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2iv(const GLint* aiXY)
{
    SE_BODY_A1(sglWindowPos2iv, aiXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2s(GLshort sX, GLshort sY)
{
    SE_BODY_A2(sglWindowPos2s, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2sv(const GLshort* asXY)
{
    SE_BODY_A1(sglWindowPos2sv, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3d(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_BODY_A3(sglWindowPos3d, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3dv(const GLdouble* adXYZ)
{
    SE_BODY_A1(sglWindowPos3dv, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3f(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_BODY_A3(sglWindowPos3f, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3fv(const GLfloat* afXYZ)
{
    SE_BODY_A1(sglWindowPos3fv, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3i(GLint iX, GLint iY, GLint iZ)
{
    SE_BODY_A3(sglWindowPos3i, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3iv(const GLint* aiXYZ)
{
    SE_BODY_A1(sglWindowPos3iv, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3s(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_BODY_A3(sglWindowPos3s, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3sv(const GLshort* asXYZ)
{
    SE_BODY_A1(sglWindowPos3sv, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_InitOpenGL14()
{
    if( SE_GL_GetVersion() >= SE_GL_VERSION_1_4 )
    {
        SE_ExistsOpenGL14 = 1;

        /* GL_{EXT,INGR}_blend_func_separate */
        SE_GET_FUNCTION(sglBlendFuncSeparate);

        /* GL_EXT_fog_coord */
        SE_GET_FUNCTION(sglFogCoordf);
        SE_GET_FUNCTION(sglFogCoordfv);
        SE_GET_FUNCTION(sglFogCoordd);
        SE_GET_FUNCTION(sglFogCoorddv);
        SE_GET_FUNCTION(sglFogCoordPointer);

        /* GL_EXT_multi_draw_arrays */
        SE_GET_FUNCTION(sglMultiDrawArrays);
        SE_GET_FUNCTION(sglMultiDrawElements);

        /* GL_{ARB,EXT,SGIS}_point_parameters */
        SE_GET_FUNCTION(sglPointParameterf);
        SE_GET_FUNCTION(sglPointParameterfv);

        /* GL_NV_point_sprite */
        SE_GET_FUNCTION(sglPointParameteri);
        SE_GET_FUNCTION(sglPointParameteriv);

        /* GL_EXT_secondary_color */
        SE_GET_FUNCTION(sglSecondaryColor3b);
        SE_GET_FUNCTION(sglSecondaryColor3bv);
        SE_GET_FUNCTION(sglSecondaryColor3d);
        SE_GET_FUNCTION(sglSecondaryColor3dv);
        SE_GET_FUNCTION(sglSecondaryColor3f);
        SE_GET_FUNCTION(sglSecondaryColor3fv);
        SE_GET_FUNCTION(sglSecondaryColor3i);
        SE_GET_FUNCTION(sglSecondaryColor3iv);
        SE_GET_FUNCTION(sglSecondaryColor3s);
        SE_GET_FUNCTION(sglSecondaryColor3sv);
        SE_GET_FUNCTION(sglSecondaryColor3ub);
        SE_GET_FUNCTION(sglSecondaryColor3ubv);
        SE_GET_FUNCTION(sglSecondaryColor3ui);
        SE_GET_FUNCTION(sglSecondaryColor3uiv);
        SE_GET_FUNCTION(sglSecondaryColor3us);
        SE_GET_FUNCTION(sglSecondaryColor3usv);
        SE_GET_FUNCTION(sglSecondaryColorPointer);

        /* GL_{ARB,MESA}_window_pos */
        SE_GET_FUNCTION(sglWindowPos2d);
        SE_GET_FUNCTION(sglWindowPos2dv);
        SE_GET_FUNCTION(sglWindowPos2f);
        SE_GET_FUNCTION(sglWindowPos2fv);
        SE_GET_FUNCTION(sglWindowPos2i);
        SE_GET_FUNCTION(sglWindowPos2iv);
        SE_GET_FUNCTION(sglWindowPos2s);
        SE_GET_FUNCTION(sglWindowPos2sv);
        SE_GET_FUNCTION(sglWindowPos3d);
        SE_GET_FUNCTION(sglWindowPos3dv);
        SE_GET_FUNCTION(sglWindowPos3f);
        SE_GET_FUNCTION(sglWindowPos3fv);
        SE_GET_FUNCTION(sglWindowPos3i);
        SE_GET_FUNCTION(sglWindowPos3iv);
        SE_GET_FUNCTION(sglWindowPos3s);
        SE_GET_FUNCTION(sglWindowPos3sv);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.5 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL15 = 0;

typedef void (STDCALL* PsglGenQueries)(GLsizei, GLuint*);
typedef void (STDCALL* PsglDeleteQueries)(GLsizei, const GLuint*);
typedef unsigned char (STDCALL* PsglIsQuery)(GLuint);
typedef void (STDCALL* PsglBeginQuery)(GLenum, GLuint);
typedef void (STDCALL* PsglEndQuery)(GLenum);
typedef void (STDCALL* PsglGetQueryiv)(GLenum, GLenum, GLint*);
typedef void (STDCALL* PsglGetQueryObjectiv)(GLuint, GLenum, GLint*);
typedef void (STDCALL* PsglGetQueryObjectuiv)(GLuint, GLenum, GLuint*);
typedef void (STDCALL* PsglBindBuffer)(GLenum, GLuint);
typedef void (STDCALL* PsglDeleteBuffers)(GLsizei, const GLuint*);
typedef void (STDCALL* PsglGenBuffers)(GLsizei, GLuint*);
typedef unsigned char (STDCALL* PsglIsBuffer)(GLuint);
typedef void (STDCALL* PsglBufferData)(GLenum, GLsizeiptr, const GLvoid*,
    GLenum);
typedef void (STDCALL* PsglBufferSubData)(GLenum, GLintptr, GLsizeiptr,
    const GLvoid*);
typedef void (STDCALL* PsglGetBufferSubData)(GLenum, GLintptr, GLsizeiptr,
    GLvoid*);
typedef void* (STDCALL* PsglMapBuffer)(GLenum, GLenum);
typedef unsigned char (STDCALL* PsglUnmapBuffer)(GLenum);
typedef void (STDCALL* PsglGetBufferParameteriv)(GLenum, GLenum, GLint*);
typedef void (STDCALL* PsglGetBufferPointerv)(GLenum, GLenum, GLvoid**);

static PsglGenQueries sglGenQueries = 0;
static PsglDeleteQueries sglDeleteQueries = 0;
static PsglIsQuery sglIsQuery = 0;
static PsglBeginQuery sglBeginQuery = 0;
static PsglEndQuery sglEndQuery = 0;
static PsglGetQueryiv sglGetQueryiv = 0;
static PsglGetQueryObjectiv sglGetQueryObjectiv = 0;
static PsglGetQueryObjectuiv sglGetQueryObjectuiv = 0;
static PsglBindBuffer sglBindBuffer = 0;
static PsglDeleteBuffers sglDeleteBuffers = 0;
static PsglGenBuffers sglGenBuffers = 0;
static PsglIsBuffer sglIsBuffer = 0;
static PsglBufferData sglBufferData = 0;
static PsglBufferSubData sglBufferSubData = 0;
static PsglGetBufferSubData sglGetBufferSubData = 0;
static PsglMapBuffer sglMapBuffer = 0;
static PsglUnmapBuffer sglUnmapBuffer = 0;
static PsglGetBufferParameteriv sglGetBufferParameteriv = 0;
static PsglGetBufferPointerv sglGetBufferPointerv = 0;
/*--------------------------------------------------------------------------*/
void SE_glGenQueries(GLsizei iNumQueries, GLuint* auiID)
{
    SE_BODY_A2(sglGenQueries, iNumQueries, auiID);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteQueries(GLsizei iNumQueries, const GLuint* auiID)
{
    SE_BODY_A2(sglDeleteQueries, iNumQueries, auiID);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsQuery(GLuint uiID)
{
    SE_BODY_A1_RET(sglIsQuery, uiID, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBeginQuery(GLenum eTarget, GLuint uiID)
{
    SE_BODY_A2(sglBeginQuery, eTarget, uiID);
}
/*--------------------------------------------------------------------------*/
void SE_glEndQuery(GLenum eTarget)
{
    SE_BODY_A1(sglEndQuery, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryiv(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetQueryiv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryObjectiv(GLuint uiID, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetQueryObjectiv, uiID, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryObjectuiv(GLuint uiID, GLenum ePName, GLuint* auiParam)
{
    SE_BODY_A3(sglGetQueryObjectuiv, uiID, ePName, auiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glBindBuffer(GLenum eTarget, GLuint uiBuffer)
{
    SE_BODY_A2(sglBindBuffer, eTarget, uiBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteBuffers(GLsizei iNumBuffers, const GLuint* auiBuffer)
{
    SE_BODY_A2(sglDeleteBuffers, iNumBuffers, auiBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glGenBuffers(GLsizei iNumBuffers, GLuint* auiBuffer)
{
    SE_BODY_A2(sglGenBuffers, iNumBuffers, auiBuffer);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsBuffer(GLuint uiBuffer)
{
    SE_BODY_A1_RET(sglIsBuffer, uiBuffer, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBufferData(GLenum eTarget, GLsizeiptr piSize, const GLvoid* pvData, 
    GLenum eUsage)
{
    SE_BODY_A4(sglBufferData, eTarget, piSize, pvData, eUsage);
}
/*--------------------------------------------------------------------------*/
void SE_glBufferSubData(GLenum eTarget, GLintptr piOffset, GLsizeiptr piSize, 
    const GLvoid* pvData)
{
    SE_BODY_A4(sglBufferSubData, eTarget, piOffset, piSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferSubData(GLenum eTarget, GLintptr piOffset, 
    GLsizeiptr piSize, GLvoid* pvData)
{
    SE_BODY_A4(sglGetBufferSubData, eTarget, piOffset, piSize, pvData);
}
/*--------------------------------------------------------------------------*/
GLvoid* SE_glMapBuffer(GLenum eTarget, GLenum eAccess)
{
    SE_BODY_A2_RET(sglMapBuffer, eTarget, eAccess, GLvoid*, 0);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glUnmapBuffer(GLenum eTarget)
{
    SE_BODY_A1_RET(sglUnmapBuffer, eTarget, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferParameteriv(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetBufferParameteriv, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferPointerv(GLenum eTarget, GLenum ePName, GLvoid** apvParam)
{
    SE_BODY_A3(sglGetBufferPointerv, eTarget, ePName, apvParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitOpenGL15()
{
    if( SE_GL_GetVersion() >= SE_GL_VERSION_1_5 )
    {
        SE_ExistsOpenGL15 = 1;

        /* GL_ARB_occlusion_query */
        SE_GET_FUNCTION(sglGenQueries);
        SE_GET_FUNCTION(sglDeleteQueries);
        SE_GET_FUNCTION(sglIsQuery);
        SE_GET_FUNCTION(sglBeginQuery);
        SE_GET_FUNCTION(sglEndQuery);
        SE_GET_FUNCTION(sglGetQueryiv);
        SE_GET_FUNCTION(sglGetQueryObjectiv);
        SE_GET_FUNCTION(sglGetQueryObjectuiv);

        /* GL_ARB_vertex_buffer_object */
        SE_GET_FUNCTION(sglBindBuffer);
        SE_GET_FUNCTION(sglDeleteBuffers);
        SE_GET_FUNCTION(sglGenBuffers);
        SE_GET_FUNCTION(sglIsBuffer);
        SE_GET_FUNCTION(sglBufferData);
        SE_GET_FUNCTION(sglBufferSubData);
        SE_GET_FUNCTION(sglGetBufferSubData);
        SE_GET_FUNCTION(sglMapBuffer);
        SE_GET_FUNCTION(sglUnmapBuffer);
        SE_GET_FUNCTION(sglGetBufferParameteriv);
        SE_GET_FUNCTION(sglGetBufferPointerv);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 2.0 */
/*--------------------------------------------------------------------------*/
int SE_ExistsOpenGL20 = 0;

typedef void (STDCALL* PsglBlendEquationSeparate)(GLenum, GLenum);
typedef void (STDCALL* PsglDrawBuffers)(GLsizei, const GLenum*);
typedef void (STDCALL* PsglStencilOpSeparate)(GLenum, GLenum, GLenum,
    GLenum);
typedef void (STDCALL* PsglStencilFuncSeparate)(GLenum, GLenum, GLint,
    GLuint);
typedef void (STDCALL* PsglStencilMaskSeparate)(GLenum, GLuint);
typedef void (STDCALL* PsglAttachShader)(GLuint, GLuint);
typedef void (STDCALL* PsglBindAttribLocation)(GLuint, GLuint,
    const GLchar*);
typedef void (STDCALL* PsglCompileShader)(GLuint);
typedef GLuint (STDCALL* PsglCreateProgram)(void);
typedef GLuint (STDCALL* PsglCreateShader)(GLenum);
typedef void (STDCALL* PsglDeleteProgram)(GLuint);
typedef void (STDCALL* PsglDeleteShader)(GLuint);
typedef void (STDCALL* PsglDetachShader)(GLuint, GLuint);
typedef void (STDCALL* PsglDisableVertexAttribArray)(GLuint);
typedef void (STDCALL* PsglEnableVertexAttribArray)(GLuint);
typedef void (STDCALL* PsglGetActiveAttrib)(GLuint, GLuint, GLsizei,
    GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (STDCALL* PsglGetActiveUniform)(GLuint, GLuint, GLsizei,
    GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (STDCALL* PsglGetAttachedShaders)(GLuint, GLsizei, GLsizei*,
    GLuint*);
typedef GLint (STDCALL* PsglGetAttribLocation)(GLuint, const GLchar*);
typedef void (STDCALL* PsglGetProgramiv)(GLuint, GLenum, GLint*);
typedef void (STDCALL* PsglGetProgramInfoLog)(GLuint, GLsizei, GLsizei*,
    GLchar*);
typedef void (STDCALL* PsglGetShaderiv)(GLuint, GLenum, GLint*);
typedef void (STDCALL* PsglGetShaderInfoLog)(GLuint, GLsizei, GLsizei*,
    GLchar*);
typedef void (STDCALL* PsglGetShaderSource)(GLuint, GLsizei, GLsizei*,
    GLchar*);
typedef GLint (STDCALL* PsglGetUniformLocation)(GLuint, const GLchar*);
typedef void (STDCALL* PsglGetUniformfv)(GLuint, GLint, GLfloat*);
typedef void (STDCALL* PsglGetUniformiv)(GLuint, GLint, GLint*);
typedef void (STDCALL* PsglGetVertexAttribdv)(GLuint, GLenum, GLdouble*);
typedef void (STDCALL* PsglGetVertexAttribfv)(GLuint, GLenum, GLfloat*);
typedef void (STDCALL* PsglGetVertexAttribiv)(GLuint, GLenum, GLint*);
typedef void (STDCALL* PsglGetVertexAttribPointerv)(GLuint, GLenum,
    GLvoid**);
typedef GLboolean (STDCALL* PsglIsProgram)(GLuint);
typedef GLboolean (STDCALL* PsglIsShader)(GLuint);
typedef void (STDCALL* PsglLinkProgram)(GLuint);
typedef void (STDCALL* PsglShaderSource)(GLuint, GLsizei, const GLchar**,
    const GLint*);
typedef void (STDCALL* PsglUseProgram)(GLuint);
typedef void (STDCALL* PsglUniform1f)(GLint, GLfloat);
typedef void (STDCALL* PsglUniform2f)(GLint, GLfloat, GLfloat);
typedef void (STDCALL* PsglUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglUniform4f)(GLint, GLfloat, GLfloat, GLfloat,
    GLfloat);
typedef void (STDCALL* PsglUniform1i)(GLint, GLint);
typedef void (STDCALL* PsglUniform2i)(GLint, GLint, GLint);
typedef void (STDCALL* PsglUniform3i)(GLint, GLint, GLint, GLint);
typedef void (STDCALL* PsglUniform4i)(GLint, GLint, GLint, GLint, GLint);
typedef void (STDCALL* PsglUniform1fv)(GLint, GLsizei, const GLfloat*);
typedef void (STDCALL* PsglUniform2fv)(GLint, GLsizei, const GLfloat*);
typedef void (STDCALL* PsglUniform3fv)(GLint, GLsizei, const GLfloat*);
typedef void (STDCALL* PsglUniform4fv)(GLint, GLsizei, const GLfloat*);
typedef void (STDCALL* PsglUniform1iv)(GLint, GLsizei, const GLint*);
typedef void (STDCALL* PsglUniform2iv)(GLint, GLsizei, const GLint*);
typedef void (STDCALL* PsglUniform3iv)(GLint, GLsizei, const GLint*);
typedef void (STDCALL* PsglUniform4iv)(GLint, GLsizei, const GLint*);
typedef void (STDCALL* PsglUniformMatrix2fv)(GLint, GLsizei, GLboolean,
    const GLfloat*);
typedef void (STDCALL* PsglUniformMatrix3fv)(GLint, GLsizei, GLboolean,
    const GLfloat*);
typedef void (STDCALL* PsglUniformMatrix4fv)(GLint, GLsizei, GLboolean,
    const GLfloat*);
typedef void (STDCALL* PsglValidateProgram)(GLuint);
typedef void (STDCALL* PsglVertexAttrib1d)(GLuint, GLdouble);
typedef void (STDCALL* PsglVertexAttrib1dv)(GLuint, const GLdouble*);
typedef void (STDCALL* PsglVertexAttrib1f)(GLuint, GLfloat);
typedef void (STDCALL* PsglVertexAttrib1fv)(GLuint, const GLfloat*);
typedef void (STDCALL* PsglVertexAttrib1s)(GLuint, GLshort);
typedef void (STDCALL* PsglVertexAttrib1sv)(GLuint, const GLshort*);
typedef void (STDCALL* PsglVertexAttrib2d)(GLuint, GLdouble, GLdouble);
typedef void (STDCALL* PsglVertexAttrib2dv)(GLuint, const GLdouble*);
typedef void (STDCALL* PsglVertexAttrib2f)(GLuint, GLfloat, GLfloat);
typedef void (STDCALL* PsglVertexAttrib2fv)(GLuint, const GLfloat*);
typedef void (STDCALL* PsglVertexAttrib2s)(GLuint, GLshort, GLshort);
typedef void (STDCALL* PsglVertexAttrib2sv)(GLuint, const GLshort*);
typedef void (STDCALL* PsglVertexAttrib3d)(GLuint, GLdouble, GLdouble,
    GLdouble);
typedef void (STDCALL* PsglVertexAttrib3dv)(GLuint, const GLdouble*);
typedef void (STDCALL* PsglVertexAttrib3f)(GLuint, GLfloat, GLfloat,
    GLfloat);
typedef void (STDCALL* PsglVertexAttrib3fv)(GLuint, const GLfloat*);
typedef void (STDCALL* PsglVertexAttrib3s)(GLuint, GLshort, GLshort,
    GLshort);
typedef void (STDCALL* PsglVertexAttrib3sv)(GLuint, const GLshort*);
typedef void (STDCALL* PsglVertexAttrib4Nbv)(GLuint, const GLbyte*);
typedef void (STDCALL* PsglVertexAttrib4Niv)(GLuint, const GLint*);
typedef void (STDCALL* PsglVertexAttrib4Nsv)(GLuint, const GLshort*);
typedef void (STDCALL* PsglVertexAttrib4Nub)(GLuint, GLubyte, GLubyte,
    GLubyte, GLubyte);
typedef void (STDCALL* PsglVertexAttrib4Nubv)(GLuint, const GLubyte*);
typedef void (STDCALL* PsglVertexAttrib4Nuiv)(GLuint, const GLuint*);
typedef void (STDCALL* PsglVertexAttrib4Nusv)(GLuint, const GLushort*);
typedef void (STDCALL* PsglVertexAttrib4bv)(GLuint, const GLbyte*);
typedef void (STDCALL* PsglVertexAttrib4d)(GLuint, GLdouble, GLdouble,
    GLdouble, GLdouble);
typedef void (STDCALL* PsglVertexAttrib4dv)(GLuint, const GLdouble*);
typedef void (STDCALL* PsglVertexAttrib4f)(GLuint, GLfloat, GLfloat,
    GLfloat, GLfloat);
typedef void (STDCALL* PsglVertexAttrib4fv)(GLuint, const GLfloat*);
typedef void (STDCALL* PsglVertexAttrib4iv)(GLuint, const GLint*);
typedef void (STDCALL* PsglVertexAttrib4s)(GLuint, GLshort, GLshort,
    GLshort, GLshort);
typedef void (STDCALL* PsglVertexAttrib4sv)(GLuint, const GLshort*);
typedef void (STDCALL* PsglVertexAttrib4ubv)(GLuint, const GLubyte*);
typedef void (STDCALL* PsglVertexAttrib4uiv)(GLuint, const GLuint*);
typedef void (STDCALL* PsglVertexAttrib4usv)(GLuint, const GLushort*);
typedef void (STDCALL* PsglVertexAttribPointer)(GLuint, GLint, GLenum,
    GLboolean, GLsizei, const GLvoid*);

static PsglBlendEquationSeparate sglBlendEquationSeparate = 0;
static PsglDrawBuffers sglDrawBuffers = 0;
static PsglStencilOpSeparate sglStencilOpSeparate = 0;
static PsglStencilFuncSeparate sglStencilFuncSeparate = 0;
static PsglStencilMaskSeparate sglStencilMaskSeparate = 0;
static PsglAttachShader sglAttachShader = 0;
static PsglBindAttribLocation sglBindAttribLocation = 0;
static PsglCompileShader sglCompileShader = 0;
static PsglCreateProgram sglCreateProgram = 0;
static PsglCreateShader sglCreateShader = 0;
static PsglDeleteProgram sglDeleteProgram = 0;
static PsglDeleteShader sglDeleteShader = 0;
static PsglDetachShader sglDetachShader = 0;
static PsglDisableVertexAttribArray sglDisableVertexAttribArray = 0;
static PsglEnableVertexAttribArray sglEnableVertexAttribArray = 0;
static PsglGetActiveAttrib sglGetActiveAttrib = 0;
static PsglGetActiveUniform sglGetActiveUniform = 0;
static PsglGetAttachedShaders sglGetAttachedShaders = 0;
static PsglGetAttribLocation sglGetAttribLocation = 0;
static PsglGetProgramiv sglGetProgramiv = 0;
static PsglGetProgramInfoLog sglGetProgramInfoLog = 0;
static PsglGetShaderiv sglGetShaderiv = 0;
static PsglGetShaderInfoLog sglGetShaderInfoLog = 0;
static PsglGetShaderSource sglGetShaderSource = 0;
static PsglGetUniformLocation sglGetUniformLocation = 0;
static PsglGetUniformfv sglGetUniformfv = 0;
static PsglGetUniformiv sglGetUniformiv = 0;
static PsglGetVertexAttribdv sglGetVertexAttribdv = 0;
static PsglGetVertexAttribfv sglGetVertexAttribfv = 0;
static PsglGetVertexAttribiv sglGetVertexAttribiv = 0;
static PsglGetVertexAttribPointerv sglGetVertexAttribPointerv = 0;
static PsglIsProgram sglIsProgram = 0;
static PsglIsShader sglIsShader = 0;
static PsglLinkProgram sglLinkProgram = 0;
static PsglShaderSource sglShaderSource = 0;
static PsglUseProgram sglUseProgram = 0;
static PsglUniform1f sglUniform1f = 0;
static PsglUniform2f sglUniform2f = 0;
static PsglUniform3f sglUniform3f = 0;
static PsglUniform4f sglUniform4f = 0;
static PsglUniform1i sglUniform1i = 0;
static PsglUniform2i sglUniform2i = 0;
static PsglUniform3i sglUniform3i = 0;
static PsglUniform4i sglUniform4i = 0;
static PsglUniform1fv sglUniform1fv = 0;
static PsglUniform2fv sglUniform2fv = 0;
static PsglUniform3fv sglUniform3fv = 0;
static PsglUniform4fv sglUniform4fv = 0;
static PsglUniform1iv sglUniform1iv = 0;
static PsglUniform2iv sglUniform2iv = 0;
static PsglUniform3iv sglUniform3iv = 0;
static PsglUniform4iv sglUniform4iv = 0;
static PsglUniformMatrix2fv sglUniformMatrix2fv = 0;
static PsglUniformMatrix3fv sglUniformMatrix3fv = 0;
static PsglUniformMatrix4fv sglUniformMatrix4fv = 0;
static PsglValidateProgram sglValidateProgram = 0;
static PsglVertexAttrib1d sglVertexAttrib1d = 0;
static PsglVertexAttrib1dv sglVertexAttrib1dv = 0;
static PsglVertexAttrib1f sglVertexAttrib1f = 0;
static PsglVertexAttrib1fv sglVertexAttrib1fv = 0;
static PsglVertexAttrib1s sglVertexAttrib1s = 0;
static PsglVertexAttrib1sv sglVertexAttrib1sv = 0;
static PsglVertexAttrib2d sglVertexAttrib2d = 0;
static PsglVertexAttrib2dv sglVertexAttrib2dv = 0;
static PsglVertexAttrib2f sglVertexAttrib2f = 0;
static PsglVertexAttrib2fv sglVertexAttrib2fv = 0;
static PsglVertexAttrib2s sglVertexAttrib2s = 0;
static PsglVertexAttrib2sv sglVertexAttrib2sv = 0;
static PsglVertexAttrib3d sglVertexAttrib3d = 0;
static PsglVertexAttrib3dv sglVertexAttrib3dv = 0;
static PsglVertexAttrib3f sglVertexAttrib3f = 0;
static PsglVertexAttrib3fv sglVertexAttrib3fv = 0;
static PsglVertexAttrib3s sglVertexAttrib3s = 0;
static PsglVertexAttrib3sv sglVertexAttrib3sv = 0;
static PsglVertexAttrib4Nbv sglVertexAttrib4Nbv = 0;
static PsglVertexAttrib4Niv sglVertexAttrib4Niv = 0;
static PsglVertexAttrib4Nsv sglVertexAttrib4Nsv = 0;
static PsglVertexAttrib4Nub sglVertexAttrib4Nub = 0;
static PsglVertexAttrib4Nubv sglVertexAttrib4Nubv = 0;
static PsglVertexAttrib4Nuiv sglVertexAttrib4Nuiv = 0;
static PsglVertexAttrib4Nusv sglVertexAttrib4Nusv = 0;
static PsglVertexAttrib4bv sglVertexAttrib4bv = 0;
static PsglVertexAttrib4d sglVertexAttrib4d = 0;
static PsglVertexAttrib4dv sglVertexAttrib4dv = 0;
static PsglVertexAttrib4f sglVertexAttrib4f = 0;
static PsglVertexAttrib4fv sglVertexAttrib4fv = 0;
static PsglVertexAttrib4iv sglVertexAttrib4iv = 0;
static PsglVertexAttrib4s sglVertexAttrib4s = 0;
static PsglVertexAttrib4sv sglVertexAttrib4sv = 0;
static PsglVertexAttrib4ubv sglVertexAttrib4ubv = 0;
static PsglVertexAttrib4uiv sglVertexAttrib4uiv = 0;
static PsglVertexAttrib4usv sglVertexAttrib4usv = 0;
static PsglVertexAttribPointer sglVertexAttribPointer = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendEquationSeparate(GLenum eModeRGB, GLenum eModeAlpha)
{
    SE_BODY_A2(sglBlendEquationSeparate, eModeRGB, eModeAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawBuffers(GLsizei iNumBuffers, const GLenum* aeBuffer)
{
    SE_BODY_A2(sglDrawBuffers, iNumBuffers, aeBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilOpSeparate(GLenum eFace, GLenum eSFail, GLenum eDPFail, 
    GLenum eDPPass)
{
    SE_BODY_A4(sglStencilOpSeparate, eFace, eSFail, eDPFail, eDPPass);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilFuncSeparate(GLenum eFrontFunc, GLenum eBackFunc, 
    GLint iReference, GLuint uiMask)
{
    SE_BODY_A4(sglStencilFuncSeparate, eFrontFunc, eBackFunc, iReference, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glStencilMaskSeparate(GLenum eFace, GLuint uiMask)
{
    SE_BODY_A2(sglStencilMaskSeparate, eFace, uiMask);
}
/*--------------------------------------------------------------------------*/
void SE_glAttachShader(GLuint uiProgram, GLuint uiShader)
{
    SE_BODY_A2(sglAttachShader, uiProgram, uiShader);
}
/*--------------------------------------------------------------------------*/
void SE_glBindAttribLocation(GLuint uiProgram, GLuint uiIndex, 
    const GLchar* acName)
{
    SE_BODY_A3(sglBindAttribLocation, uiProgram, uiIndex, acName);
}
/*--------------------------------------------------------------------------*/
void SE_glCompileShader(GLuint uiShader)
{
    SE_BODY_A1(sglCompileShader, uiShader);
}
/*--------------------------------------------------------------------------*/
GLuint SE_glCreateProgram()
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A0_RET(sglCreateProgram, GLuint, 0);
}
/*--------------------------------------------------------------------------*/
GLuint SE_glCreateShader(GLenum eType)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A1_RET(sglCreateShader, eType, GLuint, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteProgram(GLuint uiProgram)
{
    SE_BODY_A1(sglDeleteProgram, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteShader(GLuint uiShader)
{
    SE_BODY_A1(sglDeleteShader, uiShader);
}
/*--------------------------------------------------------------------------*/
void SE_glDetachShader(GLuint uiProgram, GLuint uiShader)
{
    SE_BODY_A2(sglDetachShader, uiProgram, uiShader);
}
/*--------------------------------------------------------------------------*/
void SE_glDisableVertexAttribArray(GLuint uiIndex)
{
    SE_BODY_A1(sglDisableVertexAttribArray, uiIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glEnableVertexAttribArray(GLuint uiIndex)
{
    SE_BODY_A1(sglEnableVertexAttribArray, uiIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glGetActiveAttrib(GLuint uiProgram, GLuint uiIndex, GLsizei iBufSize, 
    GLsizei* piLength, GLint* piSize, GLenum* peType, GLchar* acName)
{
    SE_BODY_A7(sglGetActiveAttrib, uiProgram, uiIndex, iBufSize, piLength, piSize, 
        peType, acName);
}
/*--------------------------------------------------------------------------*/
void SE_glGetActiveUniform(GLuint uiProgram, GLuint uiIndex, GLsizei iBufSize, 
    GLsizei* piLength, GLint* piSize, GLenum* peType, GLchar* acName)
{
    SE_BODY_A7(sglGetActiveUniform, uiProgram, uiIndex, iBufSize, piLength, piSize, 
        peType, acName);
}
/*--------------------------------------------------------------------------*/
void SE_glGetAttachedShaders(GLuint uiProgram, GLsizei iMaxCount, 
    GLsizei* aiCount, GLuint* aiObj)
{
    SE_BODY_A4(sglGetAttachedShaders, uiProgram, iMaxCount, aiCount, aiObj);
}
/*--------------------------------------------------------------------------*/
GLint SE_glGetAttribLocation(GLuint uiProgram, const GLchar* acName)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A2_RET(sglGetAttribLocation, uiProgram, acName, GLint, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramiv(GLuint uiProgram, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetProgramiv, uiProgram, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramInfoLog(GLuint uiProgram, GLsizei iBufSize, 
    GLsizei* piLength, GLchar* acInfoLog)
{
    SE_BODY_A4(sglGetProgramInfoLog, uiProgram, iBufSize, piLength, acInfoLog);
}
/*--------------------------------------------------------------------------*/
void SE_glGetShaderiv(GLuint uiShader, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetShaderiv, uiShader, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetShaderInfoLog(GLuint uiShader, GLsizei iBufSize, 
    GLsizei* piLength, GLchar* acInfoLog)
{
    SE_BODY_A4(sglGetShaderInfoLog, uiShader, iBufSize, piLength, acInfoLog);
}
/*--------------------------------------------------------------------------*/
void SE_glGetShaderSource(GLuint uiShader, GLsizei iBufSize, 
    GLsizei* piLength, GLchar* acSource)
{
    SE_BODY_A4(sglGetShaderSource, uiShader, iBufSize, piLength, acSource);
}
/*--------------------------------------------------------------------------*/
GLint SE_glGetUniformLocation(GLuint uiProgram, const GLchar* acName)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A2_RET(sglGetUniformLocation, uiProgram, acName, GLint, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetUniformfv(GLuint uiProgram, GLint uiLocation, GLfloat* afParam)
{
    SE_BODY_A3(sglGetUniformfv, uiProgram, uiLocation, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetUniformiv(GLuint uiProgram, GLint uiLocation, GLint* aiParam)
{
    SE_BODY_A3(sglGetUniformiv, uiProgram, uiLocation, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribdv(GLuint uiIndex, GLenum ePName, GLdouble* adParam)
{
    SE_BODY_A3(sglGetVertexAttribdv, uiIndex, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribfv(GLuint uiIndex, GLenum ePName, GLfloat* afParam)
{
    SE_BODY_A3(sglGetVertexAttribfv, uiIndex, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribiv(GLuint uiIndex, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetVertexAttribiv, uiIndex, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribPointerv(GLuint uiIndex, GLenum ePName, 
    GLvoid** apvParam)
{
    SE_BODY_A3(sglGetVertexAttribPointerv, uiIndex, ePName, apvParam);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsProgram(GLuint uiProgram)
{
    SE_BODY_A1_RET(sglIsProgram, uiProgram, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsShader(GLuint uiShader)
{
    SE_BODY_A1_RET(sglIsShader, uiShader, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glLinkProgram(GLuint uiProgram)
{
    SE_BODY_A1(sglLinkProgram, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glShaderSource(GLuint uiShader, GLsizei iCount, 
    const GLchar** aacString, const GLint* piLength)
{
    SE_BODY_A4(sglShaderSource, uiShader, iCount, aacString, piLength);
}
/*--------------------------------------------------------------------------*/
void SE_glUseProgram(GLuint uiProgram)
{
    SE_BODY_A1(sglUseProgram, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1f(GLint uiLocation, GLfloat fV0)
{
    SE_BODY_A2(sglUniform1f, uiLocation, fV0);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2f(GLint uiLocation, GLfloat fV0, GLfloat fV1)
{
    SE_BODY_A3(sglUniform2f, uiLocation, fV0, fV1);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3f(GLint uiLocation, GLfloat fV0, GLfloat fV1, GLfloat fV2)
{
    SE_BODY_A4(sglUniform3f, uiLocation, fV0, fV1, fV2);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4f(GLint uiLocation, GLfloat fV0, GLfloat fV1, GLfloat fV2, 
    GLfloat fV3)
{
    SE_BODY_A5(sglUniform4f, uiLocation, fV0, fV1, fV2, fV3);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1i(GLint uiLocation, GLint iV0)
{
    SE_BODY_A2(sglUniform1i, uiLocation, iV0);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2i(GLint uiLocation, GLint iV0, GLint iV1)
{
    SE_BODY_A3(sglUniform2i, uiLocation, iV0, iV1);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3i(GLint uiLocation, GLint iV0, GLint iV1, GLint iV2)
{
    SE_BODY_A4(sglUniform3i, uiLocation, iV0, iV1, iV2);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4i(GLint uiLocation, GLint iV0, GLint iV1, GLint iV2, 
    GLint iV3)
{
    SE_BODY_A5(sglUniform4i, uiLocation, iV0, iV1, iV2, iV3);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1fv(GLint uiLocation, GLsizei iCount, const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform1fv, uiLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2fv(GLint uiLocation, GLsizei iCount, const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform2fv, uiLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3fv(GLint uiLocation, GLsizei iCount, const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform3fv, uiLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4fv(GLint uiLocation, GLsizei iCount, const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform4fv, uiLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1iv(GLint uiLocation, GLsizei iCount, const GLint* aiValue)
{
    SE_BODY_A3(sglUniform1iv, uiLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2iv(GLint uiLocation, GLsizei iCount, const GLint* aiValue)
{
    SE_BODY_A3(sglUniform2iv, uiLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3iv(GLint uiLocation, GLsizei iCount, const GLint* aiValue)
{
    SE_BODY_A3(sglUniform3iv, uiLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4iv(GLint uiLocation, GLsizei iCount, const GLint* aiValue)
{
    SE_BODY_A3(sglUniform4iv, uiLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix2fv(GLint uiLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix2fv, uiLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix3fv(GLint uiLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix3fv, uiLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix4fv(GLint uiLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix4fv, uiLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glValidateProgram(GLuint uiProgram)
{
    SE_BODY_A1(sglValidateProgram, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1d(GLuint uiIndex, GLdouble dX)
{
    SE_BODY_A2(sglVertexAttrib1d, uiIndex, dX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1dv(GLuint uiIndex, const GLdouble* pdX)
{
    SE_BODY_A2(sglVertexAttrib1dv, uiIndex, pdX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1f(GLuint uiIndex, GLfloat fX)
{
    SE_BODY_A2(sglVertexAttrib1f, uiIndex, fX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1fv(GLuint uiIndex, const GLfloat* pfX)
{
    SE_BODY_A2(sglVertexAttrib1fv, uiIndex, pfX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1s(GLuint uiIndex, GLshort sX)
{
    SE_BODY_A2(sglVertexAttrib1s, uiIndex, sX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1sv(GLuint uiIndex, const GLshort* psX)
{
    SE_BODY_A2(sglVertexAttrib1sv, uiIndex, psX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2d(GLuint uiIndex, GLdouble dX, GLdouble dY)
{
    SE_BODY_A3(sglVertexAttrib2d, uiIndex, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2dv(GLuint uiIndex, const GLdouble* adXY)
{
    SE_BODY_A2(sglVertexAttrib2dv, uiIndex, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2f(GLuint uiIndex, GLfloat fX, GLfloat fY)
{
    SE_BODY_A3(sglVertexAttrib2f, uiIndex, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2fv(GLuint uiIndex, const GLfloat* afXY)
{
    SE_BODY_A2(sglVertexAttrib2fv, uiIndex, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2s(GLuint uiIndex, GLshort sX, GLshort sY)
{
    SE_BODY_A3(sglVertexAttrib2s, uiIndex, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2sv(GLuint uiIndex, const GLshort* asXY)
{
    SE_BODY_A2(sglVertexAttrib2sv, uiIndex, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3d(GLuint uiIndex, GLdouble dX, GLdouble dY, 
    GLdouble dZ)
{
    SE_BODY_A4(sglVertexAttrib3d, uiIndex, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3dv(GLuint uiIndex, const GLdouble* adXYZ)
{
    SE_BODY_A2(sglVertexAttrib3dv, uiIndex, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3f(GLuint uiIndex, GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_BODY_A4(sglVertexAttrib3f, uiIndex, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3fv(GLuint uiIndex, const GLfloat* afXYZ)
{
    SE_BODY_A2(sglVertexAttrib3fv, uiIndex, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3s(GLuint uiIndex, GLshort sX, GLshort sY, GLshort sZ)
{
    SE_BODY_A4(sglVertexAttrib3s, uiIndex, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3sv(GLuint uiIndex, const GLshort* asXYZ)
{
    SE_BODY_A2(sglVertexAttrib3sv, uiIndex, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nbv(GLuint uiIndex, const GLbyte* acXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Nbv, uiIndex, acXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Niv(GLuint uiIndex, const GLint* aiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Niv, uiIndex, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nsv(GLuint uiIndex, const GLshort* asXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Nsv, uiIndex, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nub(GLuint uiIndex, GLubyte ucX, GLubyte ucY, 
    GLubyte ucZ, GLubyte ucW)
{
    SE_BODY_A5(sglVertexAttrib4Nub, uiIndex, ucX, ucY, ucZ, ucW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nubv(GLuint uiIndex, const GLubyte* aucXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Nubv, uiIndex, aucXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nuiv(GLuint uiIndex, const GLuint* auiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Nuiv, uiIndex, auiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4Nusv(GLuint uiIndex, const GLushort* ausXYZW)
{
    SE_BODY_A2(sglVertexAttrib4Nusv, uiIndex, ausXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4bv(GLuint uiIndex, const GLbyte* acXYZW)
{
    SE_BODY_A2(sglVertexAttrib4bv, uiIndex, acXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4d(GLuint uiIndex, GLdouble dX, GLdouble dY, 
    GLdouble dZ, GLdouble dW)
{
    SE_BODY_A5(sglVertexAttrib4d, uiIndex, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4dv(GLuint uiIndex, const GLdouble* adXYZW)
{
    SE_BODY_A2(sglVertexAttrib4dv, uiIndex, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4f(GLuint uiIndex, GLfloat fX, GLfloat fY, GLfloat fZ, 
    GLfloat fW)
{
    SE_BODY_A5(sglVertexAttrib4f, uiIndex, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4fv(GLuint uiIndex, const GLfloat* afXYZW)
{
    SE_BODY_A2(sglVertexAttrib4fv, uiIndex, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4iv(GLuint uiIndex, const GLint* aiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4iv, uiIndex, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4s(GLuint uiIndex, GLshort sX, GLshort sY, GLshort sZ, 
    GLshort sW)
{
    SE_BODY_A5(sglVertexAttrib4s, uiIndex, sX, sY, sZ, sW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4sv(GLuint uiIndex, const GLshort* asXYZW)
{
    SE_BODY_A2(sglVertexAttrib4sv, uiIndex, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4ubv(GLuint uiIndex, const GLubyte* aucXYZW)
{
    SE_BODY_A2(sglVertexAttrib4ubv, uiIndex, aucXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4uiv(GLuint uiIndex, const GLuint* auiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4uiv, uiIndex, auiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4usv(GLuint uiIndex, const GLushort* ausXYZW)
{
    SE_BODY_A2(sglVertexAttrib4usv, uiIndex, ausXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttribPointer(GLuint uiIndex, GLint iSize, GLenum eType, 
     GLboolean ucNormalized, GLsizei iStride, const GLvoid* pvPointer)
{
    SE_BODY_A6(sglVertexAttribPointer, uiIndex, iSize, eType, ucNormalized, 
        iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitOpenGL20()
{
    if( SE_GL_GetVersion() >= SE_GL_VERSION_2_0 )
    {
        SE_ExistsOpenGL20 = 1;

        SE_GET_FUNCTION(sglGetShaderiv);
        SE_GET_FUNCTION(sglIsShader);
        SE_GET_FUNCTION(sglStencilMaskSeparate);

        /* GL_ARB_draw_buffers */
        SE_GET_FUNCTION(sglDrawBuffers);

        /* GL_ARB_shader_objects */
        SE_GET_FUNCTION(sglAttachShader);       /* glAttachObjectARB */
        SE_GET_FUNCTION(sglCompileShader);
        SE_GET_FUNCTION(sglCreateProgram);      /* glCreateProgramObjectARB */
        SE_GET_FUNCTION(sglCreateShader);       /* glCreateShaderObjectARB */
        SE_GET_FUNCTION(sglDeleteProgram);      /* glDeleteProgramObjectARB */
        SE_GET_FUNCTION(sglDeleteShader);       /* glDeleteProgramObjectARB */
        SE_GET_FUNCTION(sglDetachShader);       /* glDetachObjectARB */
        SE_GET_FUNCTION(sglGetActiveUniform);
        SE_GET_FUNCTION(sglGetAttachedShaders); /* glGetAttachObjectsARB */
        SE_GET_FUNCTION(sglGetProgramInfoLog);  /* glGetInfoLogARB */
        SE_GET_FUNCTION(sglGetShaderInfoLog);   /* glGetInfoLogARB */
        SE_GET_FUNCTION(sglGetShaderSource);
        SE_GET_FUNCTION(sglGetUniformfv);
        SE_GET_FUNCTION(sglGetUniformiv);
        SE_GET_FUNCTION(sglGetUniformLocation);
        SE_GET_FUNCTION(sglLinkProgram);
        SE_GET_FUNCTION(sglShaderSource);
        SE_GET_FUNCTION(sglUniform1f);
        SE_GET_FUNCTION(sglUniform2f);
        SE_GET_FUNCTION(sglUniform3f);
        SE_GET_FUNCTION(sglUniform4f);
        SE_GET_FUNCTION(sglUniform1i);
        SE_GET_FUNCTION(sglUniform2i);
        SE_GET_FUNCTION(sglUniform3i);
        SE_GET_FUNCTION(sglUniform4i);
        SE_GET_FUNCTION(sglUniform1fv);
        SE_GET_FUNCTION(sglUniform2fv);
        SE_GET_FUNCTION(sglUniform3fv);
        SE_GET_FUNCTION(sglUniform4fv);
        SE_GET_FUNCTION(sglUniform1iv);
        SE_GET_FUNCTION(sglUniform2iv);
        SE_GET_FUNCTION(sglUniform3iv);
        SE_GET_FUNCTION(sglUniform4iv);
        SE_GET_FUNCTION(sglUniformMatrix2fv);
        SE_GET_FUNCTION(sglUniformMatrix3fv);
        SE_GET_FUNCTION(sglUniformMatrix4fv);
        SE_GET_FUNCTION(sglUseProgram);         /* glUseProgramObjectARB */
        SE_GET_FUNCTION(sglValidateProgram);

        /* GL_ARB_fragment_program and GL_ARB_vertex_program */
        SE_GET_FUNCTION(sglDisableVertexAttribArray);
        SE_GET_FUNCTION(sglEnableVertexAttribArray);
        SE_GET_FUNCTION(sglGetProgramiv);
        SE_GET_FUNCTION(sglGetVertexAttribdv);
        SE_GET_FUNCTION(sglGetVertexAttribfv);
        SE_GET_FUNCTION(sglGetVertexAttribiv);
        SE_GET_FUNCTION(sglGetVertexAttribPointerv);
        SE_GET_FUNCTION(sglIsProgram);
        SE_GET_FUNCTION(sglVertexAttrib1d);
        SE_GET_FUNCTION(sglVertexAttrib1dv);
        SE_GET_FUNCTION(sglVertexAttrib1f);
        SE_GET_FUNCTION(sglVertexAttrib1fv);
        SE_GET_FUNCTION(sglVertexAttrib1s);
        SE_GET_FUNCTION(sglVertexAttrib1sv);
        SE_GET_FUNCTION(sglVertexAttrib2d);
        SE_GET_FUNCTION(sglVertexAttrib2dv);
        SE_GET_FUNCTION(sglVertexAttrib2f);
        SE_GET_FUNCTION(sglVertexAttrib2fv);
        SE_GET_FUNCTION(sglVertexAttrib2s);
        SE_GET_FUNCTION(sglVertexAttrib2sv);
        SE_GET_FUNCTION(sglVertexAttrib3d);
        SE_GET_FUNCTION(sglVertexAttrib3dv);
        SE_GET_FUNCTION(sglVertexAttrib3f);
        SE_GET_FUNCTION(sglVertexAttrib3fv);
        SE_GET_FUNCTION(sglVertexAttrib3s);
        SE_GET_FUNCTION(sglVertexAttrib3sv);
        SE_GET_FUNCTION(sglVertexAttrib4Nbv);
        SE_GET_FUNCTION(sglVertexAttrib4Niv);
        SE_GET_FUNCTION(sglVertexAttrib4Nsv);
        SE_GET_FUNCTION(sglVertexAttrib4Nub);
        SE_GET_FUNCTION(sglVertexAttrib4Nubv);
        SE_GET_FUNCTION(sglVertexAttrib4Nuiv);
        SE_GET_FUNCTION(sglVertexAttrib4Nusv);
        SE_GET_FUNCTION(sglVertexAttrib4bv);
        SE_GET_FUNCTION(sglVertexAttrib4d);
        SE_GET_FUNCTION(sglVertexAttrib4dv);
        SE_GET_FUNCTION(sglVertexAttrib4f);
        SE_GET_FUNCTION(sglVertexAttrib4fv);
        SE_GET_FUNCTION(sglVertexAttrib4iv);
        SE_GET_FUNCTION(sglVertexAttrib4s);
        SE_GET_FUNCTION(sglVertexAttrib4sv);
        SE_GET_FUNCTION(sglVertexAttrib4ubv);
        SE_GET_FUNCTION(sglVertexAttrib4uiv);
        SE_GET_FUNCTION(sglVertexAttrib4usv);
        SE_GET_FUNCTION(sglVertexAttribPointer);

        /* GL_ARB_vertex_shader */
        SE_GET_FUNCTION(sglBindAttribLocation);
        SE_GET_FUNCTION(sglGetActiveAttrib);
        SE_GET_FUNCTION(sglGetAttribLocation);

        /* GL_EXT_blend_equation_separate */
        SE_GET_FUNCTION(sglBlendEquationSeparate);

        /* GL_ATI_separate_stencil */
        SE_GET_FUNCTION(sglStencilOpSeparate);
        SE_GET_FUNCTION(sglStencilFuncSeparate);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** ARB Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 01) GL_ARB_multitexture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbMultitexture = 0;

static PsglActiveTexture sglActiveTextureARB = 0;
static PsglClientActiveTexture sglClientActiveTextureARB = 0;
static PsglMultiTexCoord1d sglMultiTexCoord1dARB = 0;
static PsglMultiTexCoord1dv sglMultiTexCoord1dvARB = 0;
static PsglMultiTexCoord1f sglMultiTexCoord1fARB = 0;
static PsglMultiTexCoord1fv sglMultiTexCoord1fvARB = 0;
static PsglMultiTexCoord1i sglMultiTexCoord1iARB = 0;
static PsglMultiTexCoord1iv sglMultiTexCoord1ivARB = 0;
static PsglMultiTexCoord1s sglMultiTexCoord1sARB = 0;
static PsglMultiTexCoord1sv sglMultiTexCoord1svARB = 0;
static PsglMultiTexCoord2d sglMultiTexCoord2dARB = 0;
static PsglMultiTexCoord2dv sglMultiTexCoord2dvARB = 0;
static PsglMultiTexCoord2f sglMultiTexCoord2fARB = 0;
static PsglMultiTexCoord2fv sglMultiTexCoord2fvARB = 0;
static PsglMultiTexCoord2i sglMultiTexCoord2iARB = 0;
static PsglMultiTexCoord2iv sglMultiTexCoord2ivARB = 0;
static PsglMultiTexCoord2s sglMultiTexCoord2sARB = 0;
static PsglMultiTexCoord2sv sglMultiTexCoord2svARB = 0;
static PsglMultiTexCoord3d sglMultiTexCoord3dARB = 0;
static PsglMultiTexCoord3dv sglMultiTexCoord3dvARB = 0;
static PsglMultiTexCoord3f sglMultiTexCoord3fARB = 0;
static PsglMultiTexCoord3fv sglMultiTexCoord3fvARB = 0;
static PsglMultiTexCoord3i sglMultiTexCoord3iARB = 0;
static PsglMultiTexCoord3iv sglMultiTexCoord3ivARB = 0;
static PsglMultiTexCoord3s sglMultiTexCoord3sARB = 0;
static PsglMultiTexCoord3sv sglMultiTexCoord3svARB = 0;
static PsglMultiTexCoord4d sglMultiTexCoord4dARB = 0;
static PsglMultiTexCoord4dv sglMultiTexCoord4dvARB = 0;
static PsglMultiTexCoord4f sglMultiTexCoord4fARB = 0;
static PsglMultiTexCoord4fv sglMultiTexCoord4fvARB = 0;
static PsglMultiTexCoord4i sglMultiTexCoord4iARB = 0;
static PsglMultiTexCoord4iv sglMultiTexCoord4ivARB = 0;
static PsglMultiTexCoord4s sglMultiTexCoord4sARB = 0;
static PsglMultiTexCoord4sv sglMultiTexCoord4svARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glActiveTextureARB(GLenum eTexture)
{
    SE_BODY_A1(sglActiveTextureARB, eTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glClientActiveTextureARB(GLenum eTexture)
{
    SE_BODY_A1(sglClientActiveTextureARB, eTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1dARB(GLenum eTarget, GLdouble dS)
{
    SE_BODY_A2(sglMultiTexCoord1dARB, eTarget, dS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1dvARB(GLenum eTarget, const GLdouble* pdS)
{
    SE_BODY_A2(sglMultiTexCoord1dvARB, eTarget, pdS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1fARB(GLenum eTarget, GLfloat fS)
{
    SE_BODY_A2(sglMultiTexCoord1fARB, eTarget, fS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1fvARB(GLenum eTarget, const GLfloat* pfS)
{
    SE_BODY_A2(sglMultiTexCoord1fvARB, eTarget, pfS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1iARB(GLenum eTarget, GLint iS)
{
    SE_BODY_A2(sglMultiTexCoord1iARB, eTarget, iS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1ivARB(GLenum eTarget, const GLint* piS)
{
    SE_BODY_A2(sglMultiTexCoord1ivARB, eTarget, piS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1sARB(GLenum eTarget, GLshort sS)
{
    SE_BODY_A2(sglMultiTexCoord1sARB, eTarget, sS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord1svARB(GLenum eTarget, const GLshort* psS)
{
    SE_BODY_A2(sglMultiTexCoord1svARB, eTarget, psS);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2dARB(GLenum eTarget, GLdouble dS, GLdouble dT)
{
    SE_BODY_A3(sglMultiTexCoord2dARB, eTarget, dS, dT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2dvARB(GLenum eTarget, const GLdouble* adST)
{
    SE_BODY_A2(sglMultiTexCoord2dvARB, eTarget, adST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2fARB(GLenum eTarget, GLfloat fS, GLfloat fT)
{
    SE_BODY_A3(sglMultiTexCoord2fARB, eTarget, fS, fT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2fvARB(GLenum eTarget, const GLfloat* afST)
{
    SE_BODY_A2(sglMultiTexCoord2fvARB, eTarget, afST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2iARB(GLenum eTarget, GLint iS, GLint iT)
{
    SE_BODY_A3(sglMultiTexCoord2iARB, eTarget, iS, iT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2ivARB(GLenum eTarget, const GLint* aiST)
{
    SE_BODY_A2(sglMultiTexCoord2ivARB, eTarget, aiST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2sARB(GLenum eTarget, GLshort sS, GLshort sT)
{
    SE_BODY_A3(sglMultiTexCoord2sARB, eTarget, sS, sT);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord2svARB(GLenum eTarget, const GLshort* asST)
{
    SE_BODY_A2(sglMultiTexCoord2svARB, eTarget, asST);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3dARB(GLenum eTarget, GLdouble dS, GLdouble dT, 
    GLdouble dR)
{
    SE_BODY_A4(sglMultiTexCoord3dARB, eTarget, dS, dT, dR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3dvARB(GLenum eTarget, const GLdouble* adSTR)
{
    SE_BODY_A2(sglMultiTexCoord3dvARB, eTarget, adSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3fARB(GLenum eTarget, GLfloat fS, GLfloat fT, 
    GLfloat fR)
{
    SE_BODY_A4(sglMultiTexCoord3fARB, eTarget, fS, fT, fR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3fvARB(GLenum eTarget, const GLfloat* afSTR)
{
    SE_BODY_A2(sglMultiTexCoord3fvARB, eTarget, afSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3iARB(GLenum eTarget, GLint iS, GLint iT, GLint iR)
{
    SE_BODY_A4(sglMultiTexCoord3iARB, eTarget, iS, iT, iR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3ivARB(GLenum eTarget, const GLint* aiSTR)
{
    SE_BODY_A2(sglMultiTexCoord3ivARB, eTarget, aiSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3sARB(GLenum eTarget, GLshort sS, GLshort sT, 
    GLshort sR)
{
    SE_BODY_A4(sglMultiTexCoord3sARB, eTarget, sS, sT, sR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord3svARB(GLenum eTarget, const GLshort* asSTR)
{
    SE_BODY_A2(sglMultiTexCoord3svARB, eTarget, asSTR);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4dARB(GLenum eTarget, GLdouble dS, GLdouble dT, 
    GLdouble dR, GLdouble dQ)
{
    SE_BODY_A5(sglMultiTexCoord4dARB, eTarget, dS, dT, dR, dQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4dvARB(GLenum eTarget, const GLdouble* adSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4dvARB, eTarget, adSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4fARB(GLenum eTarget, GLfloat fS, GLfloat fT, 
    GLfloat fR, GLfloat fQ)
{
    SE_BODY_A5(sglMultiTexCoord4fARB, eTarget, fS, fT, fR, fQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4fvARB(GLenum eTarget, const GLfloat* afSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4fvARB, eTarget, afSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4iARB(GLenum eTarget, GLint iS, GLint iT, GLint iR, 
    GLint iQ)
{
    SE_BODY_A5(sglMultiTexCoord4iARB, eTarget, iS, iT, iR, iQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4ivARB(GLenum eTarget, const GLint* aiSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4ivARB, eTarget, aiSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4sARB(GLenum eTarget, GLshort sS, GLshort sT, 
    GLshort sR, GLshort sQ)
{
    SE_BODY_A5(sglMultiTexCoord4sARB, eTarget, sS, sT, sR, sQ);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiTexCoord4svARB(GLenum eTarget, const GLshort* asSTRQ)
{
    SE_BODY_A2(sglMultiTexCoord4svARB, eTarget, asSTRQ);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbMultitexture()
{
    if( SE_GL_SupportsExtension("GL_ARB_multitexture") )
    {
        SE_ExistsGlArbMultitexture = 1;

        SE_GET_FUNCTION_C(sglActiveTexture, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglClientActiveTexture, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord1sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord2sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord3sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiTexCoord4sv, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 03) GL_ARB_transpose_matrix */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTransposeMatrix = 0;

static PsglLoadTransposeMatrixf sglLoadTransposeMatrixfARB = 0;
static PsglLoadTransposeMatrixd sglLoadTransposeMatrixdARB = 0;
static PsglMultTransposeMatrixf sglMultTransposeMatrixfARB = 0;
static PsglMultTransposeMatrixd sglMultTransposeMatrixdARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glLoadTransposeMatrixdARB(const GLdouble* adMatrix)
{
    SE_BODY_A1(sglLoadTransposeMatrixdARB, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glLoadTransposeMatrixfARB(const GLfloat* afMatrix)
{
    SE_BODY_A1(sglLoadTransposeMatrixfARB, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glMultTransposeMatrixdARB(const GLdouble* adMatrix)
{
    SE_BODY_A1(sglMultTransposeMatrixdARB, adMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_glMultTransposeMatrixfARB(const GLfloat* afMatrix)
{
    SE_BODY_A1(sglMultTransposeMatrixfARB, afMatrix);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTransposeMatrix()
{
    if( SE_GL_SupportsExtension("GL_ARB_transpose_matrix") )
    {
        SE_ExistsGlArbTransposeMatrix = 1;

        SE_GET_FUNCTION_C(sglLoadTransposeMatrixf, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglLoadTransposeMatrixd, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultTransposeMatrixf, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultTransposeMatrixd, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 05) GL_ARB_multisample */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbMultisample = 0;

static PsglSampleCoverage sglSampleCoverageARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glSampleCoverageARB(GLclampf fValue, GLboolean ucInvert)
{
    SE_BODY_A2(sglSampleCoverageARB, fValue, ucInvert);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbMultisample()
{
    if( SE_GL_SupportsExtension("GL_ARB_multisample") )
    {
        SE_ExistsGlArbMultisample = 1;

        SE_GET_FUNCTION_C(sglSampleCoverage, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 06) GL_ARB_texture_env_add */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureEnvAdd = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureEnvAdd()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_env_add") )
    {
        SE_ExistsGlArbTextureEnvAdd = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 07) GL_ARB_texture_cube_map */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureCubeMap = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureCubeMap()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_cube_map") )
    {
        SE_ExistsGlArbTextureCubeMap = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 12) GL_ARB_texture_compression */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureCompression = 0;

static PsglCompressedTexImage3D sglCompressedTexImage3DARB = 0;
static PsglCompressedTexImage2D sglCompressedTexImage2DARB = 0;
static PsglCompressedTexImage1D sglCompressedTexImage1DARB = 0;
static PsglCompressedTexSubImage3D sglCompressedTexSubImage3DARB = 0;
static PsglCompressedTexSubImage2D sglCompressedTexSubImage2DARB = 0;
static PsglCompressedTexSubImage1D sglCompressedTexSubImage1DARB = 0;
static PsglGetCompressedTexImage sglGetCompressedTexImageARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage1DARB(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLint iBorder, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A7(sglCompressedTexImage1DARB, eTarget, iLevel, eInternalFormat, 
        iWidth, iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage2DARB(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLint iBorder, 
    GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A8(sglCompressedTexImage2DARB, eTarget, iLevel, eInternalFormat, 
        iWidth, iHeight, iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexImage3DARB(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth, 
    GLint iBorder, GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A9(sglCompressedTexImage3DARB, eTarget, iLevel, eInternalFormat, 
        iWidth, iHeight, iDepth, iBorder, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage1DARB(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A7(sglCompressedTexSubImage1DARB, eTarget, iLevel, iXOffset, iWidth, 
        eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage2DARB(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight, 
    GLenum eFormat, GLsizei iImageSize, const GLvoid* pvData)
{
    SE_BODY_A9(sglCompressedTexSubImage2DARB, eTarget, iLevel, iXOffset, iYOffset, 
        iWidth, iHeight, eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCompressedTexSubImage3DARB(GLenum eTarget, GLint iLevel, 
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth, 
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLsizei iImageSize, 
    const GLvoid* pvData)
{
    SE_BODY_A11(sglCompressedTexSubImage3DARB, eTarget, iLevel, iXOffset, 
        iYOffset, iZOffset, iWidth, iHeight, iDepth, eFormat, iImageSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glGetCompressedTexImageARB(GLenum eTarget, GLint iLevel, 
    GLvoid* pvData)
{
    SE_BODY_A3(sglGetCompressedTexImageARB, eTarget, iLevel, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureCompression()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_compression") )
    {
        SE_ExistsGlArbTextureCompression = 1;

        SE_GET_FUNCTION_C(sglCompressedTexImage3D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglCompressedTexImage2D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglCompressedTexImage1D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglCompressedTexSubImage3D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglCompressedTexSubImage2D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglCompressedTexSubImage1D, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetCompressedTexImage, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 13) GL_ARB_texture_border_clamp */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureBorderClamp = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureBorderClamp()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_border_clamp") )
    {
        SE_ExistsGlArbTextureBorderClamp = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 14) GL_ARB_point_parameters */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbPointParameters = 0;

static PsglPointParameterf sglPointParameterfARB = 0;
static PsglPointParameterfv sglPointParameterfvARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glPointParameterfARB(GLenum ePName, GLfloat fParam)
{
    SE_BODY_A2(sglPointParameterfARB, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameterfvARB(GLenum ePName, const GLfloat* afParam)
{
    SE_BODY_A2(sglPointParameterfvARB, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbPointParameters()
{
    if( SE_GL_SupportsExtension("GL_ARB_point_parameters") )
    {
        SE_ExistsGlArbPointParameters = 1;

        SE_GET_FUNCTION_C(sglPointParameterf, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglPointParameterfv, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 15) GL_ARB_vertex_blend */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbVertexBlend = 0;

typedef void (STDCALL* PsglWeightbvARB)(GLint, const GLbyte*);
typedef void (STDCALL* PsglWeightsvARB)(GLint, const GLshort*);
typedef void (STDCALL* PsglWeightivARB)(GLint, const GLint*);
typedef void (STDCALL* PsglWeightfvARB)(GLint, const GLfloat*);
typedef void (STDCALL* PsglWeightdvARB)(GLint, const GLdouble*);
typedef void (STDCALL* PsglWeightubvARB)(GLint, const GLubyte*);
typedef void (STDCALL* PsglWeightusvARB)(GLint, const GLushort*);
typedef void (STDCALL* PsglWeightuivARB)(GLint, const GLuint*);
typedef void (STDCALL* PsglWeightPointerARB)(GLint, GLenum, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglVertexBlendARB)(GLint);

static PsglWeightbvARB sglWeightbvARB = 0;
static PsglWeightsvARB sglWeightsvARB = 0;
static PsglWeightivARB sglWeightivARB = 0;
static PsglWeightfvARB sglWeightfvARB = 0;
static PsglWeightdvARB sglWeightdvARB = 0;
static PsglWeightubvARB sglWeightubvARB = 0;
static PsglWeightusvARB sglWeightusvARB = 0;
static PsglWeightuivARB sglWeightuivARB = 0;
static PsglWeightPointerARB sglWeightPointerARB = 0;
static PsglVertexBlendARB sglVertexBlendARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glWeightbvARB(GLint iSize, const GLbyte* acWeight)
{
    SE_BODY_A2(sglWeightbvARB, iSize, acWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightsvARB(GLint iSize, const GLshort* asWeight)
{
    SE_BODY_A2(sglWeightsvARB, iSize, asWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightivARB(GLint iSize, const GLint* aiWeight)
{
    SE_BODY_A2(sglWeightivARB, iSize, aiWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightfvARB(GLint iSize, const GLfloat* afWeight)
{
    SE_BODY_A2(sglWeightfvARB, iSize, afWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightdvARB(GLint iSize, const GLdouble* adWeight)
{
    SE_BODY_A2(sglWeightdvARB, iSize, adWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightubvARB(GLint iSize, const GLubyte* aucWeight)
{
    SE_BODY_A2(sglWeightubvARB, iSize, aucWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightusvARB(GLint iSize, const GLushort* ausWeight)
{
    SE_BODY_A2(sglWeightusvARB, iSize, ausWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightuivARB(GLint iSize, const GLuint* auiWeight)
{
    SE_BODY_A2(sglWeightuivARB, iSize, auiWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glWeightPointerARB(GLint iSize, GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglWeightPointerARB, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexBlendARB(GLint iCount)
{
    SE_BODY_A1(sglVertexBlendARB, iCount);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbVertexBlend()
{
    if( SE_GL_SupportsExtension("GL_ARB_vertex_blend") )
    {
        SE_ExistsGlArbVertexBlend = 1;

        SE_GET_FUNCTION(sglWeightbvARB);
        SE_GET_FUNCTION(sglWeightsvARB);
        SE_GET_FUNCTION(sglWeightivARB);
        SE_GET_FUNCTION(sglWeightfvARB);
        SE_GET_FUNCTION(sglWeightdvARB);
        SE_GET_FUNCTION(sglWeightubvARB);
        SE_GET_FUNCTION(sglWeightusvARB);
        SE_GET_FUNCTION(sglWeightuivARB);
        SE_GET_FUNCTION(sglWeightPointerARB);
        SE_GET_FUNCTION(sglVertexBlendARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 16) GL_ARB_matrix_palette */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbMatrixPalette = 0;

typedef void (STDCALL* PsglCurrentPaletteMatrixARB)(GLint);
typedef void (STDCALL* PsglMatrixIndexubvARB)(GLint, const GLubyte*);
typedef void (STDCALL* PsglMatrixIndexusvARB)(GLint, const GLushort*);
typedef void (STDCALL* PsglMatrixIndexuivARB)(GLint, const GLuint*);
typedef void (STDCALL* PsglMatrixIndexPointerARB)(GLint, GLenum, GLsizei,
    const GLvoid*);

static PsglCurrentPaletteMatrixARB sglCurrentPaletteMatrixARB = 0;
static PsglMatrixIndexubvARB sglMatrixIndexubvARB = 0;
static PsglMatrixIndexusvARB sglMatrixIndexusvARB = 0;
static PsglMatrixIndexuivARB sglMatrixIndexuivARB = 0;
static PsglMatrixIndexPointerARB sglMatrixIndexPointerARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glCurrentPaletteMatrixARB(GLint iIndex)
{
    SE_BODY_A1(sglCurrentPaletteMatrixARB, iIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glMatrixIndexubvARB(GLint iSize, const GLubyte* aucIndex)
{
    SE_BODY_A2(sglMatrixIndexubvARB, iSize, aucIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glMatrixIndexusvARB(GLint iSize, const GLushort* ausIndex)
{
    SE_BODY_A2(sglMatrixIndexusvARB, iSize, ausIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glMatrixIndexuivARB(GLint iSize, const GLuint* auiIndex)
{
    SE_BODY_A2(sglMatrixIndexuivARB, iSize, auiIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glMatrixIndexPointerARB(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglMatrixIndexPointerARB, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbMatrixPalette()
{
    if( SE_GL_SupportsExtension("GL_ARB_matrix_palette") )
    {
        SE_ExistsGlArbMatrixPalette = 1;

        SE_GET_FUNCTION(sglCurrentPaletteMatrixARB);
        SE_GET_FUNCTION(sglMatrixIndexubvARB);
        SE_GET_FUNCTION(sglMatrixIndexusvARB);
        SE_GET_FUNCTION(sglMatrixIndexuivARB);
        SE_GET_FUNCTION(sglMatrixIndexPointerARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 17) GL_ARB_texture_env_combine */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureEnvCombine = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureEnvCombine()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_env_combine") )
    {
        SE_ExistsGlArbTextureEnvCombine = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 18) GL_ARB_texture_env_crossbar */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureEnvCrossbar = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureEnvCrossbar()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_env_crossbar") )
    {
        SE_ExistsGlArbTextureEnvCrossbar = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 19) GL_ARB_texture_env_dot3 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureEnvDot3 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureEnvDot3()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_env_dot3") )
    {
        SE_ExistsGlArbTextureEnvDot3 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 21) GL_ARB_texture_mirrored_repeat */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureMirroredRepeat = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureMirroredRepeat()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_mirrored_repeat") )
    {
        SE_ExistsGlArbTextureMirroredRepeat = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 22) GL_ARB_depth_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbDepthTexture = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbDepthTexture()
{
    if( SE_GL_SupportsExtension("GL_ARB_depth_texture") )
    {
        SE_ExistsGlArbDepthTexture = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 23) GL_ARB_shadow */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbShadow = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbShadow()
{
    if( SE_GL_SupportsExtension("GL_ARB_shadow") )
    {
        SE_ExistsGlArbShadow = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 24) GL_ARB_shadow_ambient */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbShadowAmbient = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbShadowAmbient()
{
    if( SE_GL_SupportsExtension("GL_ARB_shadow_ambient") )
    {
        SE_ExistsGlArbShadowAmbient = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 25) GL_ARB_window_pos */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbWindowPos = 0;

static PsglWindowPos2d sglWindowPos2dARB = 0;
static PsglWindowPos2dv sglWindowPos2dvARB = 0;
static PsglWindowPos2f sglWindowPos2fARB = 0;
static PsglWindowPos2fv sglWindowPos2fvARB = 0;
static PsglWindowPos2i sglWindowPos2iARB = 0;
static PsglWindowPos2iv sglWindowPos2ivARB = 0;
static PsglWindowPos2s sglWindowPos2sARB = 0;
static PsglWindowPos2sv sglWindowPos2svARB = 0;
static PsglWindowPos3d sglWindowPos3dARB = 0;
static PsglWindowPos3dv sglWindowPos3dvARB = 0;
static PsglWindowPos3f sglWindowPos3fARB = 0;
static PsglWindowPos3fv sglWindowPos3fvARB = 0;
static PsglWindowPos3i sglWindowPos3iARB = 0;
static PsglWindowPos3iv sglWindowPos3ivARB = 0;
static PsglWindowPos3s sglWindowPos3sARB = 0;
static PsglWindowPos3sv sglWindowPos3svARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2dARB(GLdouble dX, GLdouble dY)
{
    SE_BODY_A2(sglWindowPos2dARB, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2dvARB(const GLdouble* adXY)
{
    SE_BODY_A1(sglWindowPos2dvARB, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2fARB(GLfloat fX, GLfloat fY)
{
    SE_BODY_A2(sglWindowPos2fARB, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2fvARB(const GLfloat* afXY)
{
    SE_BODY_A1(sglWindowPos2fvARB, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2iARB(GLint iX, GLint iY)
{
    SE_BODY_A2(sglWindowPos2iARB, iX, iY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2ivARB(const GLint* aiXY)
{
    SE_BODY_A1(sglWindowPos2ivARB, aiXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2sARB(GLshort sX, GLshort sY)
{
    SE_BODY_A2(sglWindowPos2sARB, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos2svARB(const GLshort* asXY)
{
    SE_BODY_A1(sglWindowPos2svARB, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3dARB(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_BODY_A3(sglWindowPos3dARB, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3dvARB(const GLdouble* adXYZ)
{
    SE_BODY_A1(sglWindowPos3dvARB, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3fARB(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_BODY_A3(sglWindowPos3fARB, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3fvARB(const GLfloat* afXYZ)
{
    SE_BODY_A1(sglWindowPos3fvARB, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3iARB(GLint iX, GLint iY, GLint iZ)
{
    SE_BODY_A3(sglWindowPos3iARB, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3ivARB(const GLint* aiXYZ)
{
    SE_BODY_A1(sglWindowPos3ivARB, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3sARB(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_BODY_A3(sglWindowPos3sARB, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glWindowPos3svARB(const GLshort* asXYZ)
{
    SE_BODY_A1(sglWindowPos3svARB, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbWindowPos()
{
    if( SE_GL_SupportsExtension("GL_ARB_window_pos") )
    {
        SE_ExistsGlArbWindowPos = 1;

        SE_GET_FUNCTION_C(sglWindowPos2d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos2sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglWindowPos3sv, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 26) GL_ARB_vertex_program */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbVertexProgram = 0;

typedef void (STDCALL* PsglBindProgramARB)(GLenum, GLuint);
typedef void (STDCALL* PsglDeleteProgramsARB)(GLsizei, const GLuint*);
typedef void (STDCALL* PsglGenProgramsARB)(GLsizei, GLuint*);
typedef void (STDCALL* PsglGetProgramEnvParameterdvARB)(GLenum, GLuint,
    GLdouble*);
typedef void (STDCALL* PsglGetProgramEnvParameterfvARB)(GLenum, GLuint,
    GLfloat*);
typedef void (STDCALL* PsglGetProgramLocalParameterdvARB)(GLenum, GLuint,
    GLdouble*);
typedef void (STDCALL* PsglGetProgramLocalParameterfvARB)(GLenum, GLuint,
    GLfloat*);
typedef void (STDCALL* PsglGetProgramStringARB)(GLenum, GLenum, GLvoid*);
typedef void (STDCALL* PsglProgramEnvParameter4dARB)(GLenum, GLuint,
    GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglProgramEnvParameter4dvARB)(GLenum, GLuint,
    const GLdouble*);
typedef void (STDCALL* PsglProgramEnvParameter4fARB)(GLenum, GLuint,
    GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglProgramEnvParameter4fvARB)(GLenum, GLuint,
    const GLfloat*);
typedef void (STDCALL* PsglProgramLocalParameter4dARB)(GLenum, GLuint,
    GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglProgramLocalParameter4dvARB)(GLenum, GLuint,
    const GLdouble*);
typedef void (STDCALL* PsglProgramLocalParameter4fARB)(GLenum, GLuint,
    GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglProgramLocalParameter4fvARB)(GLenum, GLuint,
    const GLfloat*);
typedef void (STDCALL* PsglProgramStringARB)(GLenum, GLenum, GLsizei,
    const GLvoid*);

static PsglBindProgramARB sglBindProgramARB = 0;
static PsglDeleteProgramsARB sglDeleteProgramsARB = 0;
static PsglGenProgramsARB sglGenProgramsARB = 0;
static PsglGetProgramEnvParameterdvARB sglGetProgramEnvParameterdvARB = 0;
static PsglGetProgramEnvParameterfvARB sglGetProgramEnvParameterfvARB = 0;
static PsglGetProgramLocalParameterdvARB sglGetProgramLocalParameterdvARB = 0;
static PsglGetProgramLocalParameterfvARB sglGetProgramLocalParameterfvARB = 0;
static PsglGetProgramStringARB sglGetProgramStringARB = 0;
static PsglProgramEnvParameter4dARB sglProgramEnvParameter4dARB = 0;
static PsglProgramEnvParameter4dvARB sglProgramEnvParameter4dvARB = 0;
static PsglProgramEnvParameter4fARB sglProgramEnvParameter4fARB = 0;
static PsglProgramEnvParameter4fvARB sglProgramEnvParameter4fvARB = 0;
static PsglProgramLocalParameter4dARB sglProgramLocalParameter4dARB = 0;
static PsglProgramLocalParameter4dvARB sglProgramLocalParameter4dvARB = 0;
static PsglProgramLocalParameter4fARB sglProgramLocalParameter4fARB = 0;
static PsglProgramLocalParameter4fvARB sglProgramLocalParameter4fvARB = 0;
static PsglProgramStringARB sglProgramStringARB = 0;

static PsglDisableVertexAttribArray sglDisableVertexAttribArrayARB = 0;
static PsglEnableVertexAttribArray sglEnableVertexAttribArrayARB = 0;
static PsglGetProgramiv sglGetProgramivARB = 0;
static PsglGetVertexAttribdv sglGetVertexAttribdvARB = 0;
static PsglGetVertexAttribfv sglGetVertexAttribfvARB = 0;
static PsglGetVertexAttribiv sglGetVertexAttribivARB = 0;
static PsglGetVertexAttribPointerv sglGetVertexAttribPointervARB = 0;
static PsglIsProgram sglIsProgramARB = 0;
static PsglVertexAttrib1d sglVertexAttrib1dARB = 0;
static PsglVertexAttrib1dv sglVertexAttrib1dvARB = 0;
static PsglVertexAttrib1f sglVertexAttrib1fARB = 0;
static PsglVertexAttrib1fv sglVertexAttrib1fvARB = 0;
static PsglVertexAttrib1s sglVertexAttrib1sARB = 0;
static PsglVertexAttrib1sv sglVertexAttrib1svARB = 0;
static PsglVertexAttrib2d sglVertexAttrib2dARB = 0;
static PsglVertexAttrib2dv sglVertexAttrib2dvARB = 0;
static PsglVertexAttrib2f sglVertexAttrib2fARB = 0;
static PsglVertexAttrib2fv sglVertexAttrib2fvARB = 0;
static PsglVertexAttrib2s sglVertexAttrib2sARB = 0;
static PsglVertexAttrib2sv sglVertexAttrib2svARB = 0;
static PsglVertexAttrib3d sglVertexAttrib3dARB = 0;
static PsglVertexAttrib3dv sglVertexAttrib3dvARB = 0;
static PsglVertexAttrib3f sglVertexAttrib3fARB = 0;
static PsglVertexAttrib3fv sglVertexAttrib3fvARB = 0;
static PsglVertexAttrib3s sglVertexAttrib3sARB = 0;
static PsglVertexAttrib3sv sglVertexAttrib3svARB = 0;
static PsglVertexAttrib4Nbv sglVertexAttrib4NbvARB = 0;
static PsglVertexAttrib4Niv sglVertexAttrib4NivARB = 0;
static PsglVertexAttrib4Nsv sglVertexAttrib4NsvARB = 0;
static PsglVertexAttrib4Nub sglVertexAttrib4NubARB = 0;
static PsglVertexAttrib4Nubv sglVertexAttrib4NubvARB = 0;
static PsglVertexAttrib4Nuiv sglVertexAttrib4NuivARB = 0;
static PsglVertexAttrib4Nusv sglVertexAttrib4NusvARB = 0;
static PsglVertexAttrib4bv sglVertexAttrib4bvARB = 0;
static PsglVertexAttrib4d sglVertexAttrib4dARB = 0;
static PsglVertexAttrib4dv sglVertexAttrib4dvARB = 0;
static PsglVertexAttrib4f sglVertexAttrib4fARB = 0;
static PsglVertexAttrib4fv sglVertexAttrib4fvARB = 0;
static PsglVertexAttrib4iv sglVertexAttrib4ivARB = 0;
static PsglVertexAttrib4s sglVertexAttrib4sARB = 0;
static PsglVertexAttrib4sv sglVertexAttrib4svARB = 0;
static PsglVertexAttrib4ubv sglVertexAttrib4ubvARB = 0;
static PsglVertexAttrib4uiv sglVertexAttrib4uivARB = 0;
static PsglVertexAttrib4usv sglVertexAttrib4usvARB = 0;
static PsglVertexAttribPointer sglVertexAttribPointerARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glBindProgramARB(GLenum eTarget, GLuint uiProgram)
{
    SE_BODY_A2(sglBindProgramARB, eTarget, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteProgramsARB(GLsizei iNumPrograms, const GLuint* auiPrograms)
{
    SE_BODY_A2(sglDeleteProgramsARB, iNumPrograms, auiPrograms);
}
/*--------------------------------------------------------------------------*/
void SE_glDisableVertexAttribArrayARB(GLuint uiIndex)
{
    SE_BODY_A1(sglDisableVertexAttribArrayARB, uiIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glEnableVertexAttribArrayARB(GLuint uiIndex)
{
    SE_BODY_A1(sglEnableVertexAttribArrayARB, uiIndex);
}
/*--------------------------------------------------------------------------*/
void SE_glGenProgramsARB(GLsizei iNumPrograms, GLuint* auiPrograms)
{
    SE_BODY_A2(sglGenProgramsARB, iNumPrograms, auiPrograms);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramivARB(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetProgramivARB, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramEnvParameterdvARB(GLenum eTarget, GLuint uiIndex, 
    GLdouble* adParam)
{
    SE_BODY_A3(sglGetProgramEnvParameterdvARB, eTarget, uiIndex, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramEnvParameterfvARB(GLenum eTarget, GLuint uiIndex, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetProgramEnvParameterfvARB, eTarget, uiIndex, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramLocalParameterdvARB(GLenum eTarget, GLuint uiIndex, 
    GLdouble* adParam)
{
    SE_BODY_A3(sglGetProgramLocalParameterdvARB, eTarget, uiIndex, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramLocalParameterfvARB(GLenum eTarget, GLuint uiIndex, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetProgramLocalParameterfvARB, eTarget, uiIndex, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetProgramStringARB(GLenum eTarget, GLenum ePName, 
    GLvoid* pvString)
{
    SE_BODY_A3(sglGetProgramStringARB, eTarget, ePName, pvString);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribdvARB(GLuint uiIndex, GLenum ePName, 
    GLdouble* adParam)
{
    SE_BODY_A3(sglGetVertexAttribdvARB, uiIndex, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribfvARB(GLuint uiIndex, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetVertexAttribfvARB, uiIndex, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribivARB(GLuint uiIndex, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetVertexAttribivARB, uiIndex, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetVertexAttribPointervARB(GLuint uiIndex, GLenum ePName, 
    GLvoid** apvPointer)
{
    SE_BODY_A3(sglGetVertexAttribPointervARB, uiIndex, ePName, apvPointer);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsProgramARB(GLuint uiProgram)
{
    SE_BODY_A1_RET(sglIsProgramARB, uiProgram, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramEnvParameter4dARB(GLenum eTarget, GLuint uiIndex, 
    GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW)
{
    SE_BODY_A6(sglProgramEnvParameter4dARB, eTarget, uiIndex, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramEnvParameter4dvARB(GLenum eTarget, GLuint uiIndex, 
    const GLdouble* adXYZW)
{
    SE_BODY_A3(sglProgramEnvParameter4dvARB, eTarget, uiIndex, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramEnvParameter4fARB(GLenum eTarget, GLuint uiIndex, 
    GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW)
{
    SE_BODY_A6(sglProgramEnvParameter4fARB, eTarget, uiIndex, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramEnvParameter4fvARB(GLenum eTarget, GLuint uiIndex, 
    const GLfloat* afXYZW)
{
    SE_BODY_A3(sglProgramEnvParameter4fvARB, eTarget, uiIndex, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramLocalParameter4dARB(GLenum eTarget, GLuint uiIndex, 
    GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW)
{
    SE_BODY_A6(sglProgramLocalParameter4dARB, eTarget, uiIndex, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramLocalParameter4dvARB(GLenum eTarget, GLuint uiIndex, 
    const GLdouble* adXYZW)
{
    SE_BODY_A3(sglProgramLocalParameter4dvARB, eTarget, uiIndex, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramLocalParameter4fARB(GLenum eTarget, GLuint uiIndex, 
    GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW)
{
    SE_BODY_A6(sglProgramLocalParameter4fARB, eTarget, uiIndex, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramLocalParameter4fvARB(GLenum eTarget, GLuint uiIndex, 
    const GLfloat* afXYZW)
{
    SE_BODY_A3(sglProgramLocalParameter4fvARB, eTarget, uiIndex, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glProgramStringARB(GLenum eTarget, GLenum eFormat, GLsizei iLength, 
    const GLvoid* pvString)
{
    SE_BODY_A4(sglProgramStringARB, eTarget, eFormat, iLength, pvString);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1dARB(GLuint uiIndex, GLdouble dX)
{
    SE_BODY_A2(sglVertexAttrib1dARB, uiIndex, dX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1dvARB(GLuint uiIndex, const GLdouble* pdX)
{
    SE_BODY_A2(sglVertexAttrib1dvARB, uiIndex, pdX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1fARB(GLuint uiIndex, GLfloat fX)
{
    SE_BODY_A2(sglVertexAttrib1fARB, uiIndex, fX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1fvARB(GLuint uiIndex, const GLfloat* pfX)
{
    SE_BODY_A2(sglVertexAttrib1fvARB, uiIndex, pfX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1sARB(GLuint uiIndex, GLshort sX)
{
    SE_BODY_A2(sglVertexAttrib1sARB, uiIndex, sX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib1svARB(GLuint uiIndex, const GLshort* psX)
{
    SE_BODY_A2(sglVertexAttrib1svARB, uiIndex, psX);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2dARB(GLuint uiIndex, GLdouble dX, GLdouble dY)
{
    SE_BODY_A3(sglVertexAttrib2dARB, uiIndex, dX, dY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2dvARB(GLuint uiIndex, const GLdouble* adXY)
{
    SE_BODY_A2(sglVertexAttrib2dvARB, uiIndex, adXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2fARB(GLuint uiIndex, GLfloat fX, GLfloat fY)
{
    SE_BODY_A3(sglVertexAttrib2fARB, uiIndex, fX, fY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2fvARB(GLuint uiIndex, const GLfloat* afXY)
{
    SE_BODY_A2(sglVertexAttrib2fvARB, uiIndex, afXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2sARB(GLuint uiIndex, GLshort sX, GLshort sY)
{
    SE_BODY_A3(sglVertexAttrib2sARB, uiIndex, sX, sY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib2svARB(GLuint uiIndex, const GLshort* asXY)
{
    SE_BODY_A2(sglVertexAttrib2svARB, uiIndex, asXY);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3dARB(GLuint uiIndex, GLdouble dX, GLdouble dY, 
    GLdouble dZ)
{
    SE_BODY_A4(sglVertexAttrib3dARB, uiIndex, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3dvARB(GLuint uiIndex, const GLdouble* adXYZ)
{
    SE_BODY_A2(sglVertexAttrib3dvARB, uiIndex, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3fARB(GLuint uiIndex, GLfloat fX, GLfloat fY, 
    GLfloat fZ)
{
    SE_BODY_A4(sglVertexAttrib3fARB, uiIndex, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3fvARB(GLuint uiIndex, const GLfloat* afXYZ)
{
    SE_BODY_A2(sglVertexAttrib3fvARB, uiIndex, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3sARB(GLuint uiIndex, GLshort sX, GLshort sY, 
    GLshort sZ)
{
    SE_BODY_A4(sglVertexAttrib3sARB, uiIndex, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib3svARB(GLuint uiIndex, const GLshort* asXYZ)
{
    SE_BODY_A2(sglVertexAttrib3svARB, uiIndex, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NbvARB(GLuint uiIndex, const GLbyte* acXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NbvARB, uiIndex, acXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NivARB(GLuint uiIndex, const GLint* aiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NivARB, uiIndex, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NsvARB(GLuint uiIndex, const GLshort* asXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NsvARB, uiIndex, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NubARB(GLuint uiIndex, GLubyte ucX, GLubyte ucY, 
    GLubyte ucZ, GLubyte ucW)
{
    SE_BODY_A5(sglVertexAttrib4NubARB, uiIndex, ucX, ucY, ucZ, ucW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NubvARB(GLuint uiIndex, const GLubyte* aucXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NubvARB, uiIndex, aucXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NuivARB(GLuint uiIndex, const GLuint* auiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NuivARB, uiIndex, auiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4NusvARB(GLuint uiIndex, const GLushort* ausXYZW)
{
    SE_BODY_A2(sglVertexAttrib4NusvARB, uiIndex, ausXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4bvARB(GLuint uiIndex, const GLbyte* acXYZW)
{
    SE_BODY_A2(sglVertexAttrib4bvARB, uiIndex, acXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4dARB(GLuint uiIndex, GLdouble dX, GLdouble dY, 
    GLdouble dZ, GLdouble dW)
{
    SE_BODY_A5(sglVertexAttrib4dARB, uiIndex, dX, dY, dZ, dW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4dvARB(GLuint uiIndex, const GLdouble* adXYZW)
{
    SE_BODY_A2(sglVertexAttrib4dvARB, uiIndex, adXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4fARB(GLuint uiIndex, GLfloat fX, GLfloat fY, 
    GLfloat fZ, GLfloat fW)
{
    SE_BODY_A5(sglVertexAttrib4fARB, uiIndex, fX, fY, fZ, fW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4fvARB(GLuint uiIndex, const GLfloat* afXYZW)
{
    SE_BODY_A2(sglVertexAttrib4fvARB, uiIndex, afXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4ivARB(GLuint uiIndex, const GLint* aiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4ivARB, uiIndex, aiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4sARB(GLuint uiIndex, GLshort sX, GLshort sY, 
    GLshort sZ, GLshort sW)
{
    SE_BODY_A5(sglVertexAttrib4sARB, uiIndex, sX, sY, sZ, sW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4svARB(GLuint uiIndex, const GLshort* asXYZW)
{
    SE_BODY_A2(sglVertexAttrib4svARB, uiIndex, asXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4ubvARB(GLuint uiIndex, const GLubyte* aucXYZW)
{
    SE_BODY_A2(sglVertexAttrib4ubvARB, uiIndex, aucXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4uivARB(GLuint uiIndex, const GLuint* auiXYZW)
{
    SE_BODY_A2(sglVertexAttrib4uivARB, uiIndex, auiXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttrib4usvARB(GLuint uiIndex, const GLushort* ausXYZW)
{
    SE_BODY_A2(sglVertexAttrib4usvARB, uiIndex, ausXYZW);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexAttribPointerARB(GLuint uiIndex, GLint iSize, GLenum eType, 
    GLboolean ucNormalized, GLsizei iStride, const GLvoid* pvPointer)
{
    SE_BODY_A6(sglVertexAttribPointerARB, uiIndex, iSize, eType, ucNormalized, 
        iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbVertexProgram()
{
    if( SE_GL_SupportsExtension("GL_ARB_vertex_program") )
    {
        SE_ExistsGlArbVertexProgram = 1;

        SE_GET_FUNCTION(sglBindProgramARB);
        SE_GET_FUNCTION(sglDeleteProgramsARB);
        SE_GET_FUNCTION(sglGenProgramsARB);
        SE_GET_FUNCTION(sglGetProgramEnvParameterdvARB);
        SE_GET_FUNCTION(sglGetProgramEnvParameterfvARB);
        SE_GET_FUNCTION(sglGetProgramLocalParameterdvARB);
        SE_GET_FUNCTION(sglGetProgramLocalParameterfvARB);
        SE_GET_FUNCTION(sglGetProgramStringARB);
        SE_GET_FUNCTION(sglProgramEnvParameter4dARB);
        SE_GET_FUNCTION(sglProgramEnvParameter4dvARB);
        SE_GET_FUNCTION(sglProgramEnvParameter4fARB);
        SE_GET_FUNCTION(sglProgramEnvParameter4fvARB);
        SE_GET_FUNCTION(sglProgramLocalParameter4dARB);
        SE_GET_FUNCTION(sglProgramLocalParameter4dvARB);
        SE_GET_FUNCTION(sglProgramLocalParameter4fARB);
        SE_GET_FUNCTION(sglProgramLocalParameter4fvARB);
        SE_GET_FUNCTION(sglProgramStringARB);

        SE_GET_FUNCTION_C(sglDisableVertexAttribArray, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglEnableVertexAttribArray, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetProgramiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetVertexAttribdv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetVertexAttribfv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetVertexAttribiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetVertexAttribPointerv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglIsProgram, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib1sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib2sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib3sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nbv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Niv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nsv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nub, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nubv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nuiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4Nusv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4bv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4d, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4dv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4s, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4sv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4ubv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4uiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttrib4usv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglVertexAttribPointer, ARB, SE_ARB_OVERRIDE);
    }
}/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 27) GL_ARB_fragment_program */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbFragmentProgram = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbFragmentProgram()
{
    if( SE_GL_SupportsExtension("GL_ARB_fragment_program") )
    {
        SE_ExistsGlArbFragmentProgram = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 28) GL_ARB_vertex_buffer_object */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbVertexBufferObject = 0;

static PsglBindBuffer sglBindBufferARB = 0;
static PsglDeleteBuffers sglDeleteBuffersARB = 0;
static PsglGenBuffers sglGenBuffersARB = 0;
static PsglIsBuffer sglIsBufferARB = 0;
static PsglBufferData sglBufferDataARB = 0;
static PsglBufferSubData sglBufferSubDataARB = 0;
static PsglGetBufferSubData sglGetBufferSubDataARB = 0;
static PsglMapBuffer sglMapBufferARB = 0;
static PsglUnmapBuffer sglUnmapBufferARB = 0;
static PsglGetBufferParameteriv sglGetBufferParameterivARB = 0;
static PsglGetBufferPointerv sglGetBufferPointervARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glBindBufferARB(GLenum eTarget, GLuint uiBuffer)
{
    SE_BODY_A2(sglBindBufferARB, eTarget, uiBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteBuffersARB(GLsizei iNumBuffers, const GLuint* auiBuffer)
{
    SE_BODY_A2(sglDeleteBuffersARB, iNumBuffers, auiBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glGenBuffersARB(GLsizei iNumBuffers, GLuint* auiBuffer)
{
    SE_BODY_A2(sglGenBuffersARB, iNumBuffers, auiBuffer);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsBufferARB(GLuint uiBuffer)
{
    SE_BODY_A1_RET(sglIsBufferARB, uiBuffer, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBufferDataARB(GLenum eTarget, GLsizeiptrARB piSize, 
    const GLvoid* pvData, GLenum eUsage)
{
    SE_BODY_A4(sglBufferDataARB, eTarget, piSize, pvData, eUsage);
}
/*--------------------------------------------------------------------------*/
void SE_glBufferSubDataARB(GLenum eTarget, GLintptrARB piOffset, 
    GLsizeiptrARB piSize, const GLvoid* pvData)
{
    SE_BODY_A4(sglBufferSubDataARB, eTarget, piOffset, piSize, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferSubDataARB(GLenum eTarget, GLintptrARB piOffset, 
    GLsizeiptrARB piSize, GLvoid* pvData)
{
    SE_BODY_A4(sglGetBufferSubDataARB, eTarget, piOffset, piSize, pvData);
}
/*--------------------------------------------------------------------------*/
GLvoid* SE_glMapBufferARB(GLenum eTarget, GLenum eAccess)
{
    SE_BODY_A2_RET(sglMapBufferARB, eTarget, eAccess, GLvoid*, 0);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glUnmapBufferARB(GLenum eTarget)
{
    SE_BODY_A1_RET(sglUnmapBufferARB, eTarget, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferParameterivARB(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetBufferParameterivARB, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetBufferPointervARB(GLenum eTarget, GLenum ePName, 
    GLvoid** apvParam)
{
    SE_BODY_A3(sglGetBufferPointervARB, eTarget, ePName, apvParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbVertexBufferObject()
{
    if( SE_GL_SupportsExtension("GL_ARB_vertex_buffer_object") )
    {
        SE_ExistsGlArbVertexBufferObject = 1;

        SE_GET_FUNCTION_C(sglBindBuffer, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglDeleteBuffers, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGenBuffers, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglIsBuffer, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglBufferData, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglBufferSubData, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetBufferSubData, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglMapBuffer, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUnmapBuffer, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetBufferParameteriv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetBufferPointerv, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 29) GL_ARB_occlusion_query */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbOcclusionQuery = 0;

static PsglGenQueries sglGenQueriesARB = 0;
static PsglDeleteQueries sglDeleteQueriesARB = 0;
static PsglIsQuery sglIsQueryARB = 0;
static PsglBeginQuery sglBeginQueryARB = 0;
static PsglEndQuery sglEndQueryARB = 0;
static PsglGetQueryiv sglGetQueryivARB = 0;
static PsglGetQueryObjectiv sglGetQueryObjectivARB = 0;
static PsglGetQueryObjectuiv sglGetQueryObjectuivARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glGenQueriesARB(GLsizei iNumQueries, GLuint* auiID)
{
    SE_BODY_A2(sglGenQueriesARB, iNumQueries, auiID);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteQueriesARB(GLsizei iNumQueries, const GLuint* auiID)
{
    SE_BODY_A2(sglDeleteQueriesARB, iNumQueries, auiID);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsQueryARB(GLuint uiID)
{
    SE_BODY_A1_RET(sglIsQueryARB, uiID, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBeginQueryARB(GLenum eTarget, GLuint uiID)
{
    SE_BODY_A2(sglBeginQueryARB, eTarget, uiID);
}
/*--------------------------------------------------------------------------*/
void SE_glEndQueryARB(GLenum eTarget)
{
    SE_BODY_A1(sglEndQueryARB, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryivARB(GLenum eTarget, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetQueryivARB, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryObjectivARB(GLuint uiID, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A3(sglGetQueryObjectivARB, uiID, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetQueryObjectuivARB(GLuint uiID, GLenum ePName, GLuint* auiParam)
{
    SE_BODY_A3(sglGetQueryObjectuivARB, uiID, ePName, auiParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbOcclusionQuery()
{
    if( SE_GL_SupportsExtension("GL_ARB_occlusion_query") )
    {
        SE_ExistsGlArbOcclusionQuery = 1;

        SE_GET_FUNCTION_C(sglGenQueries, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglDeleteQueries, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglIsQuery, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglBeginQuery, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglEndQuery, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetQueryiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetQueryObjectiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetQueryObjectuiv, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 29) GL_ARB_shader_objects */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbShaderObjects = 0;

typedef GLhandleARB (STDCALL* PsglGetHandleARB)(GLenum);
typedef void (STDCALL* PsglGetObjectParameterfvARB)(GLhandleARB, GLenum,
    GLfloat*);
typedef void (STDCALL* PsglGetObjectParameterivARB)(GLhandleARB, GLenum,
    GLint*);

typedef void (STDCALL* PsglAttachObject)(GLhandleARB, GLhandleARB);
typedef GLhandleARB (STDCALL* PsglCreateProgramObject)(void);
typedef GLhandleARB (STDCALL* PsglCreateShaderObject)(GLenum);
typedef void (STDCALL* PsglDeleteObject)(GLhandleARB);
typedef void (STDCALL* PsglDetachObject)(GLhandleARB, GLhandleARB);
typedef void (STDCALL* PsglGetInfoLog)(GLhandleARB, GLsizei, GLsizei*,
    GLcharARB*);
typedef void (STDCALL* PsglGetAttachedObjects)(GLhandleARB, GLsizei,
    GLsizei*, GLhandleARB*);
typedef void (STDCALL* PsglUseProgramObject)(GLhandleARB);

static PsglGetHandleARB sglGetHandleARB = 0;
static PsglGetObjectParameterfvARB sglGetObjectParameterfvARB = 0;
static PsglGetObjectParameterivARB sglGetObjectParameterivARB = 0;

static PsglAttachObject sglAttachObjectARB = 0;
static PsglCreateProgramObject sglCreateProgramObjectARB = 0;
static PsglCreateShaderObject sglCreateShaderObjectARB = 0;
static PsglDeleteObject sglDeleteObjectARB = 0;
static PsglDetachObject sglDetachObjectARB = 0;
static PsglGetInfoLog sglGetInfoLogARB = 0;
static PsglGetAttachedObjects sglGetAttachedObjectsARB = 0;
static PsglUseProgramObject sglUseProgramObjectARB = 0;

static PsglCompileShader sglCompileShaderARB = 0;
static PsglGetActiveUniform sglGetActiveUniformARB = 0;
static PsglGetUniformfv sglGetUniformfvARB = 0;
static PsglGetUniformiv sglGetUniformivARB = 0;
static PsglGetUniformLocation sglGetUniformLocationARB = 0;
static PsglGetShaderSource sglGetShaderSourceARB = 0;
static PsglLinkProgram sglLinkProgramARB = 0;
static PsglShaderSource sglShaderSourceARB = 0;
static PsglUniform1f sglUniform1fARB = 0;
static PsglUniform2f sglUniform2fARB = 0;
static PsglUniform3f sglUniform3fARB = 0;
static PsglUniform4f sglUniform4fARB = 0;
static PsglUniform1i sglUniform1iARB = 0;
static PsglUniform2i sglUniform2iARB = 0;
static PsglUniform3i sglUniform3iARB = 0;
static PsglUniform4i sglUniform4iARB = 0;
static PsglUniform1fv sglUniform1fvARB = 0;
static PsglUniform2fv sglUniform2fvARB = 0;
static PsglUniform3fv sglUniform3fvARB = 0;
static PsglUniform4fv sglUniform4fvARB = 0;
static PsglUniform1iv sglUniform1ivARB = 0;
static PsglUniform2iv sglUniform2ivARB = 0;
static PsglUniform3iv sglUniform3ivARB = 0;
static PsglUniform4iv sglUniform4ivARB = 0;
static PsglUniformMatrix2fv sglUniformMatrix2fvARB = 0;
static PsglUniformMatrix3fv sglUniformMatrix3fvARB = 0;
static PsglUniformMatrix4fv sglUniformMatrix4fvARB = 0;
static PsglValidateProgram sglValidateProgramARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glAttachObjectARB(GLhandleARB uiContainer, GLhandleARB uiObject)
{
    SE_BODY_A2(sglAttachObjectARB, uiContainer, uiObject);
}
/*--------------------------------------------------------------------------*/
void SE_glCompileShaderARB(GLhandleARB uiShader)
{
    SE_BODY_A1(sglCompileShaderARB, uiShader);
}
/*--------------------------------------------------------------------------*/
GLhandleARB SE_glCreateProgramObjectARB()
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A0_RET(sglCreateProgramObjectARB, GLhandleARB, 0);
}
/*--------------------------------------------------------------------------*/
GLhandleARB SE_glCreateShaderObjectARB(GLenum eType)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A1_RET(sglCreateShaderObjectARB, eType, GLhandleARB, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteObjectARB(GLhandleARB uiObject)
{
    SE_BODY_A1(sglDeleteObjectARB, uiObject);
}
/*--------------------------------------------------------------------------*/
void SE_glDetachObjectARB(GLhandleARB uiContainer, GLhandleARB uiObject)
{
    SE_BODY_A2(sglDetachObjectARB, uiContainer, uiObject);
}
/*--------------------------------------------------------------------------*/
void SE_glGetActiveUniformARB(GLhandleARB uiProgram, GLuint uiIndex, 
    GLsizei iMaxLength, GLsizei* piLength, GLint* piSize, GLenum* peType, 
    GLcharARB* acName)
{
    SE_BODY_A7(sglGetActiveUniformARB, uiProgram, uiIndex, iMaxLength, piLength, 
        piSize, peType, acName);
}
/*--------------------------------------------------------------------------*/
void SE_glGetAttachedObjectsARB(GLhandleARB uiContainer, GLsizei iMaxCount, 
    GLsizei* aiCount, GLhandleARB* auiObject)
{
    SE_BODY_A4(sglGetAttachedObjectsARB, uiContainer, iMaxCount, aiCount, 
        auiObject);
}
/*--------------------------------------------------------------------------*/
GLhandleARB SE_glGetHandleARB(GLenum ePName)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A1_RET(sglGetHandleARB, ePName, GLhandleARB, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetInfoLogARB(GLhandleARB uiObject, GLsizei iMaxLength, 
    GLsizei* piLength, GLcharARB* acInfoLog)
{
    SE_BODY_A4(sglGetInfoLogARB, uiObject, iMaxLength, piLength, acInfoLog);
}
/*--------------------------------------------------------------------------*/
void SE_glGetObjectParameterfvARB(GLhandleARB uiObject, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetObjectParameterfvARB, uiObject, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetObjectParameterivARB(GLhandleARB uiObject, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetObjectParameterivARB, uiObject, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetShaderSourceARB(GLhandleARB uiObject, GLsizei iMaxLength, 
    GLsizei* piLength, GLcharARB* acSource)
{
    SE_BODY_A4(sglGetShaderSourceARB, uiObject, iMaxLength, piLength, acSource);
}
/*--------------------------------------------------------------------------*/
GLint SE_glGetUniformLocationARB(GLhandleARB uiProgram, 
    const GLcharARB* acName)
{
    /* TO DO:  Check the default return value of 0 for correctness. */
    SE_BODY_A2_RET(sglGetUniformLocationARB, uiProgram, acName, GLint, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glGetUniformfvARB(GLhandleARB uiProgram, GLint iLocation, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetUniformfvARB, uiProgram, iLocation, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetUniformivARB(GLhandleARB uiProgram, GLint iLocation, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetUniformivARB, uiProgram, iLocation, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glLinkProgramARB(GLhandleARB uiProgram)
{
    SE_BODY_A1(sglLinkProgramARB, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glShaderSourceARB(GLhandleARB uiShader, GLsizei iCount, 
    const GLcharARB** aacString, const GLint* aiLength)
{
    SE_BODY_A4(sglShaderSourceARB, uiShader, iCount, aacString, aiLength);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1fARB(GLint iLocation, GLfloat fV0)
{
    SE_BODY_A2(sglUniform1fARB, iLocation, fV0);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2fARB(GLint iLocation, GLfloat fV0, GLfloat fV1)
{
    SE_BODY_A3(sglUniform2fARB, iLocation, fV0, fV1);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3fARB(GLint iLocation, GLfloat fV0, GLfloat fV1, 
    GLfloat fV2)
{
    SE_BODY_A4(sglUniform3fARB, iLocation, fV0, fV1, fV2);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4fARB(GLint iLocation, GLfloat fV0, GLfloat fV1, GLfloat fV2, 
    GLfloat fV3)
{
    SE_BODY_A5(sglUniform4fARB, iLocation, fV0, fV1, fV2, fV3);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1iARB(GLint iLocation, GLint iV0)
{
    SE_BODY_A2(sglUniform1iARB, iLocation, iV0);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2iARB(GLint iLocation, GLint iV0, GLint iV1)
{
    SE_BODY_A3(sglUniform2iARB, iLocation, iV0, iV1);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3iARB(GLint iLocation, GLint iV0, GLint iV1, GLint iV2)
{
    SE_BODY_A4(sglUniform3iARB, iLocation, iV0, iV1, iV2);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4iARB(GLint iLocation, GLint iV0, GLint iV1, GLint iV2, 
    GLint iV3)
{
    SE_BODY_A5(sglUniform4iARB, iLocation, iV0, iV1, iV2, iV3);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1fvARB(GLint iLocation, GLsizei iCount, 
    const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform1fvARB, iLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2fvARB(GLint iLocation, GLsizei iCount, 
    const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform2fvARB, iLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3fvARB(GLint iLocation, GLsizei iCount, 
    const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform3fvARB, iLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4fvARB(GLint iLocation, GLsizei iCount, 
    const GLfloat* afValue)
{
    SE_BODY_A3(sglUniform4fvARB, iLocation, iCount, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform1ivARB(GLint iLocation, GLsizei iCount, 
    const GLint* aiValue)
{
    SE_BODY_A3(sglUniform1ivARB, iLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform2ivARB(GLint iLocation, GLsizei iCount, 
    const GLint* aiValue)
{
    SE_BODY_A3(sglUniform2ivARB, iLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform3ivARB(GLint iLocation, GLsizei iCount, 
    const GLint* aiValue)
{
    SE_BODY_A3(sglUniform3ivARB, iLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniform4ivARB(GLint iLocation, GLsizei iCount, 
    const GLint* aiValue)
{
    SE_BODY_A3(sglUniform4ivARB, iLocation, iCount, aiValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix2fvARB(GLint iLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix2fvARB, iLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix3fvARB(GLint iLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix3fvARB, iLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUniformMatrix4fvARB(GLint iLocation, GLsizei iCount, 
    GLboolean ucTranspose, const GLfloat* afValue)
{
    SE_BODY_A4(sglUniformMatrix4fvARB, iLocation, iCount, ucTranspose, afValue);
}
/*--------------------------------------------------------------------------*/
void SE_glUseProgramObjectARB(GLhandleARB uiProgram)
{
    SE_BODY_A1(sglUseProgramObjectARB, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_glValidateProgramARB(GLhandleARB uiProgram)
{
    SE_BODY_A1(sglValidateProgramARB, uiProgram);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbShaderObjects()
{
    if( SE_GL_SupportsExtension("GL_ARB_shader_objects") )
    {
        SE_ExistsGlArbShaderObjects = 1;

        SE_GET_FUNCTION(sglGetHandleARB);
        SE_GET_FUNCTION(sglGetObjectParameterfvARB);
        SE_GET_FUNCTION(sglGetObjectParameterivARB);

        SE_GET_FUNCTION_CA(sglAttachObject, sglAttachShader, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglCreateProgramObject, sglCreateProgram, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglCreateShaderObject, sglCreateShader, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglDeleteObject, sglDeleteProgram, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglDeleteObject, sglDeleteShader, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglDetachObject, sglDetachShader, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglGetAttachedObjects, sglGetAttachedShaders, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglGetInfoLog, sglGetProgramInfoLog, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglGetInfoLog, sglGetShaderInfoLog, ARB, 
            SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_CA(sglUseProgramObject, sglUseProgram, ARB, 
            SE_ARB_OVERRIDE);

        SE_GET_FUNCTION_C(sglCompileShader, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetActiveUniform, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetShaderSource, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetUniformfv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetUniformiv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetUniformLocation, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglLinkProgram, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglShaderSource, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform1f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform2f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform3f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform4f, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform1i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform2i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform3i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform4i, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform1fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform2fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform3fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform4fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform1iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform2iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform3iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniform4iv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniformMatrix2fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniformMatrix3fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglUniformMatrix4fv, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglValidateProgram, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 31) GL_ARB_vertex_shader */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbVertexShader = 0;

static PsglBindAttribLocation sglBindAttribLocationARB = 0;
static PsglGetActiveAttrib sglGetActiveAttribARB = 0;
static PsglGetAttribLocation sglGetAttribLocationARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glBindAttribLocationARB(GLhandleARB uiProgram, GLuint uiIndex,
    const GLcharARB* acName)
{
    SE_BODY_A3(sglBindAttribLocationARB, uiProgram, uiIndex, acName);
}
/*--------------------------------------------------------------------------*/
void SE_glGetActiveAttribARB(GLhandleARB uiProgram, GLuint uiIndex,
    GLsizei iMaxLength, GLsizei* piLength, GLint* piSize, GLenum* peType,
    GLcharARB* acName)
{
    SE_BODY_A7(sglGetActiveAttribARB, uiProgram, uiIndex, iMaxLength, piLength,
        piSize, peType, acName);
}
/*--------------------------------------------------------------------------*/
GLint SE_glGetAttribLocationARB(GLhandleARB uiProgram,
    const GLcharARB* acName)
{
    /* 待实现:  检查返回值正确性 */
    SE_BODY_A2_RET(sglGetAttribLocationARB, uiProgram, acName, GLint, 0);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbVertexShader()
{
    if( SE_GL_SupportsExtension("GL_ARB_vertex_shader") )
    {
        SE_ExistsGlArbVertexShader = 1;

        SE_GET_FUNCTION_C(sglBindAttribLocation, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetActiveAttrib, ARB, SE_ARB_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetAttribLocation, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 32) GL_ARB_fragment_shader */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbFragmentShader = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbFragmentShader()
{
    if( SE_GL_SupportsExtension("GL_ARB_fragment_shader") )
    {
        SE_ExistsGlArbFragmentShader = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 33) GL_ARB_shading_language_100 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbShadingLanguage100 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbShadingLanguage100()
{
    if( SE_GL_SupportsExtension("GL_ARB_shading_language_100") )
    {
        SE_ExistsGlArbShadingLanguage100 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 34) GL_ARB_texture_non_power_of_two */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureNonpowerOfTwo = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureNonpowerOfTwo()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_non_power_of_two") )
    {
        SE_ExistsGlArbTextureNonpowerOfTwo = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 35) GL_ARB_point_sprite */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbPointSprite = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbPointSprite()
{
    if( SE_GL_SupportsExtension("GL_ARB_point_sprite") )
    {
        SE_ExistsGlArbPointSprite = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 36) GL_ARB_fragment_program_shadow */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbFragmentProgramShadow = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbFragmentProgramShadow()
{
    if( SE_GL_SupportsExtension("GL_ARB_fragment_program_shadow") )
    {
        SE_ExistsGlArbFragmentProgramShadow = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 37) GL_ARB_draw_buffers */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbDrawBuffers = 0;

static PsglDrawBuffers sglDrawBuffersARB = 0;
/*--------------------------------------------------------------------------*/
void SE_glDrawBuffersARB(GLsizei iNumBuffers, const GLenum* aeBuffer)
{
    SE_BODY_A2(sglDrawBuffersARB, iNumBuffers, aeBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbDrawBuffers()
{
    if( SE_GL_SupportsExtension("GL_ARB_draw_buffers") )
    {
        SE_ExistsGlArbDrawBuffers = 1;

        SE_GET_FUNCTION_C(sglDrawBuffers, ARB, SE_ARB_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 38) GL_ARB_texture_rectangle */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureRectangle = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureRectangle()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_rectangle") )
    {
        SE_ExistsGlArbTextureRectangle = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 39) GL_ARB_color_buffer_float */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbColorBufferFloat = 0;

typedef void (STDCALL* PsglClampColorARB)(GLenum, GLenum);

static PsglClampColorARB sglClampColorARB = 0;

/*--------------------------------------------------------------------------*/
void SE_glClampColorARB(GLenum eTarget, GLenum eClamp)
{
    SE_BODY_A2(sglClampColorARB, eTarget, eClamp);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlArbColorBufferFloat()
{
    if( SE_GL_SupportsExtension("GL_ARB_color_buffer_float") )
    {
        SE_ExistsGlArbColorBufferFloat = 1;

        SE_GET_FUNCTION(sglClampColorARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 40) GL_ARB_half_float_pixel */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbHalfFloatPixel = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbHalfFloatPixel()
{
    if( SE_GL_SupportsExtension("GL_ARB_half_float_pixel") )
    {
        SE_ExistsGlArbHalfFloatPixel = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 41) GL_ARB_texture_float */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbTextureFloat = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbTextureFloat()
{
    if( SE_GL_SupportsExtension("GL_ARB_texture_float") )
    {
        SE_ExistsGlArbTextureFloat = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 42) GL_ARB_pixel_buffer_object */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlArbPixelBufferObject = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlArbPixelBufferObject()
{
    if( SE_GL_SupportsExtension("GL_ARB_pixel_buffer_object") )
    {
        SE_ExistsGlArbPixelBufferObject = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** EXT Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 001) GL_EXT_abgr */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtABGR = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtABGR()
{
    if( SE_GL_SupportsExtension("GL_EXT_abgr") )
    {
        SE_ExistsGlExtABGR = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 002) GL_EXT_blend_color */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendColor = 0;

static PsglBlendColor sglBlendColorEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendColorEXT(GLclampf fRed, GLclampf fGreen, GLclampf fBlue,
    GLclampf fAlpha)
{
    SE_BODY_A4(sglBlendColorEXT, fRed, fGreen, fBlue, fAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendColor()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_color") )
    {
        SE_ExistsGlExtBlendColor = 1;

        SE_GET_FUNCTION_C(sglBlendColor, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 003) GL_EXT_polygon_offset */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPolygonOffset = 0;

typedef void (STDCALL* PsglPolygonOffsetEXT) (GLfloat, GLfloat);

static PsglPolygonOffsetEXT sglPolygonOffsetEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glPolygonOffsetEXT(GLfloat fScale, GLfloat fBias)
{
    SE_BODY_A2(sglPolygonOffsetEXT, fScale, fBias);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPolygonOffset()
{
    if( SE_GL_SupportsExtension("GL_EXT_polygon_offset") )
    {
        SE_ExistsGlExtPolygonOffset = 1;

        /* 这个函数是OpenGL 1.1的一部分, 因此不应该被覆盖 */
        SE_GET_FUNCTION(sglPolygonOffsetEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 004) GL_EXT_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTexture = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture") )
    {
        SE_ExistsGlExtTexture = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 006) GL_EXT_texture3D */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTexture3D = 0;

static PsglTexImage3D sglTexImage3DEXT = 0;
static PsglTexSubImage3D sglTexSubImage3DEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glTexImage3DEXT(GLenum eTarget, GLint iLevel, GLint iInternalFormat,
    GLsizei iWidth, GLsizei iHeight, GLsizei iDepth, GLint iBorder,
    GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A10(sglTexImage3DEXT, eTarget, iLevel, iInternalFormat, iWidth,
        iHeight, iDepth, iBorder, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glTexSubImage3DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLint iZOffset, GLsizei iWidth, GLsizei iHeight,
    GLsizei iDepth, GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A11(sglTexSubImage3DEXT, eTarget, iLevel, iXOffset, iYOffset, iZOffset,
        iWidth, iHeight, iDepth, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTexture3D()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture3D") )
    {
        SE_ExistsGlExtTexture3D = 1;

        SE_GET_FUNCTION_C(sglTexImage3D, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglTexSubImage3D, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 009) GL_EXT_subtexture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtSubtexture = 0;

typedef void (STDCALL* PsglTexSubImage1DEXT)(GLenum, GLint, GLint, GLsizei,
    GLenum, GLenum, const GLvoid*);
typedef void (STDCALL* PsglTexSubImage2DEXT)(GLenum, GLint, GLint, GLint,
    GLsizei, GLsizei, GLenum, GLenum, const GLvoid*);

static PsglTexSubImage1DEXT sglTexSubImage1DEXT = 0;
static PsglTexSubImage2DEXT sglTexSubImage2DEXT = 0;

/*--------------------------------------------------------------------------*/
void SE_glTexSubImage1DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A7(sglTexSubImage1DEXT, eTarget, iLevel, iXOffset, iWidth, eFormat,
        eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glTexSubImage2DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset,
    GLint iYOffset, GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A9(sglTexSubImage2DEXT, eTarget, iLevel, iXOffset, iYOffset, iWidth,
        iHeight, eFormat, eType, pvData);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtSubtexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_subtexture") )
    {
        SE_ExistsGlExtSubtexture = 1;

        /* 这些函数是OpenGL 1.1的一部分, 因此不应该被覆盖 */
        SE_GET_FUNCTION(sglTexSubImage1DEXT);
        SE_GET_FUNCTION(sglTexSubImage2DEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 010) GL_EXT_copy_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtCopyTexture = 0;

typedef void (STDCALL* PsglCopyTexImage1DEXT)(GLenum, GLint, GLenum, GLint,
    GLint, GLsizei, GLint);
typedef void (STDCALL* PsglCopyTexImage2DEXT)(GLenum, GLint, GLenum, GLint,
    GLint, GLsizei, GLsizei, GLint);
typedef void (STDCALL* PsglCopyTexSubImage1DEXT)(GLenum, GLint, GLint, GLint,
    GLint, GLsizei);
typedef void (STDCALL* PsglCopyTexSubImage2DEXT)(GLenum, GLint, GLint, GLint,
    GLint, GLint, GLsizei, GLsizei);

static PsglCopyTexImage1DEXT sglCopyTexImage1DEXT = 0;
static PsglCopyTexImage2DEXT sglCopyTexImage2DEXT = 0;
static PsglCopyTexSubImage1DEXT sglCopyTexSubImage1DEXT = 0;
static PsglCopyTexSubImage2DEXT sglCopyTexSubImage2DEXT = 0;
static PsglCopyTexSubImage3D sglCopyTexSubImage3DEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glCopyTexImage1DEXT(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth, GLint iBorder)
{
    SE_BODY_A7(sglCopyTexImage1DEXT, eTarget, iLevel, eInternalFormat, iX, iY, 
        iWidth, iBorder);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexImage2DEXT(GLenum eTarget, GLint iLevel, 
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth, 
    GLsizei iHeight, GLint iBorder)
{
    SE_BODY_A8(sglCopyTexImage2DEXT, eTarget, iLevel, eInternalFormat, iX, iY, 
        iWidth, iHeight, iBorder);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage1DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset, 
    GLint iX, GLint iY, GLsizei iWidth)
{
    SE_BODY_A6(sglCopyTexSubImage1DEXT, eTarget, iLevel, iXOffset, iX, iY, iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage2DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset, 
    GLint iYOffset, GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_BODY_A8(sglCopyTexSubImage2DEXT, eTarget, iLevel, iXOffset, iYOffset, iX, iY, 
        iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyTexSubImage3DEXT(GLenum eTarget, GLint iLevel, GLint iXOffset, 
    GLint iYOffset, GLint iZOffset, GLint iX, GLint iY, GLsizei iWidth, 
    GLsizei iHeight)
{
    SE_BODY_A9(sglCopyTexSubImage3DEXT, eTarget, iLevel, iXOffset, iYOffset, 
        iZOffset, iX, iY, iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtCopyTexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_copy_texture") )
    {
        SE_ExistsGlExtCopyTexture = 1;

        /* 这些函数是OpenGL 1.1的一部分, 因此不应该被覆盖 */
        SE_GET_FUNCTION(sglCopyTexImage1DEXT);
        SE_GET_FUNCTION(sglCopyTexImage2DEXT);
        SE_GET_FUNCTION(sglCopyTexSubImage1DEXT);
        SE_GET_FUNCTION(sglCopyTexSubImage2DEXT);

        SE_GET_FUNCTION_C(sglCopyTexSubImage3D, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 011) GL_EXT_histogram */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtHistogram = 0;

static PsglGetHistogram sglGetHistogramEXT = 0;
static PsglGetHistogramParameterfv sglGetHistogramParameterfvEXT = 0;
static PsglGetHistogramParameteriv sglGetHistogramParameterivEXT = 0;
static PsglGetMinmax sglGetMinmaxEXT = 0;
static PsglGetMinmaxParameterfv sglGetMinmaxParameterfvEXT = 0;
static PsglGetMinmaxParameteriv sglGetMinmaxParameterivEXT = 0;
static PsglHistogram sglHistogramEXT = 0;
static PsglMinmax sglMinmaxEXT = 0;
static PsglResetHistogram sglResetHistogramEXT = 0;
static PsglResetMinmax sglResetMinmaxEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glGetHistogramEXT(GLenum eTarget, GLboolean ucReset, GLenum eFormat, 
    GLenum eType, GLvoid* pvValues)
{
    SE_BODY_A5(sglGetHistogramEXT, eTarget, ucReset, eFormat, eType, pvValues);
}
/*--------------------------------------------------------------------------*/
void SE_glGetHistogramParameterfvEXT(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetHistogramParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetHistogramParameterivEXT(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetHistogramParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmaxEXT(GLenum eTarget, GLboolean ucReset, GLenum eFormat, 
    GLenum eType, GLvoid* pvValues)
{
    SE_BODY_A5(sglGetMinmaxEXT, eTarget, ucReset, eFormat, eType, pvValues);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmaxParameterfvEXT(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetMinmaxParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetMinmaxParameterivEXT(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetMinmaxParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glHistogramEXT(GLenum eTarget, GLsizei iWidth, GLenum eInternalFormat, 
    GLboolean ucSink)
{
    SE_BODY_A4(sglHistogramEXT, eTarget, iWidth, eInternalFormat, ucSink);
}
/*--------------------------------------------------------------------------*/
void SE_glMinmaxEXT(GLenum eTarget, GLenum eInternalFormat, GLboolean ucSink)
{
    SE_BODY_A3(sglMinmaxEXT, eTarget, eInternalFormat, ucSink);
}
/*--------------------------------------------------------------------------*/
void SE_glResetHistogramEXT(GLenum eTarget)
{
    SE_BODY_A1(sglResetHistogramEXT, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_glResetMinmaxEXT(GLenum eTarget)
{
    SE_BODY_A1(sglResetMinmaxEXT, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtHistogram()
{
    if( SE_GL_SupportsExtension("GL_EXT_histogram") )
    {
        SE_ExistsGlExtHistogram = 1;

        SE_GET_FUNCTION_C(sglGetHistogram, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetHistogramParameterfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetHistogramParameteriv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetMinmax, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetMinmaxParameterfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetMinmaxParameteriv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglHistogram, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglMinmax, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglResetHistogram, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglResetMinmax, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 012) GL_EXT_convolution */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtConvolution = 0;

static PsglConvolutionFilter1D sglConvolutionFilter1DEXT = 0;
static PsglConvolutionFilter2D sglConvolutionFilter2DEXT = 0;
static PsglConvolutionParameterf sglConvolutionParameterfEXT = 0;
static PsglConvolutionParameterfv sglConvolutionParameterfvEXT = 0;
static PsglConvolutionParameteri sglConvolutionParameteriEXT = 0;
static PsglConvolutionParameteriv sglConvolutionParameterivEXT = 0;
static PsglCopyConvolutionFilter1D sglCopyConvolutionFilter1DEXT = 0;
static PsglCopyConvolutionFilter2D sglCopyConvolutionFilter2DEXT = 0;
static PsglGetConvolutionFilter sglGetConvolutionFilterEXT = 0;
static PsglGetConvolutionParameterfv sglGetConvolutionParameterfvEXT = 0;
static PsglGetConvolutionParameteriv sglGetConvolutionParameterivEXT = 0;
static PsglGetSeparableFilter sglGetSeparableFilterEXT = 0;
static PsglSeparableFilter2D sglSeparableFilter2DEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glConvolutionFilter1DEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvImage)
{
    SE_BODY_A6(sglConvolutionFilter1DEXT, eTarget, eInternalFormat, iWidth, 
        eFormat, eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionFilter2DEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLsizei iHeight, GLenum eFormat, GLenum eType, 
    const GLvoid* pvImage)
{
    SE_BODY_A7(sglConvolutionFilter2DEXT, eTarget, eInternalFormat, iWidth, 
        iHeight, eFormat, eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameterfEXT(GLenum eTarget, GLenum ePName, 
    GLfloat fParam)
{
    SE_BODY_A3(sglConvolutionParameterfEXT, eTarget, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameterfvEXT(GLenum eTarget, GLenum ePName, 
    const GLfloat* afParam)
{
    SE_BODY_A3(sglConvolutionParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameteriEXT(GLenum eTarget, GLenum ePName, 
    GLint iParam)
{
    SE_BODY_A3(sglConvolutionParameteriEXT, eTarget, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glConvolutionParameterivEXT(GLenum eTarget, GLenum ePName, 
    const GLint* aiParam)
{
    SE_BODY_A3(sglConvolutionParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyConvolutionFilter1DEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLint iX, GLint iY, GLsizei iWidth)
{
    SE_BODY_A5(sglCopyConvolutionFilter1DEXT, eTarget, eInternalFormat, iX, iY, 
        iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyConvolutionFilter2DEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight)
{
    SE_BODY_A6(sglCopyConvolutionFilter2DEXT, eTarget, eInternalFormat, iX, iY, 
        iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionFilterEXT(GLenum eTarget, GLenum eFormat, 
    GLenum eType, GLvoid* pvImage)
{
    SE_BODY_A4(sglGetConvolutionFilterEXT, eTarget, eFormat, eType, pvImage);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionParameterfvEXT(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetConvolutionParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetConvolutionParameterivEXT(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetConvolutionParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetSeparableFilterEXT(GLenum eTarget, GLenum eFormat, GLenum eType, 
    GLvoid* pvRow, GLvoid* pvColumn, GLvoid* pvSpan)
{
    SE_BODY_A6(sglGetSeparableFilterEXT, eTarget, eFormat, eType, pvRow, pvColumn, 
        pvSpan);
}
/*--------------------------------------------------------------------------*/
void SE_glSeparableFilter2DEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLsizei iHeight, GLenum eFormat, GLenum eType, 
    const GLvoid* pvRow, const GLvoid* pvColumn)
{
    SE_BODY_A8(sglSeparableFilter2DEXT, eTarget, eInternalFormat, iWidth, iHeight, 
        eFormat, eType, pvRow, pvColumn);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtConvolution()
{
    if( SE_GL_SupportsExtension("GL_EXT_convolution") )
    {
        SE_ExistsGlExtConvolution = 1;

        SE_GET_FUNCTION_C(sglConvolutionFilter1D, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglConvolutionFilter2D, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglConvolutionParameterf, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglConvolutionParameterfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglConvolutionParameteri, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglConvolutionParameteriv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglCopyConvolutionFilter1D, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglCopyConvolutionFilter2D, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetConvolutionFilter, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetConvolutionParameterfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetConvolutionParameteriv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetSeparableFilter, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSeparableFilter2D, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 018) GL_EXT_cmyka */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtCMYKA = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtCMYKA()
{
    if( SE_GL_SupportsExtension("GL_EXT_cmyka") )
    {
        SE_ExistsGlExtCMYKA = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 020) GL_EXT_texture3D */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureObject = 0;

typedef GLboolean (STDCALL* PsglAreTexturesResidentEXT)(GLsizei,
    const GLuint*, GLboolean*);
typedef void (STDCALL* PsglBindTextureEXT)(GLenum, GLuint);
typedef void (STDCALL* PsglDeleteTexturesEXT)(GLsizei, const GLuint*);
typedef void (STDCALL* PsglGenTexturesEXT)(GLsizei, GLuint*);
typedef GLboolean (STDCALL* PsglIsTextureEXT)(GLuint);
typedef void (STDCALL* PsglPrioritizeTexturesEXT)(GLsizei, const GLuint*,
    const GLclampf*);

static PsglAreTexturesResidentEXT sglAreTexturesResidentEXT = 0;
static PsglBindTextureEXT sglBindTextureEXT = 0;
static PsglDeleteTexturesEXT sglDeleteTexturesEXT = 0;
static PsglGenTexturesEXT sglGenTexturesEXT = 0;
static PsglIsTextureEXT sglIsTextureEXT = 0;
static PsglPrioritizeTexturesEXT sglPrioritizeTexturesEXT = 0;

/*--------------------------------------------------------------------------*/
GLboolean SE_glAreTexturesResidentEXT(GLsizei iNumTextures, 
    const GLuint* auiTextures, GLboolean* aucResidences)
{
    SE_BODY_A3_RET(sglAreTexturesResidentEXT, iNumTextures, auiTextures, 
        aucResidences, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBindTextureEXT(GLenum eTarget, GLuint uiTexture)
{
    SE_BODY_A2(sglBindTextureEXT, eTarget, uiTexture);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteTexturesEXT(GLsizei iNumTextures, const GLuint* auiTextures)
{
    SE_BODY_A2(sglDeleteTexturesEXT, iNumTextures, auiTextures);
}
/*--------------------------------------------------------------------------*/
void SE_glGenTexturesEXT(GLsizei iNumTextures, GLuint* auiTexture)
{
    SE_BODY_A2(sglGenTexturesEXT, iNumTextures, auiTexture);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsTextureEXT(GLuint uiTexture)
{
    SE_BODY_A1_RET(sglIsTextureEXT, uiTexture, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glPrioritizeTexturesEXT(GLsizei iNumTextures, 
    const GLuint* auiTextures, const GLclampf* afPriorities)
{
    SE_BODY_A3(sglPrioritizeTexturesEXT, iNumTextures, auiTextures, 
        afPriorities);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureObject()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture3D") )
    {
        SE_ExistsGlExtTextureObject = 1;

        /* 这些函数是OpenGL 1.1的一部分, 因此不应该被覆盖 */
        SE_GET_FUNCTION(sglAreTexturesResidentEXT);
        SE_GET_FUNCTION(sglBindTextureEXT);
        SE_GET_FUNCTION(sglDeleteTexturesEXT);
        SE_GET_FUNCTION(sglGenTexturesEXT);
        SE_GET_FUNCTION(sglIsTextureEXT);
        SE_GET_FUNCTION(sglPrioritizeTexturesEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 023) GL_EXT_packed_pixels */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPackedPixels = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPackedPixels()
{
    if( SE_GL_SupportsExtension("GL_EXT_packed_pixels") )
    {
        SE_ExistsGlExtPackedPixels = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 027) GL_EXT_rescale_normal */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtRescaleNormal = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtRescaleNormal()
{
    if( SE_GL_SupportsExtension("GL_EXT_rescale_normal") )
    {
        SE_ExistsGlExtRescaleNormal = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 030) GL_EXT_vertex_array */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtVertexArray = 0;

typedef void (STDCALL* PsglArrayElementEXT)(GLint);
typedef void (STDCALL* PsglDrawArraysEXT)(GLenum, GLint, GLsizei);
typedef void (STDCALL* PsglGetPointervEXT)(GLenum, GLvoid**);
typedef void (STDCALL* PsglColorPointerEXT)(GLint, GLenum, GLsizei,
    GLsizei, const GLvoid*);
typedef void (STDCALL* PsglEdgeFlagPointerEXT)(GLsizei, GLsizei,
    const GLboolean*);
typedef void (STDCALL* PsglIndexPointerEXT)(GLenum, GLsizei, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglNormalPointerEXT)(GLenum, GLsizei, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglTexCoordPointerEXT)(GLint, GLenum, GLsizei,
    GLsizei, const GLvoid*);
typedef void (STDCALL* PsglVertexPointerEXT)(GLint, GLenum, GLsizei,
    GLsizei, const GLvoid*);

static PsglArrayElementEXT sglArrayElementEXT = 0;
static PsglDrawArraysEXT sglDrawArraysEXT = 0;
static PsglGetPointervEXT sglGetPointervEXT = 0;
static PsglColorPointerEXT sglColorPointerEXT = 0;
static PsglEdgeFlagPointerEXT sglEdgeFlagPointerEXT = 0;
static PsglIndexPointerEXT sglIndexPointerEXT = 0;
static PsglNormalPointerEXT sglNormalPointerEXT = 0;
static PsglTexCoordPointerEXT sglTexCoordPointerEXT = 0;
static PsglVertexPointerEXT sglVertexPointerEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glArrayElementEXT(GLint i)
{
    SE_BODY_A1(sglArrayElementEXT, i);
}
/*--------------------------------------------------------------------------*/
void SE_glColorPointerEXT(GLint iSize, GLenum eType, GLsizei iStride, 
    GLsizei iCount, const GLvoid* pvPointer)
{
    SE_BODY_A5(sglColorPointerEXT, iSize, eType, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glDrawArraysEXT(GLenum eMode, GLint iFirst, GLsizei iCount)
{
    SE_BODY_A3(sglDrawArraysEXT, eMode, iFirst, iCount);
}
/*--------------------------------------------------------------------------*/
void SE_glEdgeFlagPointerEXT(GLsizei iStride, GLsizei iCount, 
    const GLboolean* pvPointer)
{
    SE_BODY_A3(sglEdgeFlagPointerEXT, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glGetPointervEXT(GLenum ePName, GLvoid** apvParam)
{
    SE_BODY_A2(sglGetPointervEXT, ePName, apvParam);
}
/*--------------------------------------------------------------------------*/
void SE_glIndexPointerEXT(GLenum eType, GLsizei iStride, GLsizei iCount, 
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglIndexPointerEXT, eType, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glNormalPointerEXT(GLenum eType, GLsizei iStride, GLsizei iCount, 
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglNormalPointerEXT, eType, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glTexCoordPointerEXT(GLint iSize, GLenum eType, GLsizei iStride, 
    GLsizei iCount, const GLvoid* pvPointer)
{
    SE_BODY_A5(sglTexCoordPointerEXT, iSize, eType, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexPointerEXT(GLint iSize, GLenum eType, GLsizei iStride, 
    GLsizei iCount, const GLvoid* pvPointer)
{
    SE_BODY_A5(sglVertexPointerEXT, iSize, eType, iStride, iCount, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtVertexArray()
{
    if( SE_GL_SupportsExtension("GL_EXT_vertex_array") )
    {
        SE_ExistsGlExtVertexArray = 1;

        /* 这些函数是OpenGL 1.1的一部分, 因此不应该被覆盖 */
        SE_GET_FUNCTION(sglArrayElementEXT);
        SE_GET_FUNCTION(sglDrawArraysEXT);
        SE_GET_FUNCTION(sglGetPointervEXT);

        SE_GET_FUNCTION(sglColorPointerEXT);
        SE_GET_FUNCTION(sglEdgeFlagPointerEXT);
        SE_GET_FUNCTION(sglIndexPointerEXT);
        SE_GET_FUNCTION(sglNormalPointerEXT);
        SE_GET_FUNCTION(sglTexCoordPointerEXT);
        SE_GET_FUNCTION(sglVertexPointerEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 031) GL_EXT_misc_attribute */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtMiscAttribute = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtMiscAttribute()
{
    if( SE_GL_SupportsExtension("GL_EXT_misc_attribute") )
    {
        SE_ExistsGlExtMiscAttribute = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 037) GL_EXT_blend_minmax */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendMinMax = 0;

static PsglBlendEquation sglBlendEquationEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendEquationEXT(GLenum eMode)
{
    SE_BODY_A1(sglBlendEquationEXT, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendMinMax()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_minmax") )
    {
        SE_ExistsGlExtBlendMinMax = 1;

        SE_GET_FUNCTION_C(sglBlendEquation, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 038) GL_EXT_blend_subtract */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendSubtract = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendSubtract()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_subtract") )
    {
        SE_ExistsGlExtBlendSubtract = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 039) GL_EXT_blend_logic_op */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendLogicOp = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendLogicOp()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_logic_op") )
    {
        SE_ExistsGlExtBlendLogicOp = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 054) GL_EXT_point_parameters */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPointParameters = 0;

static PsglPointParameterf sglPointParameterfEXT = 0;
static PsglPointParameterfv sglPointParameterfvEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glPointParameterfEXT(GLenum ePName, GLfloat fParam)
{
    SE_BODY_A2(sglPointParameterfEXT, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPointParameterfvEXT(GLenum ePName, const GLfloat* afParam)
{
    SE_BODY_A2(sglPointParameterfvEXT, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPointParameters()
{
    if( SE_GL_SupportsExtension("GL_EXT_point_parameters") )
    {
        SE_ExistsGlExtPointParameters = 1;

        SE_GET_FUNCTION_C(sglPointParameterf, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglPointParameterfv, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 074) GL_EXT_color_subtable */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtColorSubtable = 0;

static PsglColorSubTable sglColorSubTableEXT = 0;
static PsglCopyColorSubTable sglCopyColorSubTableEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glColorSubTableEXT(GLenum eTarget, GLsizei iStart, GLsizei iCount,
    GLenum eFormat, GLenum eType, const GLvoid* pvData)
{
    SE_BODY_A6(sglColorSubTableEXT, eTarget, iStart, iCount, eFormat, eType,
        pvData);
}
/*--------------------------------------------------------------------------*/
void SE_glCopyColorSubTableEXT(GLenum eTarget, GLsizei iStart, GLint iX,
    GLint iY, GLsizei iWidth)
{
    SE_BODY_A5(sglCopyColorSubTableEXT, eTarget, iStart, iX, iY, iWidth);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtColorSubtable()
{
    if( SE_GL_SupportsExtension("GL_EXT_color_subtable") )
    {
        SE_ExistsGlExtColorSubtable = 1;

        SE_GET_FUNCTION_C(sglColorSubTable, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglCopyColorSubTable, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 078) GL_EXT_paletted_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPalettedTexture = 0;

static PsglColorTable sglColorTableEXT = 0;
static PsglGetColorTable sglGetColorTableEXT = 0;
static PsglGetColorTableParameterfv sglGetColorTableParameterfvEXT = 0;
static PsglGetColorTableParameteriv sglGetColorTableParameterivEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glColorTableEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvTable)
{
    SE_BODY_A6(sglColorTableEXT, eTarget, eInternalFormat, iWidth, eFormat, eType, 
        pvTable);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTableEXT(GLenum eTarget, GLenum eFormat, GLenum eType, 
    GLvoid* pvTable)
{
    SE_BODY_A4(sglGetColorTableEXT, eTarget, eFormat, eType, pvTable);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTableParameterfvEXT(GLenum eTarget, GLenum ePName, 
    GLfloat* afParam)
{
    SE_BODY_A3(sglGetColorTableParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGetColorTableParameterivEXT(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetColorTableParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPalettedTexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_paletted_texture") )
    {
        SE_ExistsGlExtPalettedTexture = 1;

        SE_GET_FUNCTION_C(sglColorTable, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetColorTable, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetColorTableParameterfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglGetColorTableParameteriv, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 079) GL_EXT_clip_volume_hint */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtClipVolumeHint = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtClipVolumeHint()
{
    if( SE_GL_SupportsExtension("GL_EXT_clip_volume_hint") )
    {
        SE_ExistsGlExtClipVolumeHint = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 093) GL_EXT_index_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtIndexTexture = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtIndexTexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_index_texture") )
    {
        SE_ExistsGlExtIndexTexture = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 094) GL_EXT_index_material */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtIndexMaterial = 0;

typedef void (STDCALL* PsglIndexMaterialEXT)(GLenum, GLenum);

static PsglIndexMaterialEXT sglIndexMaterialEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glIndexMaterialEXT(GLenum eFace, GLenum eMode)
{
    SE_BODY_A2(sglIndexMaterialEXT, eFace, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtIndexMaterial()
{
    if( SE_GL_SupportsExtension("GL_EXT_index_material") )
    {
        SE_ExistsGlExtIndexMaterial = 1;

        SE_GET_FUNCTION(sglIndexMaterialEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 095) GL_EXT_index_func */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtIndexFunc = 0;

typedef void (STDCALL* PsglIndexFuncEXT)(GLenum, GLclampf);

static PsglIndexFuncEXT sglIndexFuncEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glIndexFuncEXT(GLenum eFunction, GLclampf fReference)
{
    SE_BODY_A2(sglIndexFuncEXT, eFunction, fReference);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtIndexFunc()
{
    if( SE_GL_SupportsExtension("GL_EXT_index_func") )
    {
        SE_ExistsGlExtIndexFunc = 1;

        SE_GET_FUNCTION(sglIndexFuncEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 096) GL_EXT_index_array_formats */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtIndexArrayFormats = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtIndexArrayFormats()
{
    if( SE_GL_SupportsExtension("GL_EXT_index_array_formats") )
    {
        SE_ExistsGlExtIndexArrayFormats = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 097) GL_EXT_compiled_vertex_array */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtCompiledVertexArray = 0;

typedef void (STDCALL* PsglLockArraysEXT)(GLint, GLsizei);
typedef void (STDCALL* PsglUnlockArraysEXT)(void);

static PsglLockArraysEXT sglLockArraysEXT = 0;
static PsglUnlockArraysEXT sglUnlockArraysEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glLockArraysEXT(GLint iFirst, GLsizei iCount)
{
    SE_BODY_A2(sglLockArraysEXT, iFirst, iCount);
}
/*--------------------------------------------------------------------------*/
void SE_glUnlockArraysEXT()
{
    SE_BODY_A0(sglUnlockArraysEXT);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtCompiledVertexArray()
{
    if( SE_GL_SupportsExtension("GL_EXT_compiled_vertex_array") )
    {
        SE_ExistsGlExtCompiledVertexArray = 1;

        SE_GET_FUNCTION(sglLockArraysEXT);
        SE_GET_FUNCTION(sglUnlockArraysEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 098) GL_EXT_cull_vertex */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtCullVertex = 0;

typedef void (STDCALL* PsglCullParameterdvEXT)(GLenum, GLdouble*);
typedef void (STDCALL* PsglCullParameterfvEXT)(GLenum, GLfloat*);

static PsglCullParameterdvEXT sglCullParameterdvEXT = 0;
static PsglCullParameterfvEXT sglCullParameterfvEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glCullParameterdvEXT(GLenum ePName, GLdouble* adParam)
{
    SE_BODY_A2(sglCullParameterdvEXT, ePName, adParam);
}
/*--------------------------------------------------------------------------*/
void SE_glCullParameterfvEXT(GLenum ePName, GLfloat* afParam)
{
    SE_BODY_A2(sglCullParameterfvEXT, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtCullVertex()
{
    if( SE_GL_SupportsExtension("GL_EXT_cull_vertex") )
    {
        SE_ExistsGlExtCullVertex = 1;

        SE_GET_FUNCTION(sglCullParameterdvEXT);
        SE_GET_FUNCTION(sglCullParameterfvEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 112) GL_EXT_draw_range_elements */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtDrawRangeElements = 0;

static PsglDrawRangeElements sglDrawRangeElementsEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glDrawRangeElementsEXT(GLenum eMode, GLuint uiStart, GLuint uiEnd,
    GLsizei iCount, GLenum eType, const GLvoid* pvIndices)
{
    SE_BODY_A6(sglDrawRangeElementsEXT, eMode, uiStart, uiEnd, iCount, eType,
        pvIndices);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtDrawRangeElements()
{
    if( SE_GL_SupportsExtension("GL_EXT_draw_range_elements") )
    {
        SE_ExistsGlExtDrawRangeElements = 1;

        SE_GET_FUNCTION_C(sglDrawRangeElements, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 117) GL_EXT_light_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtLightTexture = 0;

typedef void (STDCALL* PsglApplyTextureEXT)(GLenum);
typedef void (STDCALL* PsglTextureLightEXT)(GLenum);
typedef void (STDCALL* PsglTextureMaterialEXT)(GLenum, GLenum);

static PsglApplyTextureEXT sglApplyTextureEXT = 0;
static PsglTextureLightEXT sglTextureLightEXT = 0;
static PsglTextureMaterialEXT sglTextureMaterialEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glApplyTextureEXT(GLenum eMode)
{
    SE_BODY_A1(sglApplyTextureEXT, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_glTextureLightEXT(GLenum ePName)
{
    SE_BODY_A1(sglTextureLightEXT, ePName);
}
/*--------------------------------------------------------------------------*/
void SE_glTextureMaterialEXT(GLenum eFace, GLenum eMode)
{
    SE_BODY_A2(sglTextureMaterialEXT,eFace,eMode);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtLightTexture()
{
    if( SE_GL_SupportsExtension("GL_EXT_light_texture") )
    {
        SE_ExistsGlExtLightTexture = 1;

        SE_GET_FUNCTION(sglApplyTextureEXT);
        SE_GET_FUNCTION(sglTextureLightEXT);
        SE_GET_FUNCTION(sglTextureMaterialEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 129) GL_EXT_bgra */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBGRA = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBGRA()
{
    if( SE_GL_SupportsExtension("GL_EXT_bgra") )
    {
        SE_ExistsGlExtBGRA = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 138) GL_EXT_pixel_transform */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPixelTransform = 0;

typedef void (STDCALL* PsglPixelTransformParameteriEXT)(GLenum, GLenum,
    GLint);
typedef void (STDCALL* PsglPixelTransformParameterfEXT)(GLenum, GLenum,
    GLfloat);
typedef void (STDCALL* PsglPixelTransformParameterivEXT)(GLenum, GLenum,
    const GLint*);
typedef void (STDCALL* PsglPixelTransformParameterfvEXT)(GLenum, GLenum,
    const GLfloat*);

static PsglPixelTransformParameteriEXT sglPixelTransformParameteriEXT = 0;
static PsglPixelTransformParameterfEXT sglPixelTransformParameterfEXT = 0;
static PsglPixelTransformParameterivEXT sglPixelTransformParameterivEXT = 0;
static PsglPixelTransformParameterfvEXT sglPixelTransformParameterfvEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glPixelTransformParameteriEXT(GLenum eTarget, GLenum ePName, 
    GLint iParam)
{
    SE_BODY_A3(sglPixelTransformParameteriEXT, eTarget, ePName, iParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelTransformParameterfEXT(GLenum eTarget, GLenum ePName, 
    GLfloat fParam)
{
    SE_BODY_A3(sglPixelTransformParameterfEXT, eTarget, ePName, fParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelTransformParameterivEXT(GLenum eTarget, GLenum ePName, 
    const GLint* aiParam)
{
    SE_BODY_A3(sglPixelTransformParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glPixelTransformParameterfvEXT(GLenum eTarget, GLenum ePName, 
    const GLfloat* afParam)
{
    SE_BODY_A3(sglPixelTransformParameterfvEXT, eTarget, ePName, afParam);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPixelTransform ()
{
    if( SE_GL_SupportsExtension("GL_EXT_pixel_transform") )
    {
        SE_ExistsGlExtPixelTransform = 1;

        SE_GET_FUNCTION(sglPixelTransformParameteriEXT);
        SE_GET_FUNCTION(sglPixelTransformParameterfEXT);
        SE_GET_FUNCTION(sglPixelTransformParameterivEXT);
        SE_GET_FUNCTION(sglPixelTransformParameterfvEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 139) GL_EXT_pixel_transform_color_table */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPixelTransformColorTable = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPixelTransformColorTable()
{
    if( SE_GL_SupportsExtension("GL_EXT_pixel_transform_color_table") )
    {
        SE_ExistsGlExtPixelTransformColorTable = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 141) GL_EXT_shared_texture_palette */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtSharedTexturePalette = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtSharedTexturePalette()
{
    if( SE_GL_SupportsExtension("GL_EXT_shared_texture_palette") )
    {
        SE_ExistsGlExtSharedTexturePalette = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 144) GL_EXT_separate_specular_color */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtSeparateSpecularColor = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtSeparateSpecularColor()
{
    if( SE_GL_SupportsExtension("GL_EXT_separate_specular_color") )
    {
        SE_ExistsGlExtSeparateSpecularColor = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 145) GL_EXT_secondary_color */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtSecondaryColor = 0;

static PsglSecondaryColor3b sglSecondaryColor3bEXT = 0;
static PsglSecondaryColor3bv sglSecondaryColor3bvEXT = 0;
static PsglSecondaryColor3d sglSecondaryColor3dEXT = 0;
static PsglSecondaryColor3dv sglSecondaryColor3dvEXT = 0;
static PsglSecondaryColor3f sglSecondaryColor3fEXT = 0;
static PsglSecondaryColor3fv sglSecondaryColor3fvEXT = 0;
static PsglSecondaryColor3i sglSecondaryColor3iEXT = 0;
static PsglSecondaryColor3iv sglSecondaryColor3ivEXT = 0;
static PsglSecondaryColor3s sglSecondaryColor3sEXT = 0;
static PsglSecondaryColor3sv sglSecondaryColor3svEXT = 0;
static PsglSecondaryColor3ub sglSecondaryColor3ubEXT = 0;
static PsglSecondaryColor3ubv sglSecondaryColor3ubvEXT = 0;
static PsglSecondaryColor3ui sglSecondaryColor3uiEXT = 0;
static PsglSecondaryColor3uiv sglSecondaryColor3uivEXT = 0;
static PsglSecondaryColor3us sglSecondaryColor3usEXT = 0;
static PsglSecondaryColor3usv sglSecondaryColor3usvEXT = 0;
static PsglSecondaryColorPointer sglSecondaryColorPointerEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3bEXT(GLbyte cRed, GLbyte cGreen, GLbyte cBlue)
{
    SE_BODY_A3(sglSecondaryColor3bEXT, cRed, cGreen, cBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3bvEXT(const GLbyte* acRGB)
{
    SE_BODY_A1(sglSecondaryColor3bvEXT, acRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3dEXT(GLdouble dRed, GLdouble dGreen, GLdouble dBlue)
{
    SE_BODY_A3(sglSecondaryColor3dEXT, dRed, dGreen, dBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3dvEXT(const GLdouble* adRGB)
{
    SE_BODY_A1(sglSecondaryColor3dvEXT, adRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3fEXT(GLfloat fRed, GLfloat fGreen, GLfloat fBlue)
{
    SE_BODY_A3(sglSecondaryColor3fEXT, fRed, fGreen, fBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3fvEXT(const GLfloat* afRGB)
{
    SE_BODY_A1(sglSecondaryColor3fvEXT, afRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3iEXT(GLint iRed, GLint iGreen, GLint iBlue)
{
    SE_BODY_A3(sglSecondaryColor3iEXT, iRed, iGreen, iBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ivEXT(const GLint* aiRGB)
{
    SE_BODY_A1(sglSecondaryColor3ivEXT, aiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3sEXT(GLshort sRed, GLshort sGreen, GLshort sBlue)
{
    SE_BODY_A3(sglSecondaryColor3sEXT, sRed, sGreen, sBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3svEXT(const GLshort* asRGB)
{
    SE_BODY_A1(sglSecondaryColor3svEXT, asRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ubEXT(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue)
{
    SE_BODY_A3(sglSecondaryColor3ubEXT, ucRed, ucGreen, ucBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3ubvEXT(const GLubyte* aucRGB)
{
    SE_BODY_A1(sglSecondaryColor3ubvEXT, aucRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3uiEXT(GLuint uiRed, GLuint uiGreen, GLuint uiBlue)
{
    SE_BODY_A3(sglSecondaryColor3uiEXT, uiRed, uiGreen, uiBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3uivEXT(const GLuint* auiRGB)
{
    SE_BODY_A1(sglSecondaryColor3uivEXT, auiRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3usEXT(GLushort usRed, GLushort usGreen, 
    GLushort usBlue)
{
    SE_BODY_A3(sglSecondaryColor3usEXT, usRed, usGreen, usBlue);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColor3usvEXT(const GLushort* ausRGB)
{
    SE_BODY_A1(sglSecondaryColor3usvEXT, ausRGB);
}
/*--------------------------------------------------------------------------*/
void SE_glSecondaryColorPointerEXT(GLint iSize, GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A4(sglSecondaryColorPointerEXT, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtSecondaryColor()
{
    if( SE_GL_SupportsExtension("GL_EXT_secondary_color") )
    {
        SE_ExistsGlExtSecondaryColor = 1;

        SE_GET_FUNCTION_C(sglSecondaryColor3b, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3bv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3d, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3dv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3f, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3fv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3i, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3iv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3s, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3sv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3ub, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3ubv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3ui, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3uiv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3us, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColor3usv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglSecondaryColorPointer, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 147) GL_EXT_texture_perturb_normal */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTexturePerturbNormal = 0;

typedef void (STDCALL* PsglTextureNormalEXT)(GLenum);

static PsglTextureNormalEXT sglTextureNormalEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glTextureNormalEXT(GLenum eMode)
{
    SE_BODY_A1(sglTextureNormalEXT, eMode);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTexturePerturbNormal()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_perturb_normal") )
    {
        SE_ExistsGlExtTexturePerturbNormal = 1;

        SE_GET_FUNCTION(sglTextureNormalEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 148) GL_EXT_multi_draw_arrays */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtMultidrawArrays = 0;

static PsglMultiDrawArrays sglMultiDrawArraysEXT = 0;
static PsglMultiDrawElements sglMultiDrawElementsEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glMultiDrawArraysEXT(GLenum eMode, GLint* aiFirst, GLsizei* aiCount,
    GLsizei iPrimitiveCount)
{
    SE_BODY_A4(sglMultiDrawArraysEXT, eMode, aiFirst, aiCount, iPrimitiveCount);
}
/*--------------------------------------------------------------------------*/
void SE_glMultiDrawElementsEXT(GLenum eMode, const GLsizei* aiCount,
    GLenum eType, const GLvoid** apvIndices, GLsizei iPrimitiveCount)
{
    SE_BODY_A5(sglMultiDrawElementsEXT, eMode, aiCount, eType, apvIndices, 
        iPrimitiveCount);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtMultidrawArrays()
{
    if( SE_GL_SupportsExtension("GL_EXT_multi_draw_arrays") )
    {
        SE_ExistsGlExtMultidrawArrays = 1;

        SE_GET_FUNCTION_C(sglMultiDrawArrays, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglMultiDrawElements, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 149) GL_EXT_fog_coord */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtFogCoord = 0;

static PsglFogCoordf sglFogCoordfEXT = 0;
static PsglFogCoordfv sglFogCoordfvEXT = 0;
static PsglFogCoordd sglFogCoorddEXT = 0;
static PsglFogCoorddv sglFogCoorddvEXT = 0;
static PsglFogCoordPointer sglFogCoordPointerEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glFogCoorddEXT(GLdouble dCoord)
{
    SE_BODY_A1(sglFogCoorddEXT, dCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoorddvEXT(const GLdouble* pdCoord)
{
    SE_BODY_A1(sglFogCoorddvEXT, pdCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordfEXT(GLfloat fCoord)
{
    SE_BODY_A1(sglFogCoordfEXT, fCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordfvEXT(const GLfloat* pfCoord)
{
    SE_BODY_A1(sglFogCoordfvEXT, pfCoord);
}
/*--------------------------------------------------------------------------*/
void SE_glFogCoordPointerEXT(GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A3(sglFogCoordPointerEXT, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtFogCoord()
{
    if( SE_GL_SupportsExtension("GL_EXT_fog_coord") )
    {
        SE_ExistsGlExtFogCoord = 1;

        SE_GET_FUNCTION_C(sglFogCoordf, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglFogCoordfv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglFogCoordd, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglFogCoorddv, EXT, SE_EXT_OVERRIDE);
        SE_GET_FUNCTION_C(sglFogCoordPointer, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 156) GL_EXT_coordinate_frame */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtCoordinateFrame = 0;

typedef void (STDCALL* PsglTangent3bEXT)(GLbyte, GLbyte, GLbyte);
typedef void (STDCALL* PsglTangent3bvEXT)(const GLbyte*);
typedef void (STDCALL* PsglTangent3dEXT)(GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglTangent3dvEXT)(const GLdouble*);
typedef void (STDCALL* PsglTangent3fEXT)(GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglTangent3fvEXT)(const GLfloat*);
typedef void (STDCALL* PsglTangent3iEXT)(GLint, GLint, GLint);
typedef void (STDCALL* PsglTangent3ivEXT)(const GLint*);
typedef void (STDCALL* PsglTangent3sEXT)(GLshort, GLshort, GLshort);
typedef void (STDCALL* PsglTangent3svEXT)(const GLshort*);
typedef void (STDCALL* PsglBinormal3bEXT)(GLbyte, GLbyte, GLbyte);
typedef void (STDCALL* PsglBinormal3bvEXT)(const GLbyte*);
typedef void (STDCALL* PsglBinormal3dEXT)(GLdouble, GLdouble, GLdouble);
typedef void (STDCALL* PsglBinormal3dvEXT)(const GLdouble*);
typedef void (STDCALL* PsglBinormal3fEXT)(GLfloat, GLfloat, GLfloat);
typedef void (STDCALL* PsglBinormal3fvEXT)(const GLfloat*);
typedef void (STDCALL* PsglBinormal3iEXT)(GLint, GLint, GLint);
typedef void (STDCALL* PsglBinormal3ivEXT)(const GLint*);
typedef void (STDCALL* PsglBinormal3sEXT)(GLshort, GLshort, GLshort);
typedef void (STDCALL* PsglBinormal3svEXT)(const GLshort*);
typedef void (STDCALL* PsglTangentPointerEXT)(GLenum, GLsizei,
    const GLvoid*);
typedef void (STDCALL* PsglBinormalPointerEXT)(GLenum, GLsizei,
    const GLvoid*);

static PsglTangent3bEXT sglTangent3bEXT = 0;
static PsglTangent3bvEXT sglTangent3bvEXT = 0;
static PsglTangent3dEXT sglTangent3dEXT = 0;
static PsglTangent3dvEXT sglTangent3dvEXT = 0;
static PsglTangent3fEXT sglTangent3fEXT = 0;
static PsglTangent3fvEXT sglTangent3fvEXT = 0;
static PsglTangent3iEXT sglTangent3iEXT = 0;
static PsglTangent3ivEXT sglTangent3ivEXT = 0;
static PsglTangent3sEXT sglTangent3sEXT = 0;
static PsglTangent3svEXT sglTangent3svEXT = 0;
static PsglBinormal3bEXT sglBinormal3bEXT = 0;
static PsglBinormal3bvEXT sglBinormal3bvEXT = 0;
static PsglBinormal3dEXT sglBinormal3dEXT = 0;
static PsglBinormal3dvEXT sglBinormal3dvEXT = 0;
static PsglBinormal3fEXT sglBinormal3fEXT = 0;
static PsglBinormal3fvEXT sglBinormal3fvEXT = 0;
static PsglBinormal3iEXT sglBinormal3iEXT = 0;
static PsglBinormal3ivEXT sglBinormal3ivEXT = 0;
static PsglBinormal3sEXT sglBinormal3sEXT = 0;
static PsglBinormal3svEXT sglBinormal3svEXT = 0;
static PsglTangentPointerEXT sglTangentPointerEXT = 0;
static PsglBinormalPointerEXT sglBinormalPointerEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glTangent3bEXT(GLbyte cX, GLbyte cY, GLbyte cZ)
{
    SE_BODY_A3(sglTangent3bEXT, cX, cY, cZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3bvEXT(const GLbyte* acXYZ)
{
    SE_BODY_A1(sglTangent3bvEXT, acXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3dEXT(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_BODY_A3(sglTangent3dEXT, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3dvEXT(const GLdouble* adXYZ)
{
    SE_BODY_A1(sglTangent3dvEXT, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3fEXT(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_BODY_A3(sglTangent3fEXT, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3fvEXT(const GLfloat* afXYZ)
{
    SE_BODY_A1(sglTangent3fvEXT, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3iEXT(GLint iX, GLint iY, GLint iZ)
{
    SE_BODY_A3(sglTangent3iEXT, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3ivEXT(const GLint* aiXYZ)
{
    SE_BODY_A1(sglTangent3ivEXT, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3sEXT(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_BODY_A3(sglTangent3sEXT, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangent3svEXT(const GLshort* asXYZ)
{
    SE_BODY_A1(sglTangent3svEXT, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3bEXT(GLbyte cX, GLbyte cY, GLbyte cZ)
{
    SE_BODY_A3(sglBinormal3bEXT, cX, cY, cZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3bvEXT(const GLbyte* acXYZ)
{
    SE_BODY_A1(sglBinormal3bvEXT, acXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3dEXT(GLdouble dX, GLdouble dY, GLdouble dZ)
{
    SE_BODY_A3(sglBinormal3dEXT, dX, dY, dZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3dvEXT(const GLdouble* adXYZ)
{
    SE_BODY_A1(sglBinormal3dvEXT, adXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3fEXT(GLfloat fX, GLfloat fY, GLfloat fZ)
{
    SE_BODY_A3(sglBinormal3fEXT, fX, fY, fZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3fvEXT(const GLfloat* afXYZ)
{
    SE_BODY_A1(sglBinormal3fvEXT, afXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3iEXT(GLint iX, GLint iY, GLint iZ)
{
    SE_BODY_A3(sglBinormal3iEXT, iX, iY, iZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3ivEXT(const GLint* aiXYZ)
{
    SE_BODY_A1(sglBinormal3ivEXT, aiXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3sEXT(GLshort sX, GLshort sY, GLshort sZ)
{
    SE_BODY_A3(sglBinormal3sEXT, sX, sY, sZ);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormal3svEXT(const GLshort* asXYZ)
{
    SE_BODY_A1(sglBinormal3svEXT, asXYZ);
}
/*--------------------------------------------------------------------------*/
void SE_glTangentPointerEXT(GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A3(sglTangentPointerEXT, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_glBinormalPointerEXT(GLenum eType, GLsizei iStride, 
    const GLvoid* pvPointer)
{
    SE_BODY_A3(sglBinormalPointerEXT, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtCoordinateFrame()
{
    if( SE_GL_SupportsExtension("GL_EXT_coordinate_frame") )
    {
        SE_ExistsGlExtCoordinateFrame = 1;

        SE_GET_FUNCTION(sglTangent3bEXT);
        SE_GET_FUNCTION(sglTangent3bvEXT);
        SE_GET_FUNCTION(sglTangent3dEXT);
        SE_GET_FUNCTION(sglTangent3dvEXT);
        SE_GET_FUNCTION(sglTangent3fEXT);
        SE_GET_FUNCTION(sglTangent3fvEXT);
        SE_GET_FUNCTION(sglTangent3iEXT);
        SE_GET_FUNCTION(sglTangent3ivEXT);
        SE_GET_FUNCTION(sglTangent3sEXT);
        SE_GET_FUNCTION(sglTangent3svEXT);
        SE_GET_FUNCTION(sglBinormal3bEXT);
        SE_GET_FUNCTION(sglBinormal3bvEXT);
        SE_GET_FUNCTION(sglBinormal3dEXT);
        SE_GET_FUNCTION(sglBinormal3dvEXT);
        SE_GET_FUNCTION(sglBinormal3fEXT);
        SE_GET_FUNCTION(sglBinormal3fvEXT);
        SE_GET_FUNCTION(sglBinormal3iEXT);
        SE_GET_FUNCTION(sglBinormal3ivEXT);
        SE_GET_FUNCTION(sglBinormal3sEXT);
        SE_GET_FUNCTION(sglBinormal3svEXT);
        SE_GET_FUNCTION(sglTangentPointerEXT);
        SE_GET_FUNCTION(sglBinormalPointerEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 158) GL_EXT_texture_env_combine */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureEnvCombine = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureEnvCombine()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_env_combine") )
    {
        SE_ExistsGlExtTextureEnvCombine = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 173) GL_EXT_blend_func_separate */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendFuncSeparate = 0;

static PsglBlendFuncSeparate sglBlendFuncSeparateEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendFuncSeparateEXT(GLenum eSrcFactorRGB, GLenum eDstFactorRGB,
    GLenum eSrcFactorA, GLenum eDstFactorA)
{
    SE_BODY_A4(sglBlendFuncSeparateEXT, eSrcFactorRGB, eDstFactorRGB, 
        eSrcFactorA, eDstFactorA);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendFuncSeparate()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_func_separate") )
    {
        SE_ExistsGlExtBlendFuncSeparate = 1;

        SE_GET_FUNCTION_C(sglBlendFuncSeparate, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 176) GL_EXT_stencil_wrap */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtStencilWrap = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtStencilWrap()
{
    if( SE_GL_SupportsExtension("GL_EXT_stencil_wrap") )
    {
        SE_ExistsGlExtStencilWrap = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 178) GL_EXT_422_pixels */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExt422Pixels = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExt422Pixels()
{
    if( SE_GL_SupportsExtension("GL_EXT_422_pixels") )
    {
        SE_ExistsGlExt422Pixels = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 185) GL_EXT_texture_env_add */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureEnvAdd = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureEnvAdd()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_env_add") )
    {
        SE_ExistsGlExtTextureEnvAdd = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 186) GL_EXT_texture_lod_bias */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureLodBias = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureLodBias()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_lod_bias") )
    {
        SE_ExistsGlExtTextureLodBias = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 187) GL_EXT_texture_filter_anisotropic */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureFilterAnisotropic = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureFilterAnisotropic()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_filter_anisotropic") )
    {
        SE_ExistsGlExtTextureFilterAnisotropic = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 188) GL_EXT_vertex_weighting */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtVertexWeighting = 0;

typedef void (STDCALL* PsglVertexWeightfEXT)(GLfloat);
typedef void (STDCALL* PsglVertexWeightfvEXT)(const GLfloat*);
typedef void (STDCALL* PsglVertexWeightPointerEXT)(GLsizei, GLenum,
    GLsizei, const GLvoid*);

static PsglVertexWeightfEXT sglVertexWeightfEXT = 0;
static PsglVertexWeightfvEXT sglVertexWeightfvEXT = 0;
static PsglVertexWeightPointerEXT sglVertexWeightPointerEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glVertexWeightfEXT(GLfloat fWeight)
{
    SE_BODY_A1(sglVertexWeightfEXT, fWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexWeightfvEXT(const GLfloat* afWeight)
{
    SE_BODY_A1(sglVertexWeightfvEXT, afWeight);
}
/*--------------------------------------------------------------------------*/
void SE_glVertexWeightPointerEXT(GLsizei iSize, GLenum eType, 
    GLsizei iStride, const GLvoid* pvPointer)
{
    SE_BODY_A4(sglVertexWeightPointerEXT, iSize, eType, iStride, pvPointer);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtVertexWeighting()
{
    if( SE_GL_SupportsExtension("GL_EXT_vertex_weighting") )
    {
        SE_ExistsGlExtVertexWeighting = 1;

        SE_GET_FUNCTION(sglVertexWeightfEXT);
        SE_GET_FUNCTION(sglVertexWeightfvEXT);
        SE_GET_FUNCTION(sglVertexWeightPointerEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 198) GL_EXT_texture_compression_s3tc */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureCompressionS3TC = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureCompressionS3TC()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_compression_s3tc") )
    {
        SE_ExistsGlExtTextureCompressionS3TC = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 209) GL_EXT_multisample */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtMultisample = 0;

typedef void (STDCALL* PsglSampleMaskEXT)(GLclampf, GLboolean);
typedef void (STDCALL* PsglSamplePatternEXT)(GLenum);

static PsglSampleMaskEXT sglSampleMaskEXT = 0;
static PsglSamplePatternEXT sglSamplePatternEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glSampleMaskEXT(GLclampf fValue, GLboolean ucInvert)
{
    SE_BODY_A2(sglSampleMaskEXT, fValue, ucInvert);
}
/*--------------------------------------------------------------------------*/
void SE_glSamplePatternEXT(GLenum ePattern)
{
    SE_BODY_A1(sglSamplePatternEXT, ePattern);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtMultisample()
{
    if( SE_GL_SupportsExtension("GL_EXT_multisample") )
    {
        SE_ExistsGlExtMultisample = 1;

        SE_GET_FUNCTION(sglSampleMaskEXT);
        SE_GET_FUNCTION(sglSamplePatternEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 220) GL_EXT_texture_env_dot3 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureEnvDot3 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureEnvDot3()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_env_dot3") )
    {
        SE_ExistsGlExtTextureEnvDot3 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 267) GL_EXT_shadow_funcs */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtShadowFuncs = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtShadowFuncs()
{
    if( SE_GL_SupportsExtension("GL_EXT_shadow_funcs") )
    {
        SE_ExistsGlExtShadowFuncs = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 268) GL_EXT_stencil_two_side */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtStencilTwoSide = 0;

typedef void (STDCALL* PsglActiveStencilFaceEXT)(GLenum);

static PsglActiveStencilFaceEXT sglActiveStencilFaceEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glActiveStencilFaceEXT(GLenum eFace)
{
    SE_BODY_A1(sglActiveStencilFaceEXT, eFace);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtStencilTwoSide()
{
    if( SE_GL_SupportsExtension("GL_EXT_stencil_two_side") )
    {
        SE_ExistsGlExtStencilTwoSide = 1;

        SE_GET_FUNCTION(sglActiveStencilFaceEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 297) GL_EXT_depth_bounds_test */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtDepthBoundsTest = 0;

typedef void (STDCALL* PsglDepthBoundsEXT)(GLclampd, GLclampd);

static PsglDepthBoundsEXT sglDepthBoundsEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glDepthBoundsEXT(GLclampd dMin, GLclampd dMax)
{
    SE_BODY_A2(sglDepthBoundsEXT, dMin, dMax);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtDepthBoundsTest()
{
    if( SE_GL_SupportsExtension("GL_EXT_depth_bounds_test") )
    {
        SE_ExistsGlExtDepthBoundsTest = 1;

        SE_GET_FUNCTION(sglDepthBoundsEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 298) GL_EXT_texture_mirror_clamp */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureMirrorClamp = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureMirrorClamp()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_mirror_clamp") )
    {
        SE_ExistsGlExtTextureMirrorClamp = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 299) GL_EXT_blend_equation_separate */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtBlendEquationSeparate = 0;

static PsglBlendEquationSeparate sglBlendEquationSeparateEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlendEquationSeparateEXT(GLenum eModeRGB, GLenum eModeAlpha)
{
    SE_BODY_A2(sglBlendEquationSeparateEXT, eModeRGB, eModeAlpha);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtBlendEquationSeparate()
{
    if( SE_GL_SupportsExtension("GL_EXT_blend_equation_separate") )
    {
        SE_ExistsGlExtBlendEquationSeparate = 1;

        SE_GET_FUNCTION_C(sglBlendEquationSeparate, EXT, SE_EXT_OVERRIDE);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 302) GL_EXT_pixel_buffer_object */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPixelBufferObject = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPixelBufferObject()
{
    if( SE_GL_SupportsExtension("GL_EXT_pixel_buffer_object") )
    {
        SE_ExistsGlExtPixelBufferObject = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 304) GL_NV_fragment_program2 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlNvFragmentProgram2 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlNvFragmentProgram2()
{
    if( SE_GL_SupportsExtension("GL_NV_fragment_program2") )
    {
        SE_ExistsGlNvFragmentProgram2 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 306) GL_NV_vertex_program3 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlNvVertexProgram3 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlNvVertexProgram3()
{
    if( SE_GL_SupportsExtension("GL_NV_vertex_program3") )
    {
        SE_ExistsGlNvVertexProgram3 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 309) GL_EXT_texture_compression_dxt1 */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureCompressionDXT1 = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureCompressionDXT1()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_compression_dxt1") )
    {
        SE_ExistsGlExtTextureCompressionDXT1 = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 310) GL_EXT_framebuffer_object */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtFrameBufferObject = 0;

typedef GLboolean (STDCALL* PsglIsRenderbufferEXT)(GLuint);
typedef void (STDCALL* PsglBindRenderbufferEXT)(GLenum, GLuint);
typedef void (STDCALL* PsglDeleteRenderbuffersEXT)(GLsizei, const GLuint*);
typedef void (STDCALL* PsglGenRenderbuffersEXT)(GLsizei, GLuint*);
typedef void (STDCALL* PsglRenderbufferStorageEXT)(GLenum, GLenum,
    GLsizei, GLsizei);
typedef void (STDCALL* PsglGetRenderbufferParameterivEXT)(GLenum, GLenum,
    GLint*);
typedef GLboolean (STDCALL* PsglIsFramebufferEXT)(GLuint);
typedef void (STDCALL* PsglBindFramebufferEXT)(GLenum, GLuint);
typedef void (STDCALL* PsglDeleteFramebuffersEXT)(GLsizei, const GLuint*);
typedef void (STDCALL* PsglGenFramebuffersEXT)(GLsizei, GLuint*);
typedef GLenum (STDCALL* PsglCheckFramebufferStatusEXT)(GLenum);
typedef void (STDCALL* PsglFramebufferTexture1DEXT)(GLenum, GLenum, GLenum,
    GLuint, GLint);
typedef void (STDCALL* PsglFramebufferTexture2DEXT)(GLenum, GLenum, GLenum,
    GLuint, GLint);
typedef void (STDCALL* PsglFramebufferTexture3DEXT)(GLenum, GLenum, GLenum,
    GLuint, GLint, GLint);
typedef void (STDCALL* PsglFramebufferRenderbufferEXT)(GLenum, GLenum,
    GLenum, GLuint);
typedef void (STDCALL* PsglGetFramebufferAttachmentParameterivEXT)(GLenum,
    GLenum, GLenum, GLint*);
typedef void (STDCALL* PsglGenerateMipmapEXT)(GLenum);

static PsglIsRenderbufferEXT sglIsRenderbufferEXT = 0;
static PsglBindRenderbufferEXT sglBindRenderbufferEXT = 0;
static PsglDeleteRenderbuffersEXT sglDeleteRenderbuffersEXT = 0;
static PsglGenRenderbuffersEXT sglGenRenderbuffersEXT = 0;
static PsglRenderbufferStorageEXT sglRenderbufferStorageEXT = 0;
static PsglGetRenderbufferParameterivEXT sglGetRenderbufferParameterivEXT = 0;
static PsglIsFramebufferEXT sglIsFramebufferEXT = 0;
static PsglBindFramebufferEXT sglBindFramebufferEXT = 0;
static PsglDeleteFramebuffersEXT sglDeleteFramebuffersEXT = 0;
static PsglGenFramebuffersEXT sglGenFramebuffersEXT = 0;
static PsglCheckFramebufferStatusEXT sglCheckFramebufferStatusEXT = 0;
static PsglFramebufferTexture1DEXT sglFramebufferTexture1DEXT = 0;
static PsglFramebufferTexture2DEXT sglFramebufferTexture2DEXT = 0;
static PsglFramebufferTexture3DEXT sglFramebufferTexture3DEXT = 0;
static PsglFramebufferRenderbufferEXT sglFramebufferRenderbufferEXT = 0;
static PsglGetFramebufferAttachmentParameterivEXT
    sglGetFramebufferAttachmentParameterivEXT = 0;
static PsglGenerateMipmapEXT sglGenerateMipmapEXT = 0;
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsRenderbufferEXT(GLuint uiRenderBuffer)
{
    SE_BODY_A1_RET(sglIsRenderbufferEXT, uiRenderBuffer, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBindRenderbufferEXT(GLenum eTarget, GLuint uiRenderBuffer)
{
    SE_BODY_A2(sglBindRenderbufferEXT, eTarget, uiRenderBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteRenderbuffersEXT(GLsizei iNumBuffers, 
    const GLuint* auiRenderBuffer)
{
    SE_BODY_A2(sglDeleteRenderbuffersEXT, iNumBuffers, auiRenderBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glGenRenderbuffersEXT(GLsizei iNumBuffers, GLuint* auiRenderBuffer)
{
    SE_BODY_A2(sglGenRenderbuffersEXT, iNumBuffers, auiRenderBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glRenderbufferStorageEXT(GLenum eTarget, GLenum eInternalFormat, 
    GLsizei iWidth, GLsizei iHeight)
{
    SE_BODY_A4(sglRenderbufferStorageEXT, eTarget, eInternalFormat, iWidth, 
        iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_glGetRenderbufferParameterivEXT(GLenum eTarget, GLenum ePName, 
    GLint* aiParam)
{
    SE_BODY_A3(sglGetRenderbufferParameterivEXT, eTarget, ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_glIsFramebufferEXT(GLuint uiFrameBuffer)
{
    SE_BODY_A1_RET(sglIsFramebufferEXT, uiFrameBuffer, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
void SE_glBindFramebufferEXT(GLenum eTarget, GLuint uiFrameBuffer)
{
    SE_BODY_A2(sglBindFramebufferEXT, eTarget, uiFrameBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glDeleteFramebuffersEXT(GLsizei iNumBuffers, 
    const GLuint* auiFrameBuffer)
{
    SE_BODY_A2(sglDeleteFramebuffersEXT, iNumBuffers, auiFrameBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glGenFramebuffersEXT(GLsizei iNumBuffers, GLuint* auiFrameBuffer)
{
    SE_BODY_A2(sglGenFramebuffersEXT, iNumBuffers, auiFrameBuffer);
}
/*--------------------------------------------------------------------------*/
GLenum SE_glCheckFramebufferStatusEXT(GLenum eTarget)
{
    SE_BODY_A1_RET(sglCheckFramebufferStatusEXT, eTarget, GLenum, 
        GL_FRAMEBUFFER_UNSUPPORTED_EXT);
}
/*--------------------------------------------------------------------------*/
void SE_glFramebufferTexture1DEXT(GLenum eTarget, GLenum eAttachment, 
    GLenum eTextureTarget, GLuint uiTexture, GLint iLevel)
{
    SE_BODY_A5(sglFramebufferTexture1DEXT, eTarget, eAttachment, eTextureTarget, 
        uiTexture, iLevel);
}
/*--------------------------------------------------------------------------*/
void SE_glFramebufferTexture2DEXT(GLenum eTarget, GLenum eAttachment, 
    GLenum eTextureTarget, GLuint uiTexture, GLint iLevel)
{
    SE_BODY_A5(sglFramebufferTexture2DEXT, eTarget, eAttachment, eTextureTarget, 
        uiTexture, iLevel);
}
/*--------------------------------------------------------------------------*/
void SE_glFramebufferTexture3DEXT(GLenum eTarget, GLenum eAttachment, 
    GLenum eTextureTarget, GLuint uiTexture, GLint iLevel, GLint iZOffset)
{
    SE_BODY_A6(sglFramebufferTexture3DEXT, eTarget, eAttachment, eTextureTarget, 
        uiTexture, iLevel, iZOffset);
}
/*--------------------------------------------------------------------------*/
void SE_glFramebufferRenderbufferEXT(GLenum eTarget, GLenum eAttachment, 
    GLenum eRenderBufferTarget, GLuint uiRenderBuffer)
{
    SE_BODY_A4(sglFramebufferRenderbufferEXT, eTarget, eAttachment, 
        eRenderBufferTarget, uiRenderBuffer);
}
/*--------------------------------------------------------------------------*/
void SE_glGetFramebufferAttachmentParameterivEXT(GLenum eTarget, 
    GLenum eAttachment, GLenum ePName, GLint* aiParam)
{
    SE_BODY_A4(sglGetFramebufferAttachmentParameterivEXT, eTarget, eAttachment, 
        ePName, aiParam);
}
/*--------------------------------------------------------------------------*/
void SE_glGenerateMipmapEXT(GLenum eTarget)
{
    SE_BODY_A1(sglGenerateMipmapEXT, eTarget);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtFrameBufferObject()
{
    if( SE_GL_SupportsExtension("GL_EXT_framebuffer_object") )
    {
        SE_ExistsGlExtFrameBufferObject = 1;

        SE_GET_FUNCTION(sglIsRenderbufferEXT);
        SE_GET_FUNCTION(sglBindRenderbufferEXT);
        SE_GET_FUNCTION(sglDeleteRenderbuffersEXT);
        SE_GET_FUNCTION(sglGenRenderbuffersEXT);
        SE_GET_FUNCTION(sglRenderbufferStorageEXT);
        SE_GET_FUNCTION(sglGetRenderbufferParameterivEXT);
        SE_GET_FUNCTION(sglIsFramebufferEXT);
        SE_GET_FUNCTION(sglBindFramebufferEXT);
        SE_GET_FUNCTION(sglDeleteFramebuffersEXT);
        SE_GET_FUNCTION(sglGenFramebuffersEXT);
        SE_GET_FUNCTION(sglCheckFramebufferStatusEXT);
        SE_GET_FUNCTION(sglFramebufferTexture1DEXT);
        SE_GET_FUNCTION(sglFramebufferTexture2DEXT);
        SE_GET_FUNCTION(sglFramebufferTexture3DEXT);
        SE_GET_FUNCTION(sglFramebufferRenderbufferEXT);
        SE_GET_FUNCTION(sglGetFramebufferAttachmentParameterivEXT);
        SE_GET_FUNCTION(sglGenerateMipmapEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 312) GL_EXT_packed_depth_stencil */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtPackedDepthStencil = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtPackedDepthStencil()
{
    if( SE_GL_SupportsExtension("GL_EXT_packed_depth_stencil") )
    {
        SE_ExistsGlExtPackedDepthStencil = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 314) GL_EXT_stencil_clear_tag */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtStencilClearTag = 0;

typedef void (STDCALL* PsglStencilClearTagEXT)(GLsizei, GLuint);

static PsglStencilClearTagEXT sglStencilClearTagEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glStencilClearTagEXT(GLsizei iStencilTagBits,
    GLuint uiStencilClearTag)
{
    SE_BODY_A2(sglStencilClearTagEXT, iStencilTagBits, uiStencilClearTag);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtStencilClearTag()
{
    if( SE_GL_SupportsExtension("GL_EXT_stencil_clear_tag") )
    {
        SE_ExistsGlExtStencilClearTag = 1;

        SE_GET_FUNCTION(sglStencilClearTagEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 315) GL_EXT_texture_sRGB */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtTextureSRGB = 0;
/*--------------------------------------------------------------------------*/
void SE_InitGlExtTextureSRGB()
{
    if( SE_GL_SupportsExtension("GL_EXT_texture_sRGB") )
    {
        SE_ExistsGlExtTextureSRGB = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 316) GL_EXT_framebuffer_blit */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtFrameBufferBlit = 0;

typedef void (STDCALL* PsglBlitFramebufferEXT)(GLint, GLint, GLint, GLint,
    GLint, GLint, GLint, GLint, GLbitfield, GLenum);

static PsglBlitFramebufferEXT sglBlitFramebufferEXT = 0;
/*--------------------------------------------------------------------------*/
void SE_glBlitFramebufferEXT(GLint iSrcX0, GLint iSrcY0, GLint iSrcX1,
    GLint iSrcY1, GLint iDstX0, GLint iDstY0, GLint iDstX1, GLint iDstY1,
    GLbitfield uiMask, GLenum eFilter)
{
    SE_BODY_A10(sglBlitFramebufferEXT, iSrcX0, iSrcY0, iSrcX1, iSrcY1, iDstX0, 
        iDstY0, iDstX1, iDstY1, uiMask, eFilter);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtFrameBufferBlit()
{
    if( SE_GL_SupportsExtension("GL_EXT_framebuffer_blit") )
    {
        SE_ExistsGlExtFrameBufferBlit = 1;

        SE_GET_FUNCTION(sglBlitFramebufferEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 317) GL_EXT_framebuffer_multisample */
/*--------------------------------------------------------------------------*/
int SE_ExistsGlExtFrameBufferMultisample = 0;

typedef void (STDCALL* PsglRenderbufferStorageMultisampleEXT)(GLenum,
    GLsizei, GLenum, GLsizei, GLsizei);

static PsglRenderbufferStorageMultisampleEXT
    sglRenderbufferStorageMultisampleEXT = 0;

/*--------------------------------------------------------------------------*/
void SE_glRenderbufferStorageMultisampleEXT(GLenum eTarget, GLsizei iSamples,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight)
{
    SE_BODY_A5(sglRenderbufferStorageMultisampleEXT, eTarget, iSamples, 
        eInternalFormat, iWidth, iHeight);
}
/*--------------------------------------------------------------------------*/
void SE_InitGlExtFrameBufferMultisample()
{
    if( SE_GL_SupportsExtension("GL_EXT_framebuffer_multisample") )
    {
        SE_ExistsGlExtFrameBufferMultisample = 1;

        SE_GET_FUNCTION(sglRenderbufferStorageMultisampleEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Access to OpenGL driver information. */
/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif
/*--------------------------------------------------------------------------*/
const char* SE_GL_GetVendorString()
{
    return (const char*)glGetString(GL_VENDOR);
}
/*--------------------------------------------------------------------------*/
const char* SE_GL_GetRendererString()
{
    return (const char*)glGetString(GL_RENDERER);
}
/*--------------------------------------------------------------------------*/
const char* SE_GL_GetVersionString()
{
    return (const char*)glGetString(GL_VERSION);
}
/*--------------------------------------------------------------------------*/
const char* SE_GL_GetExtensionString()
{
    return (const char*)glGetString(GL_EXTENSIONS);
}
/*--------------------------------------------------------------------------*/
int SE_GL_SupportsExtension(const char* acExtension)
{
    const char* acExtensionString;
    char* acBegin;
    char cEnd;

    if( !acExtension )
    {
        return 0;
    }

    acExtensionString = SE_GL_GetExtensionString();
    if( !acExtensionString )
    {
        return 0;
    }

    acBegin = (char*)strstr(acExtensionString, acExtension);
    if( !acBegin )
    {
        return 0;
    }

    /* 找到指定extension的字符串, 但要确定它不是其他extension字符串的子串. */
    cEnd = *(acBegin + strlen(acExtension));

    return cEnd == ' ' || cEnd == 0 || cEnd == '\t' || cEnd == '\n';
}
/*--------------------------------------------------------------------------*/
int SE_GL_GetVersion()
{
    const char* pcToken = SE_GL_GetVersionString();
    if( pcToken )
    {
        if( *pcToken == '1' )
        {
            pcToken++;
            if( pcToken && *pcToken == '.' )
            {
                pcToken++;
                if( pcToken )
                {
                    switch( *pcToken )
                    {
                    case '1': return SE_GL_VERSION_1_1;
                    case '2': return SE_GL_VERSION_1_2;
                    case '3': return SE_GL_VERSION_1_3;
                    case '4': return SE_GL_VERSION_1_4;
                    case '5': return SE_GL_VERSION_1_5;
                    }
                }
            }
        }
        else if( *pcToken == '2' )
        {
            return SE_GL_VERSION_2_0;
        }
    }

    return SE_GL_VERSION_NONE;
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL系统的初始化 */
/*--------------------------------------------------------------------------*/
#include <cstdio>
#include <cstdlib>

/* Disable the MSVC8 warnings about deprecated functions. */
#pragma warning( push )
#pragma warning( disable : 4996 )

void SE_GL_Initialize(const char* acInfoFile)
{
    if( acInfoFile )
    {
        FILE* pInfo = fopen(acInfoFile, "wt");
        if( pInfo )
        {
            const char* acVendor;
            const char* acRenderer;
            const char* acVersion;
            const char* acExtensions;

            acVendor = SE_GL_GetVendorString();
            if( acVendor )
            {
                fprintf(pInfo, "vendor = %s\n", acVendor);
            }
            else
            {
                fprintf(pInfo, "vendor = <null>\n");
            }

            acRenderer = SE_GL_GetRendererString();
            if( acRenderer )
            {
                fprintf(pInfo, "renderer = %s\n", acRenderer);
            }
            else
            {
                fprintf(pInfo, "renderer = <null>\n");
            }

            acVersion = SE_GL_GetVersionString();
            if( acVersion )
            {
                fprintf(pInfo, "version = %s\n", acVersion);
            }
            else
            {
                fprintf(pInfo, "version = <null>\n");
            }

            acExtensions = SE_GL_GetExtensionString();
            if( acExtensions )
            {
                char* acExt;
                char* pcToken;

                fprintf(pInfo, "extensions =\n");
                acExt = (char*)malloc((int)strlen(acExtensions) + 1);
                strcpy(acExt, acExtensions);
                pcToken = strtok(acExt, " \t\n");
                while( pcToken )
                {
                    fprintf(pInfo, "    %s\n", pcToken);
                    pcToken = strtok(0, " \t\n");
                }
                free(acExt);
            }
            else
            {
                fprintf(pInfo, "extensions = <null>\n");
            }

            fclose(pInfo);
        }
    }

    SE_InitOpenGL12();
    SE_InitGlArbImaging();
    SE_InitOpenGL13();
    SE_InitOpenGL14();
    SE_InitOpenGL15();
    SE_InitOpenGL20();

    SE_InitGlArbMultitexture();
    SE_InitGlArbTransposeMatrix();
    SE_InitGlArbMultisample();
    SE_InitGlArbTextureEnvAdd();
    SE_InitGlArbTextureCubeMap();
    SE_InitGlArbTextureCompression();
    SE_InitGlArbTextureBorderClamp();
    SE_InitGlArbPointParameters();
    SE_InitGlArbVertexBlend();
    SE_InitGlArbMatrixPalette();
    SE_InitGlArbTextureEnvCombine();
    SE_InitGlArbTextureEnvCrossbar();
    SE_InitGlArbTextureEnvDot3();
    SE_InitGlArbTextureMirroredRepeat();
    SE_InitGlArbDepthTexture();
    SE_InitGlArbShadow();
    SE_InitGlArbShadowAmbient();
    SE_InitGlArbWindowPos();
    SE_InitGlArbVertexProgram();
    SE_InitGlArbFragmentProgram();
    SE_InitGlArbVertexBufferObject();
    SE_InitGlArbOcclusionQuery();
    SE_InitGlArbShaderObjects();
    SE_InitGlArbVertexShader();
    SE_InitGlArbFragmentShader();
    SE_InitGlArbShadingLanguage100();
    SE_InitGlArbTextureNonpowerOfTwo();
    SE_InitGlArbPointSprite();
    SE_InitGlArbFragmentProgramShadow();
    SE_InitGlArbDrawBuffers();
    SE_InitGlArbTextureRectangle();
    SE_InitGlArbColorBufferFloat();
    SE_InitGlArbHalfFloatPixel();
    SE_InitGlArbTextureFloat();
    SE_InitGlArbPixelBufferObject();

    SE_InitGlExtABGR();
    SE_InitGlExtBlendColor();
    SE_InitGlExtPolygonOffset();
    SE_InitGlExtTexture();
    SE_InitGlExtTexture3D();
    SE_InitGlExtSubtexture();
    SE_InitGlExtCopyTexture();
    SE_InitGlExtHistogram();
    SE_InitGlExtConvolution();
    SE_InitGlExtCMYKA();
    SE_InitGlExtTextureObject();
    SE_InitGlExtPackedPixels();
    SE_InitGlExtRescaleNormal();
    SE_InitGlExtVertexArray();
    SE_InitGlExtMiscAttribute();
    SE_InitGlExtBlendMinMax();
    SE_InitGlExtBlendSubtract();
    SE_InitGlExtBlendLogicOp();
    SE_InitGlExtPointParameters();
    SE_InitGlExtColorSubtable();
    SE_InitGlExtPalettedTexture();
    SE_InitGlExtClipVolumeHint();
    SE_InitGlExtIndexTexture();
    SE_InitGlExtIndexMaterial();
    SE_InitGlExtIndexFunc();
    SE_InitGlExtIndexArrayFormats();
    SE_InitGlExtCompiledVertexArray();
    SE_InitGlExtCullVertex();
    SE_InitGlExtDrawRangeElements();
    SE_InitGlExtLightTexture();
    SE_InitGlExtBGRA();
    SE_InitGlExtPixelTransform();
    SE_InitGlExtPixelTransformColorTable();
    SE_InitGlExtSharedTexturePalette();
    SE_InitGlExtSeparateSpecularColor();
    SE_InitGlExtSecondaryColor();
    SE_InitGlExtTexturePerturbNormal();
    SE_InitGlExtMultidrawArrays();
    SE_InitGlExtFogCoord();
    SE_InitGlExtCoordinateFrame();
    SE_InitGlExtTextureEnvCombine();
    SE_InitGlExtBlendFuncSeparate();
    SE_InitGlExtStencilWrap();
    SE_InitGlExt422Pixels();
    SE_InitGlExtTextureEnvAdd();
    SE_InitGlExtTextureLodBias();
    SE_InitGlExtTextureFilterAnisotropic();
    SE_InitGlExtVertexWeighting();
    SE_InitGlExtTextureCompressionS3TC();
    SE_InitGlExtMultisample();
    SE_InitGlExtTextureEnvDot3();
    SE_InitGlExtShadowFuncs();
    SE_InitGlExtStencilTwoSide();
    SE_InitGlExtDepthBoundsTest();
    SE_InitGlExtTextureMirrorClamp();
    SE_InitGlExtBlendEquationSeparate();
    SE_InitGlExtPixelBufferObject();
    SE_InitGlNvFragmentProgram2();
    SE_InitGlNvVertexProgram3();
    SE_InitGlExtTextureCompressionDXT1();
    SE_InitGlExtFrameBufferObject();
    SE_InitGlExtPackedDepthStencil();
    SE_InitGlExtStencilClearTag();
    SE_InitGlExtTextureSRGB();
    SE_InitGlExtFrameBufferBlit();
    SE_InitGlExtFrameBufferMultisample();
}

#pragma warning( pop )
/*--------------------------------------------------------------------------*/
