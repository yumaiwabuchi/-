//
// TutorialScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TutorialScene final : public Scene {
public:
    TutorialScene();
    virtual ~TutorialScene() { Terminate(); }

    TutorialScene(TutorialScene&&) = default;
    TutorialScene& operator= (TutorialScene&&) = default;

    TutorialScene(TutorialScene const&) = delete;
    TutorialScene& operator= (TutorialScene const&) = delete;

    // These are the functions you will implement.
    void Initialize() override;
    void LoadAssets() override;

    void Terminate() override;

    void OnDeviceLost() override;
    void OnRestartSound() override;

    NextScene Update(const float deltaTime) override;
    void Render() override;

private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

    // 変数の宣言

    DX9::SPRITEFONT tap_font_;

    DX9::SPRITE bg_sky_sprite_;
    DX9::SPRITE bg_front_sea_sprite_;
    DX9::SPRITE bg_behind_sea_sprite_;
    DX9::SPRITE bg_frame_sprite_;

    DX9::SPRITE shark_sprite_;
    DX9::SPRITE shark_behind_sprite_;

    DX9::SPRITE shark_gauge_;
    DX9::SPRITE shark_gauge_empty_;

    DX9::SPRITE angler_line_;

    DX9::SPRITE black_sprite_;

    // 定数

   // BG
    const float BG_SIZE_X_ = 1280.0f;
    const float BG_SIZE_Y_ = 720.0f;
    const float BG_SKY_POSITION_Z_ = 1.0f;
    const float BG_FRONT_SEA_POSITION_Z_ = -2.0f;
    const float BG_FRONT_SEA_START_POSITION_X_ = -480.0f;
    const float BG_BEHIND_SEA_POSITION_Z_ = 0.1f;
    const float BG_FRAME_POSITION_Z_ = -3.0f;
    const float BG_SPEED_ = 100.0f;
    const float BG_FRONT_SPEED_ = 150.0f;

    // サメの動き
    const float SHARK_SIZE_X_ = 320.0f;
    const float SHARK_SIZE_Y_ = 240.0f;
    const float SHARK_SIZE_HALF_X_ = SHARK_SIZE_X_ / 2.0f;
    const float SHARK_SIZE_HALF_Y_ = SHARK_SIZE_Y_ / 2.0f;
    const float SHARK_START_POSITION_X_ = 0.0f;
    const float SHARK_START_POSITION_Y_ = 200.0f;
    const float SHARK_START_POSITION_Z_ = 0.0f;
    const float SHARK_RIGHT_LIMIT_POSITION_X_ = 1280.0f - SHARK_SIZE_X_;
    const float SHARK_LEFT_LIMIT_POSITION_X_ = 0.0f;
    const float SHARK_UP_LIMIT_POSITION_Y_ = 0.0f;
    const float SHARK_DOWN_LIMIT_POSITION_Y_ = 720.0f - SHARK_SIZE_Y_;
    const float SHARK_STOP_TIME_ = 1.0f;
    const float SHARK_MOVE_SPEED_ = 300.0f;
    const float SHARK_MOVE_SPEED_Y_ = 1500.0f;
    const float SHARK_MOVE_SPEED_SIDE_ = 250.0f;
    const float SHARK_MOVE_UP_SPEED_ = 1.0f;
    const float SHARK_MOVE_UP_SPEED_UP_ = 3.0f;
    const float SHARK_MOVE_UP_SPEED_UP_LIMIT_ = 3.0f;
    const float INPUT_TIME_LIMIT_ = 0.5f;
    const float SHARK_SPRITE_X_CHANGE_TIME_ = 0.2f;
    const float SHARK_SPRITE_SIZE_X_LIMIT_ = 4160.0f - SHARK_SIZE_X_;

    // サメのゲージ
    const float SHARK_GAUGE_START_POSITION_X_ = 640.0f - 300.0f;
    const float SHARK_GAUGE_START_POSITION_Y_ = 620.0f;
    const float SHARK_GAUGE_START_POSITION_Z_ = -10.0f;
    const float SHARK_GAUGE_SIZE_X_ = 600.0f;
    const float SHARK_GAUGE_SIZE_Y_ = 50.0f;
    const float SHARK_GAUGE_GROW_SPEED_ = 600.0f;
    const float SHARK_GAUGE_DECREASE_SPEED_ = 400.0f;
    const float SHARK_GAUGE_STOP_TIME_ = 1.0f;

    // 釣り人のライン
    const float ANGLER_LINE_START_POSITION_X_ = SHARK_GAUGE_START_POSITION_X_ + 100.0f;
    const float ANGLER_LINE_START_POSITION_Y_ = SHARK_GAUGE_START_POSITION_Y_;
    const float ANGLER_LINE_START_POSITION_Z_ = SHARK_GAUGE_START_POSITION_Z_;
    const float ANGLER_LINE_LIMIT_RIGHT_ = SHARK_GAUGE_START_POSITION_X_ + SHARK_GAUGE_SIZE_X_ - 100.0f;
    const float ANGLER_LINE_LIMIT_LEFT_ = SHARK_GAUGE_START_POSITION_X_ + 100.0f;
    const float ANGLER_LINE_MOVE_SPEED_ = 450.0f;

    // サメ引っ張られる力
    const float SHARK_PULL_SPEED_NOTHING_ = 310.0f;
    const float SHARK_PULL_SPEED_SHARKLARGE_ = 1280.0f / 3.0f;

    // ゲージの差
    const float SHARK_LARGE_LINE_POSITION_ = -340.0f;

    // 釣り糸
    const float FISHING_LINE_2_DIFFERENCE_ = 0.5f;
    const float FISHING_LINE_3_DIFFERENCE_ = -0.5f;
    const float SHARK_LINE_DIFFERENCE_X_ = SHARK_SIZE_HALF_X_;
    const float SHARK_LINE_DIFFERENCE_Y_ = SHARK_SIZE_HALF_Y_;


    // 変数

    // BG
    SimpleMath::Vector3 bg_sky_position_;
    SimpleMath::Vector3 bg_front_sea_position_;
    SimpleMath::Vector3 bg_behind_sea_position_;
    SimpleMath::Vector3 bg_frame_position_;

    // サメ
    SimpleMath::Vector3 shark_position_;
    float shark_speed_;
    float shark_speed_up_;
    float shark_move_time_;
    int   shark_direction_flg_;
    int   shark_count_flg;
    float right_input_time_;
    float left_input_time_;
    float shark_sprite_x_;
    float shark_sprite_time_;
    enum SharkState {
        rightinput,
        leftinput
    };

    // サメのゲージ
    SimpleMath::Vector3 shark_gauge_position_;
    SimpleMath::Vector3 shark_gauge_empty_position_;
    float shark_gauge_x_;
    float shark_gauge_speed_;
    int shark_gauge_flg_;
    float shark_gauge_stop_time_;
    int shark_standby_flg_;
    float shark_standby_time_;

    // 釣り人ライン
    SimpleMath::Vector3 angler_line_position_;
    int angler_line_move_direction_;
    float angler_line_value_;
    enum Angler_Line_Direction_ {
        right,
        left
    };

    // 釣り竿
    SimpleMath::Vector3 fishing_rod_position_;
    int fishing_rod_direction;
    enum FishingRodMoveDirection {
        rightmove,
        leftmove
    };
    float fishing_rod_speed_;

    // 釣り人UI
    SimpleMath::Vector3 angler_UI_position_;
    SimpleMath::Vector3 angler_position_UI_position_;

    // ゲージの差を判定する変数
    int gauge_difference_;

    enum GaugeDirection {
        sharklarge,
        sharkmedium,
        sharksmall,
        anglerlarge,
        anglermedium,
        anglersmall,
        nothing
    };

    // 黒背景
    int black_alpha_;
    int black_flg_;

    float tutorial_time_;
    float gauge_stop_after_time_;
    int gauge_stop_after_flg_;

    int next_scene_flg_;

    // 関数
private:
    void BGUpdate(const float deltaTime);
    void SharkUpdate(const float deltaTime);
    void SharkSpriteUpdate(const float deltaTime);
    void SharkMoveUpdate(const float deltaTime);
    void SharkGaugeUpdate(const float deltaTime);
    void GaugeDifferenceUpdate(const float deltaTime);
    void AnglerGaugeUpdate(const float deltaTime);
    void TutorialUpdate(const float deltaTime);
};