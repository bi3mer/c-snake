#include "raylib.h"

typedef enum
{
    Scene_Menu = 0,
    Scene_Game,
    Scene_Error
} Scene;

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    unsigned int frame_counter = 0;
    Scene scene = Scene_Menu;

    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ///////////////////////////////////////////////////////////////////////
        // Game Logic
        ++frame_counter;

        switch (scene)
        {
        case Scene_Menu:
        {
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
            {
                scene = Scene_Game;
            }

            break;
        }
        case Scene_Game:
        {
            if (IsKeyPressed(KEY_Q))
            {
                scene = Scene_Menu;
            }

            break;
        }
        case Scene_Error:
        default:
            break;
        }

        ///////////////////////////////////////////////////////////////////////
        // Render Logic
        BeginDrawing();
        ClearBackground(BLACK);

        switch (scene)
        {
        case Scene_Menu:
        {
            const char *title = "Snake";
            const int title_font_size = 50;
            const int title_width = MeasureText(title, title_font_size);

            DrawText(title, (screen_width - title_width) / 2, screen_height / 4,
                     title_font_size, WHITE);

            if ((frame_counter / 30) % 2)
            {
                const char *instructions = "Press 'space' to Play!";
                const int i_font_size = 30;
                const int i_width = MeasureText(instructions, i_font_size);

                DrawText(instructions, (screen_width - i_width) / 2,
                         screen_height / 2, i_font_size, WHITE);
            }
            break;
        }
        case Scene_Game:
        {
            DrawText("GAME", 190, 200, 20, WHITE);
            break;
        }
        case Scene_Error:
        default:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
