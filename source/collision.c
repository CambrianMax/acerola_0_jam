
void
kill_bink()
{
    if(gs.bink_dead)
        return;
    gs.player->death_marked = true;
    
    gs.bink_dead = true;
    for(i32 i = 0; i < 3; i++)
    {
        add_particle_entity(gs.player->aabb.pos.x,gs.player->aabb.pos.y, M_PINK, 600, 0.8f);
        add_particle_entity(gs.player->aabb.pos.x,gs.player->aabb.pos.y, M_LIGHT_YELLOW, 600, 0.8f);
        add_particle_entity(gs.player->aabb.pos.x,gs.player->aabb.pos.y, M_LIGHT_BLUE, 600, 0.8f);
        
    }
    play_sfx(BINK_DEATH_SFX);
    
    add_misc_entity(DEATH_RESPAWNER);
}


void process_halt_collide(Entity *e0, Entity *e1, CollisionInfo* col_info)
{
    if(e0->type == BAD_BULLET_ENT)
    {
        if(!(e0->subtype == EVIL_WITCH))
        {
            e0->death_marked = true;
            for(i32 i = 0; i < 5; i++)
            {
                add_particle_entity(e0->aabb.pos.x,e0->aabb.pos.y, M_WHITE, 600, 0.4f);
                
            }
            
        }
        if(e1->type == PLAYER_ENT)
        {
            kill_bink();
        }
    }
    if(e1->type == BAD_BULLET_ENT)
    {
        if(!(e1->subtype == EVIL_WITCH))
        {
            e1->death_marked = true;
            for(i32 i = 0; i < 5; i++)
            {
                add_particle_entity(e0->aabb.pos.x,e0->aabb.pos.y, M_WHITE, 600, 0.4f);
                
            }
            
        }
        if(e0->type == PLAYER_ENT)
        {
            kill_bink();
        }
    }
    
    if(e0->type == BINK_BLAST_ENT)
    {
        e0->death_marked = true;
        add_temp_entity(e0->aabb.pos.x, e0->aabb.pos.y- 15.0f, BINK_BLAST_FINISH_SPR);
        play_sfx(BBF_SFX);
        for(i32 i = 0; i < 2; i++)
        {
            add_particle_entity(e0->aabb.pos.x,e0->aabb.pos.y, M_HOT_PINK, 1000, 0.4f);
            add_particle_entity(e0->aabb.pos.x,e0->aabb.pos.y, M_ORANGE, 1000, 0.4f);
            
        }
        if(e1->type == DESTRUCTIBLE_ENT)
        {
            if(e1->sprite_id == DEVIL_TREE_SPR )
            {
                
                e1->death_marked = true;
                Entity *t_temp = add_temp_entity(e1->aabb.pos.x, e1->aabb.pos.y, DEVIL_DIES_SPR);
                t_temp->scale = 1.75;
                gs.devil_dead = true;
                set_entity_sprite(gs.witch, WITCH_P_SPR);
                gs.witch->shader_id= STANDARD_SHADER;
                start_dialouge(WITCH_1_D, WITCH_4_D);
                gs.platform_mode = true;
                stop_music();
                entities_apply(&death_mark_witch_blocks);
                gs.witch_active = false;
                play_sfx(TREE_DEATH_SFX);
            }
            else
            {
                e1->death_marked = true;
                play_sfx(CRUMBLE_SFX);
                for(i32 i = 0; i < 10; i++)
                {
                    
                    add_particle_entity(e1->aabb.pos.x,e1->aabb.pos.y, M_GRAY, 300, 0.7f);
                    
                }
            }
        }
    }
    if(e0->type== PLAYER_ENT && (e1->type==S_COLLISION_ENT || e1->type==DESTRUCTIBLE_ENT ))
    {
        if(e1->subtype == TELE_BOX)
        {
            
            prepare_warp(e1->c.room_id, e1->c.tele_x, e1->c.tele_y);
            return;
        }
        
        
        if(gs.platform_mode)
        {
            
            if(col_info->contact_normal.y == 1.0f)
            {
                e0->p.grounded = true;
                {
                    if(e0->sprite_id == PLAYER_PRJ_SPR)
                        set_entity_sprite(e0, PLAYER_PRI_SPR);
                    else if(e0->sprite_id == PLAYER_PLJ_SPR)
                        set_entity_sprite(e0, PLAYER_PLI_SPR);
                    
                    if(!gi->controller.action_right.ended_down)
                        e0->p.jump_buffer = 0.0f;
                }
            }
            
        }
    }
    if(!e0->intangible)
    {
        e0->velocity.x += col_info->contact_normal.x * abs_r32(e0->velocity.x) * (1.0f - col_info->hit_time);
        e0->velocity.y += col_info->contact_normal.y * abs_r32(e0->velocity.y) * (1.0f - col_info->hit_time);
        e0->p.collide_check = true;
    }
}




