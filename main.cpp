/*
 * File:        [main.cpp]
 * Description: [The main entry point - initializes the game window, loads assets,
 *              and runs the main game loop.] 
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[21/09/2025, Implement game state management, add main menu and game over screen]
 * Version:     [0.0.2]
 *
 * Notes:
 *  - CheckMapBounds: Handles boundary checking to keep the player within the map limits.
 *  - Implements collision detection between the player and static props.
 *  - Handles enemy death
 *  - Handles game state management
 *  - Implements main menu and game over screen
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

void CheckMapBounds(PlayerCharacter& character, const Texture2D& worldMap, 
                    float mapScale, int windowWidth, int windowHeight){
    const float mapWidth = worldMap.width * mapScale;
    const float mapHeight = worldMap.height * mapScale;
    const Vector2 worldPos = character.GetWorldPos();

    if (worldPos.x < 0.0f ||
        worldPos.y < 0.0f ||
        worldPos.x + windowWidth > mapWidth ||
        worldPos.y + windowHeight > mapHeight)
    {
        character.UndoMovement();
        // DrawText("Hit the bounds!", 10, 10, 20, RED); //debug
    }
}

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

    // Game state management
    enum GameState {
        MainMenu,
        Gameplay,
        GameOver
    };
    
    GameState currentState = MainMenu;

    // UI Button rectangles
    Rectangle startButtonRec{ kWindowWidth / 2.f - 100.f, kWindowHeight / 2.f - 25.f, 200.f, 50.f };
    Rectangle exitButtonRec{ kWindowWidth / 2.f - 100.f, kWindowHeight / 2.f + 45.f, 200.f, 50.f };
    Rectangle restartButtonRec = startButtonRec; // Reuse for game over screen
    

    bool exitWindow = false;

    SetTargetFPS(60);

    // Keep window open and clear background
    while (!WindowShouldClose() && !exitWindow){

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);


        switch (currentState){
            case MainMenu:
            {
                DrawText("Gordon's Island", kWindowWidth / 2 - MeasureText("Gordon's Island", 40) / 2, kWindowHeight / 2 - 100, 40, RED);
                
                DrawRectangleRec(startButtonRec, LIGHTGRAY);
                DrawText("Start Game", startButtonRec.x + 40, startButtonRec.y + 15, 20, DARKGRAY);

                DrawRectangleRec(exitButtonRec, LIGHTGRAY);
                DrawText("Exit Game", exitButtonRec.x + 50, exitButtonRec.y + 15, 20, DARKGRAY);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(GetMousePosition(), startButtonRec)) {
                        
                        // Reset characters and set targets before starting
                        gordon.Reset();
                        for (auto enemy : enemies) {
                            enemy->Reset();
                            enemy->SetTarget(&gordon);
                        }
                        currentState = Gameplay;
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), exitButtonRec)) {
                        exitWindow = true;
                    }
                }
            }
            break;

            case Gameplay:
            {
                worldMapPos = Vector2Scale(gordon.GetWorldPos(), -1.0f);
                DrawTextureEx(worldMap, worldMapPos, 0.0, mapScale, WHITE);

                // Render props
                for(auto prop : props){
                    prop.Render(gordon.GetWorldPos());
                }

                // Show player character's health
                std::string gordonsHealth = "Health: ";
                gordonsHealth.append(std::to_string(gordon.GetPlayerHealth()), 0, 3);
                DrawText(gordonsHealth.c_str(), 20, 40, 30, YELLOW);

                // Character update
                gordon.Tick(GetFrameTime());

                // Check map bounds
                CheckMapBounds(gordon, worldMap, mapScale, kWindowWidth, kWindowHeight);

                // Check for prop collision
                for (auto prop : props){
                    if (CheckCollisionRecs(prop.GetCollisionRec(gordon.GetWorldPos()), gordon.GetCollisionRec())){
                        gordon.UndoMovement();
                        // DrawText("Collision Detected!", 10, 10, 20, RED); // debug
                    }
                }

                // Enemy update
                for (auto enemy : enemies){
                    enemy->Tick(GetFrameTime());
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    // DrawText("Attack!", 10, 10, 20, YELLOW); // debug
                    for (auto enemy : enemies){
                        // Kill enemy
                        if (CheckCollisionRecs(enemy->GetCollisionRec(), gordon.GetWeaponCollisionRec())){
                            enemy->SetAlive(false);
                        }
                    }
                }

                if (!gordon.GetAlive()) {
                    currentState = GameOver;
                }
            }
            break;

            case GameOver:
            {
                DrawText("Game Over", kWindowWidth / 2 - MeasureText("Game Over", 50) / 2, kWindowHeight / 2 - 100, 50, RED);

                DrawRectangleRec(restartButtonRec, LIGHTGRAY);
                DrawText("Restart", restartButtonRec.x + 60, restartButtonRec.y + 15, 20, DARKGRAY);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(GetMousePosition(), restartButtonRec)) {
                        
                        // Reset all characters and set targets
                        gordon.Reset();
                        
                        for (auto enemy : enemies) {
                            enemy->Reset();
                            enemy->SetTarget(&gordon);
                        }
                        
                        currentState = Gameplay;
                    }
                }
            }
            break;
        }
        
        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
