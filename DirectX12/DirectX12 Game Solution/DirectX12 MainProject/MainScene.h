//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include <random>
#include "DontDestroyOnLoad.h"

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

    // �ϐ��̐錾

    DX9::SPRITEFONT tap_font_;

    DX9::SPRITE gauge_red_sprite_;
    DX9::SPRITE gauge_blue_sprite_;

    DX9::SPRITE shark_sprite_;

    DX9::SPRITE fishing_rod_sprite_;

    // �萔
    
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

    //QTE�v���O����
    // �ϐ�
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

    //�w�i
    DX9::SPRITE bg_Sprite_;

    //QTE �ϐ�
    float QTE_;
    int QTE_No_;
    float QTE_Time_= 0;
    float QTE_P_;

    //QTE�{�^��
    int QTE_Z_1;
    int QTE_Z_2;
    int QTE_Z_3;
    int QTE_Z_4;

    //QTE�f�o�b�O�p
    DX9::SPRITEFONT QTE_font_;


    //�{�^���K�C�h�摜
    int pattern_;

    DX9::SPRITE A_;
    DX9::SPRITE B_;
    DX9::SPRITE X_;
    DX9::SPRITE Y_;

    //�{�^���摜�@Z��
    int A_Z;
    int B_Z;
    int X_Z;
    int Y_Z;

    //QTE�����_��generator
    std::mt19937 randomEngine_;
    std::uniform_int_distribution<int> random_QTE_pattern_;


    //Second_Shark_attack_�v���O����
    //�ϐ�
    int Attack_2P_;
    int Physical_strength_is_reduced_;
    int Down_Human_End_;
    
    //attack_count
    int Attack_count_;
    const int three_count_ = 1;

    //�T���̗�
    int Shark_Physical_strength_;

    

    //�����l�ϐ�
    int Human_No_;
    float Human_Y_Time_;
    int Time_Flag_;

    int Human_X_P_;
    int Human_Y_P_;
    int Human_Z_P_;

    /*int Down_Human_No_;*/
    //�T��attack�Qbutton
    DX9::SPRITE B_Attack2_;
    //��������l
    DX9::SPRITE Down_Human_;
    //��������l�@�ʒu�����_�� X
    std::mt19937 random_Engine_;
    std::uniform_int_distribution<int> random_Human_pattern_;
    
   

    enum FishingRodMoveDirection {
        right,
        left
    };

// �֐�
private:
        void GaugeUpdate(const float deltaTime);
        void AnglerattackQTEUpdate(const float deltaTime);
        void SharkUpdate(const float deltaTime);
        void FishingRodUpdate(const float deltaTime);
        void SecondSharkattackUpdate(const float deltaTime);

};