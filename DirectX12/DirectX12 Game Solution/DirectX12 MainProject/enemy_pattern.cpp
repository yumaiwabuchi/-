#include <enemy_pattern.h>
#include <random>
#include <DontDestroyOnLoad.h>

void enemy_pattern::Initialize()
{
    //初期位置
    
    pattern_x = 0;

    pattern_flag_x = 0;

    back_flag = 0;

    enemy_count_ = ENEMY_COUNT_;

    enemy_count_2 = ENEMY_COUNT2_;

    for (int i = 0; i < ENEMY_COUNT_; i++)
    {
        x_position_[i] = X_START_POSITION_[i];
        y_position_[i] = Y_START_POSITION_[i];
        
    }

    for (int A = 0; A < ENEMY_COUNT2_; A++)
    {
        x_position_2[A] = X_START_POSITION_2[A];
        y_position_2[A] = Y_START_POSITION_2[A];

    }

    Random_Enemy_Pattern_1 = std::uniform_int_distribution<>(1, 1);
    
    pattern_x = Random_Enemy_Pattern_1(randomEngine_1);

    Random_Enemy_Pattern_2 = std::uniform_int_distribution<>(0, 6);
    /*pattern_x = Random_Enemy_Pattern_1(randomEngine_1);*/

    //変数　初期化
    

    left_speed_serect_1 = LEFT_SPEED_SERECT_1;
    left_speed_serect_2 = LEFT_SPEED_SERECT_2;
    left_speed_serect_3 = LEFT_SPEED_SERECT_3;

    normal_speed_serect_ = NORMAL_SPEED_SERECT_;

    light_speed_serect_1 = LIGHT_SPEED_SERECT_1;
    light_speed_serect_2 = LIGHT_SPEED_SERECT_2;
    light_speed_serect_3 = LIGHT_SPEED_SERECT_3;


    //当たり判定
    enemy_size_x = ENEMY_SIZE_X;
    enemy_size_y = ENEMY_SIZE_Y;

    hit_enemy_flg_ = 0;
    hit_enemy_time_ = 0.0f;

   
}

void enemy_pattern::LoadAssets()
{

    //プレイヤースクリプト
    

        
        
            enemy_sprite_1 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"c14ab7d9633ac48b.png");
               
            enemy_sprite_2 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Rock.png");
        

            font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 50);

}

void enemy_pattern::Update(const float deltaTime, const int gaugeDirection)
{
    if (DXTK->KeyEvent->pressed.K)
    {

        back_flag = 1;
    }
    
    //関数
    enemy_pattern_Update(deltaTime, gaugeDirection);

    if (pattern_flag_x == 1) 
        pattern_1(deltaTime);
    
    


}

void enemy_pattern::enemy_pattern_Update(const float deltaTime, const int gaugeDirection)
{
   
   if (x_position_[0] >= 1050)
   {
       back_flag = 7;

   }

   if (x_position_[39] <= 1000)
   {
       back_flag = 7;

   }

        

   if (Random_Enemy_Pattern_1(randomEngine_1) == 1)
   {

       pattern_flag_x = 1;

   }
   

   if (gaugeDirection == nothing) {
       back_flag = 0;
   }

    if (DXTK->KeyEvent->pressed.Q || gaugeDirection == sharksmall)
    {

        back_flag = 1;  //Random_Enemy_Pattern_2(randomEngine_2);
    
    }

    if (DXTK->KeyEvent->pressed.W || gaugeDirection == sharkmedium)
    {

        back_flag = 2;  //Random_Enemy_Pattern_2(randomEngine_2);

    }

    if (DXTK->KeyEvent->pressed.E || gaugeDirection == sharklarge)
    {

        back_flag = 3;  //Random_Enemy_Pattern_2(randomEngine_2);

    }

    if (DXTK->KeyEvent->pressed.R || gaugeDirection == anglersmall)
    {

        back_flag = 4;  //Random_Enemy_Pattern_2(randomEngine_2);

    }

    if (DXTK->KeyEvent->pressed.T || gaugeDirection == anglermedium)
    {

        back_flag = 5;  //Random_Enemy_Pattern_2(randomEngine_2);

    }

    if (DXTK->KeyEvent->pressed.Y || gaugeDirection == anglerlarge)
    {

        back_flag = 6;  //Random_Enemy_Pattern_2(randomEngine_2);

    }


}

