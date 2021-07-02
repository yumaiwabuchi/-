//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include <random>
#include "DontDestroyOnLoad.h"


// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //全プログラム制御フラグ
    shark_STOP_FLAG_ = Shark_STOP_FLAG_; //(int)


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

    shark_hp_flg_  = 0;
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

    //QTE 指示
    button_Instruct_ = Button_Instruct_;
    //QTE
    qte_ = QTE_;
    qte_time_ = QTE_Time_;
    qte_no_ = QTE_No_;

    qte_z_1 = QTE_Z_1;
    qte_z_2 = QTE_Z_2;
    qte_z_3 = QTE_Z_3;
    qte_z_4 = QTE_Z_4;

    a_z = A_Z;
    b_z = B_Z;
    x_z = X_Z;
    y_z = Y_Z;
    //QTE
    pattern_ = Pattern_;
    //QTE
    random_QTE_pattern_ = std::uniform_int_distribution<int>(1, 4);
    qte_pattern_ = QTE_pattern_;

    //secondサメ攻撃
    fishing_rod_size_x_ = FISHING_ROD_SIZE_X_;
    fishing_rod_size_y_ = FISHING_ROD_SIZE_Y_;

    //落っこち人間
    //初期化
    Flag_GG_ = 0.0f;
    Human_Flag_ = 0.0f;
    Human_Y_Time_ = 0.0f;

    Human_Y_P_ = -50;
    Human_Z_P_ = -3;
    Attack_count_ = three_count_;

    Human_Y_P_ = -100;
    random_Human_pattern_ = std::uniform_int_distribution<int>(200, 1000);

    Human_size_x_ = HUMAN_SIZE_X_;
    Human_size_y_ = HUMAN_SIZE_Y_;

    Human_dead_ = 0;
    Human_HP_ = 0.0f;
    Human_GH_ = 0;

    //QTE2初期化
    pattern2_ = 0;
    qte_serect2_ = QTE_serect2_;
    qte_push_button_ = QTE_push_button_;
    qte_time_flg_ = QTE_Time_Flg_;
    push_button_ = Push_button_;
    qte_p_ = QTE_P_;

    a_z1 = A_Z1; a_z2 = A_Z2; a_z3 = A_Z3; a_z4 = A_Z4; a_z5 = A_Z5;
    b_z1 = B_Z1; b_z2 = B_Z2; b_z3 = B_Z3; b_z4 = B_Z4; b_z5 = B_Z5;
    x_z1 = X_Z1; x_z2 = X_Z2; x_z3 = X_Z3; x_z4 = X_Z4; x_z5 = X_Z5;
    y_z1 = Y_Z1; y_z2 = Y_Z2; y_z3 = Y_Z3; y_z4 = Y_Z4; y_z5 = Y_Z5;
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

    shark_sprite_        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"light1.png");
    shark_behind_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"left1.png");

    fishing_rod_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"boat.png");

    angler_hp_empty_sprite_      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.under.png");
    angler_hp_hull_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI.red.2.psd.png");

    dead_zone_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dead_Zone.png");

    danger_sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"WARNING.png");

    //QTEボタン画像
    A_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"QTE.A.png");
    B_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"QTE.B.png");
    X_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"QTE.X.png");
    Y_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"QTE.Y.png");
    //QTEデバッグ用font
    QTE_font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 30);

    //落ちる人
    Down_Human_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Oboreru_Hito.png");
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
    if (shark_STOP_FLAG_ == 0) {
        SharkUpdate(deltaTime);
        FishingRodUpdate(deltaTime);
        DeadZoneUpdate(deltaTime);
        AnglerUpdate(deltaTime);
    }

    SharkAtack2Update(deltaTime);
    QTEUpdate2(deltaTime);

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

    //サメZ_position_
    shark_position_.z = -20;


    //QTE
    qte_p_ = shark_position_.y;


    if (qte_p_ >= 180) {
        qte_ += 1 * deltaTime;
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
   /* if (shark_hp_position_y_ <= SHARK_HP_POSITION_Y_) {
        shark_hp_position_y_ = SHARK_HP_POSITION_Y_;
    }

    if (shark_hp_position_y_ >= SHARK_HP_POSITION_Y_) {
        shark_hp_position_y_ = SHARK_HP_POSITION_Y_;
    }*/

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

void MainScene::SharkAtack2Update(const float deltaTime)
{
    if (Attack_count_ == 1) {
        if (Flag_GG_ <= 0.2f) {
            if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
                RectWH(fishing_rod_position_.x, fishing_rod_position_.y, fishing_rod_size_x_, fishing_rod_size_y_))) {
                // あたったとき
                fishing_time += deltaTime;
                Attack_2P_ = 1;
                Time_Flag_ = 1;
                Human_X_P_ = random_Human_pattern_(random_Engine_);
                Flag_GG_ = 1.0f;

            }

        }
    }

    if (Attack_count_ == 2) {
        if (Flag_GG_ <= 0.2f) {
            if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
                RectWH(fishing_rod_position_.x, fishing_rod_position_.y, fishing_rod_size_x_, fishing_rod_size_y_))) {
                // あたったとき
                fishing_time += deltaTime;
                Attack_2P_ = 2;
                Time_Flag_ = 1;
                Human_X_P_ = random_Human_pattern_(random_Engine_);
                Flag_GG_ = 1.0f;

            }

        }

    }

    if (Attack_count_ == 3) {
        if (Flag_GG_ <= 0.2f) {
            if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
                RectWH(fishing_rod_position_.x, fishing_rod_position_.y, fishing_rod_size_x_, fishing_rod_size_y_))) {
                // あたったとき
                fishing_time += deltaTime;
                Attack_2P_ = 3;
                Time_Flag_ = 1;
                Human_X_P_ = random_Human_pattern_(random_Engine_);
                Flag_GG_ = 1.0f;

            }

        }
    }

    if (Time_Flag_ == 1) {
        Human_Y_Time_ += deltaTime;
    }

    if (Human_Y_Time_ >= 0.2f) {
        Human_Flag_ = 1.0f;

        Human_Y_Time_ = 0.0f;

    }

    if (Human_Flag_ == 1.0f) {
        Human_Y_P_ += 18;
        Human_Flag_ -= deltaTime;
    }

    if (Human_Y_P_ >= -30) {
        Human_Z_P_ = -10;
        Attack_2P_ = 0;
    }

    if (Human_Y_P_ >= 730) {
        Human_Z_P_ = 50;
        Time_Flag_ = 0;
        Human_Y_Time_ = 0.0f;
        Attack_count_ += 1;
        Human_Y_P_ = -100;
        Flag_GG_ = 0.0f;
    }

    //人が食われると回復するコード

    if (Human_GH_ == 0) {
        if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
            RectWH(Human_X_P_, Human_Y_P_, Human_size_x_, Human_size_y_))) {
            // あたったとき
            Human_Z_P_ = 50;
            Human_Y_P_ = 800;
            Human_dead_ = 1;

        }

    }

    if (Human_dead_ == 1) {
        Human_HP_ += deltaTime;
        shark_hp_ -= 15.0f;
        shark_hp_position_y_ -= 15.0f;
        Human_GH_ = 1;
    }

    if (Human_HP_ >= 0.1f) {
        Human_GH_ = 0;
        Human_dead_ = 0;
    }

}

