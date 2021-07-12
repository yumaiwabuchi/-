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

    DX9::SPRITEFONT tap_font_;
    DX9::SPRITEFONT debug_font_;

    DX9::SPRITE bg_sky_sprite_;
    DX9::SPRITE bg_front_sea_sprite_;
    DX9::SPRITE bg_behind_sea_sprite_;
    DX9::SPRITE bg_frame_sprite_;

    DX9::SPRITE gauge_red_sprite_;
    DX9::SPRITE gauge_blue_sprite_;
    DX9::SPRITE battle_cut_in_sprite_;
    DX9::SPRITE you_win_sprite_;

    DX9::SPRITE shark_hp_empty_sprite_;
    DX9::SPRITE shark_hp_hull_sprite_;

    DX9::SPRITE shark_sprite_;
    DX9::SPRITE shark_behind_sprite_;

    DX9::SPRITE shark_gauge_;
    DX9::SPRITE shark_gauge_empty_;

    DX9::SPRITE angler_line_;

    DX9::SPRITE angler_UI_;
    DX9::SPRITE angler_position_UI_;

    DX9::SPRITE fishing_rod_sprite_;

    DX9::SPRITE angler_hp_empty_sprite_;
    DX9::SPRITE angler_hp_hull_sprite_;

    DX9::SPRITE dead_zone_sprite_;

    DX9::SPRITE danger_sprite_;

    

    // �萔

    // BG
    const float BG_SIZE_X_                     = 1280.0f;
    const float BG_SIZE_Y_                     =  720.0f;
    const float BG_SKY_POSITION_Z_             =    1.0f;
    const float BG_FRONT_SEA_POSITION_Z_       =   -2.0f;
    const float BG_FRONT_SEA_START_POSITION_X_ = -480.0f;
    const float BG_BEHIND_SEA_POSITION_Z_      =    0.1f;
    const float BG_FRAME_POSITION_Z_           =   -3.0f;
    const float BG_SPEED_                      =  100.0f;
    const float BG_FRONT_SPEED_                =  150.0f;
    
    // �T���̓���
    const float SHARK_SIZE_X_                 =                      320.0f;
    const float SHARK_SIZE_Y_                 =                      240.0f;
    const float SHARK_SIZE_HALF_X_            =        SHARK_SIZE_X_ / 2.0f;
    const float SHARK_SIZE_HALF_Y_            =        SHARK_SIZE_Y_ / 2.0f;
    const float SHARK_START_POSITION_X_       = 640.0f - SHARK_SIZE_HALF_X_;
    const float SHARK_START_POSITION_Y_       =                      400.0f;
    const float SHARK_START_POSITION_Z_       =                        0.0f;
    const float SHARK_RIGHT_LIMIT_POSITION_X_ =     1280.0f - SHARK_SIZE_X_;
    const float SHARK_LEFT_LIMIT_POSITION_X_  =                        0.0f;
    const float SHARK_UP_LIMIT_POSITION_Y_    =                        0.0f;
    const float SHARK_DOWN_LIMIT_POSITION_Y_  =      720.0f - SHARK_SIZE_Y_;
    const float SHARK_STOP_TIME_              =                        1.0f;
    const float SHARK_MOVE_SPEED_             =                      300.0f;
    const float SHARK_MOVE_SPEED_Y_           =                     1500.0f;
    const float SHARK_MOVE_SPEED_SIDE_        =                      250.0f;
    const float SHARK_MOVE_UP_SPEED_          =                        1.0f;
    const float SHARK_MOVE_UP_SPEED_UP_       =                        3.0f;
    const float SHARK_MOVE_UP_SPEED_UP_LIMIT_ =                        3.0f;
    const float INPUT_TIME_LIMIT_             =                        0.5f;
    const float SHARK_SPRITE_X_CHANGE_TIME_   =                        0.2f;
    const float SHARK_SPRITE_SIZE_X_LIMIT_    =     4160.0f - SHARK_SIZE_X_;

    // �T���̃Q�[�W
    const float SHARK_GAUGE_START_POSITION_X_ = 640.0f - 300.0f;
    const float SHARK_GAUGE_START_POSITION_Y_ = 620.0f;
    const float SHARK_GAUGE_START_POSITION_Z_ =           -10.0f;
    const float SHARK_GAUGE_SIZE_X_           = 600.0f;
    const float SHARK_GAUGE_SIZE_Y_           = 50.0f;
    const float SHARK_GAUGE_GROW_SPEED_       = 600.0f;
    const float SHARK_GAUGE_DECREASE_SPEED_   = 400.0f;
    const float SHARK_GAUGE_STOP_TIME_        = 1.0f;

    // �ނ�l�̃��C��
    const float ANGLER_LINE_START_POSITION_X_ = SHARK_GAUGE_START_POSITION_X_ + 100.0f;
    const float ANGLER_LINE_START_POSITION_Y_ = SHARK_GAUGE_START_POSITION_Y_;
    const float ANGLER_LINE_START_POSITION_Z_ = SHARK_GAUGE_START_POSITION_Z_;
    const float ANGLER_LINE_LIMIT_RIGHT_ = SHARK_GAUGE_START_POSITION_X_ + SHARK_GAUGE_SIZE_X_ - 100.0f;
    const float ANGLER_LINE_LIMIT_LEFT_  = SHARK_GAUGE_START_POSITION_X_ + 100.0f;
    const float ANGLER_LINE_MOVE_SPEED_ = 450.0f;
    
    // �T����HP
    const float SHARK_HP_POSITION_X_    =                    10.0f;
    const float SHARK_HP_POSITION_Y_    =          360.0f - 232.0f;
    const float SHARK_HP_POSITION_Z_    =                    -5.0f;
    const float SHARK_HP_RIGHT_LIMIT_   =                   114.0f;
    const float SHARK_HP_DOWN_LIMIT_    =                   464.0f;
    const float SHARK_HP_START_         =                     0.0f;
    const float SHARK_HP_DAMAGE_        =                     4.4f;
    const float SHARK_HP_DAMAGE_SLOWLY_ =  SHARK_HP_DAMAGE_ * 2.0f;
    const float SHARK_HP_DAMAGE_ATACK   =                     5.0f;
    const float SHARK_HP_HEAL_          =                    50.0f;

    // �T���̍U��
    const float SHARK_ATACK_GROW_SPEED_     = 1200.0f;
    const float SHARK_ATACK_DECREASE_SPEED_ = 1400.0f;
    const float SHARK_ATACK_LIMIT_SPEED_    =  700.0f;
    const float SHARK_ATACK_TIME_           =   1.00f;

    // �T�������������
    const float SHARK_PULL_SPEED_NOTHING_      = 310.0f;
    const float SHARK_PULL_SPEED_SHARKLARGE_   =  10.0f;
    const float SHARK_PULL_SPEED_SHARKMEDIUM_  =  50.0f;
    const float SHARK_PULL_SPEED_SHARKSMALL_   = 100.0f;
    const float SHARK_PULL_SPEED_ANGLERLARGE_  = 460.0f;
    const float SHARK_PULL_SPEED_ANGLERMEDIUM_ = 410.0f;
    const float SHARK_PULL_SPEED_ANGLERSMALL_  = 360.0f;

    // �ނ�lUI
    const float ANGLER_UI_START_POSITION_X_ = 640.0f - (843.0f / 2.0f);
    const float ANGLER_UI_START_POSITION_Y_ = 50.0f;
    const float ANGLER_UI_START_POSITION_Z_ = 0.0f;
    const float ANGLER_POZI_UI_START_POSITION_X_ = ANGLER_UI_START_POSITION_X_;
    const float ANGLER_POZI_UI_START_POSITION_Y_ = 0.0f;
    const float ANGLER_POZI_UI_START_POSITION_Z_ = 0.0f;
    const float ANGLER_UI_LARGE_SPEED_ = 53.0f;
    const float ANGLER_UI_MEDIUM_SPEED_ = ANGLER_UI_LARGE_SPEED_ * 0.6f;
    const float ANGLER_UI_SMALL_SPEED_ = ANGLER_UI_LARGE_SPEED_ * 0.4f;
    const float ANGLER_UI_LIMIT_POSITION_X_ = ANGLER_UI_START_POSITION_X_ + 795.0f;
    const float BATTLE_APPEAR_POSITION_X_ = ANGLER_UI_START_POSITION_X_ + 695.0f;

    // �Q�[�W�̍�
    const float SHARK_LARGE_LINE_POSITION_   = -340.0f + 166.0f + 166.0f;
    const float SHARK_MEDIUM_LINE_POSITION_  = -340.0f + 166.0f;
    const float SHARK_SMALL_LINE_POSITION_   = -340.0f;
    const float ANGLER_LARGE_LINE_POSITION_  = -340.0f - 166.0f - 166.0f;
    const float ANGLER_MEDIUM_LINE_POSITION_ = -340.0f - 166.0f;
    const float ANGLER_SMALL_LINE_POSITION_  = -340.0f;

    // �ނ�Ƃ̓���
    const float FISHING_ROD_SIZE_X_                 =                        200.0f;
    const float FISHING_ROD_SIZE_Y_                 =                        200.0f;
    const float FISHING_ROD_SIZE_HALF_X_            =    FISHING_ROD_SIZE_X_ / 2.0f;
    const float FISHING_ROD_SIZE_HALF_Y_            =    FISHING_ROD_SIZE_Y_ / 2.0f;
    const float FISHING_ROD_START_POSITION_X_       =                          0.0f;
    const float FISHING_ROD_START_POSITION_Y_       =                        -50.0f;
    const float FISHING_ROD_START_POSITION_Z_       =                          0.0f;
    const float FISHING_ROD_RIGHT_LIMIT_POSITION_X_ = 1280.0f - FISHING_ROD_SIZE_X_;
    const float FISHING_ROD_LEFT_LIMIT_POSITION_X_  =                          0.0f;
    const float FISHING_ROD_UP_LIMIT_POSITION_Y_    =                       -100.0f;
    const float FISHING_ROD_DOWN_LIMIT_POSITION_Y_  =  720.0f - FISHING_ROD_SIZE_Y_;
    const float FISHING_ROD_START_SPEED_            =                        100.0f;

    // �ނ莅
    const float FISHING_LINE_2_DIFFERENCE_ =               0.5f;
    const float FISHING_LINE_3_DIFFERENCE_ =              -0.5f;
    const float SHARK_LINE_DIFFERENCE_X_   = SHARK_SIZE_HALF_X_;
    const float SHARK_LINE_DIFFERENCE_Y_   = SHARK_SIZE_HALF_Y_;


    // �ނ�ƂɌ���������
    const float TOWARDS_FISHING_ROD_START_SPEED_ = 170.0f;
    const float TOWARDS_FISHING_ROD_SPEED_UP_    =  80.0f;
    const float SHARK_ROD_DIFFERENCE_            = 150.0f;

    // �ނ�l�̈ʒu

    // �ނ�l
    const float ANGLER_HP_POSITION_X_       = 1280.0f - 114.0f;
    const float ANGLER_HP_POSITION_Y_       =  360.0f - 232.0f;
    const float ANGLER_HP_POSITION_Z_       =            -5.0f;
    const float ANGLER_HP_RIGHT_LIMIT_      =           114.0f;
    const float ANGLER_HP_DOWN_LIMIT_       =           464.0f;
    const float ANGLER_HP_START_            =             0.0f;
    const float ANGLER_HP_HALF_             =           200.0f;
    const float ANGLER_POSITION_SPEED_Y_    =             5.0f;
    const float ANGLER_POSITION_SPEED_UP_Y_ =            15.0f;

    // �΂��荇��
    const float GAUGE_SIZE_HALF_X_          =   300.0f;
    const float GAUGE_START_POSITION_X_     =   340.0f;
    const float GAUGE_START_POSITION_Y_     =   260.0f;
    const float GAUGE_RED_POSITION_Z_       =   -30.0f;
    const float GAUGE_BLUE_POSITION_Z_      =   -29.0f;
    const float GAUGE_RED_HEIGHT_START_     =   200.0f;
    const float GAUGE_RED_WIDTH_START_      =   300.0f;
    const float GAUGE_RED_WIDTH_LIMIT_      =   600.0f;
    const float GAUGE_RED_WIDTH_ADD_SPEED_  =   200.0f;
    const float GAUGE_RED_WIDTH_TAKE_SPEED_ =  1350.0f;
    const float BATTLE_CUT_IN_POSI_X_       = -1280.0f;
    const float BATTLE_CUT_IN_POSI_Y_       =   180.0f;
    const float BATTLE_CUT_IN_POSI_Z_       =   -10.0f;
    const float YOU_WIN_POSITION_Y_         =   180.0f;
    const float YOU_WIN_POSITION_Z_         =   -50.0f;
    const float CUT_IN_SPRITE_SPEED_ = 1280.0f;
    const float BATTLE_START_TIME_ = 2.0f;
    const float BATTLE_TIME_ = 5.0f;
    const float BATTLE_FINISH_CLEAR_TIME_ = 3.0f;
    const float BATTLE_FINISH_MISS_TIME_ = 0.5f;
    const float BATTLE_MISS_UI_BACK_SPEED_ = 1000.0f;

    // �J�E���g�_�E��
    const float COUNT_DOWN_START_           =     100.0f;
    const float COUNT_DOWN_NUMBER_          =       1.0f;

    // �f�b�h�]�[��
    const float DEAD_ZONE_RIMIT_TIME_     =    30.0f;
    const float DEAD_ZONE_UP_             =    0.0f;
    const float DEAD_ZONE_DOWN_           =  100.0f;
    const float DEAD_ZONE_RIGHT_          = 1280.0f;
    const float DEAD_ZONE_LEFT_           =    0.0f;
    const float DANGER_POSITION_X_        =  320.0f;
    const float DANGER_POSITION_Y_        =  260.0f;
    const float DANGER_POSITION_Z_        =   -1.0f;
    const float DANGER_ALPHA_VALUE_SPEED_ =    2.0f;
    const float DANGER_ALPHA_VALUE_LIMIT_ =   0.95f;

    // �̗͌��鑬�x�̃{�[�_�[
    const float SHARK_HP_DAMAGE_SPEED_BORDER_ = 410.0f;



    // �ϐ�

    // BG
    SimpleMath::Vector3 bg_sky_position_;
    SimpleMath::Vector3 bg_front_sea_position_;
    SimpleMath::Vector3 bg_behind_sea_position_;
    SimpleMath::Vector3 bg_frame_position_;

    // �T��
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

    // �T���̃Q�[�W
    SimpleMath::Vector3 shark_gauge_position_;
    SimpleMath::Vector3 shark_gauge_empty_position_;
    float shark_gauge_x_;
    float shark_gauge_speed_;
    int shark_gauge_flg_;
    float shark_gauge_stop_time_;
    int shark_standby_flg_;
    float shark_standby_time_;

    // �ނ�l���C��
    SimpleMath::Vector3 angler_line_position_;
    int angler_line_move_direction_;
    float angler_line_value_;
    enum Angler_Line_Direction_ {
        right,
        left
    };

    // �ނ�lUI
    SimpleMath::Vector3 angler_UI_position_;
    SimpleMath::Vector3 angler_position_UI_position_;

    // �Q�[�W�̍�
    /*int gauge_difference_;
    enum GaugeDirection {
        sharklarge,
        sharkmedium,
        sharksmall,
        anglerlarge,
        anglermedium,
        anglersmall,
        nothing
    };*/

    // �ނ�l
    SimpleMath::Vector3 angler_hp_cover_position_;
    SimpleMath::Vector3 angler_hp_position_;
    float angler_hp_;
    float angler_hp_zero_time_;
    int   angler_hp_flg_;

    // �ނ��
    SimpleMath::Vector3 fishing_rod_position_;
    int fishing_rod_direction;
    enum FishingRodMoveDirection {
        rightmove,
        leftmove
    };
    float fishing_rod_speed_;

    // �T����HP
    SimpleMath::Vector3 shark_hp_cover_position_;
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
    SimpleMath::Vector3 battle_cut_in_posi_;
    int battle_cut_in_flg_;
    float battle_start_time_;
    float battle_time;
    int battle_flg;
    float battle_finish_time;
    int you_win_flg;
    SimpleMath::Vector3 you_win_position;
    int battle_start_flg_;

    // �J�E���g�_�E��
    int   count_down_;

    // �f�b�h�]�[��
    float dead_zone_time;
    int   danger_flg;
    float danger_alpha_;
    float danger_alpha_flg_;
    enum {
        Up,
        Down
    };

    // �Q�[���I�[�o�[
    int   game_over_flg_;

    // �Q�[���N���A
    int   game_clear_flg_;

    // �v���C�^�C��
    float game_time_;

    // �����蔻��
    bool  isIntersect(Rect& rect1, Rect& rect2);

// �֐�
private:
    void BGUpdate             (const float deltaTime);
    void GaugeUpdate          (const float deltaTime);
    void SharkUpdate          (const float deltaTime);
    // void SharkHPUpdate        (const float deltaTime);
    void SharkMoveUpdate      (const float deltaTime);
    // void SharkAtackUpdate     (const float deltaTime);
    void SharkSpriteUpdate    (const float deltaTime);
    void SharkGaugeUpdate     (const float deltaTime);
    void GaugeDifferenceUpdate(const float deltaTime);
    // void FishingRodUpdate     (const float deltaTime);
    // void DeadZoneUpdate       (const float deltaTime);
    void AnglerUpdate         (const float deltaTime);
    void AnglerUIUpdate       (const float deltaTime);
    void AnglerGaugeUpdate    (const float deltaTime);
    void GameTimeUpdate       (const float deltaTime);
    void DeadUpdate           (const float deltaTime);

public:
    // �Q�[�W�̍��𔻒肷��ϐ�
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

};

