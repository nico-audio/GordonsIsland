/*
 * File:        [main.cpp]
 * Description: [Top down 2D game]
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[14/08/2025, Idle animation, run animation]
 * Version:     [0.0.1]
 *
 * Notes:
 * 
 * 
 *
 * Usage:
 * []
 */

 #include "raylib.h"
 #include "raymath.h"

 // Gets player input and returns a direction vector
 Vector2 getInputDirection(){
    Vector2 direction{};

    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    
    return direction;
 }
 
 int main(){
    
    // Window dimensions
    const int kWindowWidth{384};
    const int kWindowHeight{384};
    
    // Draw window
    InitWindow(kWindowWidth, kWindowHeight, "Top down 2D game");

    // Load world map texture
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

    // Map position
    Vector2 worldMapPos{0.0, 0.0};

    // Movement speed
    float speed{4.0};

    // Load character texture
    Texture2D gordon = LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png");
    Texture2D gordonIdle = LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png");
    Texture2D gordonRun = LoadTexture("characters/Gordon/Unarmed_Run/Unarmed_Run_full.png");
    Vector2 gordonPos{
        (float)kWindowWidth/2.0f - 4.0f * (0.5f * (float)gordon.width/12.0f),
        (float)kWindowHeight/2.0f - 4.0f * (0.5f * (float)gordon.height/4.0f)
    };

    // 1: facing right, -1: facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    int frame{};
    const int kMaxFrames{12};
    const float kUpdateTime{1.f/12.f};

    float sprSize{12};
    
    SetTargetFPS(60);
    
    // Keep window open and clear background
    while (!WindowShouldClose()){

        // Delta time
        const float dT{GetFrameTime()};
        
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        
        // Movement
        Vector2 direction = getInputDirection();
        if (Vector2Length(direction) != 0.0){
            worldMapPos = Vector2Subtract(worldMapPos, Vector2Scale(Vector2Normalize(direction), speed));
            rightLeft = ((direction.x < 0.f) ? -1.f : 1.f);
            gordon = gordonRun;
            sprSize = 8.f;
        }
        else{
            gordon = gordonIdle;
            sprSize = 12.f;
        }

        // Draw world map
        DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

        // Update running time
        runningTime += dT;
        
        // Update animation frame
        if(runningTime >= kUpdateTime){
            runningTime = 0.0;
            frame++;
            if(frame > kMaxFrames) frame = 0;
        }

        // Draw character
        Rectangle source{frame * (float)gordon.width/sprSize, 0.f, (float)gordon.width/sprSize, (float)gordon.height/4.0f};
        Rectangle destRec{gordonPos.x, gordonPos.y, 4.0f * (float)gordon.width/sprSize, 4.0f * (float)gordon.height/4.0f};

        // Select different row from spritesheet
        source.y = ((rightLeft == 1.f) ? 2.f* source.height : 1.f * source.height);

        DrawTexturePro(gordon, source, destRec, Vector2{}, 0.f, WHITE);

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    UnloadTexture(gordon);
    CloseWindow();
}
