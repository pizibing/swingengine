#ifndef Swing_HelloiPhone_H
#define Swing_HelloiPhone_H

#include "SEWindowApplication3.h"
#include "SwingOGLES1Renderer.h"

using namespace Swing;

class HelloiPhone : public WindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    HelloiPhone(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);

protected:
    void CreateScene(void);

    NodePtr m_spScene;
    TriMeshPtr m_spMesh;
    Culler m_Culler;
};

#endif
