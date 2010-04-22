#ifndef Swing_Lighting_H
#define Swing_Lighting_H

#include "SEWindowApplication3.h"

using namespace Swing;

class Lighting : public SEWindowApplication3
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

    SENodePtr m_spScene;
    SETriMeshPtr m_spTeapot;
    SETriMeshPtr m_spQuad;
    SETexturePtr m_spTexture1;
    SETexturePtr m_spTexture2;
    SECuller m_Culler;

    SELightPtr m_aspLight[4];
};

#endif
