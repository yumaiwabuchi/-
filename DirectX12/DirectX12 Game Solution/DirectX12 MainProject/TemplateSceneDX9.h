//
// TemplateScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TemplateScene final : public Scene {
public:
	TemplateScene();
	virtual ~TemplateScene() { Terminate(); }

	TemplateScene(TemplateScene&&) = default;
	TemplateScene& operator= (TemplateScene&&) = default;

	TemplateScene(TemplateScene const&) = delete;
	TemplateScene& operator= (TemplateScene const&) = delete;

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

private:

};