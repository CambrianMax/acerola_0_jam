/* date = February 28th 2024 11:20 pm */

#ifndef INPUT_H
#define INPUT_H


typedef struct 
{
    bool32 ended_down;
    b32 pressed;
}GameButtonState;

typedef struct 
{
    bool32 is_connected;
    bool32 is_analog;
    real32 stick_average_x;
    real32 stick_average_y;
    
    union
    {
        GameButtonState buttons[15];
        struct
        {
            GameButtonState move_up;
            GameButtonState move_down;
            GameButtonState move_left;
            GameButtonState move_right;
            
            GameButtonState action_up;
            GameButtonState action_down;
            GameButtonState action_left;
            GameButtonState action_right;
            
            GameButtonState left_shoulder;
            GameButtonState right_shoulder;
            
            GameButtonState back;
            GameButtonState start;
            
            GameButtonState shift;
            GameButtonState back_space;
            GameButtonState enter;
            
            //NOTE: add all buttons about this line
            
            GameButtonState terminator;
        };
    };
    
}GameControllerInput;


typedef struct{
    GameButtonState mouse_buttons[5];
    int32 mouse_x, mouse_y, mouse_z;
    r32 mouse_wheel;
    real32 elapsed_seconds;
    GameControllerInput controller;
}GameInput;


void
process_key_press(GameButtonState* new_button, GameButtonState* old_button, b32 ended_down)
{
    new_button->ended_down = ended_down;
    if(!old_button->ended_down && ended_down)
    {
        new_button->pressed = true;
    }
}


#endif //INPUT_H
