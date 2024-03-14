



void
PLAYER_ENT_sim(Entity* e)
{
    
    
    
    GameControllerInput* in = &gi->controller;
    
    e->p.trail_cooldown += -gi->elapsed_seconds;
    if(gs.platform_mode)
    {
        f32 x_acc = 5000.0f;
        f32 x_decc = 8000.0f;
        f32 x_maxspeed = 300.0f;
        b32 x_moving = false;
        
        
        if(!e->p.collide_check)
        {
            if(e->p.grounded)
            {
                e->p.coyate_time  = 0.08f;
            }
            e->p.grounded = false;
        }
        
        e->p.collide_check = false;
        
        if(!e->p.grounded)
        {
            x_acc = 5000.0f;
            x_decc = 500.0f;
        }
        if(in->move_right.ended_down)
        {
            e->velocity.x += gi->elapsed_seconds * x_acc;
            x_moving = true;
        }
        if(in->move_left.ended_down)
        {
            e->velocity.x -= gi->elapsed_seconds * x_acc;
            x_moving = true;
        }
        if(!x_moving)
        {
            if(e->velocity.x > 0)
            {
                e->velocity.x -= gi->elapsed_seconds * x_decc;
                e->velocity.x = max_r32(e->velocity.x, 0.0f);
            }
            
            if(e->velocity.x < 0)
            {
                e->velocity.x += gi->elapsed_seconds * x_decc;
                e->velocity.x = min_r32(e->velocity.x, 0.0f);
            }
        }
        else
        {
            
            if(e->velocity.x > 0)
            {
                e->velocity.x = min_r32(e->velocity.x, x_maxspeed);
            }
            else
            {
                
                e->velocity.x = max_r32(e->velocity.x, -x_maxspeed);
            }
        }
        
        if(in->action_right.pressed)
        {
            e->p.jump_buffer = 0.2f;
        }
        if((e->p.grounded || e->p.coyate_time > 0.0f) && e->p.jump_buffer > 0)
        {
            e->velocity.y = 700;
            e->p.grounded = false;
            e->p.jump_desired = true;
            e->p.coyate_time = 0.0f;
            e->p.jump_buffer = 0.0f;
            play_sfx(BINK_JUMP_SFX);
        }
        if(in->action_right.ended_down && e->p.jump_desired == true)
        {
            e->p.jump_desired = true;
        }
        else
        {
            e->p.jump_desired = false;
        }
        
        if(e->velocity.y < 0.0f)
            e->p.jump_desired = false;
        
        
        if(e->p.jump_desired)
            e->velocity.y += gi->elapsed_seconds * -2000;
        else
            e->velocity.y += gi->elapsed_seconds * -6000;
        
        if(!e->p.grounded)
        {
            if(e->velocity.x > 0)
                
                set_entity_sprite(e, PLAYER_PRJ_SPR);
            
            else if(e->velocity.x < 0)
                set_entity_sprite(e, PLAYER_PLJ_SPR);
            else
            {
                if(e->sprite_id == PLAYER_PRI_SPR)
                    set_entity_sprite(e, PLAYER_PRJ_SPR);
                else if(e->sprite_id == PLAYER_PLI_SPR)
                    set_entity_sprite(e, PLAYER_PLJ_SPR);
            }
            
        }
        else if(e->velocity.x > 0)
        {
            set_entity_sprite(e, PLAYER_PRW_SPR);
        }
        else if(e->velocity.x < 0)
        {
            set_entity_sprite(e, PLAYER_PLW_SPR);
        }
        else
        {
            if(e->sprite_id == PLAYER_PRW_SPR)
                set_entity_sprite(e, PLAYER_PRI_SPR);
            else if(e->sprite_id == PLAYER_PLW_SPR)
                set_entity_sprite(e, PLAYER_PLI_SPR);
        }
        
        if(e->p.jump_buffer > 0)
        {
            e->p.jump_buffer += -gi->elapsed_seconds;
        }
        
        if(e->p.coyate_time> 0)
        {
            e->p.coyate_time += -gi->elapsed_seconds;
        }
        
        if((e->velocity.x ) && e->p.trail_cooldown <= 0)
        {
            add_particle_entity(e->aabb.pos.x,e->aabb.pos.y- 15, M_WHITE, 10, 0.5);
            e->p.trail_cooldown = 0.20f;
        }
    }
    else
    {
        e->velocity.x = 0.0f;
        e->velocity.y = 0.0f;
        f32 speed = 200;
        f32 dx = 0.0f;
        f32 dy = 0.0f;
        
        /*
        e->dash_modifer -= 1000 *gi->elapsed_seconds;
        e->dash_modifer = max_r32(0.0f, e->dash_modifer);
        e->dash_cooldown -= gi->elapsed_seconds;
        
        if(in->action_right.pressed && e->dash_cooldown < 0.0f)
        {
            e->dash_modifer = 350;
            e->dash_cooldown = 0.5f;
            for(i32 i = 0; i < 10; i++)
                add_particle_entity(e->aabb.pos.x,e->aabb.pos.y- 15, M_WHITE, 50, 0.7);
        }
        speed += e->dash_modifer;
        */
        if(in->move_right.ended_down)
        {
            dx += 1.0f;
        }
        if(in->move_left.ended_down)
        {
            dx += -1.0f;
        }
        
        if(in->move_up.ended_down)
        {
            dy += 1.0f;
        }
        
        if(in->move_down.ended_down)
        {
            dy += -1.0f;
        }
        
        if(dx == 0 && dy == 0)
            e->velocity = (V2){0,0};
        else
            e->velocity = v2_mul(speed, v2_normalize((V2){dx, dy}));
        
        //e->velocity = v2_mul(speed, e->velocity);
        
        if(dy < 0)
            set_entity_sprite(e, PLAYER_FW_SPR);
        else if (dx > 0)
            set_entity_sprite(e, PLAYER_RW_SPR);
        else if (dy > 0)
            set_entity_sprite(e, PLAYER_BW_SPR);
        else if (dx < 0)
            set_entity_sprite(e, PLAYER_LW_SPR);
        else
        {
            if(e->sprite_id == PLAYER_FW_SPR)
                set_entity_sprite(e, PLAYER_FI_SPR);
            else if(e->sprite_id == PLAYER_RW_SPR)
                set_entity_sprite(e, PLAYER_RI_SPR);
            else if(e->sprite_id == PLAYER_BW_SPR)
                set_entity_sprite(e, PLAYER_BI_SPR);
            else if(e->sprite_id == PLAYER_LW_SPR)
                set_entity_sprite(e, PLAYER_LI_SPR);
        }
        
        
        if(e->p.dash_modifer > 0.0f)
            e->p.trail_cooldown += -gi->elapsed_seconds*4;
        
        
        if((e->velocity.x || e->velocity.y) && e->p.trail_cooldown <= 0)
        {
            add_particle_entity(e->aabb.pos.x,e->aabb.pos.y- 15, M_WHITE, 10, 0.5);
            e->p.trail_cooldown = 0.20f;
        }
        
        
    }
    
    
    i32 bink_blast_speed = 10;
    e->p.bb_cooldown += gi->elapsed_seconds;
    if(in->action_down.pressed && e->p.bb_cooldown > 0.3f)
    {
        e->p.bb_cooldown = 0;
        V2 bb_vec = {1,0};
        
        switch(e->sprite_id)
        {
            case PLAYER_LI_SPR:
            case PLAYER_LW_SPR:
            case PLAYER_PLI_SPR:
            case PLAYER_PLW_SPR:
            case PLAYER_PLJ_SPR:
            {
                bb_vec.x = -1.0f;
            }break;
            case PLAYER_FI_SPR:
            case PLAYER_FW_SPR:
            {
                bb_vec.x = 0.0f;
                bb_vec.y = -1.0f;
            }break;
            case PLAYER_BI_SPR:
            case PLAYER_BW_SPR:
            {
                bb_vec.x = 0.0f;
                bb_vec.y = 1.0f;
            }break;
            
        }
        add_bink_blast_entity(e->aabb.pos.x, e->aabb.pos.y, v2_mul(bink_blast_speed,bb_vec));
    }
    
}



