/*
 * File:        [PlayerCharacter.h]
 * Description: Defines the Character class, which manages the player character's
 *              position, movement, animation, and rendering.
 * Author:      [Nico V.]
 * Created on:  [18/08/2025]
 * Last updated:[14/09/2025, update asset file path]
 * Version:     [0.0.2]
 *
 * Notes:
 *  - This class is responsible for handling player input for movement.
 *
 * Usage:
 *  - Create an instance of Character in main
 *  - Call Tick() every frame to draw, update character and handle input
 *  - Call GetScreenPos() to get the character's world position
 *  - Call TakeDamage() when the character is hit.
 *  - Call GetPlayerHealth() to check health status.
 *  
 */

 #ifndef PLAYER_CHARACTER_H
 #define PLAYER_CHARACTER_H
 #include "raylib.h"
 #include "Character.h"

// Character - Handles player character movement, animation and rendering
class PlayerCharacter : public Character {
public:
    PlayerCharacter(int winWidth, int winHeight);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 GetScreenPos() override;
    Rectangle GetWeaponCollisionRec() { return weaponCollisionRec; }
    float GetPlayerHealth() const { return health; }
    void TakeDamage(float damage);
    virtual void Reset() override;
private:
    // Animaiton variables
    int maxFrames{12};
    float sheetHeight{4.0f};
    
    // Window dimensions
    int windowWidth{};
    int windowHeight{};

    // Weapon variables
    Texture2D weapon{LoadTexture("Assets/weapons/weapon_sword.png")};
    Rectangle weaponCollisionRec{};

    // Character stats
    float health{100.0f};
};

#endif
