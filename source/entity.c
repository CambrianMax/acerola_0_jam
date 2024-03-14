




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
    if(gs.pause_entities)
        return;
    entities_apply(&update_entity);
}


Entity* add_player_entity(f32 x, f32 y)
{
    
    Entity e = 
    {
        .scale = 1.0f,
        .type = PLAYER_ENT,
        .sprite_id = PLAYER_FI_SPR,
        .aabb.pos = {x,y},
        .aabb.half_size = {10,10},
        .d_layer = MID_TILE,
    };
    if(gs.platform_mode)
    {
        if(x > 350)
            e.sprite_id = PLAYER_PLI_SPR;
        else
            e.sprite_id = PLAYER_PRI_SPR;
        
    }
    gs.player = add_entity(&e);
    return gs.player;
}



Entity* add_w_collision_entity(f32 x, f32 y, f32 w, f32 h)
{
    Entity e = 
    {
        .type = S_COLLISION_ENT,
        .subtype = EVIL_WITCH,
        .aabb.pos = {x,y},
        .aabb.half_size = {w,h},
        .invisible = true,
    };
    return add_entity(&e);
}


Entity* add_s_collision_entity(f32 x, f32 y, f32 w, f32 h)
{
    Entity e = 
    {
        .type = S_COLLISION_ENT,
        .aabb.pos = {x,y},
        .aabb.half_size = {w,h},
        .invisible = true,
    };
    return add_entity(&e);
}


Entity* add_t_collision_entity(f32 x, f32 y, f32 w, f32 h, i32 room_id, i32 tele_x, i32 tele_y)
{
    Entity e = 
    {
        .type = S_COLLISION_ENT,
        .subtype = TELE_BOX,
        .aabb.pos = {x,y},
        .aabb.half_size = {w,h},
        .invisible = true,
        .c.room_id = room_id,
        .c.tele_x = tele_x,
        .c.tele_y = tele_y,
    };
    return add_entity(&e);
}



Entity* add_dialouge_entity(f32 x, f32 y, DialougeId id)
{
    Entity e = 
    {
        .scale = 1.0f,
        .sprite_id= dialouge_sprites[id],
        .type = DIALOUGE_ENT,
        .aabb.pos = {x,y},
        .info_id = id,
        .d_layer = MID_TILE,
    };
    
    add_s_collision_entity(x,y+10,10,10);
    return add_entity(&e);
}




Entity* add_texty_entity(f32 x, f32 y, DialougeId id)
{
    Entity e = 
    {
        .type = TEXTY_ENT,
        .aabb.pos = {x+20,y+10},
        .initial_pos = {x,y},
        .info_id = id,
        .alpha = 1.0f,
        .d_layer = GUI_LOW,
    };
    if(id != INIT_D)
        play_sfx(DIA_SFX);
    return add_entity(&e);
}



Entity* add_bink_blast_entity(f32 x, f32 y, V2 vel)
{
    Entity e = 
    {
        .scale = 1.0f,
        .type = BINK_BLAST_ENT,
        .sprite_id = BINK_BLAST_SPR,
        .aabb.pos = {x,y},
        .aabb.half_size = {10,10},
        .d_layer = MID_TILE,
        .velocity = vel,
    };
    play_sfx(BB_SFX);
    return add_entity(&e);
}

Entity* add_decor_entity(f32 x, f32 y, SpriteId id)
{
    Entity e = 
    {
        .scale = 1.0f,
        .sprite_id= id,
        .type = DECOR_ENT,
        .aabb.pos = {x,y},
        .d_layer = MID_TILE,
    };
    const Sprite* spr = &sprites[id];
    if((id == WITCH_BLOCK_SPR || id == WITCH_BLOCK_2_SPR) && !gs.platform_mode)
        add_w_collision_entity(x,y + spr->y_offset,spr->w,spr->h);
    else if(spr->col)
    {
        
        add_s_collision_entity(x,y + spr->y_offset,spr->w,spr->h);
    }
    
    return add_entity(&e);
}


Entity* add_destructible_entity(f32 x, f32 y, SpriteId id)
{
    
    const Sprite* spr = &sprites[id];
    Entity e = 
    {
        .scale = 1.0f,
        .sprite_id= id,
        .type = DESTRUCTIBLE_ENT,
        .aabb.pos = {x,y},
        .aabb.half_size = {spr->w,spr->h},
        .d_layer = MID_TILE,
    };
    if(id == DEVIL_TREE_SPR)
        e.scale = 1.75f;
    
    return add_entity(&e);
}


Entity* 
add_temp_entity(f32 x, f32 y, SpriteId id)
{
    const Sprite* spr = &sprites[id];
    Entity e = 
    {
        .scale = 1.0f,
        .sprite_id= id,
        .type = TEMP_ENT,
        .aabb.pos = {x,y},
        .aabb.half_size = {spr->w,spr->h},
        .d_layer = MID_TILE,
    };
    
    return add_entity(&e);
}



Entity* 
add_misc_entity(i32 id)
{
    Entity e = 
    {
        .invisible = true,
        .subtype = id,
        .scale =1.0f,
        .type = MISC_ENT,
    };
    
    return add_entity(&e);
}


Entity* 
add_particle_entity(f32 x, f32 y, i32 id, i32 mag, f32 scale)
{
    
    const Sprite* spr = &sprites[PARTICLE_SPR];
    Entity e = 
    {
        .scale = scale,
        .sprite_id= PARTICLE_SPR,
        .color = id,
        .type = PARTICLE_ENT,
        .aabb.pos = {x,y},
        .velocity={rand() % mag - mag/2, rand() % mag - mag/2},
        //.aabb.half_size = {spr->w,spr->h},
        .d_layer = LOW_TILE,
        //.shader_id = COLOR_SHADER,
        .shader_id = COLOR_SHADER,
        
    };
    
    return add_entity(&e);
}



Entity* add_bad_bullet_entity(f32 x, f32 y, V2 vel, i32 subtype, SpriteId id)
{
    
    const Sprite* spr = &sprites[id];
    Entity e = 
    {
        .scale = 1.0f,
        .sprite_id= id,
        .type = BAD_BULLET_ENT,
        .aabb.pos = {x,y},
        .aabb.half_size = {spr->w, spr->h},
        .velocity = vel,
        .subtype = subtype,
        .d_layer = MID_TILE,
    };
    
    return add_entity(&e);
}

void kill_entity(Entity* e)
{
    *e = gs.entities[gs.num_entities -1];
    gs.entities[gs.num_entities -1] = (Entity){0};
    if(e->type == PLAYER_ENT)
        gs.player = e;
    if(e->type == BAD_BULLET_ENT && e->sprite_id == WITCH_I_SPR)
        gs.witch = e;
    
    --gs.num_entities;
}




void remove_dead_entities()
{
    for(i32 i = 0; i < gs.num_entities; i++)
    {
        if(gs.entities[i].death_marked)
            kill_entity(&gs.entities[i]);
    }
}



void clear_entities()
{
    gs.num_entities = 0;
}
