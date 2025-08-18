/*
 * File:        [main.cpp]
 * Description: [Top down 2D game]
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[18/08/2025, Character instance, check map bounds]
 * Version:     [0.0.1]
 *
 * Notes:
 *
 *
 * Usage:
 * [Controls]
 * - Use WASD keys to move the character
 */

#include "raylib.h"
#include "raymath.h"
#include "Character.h"

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
    const float mapScale{4.0f};

    // Character variables
    Character gordon;
    gordon.SetScreenPos(kWindowWidth, kWindowHeight); 

    SetTargetFPS(60);

    // Keep window open and clear background
    while (!WindowShouldClose()){

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Move map position
        worldMapPos = Vector2Scale(gordon.GetWorldPos(), -1.0f);

        // Draw world map
        DrawTextureEx(worldMap, worldMapPos, 0.0, mapScale, WHITE);
        
        // Character update
        gordon.Tick(GetFrameTime());

        // Check map bounds
        if (gordon.GetWorldPos().x < 0.0f ||
            gordon.GetWorldPos().y < 0.0f ||
            gordon.GetWorldPos().x + kWindowWidth > worldMap.width * mapScale ||
            gordon.GetWorldPos().y + kWindowHeight > worldMap.height * mapScale)
            {
                gordon.UndoMovement();
            }

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
