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
    shark_position_.x = SHARK_START_POSITION_X_;
    shark_position_.y = SHARK_START_POSITION_Y_;
    shark_position_.z = SHARK_START_POSITION_Z_;

    shark_speed_ = SHARK_MOVE_SPEED_;

    fishing_rod_position_.x = FISHING_ROD_START_POSITION_X_;
    fishing_rod_position_.y = FISHING_ROD_START_POSITION_Y_;
    fishing_rod_position_.z = FISHING_ROD_START_POSITION_Z_;

    fishing_rod_speed_ = FISHING_ROD_START_SPEED_;
    fishing_rod_direction = right;

    towards_fishing_rod_speed_ = TOWARDS_FISHING_ROD_START_SPEED_;

    gauge_x_         = GAUGE_START_POSITION_X_;
    gauge_y_         = GAUGE_START_POSITION_Y_;
    gauge_red_z_     = GAUGE_RED_POSITION_Z_;
    gauge_blue_z_    = GAUGE_BLUE_POSITION_Z_;
    gauge_red_width_ = GAUGE_RED_WIDTH_START_;
    gauge_display_flg = 0;

    tap_flg_ = 0;

    count_down_ = COUNT_DOWN_START_;
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


    // グラフィックリソースの初期化処理

    tap_font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 50);

    gauge_red_sprite_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Gauge_Red_.png");
    gauge_blue_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Gauge_Blue_.png");

    shark_sprite_      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Fish_Shark.png");

    fishing_rod_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Fishing_Tsurizao_Nagezao.png");
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

    SharkUpdate(deltaTime);
    FishingRodUpdate(deltaTime);

    if (DXTK->KeyEvent->pressed.T) {
        if (gauge_display_flg == 0) {
            gauge_display_flg = 1;
        }
        else {
            gauge_display_flg = 0;
            gauge_red_width_ = GAUGE_RED_WIDTH_START_;
        }
    }
    if (gauge_display_flg == 1) {
        GaugeUpdate(deltaTime);
    }

    return NextScene::Continue;
}

void MainScene::SharkUpdate(const float deltaTime)
{
    constexpr float SPEED = 300.0f;
    const float SQUARE_X =  DXTK->GamePadState[0].thumbSticks.leftX;
    const float SQUARE_Y = -DXTK->GamePadState[0].thumbSticks.leftY;

    SimpleMath::Vector3 movement = SimpleMath::Vector3::Zero;

    movement.x = SQUARE_X * sqrt(1.0f - 0.5f * SQUARE_Y * SQUARE_Y);
    movement.y = SQUARE_Y * sqrt(1.0f - 0.5f * SQUARE_X * SQUARE_X);

    shark_position_ += movement * SPEED * deltaTime;
    shark_position_.Clamp(
        SimpleMath::Vector3(SHARK_LEFT_LIMIT_POSITION_X_, SHARK_UP_LIMIT_POSITION_Y_, 0.0f),
        SimpleMath::Vector3(SHARK_RIGHT_LIMIT_POSITION_X_, SHARK_DOWN_LIMIT_POSITION_Y_, 0.0f)
    );

    SimpleMath::Vector3 towards_fishing_rod_ = fishing_rod_position_ - shark_position_;
    towards_fishing_rod_.Normalize();
    towards_fishing_rod_ *= towards_fishing_rod_speed_ * deltaTime;
    shark_position_ += towards_fishing_rod_;

}

void MainScene::FishingRodUpdate(const float deltaTime)
{
    if (fishing_rod_direction == right) {
        fishing_rod_position_.x += fishing_rod_speed_ * deltaTime;
        if (fishing_rod_position_.x >= FISHING_ROD_RIGHT_LIMIT_POSITION_X_) {
            fishing_rod_direction = left;
        }
    }
    else {
        fishing_rod_position_.x -= fishing_rod_speed_ * deltaTime;
        if (fishing_rod_position_.x <= FISHING_ROD_LEFT_LIMIT_POSITION_X_) {
            fishing_rod_direction = right;
        }
    }

    fishing_rod_position_.Clamp(
        SimpleMath::Vector3(FISHING_ROD_LEFT_LIMIT_POSITION_X_, FISHING_ROD_UP_LIMIT_POSITION_Y_, 0.0f),
        SimpleMath::Vector3(FISHING_ROD_RIGHT_LIMIT_POSITION_X_, FISHING_ROD_DOWN_LIMIT_POSITION_Y_, 0.0f)
    );
}

void MainScene::GaugeUpdate(const float deltaTime)
{
    // 赤ゲージ
    gauge_red_width_ += GAUGE_RED_WIDTH_ADD_SPEED_ * deltaTime;

    if (DXTK->KeyEvent->pressed.Space) {
        gauge_red_width_ -= GAUGE_RED_WIDTH_TAKE_SPEED_ * deltaTime;
        tap_flg_ = 1;
    }
    else {
        tap_flg_ = 0;
    }

    if (gauge_red_width_ >= GAUGE_RED_WIDTH_LIMIT_) {
        gauge_red_width_  = GAUGE_RED_WIDTH_LIMIT_;
    }

    if (gauge_red_width_ <= 0.0f) {
        gauge_red_width_  = 0.0f;
    }
}



// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 0));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->DrawSimple(shark_sprite_.Get(), shark_position_);

    DX9::SpriteBatch->DrawSimple(fishing_rod_sprite_.Get(), fishing_rod_position_);

    if (gauge_display_flg == 1) {
        DX9::SpriteBatch->DrawSimple(
            gauge_red_sprite_.Get(),
            SimpleMath::Vector3(gauge_x_, gauge_y_, gauge_red_z_),
            RectWH(0.0f, 0.0f, gauge_red_width_, GAUGE_RED_HEIGHT_START_)
        );

        DX9::SpriteBatch->DrawSimple(gauge_blue_sprite_.Get(), SimpleMath::Vector3(gauge_x_, gauge_y_, gauge_blue_z_));

        if (tap_flg_ == 0) {
            DX9::SpriteBatch->DrawString(
                tap_font_.Get(),
                SimpleMath::Vector2(530.0f, 150.0f),
                DX9::Colors::RGBA(0, 0, 0, 255),
                L"TAP!!"
            );
        }
    }
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

