//
// RuleOperationScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class RuleOperationScene final : public Scene {
public:
    RuleOperationScene();
    virtual ~RuleOperationScene() { Terminate(); }

    RuleOperationScene(RuleOperationScene&&) = default;
    RuleOperationScene& operator= (RuleOperationScene&&) = default;

    RuleOperationScene(RuleOperationScene const&) = delete;
    RuleOperationScene& operator= (RuleOperationScene const&) = delete;

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

    // �ϐ��̐錾

    DX9::SPRITE bg_sky_sprite_;

};