/*
 * File:        [Character.h]
 * Description: Defines the Character class, which manages the player character's
 *              position, movement, animation, and rendering.
 * Author:      [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[25/08/2025, Screen pos getter override, window dimension variables]
 * Version:     [0.0.1]
 *
 * Notes:
 *  - This class is responsible for handling player input for movement.
 *
 * Usage:
 *  - Create an instance of Character in main
 *  - Call Tick() every frame to draw, update character and handle input
 *  - Call GetScreenPos() to get the character's world position
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
    virtual Vector2 GetScreenPos() override;
private:
    // Animaiton variables
    int maxFrames{12};
    float sheetHeight{4.0f};
    
    // Window dimensions
    int windowWidth{};
    int windowHeight{};
};

#endif