void MainScene::QTEUpdate2(const float deltaTime)
{
    if (qte_ >= 10.0f) {
        //QTEセレクト
        qte_serect2_ = 1;
        qte_ = 0.0f;
    }

    if (qte_serect2_ == 1) {
        shark_STOP_FLAG_ = 1;



        if (shark_position_.x <= 620 && shark_position_.y <= 350) {
            pattern2_ = 1;
            a_z1 = -34; a_z2 = -33; a_z3 = -32; a_z4 = -31; a_z5 = -30;

            button_Instruct_ = 1;
        }

        if (shark_position_.x >= 621 && shark_position_.y <= 351) {
            pattern2_ = 2;
            b_z1 = -34; b_z2 = -33; b_z3 = -32; b_z4 = -31; b_z5 = -30;

            button_Instruct_ = 1;
        }

        if (shark_position_.x <= 620 && shark_position_.y >= 350) {
            pattern2_ = 3;
            x_z1 = -34; x_z2 = -33; x_z3 = -32; x_z4 = -31; x_z5 = -30;

            button_Instruct_ = 1;
        }

        if (shark_position_.x >= 621 && shark_position_.y >= 351) {
            pattern2_ = 4;
            y_z1 = -34; y_z2 = -33; y_z3 = -32; y_z4 = -31; y_z5 = -30;

            button_Instruct_ = 1;
        }


    }


    //QTE(4)パターン

    if (pattern2_ == 1) {
        qte_serect2_ = 0;
        shark_STOP_FLAG_ = 1;
        qte_time_ += deltaTime;

        if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED && qte_push_button_ == 0) {
            qte_serect2_ = 0;
            a_z1 = 50;
            /*qte_push_button_ = 1;*/
        }

        if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED) {
            qte_push_button_ += 1;
        }

        /*if(DXTK->KeyEvent->pressed.Up) {
            qte_serect2_ = 0;
            a_z1 = 50;
            qte_push_button_ = push_button_1;
        }*/


        if (qte_push_button_ == 1) {

            if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED /*, DXTK->KeyEvent->pressed.Up*/) {
                a_z2 = 50;
                /*qte_push_button_ = 2;*/
            }

        }

        if (qte_push_button_ == 2) {

            if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED) {
                a_z3 = 50;
                /*qte_push_button_ = 3;*/
            }

        }

        if (qte_push_button_ == 3) {

            if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED) {
                a_z4 = 50;
                /*qte_push_button_ = 4;*/
            }

        }

        if (qte_push_button_ == 4) {

            if (DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED) {
                a_z5 = 50;
                shark_STOP_FLAG_ = 0; button_Instruct_ = 0;
                /*qte_push_button_ = 5;*/
                qte_pattern_ = 0.0f;
                qte_time_ = 0.0f;
                pattern2_ = 0;
            }

        }

    }

    if (pattern2_ == 2) {
        qte_serect2_ = 0;
        shark_STOP_FLAG_ = 1;
        qte_time_ += deltaTime;


        if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED && qte_push_button_ == 0) {
            qte_serect2_ = 0;
            b_z1 = 50;
            /*qte_push_button_ = 1;*/
        }

        /*if (DXTK->KeyEvent->pressed.Right) {
            qte_serect2_ = 0;
            b_z1 = 50;
            qte_push_button_ = push_button_1;
        }*/

        if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
            qte_push_button_ += 1;
        }


        if (qte_push_button_ == 1) {

            if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
                b_z2 = 50;
                /*qte_push_button_ = 2;*/
            }

        }

        if (qte_push_button_ == 2) {

            if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
                b_z3 = 50;
                /*qte_push_button_ = 3;*/
            }

        }

        if (qte_push_button_ == 3) {

            if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
                b_z4 = 50;
                /*qte_push_button_ = 4;*/
            }

        }

        if (qte_push_button_ == push_button_4) {

            if (DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
                b_z5 = 50;
                shark_STOP_FLAG_ = 0; pattern2_ = 0;
                button_Instruct_ = 0;
                /*qte_push_button_ = 5;*/
                qte_pattern_ = 0.0f;
                qte_time_ = 0.0f;
            }

        }

    }

    if (pattern2_ == 3) {
        qte_serect2_ = 0;

        shark_STOP_FLAG_ = 1;
        qte_time_ += deltaTime;



        if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED && qte_push_button_ == 0) {
            qte_serect2_ = 0;
            x_z1 = 50;
            /*qte_push_button_ = 1;*/
        }

        if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
            qte_push_button_ += 1;
        }



        if (qte_push_button_ == 1) {

            if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
                x_z2 = 50;
                /*qte_push_button_ = 2;*/
            }

        }

        if (qte_push_button_ == 2) {

            if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
                x_z3 = 50;
                /*qte_push_button_ = 3;*/
            }

        }

        if (qte_push_button_ == 3) {

            if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
                x_z4 = 50;
                /* qte_push_button_ = 4;*/
            }

        }

        if (qte_push_button_ == 4) {

            if (DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
                x_z5 = 50;
                shark_STOP_FLAG_ = 0; button_Instruct_ = 0;
                pattern2_ = 0;
                /*qte_push_button_ = 5;*/
                qte_pattern_ = 0.0f;
                qte_time_ = 0.0f;
            }

        }

    }

    if (pattern2_ == 4) {
        qte_serect2_ = 0;
        shark_STOP_FLAG_ = 1;
        qte_time_ += deltaTime;


        if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED && qte_push_button_ == 0) {
            qte_serect2_ = 0;
            y_z1 = 50;
            /*qte_push_button_ = 1;*/
        }

        if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
            qte_push_button_ += 1;
        }


        if (qte_push_button_ == 1) {

            if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
                y_z2 = 50;
                /*qte_push_button_ = 2;*/
            }

        }

        if (qte_push_button_ == 2) {

            if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
                y_z3 = 50;
                /*qte_push_button_ = 3;*/
            }

        }

        if (qte_push_button_ == 3) {

            if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
                y_z4 = 50;
                /* qte_push_button_ = 4;*/
            }

        }

        if (qte_push_button_ == 4) {

            if (DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
                y_z5 = 50;
                shark_STOP_FLAG_ = 0; button_Instruct_ = 0;
                pattern2_ = 0;
                /*qte_push_button_ = 5;*/
                qte_pattern_ = 0.0f;
                qte_time_ = 0.0f;
            }

        }

    }

    if (qte_push_button_ == 5) {
        shark_STOP_FLAG_ = 0; button_Instruct_ = 0;
        pattern2_ = 0;

        qte_pattern_ = 0.0f;
        qte_time_ = 0.0f;
    }

    if (pattern2_ == 0) {

        qte_push_button_ = 0;
    }

    if (qte_time_ >= 1.8f) {
        shark_STOP_FLAG_ = 0;
        qte_push_button_ = 0;
        shark_position_.y -= 10;
        push_button_ += deltaTime;
        DXTK->GamePadVibration(0, 0.6f, 0.6f);

    }


    if (push_button_ >= 0.8f) {
        DXTK->GamePadVibration(0, 0.0f, 0.0f);
        qte_pattern_ = 0;
    }

    if (qte_time_ >= 2.2f) {
        button_Instruct_ = 0;
        push_button_ = 0.0f;
        pattern2_ = 0;
        qte_push_button_ = 0;

        qte_time_flg_ = 1;
        qte_time_ = 0.0f;
    }

    if (pattern2_ == 0) {

        a_z1 = 50; a_z2 = 50; a_z3 = 50; a_z4 = 50; a_z5 = 50;
        b_z1 = 50; b_z2 = 50; b_z3 = 50; b_z4 = 50; b_z5 = 50;
        x_z1 = 50; x_z2 = 50; x_z3 = 50; x_z4 = 50; x_z5 = 50;
        y_z1 = 50; y_z2 = 50; y_z3 = 50; y_z4 = 50; y_z5 = 50;

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

    //QTE２

    if (pattern2_ == 1) {
        /*A_Z1 = -14; A_Z2 = -13; A_Z3 = -12; A_Z4 = -11; A_Z5 = -10;*/


        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(500, 320, a_z1));
        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(530, 320, a_z2));
        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(560, 320, a_z3));
        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(590, 320, a_z4));
        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(620, 320, a_z5));

    }

    if (pattern2_ == 2) {

        /*B_Z1 = -14; B_Z2 = -13; B_Z3 = -12; B_Z4 = -11; B_Z5 = -10;*/


        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(500, 320, b_z1));
        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(530, 320, b_z2));
        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(560, 320, b_z3));
        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(590, 320, b_z4));
        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(620, 320, b_z5));

    }


    if (pattern2_ == 3) {

        /*X_Z1 = -14; X_Z2 = -13; X_Z3 = -12; X_Z4 = -11; X_Z5 = -10;*/


        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(580, 300, x_z1));
        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(580, 330, x_z2));
        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(580, 360, x_z3));
        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(580, 390, x_z4));
        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(580, 420, x_z5));

    }

    if (pattern2_ == 4) {

        /*Y_Z1 = -34; Y_Z2 = -33; Y_Z3 = -32; Y_Z4 = -31; Y_Z5 = -30;*/


        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(580, 300, y_z1));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(580, 330, y_z2));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(580, 360, y_z3));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(580, 390, y_z4));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(580, 420, y_z5));

    }

    //HumanDown


    DX9::SpriteBatch->DrawSimple(Down_Human_.Get(), SimpleMath::Vector3(Human_X_P_, Human_Y_P_, Human_Z_P_));

    //QTE　テキスト指示
    if (button_Instruct_ == 1) {
        DX9::SpriteBatch->DrawString(
            QTE_font_.Get(),
            SimpleMath::Vector2(400.0f, 250.0f),
            DX9::Colors::RGBA(255, 255, 0, 255),
            L"ボタンを押せ!!"
        );
    }

    DX9::SpriteBatch->DrawString(
        QTE_font_.Get(),
        SimpleMath::Vector2(0.0f, 650.0f),
        DX9::Colors::RGBA(255, 255, 0, 255),
        L"%d", qte_push_button_
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

