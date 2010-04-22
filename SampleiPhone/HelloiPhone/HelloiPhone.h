#ifndef Swing_HelloiPhone_H
#define Swing_HelloiPhone_H

#include "SEWindowApplication3.h"
#include "SwingOGLES1Renderer.h"

using namespace Swing;

class HelloiPhone : public SEWindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    HelloiPhone(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);

protected:
    void CreateScene(void);

    SENodePtr m_spScene;
    SETriMeshPtr m_spMesh;
    SECuller m_Culler;
};

#endif