void
INVALID_ENT_sim(Entity* e)
{
}


void
DECOR_ENT_sim(Entity* e)
{
    switch(e->sprite_id)
    {
        
        case TITLE_SPR:
        {
            
            e->aabb.pos.x = capped_lerp(e->aabb.pos.x, 550, gi->elapsed_seconds);
            e->aabb.pos.y = capped_lerp(e->aabb.pos.y, 250, gi->elapsed_seconds);
        }break;
        
        case WITCH_CASTER_D_SPR:
        {
            e->dec.emit_cooldown += -gi->elapsed_seconds;
            if(e->dec.emit_cooldown <= 0.0f)
            {
                f32 speed = 300;
                
                V2 vel = {0,-speed};
                
                add_bad_bullet_entity(e->aabb.pos.x, e->aabb.pos.y +20, vel, 0, W_BULLET_SPR);
                e->dec.emit_cooldown = 1.0f;
            }
        }break;
        case WITCH_CASTER_L_SPR:
        {
            e->dec.emit_cooldown += -gi->elapsed_seconds;
            if(e->dec.emit_cooldown <= 0.0f)
            {
                f32 speed = 300;
                
                V2 vel = {-speed,0};
                
                add_bad_bullet_entity(e->aabb.pos.x, e->aabb.pos.y +20, vel, 0, W_BULLET_SPR);
                e->dec.emit_cooldown = 1.0f;
            }
        }break;
        case WITCH_CASTER_R_SPR:
        {
            e->dec.emit_cooldown += -gi->elapsed_seconds;
            if(e->dec.emit_cooldown <= 0.0f)
            {
                f32 speed = 300;
                
                V2 vel = {speed,0};
                
                add_bad_bullet_entity(e->aabb.pos.x, e->aabb.pos.y +20, vel, 0, W_BULLET_SPR);
                e->dec.emit_cooldown = 1.0f;
            }
        }break;
        
        case WITCH_CASTER_U_SPR:
        {
            e->dec.emit_cooldown += -gi->elapsed_seconds;
            if(e->dec.emit_cooldown <= 0.0f)
            {
                f32 speed = 300;
                
                V2 vel = {0,speed};
                
                add_bad_bullet_entity(e->aabb.pos.x, e->aabb.pos.y +20, vel, 0, W_BULLET_SPR);
                e->dec.emit_cooldown = 1.0f;
            }
        }break;
        default:
        {}break;
    }
}



