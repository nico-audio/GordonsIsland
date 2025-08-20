/*
 * File:        [Prop.h]
 * Description: [Defines the Prop class, which represents an object in the game world.]
 * Author:      [Nico V.]
 * Created on:  [19/08/2025]
 * Last updated:[20/08/2025, Render function]
 * Version:     [0.0.1]
 *
 * Notes:
 * 
 *
 * Usage:
 * - Instantiate a Prop object in your main game file.
 * - Call Render() on tick, passing the player's world position
 *    to draw the prop relative to the camera/player.
 *  
 */

 #include "raylib.h"

 class Prop{
    public:
        Prop(Vector2 pos, Texture2D tex);
        void Render(Vector2 gordonPos);
    private:
        Texture2D texture{};
        Vector2 worldPos{};
        float scale{4.0f};
 };