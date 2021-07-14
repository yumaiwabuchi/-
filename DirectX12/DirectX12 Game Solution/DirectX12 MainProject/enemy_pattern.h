#include <Base/pch.h>
#include <Base/dxtk.h>
#include "Scene.h"
#include <random>
//#include "MainScene.h"
#include "defined.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class enemy_pattern {

private:
	

	//お邪魔画像
	DX9::SPRITE enemy_sprite_1;//
	DX9::SPRITE enemy_sprite_2;//

	DX9::SPRITEFONT font_;

	DX9::SPRITEFONT fishing_timenoon_;


private:
	//定数

	//釣られるまで
	const int FISHING_TIME_ = 3375;

	//スプライトcount
	const int ENEMY_COUNT_ = 40;
	const int ENEMY_COUNT2_ = 14;

	//お邪魔　座標
	//startposition
	const float X_START_POSITION_[40] =
	{
		-4370.0f,-3880.0f,-3120.0f,-2480.0f,2185.0f,
		-1950.0f,-1230.0f,-740.0f,-320.0f,1550.0f,
		2250.0f,2610.0f,2805.0f,3380.0f,3610.0f,
		3950.0f,4500.0f,4900.0f,5160.0f,5410.0f,
		5970.0f,6160.0f,6680.0f,7770.0f,
		8500.0f,9010.0f,9460.0f,9815.0f,10425.0f,
		10955.0f,11405.0f,11570.0f,11795.0f,12140.0f,
		12540.0f,12970.0f,13100.0f,13380.0f,13755.0f,
		13990.0f
	};


	const float Y_START_POSITION_[40] =
	{
		370.0f,25.0f,110.0f,30.0f,500.0f,
		350.0f,30.0f,90.0f,0.0f,310.0f,
		45.0f,30.0f,210.0f,400.0f,500.0f,
		30.0f,40.0f,300.0f,500.0f,370.0f,
		210.0f,30.0f,300.0f,30.0f,
		60.0f,10.0f,10.0f,290.0f,290.0f,
		20.0f,290.0f,290.0f,290.0f,10.0f,
		280.0f,10.0f,230.0f,140.0f,180.0f,
		0.0f
	};

	const float X_START_POSITION_2[14] =
	{
		-3520.0f,-2180.0f,-1690.0f,-1120.0f,-420.0f,
		1020.0f,4160.0f,7320.0f,8230.0f,9225.0f,
		10010.0f,12155.0f,12830.0f,13610.0f
	};


	const float Y_START_POSITION_2[14] =
	{
		500.0f,500.0f,500.0f,500.0f,500.0f,
		500.0f,500.0f,460.0f,500.0f,500.0f,
		500.0f,500.0f,500.0f,500.0f
	};

	const float SPEED_UP_TIME_ = 0.0f;


	const float LEFT_SPEED_SERECT_1 = 500;
	/*const float LEFT_SPEED_SERECT_2 = 1000;
	const float LEFT_SPEED_SERECT_3 = 14;*/

   const float NORMAL_SPEED_SERECT_ = 100;
  
   const float LIGHT_SPEED_SERECT_1 = 300;
   /*const float LIGHT_SPEED_SERECT_2 = 400;
   const float LIGHT_SPEED_SERECT_3 = 550;*/
   
   //当たり判定
   const int ENEMY_SIZE_X = 120;
   const int ENEMY_SIZE_Y = 120;

   //パワー減少
   const float DOWN_POWER_ = 50;
   const float UP_POWER_ = 80;



public:
	//関数
	void Initialize();
	void LoadAssets();

	void Update(const float deltaTime, const int gaugeDirection, SimpleMath::Vector3& shark_position);

	void Render();

public:
	//追加　関数 Main
	void enemy_pattern_Update(const float deltaTime, const int gaugeDirection);
	void enemy_out_Update(const float deltaTime, SimpleMath::Vector3& shark_position);
	//Enemy_Pattern
	void pattern_1(const float deltaTime, SimpleMath::Vector3& shark_position);
	
	
	//Render
	void enemy_Render();

	bool  isIntersect(Rect& rect1, Rect& rect2);

private:
	//変数
	int enemy_count_;//エネミーcount（１５）
	int enemy_count_2;

	float pattern_x;//
	

	float left_speed_serect_1;
	float left_speed_serect_2;
	float left_speed_serect_3;
	
	float normal_speed_serect_;
	 
	float light_speed_serect_1;
	float light_speed_serect_2;
	float light_speed_serect_3;
	//座標　ｘ・ｙ・ｚ
	
	
	float x_position_[40];
	float y_position_[40];

	float x_position_2[14];
	float y_position_2[14];


	int enemy_size_x;
	int enemy_size_y;
//flag
	//X     //Y    

	int speed_up_time_;

	int back_flag;

	int pattern_flag_x;

	int hit_enemy_flg_;
	float hit_enemy_time_;

	int fishing_time_;
	
//random_program ランダムgenerator
	
	
    
    std::mt19937 randomEngine_1;
	std::uniform_int_distribution<int> Random_Enemy_Pattern_1;
	std::mt19937 randomEngine_2;
	std::uniform_int_distribution<int> Random_Enemy_Pattern_2;
	
public:
	//当たり判定
	const float SHARK_SIZE_X_ = 380.0f;
	const float SHARK_SIZE_Y_ = 230.0f;
	
	
	int GetHitFlg() { return hit_enemy_flg_; }

};
