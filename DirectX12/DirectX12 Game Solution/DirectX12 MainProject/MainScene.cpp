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

    //サメ体力
    Shark_Physical_strength_ = 1000;


    //QTE 初期化変数
    QTE_ = 0.0f;
    QTE_Time_ = 0.0f;
    QTE_No_ = 0;
   
    QTE_Z_1 = 5;
    QTE_Z_2 = 5;
    QTE_Z_3 = 5;
    QTE_Z_4 = 5;
    //Z軸座標
    A_Z = 5;
    B_Z = 5;
    X_Z = 5;
    Y_Z = 5;
    //QTEパターン
    pattern_ = 0;
    //ランダムQTE
    random_QTE_pattern_ = std::uniform_int_distribution<int>(1, 4);
        
    //Secondサメ攻撃
    //変数初期化
    Human_Y_P_ = -50;
    Human_Z_P_ = 50;
    Attack_count_ = three_count_;

    //落っこちる人　YP
    Human_Y_P_ = -10000;
    random_Human_pattern_ = std::uniform_int_distribution<int>(150, 1130);
   
    

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

    //背景
    bg_Sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"blue_bg.png");

    //QTEボタン画像
    A_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"A.png");
    B_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"B.png");
    X_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"X.png");
    Y_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Y.png");
    //QTEデバッグ用
    QTE_font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 30);

    //サメ攻撃ボタン２
    B_Attack2_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"B.png");

    Down_Human_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"落下する人.png");

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
    //QTE void
    AnglerattackQTEUpdate(deltaTime);
    //Shaekattack void
    SecondSharkattackUpdate(deltaTime);



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

    //サメZ_position_
    shark_position_.z = -20;

    
    //QTE
    QTE_P_ = shark_position_.y;

    if (QTE_P_ > 400) {
        QTE_ += deltaTime;
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

void MainScene::AnglerattackQTEUpdate(const float deltaTime)
{

    

    if (QTE_ >= 10.0f) {

        //QTEランダムパターン
        QTE_No_ = random_QTE_pattern_(randomEngine_);
        QTE_ -= 10.0f;
        
    }

    

        //QTE(4)パターン

        if (QTE_No_ == 1) {

            pattern_ = 1;
            QTE_Time_ += deltaTime;

            if (QTE_Time_ <= 1.8f) {
                if (DXTK->GamePadState[0].IsAPressed() && DXTK->GamePadState[0].IsBPressed()) {

                    pattern_ = 0;
                    QTE_No_ = 0.0f;
                    QTE_Time_ = 0.0f;
                }
            }

            if (QTE_Time_ > 1.8f) {

                pattern_ = 0;
                    
                    shark_position_.y -= 8;

                    DXTK->GamePadVibration(0, 0.5f, 0.5f);

            }

        }

        if (QTE_No_ == 2) {

            pattern_ = 2;
            QTE_Time_ += deltaTime;

            if (QTE_Time_ <= 1.8f) {
                if (DXTK->GamePadState[0].IsBPressed() && DXTK->GamePadState[0].IsYPressed()) {

                    pattern_ = 0;
                    QTE_No_ = 0.0f;
                    QTE_Time_ = 0.0f;
                }

            }

            if (QTE_Time_ > 1.8f) {

                pattern_ = 0;
                    shark_position_.y -= 8;

                    DXTK->GamePadVibration(0, 0.5f, 0.5f);

            }
        }

        if (QTE_No_ == 3) {
            
            pattern_ = 3;
            QTE_Time_ += deltaTime;

            if (QTE_Time_ <=1.8f) {
                if (DXTK->GamePadState[0].IsXPressed() && DXTK->GamePadState[0].IsAPressed()) {


                    pattern_ = 0;
                    QTE_No_ = 0.0f;
                    QTE_Time_ = 0.0f;
                }

            }

            if (QTE_Time_ > 1.8f) {

                pattern_ = 0;
                    shark_position_.y -= 8;

                    DXTK->GamePadVibration(0, 0.5f, 0.5f);
            }
        }

        if (QTE_No_ == 4) {

            pattern_ = 4;
            QTE_Time_ += deltaTime;

            if (QTE_Time_ <= 1.8f) {
                if (DXTK->GamePadState[0].IsYPressed() && DXTK->GamePadState[0].IsXPressed()) {


                    pattern_ = 0;
                    QTE_No_ = 0.0f;
                    QTE_Time_ = 0.0f;
                }

            }
            
            if (QTE_Time_ > 1.8f) {
                
                pattern_ = 0;
                    shark_position_.y -= 8;
                    DXTK->GamePadVibration(0, 0.5f, 0.5f);

            }
        }

        if (QTE_Time_ >= 2.3f) {
            pattern_ = 0;
            QTE_Time_ = 0.0f;
            QTE_No_ = 0.0f;
            DXTK->GamePadVibration(0, 0.0f, 0.0f);
        }

        if (pattern_ == 0) {

            A_Z = 45;
            B_Z = 45;
            X_Z = 45;
            Y_Z = 45;

        }
}

void MainScene::SecondSharkattackUpdate(const float deltaTime)
{

    if (Attack_count_ == 1) {

        if (shark_position_.x > fishing_rod_position_.x + 40.0f || shark_position_.x + 400.0f < fishing_rod_position_.x ||
            shark_position_.y > fishing_rod_position_.y + 43.0f || shark_position_.y + 231.0f < fishing_rod_position_.y) {
            // 当たっていない
        }
        else {
            Attack_2P_ = 1;
            Time_Flag_ = 1;
            // 当たっている
        }
    }

    if (Attack_count_ == 2) {

        if (shark_position_.x > fishing_rod_position_.x + 40.0f || shark_position_.x + 400.0f < fishing_rod_position_.x ||
            shark_position_.y > fishing_rod_position_.y + 43.0f || shark_position_.y + 231.0f < fishing_rod_position_.y) {
            // 当たっていない
        }
        else {
            Attack_2P_ = 2;
            Time_Flag_ = 1;
            // 当たっている
        }
    }

    if (Attack_count_ == 3) {

        if (shark_position_.x > fishing_rod_position_.x + 60.0f || shark_position_.x + 400.0f < fishing_rod_position_.x ||
            shark_position_.y > fishing_rod_position_.y + 55.0f || shark_position_.y + 231.0f < fishing_rod_position_.y) {
            // 当たっていない
        }
        else {
            Attack_2P_ = 3;
            Time_Flag_ = 1;
            // 当たっている
        }
    }

    if (Time_Flag_ == 1) {
        Human_Y_Time_ += deltaTime;
    }

    if (Human_Y_Time_ >= 0.5f) {
        Human_Y_P_ += 5;
        Human_Y_Time_ = 0;
    }



    if (Attack_2P_ == 1) {

        Human_Y_P_ = -30;
        Human_X_P_ = random_Human_pattern_(random_Engine_);
        Human_No_ = 1;
        /*Attack_2P_ = 0;*/
    }

    if (Attack_2P_ == 2) {

        Human_Y_P_ = -30;
        Human_X_P_ = random_Human_pattern_(random_Engine_);
        Human_No_ = 1;
        /*Attack_2P_ = 0;*/
    }

    if (Attack_2P_ == 3) {

        Human_Y_P_ = -30;
        Human_X_P_ = random_Human_pattern_(random_Engine_);
        Human_No_ = 1;
        /*Attack_2P_ = 0;*/
    }

    if (Human_Y_P_ >= 30) {
        Human_Z_P_ = -30;
        Attack_2P_ = 0;
    }

    if (Human_Y_P_ >= 730 && Attack_count_ == 1) {
        Human_Y_P_ = -10000;
        Human_Z_P_ = 50;
        Attack_count_ = 2;
    }
    
    if (Human_Y_P_ >= 730 && Attack_count_ == 2) {
        Human_Y_P_ = -10000;
        Human_Z_P_ = 50;
        Attack_count_ = 3;
    }

    if (Human_Y_P_ >= 730 && Attack_count_ == 3) {
        Human_Y_P_ = -10000;
        Human_Z_P_ = 50;
        Attack_count_ = 4;
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

    //背景
    DX9::SpriteBatch->DrawSimple(bg_Sprite_.Get(), SimpleMath::Vector3(0, 0, 10));

    //QTEボタン

    if (pattern_ == 1) {

        A_Z = -5;
        B_Z = -5;

        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(550, 400, A_Z));
        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(650, 400, B_Z));
    }

    if (pattern_ == 2) {

        B_Z = -5;
        Y_Z = -5;

        DX9::SpriteBatch->DrawSimple(B_.Get(), SimpleMath::Vector3(550, 400, B_Z));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(650, 400, Y_Z));
    }
    
    if (pattern_ == 3) {

        A_Z = -5;
        X_Z = -5;

        DX9::SpriteBatch->DrawSimple(A_.Get(), SimpleMath::Vector3(550, 400, A_Z));
        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(650, 400, X_Z));
    }

    if (pattern_ == 4) {

        X_Z = -5;
        Y_Z = -5;

        DX9::SpriteBatch->DrawSimple(X_.Get(), SimpleMath::Vector3(550, 400, X_Z));
        DX9::SpriteBatch->DrawSimple(Y_.Get(), SimpleMath::Vector3(650, 400, Y_Z));
    }

    
    //サメ攻撃２落下する人
    if (Human_No_ == 1) {

        DX9::SpriteBatch->DrawSimple(Down_Human_.Get(), SimpleMath::Vector3(Human_X_P_, Human_Y_P_, Human_Z_P_));
    }

    if (Human_No_ == 2) {

        DX9::SpriteBatch->DrawSimple(Down_Human_.Get(), SimpleMath::Vector3(Human_X_P_, Human_Y_P_, Human_Z_P_));
    }

    if (Human_No_ == 3) {

        DX9::SpriteBatch->DrawSimple(Down_Human_.Get(), SimpleMath::Vector3(Human_X_P_, Human_Y_P_, Human_Z_P_));
    }


    //デバッグ用
        DX9::SpriteBatch->DrawString(
            QTE_font_.Get(),
            SimpleMath::Vector2(0.0f, 100.0f),
            DX9::Colors::RGBA(0, 0, 0, 255),
            L"QTE：%d", Attack_count_);
    


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

