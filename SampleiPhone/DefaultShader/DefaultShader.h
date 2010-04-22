#ifndef Swing_DefaultShader_H
#define Swing_DefaultShader_H

#include "SEWindowApplication3.h"

using namespace Swing;

class DefaultShader : public SEWindowApplication3
{
    SE_DECLARE_INITIALIZE;

public:
    DefaultShader(void);

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
