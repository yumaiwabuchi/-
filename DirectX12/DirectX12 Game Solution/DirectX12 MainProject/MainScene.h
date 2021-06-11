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

    DX9::SPRITEFONT bottun_font_;

    DX9::SPRITE gauge_red_sprite_;
    DX9::SPRITE gauge_blue_sprite_;

    const float GAUGE_POSITION_X_           =  340.0f;
    const float GAUGE_POSITION_Y_           =  260.0f;
    const float GAUGE_RED_POSITION_Z_       =    0.0f;
    const float GAUGE_BLUE_POSITION_Z_      =    1.0f;
    const float GAUGE_RED_HEIGHT_START_     =  200.0f;
    const float GAUGE_RED_WIDTH_START_      =  300.0f;
    const float GAUGE_RED_WIDTH_ADD_SPEED_  =  210.0f;
    const float GAUGE_RED_WIDTH_TAKE_SPEED_ =  1400.0f;

    float gauge_x_;
    float gauge_y_;
    float gauge_red_z_;
    float gauge_blue_z_;

    float gauge_red_width_;
    
};