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
    bg_sky_position_.x = 0.0f;
    bg_sky_position_.y = 0.0f;
    bg_sky_position_.z = BG_SKY_POSITION_Z_;

    bg_front_sea_position_.x = BG_FRONT_SEA_START_POSITION_X_;
    bg_front_sea_position_.y = 0.0f;
    bg_front_sea_position_.z = BG_FRONT_SEA_POSITION_Z_;

    bg_behind_sea_position_.x = 0.0f;
    bg_behind_sea_position_.y = 0.0f;
    bg_behind_sea_position_.z = BG_BEHIND_SEA_POSITION_Z_;

    bg_frame_position_.x = 0.0f;
    bg_frame_position_.y = 0.0f;
    bg_frame_position_.z = BG_FRAME_POSITION_Z_;

    shark_position_.x = SHARK_START_POSITION_X_;
    shark_position_.y = SHARK_START_POSITION_Y_;
    shark_position_.z = SHARK_START_POSITION_Z_;

    shark_direction_flg_ = 0;
    shark_count_flg      = 0;

    shark_move_time_ = 0.0f;

    shark_speed_    =    SHARK_MOVE_SPEED_;
    shark_speed_up_ = SHARK_MOVE_UP_SPEED_;

    shark_hp_cover_position_.x = SHARK_HP_POSITION_X_;
    shark_hp_cover_position_.y = SHARK_HP_POSITION_Y_;
    shark_hp_cover_position_.z = SHARK_HP_POSITION_Z_;

    shark_hp_position_x_ = SHARK_HP_POSITION_X_;
    shark_hp_position_y_ = SHARK_HP_POSITION_Y_;
    shark_hp_position_z_ = SHARK_HP_POSITION_Z_;

    right_input_time_ = 0.0f;
    left_input_time_  = 0.0f;

    shark_hp_ = SHARK_HP_START_;
    angler_hp_ = ANGLER_HP_START_;

    shark_hp_flg_ = 0;
    angler_hp_flg_ = 0;

    atack_flg_      =    0;
    atack_move_flg_ =    0;
    atack_count_    =    0;
    atack_time_     = 0.0f;
    atack_move_y_   = 0.0f;

    fishing_rod_position_.x = FISHING_ROD_START_POSITION_X_;
    fishing_rod_position_.y = FISHING_ROD_START_POSITION_Y_;
    fishing_rod_position_.z = FISHING_ROD_START_POSITION_Z_;

    fishing_rod_speed_    = FISHING_ROD_START_SPEED_;
    fishing_rod_direction =                    right;

    angler_hp_cover_position_.x = ANGLER_HP_POSITION_X_;
    angler_hp_cover_position_.y = ANGLER_HP_POSITION_Y_;
    angler_hp_cover_position_.z = ANGLER_HP_POSITION_Z_;

    angler_hp_position_.x = ANGLER_HP_POSITION_X_;
    angler_hp_position_.y = ANGLER_HP_POSITION_Y_;
    angler_hp_position_.z = ANGLER_HP_POSITION_Z_;

    towards_fishing_rod_speed_ = TOWARDS_FISHING_ROD_START_SPEED_;

    gauge_x_          = GAUGE_START_POSITION_X_;
    gauge_y_          = GAUGE_START_POSITION_Y_;
    gauge_red_z_      =   GAUGE_RED_POSITION_Z_;
    gauge_blue_z_     =  GAUGE_BLUE_POSITION_Z_;
    gauge_red_width_  =  GAUGE_RED_WIDTH_START_;
    gauge_display_flg =                       0;

    tap_flg_ = 0;

    count_down_ = COUNT_DOWN_START_;

    dead_zone_time = 0.0f;

    danger_flg        =    0;
    danger_alpha_     = 0.0f;
    danger_alpha_flg_ =    0;

    game_over_flg_ = 0;

    game_clear_flg_ = 0;

    game_time_ = 0.0f;
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

    tap_font_   = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 50);
    debug_font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 25);

    bg_sky_sprite_        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Haikei.png");
    bg_front_sea_sprite_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"1_00000 (1).png");
    bg_behind_sea_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"1_00000.png");
    bg_frame_sprite_      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"image0_11.png");

    gauge_red_sprite_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Gauge_Red_.png");
    gauge_blue_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Gauge_Blue_.png");

    shark_hp_empty_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.under.png");
    shark_hp_hull_sprite_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.red.2.psd.png");

    shark_sprite_        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Fish_Shark.png");
    shark_behind_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Fish_Shark_Behind.png");

    fishing_rod_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ship.png");

    angler_hp_empty_sprite_      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.under.png");
    angler_hp_hull_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.red.2.psd.png");

    dead_zone_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dead_Zone.png");

    danger_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Danger.png");
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

    BGUpdate         (deltaTime);
    GameTimeUpdate   (deltaTime);
    SharkUpdate      (deltaTime);
    FishingRodUpdate (deltaTime);
    DeadZoneUpdate   (deltaTime);
    AnglerUpdate     (deltaTime);

    if (DXTK->KeyEvent->pressed.T) {
        if (gauge_display_flg == 0) {
            gauge_display_flg  = 1;
        }
        else {
            gauge_display_flg = 0;
            gauge_red_width_  = GAUGE_RED_WIDTH_START_;
        }
    }

    if (gauge_display_flg == 1) {
        GaugeUpdate(deltaTime);
    }

    if (game_clear_flg_ == 1) {
        DXTK->GamePadVibration(0.0f, 0.0f, 0.0f);
        return NextScene::WinScene;
    }

    if (game_over_flg_ == 1) {
        DXTK->GamePadVibration(0.0f, 0.0f, 0.0f);
        return NextScene::LossScene;

    }

    return NextScene::Continue;
}

