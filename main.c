#include <math.h>
#include <raylib.h>

const int WIDTH = 1000;
const int HEIGHT = 600;

int worldMap[24][24] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct Dir {
    float x, y;
} Dir;

typedef struct Player {
    Vector2 pos;
    Dir dir;
    Vector2 plane;
} Player;

void raycasting(Player *player) {

    float rayDirX, rayDirY;
    float windowX;
    for (int x = 0; x < WIDTH; x += 1) {
        windowX = 2 * x / (float)WIDTH - 1;
        rayDirX = player->dir.x + player->plane.x * windowX;
        rayDirY = player->dir.y + player->plane.y * windowX;

        // DDA setup
        int mapX = (int)player->pos.x;
        int mapY = (int)player->pos.y;

        float deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1 / rayDirY);

        float sideDistX, sideDistY;
        float stepX, stepY;
        float perpWallDist;

        // was there a wall hit?
        int hit = 0;

        // was hits on side-x (0) or side-y (1)?
        int side;

        if (rayDirX < 0) {
            sideDistX = (player->pos.x - mapX) * deltaDistX;
            stepX = -1;
        } else {
            sideDistX = (mapX + 1 - player->pos.x) * deltaDistX;
            stepX = 1;
        }

        if (rayDirY < 0) {
            sideDistY = (player->pos.y - mapY) * deltaDistY;
            stepY = -1;
        } else {
            sideDistY = (mapY + 1 - player->pos.y) * deltaDistY;
            stepY = 1;
        }

        // is wall hit?
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (worldMap[mapX][mapY] > 0) {
                hit = 1;
            }
        }

        // fisheye effect prevention
        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
        } else {
            perpWallDist = (sideDistY - deltaDistY);
        }

        int lineHeight = (int)HEIGHT / perpWallDist;

        // line starting and ending points
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }

        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) {
            drawEnd = HEIGHT - 1;
        }

        // wall color
        Color color;
        switch (worldMap[mapX][mapY]) {
        case 1:
            color = MAROON;
            break;
        case 2:
            color = GREEN;
            break;
        case 3:
            color = SKYBLUE;
            break;
        case 4:
            color = PURPLE;
            break;
        case 5:
            color = DARKBROWN;
            break;
        }

        if (side == 1) {

            color.r *= 0.80;
            color.g *= 0.80;
            color.b *= 0.80;
        }

        // drawing lines based on start and end points
        DrawLine(x, drawStart, x, drawEnd, color);
    }
}

Vector2 rotate_2d(float x, float y, float angle) {

    angle = angle * DEG2RAD;
    float cos_theta = cos(angle);
    float sin_theta = sin(angle);

    float x_new = x * cos_theta - y * sin_theta;
    float y_new = x * sin_theta + y * cos_theta;

    return (Vector2){x_new, y_new};
}

void player_movement(Player *player, float dt) {
    float moveSpeed = 5 * dt;
    float rotationSpeed = 90 * dt;

    // move forward if no wall in front of you
    if (IsKeyDown(KEY_W)) {
        if (worldMap[(int)(player->pos.x + player->dir.x * moveSpeed)]
                    [(int)(player->pos.y)] == false)
            player->pos.x += player->dir.x * moveSpeed;
        if (worldMap[(int)(player->pos.x)]
                    [(int)(player->pos.y + player->dir.y * moveSpeed)] == false)
            player->pos.y += player->dir.y * moveSpeed;
    }
    // move backwards if no wall behind you
    if (IsKeyDown(KEY_S)) {
        if (worldMap[(int)(player->pos.x - player->dir.x * moveSpeed)]
                    [(int)(player->pos.y)] == false)
            player->pos.x -= player->dir.x * moveSpeed;
        if (worldMap[(int)(player->pos.x)]
                    [(int)(player->pos.y - player->dir.y * moveSpeed)] == false)
            player->pos.y -= player->dir.y * moveSpeed;
    }

    if (IsKeyDown(KEY_D)) { // right side

        Vector2 direction =
            rotate_2d(player->dir.x, player->dir.y, -rotationSpeed);
        player->dir.x = direction.x;
        player->dir.y = direction.y;

        Vector2 planes =
            rotate_2d(player->plane.x, player->plane.y, -rotationSpeed);
        player->plane.x = planes.x;
        player->plane.y = planes.y;
    }

    if (IsKeyDown(KEY_A)) { // left side

        Vector2 direction =
            rotate_2d(player->dir.x, player->dir.y, rotationSpeed);
        player->dir.x = direction.x;
        player->dir.y = direction.y;

        Vector2 planes =
            rotate_2d(player->plane.x, player->plane.y, rotationSpeed);
        player->plane.x = planes.x;
        player->plane.y = planes.y;
    }
}

int main() {

    InitWindow(WIDTH, HEIGHT, "Raycasting");
    SetTargetFPS(60);

    Player player;
    player.pos.x = 8;
    player.pos.y = 2;

    player.dir.x = -1; // looking at left direction
    player.dir.y = 0;

    player.plane.x = 0;
    player.plane.y = 0.66;

    float dt;

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawFPS(5, 5);

        dt = GetFrameTime();

        raycasting(&player);
        player_movement(&player, dt);

        ClearBackground(BLACK);
        EndDrawing();
    }
}
