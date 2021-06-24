//
// MainScene.h
//

#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
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
    //�Q�[������t���O
    int Shark_STOP_FLAG_;
    //�o�b�N�w�i
    DX9::SPRITE main_bg_;


    DX9::SPRITEFONT tap_font_;
    DX9::SPRITEFONT debug_font_;

    DX9::SPRITE gauge_red_sprite_;
    DX9::SPRITE gauge_blue_sprite_;

    DX9::SPRITE shark_hp_empty_sprite_;
    DX9::SPRITE shark_hp_hull_sprite_;

    DX9::SPRITE shark_sprite_;
    DX9::SPRITE shark_behind_sprite_;

    DX9::SPRITE fishing_rod_sprite_;

    DX9::SPRITE angler_sprite_;
    DX9::SPRITE angler_move_sprite_;

    DX9::SPRITE dead_zone_sprite_;

    DX9::SPRITE danger_sprite_;

    // �萔
    

    // �T���̓���
    const float SHARK_SIZE_X_ = 400.0f;
    const float SHARK_SIZE_Y_ = 231.0f;
    const float SHARK_SIZE_HALF_Y_ = SHARK_SIZE_Y_ / 2.0f;
    const float SHARK_START_POSITION_X_ = 640.0f - 200.0f;
    const float SHARK_START_POSITION_Y_ = 400.0f;
    const float SHARK_START_POSITION_Z_ = 0.0f;
    const float SHARK_RIGHT_LIMIT_POSITION_X_ = 1280.0f - 400.0f;
    const float SHARK_LEFT_LIMIT_POSITION_X_ = 0.0f;
    const float SHARK_UP_LIMIT_POSITION_Y_ = 0.0f;
    const float SHARK_DOWN_LIMIT_POSITION_Y_ = 720.0f - 231.0f;
    const float SHARK_STOP_TIME_ = 1.0f;
    const float SHARK_MOVE_SPEED_ = 300.0f;
    const float SHARK_MOVE_SPEED_Y_ = 900.0f;

    // �T����HP
    const float SHARK_HP_POSITION_X_ = 10.0f;
    const float SHARK_HP_POSITION_Y_ = 360.0f - 200.0f;
    const float SHARK_HP_POSITION_Z_ = 0.0f;
    const float SHARK_HP_RIGHT_LIMIT_ = 50.0f;
    const float SHARK_HP_DOWN_LIMIT_ = 400.0f;
    const float SHARK_HP_START_ = 0.0f;
    const float SHARK_HP_DAMAGE_ = 4.4f;
    const float SHARK_HP_DAMAGE_SLOWLY_ = SHARK_HP_DAMAGE_ * 2.0f;
    const float SHARK_HP_DAMAGE_ATACK = 5.0f;
    const float SHARK_HP_HEAL_ = 50.0f;

    // �T���̍U��
    const float SHARK_ATACK_GROW_SPEED_ = 1200.0f;
    const float SHARK_ATACK_DECREASE_SPEED_ = 1400.0f;
    const float SHARK_ATACK_LIMIT_SPEED_ = 700.0f;
    const float SHARK_ATACK_TIME_ = 1.0f;

    // �ނ�Ƃ̓���
    const float FISHING_ROD_START_POSITION_X_ = 0.0f;
    const float FISHING_ROD_START_POSITION_Y_ = 0.0f;
    const float FISHING_ROD_START_POSITION_Z_ = 0.0f;
    const float FISHING_ROD_RIGHT_LIMIT_POSITION_X_ = 1280.0f - 40.0f;
    const float FISHING_ROD_LEFT_LIMIT_POSITION_X_ = 0.0f;
    const float FISHING_ROD_UP_LIMIT_POSITION_Y_ = 0.0f;
    const float FISHING_ROD_DOWN_LIMIT_POSITION_Y_ = 720.0f - 43.0f;
    const float FISHING_ROD_START_SPEED_ = 100.0f;

    // �ނ莅
    const float FISHING_LINE_2_DIFFERENCE_ = 0.5f;
    const float FISHING_LINE_3_DIFFERENCE_ = -0.5f;
    const float SHARK_LINE_DIFFERENCE_X_ = 200.0f;
    const float SHARK_LINE_DIFFERENCE_Y_ = 115.5f;

    // �ނ�ƂɌ���������
    const float TOWARDS_FISHING_ROD_START_SPEED_ = 170.0f;

    // �ނ�l�̈ʒu
    const float ANGLER_MOVE_START_POSITION_X_ = 1280.0f - 60.0f;
    const float ANGLER_MOVE_START_POSITION_Y_ = 360.0f - 200.0f;
    const float ANGLER_MOVE_START_POSITION_Z_ = 0.0f;

    // �ނ�l
    const float ANGLER_START_POSITION_X_ = 1280.0f - 60.0f;
    const float ANGLER_START_POSITION_Y_ = 360.0f - 200.0f;
    const float ANGLER_START_POSITION_Z_ = -1.0f;
    const float ANGLER_LIMIT_POSITION_Y_ = ANGLER_START_POSITION_Y_ + 400.0f;
    const float ANGLER_POSITION_SPEED_Y_ = 5.0f;
    const float ANGLER_POSITION_SPEED_UP_Y_ = 15.0f;

    // �΂��荇��
    const float GAUGE_START_POSITION_X_ = 340.0f;
    const float GAUGE_START_POSITION_Y_ = 260.0f;
    const float GAUGE_RED_POSITION_Z_ = 0.0f;
    const float GAUGE_BLUE_POSITION_Z_ = 1.0f;
    const float GAUGE_RED_HEIGHT_START_ = 200.0f;
    const float GAUGE_RED_WIDTH_START_ = 300.0f;
    const float GAUGE_RED_WIDTH_LIMIT_ = 600.0f;
    const float GAUGE_RED_WIDTH_ADD_SPEED_ = 210.0f;
    const float GAUGE_RED_WIDTH_TAKE_SPEED_ = 1400.0f;

    // �J�E���g�_�E��
    const float COUNT_DOWN_START_ = 100.0f;
    const float COUNT_DOWN_NUMBER_ = 1.0f;

    // �f�b�h�]�[��
    const float DEAD_ZONE_RIMIT_TIME_ = 3.0f;
    const float DEAD_ZONE_UP_ = 0.0f;
    const float DEAD_ZONE_DOWN_ = 100.0f;
    const float DEAD_ZONE_RIGHT_ = 1280.0f;
    const float DEAD_ZONE_LEFT_ = 0.0f;
    const float DANGER_POSITION_X_ = 320.0f;
    const float DANGER_POSITION_Y_ = 260.0f;
    const float DANGER_POSITION_Z_ = -1.0f;

    // �̗͌��鑬�x�̃{�[�_�[
    const float SHARK_HP_DAMAGE_SPEED_BORDER_ = 410.0f;



    // �T��
    SimpleMath::Vector3 shark_position_;
    float shark_speed_;
    float shark_move_time_;
    int   shark_direction_flg_;
    enum SharkState {
        rightinput,
        leftinput
    };

    // �ނ�l�̈ʒu
    SimpleMath::Vector3 angler_move_position_;

    // �ނ�l
    SimpleMath::Vector3 angler_position_;

    // �ނ��
    SimpleMath::Vector3 fishing_rod_position_;
    int fishing_rod_direction;
    enum FishingRodMoveDirection {
        right,
        left
    };
    float fishing_rod_speed_;

    // �T����HP
    float shark_hp_position_x_;
    float shark_hp_position_y_;
    float shark_hp_position_z_;
    float shark_hp_;
    float shark_hp_zero_time_;
    int   shark_hp_flg_;

    // �T���U��
    int atack_flg_;
    int atack_move_flg_;
    int atack_count_;
    float atack_time_;
    float atack_move_y_;

    // �ނ�ƂɌ�������
    float towards_fishing_rod_speed_;

    // �΂��荇��
    float gauge_x_;
    float gauge_y_;
    float gauge_red_z_;
    float gauge_blue_z_;
    float gauge_red_width_;
    int   gauge_display_flg;
    int   tap_flg_;

    // �J�E���g�_�E��
    int   count_down_;

    // �f�b�h�]�[��
    float dead_zone_time;
    int   danger_flg;

    // �Q�[���I�[�o�[
    int   game_over_flg_;

    // �Q�[���N���A
    int   game_clear_flg_;

    // �����蔻��
    bool  isIntersect(Rect& rect1, Rect& rect2);

    //QTE�v���O����
    // �ϐ�
    int QTE_Z_1;
    int QTE_Z_2;
    int QTE_Z_3;
    int QTE_Z_4;
    float QTE_;
    float QTE_P_;
    float QTE_Time_;
    int QTE_No_;
    int QTE_pattern_;

    
   
    //�{�^���K�C�h&&�摜
    int pattern_;
    int button_Instruct_;
    DX9::SPRITEFONT QTE_font_;
   
    DX9::SPRITE A_;
    DX9::SPRITE B_;
    DX9::SPRITE X_;
    DX9::SPRITE Y_;

    //�{�^���摜�@Z��
    int A_Z; int B_Z; int X_Z; int Y_Z;

    //QTE�����_��generator
    std::mt19937 randomEngine_;
    std::uniform_int_distribution<int> random_QTE_pattern_;


    //Second_Shark_attack_�v���O����
    //�ϐ�
    int Attack_2P_;
    int Physical_strength_is_reduced_;
    int Down_Human_End_;

    float Flag_GG_;

    const float FISHING_ROD_SIZE_X_ = 22.0f;
    const float FISHING_ROD_SIZE_Y_ = 50.0f;
    
    float fishing_time = 0;
    float fishing_rod_size_x_;
    float fishing_rod_size_y_;

    //attack_count
    int Attack_count_;
    const int three_count_ = 1;

    //�T���̗�
    int Shark_Physical_strength_;

    //�����l�ϐ�
    int Human_No_;
    float Human_Y_Time_;
    int Time_Flag_;
    float Human_Flag_;

    int Human_X_P_; int Human_Y_P_; int Human_Z_P_;

    /*int Down_Human_No_;*/
    //�T��attack�Qbutton
    DX9::SPRITE B_Attack2_;
    //��������l
    DX9::SPRITE Down_Human_;
    
    const float HUMAN_SIZE_X_ = 48.0f; const float HUMAN_SIZE_Y_ = 70.0f;

    float Human_size_x_;
    float Human_size_y_;

    int Human_dead_;
    float Human_HP_;
    float Human_GH_;

    //��������l�@�ʒu�����_�� X
    std::mt19937 random_Engine_;
    std::uniform_int_distribution<int> random_Human_pattern_;


    //�ǉ�QTE�ϐ�
    int QTE_serect2_;
    int QTE_push_button_;
    int pattern2_;
    float push_button_;

    int QTE_Flg_;
    int QTE_Time_Flg_;
    //�S�p�^�[���~5
    int A_Z1; int A_Z2; int A_Z3; int A_Z4; int A_Z5;
    int B_Z1; int B_Z2; int B_Z3; int B_Z4; int B_Z5;
    int X_Z1; int X_Z2; int X_Z3; int X_Z4; int X_Z5;
    int Y_Z1; int Y_Z2; int Y_Z3; int Y_Z4; int Y_Z5;

    

// �֐�
private:
        void GaugeUpdate      (const float deltaTime);
        void SharkUpdate      (const float deltaTime);
        void SharkHPUpdate    (const float deltaTime);
        void SharkAtackUpdate (const float deltaTime);
        void FishingRodUpdate (const float deltaTime);
        void DeadZoneUpdate   (const float deltaTime);
        void AnglerUpdate     (const float deltaTime);
        void QTEUpdate        (const float deltaTime);
        void SharkAtack2Update(const float deltaTime);
        void QTEUpdate2       (const float deltaTime);
};