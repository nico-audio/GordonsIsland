/*
 * File:        [main.cpp]
 * Description: [The main entry point - initializes the game window, loads assets,
 *              and runs the main game loop.] 
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[22/08/2025, Set enemy's target to Gordon]
 * Version:     [0.0.1]
 *
 * Notes:
 *  - Handles boundary checking to keep the player within the map limits.
 *  - Implements collision detection between the player and static props.
 *
 * Usage:
 * [Controls]
 * - Use WASD keys to move the character
 */

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"


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
    Prop props[2]{
        Prop{Vector2{600.0f, 600.0f}, LoadTexture("objects/Fetus_shadow1_2.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("objects/Eye_plant_shadow2_2.png")}
    };
    
    // Enemy variables
    Enemy vampire{Vector2{},
                  LoadTexture("characters/Enemies/enemies-vampire_idle.png"),
                  LoadTexture("characters/Enemies/enemies-vampire_movement.png")
    };
    
    // Set enemy target
    vampire.SetTarget(&gordon);

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
        for(auto prop : props){
            prop.Render(gordon.GetWorldPos());
        }

        // Character update
        gordon.Tick(GetFrameTime());

        // Check map bounds
        if (gordon.GetWorldPos().x < 0.0f ||
            gordon.GetWorldPos().y < 0.0f ||
            gordon.GetWorldPos().x + kWindowWidth > worldMap.width * mapScale ||
            gordon.GetWorldPos().y + kWindowHeight > worldMap.height * mapScale)
        {
            gordon.UndoMovement();
            DrawText("Hit the bounds!", 10, 10, 20, RED); // debug
        }

        // Get the character's collision rectangle once per frame
        Rectangle gordonCollisionRec = gordon.GetCollisionRec();

        // Check for prop collision
        for (auto prop : props){
            Rectangle propCollisionRec = prop.GetCollisionRec(gordon.GetWorldPos());
            if (CheckCollisionRecs(propCollisionRec, gordonCollisionRec)){
                gordon.UndoMovement();
                DrawText("Collision Detected!", 10, 10, 20, RED); // debug
            }
            // Draw the prop's collision box for debugging
            DrawRectangleLines(propCollisionRec.x, propCollisionRec.y, propCollisionRec.width, propCollisionRec.height, RED);
        }

        // Draw the character's collision box for debugging
        DrawRectangleLines(gordonCollisionRec.x, gordonCollisionRec.y, gordonCollisionRec.width, gordonCollisionRec.height, BLUE);

        // Enemy update
        vampire.Tick(GetFrameTime());

        // Get the character's collision rectangle once per frame
        Rectangle enemyCollisionRec = vampire.GetCollisionRec();
        
        // Draw enemy's collision box for debugging
        DrawRectangleLines(enemyCollisionRec.x, enemyCollisionRec.y, enemyCollisionRec.width, enemyCollisionRec.height, YELLOW);

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
