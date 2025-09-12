/*
 * File:        [Enemy.h]
 * Description: [Defines the Enemy class]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[12/09/2025, update dependencies]
 * Version:     [0.0.2]
 *
 * Notes:
 * - This class manages sprite sheet animation for idle and run states.
 *
 * Usage:
 * - Create an instance of Enemy in main
 * - Call Tick() every frame to draw and update enemy
 * - Call SetTarget() to define the enemy's target
 * - Define enemy damage value
 *  
 */


 #include "raylib.h"
 #include "Character.h"
 #include "PlayerCharacter.h"

class Enemy : public Character {
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    virtual void Tick(float deltaTime) override;
    void SetTarget(PlayerCharacter* character){ target = character; };
    virtual Vector2 GetScreenPos() override;
    virtual Rectangle GetCollisionRec() override;
    virtual void Reset() override;
private:
    PlayerCharacter* target;
    Vector2 initialPos{};
    int maxFrames{6};
    float damagePerSec{10.0f};
    float chaseRadius{25.0f};
};