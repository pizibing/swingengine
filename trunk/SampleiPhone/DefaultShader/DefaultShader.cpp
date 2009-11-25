#include "DefaultShader.h"

SE_WINDOW_APPLICATION(DefaultShader);

SE_REGISTER_INITIALIZE(DefaultShader);

//----------------------------------------------------------------------------
DefaultShader::DefaultShader()
    :
    WindowApplication3("DefaultShader", 0, 0, 320, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool DefaultShader::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    // set camera.
    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -5.0f);
    Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);
    
    CreateScene();
    
    // initial update of objects.
    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    // initial culling of scene.
    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.01f, 0.001f);
    InitializeObjectMotion(m_spScene);
    return true;
}
//----------------------------------------------------------------------------
void DefaultShader::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void DefaultShader::OnIdle()
{
    // Rotate the box.
    Matrix3f mat3fRot;
    mat3fRot.FromEulerAnglesXYZ(-0.02f, 0.02f, -0.02f);
    m_spMesh->Local.SetRotate(m_spMesh->Local.GetRotate()*mat3fRot);
    m_spMesh->UpdateGS();
    
    MeasureTime();

    if( MoveCamera() )
    {
        m_Culler.ComputeUnculledSet(m_spScene);
    }
    
    if( MoveObject() )
    {
        m_spScene->UpdateGS();
        m_Culler.ComputeUnculledSet(m_spScene);
    }
    
    m_pRenderer->ClearBuffers();
    if( m_pRenderer->BeginScene() )
    {
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();
    
    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void DefaultShader::CreateScene()
{
    m_spScene = SE_NEW Node;
	
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    StandardMesh tempSM(tempAttr);
    m_spMesh = tempSM.Box(1.0f, 1.0f, 1.0f);
    m_spScene->AttachChild(m_spMesh);
	
    DefaultShaderEffect* pEffect = SE_NEW DefaultShaderEffect;
    m_spMesh->AttachEffect(pEffect);
}
//----------------------------------------------------------------------------