void MainScene::BGUpdate(const float deltaTime) 
{
    bg_front_sea_position_.x -= BG_SPEED_ * deltaTime;
    bg_behind_sea_position_.x -= BG_FRONT_SPEED_ * deltaTime;

    if (bg_front_sea_position_.x <= -BG_SIZE_X_){
        bg_front_sea_position_.x = 0.0f;
    }

    if (bg_behind_sea_position_.x <= -BG_SIZE_X_) {
        bg_behind_sea_position_.x = 0.0f;
    }
}

void MainScene::GameTimeUpdate(const float deltaTime)
{
    game_time_ += deltaTime;
}

void MainScene::SharkUpdate(const float deltaTime)
{
    SharkMoveUpdate (deltaTime);
    SharkHPUpdate   (deltaTime);
    SharkAtackUpdate(deltaTime);
}

void MainScene::SharkMoveUpdate(const float deltaTime)
{
    constexpr float SPEED = 300.0f;
    const float SQUARE_X = DXTK->GamePadState[0].thumbSticks.leftX;
    const float SQUARE_Y = -DXTK->GamePadState[0].thumbSticks.leftY;

    SimpleMath::Vector3 movement = SimpleMath::Vector3::Zero;

    movement.x = SQUARE_X * sqrt(1.0f - 0.5f * SQUARE_Y * SQUARE_Y);
    movement.y = SQUARE_Y * sqrt(1.0f - 0.5f * SQUARE_X * SQUARE_X);

    if (movement.y > 0.0f) {
        movement.y = 0.0f;
    }

    if (movement.y < 0.0f) {
        shark_speed_up_ += SHARK_MOVE_UP_SPEED_UP_ * deltaTime;
        if (shark_speed_up_ >= SHARK_MOVE_UP_SPEED_UP_LIMIT_) {
            shark_speed_up_  = SHARK_MOVE_UP_SPEED_UP_LIMIT_;
        }
    }
    else {
        shark_speed_up_ = SHARK_MOVE_UP_SPEED_;
    }

    if (shark_hp_flg_ == 0) {
        shark_position_ += movement * SPEED * shark_speed_up_ * deltaTime;
    }

    shark_position_.Clamp(
        SimpleMath::Vector3(SHARK_LEFT_LIMIT_POSITION_X_, SHARK_UP_LIMIT_POSITION_Y_, 0.0f),
        SimpleMath::Vector3(SHARK_RIGHT_LIMIT_POSITION_X_, SHARK_DOWN_LIMIT_POSITION_Y_, 0.0f)
    );

    SimpleMath::Vector3 towards_fishing_rod_ = fishing_rod_position_ - shark_position_;
    towards_fishing_rod_.Normalize();

    if (angler_hp_ < ANGLER_HP_HALF_) {
        towards_fishing_rod_ *= towards_fishing_rod_speed_ * deltaTime;
    }
    else {
        towards_fishing_rod_ *= (towards_fishing_rod_speed_ + TOWARDS_FISHING_ROD_SPEED_UP_) * deltaTime;
    }

    shark_position_ += towards_fishing_rod_;

    
    if ((shark_position_.x + SHARK_SIZE_HALF_X_) - (fishing_rod_position_.x + FISHING_ROD_SIZE_HALF_X_) > SHARK_ROD_DIFFERENCE_) {
        if (right_input_time_ <= INPUT_TIME_LIMIT_) {

            if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_SIDE_ * deltaTime;
                right_input_time_ += deltaTime;
                shark_direction_flg_ = 1;
            }
        }
        else {
            if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_SIDE_ * deltaTime;
                right_input_time_  = 0.0f ;
                shark_direction_flg_ = 0;
            }
        }

        if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
            if (shark_count_flg == 1) {
                shark_count_flg  = 0;
                shark_direction_flg_ = 1;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }

        if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
            if (shark_count_flg == 0) {
                shark_count_flg  = 1;
                shark_direction_flg_ = 0;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }
    }
    else if ((shark_position_.x + SHARK_SIZE_HALF_X_) - (fishing_rod_position_.x + FISHING_ROD_SIZE_HALF_X_) < -SHARK_ROD_DIFFERENCE_) {
        if (left_input_time_ <= INPUT_TIME_LIMIT_) {

            if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_SIDE_ * deltaTime;
                left_input_time_  += deltaTime;
                shark_direction_flg_ = 0;
                if (shark_count_flg == 0) {
                    shark_count_flg  = 1;
                    if (atack_flg_ == 0) {
                        atack_count_ += 1;
                    }
                }
            }
        }
        else {
            if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_SIDE_ * deltaTime;
                left_input_time_ = 0.0f;
                shark_direction_flg_ = 1;
                if (shark_count_flg == 1) {
                    shark_count_flg  = 0;
                    if (atack_flg_ == 0) {
                        atack_count_ += 1;
                    }
                }
            }
        }

        if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
            if (shark_count_flg == 0) {
                shark_count_flg  = 1;
                shark_direction_flg_ = 0;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }

        if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
            if (shark_count_flg == 1) {
                shark_count_flg  = 0;
                shark_direction_flg_ = 1;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }
    }
    else {
        if (shark_direction_flg_ == 0) {
            if (DXTK->KeyEvent->pressed.D || movement.x > 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_Y_ * deltaTime;
                shark_direction_flg_ = 1;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }

        if (shark_direction_flg_ == 1) {
            if (DXTK->KeyEvent->pressed.A || movement.x < 0.0f) {
                shark_position_.y += SHARK_MOVE_SPEED_Y_ * deltaTime;
                shark_direction_flg_ = 0;
                if (atack_flg_ == 0) {
                    atack_count_ += 1;
                }
            }
        }
    }


    if (shark_hp_flg_ == 0) {
        if (DXTK->KeyState->W) {
            shark_position_.y -= SHARK_MOVE_SPEED_ * deltaTime;
        }

        /*if (DXTK->KeyState->S) {
            shark_position_.y += SHARK_MOVE_SPEED_ * deltaTime;
        }*/

        if (DXTK->KeyState->D) {
            shark_position_.x += SHARK_MOVE_SPEED_ * deltaTime;
        }

        if (DXTK->KeyState->A) {
            shark_position_.x -= SHARK_MOVE_SPEED_ * deltaTime;
        }

        
    }

}

