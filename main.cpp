/*
 * File:        [main.cpp]
 * Description: [Top down 2D game]
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[12/08/2025, Movement implementation, add character texture]
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
    Vector2 gordonPos{
        (float)kWindowWidth/2.0f - 4.0f * (0.5f * (float)gordon.width/12.0f),
        (float)kWindowHeight/2.0f - 4.0f * (0.5f * (float)gordon.height/4.0f)
    };
    
    SetTargetFPS(60);
    
    // Keep window open and clear background
    while (!WindowShouldClose()){
        
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        
        // Movement
        Vector2 direction = getInputDirection();
        if (Vector2Length(direction) != 0.0){
            worldMapPos = Vector2Subtract(worldMapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        // Draw world map
        DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

        // Draw character
        Rectangle source{0.f, 0.f, (float)gordon.width/12.f, (float)gordon.height/4.0f};
        Rectangle destRec{gordonPos.x, gordonPos.y, 4.0f * (float)gordon.width/12.0f, 4.0f * (float)gordon.height/4.0f};
        DrawTexturePro(gordon, source, destRec, Vector2{}, 0.f, WHITE);

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
