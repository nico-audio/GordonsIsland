/*
 * File:        [Enemy.h]
 * Description: [Defines the Enemy class]
 * Author:      [Nico V.]
 * Created on:  [21/08/2025]
 * Last updated:[21/08/2025, Inherit from BaseCharacter]
 * Version:     [0.0.1]
 *
 * Notes:
 * - This class manages sprite sheet animation for idle and run states.
 *
 * Usage:
 * - Create an instance of Enemy in main
 * - Call Tick() every frame to draw, update enemy and handle input
 * - Call UndoMovement() to limit the enemy's movement
 *  
 */

 #include "raylib.h"
 #include "BaseCharacter.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    virtual void Tick(float deltaTime) override;
private:
    int maxFrames{6};
};