void enemy_pattern::pattern_1(const float deltaTime)
{
        if (back_flag == 0) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] += normal_speed_serect_ * deltaTime;
                
            } 

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] += normal_speed_serect_ * deltaTime;
            }
        
        }


        else if (back_flag == 1) 
        {




            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] -= left_speed_serect_1 * deltaTime;

            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] -= left_speed_serect_1 * deltaTime;
            }

        }

        else if (back_flag == 2) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] -= left_speed_serect_2 * deltaTime;
            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] -= left_speed_serect_2 * deltaTime;
            }

        }

        else if (back_flag == 3) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] -= left_speed_serect_3 * deltaTime;
            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] -= left_speed_serect_3 * deltaTime;
            }

        }

        else if (back_flag == 4) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] += light_speed_serect_1 * deltaTime;

            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] += light_speed_serect_1 * deltaTime;
            }

        }

        else if (back_flag == 5) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] += light_speed_serect_2 * deltaTime;
            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] += light_speed_serect_2 * deltaTime;
            }

        }

        else if (back_flag == 6) 
        {

            for (int i = 0; i < enemy_count_; i++) {

                x_position_[i] += light_speed_serect_3 * deltaTime;
            }

            for (int A = 0; A < enemy_count_2; A++) {

                x_position_2[A] += light_speed_serect_3 * deltaTime;
            }

        }

      enemy_out_Update(deltaTime);

    
}

void enemy_pattern::enemy_out_Update(const float deltaTime)
{
    if (hit_enemy_flg_ == 0) {
        for (int i = 0; i < 14; i++) {
            if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
                (RectWH(x_position_2[i], y_position_2[i], enemy_size_x, enemy_size_y))))
            {   // 当たった時　とげ

                hit_enemy_flg_ = 1;




            }

            else {



            }

        }

        for (int A = 0; A < 14; A++) {
            if (isIntersect(RectWH(shark_position_.x, shark_position_.y, SHARK_SIZE_X_, SHARK_SIZE_Y_),
                (RectWH(x_position_2[A], x_position_2[A], enemy_size_x, enemy_size_y))))
            { //当たった時　岩

                hit_enemy_flg_ = 1;


            }

            else
            {



            }
        }
    }

    if (hit_enemy_flg_ == 1) {
        hit_enemy_time_ += deltaTime;

        if (hit_enemy_time_ >= 1.5f) {
            hit_enemy_time_ = 0.0f;
            hit_enemy_flg_ = 0;
        }
    }
}


void enemy_pattern::Render()
{

    //関数
    enemy_Render();

}

void enemy_pattern::enemy_Render()
{
    if (pattern_flag_x == 1) {

        //プレイヤースクリプト

            for (int i = 0; i < enemy_count_; i++) 
            {
               DX9::SpriteBatch->DrawSimple(enemy_sprite_1.Get(), SimpleMath::Vector3(x_position_[i], y_position_[i], 0));
                
            }


            for (int A = 0; A < enemy_count_2; A++)
            {
               DX9::SpriteBatch->DrawSimple(enemy_sprite_2.Get(), SimpleMath::Vector3(x_position_2[A], y_position_2[A], 0));
                
            }
        
        
    }


    DX9::SpriteBatch->DrawString(
        font_.Get(),
        SimpleMath::Vector2(320.0f, 300.0f),
        DX9::Colors::RGBA(0, 0, 0, 255),
        L"%d", pattern_flag_x
    );


}

bool enemy_pattern::isIntersect(Rect& rect1, Rect& rect2)
{
    const bool isNotLeftContact = rect1.left > rect2.right; // 成り立つ or 成り立たないが変数に代入される
    const bool isNotRightContact = rect1.right < rect2.left;  // 成り立つとき…true / 成り立たない…false
    const bool isNotTopContact = rect1.top > rect2.bottom;
    const bool isNotBottomContact = rect1.bottom < rect2.top;
    if (isNotLeftContact || isNotRightContact || isNotTopContact || isNotBottomContact) {
        return false;
    }

    return true;
}