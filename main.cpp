/*
 * File:        [main.cpp]
 * Description: [Top down 2D game]
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[11/08/2025, Start project, create pop-up window and load world map texture]
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

 int main(){
    
    // Window dimensions
    const int kWindowWidth{384};
    const int kWindowHeight{384};
    
    // Draw window
    InitWindow(kWindowWidth, kWindowHeight, "Top down 2D game");

    // Load world map texture
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");
    
    SetTargetFPS(60);
    
    // Keep window open and clear background
    while (!WindowShouldClose()){
        
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw world map
        Vector2 worldMapPos{0.0, 0.0};
        DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