b32 
ray_vs_rect(V2 ray_pos, V2 ray_dir, const AABB* target_aabb, V2 *contact_pos, V2 *contact_normal, f32 *time_hit)
{
    *contact_normal = (V2){0.0f, 0.0f};
    *contact_pos = (V2){0.0f, 0.0f};
    *time_hit = 0.0f;
    
    V2 invert_dir = {1.0f / ray_dir.x, 1.0f / ray_dir.y};
    
    V2 t_near = v2_sub(v2_sub(target_aabb->pos,target_aabb->half_size ), ray_pos);
    t_near.x = t_near.x / ray_dir.x;
    t_near.y = t_near.y / ray_dir.y;
    
    //TODO: check this
    V2 t_far = v2_sub(v2_add(target_aabb->pos, target_aabb->half_size), ray_pos);
    t_far.x = t_far.x / ray_dir.x;
    t_far.y = t_far.y / ray_dir.y;
    
    if(isnan(t_far.y) || isnan(t_far.x)) return false;
    if(isnan(t_near.y) || isnan(t_near.x)) return false;
    
    
    if(t_near.x > t_far.x) f32_swap(&t_near.x, &t_far.x);
    if(t_near.y > t_far.y) f32_swap(&t_near.y, &t_far.y);
    
    if(t_near.x > t_far.y || t_near.y > t_far.x) return false;
    
    *time_hit = max_r32(t_near.x, t_near.y);
    f32 t_hit_far = min_r32(t_far.x, t_far.y);
    
    if(t_hit_far < 0) return false;
    
    *contact_pos = v2_add(ray_pos, v2_mul(*time_hit, ray_dir));
    
    if(t_near.x > t_near.y)
    {
        if(invert_dir.x < 0)
            *contact_normal = (V2){1.0f, 0.0f};
        else
            *contact_normal = (V2){-1.0f, 0.0f};
    }
    else if (t_near.x < t_near.y)
    {
        if(invert_dir.y < 0)
            *contact_normal = (V2){0.0f, 1.0f};
        else
            *contact_normal = (V2){0.0f, -1.0f};
    }
    
    
    return true;
}




// fills in contact pos, contact normal and hit time
b32 dynamic_rect_vs_rect(AABB *src_aabb, V2 src_velocity,  AABB *target_aabb, f32 elapsed_time, V2 *contact_pos, V2 *contact_normal, f32 *hit_time)
{
    if(src_velocity.x == 0 && src_velocity.y == 0)
        return false;
    AABB expanded_aabb;
    expanded_aabb.pos = target_aabb->pos;
    expanded_aabb.half_size = v2_add(target_aabb->half_size, src_aabb->half_size);
    
    
    if(ray_vs_rect(src_aabb->pos, v2_mul(elapsed_time, src_velocity), &expanded_aabb, contact_pos, contact_normal, hit_time))
    {
        return (*hit_time >= 0.0f && *hit_time < 1.0f);
    }
    return false;
}

void static_collisions()
{
    if(gs.pause_collision)
        return;
    V2 contact_pos;
    V2 contact_normal;
    f32 hit_time = 0.0f;
    gs.num_sort_pairs = 0;
    for(i32 i = 0; i < gs.num_entities; i++)
    {
        Entity* e0 = &gs.entities[i];
        if(e0->type != PLAYER_ENT && e0->type != BINK_BLAST_ENT && e0->type != BAD_BULLET_ENT)
            continue;
        if(e0->velocity.x == 0 && e0->velocity.y == 0)
            continue;
        for(i32 j = 0; j < gs.num_entities; j++)
        {
            Entity* e1 = &gs.entities[j];
            if((e1->type != S_COLLISION_ENT && e1->type != DESTRUCTIBLE_ENT && e1->type != PLAYER_ENT &&  e1->type != BAD_BULLET_ENT)|| e0 == e1)
                continue;
            AABB aabb0 = e0->aabb;
            AABB aabb1 = e1->aabb;
            if(dynamic_rect_vs_rect(&aabb0, e0->velocity, &aabb1, gi->elapsed_seconds, &contact_pos, &contact_normal, &hit_time))
            {
                gs.sort_buffer[gs.num_sort_pairs] = (SortPair){j, hit_time};
                ++gs.num_sort_pairs;
            }
            
        }
        quick_sort(gs.sort_buffer, gs.num_sort_pairs);
        
        for(i32 k = 0; k < gs.num_sort_pairs; k++)
        {
            Entity* e1 = &gs.entities[gs.sort_buffer[k].id];
            
            AABB aabb0 = e0->aabb;
            AABB aabb1 = e1->aabb;
            if(dynamic_rect_vs_rect(&aabb0, e0->velocity, &aabb1, gi->elapsed_seconds, &contact_pos, &contact_normal, &hit_time))
            {
                CollisionInfo col_info = 
                {
                    .contact_pos = contact_pos,
                    .contact_normal = contact_normal,
                    .hit_time = hit_time,
                };
                
                process_halt_collide(e0,e1, &col_info);
                process_halt_collide(e0,e1, &col_info);
            }
        }
        //e0->aabb.pos = v2_add(e0->aabb.pos, v2_mul(gi->elapsed_seconds, e0->velocity)); 
        
    }
    
    for(i32 i = 0; i < gs.num_entities; i++)
    {
        Entity* e = &gs.entities[i];
        e->aabb.pos = v2_add(e->aabb.pos, v2_mul(gi->elapsed_seconds, e->velocity)); 
        
    }
    
}




