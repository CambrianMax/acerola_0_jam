/* date = February 29th 2024 5:29 pm */

#ifndef COLLISION_H
#define COLLISION_H


typedef struct
{
    V2 pos;
    V2 half_size;
}AABB;

typedef enum
{
    STATIC_COL,
    KINETIC_COL,
    TOTAL_COLLISION_TYPES,
}CollisionTypes;


typedef struct
{
    V2 contact_pos;
    V2 contact_normal;
    f32 hit_time;
}CollisionInfo;

#endif //COLLISION_H
