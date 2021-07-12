//
// TutorialScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
TutorialScene::TutorialScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void TutorialScene::Initialize()
{
    // 背景
    bg_sky_position_ = SimpleMath::Vector3(0.0f, 0.0f, BG_SKY_POSITION_Z_);

    bg_front_sea_position_ = SimpleMath::Vector3(BG_FRONT_SEA_START_POSITION_X_, 0.0f, BG_FRONT_SEA_POSITION_Z_);

    bg_behind_sea_position_ = SimpleMath::Vector3(0.0f, 0.0f, BG_BEHIND_SEA_POSITION_Z_);

    bg_frame_position_ = SimpleMath::Vector3(0.0f, 0.0f, BG_FRAME_POSITION_Z_);

    // サメ
    shark_position_ = SimpleMath::Vector3(SHARK_START_POSITION_X_, SHARK_START_POSITION_Y_, SHARK_START_POSITION_Z_);

    shark_direction_flg_ = 1;
    shark_count_flg = 0;

    shark_move_time_ = 0.0f;

    shark_speed_ = SHARK_MOVE_SPEED_;
    shark_speed_up_ = SHARK_MOVE_UP_SPEED_;

    shark_sprite_x_ = 0.0f;
    shark_sprite_time_ = 0.0f;

    // サメのゲージ
    shark_gauge_position_.x = SHARK_GAUGE_START_POSITION_X_;
    shark_gauge_position_.y = SHARK_GAUGE_START_POSITION_Y_;
    shark_gauge_position_.z = SHARK_GAUGE_START_POSITION_Z_;

    shark_gauge_empty_position_.x = SHARK_GAUGE_START_POSITION_X_;
    shark_gauge_empty_position_.y = SHARK_GAUGE_START_POSITION_Y_;
    shark_gauge_empty_position_.z = SHARK_GAUGE_START_POSITION_Z_;

    shark_gauge_x_ = 0.0f;
    shark_gauge_speed_ = 0.0f;

    shark_gauge_flg_ = 0;

    shark_gauge_stop_time_ = 0.0f;

    shark_standby_time_ = 0.0f;
    shark_standby_flg_ = 0;

    // ゲージの差
    gauge_difference_ = nothing;

    // 釣り人ライン
    angler_line_position_ = SimpleMath::Vector3(ANGLER_LINE_START_POSITION_X_, ANGLER_LINE_START_POSITION_Y_, ANGLER_LINE_START_POSITION_Z_);
    angler_line_move_direction_ = rightmove;

    angler_line_value_ = 0.0f;

    black_alpha_ = 0;
    black_flg_ = 0;

    tutorial_time_ = 0.0f;
    gauge_stop_after_time_ = 0.0f;
    gauge_stop_after_flg_ = 0;

    next_scene_flg_ = 0;
}

// Allocate all memory the Direct3D and Direct2D resources.
void TutorialScene::LoadAssets()
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

    bg_sky_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Haikei.png");
    bg_front_sea_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"1_00000 (1).png");
    bg_behind_sea_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"1_00000.png");
    bg_frame_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"image0_11.png");

    shark_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"shark.light.in.png");
    shark_behind_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"left1.png");

    shark_gauge_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"shark_gauge_empty.png");
    shark_gauge_empty_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"shark_gauge.png");

    angler_line_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Angler_Line.png");

    black_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Black.png");

}

// Releasing resources required for termination.
void TutorialScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void TutorialScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TutorialScene::OnRestartSound()
{

}

// Updates the scene.
NextScene TutorialScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.

    BGUpdate      (deltaTime);
    SharkUpdate   (deltaTime);
    TutorialUpdate(deltaTime);

    if (next_scene_flg_ == 1) {
        return NextScene::MainScene;
    }

    return NextScene::Continue;
}

void TutorialScene::BGUpdate(const float deltaTime)
{
    // 背景の移動
    bg_front_sea_position_.x -= BG_SPEED_ * deltaTime;
    bg_behind_sea_position_.x -= BG_FRONT_SPEED_ * deltaTime;

    if (bg_front_sea_position_.x <= -BG_SIZE_X_) {
        bg_front_sea_position_.x = 0.0f;
    }

    if (bg_behind_sea_position_.x <= -BG_SIZE_X_) {
        bg_behind_sea_position_.x = 0.0f;
    }

    if (DXTK->KeyState->Right || black_flg_ == 1) {
        black_alpha_ += 255 * deltaTime;
    }

    if (DXTK->KeyState->Left || black_flg_ == 0) {
        black_alpha_ -= 500 * deltaTime;
    }

    if (black_alpha_ >= 205) {
        black_alpha_ = 205;
    }

    if (black_alpha_ <= 0) {
        black_alpha_ = 0;
    }
}

void TutorialScene::SharkUpdate(const float deltaTime)
{
    SharkMoveUpdate(deltaTime);
    // SharkHPUpdate    (deltaTime);
    // SharkAtackUpdate (deltaTime);
    SharkSpriteUpdate(deltaTime);
    SharkGaugeUpdate(deltaTime);
    GaugeDifferenceUpdate(deltaTime);
    AnglerGaugeUpdate(deltaTime);
}

