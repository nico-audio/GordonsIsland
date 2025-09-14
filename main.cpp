/*
 * File:        [main.cpp]
 * Description: [The main entry point - initializes the game window, loads assets,
 *              and runs the main game loop.] 
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[14/09/2025, Update asset file path]
 * Version:     [0.0.1]
 *
 * Notes:
 *  - Handles boundary checking to keep the player within the map limits.
 *  - Implements collision detection between the player and static props.
 *  - Handles enemy death
 *
 * Usage:
 * [Controls]
 * - Use WASD keys to move the character
 * - Use the left mouse button to attack
 */

#include "raylib.h"
#include "raymath.h"
#include "PlayerCharacter.h"
#include "Scene/Prop.h"
#include "Enemy.h"
#include <string>

int main(){

    // Window dimensions
    const int kWindowWidth{384};
    const int kWindowHeight{384};

    // Draw window
    InitWindow(kWindowWidth, kWindowHeight, "Top down 2D game");

    // Load world map texture
    Texture2D worldMap = LoadTexture("Assets/environment/nature_tileset/WorldMap3.png");

    // Map position
    Vector2 worldMapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // Character variables
    PlayerCharacter gordon{kWindowWidth, kWindowHeight};
    
    // Objects
    Prop props[2]{
        Prop{Vector2{600.0f, 600.0f}, LoadTexture("Assets/environment/objects/Fetus_shadow1_2.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("Assets/environment//Eye_plant_shadow2_2.png")}
    };

    
    // Enemy variables
    Enemy vampire{Vector2{800.0f, 300.0f},
        LoadTexture("Assets/characters/Enemies/Vampire/enemies-vampire_idle.png"),
        LoadTexture("Assets/characters/Enemies/Vampire/enemies-vampire_movement.png")
    };

    Enemy skeleton{Vector2{800.0f, 700.0f},
        LoadTexture("Assets/characters/Enemies/Skeleton/enemies-skeleton1_idle.png"),
        LoadTexture("Assets/characters/Enemies/Skeleton/enemies-skeleton1_movement.png")
    };

    Enemy* enemies[]{
        &vampire,
        &skeleton
    };

    // Set enemy target
    for (auto enemy : enemies){
        enemy -> SetTarget(&gordon);
    }

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

        // Display health and game over text
        if (!gordon.GetAlive()){
            DrawText("Game Over", 55, 60, 50, RED); // Player character is dead
            EndDrawing();
            continue;
        }
        else{
            std::string gordonsHealth = "Health: ";
            gordonsHealth.append(std::to_string(gordon.GetPlayerHealth()), 0, 3);
            DrawText(gordonsHealth.c_str(), 20, 40, 30, YELLOW);
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
            //DrawText("Hit the bounds!", 10, 10, 20, RED); // debug
        }

        // Get the character's collision rectangle once per frame
        Rectangle gordonCollisionRec = gordon.GetCollisionRec();

        // Check for prop collision
        for (auto prop : props){
            Rectangle propCollisionRec = prop.GetCollisionRec(gordon.GetWorldPos());
            if (CheckCollisionRecs(propCollisionRec, gordonCollisionRec)){
                gordon.UndoMovement();
                //DrawText("Collision Detected!", 10, 10, 20, RED); // debug
            }
            // Draw the prop's collision box for debugging
            //DrawRectangleLines(propCollisionRec.x, propCollisionRec.y, propCollisionRec.width, propCollisionRec.height, RED);
        }

        // Draw the character's collision box for debugging
        //DrawRectangleLines(gordonCollisionRec.x, gordonCollisionRec.y, gordonCollisionRec.width, gordonCollisionRec.height, BLUE);

        // Enemy update
        for (auto enemy : enemies){
            enemy -> Tick(GetFrameTime());
        }

        // Get the enemy's collision rectangle
        Rectangle enemyCollisionRec = vampire.GetCollisionRec();

        // Dislocate the collision rectangle on the Y-axis
        float y_offset = 15.0f; // Adjust this value to move the enemy collider box down
        enemyCollisionRec.y += y_offset;
        
        // Draw enemy's collision box for debugging
        //DrawRectangleLines(enemyCollisionRec.x, enemyCollisionRec.y, enemyCollisionRec.width, enemyCollisionRec.height, YELLOW);

        // Kill enemy
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            //DrawText("Attack!", 10, 10, 20, YELLOW); // debug

            for (auto enemy : enemies){
                if (CheckCollisionRecs(enemy -> GetCollisionRec(), gordon.GetWeaponCollisionRec())){
                    enemy -> SetAlive(false);
                }
            }
        }
        
        /*
        // Collision debug
        DrawText(TextFormat("Enemy: x=%.1f y=%.1f", enemyCollisionRec.x, enemyCollisionRec.y), 10, 40, 20, YELLOW);
        DrawText(TextFormat("Weapon: x=%.1f y=%.1f", gordon.GetWeaponCollisionRec().x, gordon.GetWeaponCollisionRec().y), 10, 60, 20, RED);
 
        bool collided = CheckCollisionRecs(enemyCollisionRec, gordon.GetWeaponCollisionRec());
        DrawText(collided ? "COLLIDED" : "NO COLLISION", 10, 80, 20, collided ? GREEN : GRAY);
        */
        
        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
