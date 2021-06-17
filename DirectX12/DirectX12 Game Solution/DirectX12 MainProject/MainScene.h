//
// MainScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
    MainScene();
    virtual ~MainScene() { Terminate(); }

    MainScene(MainScene&&) = default;
    MainScene& operator= (MainScene&&) = default;

    MainScene(MainScene const&) = delete;
    MainScene& operator= (MainScene const&) = delete;

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

    // ïœêîÇÃêÈåæ

    DX9::SPRITEFONT tap_font_;

    DX9::SPRITE gauge_red_sprite_;
    DX9::SPRITE gauge_blue_sprite_;

    DX9::SPRITE shark_sprite_;

    DX9::SPRITE fishing_rod_sprite_;

    // íËêî
    
    const float SHARK_START_POSITION_X_ = 640.0f - 200.0f;
    const float SHARK_START_POSITION_Y_ = 400.0f ;
    const float SHARK_START_POSITION_Z_ = 0.0f;
    const float SHARK_RIGHT_LIMIT_POSITION_X_ = 1280.0f - 400.0f;
    const float SHARK_LEFT_LIMIT_POSITION_X_ = 0.0f;
    const float SHARK_UP_LIMIT_POSITION_Y_ = 0.0f;
    const float SHARK_DOWN_LIMIT_POSITION_Y_ = 720.0f - 231.0f;
    const float SHARK_MOVE_SPEED_ = 300.0f;

    const float FISHING_ROD_START_POSITION_X_ = 0.0f;
    const float FISHING_ROD_START_POSITION_Y_ = 0.0f;
    const float FISHING_ROD_START_POSITION_Z_ = 0.0f;
    const float FISHING_ROD_RIGHT_LIMIT_POSITION_X_ = 1280.0f - 40.0f;
    const float FISHING_ROD_LEFT_LIMIT_POSITION_X_ = 0.0f;
    const float FISHING_ROD_UP_LIMIT_POSITION_Y_ = 0.0f;
    const float FISHING_ROD_DOWN_LIMIT_POSITION_Y_ = 720.0f - 43.0f;
    const float FISHING_ROD_START_SPEED_ = 100.0f;

    const float TOWARDS_FISHING_ROD_START_SPEED_ = 200.0f;

    const float GAUGE_START_POSITION_X_           =   340.0f;
    const float GAUGE_START_POSITION_Y_           =   260.0f;
    const float GAUGE_RED_POSITION_Z_       =     0.0f;
    const float GAUGE_BLUE_POSITION_Z_      =     1.0f;
    const float GAUGE_RED_HEIGHT_START_     =   200.0f;
    const float GAUGE_RED_WIDTH_START_      =   300.0f;
    const float GAUGE_RED_WIDTH_LIMIT_      =   600.0f;
    const float GAUGE_RED_WIDTH_ADD_SPEED_  =   210.0f;
    const float GAUGE_RED_WIDTH_TAKE_SPEED_ =  1400.0f;

    const float COUNT_DOWN_START_           =     100.0f;
    const float COUNT_DOWN_NUMBER_          =     1.0f;

    // ïœêî
    SimpleMath::Vector3 shark_position_;
    SimpleMath::Vector3 fishing_rod_position_;

    float shark_speed_;

    int fishing_rod_direction;
    float fishing_rod_speed_;

    float towards_fishing_rod_speed_;

    float gauge_x_;
    float gauge_y_;
    float gauge_red_z_;
    float gauge_blue_z_;
    float gauge_red_width_;
    int   gauge_display_flg;

    int   tap_flg_;
    int   count_down_;

    enum FishingRodMoveDirection {
        right,
        left
    };

// ä÷êî
private:
        void GaugeUpdate(const float deltaTime);
        void SharkUpdate(const float deltaTime);
        void FishingRodUpdate(const float deltaTime);
};