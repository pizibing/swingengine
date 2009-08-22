#ifndef Swing_Aal_Renderer_H
#define Swing_Aal_Renderer_H

#include "SEOpenALRendererLIB.h"
#include "SEOpenALRenderer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Mac OS X OpenAL1.0 Renderer类
// 说明:
// 作者:Sun Che
// 时间:20090629
//----------------------------------------------------------------------------
class SE_AUDIO_RENDERER_API AalRenderer : public OpenALRenderer
{
public:
    AalRenderer(void);
    virtual ~AalRenderer(void);

    // 参数访问.
    ALCdevice* GetALDevice(void){ return m_pALDevice; }
    ALCcontext* GetALContext(void){ return m_pALContext; }

protected:
    ALCdevice* m_pALDevice;
    ALCcontext* m_pALContext;
};

}

#endif
