#include "Lighting.h"
#include "SwingOGLES1Renderer.h"

SE_WINDOW_APPLICATION(Lighting);

SE_REGISTER_INITIALIZE(Lighting);

//----------------------------------------------------------------------------
Lighting::Lighting()
    :
    SEWindowApplication3("Lighting", 0, 0, 320, 480, 
        SEColorRGBA(1.0f, 1.0f, 1.0f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool Lighting::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    // set camera.
    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -6.0f);
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
void Lighting::OnTerminate()
{
    m_spScene = 0;
    m_spTeapot = 0;
    m_spQuad = 0;
    m_spTexture1 = 0;
    m_spTexture2 = 0;

    m_aspLight[0] = 0;
    m_aspLight[1] = 0;
    m_aspLight[2] = 0;
    m_aspLight[3] = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Lighting::OnIdle()
{
    // 旋转我们创建的teapot.
    SEMatrix3f mat3fRot;
    mat3fRot.FromEulerAnglesXYZ(0.0f, 0.01f, 0.0f);
    m_spTeapot->Local.SetRotate(m_spTeapot->Local.GetRotate()*mat3fRot);
    m_spTeapot->UpdateGS();

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
        //m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        m_pRenderer->Draw(m_spQuad);
        m_pRenderer->Draw(m_spTeapot);

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();
	
    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void Lighting::CreateLights(void)
{
    m_aspLight[0] = SE_NEW SELight(SELight::LT_AMBIENT);
    m_aspLight[1] = SE_NEW SELight(SELight::LT_DIRECTIONAL);
    m_aspLight[2] = SE_NEW SELight(SELight::LT_POINT);
    m_aspLight[3] = SE_NEW SELight(SELight::LT_SPOT);

    float fValue = 0.1f;
    m_aspLight[0]->Ambient = SEColorRGB(fValue, fValue, fValue);

    m_aspLight[1]->DVector = SEVector3f(0.0f, 0.0f, 1.0f);
    m_aspLight[1]->Ambient = SEColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[1]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Specular = SEColorRGB::SE_RGB_WHITE;

    m_aspLight[2]->Position = SEVector3f(0.0f, -2.0f, -3.0f);
    m_aspLight[2]->Ambient = SEColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[2]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[2]->Specular = SEColorRGB::SE_RGB_WHITE;

    fValue = 4.0f;
    m_aspLight[3]->Position = SEVector3f(+fValue, +fValue, +fValue);
    fValue = -SEMathf::Sqrt(1.0f/3.0f);
    m_aspLight[3]->DVector = SEVector3f(+fValue, +fValue, +fValue);
    m_aspLight[3]->Ambient = SEColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[3]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Specular = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Exponent = 1.0f;
    m_aspLight[3]->SetAngle(0.125f*SEMathf::PI);
}
//----------------------------------------------------------------------------
void Lighting::CreateScene()
{
    CreateLights();

    m_spScene = SE_NEW SENode;

    // polished egg.
    SEMaterialState* pEggMaterial = SE_NEW SEMaterialState;
    pEggMaterial->Emissive = SEColorRGB(0.5f, 0.0f, 0.0f);
    pEggMaterial->Ambient = SEColorRGB(1.0f, 0.92f, 0.804f)*0.1f;
    pEggMaterial->Diffuse = SEColorRGB(1.0f, 0.92f, 0.804f);
    pEggMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pEggMaterial->Shininess = 50.0f;
    //pEggMaterial->Alpha = 0.8f;

    // flat white.
    SEMaterialState* pBlueMaterial = SE_NEW SEMaterialState;
    pBlueMaterial->Ambient = SEColorRGB(0.0f, 0.0f, 0.0f);
    pBlueMaterial->Diffuse = SEColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Specular = SEColorRGB(0.0f, 0.0f, 0.0f);
    pBlueMaterial->Shininess = 0.0f;
    //pBlueMaterial->Alpha = 0.5f;

    // create textures.
    SEImage* pImage = SEImageCatalog::GetActive()->Find("rock");
    m_spTexture1 = SE_NEW SETexture(pImage);

    pImage = SEImageCatalog::GetActive()->Find("kate");
    m_spTexture2 = SE_NEW SETexture(pImage);

    // load a teapot from disk.
    SEStream tempStream;
    const char* acPath = SESystem::SE_GetPath("teapot.seof", 
        SESystem::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;

    SENode* pSceneLoaded = DynamicCast<SENode>(tempStream.GetObjectAt(0));
    m_spTeapot = DynamicCast<SETriMesh>(pSceneLoaded->GetChild(0));
    SE_ASSERT( m_spTeapot );

    SEAlphaState* pAS = SE_NEW SEAlphaState;
    pAS->BlendEnabled = false;
    SEZBufferState* pZS = SE_NEW SEZBufferState;
    pZS->Writable = true;
    m_spTeapot->GenerateNormals();
    m_spTeapot->AttachGlobalState(pEggMaterial);
    m_spTeapot->AttachGlobalState(pAS);
    m_spTeapot->AttachGlobalState(pZS);
    m_spTeapot->Local.SetUniformScale(5.0f);
    m_spTeapot->Local.SetTranslate(SEVector3f(0.0f, -3.0f, 0.0f));
    m_spTeapot->DetachAllEffects();
    SEOGLES1FixedEffect* pEffect = SE_NEW SEOGLES1FixedEffect(0, 1);
    pEffect->SetLight(0, m_aspLight[1]);
    m_spTeapot->AttachEffect(pEffect);
    m_spScene->AttachChild(pSceneLoaded);

    // 创建一个quad.
    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);
    tempAttr.SetTCoordChannels(1, 2);
    SEStandardMesh tempSM(tempAttr);
    m_spQuad = tempSM.Rectangle(2, 2, 5.0f, 5.0f);
    m_spQuad->Local.SetTranslate(SEVector3f(0.0f, -2.0f, 4.0f));
    m_spQuad->AttachGlobalState(pBlueMaterial);

    pEffect = SE_NEW SEOGLES1FixedEffect(2, 1);
    pEffect->SetTexture(0, m_spTexture1);
    pEffect->SetTexture(1, m_spTexture2);
    pEffect->SetLight(0, m_aspLight[1]);
    m_spQuad->AttachEffect(pEffect);
    m_spScene->AttachChild(m_spQuad);
}
//----------------------------------------------------------------------------
