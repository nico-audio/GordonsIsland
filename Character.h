/*
 * File:        [Character.h]
 * Description: Defines the Character class, which manages the player character's
 *              position, movement, animation, and rendering.
 * Author:      [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[21/08/2025, Derive from BaseCharacter class]
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
 *  - Call UndoMovement() to limit the player character's movement to boundaries or when colliding.
 *  
 */

 #ifndef CHARACTER_H
 #define CHARACTER_H
 #include "raylib.h"
 #include "BaseCharacter.h"

// Character - Handles player character movement, animation and rendering
class Character : public BaseCharacter {
public:
    Character(int winWidth, int winHeight);
    virtual void Tick(float deltaTime) override;
private:
    int maxFrames{12};
    float sheetHeight{4.0f};
};

#endif
