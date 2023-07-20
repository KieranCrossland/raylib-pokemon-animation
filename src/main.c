#include "raylib.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 450
typedef int spriteframe_t; // holds the calculation needed to render a specific frame of a sprite sheet. eg frame 5 = (player_frame_width * 4)

enum GameScene {
    TITLE,
    GAMEPLAY,    

};
typedef enum  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} CharacterDirection;

typedef enum  {
    IDLE,
    WALKING,
    RUNNING,
} CharacterState;

typedef struct {
    Vector2 pos;
    float walk_speed;
    float run_speed;
    int fcounter;
} Character;


void draw_player(Texture player_sheet, Character player, spriteframe_t direction) { //direction codes that i assigned later on.
    DrawTextureRec(player_sheet, (Rectangle){direction, 192, 186, 192}, (Vector2){player.pos.x, player.pos.y}, RAYWHITE); 
}

int main(void) {

    Character player = {
        40,
        40,
        2,
        4,
        0,


    };
    CharacterDirection player_direction = DOWN;    
    CharacterState player_state = IDLE;
    
    InitWindow(WIDTH, HEIGHT, "game");
    SetTargetFPS(60);

    Texture2D player_sheet = LoadTexture("res/sprites/characters/player/player.png");
    
    float player_frame_width = (float)(player_sheet.width / 24); /*This is the width of a single frame in the spritesheet.
    when drawn this starts at frame 1 since it uses the width of the first frame for reference.
    To draw a different frame we multiply by its sprite number minus 1.
    for example: to draw frame 4 =  player_frame_width * 3
    for example: to draw frame 1 =  player_frame_width - player_frame_width 
    for convenience there is a defined sprite_code_t type*/
    
    //idle
    spriteframe_t up_idle = player_frame_width * 9;
    spriteframe_t down_idle = player_frame_width * 3;
    spriteframe_t left_idle = player_frame_width - player_frame_width;
    spriteframe_t right_idle =  player_frame_width * 6;
    //walk
    spriteframe_t up_walk1 = player_frame_width * 10;
    spriteframe_t up_walk2 = player_frame_width * 11;
    spriteframe_t down_walk1 = player_frame_width * 4;
    spriteframe_t down_walk2 = player_frame_width * 5;
    spriteframe_t left_walk1 = player_frame_width;
    spriteframe_t left_walk2 = player_frame_width * 2;
    spriteframe_t right_walk1 = player_frame_width * 7;
    spriteframe_t right_walk2 = player_frame_width * 8;
    //run
    spriteframe_t up_run1 = player_frame_width * 22;
    spriteframe_t up_run2 = player_frame_width * 23;
    spriteframe_t down_run1 = player_frame_width * 16;
    spriteframe_t down_run2 = player_frame_width * 17;
    spriteframe_t left_run1 = player_frame_width * 13;
    spriteframe_t left_run2 = player_frame_width * 14;
    spriteframe_t right_run1 = player_frame_width * 19;
    spriteframe_t right_run2 = player_frame_width * 20;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) player_state = RUNNING;
        if (IsKeyReleased(KEY_LEFT_SHIFT)) player_state = IDLE;
        if (IsKeyDown(KEY_LEFT_SHIFT) &&!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) player_state = IDLE;

        if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            player_direction = UP;
            player_state = WALKING;
        }

        if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            player_direction = DOWN;
            player_state = WALKING;
        }
        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            player_direction = LEFT;
            player_state = WALKING;
        }
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            player_direction = RIGHT;
            player_state = WALKING;
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);
        if (player_state == IDLE) {
             printf("player_state == IDLE\n");
            switch (player_direction) {
                case UP:
                    draw_player(player_sheet, player, up_idle);
                    break;
                case DOWN:
                    draw_player(player_sheet, player, down_idle);
                    break;
                case LEFT:
                    draw_player(player_sheet, player, left_idle);
                    break;
                case RIGHT:
                    draw_player(player_sheet, player, right_idle);
            }
        }

        if (player_state == WALKING) {
            printf("player_state == WALKING\n");
            
            switch (player_direction) {
                case UP:
                    player.fcounter++;
                    if (player.fcounter <= 20) draw_player(player_sheet, player, up_walk1);
                    if (player.fcounter >= 20) draw_player(player_sheet, player, up_walk2);
                    if (player.fcounter >= 40) player.fcounter = 0;
                    if (IsKeyDown(KEY_W)) player.pos.y -= player.walk_speed;
                    if (IsKeyReleased(KEY_W)) player_state = IDLE;
                    break;
                case DOWN:
                    player.fcounter++;
                    if(player.fcounter <= 20) draw_player(player_sheet, player, down_walk1);
                    if(player.fcounter >= 20) draw_player(player_sheet, player, down_walk2);
                    if (player.fcounter >= 40) player.fcounter = 0;
                    if (IsKeyDown(KEY_S)) player.pos.y += player.walk_speed;
                    if (IsKeyReleased(KEY_S)) player_state = IDLE;
                    break;
                case LEFT:
                     player.fcounter++;
                    if (player.fcounter <= 20) draw_player(player_sheet, player, left_walk1);
                    if (player.fcounter >= 20) draw_player(player_sheet, player, left_walk2);
                    if (player.fcounter >= 40) player.fcounter = 0;
                    if (IsKeyDown(KEY_A)) player.pos.x -= player.walk_speed;
                    if (IsKeyReleased(KEY_A)) player_state = IDLE;
                    break;
                case RIGHT:
                    player.fcounter++;
                    if (player.fcounter <= 20) draw_player(player_sheet, player, right_walk1);
                    if (player.fcounter >= 20) draw_player(player_sheet, player, right_walk2);
                    if (player.fcounter >= 40) player.fcounter = 0;
                    if (IsKeyDown(KEY_D)) player.pos.x += player.walk_speed;
                    if (IsKeyReleased(KEY_D)) player_state = IDLE;
                    break;
            }
        }
        if (player_state == RUNNING) {
            printf("player_state == RUNNING\n");
            if (IsKeyDown(KEY_W)) player_direction = UP;
            if (IsKeyDown(KEY_S)) player_direction = DOWN;
            if (IsKeyDown(KEY_A)) player_direction = LEFT;
            if (IsKeyDown(KEY_D)) player_direction = RIGHT;
            switch (player_direction) {
                case UP:
                    player.fcounter++;
                    if (player.fcounter <= 15) draw_player(player_sheet, player, up_run1);
                    if (player.fcounter >= 15) draw_player(player_sheet, player, up_run2);
                    if (player.fcounter >= 30) player.fcounter = 0;
                    if (IsKeyDown(KEY_W)) player.pos.y -= player.run_speed;
                    if (IsKeyReleased(KEY_W)) player_state = IDLE;
                    break;
                case DOWN:
                    player.fcounter++;
                    if(player.fcounter <= 15) draw_player(player_sheet, player, down_run1);
                    if(player.fcounter >= 15) draw_player(player_sheet, player, down_run2);
                    if (player.fcounter >= 40) player.fcounter = 0;
                    if (IsKeyDown(KEY_S)) player.pos.y += player.run_speed;
                    break;
                case LEFT:
                     player.fcounter++;
                    if (player.fcounter <= 15) draw_player(player_sheet, player, left_run1);
                    if (player.fcounter >= 15) draw_player(player_sheet, player, left_run2);
                    if (player.fcounter >= 30) player.fcounter = 0;
                    if (IsKeyDown(KEY_A)) player.pos.x -= player.run_speed;
                    if (IsKeyReleased(KEY_A)) player_state = IDLE;
                    break;
                case RIGHT:
                    player.fcounter++;
                    if (player.fcounter <= 15) draw_player(player_sheet, player, right_run1);
                    if (player.fcounter >= 15) draw_player(player_sheet, player, right_run2);
                    if (player.fcounter >= 30) player.fcounter = 0;
                    if (IsKeyDown(KEY_D)) player.pos.x += player.run_speed;
                    if (IsKeyReleased(KEY_D)) player_state = IDLE;
                    break;
            }
            
        }

        EndDrawing();
    }
    UnloadTexture(player_sheet);
    printf("Goodbye\n");
    return 0;
}
