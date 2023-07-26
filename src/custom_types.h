#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H
#endif
typedef int spriteframe_t; // holds the calculation offset for a specific frame of a sprite sheet. eg frame 5 = (player_frame_width * 4).

typedef enum {
    TITLE,
    GAMEPLAY,    

} GameScene;

typedef enum  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direction;

typedef enum  {
    IDLE,
    WALKING,
    RUNNING,
} CharacterState;

typedef struct {
    Vector2 pos;
    float walk_speed;
    float run_speed;
    int fcounter; //framecounter for animations etc.
} Character;
