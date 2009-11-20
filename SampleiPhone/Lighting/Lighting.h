#ifndef Swing_Lighting_H
#define Swing_Lighting_H

#include "SEWindowApplication3.h"

using namespace Swing;

class Lighting : public WindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    Lighting(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);

protected:
    void CreateScene(void);
    void CreateLights(void);

    NodePtr m_spScene;
    TriMeshPtr m_spTeapot;
    TriMeshPtr m_spQuad;
    TexturePtr m_spTexture1;
    TexturePtr m_spTexture2;
    Culler m_Culler;

    LightPtr m_aspLight[4];
};

#endif