void MainScene::SharkAtackUpdate(const float deltaTime)
{

    if (atack_count_ >= 1) {
        atack_time_ += deltaTime;
        if (atack_time_ >= SHARK_ATACK_TIME_) {
            atack_count_ = 0;
            atack_time_ = 0.0f;
        }
    }
    if (atack_count_ >= 10) {
        atack_flg_ = 1;
        atack_count_ = 0;
    }

    if (atack_flg_ == 1) {
        shark_position_.y += atack_move_y_ * deltaTime;
        DXTK->GamePadVibration(0, 1.0f, 1.0f);

        if (atack_move_flg_ == 0) {
            atack_move_y_ += SHARK_ATACK_GROW_SPEED_ * deltaTime;
            angler_hp_position_.y += ANGLER_POSITION_SPEED_UP_Y_ * deltaTime;
            angler_hp_ += ANGLER_POSITION_SPEED_UP_Y_ * deltaTime;
            shark_hp_ += SHARK_HP_DAMAGE_ATACK * deltaTime;
            shark_hp_position_y_ += SHARK_HP_DAMAGE_ATACK * deltaTime;
            if (atack_move_y_ >= SHARK_ATACK_LIMIT_SPEED_) {
                atack_move_flg_ = 1;
            }
        }
        if (atack_move_flg_ == 1) {
            atack_move_y_ -= SHARK_ATACK_DECREASE_SPEED_ * deltaTime;
            if (atack_move_y_ <= 0.0f) {
                atack_move_y_ = 0.0f;
                atack_move_flg_ = 0;
                atack_flg_ = 0;
            }
        }
    }
    else {
        DXTK->GamePadVibration(0, 0.0f, 0.0f);
    }
}