void
COLLECTABLE_ENT_sim(Entity* e)
{
}


void create_tele_particles(V2 pos)
{
    for(i32 i = 0; i < 3; i++)
    {
        add_particle_entity(pos.x,pos.y, M_GROSS_GREEN, 600, 0.6f);
        add_particle_entity(pos.x,pos.y, M_GROSS_GREEN, 600, 0.6f);
        add_particle_entity(pos.x,pos.y, M_GROSS_GREEN, 600, 0.6f);
        add_particle_entity(pos.x,pos.y, M_GRAY, 600, 0.6f);
        add_particle_entity(pos.x,pos.y, M_WHITE, 600, 0.6f);
        add_particle_entity(pos.x,pos.y, M_BLACK, 600, 0.6f);
        
    }
}




void
MISC_ENT_sim(Entity* e)
{
    switch(e->subtype)
    {
        case WITCH_START:
        {
            if(!gs.witch_active)
            {
                if(gs.player->aabb.pos.y > 300)
                {
                    gs.witch_active = true;
                    play_sfx(TELE_SFX);
                    play_sfx(WITCH_LAUGH_SFX);
                    abrupt_music_change(WITCH_MUS);
                    /*
                    Entity *w = add_destructible_entity(e->aabb.pos.x,e->aabb.pos.y,WITCH_I_SPR);
                    set_entity_sprite(w, WITCH_T_SPR);
                    create_tele_particles(w->aabb.pos);
                    w->subtype = EVIL_WITCH;
                    w->c.health = 10;
                    w->shader_id = GLOW_SHADER;
                    e->death_marked = true;
    */
                    Entity *w = add_bad_bullet_entity(e->aabb.pos.x,e->aabb.pos.y,(V2){0,0}, 0,WITCH_I_SPR);
                    set_entity_sprite(w, WITCH_T_SPR);
                    create_tele_particles(w->aabb.pos);
                    w->subtype = EVIL_WITCH;
                    w->shader_id = GLOW_SHADER;
                    w->intangible = true;
                    gs.witch = w;
                    e->death_marked = true;
                    
                    add_decor_entity(30,40, WITCH_BLOCK_SPR);
                    add_decor_entity(30,60, WITCH_BLOCK_SPR);
                    add_decor_entity(30,80, WITCH_BLOCK_SPR);
                }
            }
            else 
            {
                e->m.witch_timer += gi->elapsed_seconds;
                if(e->m.witch_timer > 2.5f)
                {
                    
                    Entity *w = add_bad_bullet_entity(e->aabb.pos.x,e->aabb.pos.y,(V2){0,0}, 0,WITCH_I_SPR);
                    set_entity_sprite(w, WITCH_T_SPR);
                    create_tele_particles(w->aabb.pos);
                    w->subtype = EVIL_WITCH;
                    w->shader_id = GLOW_SHADER;
                    w->intangible = true;
                    gs.witch = w;
                    play_sfx(TELE_SFX);
                    e->death_marked = true;
                }
            }
        }break;
        case DEATH_RESPAWNER:
        e->m.respawn_timer += gi->elapsed_seconds;
        if(e->m.respawn_timer > 0.8f)
        {
            prepare_warp(gs.tele_room, gs.tele_x, gs.tele_y);
            e->death_marked = true;
        }break;
        default:{}break;
    }
}


