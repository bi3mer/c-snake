#include "raylib.h"

typedef enum
{
    Scene_Menu = 0,
    Scene_Game
} Scene;

typedef enum
{
    Grid_Empty = 0,
    Grid_Food,
    Grid_North,
    Grid_East,
    Grid_South,
    Grid_West,
} Grid_Type;

#define D 10

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    const int start_d = (int)(screen_width * 0.1f);
    const int play_d = (int)(screen_width * 0.8f);
    const int grid_d = play_d / D;

    unsigned int frame_count = 0;

    int snake_size = 1;
    Grid_Type grid[D][D] = {0};
    grid[1][6] = Grid_North;
    grid[6][1] = Grid_Food;

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
            for (int y_i = 0; y_i < D; ++y_i)
            {
                const int y_r = start_d + (y_i * grid_d);

                for (int x_i = 0; x_i < D; ++x_i)
                {
                    const int x_r = start_d + (x_i * grid_d);

                    switch (grid[y_i][x_i])
                    {
                    case Grid_Food:
                        DrawRectangle(x_r, y_r, grid_d - 1, grid_d - 1, GREEN);
                        break;
                    case Grid_North:
                    case Grid_East:
                    case Grid_South:
                    case Grid_West:
                    {
                        DrawRectangle(x_r, y_r, grid_d - 1, grid_d - 1, RED);
                        break;
                    }
                    case Grid_Empty:
                    default:
                        DrawRectangle(x_r, y_r, grid_d - 1, grid_d - 1, BLUE);
                        break;
                    }
                }
            }
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