void MainScene::SharkHPUpdate(const float deltaTime)
{

    if (shark_hp_ <= 0.0f) {
        shark_hp_ = 0.0f;
    }

    if (shark_hp_ >= SHARK_HP_DOWN_LIMIT_) {
        shark_hp_ = SHARK_HP_DOWN_LIMIT_;
    }

    if (shark_hp_flg_ == 0) {

        if (shark_position_.y + SHARK_SIZE_HALF_Y_ <= SHARK_HP_DAMAGE_SPEED_BORDER_) {
            shark_hp_ += SHARK_HP_DAMAGE_SLOWLY_ * deltaTime;
            shark_hp_position_y_ += SHARK_HP_DAMAGE_SLOWLY_ * deltaTime;
        }
        else {
            shark_hp_ += SHARK_HP_DAMAGE_ * deltaTime;
            shark_hp_position_y_ += SHARK_HP_DAMAGE_ * deltaTime;
        }

        if (shark_hp_ >= SHARK_HP_DOWN_LIMIT_) {
            shark_hp_flg_  = 1;
            game_over_flg_ = 1;
        }
    }

    else {
        
    }
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

void MainScene::AnglerUpdate(const float deltaTime)
{
    if (angler_hp_ <= 0.0f) {
        angler_hp_ = 0.0f;
    }

    if (angler_hp_ >= ANGLER_HP_DOWN_LIMIT_) {
        angler_hp_ = ANGLER_HP_DOWN_LIMIT_;
    }

    if (angler_hp_flg_ == 0) {
        angler_hp_ += ANGLER_POSITION_SPEED_Y_ * deltaTime;
        angler_hp_position_.y += ANGLER_POSITION_SPEED_Y_ * deltaTime;
        
        if (angler_hp_ >= ANGLER_HP_DOWN_LIMIT_) {
            angler_hp_flg_ = 1;
            game_clear_flg_ = 1;
        }
    }
    else {

    }
}

void MainScene::GaugeUpdate(const float deltaTime)
{
    // 赤ゲージ
    gauge_red_width_ += GAUGE_RED_WIDTH_ADD_SPEED_ * deltaTime;

    if (DXTK->KeyEvent->pressed.Space || 
        DXTK->GamePadEvent[0].leftShoulder == GamePad::ButtonStateTracker::PRESSED ||
        DXTK->GamePadEvent[0].rightShoulder == GamePad::ButtonStateTracker::PRESSED) {
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

void MainScene::DeadZoneUpdate(const float deltaTime)
{
    if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_), RectWH(DEAD_ZONE_LEFT_, DEAD_ZONE_UP_, DEAD_ZONE_RIGHT_, DEAD_ZONE_DOWN_))) {
        // あたったとき
        dead_zone_time += deltaTime;
        danger_flg = 1;
        danger_alpha_flg_ = Up;
        if (dead_zone_time >= 3.0f) {
            game_over_flg_ = 1;
        }
    }
    else {
        // あたってないとき
        dead_zone_time = 0.0f;
        danger_flg = 0;
    }

    if (danger_flg == 1) {
        if (danger_alpha_flg_ == Up) {
            danger_alpha_ += deltaTime * DANGER_ALPHA_VALUE_SPEED_;
            if (danger_alpha_ <= 0.0f) {
                danger_alpha_ = 0.0f;
                danger_alpha_flg_ = 0;
            }
        }
        else if (danger_alpha_flg_ == Down){
            danger_alpha_ -= deltaTime * DANGER_ALPHA_VALUE_SPEED_;
            if (danger_alpha_ >= DANGER_ALPHA_VALUE_LIMIT_) {
                danger_alpha_ = DANGER_ALPHA_VALUE_LIMIT_;
                danger_alpha_flg_ = 1;
            }
        }
    }
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 0));

    DXTK->Direct3D9->BeginScene();

    // 釣り糸描画
    DX9::VertexScreen vertex[6];
    vertex[0].position = SimpleMath::Vector3(fishing_rod_position_.x + FISHING_ROD_SIZE_HALF_X_, fishing_rod_position_.y + FISHING_ROD_SIZE_HALF_Y_, 0.0f);
    vertex[0].color    = DX9::Colors::RGBA(220, 220, 220, 255);

    vertex[1].position = SimpleMath::Vector3(shark_position_.x + SHARK_LINE_DIFFERENCE_X_, shark_position_.y + SHARK_LINE_DIFFERENCE_Y_, 0.0f);
    vertex[1].color    = DX9::Colors::RGBA(220, 220, 220, 255);

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

    //DX9::SpriteBatch->DrawSimple(dead_zone_sprite_.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));

    if (danger_flg == 1) {
        DX9::SpriteBatch->DrawSimple(
            danger_sprite_.Get(),
            SimpleMath::Vector3(DANGER_POSITION_X_, DANGER_POSITION_Y_, DANGER_POSITION_Z_),
            nullptr,
            DX9::Colors::Alpha(danger_alpha_));
    }

    if (shark_direction_flg_ == 1) {
        DX9::SpriteBatch->DrawSimple(shark_sprite_.Get(), shark_position_);
    }
    else {
        DX9::SpriteBatch->DrawSimple(shark_behind_sprite_.Get(), shark_position_);
    }

    DX9::SpriteBatch->DrawSimple(fishing_rod_sprite_.Get(), fishing_rod_position_);

    /*DX9::SpriteBatch->DrawSimple(shark_hp_empty_sprite_.Get(), SimpleMath::Vector3(shark_hp_position_x_, shark_hp_position_y_, shark_hp_position_z_));*/

    DX9::SpriteBatch->DrawSimple(angler_hp_empty_sprite_.Get(), angler_hp_cover_position_);

    DX9::SpriteBatch->DrawSimple(
        angler_hp_hull_sprite_.Get(),
        SimpleMath::Vector3(angler_hp_position_.x, (int)angler_hp_position_.y, angler_hp_position_.z),
        Rect(0.0f, angler_hp_, ANGLER_HP_RIGHT_LIMIT_, (int)ANGLER_HP_DOWN_LIMIT_)
    );

    DX9::SpriteBatch->DrawSimple(shark_hp_empty_sprite_.Get(), shark_hp_cover_position_);
    DX9::SpriteBatch->DrawSimple(
        shark_hp_hull_sprite_.Get(),
        SimpleMath::Vector3(shark_hp_position_x_, (int)shark_hp_position_y_, shark_hp_position_z_),
        Rect(0.0f, shark_hp_, SHARK_HP_RIGHT_LIMIT_, (int)SHARK_HP_DOWN_LIMIT_)
    );

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

   /* DX9::SpriteBatch->DrawString(
        debug_font_.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%d", atack_count_
    );

    DX9::SpriteBatch->DrawString(
        debug_font_.Get(),
        SimpleMath::Vector2(0.0f, 25.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%f", atack_time_
    );

    DX9::SpriteBatch->DrawString(
        debug_font_.Get(),
        SimpleMath::Vector2(1200.0f, 25.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%.1f", game_time_
    );
    
    DX9::SpriteBatch->DrawString(
        tap_font_.Get(),
        SimpleMath::Vector2(0.0f, 150.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%d", (int)shark_hp_
    );*/

    if (shark_hp_flg_ == 1 || game_over_flg_ == 1) {
        DX9::SpriteBatch->DrawString(
            tap_font_.Get(),
            SimpleMath::Vector2(320.0f, 300.0f),
            DX9::Colors::RGBA(0, 0, 0, 255),
            L"GAME OVER"
        );
    }

    if (game_clear_flg_ == 1) {
        DX9::SpriteBatch->DrawString(
            tap_font_.Get(),
            SimpleMath::Vector2(320.0f, 300.0f),
            DX9::Colors::RGBA(0, 0, 0, 255),
            L"GAME CLEAR"
        );
    }

    if (atack_count_ >= 10) {
        DX9::SpriteBatch->DrawString(
            tap_font_.Get(),
            SimpleMath::Vector2(530.0f, 150.0f),
            DX9::Colors::RGBA(0, 0, 0, 255),
            L"B"
        );
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

bool MainScene::isIntersect(Rect& rect1, Rect& rect2)
{
    const bool isNotLeftContact = rect1.left > rect2.right; // 成り立つ or 成り立たないが変数に代入される
    const bool isNotRightContact = rect1.right < rect2.left;  // 成り立つとき…true / 成り立たない…false
    const bool isNotTopContact = rect1.top > rect2.bottom;
    const bool isNotBottomContact = rect1.bottom < rect2.top;
    if (isNotLeftContact || isNotRightContact || isNotTopContact || isNotBottomContact) {
        return false;
    }

    return true;
}