void
BAD_BULLET_ENT_sim(Entity* e)
{
    
    
    switch(e->subtype)
    {
        
        case EVIL_WITCH:
        {
            if(gs.devil_dead)
            {
                Entity* w_t = add_temp_entity(e->aabb.pos.x, e->aabb.pos.y, WITCH_DIES_SPR);
                w_t->scale = w_t->scale;
                w_t->velocity.x = 200;
                e->velocity = (V2){0,0};
                create_tele_particles(gs.player->aabb.pos);
                
                e->death_marked = true;
                return;
            }
            
            if(e->sprite_id == WITCH_T_SPR && e->frame == sprites[WITCH_T_SPR].frame_count - 1)
                set_entity_sprite(e, WITCH_I_SPR);
            else if(e->sprite_id == WITCH_P_SPR && e->c.pain_cooldown <= 0.0f)
                set_entity_sprite(e, WITCH_I_SPR);
            
            e->scale = abs_r32(sin(gs.total_time *6.0f)/8.0f) + 1.5f;
            
            if(squared_dist(e->aabb.pos, gs.player->aabb.pos) < 50)
                kill_bink();
            
            
            if(gs.bink_dead)
                return;
            
            V2 p_dir = v2_sub(gs.player->aabb.pos, e->aabb.pos);
            p_dir = v2_mul(150, v2_normalize(p_dir));
            e->velocity = p_dir;
            
            //e->c.pain_cooldown += -gi->elapsed_seconds;
            //e->c.bullet_cooldown += -gi->elapsed_seconds;
            
            /*
            if(e->c.bullet_cooldown  <= 0.0f)
            {
                
                add_bad_bullet_entity(e->aabb.pos.x,e->aabb.pos.y,p_dir,0, W_BULLET_SPR );
                e->c.bullet_cooldown = 0.5f;
            }
            */
            //e->scale += 1.0f;
        }break;
        default:
        {
            
            if(squared_dist(e->aabb.pos, gs.player->aabb.pos) < 50)
            {
                kill_bink();
                e->death_marked = true;
            }
        };
    }
    
    
}


