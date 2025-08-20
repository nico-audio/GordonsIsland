/*
 * File:    [Prop.cpp]
 * Description: [Implements the methods for the Prop class.]
 * Author:  [Nico V.]
 * Created on:  [19/08/2025]
 * Last updated:[20/08/2025, Render function]
 * Version:     [0.0.1]
 * Notes:
 *  - Instantiated and used by main.cpp.
 *  - Depends on raylib.h for drawing functions (DrawTextureEx).
 *  - Depends on raymath.h for vector operations (Vector2Subtract). 
 *  
 */

 #include "Prop.h"
 #include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : texture(tex),
                                         worldPos(pos)
{
   // constructor body
}

 void Prop::Render(Vector2 gordonPos){
   Vector2 screenPos{Vector2Subtract(worldPos, gordonPos)};
   DrawTextureEx(texture, screenPos, 0.0, scale, WHITE);
 }
