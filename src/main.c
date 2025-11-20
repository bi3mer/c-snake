#include "assert.h"
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

typedef struct
{
    int x, y;
} Point;

static inline Point point_plus_direction(Point p, Grid_Type t)
{
    Point new_p = p;

    switch (t)
    {
    case Grid_North:
        --new_p.y;
        break;
    case Grid_East:
        ++new_p.x;
        break;
    case Grid_South:
        ++new_p.y;
        break;
    case Grid_West:
        --new_p.x;
        break;
    case Grid_Empty:
    case Grid_Food:
    default:
        assert(false);
    }

    return new_p;
}

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    const int start_d = (int)(screen_width * 0.1f);
    const int play_d = (int)(screen_width * 0.8f);
    const int grid_d = play_d / D;

    unsigned int frame_count = 0;

    Point snake_head;
    Point snake_tail;
    int snake_size;
    Grid_Type snake_direction;
    Grid_Type grid[D][D] = {0};

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

                snake_head.x = D / 2;
                snake_head.y = D / 2;
                snake_tail = snake_head;
                snake_direction = Grid_North;

                grid[snake_head.y][snake_head.x] = snake_direction;
                grid[6][1] = Grid_Food;

                frame_count = 1;
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

            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) &&
                snake_direction != Grid_South)
            {
                snake_direction = Grid_North;
            }

            if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) &&
                snake_direction != Grid_West)
            {
                snake_direction = Grid_East;
            }

            if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) &&
                snake_direction != Grid_North)
            {
                snake_direction = Grid_South;
            }

            if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) &&
                snake_direction != Grid_East)
            {
                snake_direction = Grid_West;
            }

            if (frame_count % 30 == 0)
            {
                grid[snake_head.y][snake_head.x] = snake_direction;
                snake_head = point_plus_direction(snake_head, snake_direction);
                grid[snake_head.y][snake_head.x] = snake_direction;

                Grid_Type temp_dir = grid[snake_tail.y][snake_tail.x];
                grid[snake_tail.y][snake_tail.x] = Grid_Empty;
                snake_tail = point_plus_direction(snake_tail, temp_dir);
            }

            break;
        }
        default:
            assert(false);
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
            assert(false);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
