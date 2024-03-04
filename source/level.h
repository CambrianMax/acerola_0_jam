/* date = March 2nd 2024 9:04 pm */

#ifndef LEVEL_H
#define LEVEL_H

#define TILE_SIZE 32

typedef enum
{
    TEST_LEVEL,
    TOTAL_LEVELS,
}LevelId;

char* levels[] = 
{
    [TEST_LEVEL] = "assets/test_level.tmj",
};

#endif //LEVEL_H
