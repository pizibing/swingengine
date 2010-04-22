#include "HelloiPhone.h"

SE_WINDOW_APPLICATION(HelloiPhone);

SE_REGISTER_INITIALIZE(HelloiPhone);

//----------------------------------------------------------------------------
HelloiPhone::HelloiPhone()
    :
    SEWindowApplication3("HelloiPhone", 0, 0, 320, 480, 
        SEColorRGBA(1.0f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool HelloiPhone::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    // set camera.
    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -5.0f);
    SEVector3f tempCDir(0.0f, 0.0f, 1.0f);
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
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
void HelloiPhone::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void HelloiPhone::OnIdle()
{
    // 旋转我们创建的box.
    SEMatrix3f mat3fRot;
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
void HelloiPhone::CreateScene()
{
    // 创建纹理资源.
    SEImage* pImage = SEImageCatalog::GetActive()->Find("rock");
    SETexture* pTextureDiffuse = SE_NEW SETexture(pImage);

    pImage = SEImageCatalog::GetActive()->Find("kate");
    SETexture* pTextureGirl = SE_NEW SETexture(pImage);

    m_spScene = SE_NEW SENode;

    // 创建一个box.
    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
	tempAttr.SetNormalChannels(3);
    //tempAttr.SetColorChannels(0, 3);
    tempAttr.SetTCoordChannels(0, 2);
    tempAttr.SetTCoordChannels(1, 2);
    SEStandardMesh tempSM(tempAttr);
    m_spMesh = tempSM.Box(1.0f, 1.0f, 1.0f);
//    m_spMesh->VBuffer->ColorTuple(0, 0)[0] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 0)[1] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 0)[2] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 1)[0] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 1)[1] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 1)[2] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 2)[0] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 2)[1] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 2)[2] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 3)[0] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 3)[1] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 3)[2] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 4)[0] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 4)[1] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 4)[2] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 5)[0] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 5)[1] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 5)[2] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 6)[0] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 6)[1] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 6)[2] = 0.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 7)[0] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 7)[1] = 1.0f;
//    m_spMesh->VBuffer->ColorTuple(0, 7)[2] = 1.0f;

    SEOGLES1FixedEffect* pEffect = SE_NEW SEOGLES1FixedEffect(2, 0);
    pEffect->SetTexture(0, pTextureDiffuse);
    pEffect->SetTexture(1, pTextureGirl);
    m_spMesh->AttachEffect(pEffect);
    m_spScene->AttachChild(m_spMesh);
}
//----------------------------------------------------------------------------
