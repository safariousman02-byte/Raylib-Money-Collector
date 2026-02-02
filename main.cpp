#include "raylib.h"
#include "math.h"

typedef enum GameScreen {
    LOADING,
    MENU,
    GAMEPLAY,
    GAMEOVER
} GameScreen;

    int main(){
        
            InitWindow(800, 600, "MONEY COLLECTOR GAME");
            SetTargetFPS(60);

        //-----------------------------DECLARATION--------------------------------------

            float loadingprogress = 0.0f;
                        
                        Rectangle start = {300, 150, 200, 50};
                        Rectangle upgrade = {300, 220, 200, 50};
                        Rectangle exit = {300, 290, 200, 50};
                        Vector2 mousepos = GetMousePosition();
                        bool hover01 = CheckCollisionPointRec(mousepos, start);

            Color barcolor = {8, 255, 255, 255};

            Image home = LoadImage("homepage.png");
            ImageResize(&home, 800, 600);

            Texture2D home02 = LoadTextureFromImage(home);

            Image loadpage = LoadImage("loadingbackground.png");
            ImageResize(&loadpage, 800, 600);

            Texture2D loadingpage02 = LoadTextureFromImage(loadpage);
            
            Color buttoncolor = LIGHTGRAY;
            Vector2 mousepoint = GetMousePosition();
            Rectangle buttonrect = {300, 200, 200, 50};

            Vector2 playerpos = {400.0f, 400.0f};
            float basespeed = 4.0f;
            float coinspeed = basespeed;
            Vector2 coinpos = { (float)GetRandomValue(50, 750), -20.0f};
            int score = 0;

            int lives = 3;

            bool isgameover = false;

            float titley = 100 + sin(GetTime()*3.0f) * 10.0f;

            //-------------------------STATE MENU--------------------------------------

            GameScreen currentscreen = LOADING;

            while(!WindowShouldClose()){

                
                switch(currentscreen) {
                    //........................UPDATE LOGIC..........................

                    case LOADING: {

                        loadingprogress += 0.001f;

                        if (loadingprogress >= 1.0f || IsKeyPressed(KEY_P)) currentscreen = MENU;

                    }break;

                    case MENU:{

                       

                         
                        
                        
                        

                        if (hover01 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentscreen = GAMEPLAY;

                    }break;
                    
                    case GAMEPLAY: {
                        
                        if(IsKeyDown(KEY_LEFT)) playerpos.x -= 5.0f;
                        if(IsKeyDown(KEY_RIGHT)) playerpos.x += 5.0f;

                        if (playerpos.x < 0) playerpos.x = 0;
                        if (playerpos.x > 760) playerpos.x = 760;

                        coinspeed = basespeed + (score / 5.0f);

                        if (coinspeed > 15.0f) coinspeed = 15.0f;

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

                        if (lives == 0) currentscreen = GAMEOVER;

                        if (IsKeyPressed(KEY_SPACE)) {

                            score = 0;
                            lives = 3;
                            currentscreen = MENU;

                        }

                    }break;

                    case GAMEOVER: {

                        if (IsKeyPressed(KEY_ENTER)) {

                            score = 0;
                            lives = 3;
                            currentscreen = GAMEPLAY;

                        }

                    }break;
                  
                }
                    

                BeginDrawing();
                    ClearBackground(RAYWHITE);
                        

                        switch(currentscreen){

                            case LOADING :{

                                DrawTexture(loadingpage02, 0, 0, WHITE);

                                DrawText("LAODING ASSETS...", 300, 520, 20, LIGHTGRAY);
                                DrawRectangle(250, 570, 300, 5, DARKGRAY);
                                DrawRectangle(250, 570, (int)(300*loadingprogress), 5, barcolor);

                            }break;

                            case MENU: {

                                DrawTexture(home02, 0, 0, WHITE);
                                
                                DrawRectangleRec(start, Fade(SKYBLUE, hover01 ? 0.6f : 0.3));
                                DrawRectangleLinesEx(start, 2, barcolor);
                                DrawText("GAME GAME", 330, 165, 28, WHITE);

                            }break;

                            case GAMEPLAY: {
                            
                                DrawText("USE LEFT/RIGHT ARROWS TO MOVE!", 10, 10, 20, DARKGRAY);
                                DrawText("The Heart is Beating!", 280, 200, 20, LIGHTGRAY);
                                DrawRectangleV(playerpos, (Vector2){40.0f, 40.0f}, BLUE);
                                DrawCircleV(coinpos, 10.0f, GOLD);
                                DrawText(TextFormat("Score: %i", score), 10, 40, 20, DARKGRAY);
                                DrawText(TextFormat("Lives: %i", lives), 10, 70, 20, RED);

                            }break;

                            case GAMEOVER: {

                                DrawText("GAME OVER", 300, 150, 40, MAROON);
                                DrawText(TextFormat("Final Score: %i, score"), 330, 200, 20, DARKGRAY);
                                DrawText("Press Enter To Restart", 270, 260, 20, DARKGRAY);

                            }
                        }
                        
                EndDrawing();

            }
            UnloadImage(home);
            UnloadTexture(home02);

            UnloadImage(loadpage);
            UnloadTexture(loadingpage02);

            CloseWindow();
            

        return 0;
    }