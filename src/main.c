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

    unsigned int frame_count = 0;

    bool show_menu_instructions = true;

    Scene current_scene = Scene_Menu;

    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ++frame_count;

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

            if (frame_count % 30 == 0)
            {
                show_menu_instructions = !show_menu_instructions;
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
            const char *title = "Snake";
            const int t_size = 40;
            const int t_w = MeasureText(title, t_size);

            DrawText(title, (screen_width - t_w) / 2, screen_height / 4, t_size,
                     WHITE);

            if (show_menu_instructions)
            {
                const char *instructions = "Press 'space' to Play";
                const int i_size = 30;
                const int i_w = MeasureText(instructions, i_size);

                DrawText(instructions, (screen_width - i_w) / 2,
                         screen_height / 2, i_size, WHITE);
            }

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
