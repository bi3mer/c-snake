#include "raylib.h"

typedef enum
{
    Scene_Menu = 0,
    Scene_Game
} Scene;

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    Scene current_scene = Scene_Menu;

    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        ///////////////////////////////////////////////////////////////////////
        /// Update the Game
        switch (current_scene)
        {
        case Scene_Menu:
        {
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
            {
                current_scene = Scene_Game;
            }
            break;
        }
        case Scene_Game:
        {
            if (IsKeyPressed(KEY_Q))
            {
                current_scene = Scene_Menu;
            }

            break;
        }
        default:
            break;
        }

        ///////////////////////////////////////////////////////////////////////
        /// Render the Game
        BeginDrawing();
        ClearBackground(BLACK);

        switch (current_scene)
        {
        case Scene_Menu:
        {
            DrawText("Menu Scene", 450, 450, 40, WHITE);
            break;
        }
        case Scene_Game:
        {
            DrawText("Game Scene", 450, 450, 40, WHITE);
            break;
        }
        default:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
