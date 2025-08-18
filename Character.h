/*
 * File:        [Character.h]
 * Description: Defines the Character class, which manages the player character's
 *              position, movement, animation, and rendering.
 * Author:      [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[18/08/2025, setup header file ]
 * Version:     [0.0.1]
 *
 * Notes:
 *  - This class is responsible for handling player input for movement.
 *  - It manages sprite sheet animation for idle and run states.
 *
 * Usage:
 *  - Create an instance of Character in main
 *  - Call SetScreenPos() once to initialize its screen position.
 *  - Call Tick() every frame to draw, update character and handle input
 *  
 */

#include "raylib.h"

// Character - Handles player character movement, animation and rendering
class Character {
public:
    Character();
    Vector2 GetWorldPos() { return worldPos; }
    void SetScreenPos(int winWidth, int winHeight);
    void Tick(float deltaTime);

private:
    // Character textures
    Texture2D texture{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D idle{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D run{LoadTexture("characters/Gordon/Unarmed_Run/Unarmed_Run_full.png")};
    
    // Position vectors
    Vector2 screenPos{};
    Vector2 worldPos{};

    // Direction - 1: facing right, -1: facing left
    float rightLeft{1.0f};

    // Animation variables
    float runningTime{}; 
    int frame{}; // current animation frame
    int maxFrames{12};
    const float kUpdateTime{1.0f / 12.0f};
    const float kSpeed{4.0f};
    float sheetHeight{4.0f};
    //float animFrames{12.0f}; // Total frames in the current animation spritesheet

    // Sprite dimensions
    float width{};
    float height{}; 
};