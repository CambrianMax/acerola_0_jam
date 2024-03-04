/* date = February 29th 2024 0:27 am */

#ifndef ENTITY_H
#define ENTITY_H





#define LIST_OF_ENTITY_TYPES \
X(PLAYER_ENT) \
X(DECOR_ENT) \
X(COLLECTABLE_ENT) \
X(S_COLLISION_ENT) \
X(PARALAX_ENT) \


#define X(name) name,
typedef enum
{
    LIST_OF_ENTITY_TYPES
        TOTAL_ENTITY_TYPES
}EntityType;
#undef X




typedef struct
{
    EntityType type;
    V2 velocity;
    AABB aabb;
    SpriteId sprite_id;
    r32 frame_time;
    u32 frame;
    b32 jump_desired;
    b32 grounded;
    b32 gravity;
    f32 time_jumping;
    f32 jump_buffer; //buffer_jumps
    f32 coyate_time; //
    b32 collide_check;
    b32 invisible;
    
    V2 initial_pos;
    f32 z_location;
    f32 scale;
}Entity;


#define X(name) void name##_sim(Entity* );
LIST_OF_ENTITY_TYPES
#undef X


#define X(name) [name] = &name##_sim,
void (* entity_sims[TOTAL_ENTITY_TYPES])(Entity*) = 
{
    LIST_OF_ENTITY_TYPES
};
#undef X



void entities_apply(void (*f) (Entity*));



void set_entity_sprite(Entity*, SpriteId );

Entity* add_entity(Entity* e);





#endif //ENTITY_H