void TutorialScene::SharkGaugeUpdate(const float deltaTime)
{
    if (shark_gauge_x_ < 0.0f) {
        shark_gauge_x_ = 0.0f;
    }

    // サメの引っ張りゲージ
    if (shark_gauge_flg_ == 0) {
        shark_gauge_speed_ += SHARK_GAUGE_GROW_SPEED_ * deltaTime;

        shark_gauge_x_ += shark_gauge_speed_ * deltaTime;

        if (shark_gauge_x_ > SHARK_GAUGE_SIZE_X_) {
            shark_gauge_x_ = 0.0f;
            shark_gauge_speed_ = 0.0f;
        }

        if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
            shark_gauge_flg_ = 1;
        }
    }

    else {
        shark_gauge_stop_time_ += deltaTime;

        if (shark_gauge_stop_time_ >= SHARK_GAUGE_STOP_TIME_) {
            shark_gauge_x_ -= SHARK_GAUGE_DECREASE_SPEED_ * deltaTime;
            if (shark_gauge_x_ < 0.0f) {
                shark_standby_flg_ = 1;

                if (shark_standby_flg_ == 1) {
                    shark_standby_time_ += deltaTime;

                    if (shark_standby_time_ >= 3.0f) {
                        shark_gauge_stop_time_ = 0.0f;
                        shark_gauge_speed_ = 0.0f;
                        shark_gauge_flg_ = 0;
                        shark_standby_time_ = 0.0f;
                        shark_standby_flg_ = 0;
                    }
                }
            }
        }
    }
}

void TutorialScene::GaugeDifferenceUpdate(const float deltaTime)
{
    // サメと釣り人のゲージの差の判定
    if (shark_gauge_flg_ == 1) {
        // サメ大

        if (shark_gauge_x_ - angler_line_position_.x >= SHARK_LARGE_LINE_POSITION_) {
            gauge_difference_ = sharklarge;
        }
        

        if (shark_gauge_stop_time_ >= SHARK_GAUGE_STOP_TIME_) {
            gauge_difference_ = nothing;
        }
    }
    /*else {
        gauge_difference_ = nothing;
    }*/
}

void TutorialScene::SharkSpriteUpdate(const float deltaTime)
{
    shark_sprite_time_ += deltaTime;

    if (shark_sprite_time_ >= SHARK_SPRITE_X_CHANGE_TIME_) {
        shark_sprite_x_ += SHARK_SIZE_X_;
        shark_sprite_time_ -= SHARK_SPRITE_X_CHANGE_TIME_;
        if (shark_sprite_x_ >= SHARK_SPRITE_SIZE_X_LIMIT_) {
            shark_sprite_x_ -= SHARK_SPRITE_SIZE_X_LIMIT_;
        }
    }
}

void TutorialScene::SharkMoveUpdate(const float deltaTime)
{
    constexpr float SPEED = 300.0f;
    const float SQUARE_X = DXTK->GamePadState[0].thumbSticks.leftX;
    const float SQUARE_Y = -DXTK->GamePadState[0].thumbSticks.leftY;

    SimpleMath::Vector3 movement = SimpleMath::Vector3::Zero;

    movement.x = SQUARE_X * sqrt(1.0f - 0.5f * SQUARE_Y * SQUARE_Y);
    movement.y = SQUARE_Y * sqrt(1.0f - 0.5f * SQUARE_X * SQUARE_X);

    if (movement.y < 0.0f) {
        shark_speed_up_ += SHARK_MOVE_UP_SPEED_UP_ * deltaTime;
        if (shark_speed_up_ >= SHARK_MOVE_UP_SPEED_UP_LIMIT_) {
            shark_speed_up_ = SHARK_MOVE_UP_SPEED_UP_LIMIT_;
        }
    }
    else {
        shark_speed_up_ = SHARK_MOVE_UP_SPEED_;
    }

    
    shark_position_ += movement * SPEED * deltaTime;
    

    shark_position_.Clamp(
        SimpleMath::Vector3(SHARK_LEFT_LIMIT_POSITION_X_, SHARK_UP_LIMIT_POSITION_Y_, 0.0f),
        SimpleMath::Vector3(SHARK_RIGHT_LIMIT_POSITION_X_, SHARK_DOWN_LIMIT_POSITION_Y_, 0.0f)
    );

    if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
        shark_direction_flg_ = 0;
    }

    if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
        shark_direction_flg_ = 1;
    }

    if (gauge_difference_ == nothing) {
        //shark_position_.x -= SHARK_PULL_SPEED_NOTHING_ * deltaTime;
    }
    else if (gauge_difference_ == sharklarge) {
        shark_position_.x += SHARK_PULL_SPEED_SHARKLARGE_ * deltaTime;
    }
}

