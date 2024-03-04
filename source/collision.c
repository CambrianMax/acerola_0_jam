

void process_halt_collide(Entity *e0, Entity *e1, CollisionInfo* col_info)
{
    
    
    e0->velocity.x += col_info->contact_normal.x * abs_r32(e0->velocity.x) * (1.0f - col_info->hit_time);
    e0->velocity.y += col_info->contact_normal.y * abs_r32(e0->velocity.y) * (1.0f - col_info->hit_time);
    e0->collide_check = true;
    
    if(e0->type== PLAYER_ENT && e1->type==S_COLLISION_ENT)
    {
        if(col_info->contact_normal.y == 1.0f)
        {
            e0->grounded = true;
            if(!gi->controller.action_right.ended_down)
                e0->jump_buffer = 0.0f;
        }
    }
    
    
}




inline
void f32_swap(f32* a, f32 *b)
{
    f32 c = *b;
    *b = *a;
    *a = c;
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

#define PHYSICS_ITERATIONS 2

void static_collisions()
{
    
    V2 contact_pos;
    V2 contact_normal;
    f32 hit_time = 0.0f;
    gs.num_sort_pairs = 0;
    for(i32 i = 0; i < gs.num_entities; i++)
    {
        Entity* e0 = &gs.entities[i];
        if(e0->type != PLAYER_ENT)
            continue;
        for(i32 j = 0; j < gs.num_entities; j++)
        {
            Entity* e1 = &gs.entities[j];
            if(e1->type != S_COLLISION_ENT || e0 == e1)
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
            }
        }
        e0->aabb.pos = v2_add(e0->aabb.pos, v2_mul(gi->elapsed_seconds, e0->velocity)); 
        
    }
    
}