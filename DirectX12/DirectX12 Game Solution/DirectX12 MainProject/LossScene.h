//
// LossScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class LossScene final : public Scene {
public:
    LossScene();
    virtual ~LossScene() { Terminate(); }

    LossScene(LossScene&&) = default;
    LossScene& operator= (LossScene&&) = default;

    LossScene(LossScene const&) = delete;
    LossScene& operator= (LossScene const&) = delete;

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

    DX9::SPRITE bg_sky_sprite_;

};