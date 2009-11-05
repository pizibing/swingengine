#ifndef Swing_DefaultShader_H
#define Swing_DefaultShader_H

#include "SEWindowApplication3.h"

using namespace Swing;

class DefaultShader : public WindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    DefaultShader(void);

    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnIdle(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);

protected:
    void CreateScene(void);

    NodePtr m_spScene;
    TriMeshPtr m_spMesh;
    Culler m_Culler;
};

#endif
