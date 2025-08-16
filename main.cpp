/*
 * File:        [main.cpp]
 * Description: [Top down 2D game]
 * Author:      [Nico V.]
 * Created on:  [11/08/2025]
 * Last updated:[16/08/2025, Create character class, add tick function]
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

// Character - Handles player character movement, animation and rendering
class Character {
public:
    Vector2 GetWorldPos() { return worldPos; }
    void SetScreenPos(int winWidth, int winHeight);
    void Tick(float deltaTime);

private:
    // Character textures
    Texture2D texture{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D idle{LoadTexture("characters/Gordon/Unarmed_Idle/Unarmed_Idle_full.png")};
    Texture2D run{LoadTexture("characters/Gordon/Unarmed_Run/Unarmed_Run_full.png")};
    
    // Position vectors
    Vector2 screenPos;
    Vector2 worldPos;

    // Direction - 1: facing right, -1: facing left
    float rightLeft{1.0f};

    // Animation variables
    float runningTime{}; 
    int frame{}; // current animation frame
    const int kMaxFrames{12};
    const float kUpdateTime{1.0f / 12.0f};
    const float kSpeed{4.0f};
    float animFrames{12.0f}; // Total frames in the current animation spritesheet
};

// Gets WASD player input and returns a normalized direction vector
Vector2 getInputDirection(){
    Vector2 direction{};

    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    return direction;
}

void Character::SetScreenPos(int winWidth, int winHeight){
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 12.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height / 4.0f)};
}


// Tick - Character update
void Character::Tick(float deltaTime){
    getInputDirection();
    // Movement
    Vector2 direction = getInputDirection();
    if (Vector2Length(direction) != 0.0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), kSpeed));
        rightLeft = ((direction.x < 0.f) ? -1.0f : 1.0f);
        texture = run;
        animFrames = 8.0f;
    }
    else {
        texture = idle;
        animFrames = 12.0f;
    }

    // Update running time
    runningTime += deltaTime;

    // Update animation frame
    if (runningTime >= kUpdateTime){
        runningTime = 0.0;
        frame++;
        if (frame > kMaxFrames)
        frame = 0;
    }
    // Draw character
    Rectangle source{frame * (float)texture.width / animFrames, 0.0f, (float)texture.width / animFrames, (float)texture.height / 4.0f};
    Rectangle destRec{screenPos.x, screenPos.y, 4.0f * (float)texture.width / animFrames, 4.0f * (float)texture.height / 4.0f};
    
    // Select different row from spritesheet
    source.y = ((rightLeft == 1.0f) ? 2.0f * source.height : 1.0f * source.height);
    DrawTexturePro(texture, source, destRec, Vector2{}, 0.0f, WHITE);
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

    SetTargetFPS(60);

    // Keep window open and clear background
    while (!WindowShouldClose()){

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw world map
        DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

        // Stop drawing
        EndDrawing();
    }

    UnloadTexture(worldMap);
    CloseWindow();
}
