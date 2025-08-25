/*
 * File:        [Enemy.h]
 * Description: [Defines the Enemy class]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[25/08/2025, Screen position getter]
 * Version:     [0.0.1]
 *
 * Notes:
 * - This class manages sprite sheet animation for idle and run states.
 *
 * Usage:
 * - Create an instance of Enemy in main
 * - Call Tick() every frame to draw and update enemy
 * - Call SetTarget() to define the enemy's target
 *  
 */


 #include "raylib.h"
 #include "BaseCharacter.h"
 #include "Character.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    virtual void Tick(float deltaTime) override;
    void SetTarget(Character* character){ target = character; };
    virtual Vector2 GetScreenPos() override;
private:
    Character* target;
    int maxFrames{6};
};