void TutorialScene::AnglerGaugeUpdate(const float deltaTime)
{
    // 釣り人ゲージのラインの動き
    if (shark_gauge_flg_ == 0) {
        if (angler_line_move_direction_ == rightmove) {
            angler_line_position_.x += ANGLER_LINE_MOVE_SPEED_ * deltaTime;
            if (angler_line_position_.x > ANGLER_LINE_LIMIT_RIGHT_) {
                angler_line_move_direction_ = leftmove;
            }
        }
        else if (angler_line_move_direction_ == leftmove) {
            angler_line_position_.x -= ANGLER_LINE_MOVE_SPEED_ * deltaTime;
            if (angler_line_position_.x < ANGLER_LINE_LIMIT_LEFT_) {
                angler_line_move_direction_ = rightmove;
            }
        }
    }
}

void TutorialScene::TutorialUpdate(const float deltaTime)
{
    tutorial_time_ += deltaTime;

    if (tutorial_time_ >= 2.0f && tutorial_time_ < 4.0f) {
        black_flg_ = 1;
    }

    if (tutorial_time_ >= 4.0f) {
        shark_gauge_flg_ = 1;
        black_flg_ = 0;
    }

    if (tutorial_time_ >= 7.0f) {
        next_scene_flg_ = 1;
    }
}

// Draws the scene.
void TutorialScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();

    // 釣り糸描画
    DX9::VertexScreen vertex[6];
    vertex[0].position = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    vertex[0].color = DX9::Colors::RGBA(220, 220, 220, 255);

    vertex[1].position = SimpleMath::Vector3(shark_position_.x + SHARK_LINE_DIFFERENCE_X_, shark_position_.y + SHARK_LINE_DIFFERENCE_Y_, 0.0f);
    vertex[1].color = DX9::Colors::RGBA(220, 220, 220, 255);

    vertex[2] = vertex[0];
    vertex[2].position = vertex[2].position + SimpleMath::Vector3(FISHING_LINE_2_DIFFERENCE_, 0.0f, 0.0f);
    vertex[3] = vertex[1];
    vertex[3].position = vertex[3].position + SimpleMath::Vector3(FISHING_LINE_2_DIFFERENCE_, 0.0f, 0.0f);

    vertex[4] = vertex[0];
    vertex[4].position = vertex[2].position + SimpleMath::Vector3(FISHING_LINE_3_DIFFERENCE_, 0.0f, 0.0f);
    vertex[5] = vertex[1];
    vertex[5].position = vertex[3].position + SimpleMath::Vector3(FISHING_LINE_3_DIFFERENCE_, 0.0f, 0.0f);

    DXTK->Direct3D9->DrawInstanced(D3DPT_LINELIST, 3, vertex, DX9::VertexScreen::FVF);

    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->DrawSimple(bg_sky_sprite_.Get(), bg_sky_position_);
    DX9::SpriteBatch->DrawSimple(bg_front_sea_sprite_.Get(), bg_front_sea_position_);
    DX9::SpriteBatch->DrawSimple(bg_behind_sea_sprite_.Get(), bg_behind_sea_position_);
    DX9::SpriteBatch->DrawSimple(bg_frame_sprite_.Get(), bg_frame_position_);

    if (shark_direction_flg_ == 1) {
        DX9::SpriteBatch->DrawSimple(
            shark_sprite_.Get(),
            shark_position_,
            RectWH(shark_sprite_x_, 0.0f, SHARK_SIZE_X_, SHARK_SIZE_Y_)
        );
    }
    else {
        DX9::SpriteBatch->DrawSimple(shark_behind_sprite_.Get(), shark_position_);
    }

    DX9::SpriteBatch->DrawSimple(
        shark_gauge_.Get(),
        shark_gauge_position_,
        RectWH(0.0f, 0.0f, SHARK_GAUGE_SIZE_X_, SHARK_GAUGE_SIZE_Y_)
    );

    DX9::SpriteBatch->DrawSimple(
        shark_gauge_empty_.Get(),
        shark_gauge_empty_position_,
        RectWH(0.0f, 0.0f, shark_gauge_x_, SHARK_GAUGE_SIZE_Y_)
    );

    DX9::SpriteBatch->DrawSimple(angler_line_.Get(), angler_line_position_);

    if (shark_gauge_flg_ == 1) {
        if (gauge_difference_ == sharklarge) {
            DX9::SpriteBatch->DrawString(
                tap_font_.Get(),
                SimpleMath::Vector2(320.0f, 300.0f),
                DX9::Colors::RGBA(0, 0, 0, 255),
                L"引っ張る大"
            );
        }
    }

    DX9::SpriteBatch->DrawSimple(
        black_sprite_.Get(), 
        SimpleMath::Vector3(0.0f, 0.0f, -100.0f),
        nullptr,
        DX9::Colors::RGBA(0, 0, 0, black_alpha_)
        );

    DX9::SpriteBatch->DrawString(
        tap_font_.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%d", black_alpha_
    );

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