#include "Lighting.h"
#include "SwingOGLES1Renderer.h"

SE_WINDOW_APPLICATION(Lighting);

SE_REGISTER_INITIALIZE(Lighting);

//----------------------------------------------------------------------------
Lighting::Lighting()
    :
    WindowApplication3("Lighting", 0, 0, 320, 480, 
        ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool Lighting::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    // set camera.
    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -6.0f);
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

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Lighting::OnIdle()
{
    // 旋转我们创建的teapot.
    Matrix3f mat3fRot;
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
    m_aspLight[0] = SE_NEW Light(Light::LT_AMBIENT);
    m_aspLight[1] = SE_NEW Light(Light::LT_DIRECTIONAL);
    m_aspLight[2] = SE_NEW Light(Light::LT_POINT);
    m_aspLight[3] = SE_NEW Light(Light::LT_SPOT);

    float fValue = 0.1f;
    m_aspLight[0]->Ambient = ColorRGB(fValue, fValue, fValue);

    m_aspLight[1]->DVector = Vector3f(0.0f, 0.0f, 1.0f);
    m_aspLight[1]->Ambient = ColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[1]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Specular = ColorRGB::SE_RGB_WHITE;

    m_aspLight[2]->Position = Vector3f(0.0f, -2.0f, -3.0f);
    m_aspLight[2]->Ambient = ColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[2]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[2]->Specular = ColorRGB::SE_RGB_WHITE;

    fValue = 4.0f;
    m_aspLight[3]->Position = Vector3f(+fValue, +fValue, +fValue);
    fValue = -Mathf::Sqrt(1.0f/3.0f);
    m_aspLight[3]->DVector = Vector3f(+fValue, +fValue, +fValue);
    m_aspLight[3]->Ambient = ColorRGB(0.0f, 0.0f, 0.0f);
    m_aspLight[3]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Specular = ColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Exponent = 1.0f;
    m_aspLight[3]->SetAngle(0.125f*Mathf::PI);
}
//----------------------------------------------------------------------------
void Lighting::CreateScene()
{
    CreateLights();

    m_spScene = SE_NEW Node;

    // polished egg.
    MaterialState* pEggMaterial = SE_NEW MaterialState;
    pEggMaterial->Emissive = ColorRGB(0.5f, 0.0f, 0.0f);
    pEggMaterial->Ambient = ColorRGB(1.0f, 0.92f, 0.804f)*0.1f;
    pEggMaterial->Diffuse = ColorRGB(1.0f, 0.92f, 0.804f);
    pEggMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pEggMaterial->Shininess = 50.0f;
    //pEggMaterial->Alpha = 0.8f;

    // flat white.
    MaterialState* pBlueMaterial = SE_NEW MaterialState;
    pBlueMaterial->Ambient = ColorRGB(0.0f, 0.0f, 0.0f);
    pBlueMaterial->Diffuse = ColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Specular = ColorRGB(0.0f, 0.0f, 0.0f);
    pBlueMaterial->Shininess = 0.0f;
    //pBlueMaterial->Alpha = 0.5f;

    // create textures.
    Image* pImage = ImageCatalog::GetActive()->Find("rock");
    m_spTexture1 = SE_NEW Texture(pImage);

    pImage = ImageCatalog::GetActive()->Find("kate");
    m_spTexture2 = SE_NEW Texture(pImage);

    // load a teapot from disk.
    Stream tempStream;
    const char* acPath = System::SE_GetPath("teapot.seof", System::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;

    Node* pSceneLoaded = DynamicCast<Node>(tempStream.GetObjectAt(0));
    m_spTeapot = DynamicCast<TriMesh>(pSceneLoaded->GetChild(0));
    SE_ASSERT( m_spTeapot );

    AlphaState* pAS = SE_NEW AlphaState;
    pAS->BlendEnabled = false;
    ZBufferState* pZS = SE_NEW ZBufferState;
    pZS->Writable = true;
    m_spTeapot->GenerateNormals();
    m_spTeapot->AttachGlobalState(pEggMaterial);
    m_spTeapot->AttachGlobalState(pAS);
    m_spTeapot->AttachGlobalState(pZS);
    m_spTeapot->Local.SetUniformScale(0.2f);
    m_spTeapot->Local.SetTranslate(Vector3f(0.0f, -3.0f, 0.0f));
    m_spTeapot->DetachAllEffects();
    OGLES1FixedEffect* pEffect = SE_NEW OGLES1FixedEffect(0, 1);
    pEffect->SetLight(0, m_aspLight[1]);
    m_spTeapot->AttachEffect(pEffect);
    m_spScene->AttachChild(pSceneLoaded);

    // 创建一个quad.
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);
    tempAttr.SetTCoordChannels(1, 2);
    StandardMesh tempSM(tempAttr);
    m_spQuad = tempSM.Rectangle(2, 2, 5.0f, 5.0f);
    m_spQuad->Local.SetTranslate(Vector3f(0.0f, -2.0f, 4.0f));
    m_spQuad->AttachGlobalState(pBlueMaterial);

    pEffect = SE_NEW OGLES1FixedEffect(2, 1);
    pEffect->SetTexture(0, m_spTexture1);
    pEffect->SetTexture(1, m_spTexture2);
    pEffect->SetLight(0, m_aspLight[1]);
    m_spQuad->AttachEffect(pEffect);
    m_spScene->AttachChild(m_spQuad);
}
//----------------------------------------------------------------------------
