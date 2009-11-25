#include "SEOpenALRendererPCH.h"
#include "SEiPhoneOpenALRenderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
iPhoneOpenALRenderer::iPhoneOpenALRenderer()
{
    m_pALDevice = 0;
    m_pALContext = 0;

    // 创建device和context.
    m_pALDevice = alcOpenDevice(NULL);
    SE_ASSERT( m_pALDevice );

    if( m_pALDevice )
    {
        m_pALContext = alcCreateContext(m_pALDevice, NULL);
        SE_ASSERT( m_pALContext );
        alcMakeContextCurrent(m_pALContext);
    }

    InitializeState();
}
//----------------------------------------------------------------------------
iPhoneOpenALRenderer::~iPhoneOpenALRenderer()
{
    // 释放context和device.
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_pALContext);
    alcCloseDevice(m_pALDevice);
}
//----------------------------------------------------------------------------