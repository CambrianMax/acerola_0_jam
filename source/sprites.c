


const Sprite*
get_sprite(SpriteId id)
{
    return &sprites[id];
}


const Sprite*
get_entity_sprite(Entity *e)
{
    return &sprites[e->sprite_id];
}



void
update_sprite(Entity* e)
{
    const Sprite* spr = get_entity_sprite(e);
    if (spr->frame_count <= 1)
        return;
    e->frame_time += gi->elapsed_seconds;
    r32 max_frame_time = (1.0f/(r32)spr->fps);
    
    if(e->frame_time > max_frame_time)
    {
        e->frame_time += -max_frame_time;
        ++e->frame;
        if(e->frame_time >= max_frame_time)
            e->frame_time = 0;
        if(e->frame >= spr->frame_count)
            e->frame = 0;
    }
}



void
update_sprites()
{
    entities_apply(&update_sprite);
}
