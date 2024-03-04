




Entity* add_entity(Entity* e)
{
    if(gs.num_entities >= MAX_ENTITIES)
        return NULL;
    Entity* t = &gs.entities[gs.num_entities];
    *t = *e;
    ++gs.num_entities;
    return t;
}


void
entities_apply(void (*f) (Entity* e))
{
    for(i32 i = 0; i <= (i32)gs.num_entities - 1; i++)
    {
        f(&gs.entities[i]);
    }
}



void set_entity_sprite(Entity* e, SpriteId id)
{
    if(e->sprite_id == id)
        return;
    e->sprite_id = id;
    e->frame = 0;
}


void update_entity(Entity* e)
{
    entity_sims[e->type](e);
}


void update_entities()
{
    entities_apply(&update_entity);
}


Entity* add_player_entity(f32 x, f32 y)
{
    
    Entity e = 
    {
        .type = PLAYER_ENT,
        .sprite_id = PLAYER_IDLE_SPR,
        .aabb.pos = {x,y},
        .aabb.half_size = {10,10},
        .scale = 1.0f,
    };
    gs.player = add_entity(&e);
    return gs.player;
}


Entity* add_s_collision_entity(f32 x, f32 y, f32 w, f32 h)
{
    Entity e = 
    {
        .type = S_COLLISION_ENT,
        .aabb.pos = {x,y},
        .aabb.half_size = {w,h},
        .scale = 1.0f,
    };
    return add_entity(&e);
}


Entity* add_paralax_entity(f32 x, f32 y, f32 z, SpriteId id)
{
    
    Entity e = 
    {
        .type = PARALAX_ENT,
        .sprite_id = id,
        .aabb.pos = {x,y},
        .initial_pos = {x,y},
        .z_location = z,
        .scale = 1.0f,
    };
    return add_entity(&e);
}