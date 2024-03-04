



void
PLAYER_ENT_sim(Entity* e)
{
    GameControllerInput* in = &gi->controller;
    f32 x_acc = 10000.0f;
    f32 x_decc = 5000.0f;
    f32 x_maxspeed = 500.0f;
    b32 x_moving = false;
    
    e->z_location = gs.z_location;
    
    if(!e->collide_check)
    {
        if(e->grounded)
        {
            e->coyate_time  = 0.08f;
        }
        e->grounded = false;
    }
    
    e->collide_check = false;
    
    if(!e->grounded)
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
        e->jump_buffer = 0.2f;
    }
    if((e->grounded || e->coyate_time > 0.0f) && e->jump_buffer > 0)
    {
        e->velocity.y = 800;
        e->grounded = false;
        e->jump_desired = true;
    }
    if(in->action_right.ended_down && e->jump_desired == true)
    {
        e->jump_desired = true;
    }
    else
    {
        e->jump_desired = false;
    }
    
    if(e->velocity.y < 0.0f)
        e->jump_desired = false;
    
    
    if(e->jump_desired)
        e->velocity.y += gi->elapsed_seconds * -2000;
    else
        e->velocity.y += gi->elapsed_seconds * -6000;
    
    if(e->velocity.x != 0)
        set_entity_sprite(e, PLAYER_WALK_SPR);
    else
        set_entity_sprite(e, PLAYER_IDLE_SPR);
    
    
    if(e->jump_buffer > 0)
    {
        e->jump_buffer += -gi->elapsed_seconds;
    }
    
    if(e->coyate_time> 0)
    {
        e->coyate_time += -gi->elapsed_seconds;
    }
    
    e->scale = (abs_r32(e->velocity.x)/100) + 1.0f;
    
}


void
DECOR_ENT_sim(Entity* e)
{
}



void
COLLECTABLE_ENT_sim(Entity* e)
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