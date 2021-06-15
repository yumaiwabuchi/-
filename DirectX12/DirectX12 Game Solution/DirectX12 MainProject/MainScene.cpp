//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    
    
    waveX = 0;


}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, 1280.0f, 720.0f,
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();


    // �O���t�B�b�N���\�[�X�̏���������

    bottun_font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS �S�V�b�N", 20);

    //�w�i
    Main_bg_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"blue_bg.png");
    //�w�i�@�A�j���[�V����
    sun_wave_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"���z��.png");

    //���L�����N�^�[
    Main_fish_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"fish.png");

}

// Releasing resources required for termination.
void MainScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.

    //�w�i�@�A�j���[�V����
    if (true)
        waveX += 20;

    if (waveX >= 2560)
        waveX = 0;


    return NextScene::Continue;
}



// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 255, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    //�w�i�@�摜
    DX9::SpriteBatch->DrawSimple(Main_bg_.Get(), SimpleMath::Vector3( 0, 0, 0));
    //�w�i�@�A�j���[�V����
    DX9::SpriteBatch->DrawSimple(sun_wave_.Get(), SimpleMath::Vector3( 0, 90, -1),
    RectWH(waveX, 0, 1280, 120));


    //���@�摜
    DX9::SpriteBatch->DrawSimple(Main_fish_.Get(), SimpleMath::Vector3(0, 0, -1));



    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    DXTK->Direct3D9->UpdateResource();

    DXTK->ResetCommand();
    DXTK->ClearRenderTarget(Colors::CornflowerBlue);

    const auto heapes = descriptorHeap->Heap();
    DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

    spriteBatch->Begin(DXTK->CommandList);
    spriteBatch->Draw(
        dx9GpuDescriptor,
        XMUINT2(1280, 720),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}

