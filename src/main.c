#include "raylib.h"
#include <stddef.h>

typedef enum
{
    Scene_Menu = 0,
    Scene_Game,
    Scene_Error
} Scene;

typedef enum
{
    Grid_Type_Empty = 0,
    Grid_Type_Food,
    Grid_Type_North,
    Grid_Type_East,
    Grid_Type_South,
    Grid_Type_West,
    Grid_Type_Error,
} Grid_Type;

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    unsigned int frame_counter = 0;
    Scene scene = Scene_Menu;

    size_t snake_size;
    const size_t grid_dimension = 16;
    Grid_Type grid[grid_dimension * grid_dimension];

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

                snake_size = 0;
                for (size_t i = 0; i < grid_dimension * grid_dimension; ++i)
                {
                    grid[i] = Grid_Type_Empty;
                }

                grid[10] = Grid_Type_East;
                grid[20] = Grid_Type_Food;
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
            const int game_space = (int)(0.8f * screen_width);
            const int start = (int)(0.1f * screen_width);
            const int dimension = game_space / grid_dimension;

            for (int y = 0; y < grid_dimension; ++y)
            {
                const int col = y * (int)grid_dimension;
                for (int x = 0; x < (int)grid_dimension; ++x)
                {
                    const int render_pos = start + (x * dimension);
                    switch (grid[col + x])
                    {
                    case Grid_Type_Empty:
                        break;
                    case Grid_Type_Food:
                        DrawRectangle(render_pos, render_pos, dimension - 1,
                                      dimension - 1, GREEN);
                        break;
                    case Grid_Type_North:
                    case Grid_Type_East:
                    case Grid_Type_South:
                    case Grid_Type_West:
                        DrawRectangle(render_pos, render_pos, dimension - 1,
                                      dimension - 1, RED);
                        break;
                    case Grid_Type_Error:
                    default:
                        break;
                    }
                }
            }

            DrawRectangleLines(start, start, game_space, game_space, WHITE);
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
