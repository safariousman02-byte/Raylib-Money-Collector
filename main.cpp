#include "raylib.h"

    int main(){

            InitWindow(800, 600, "MONEY COLLECTOR GAME");
            SetTargetFPS(60);

            Vector2 playerpos = {400.0f, 400.0f};
            float coinspeed = 4.0f;
            Vector2 coinpos = { (float)GetRandomValue(50, 750), -20.0f};
            int score = 0;

            int lives = 3;
            bool isgameover = false;

            while(!WindowShouldClose()){

                if (isgameover == false) {
                    
                    if(IsKeyDown(KEY_LEFT)) playerpos.x -= 5.0f;
                    if(IsKeyDown(KEY_RIGHT)) playerpos.x += 5.0f;

                    coinpos.y += coinspeed;

                    if (coinpos.y > 450.0f) {
                        lives--;
                        coinpos.y = -20.0f;
                        coinpos.x = (float)GetRandomValue(50, 750);
                    }

                    if (lives <= 0) isgameover = true;

                     Rectangle playerrect = {playerpos.x, playerpos.y, 40, 40};

                    if (CheckCollisionCircleRec(coinpos, 10.0f, playerrect)) {
                            score += 1;
                            coinpos.y = -20.0f;
                            coinpos.x = (float)GetRandomValue(50, 750);
                    }

                }
                else{

                    if (IsKeyPressed(KEY_ENTER)){
                        lives = 3;
                        score = 0;
                        isgameover = false;
                    }
                    

                }

                    

                BeginDrawing();
                    ClearBackground(RAYWHITE);
                        
                    
                        if (!isgameover){

                            DrawText("USE LEFT/RIGHT ARROWS TO MOVE!", 10, 10, 20, DARKGRAY);



                            DrawText("The Heart is Beating!", 280, 200, 20, LIGHTGRAY);

                            DrawRectangleV(playerpos, (Vector2){40.0f, 40.0f}, BLUE); 

                            DrawCircleV(coinpos, 10.0f, GOLD);

                            DrawText(TextFormat("Score: %i", score), 10, 40, 20, DARKGRAY);
                            DrawText(TextFormat("Lives: %i", lives), 10, 70, 20, RED);
                        }
                        else{
                           DrawText("GAME OVER", 300, 150, 40, MAROON);
                           DrawText("Press Enter To Restart", 270, 220, 20, DARKGRAY); 
                        }
                        
                EndDrawing();

            }
            CloseWindow();

        return 0;
    }