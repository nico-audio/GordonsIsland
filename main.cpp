/*
 * File:        [main.cpp]
 * Description: [The main entry point - initializes the game window, loads assets,
 *              and runs the main game loop.] 
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[20/08/2025, Render prop at map location]
 * Version:     [0.0.1]
 *
 * Notes:
 *  - Handles boundary checking to keep the player within the map.
 *
 * Usage:
 * [Controls]
 * - Use WASD keys to move the character
 */

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main(){

    // Window dimensions
    const int kWindowWidth{384};
    const int kWindowHeight{384};

    // Draw window
    InitWindow(kWindowWidth, kWindowHeight, "Top down 2D game");

    // Load world map texture
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap2.png");

    // Map position
    Vector2 worldMapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // Character variables
    Character gordon{kWindowWidth, kWindowHeight};

    // Objects
    Prop plant{Vector2{}, LoadTexture("objects/Fetus_shadow1_2.png")};

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

        // Render Props
        plant.Render(gordon.GetWorldPos());

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
