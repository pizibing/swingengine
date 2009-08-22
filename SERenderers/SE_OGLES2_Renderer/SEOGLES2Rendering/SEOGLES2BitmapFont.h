#ifndef Swing_OpenGLBitmapFont_H
#define Swing_OpenGLBitmapFont_H

#include "SEOpenGLRendererLIB.h"

namespace Swing
{

class SE_RENDERER_API BitmapFontChar
{
public:
    BitmapFontChar(int iXOrigin, int iYOrigin, int iXSize, int iYSize,
        const unsigned char* aucBitmap)
    {
        XOrigin = iXOrigin;
        YOrigin = iYOrigin;
        XSize = iXSize;
        YSize = iYSize;
        Bitmap = aucBitmap;
    }

    int XOrigin, YOrigin, XSize, YSize;
    const unsigned char* Bitmap;
};

class SE_RENDERER_API BitmapFont
{
public:
    BitmapFont(const char* acName, int iCount,
        const BitmapFontChar* const* pChars)
    {
        Name = acName;
        Count = iCount;
        Chars = pChars;
    }

    const char* Name;
    int Count;
    const BitmapFontChar* const* Chars;
};

extern const BitmapFont g_Verdana_S16B0I0;

}

#endif