void
BINK_BLAST_ENT_sim(Entity* e)
{
    
    if(e->velocity.x < -1.0f)
    {
        e->velocity.x = max_r32(-1000, e->velocity.x -(gi->elapsed_seconds *600) - 100);
    }
    else if(e->velocity.y < -1.0f)
    {
        e->velocity.y = max_r32(-1000, e->velocity.y -(gi->elapsed_seconds *600) - 100);
    }
    else if(e->velocity.y > 1.0f)
    {
        e->velocity.y = min_r32(1000, e->velocity.y +(gi->elapsed_seconds *600) + 100);
    }
    else{
        e->velocity.x = min_r32(1000, e->velocity.x +(gi->elapsed_seconds *600) + 100);
    }
    //e->velocity.y = min_r32(200, e->velocity.y +(gi->elapsed_seconds *100));
}


void
TEXTY_ENT_sim(Entity* e)
{
    
    switch(e->subtype)
    {
        
        case INIT_SCREEN:
        {
            if(gs.total_time > 2.0f && e->alpha >= 0)
                e->alpha += -0.05f;
            
            
            if(gi->controller.action_down.pressed)
            {
                play_sfx(BB_SFX);
                setup_intro();
                e->death_marked = true;
            }
        }break;
        
        default:
        if(!e->t.fade_switch)
        {
            e->alpha = max_r32(0.0f, e->alpha - 3* gi->elapsed_seconds);
            
        }
        else
        {
            
            e->alpha = min_r32(1.0f, e->alpha + 2* gi->elapsed_seconds);
            if(e->alpha >= 1.0f)
                e->death_marked = true;
        }
        if(dist(gs.player->aabb.pos, e->initial_pos) > 70)
        {
            e->t.fade_switch = true;
        }
    }
    
}

void
DIALOUGE_ENT_sim(Entity* e)
{
    
    
    if(!e->d.talking && dist(gs.player->aabb.pos, e->aabb.pos) < 70)
    {
        if(e->info_id == WIFE_2_D && !gs.reached_home)
        {
            gs.reached_home = true;
            start_dialouge(HOME_1_D, HOME_5_D);
            
        }
        else
        {
            add_texty_entity(e->aabb.pos.x, e->aabb.pos.y, e->info_id);
            e->d.talking = true;
        }
    }
    else if(e->d.talking && dist(gs.player->aabb.pos, e->aabb.pos) > 71)
    {
        e->d.talking = false;
    }
    
    
    //draw_text(e->aabb.pos.x -50, e->aabb.pos.y +50, 1.0f,TEST_FNT, dialouges[e->info_id]);
    //draw_text(100,100, 0.1f,TEST_FNT, "test ");
}



void
TEMP_ENT_sim(Entity* e)
{
    
    e->aabb.pos.x += e->velocity.x * gi->elapsed_seconds;
    e->aabb.pos.y += e->velocity.y * gi->elapsed_seconds;
    if(e->frame >= sprites[e->sprite_id].frame_count-1)
        e->death_marked = true;
}


void
PARTICLE_ENT_sim(Entity* e)
{
    e->scale -= gi->elapsed_seconds;
    if(e->scale < 0)
        e->death_marked = true;
    
    e->aabb.pos = v2_add(e->aabb.pos, v2_mul(gi->elapsed_seconds, e->velocity)); 
    
    
}


void
DESTRUCTIBLE_ENT_sim(Entity* e)
{
    
}


void
S_COLLISION_ENT_sim(Entity* e)
{
}

void
PARALAX_ENT_sim(Entity* e)
{
    //e->aabb.pos.x = e->initial_pos.x + (((rd.cam.x - (rd.cam.width)/2))*(1/e->z_location));
    
    //e->scale = (1.0f)/(e->z_location - gs.paralax_zoom);
    //e->scale = abs_r32(e->scale);
}