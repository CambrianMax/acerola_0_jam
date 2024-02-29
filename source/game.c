


void
game_init()
{
    load_image(TEST_IMG);
    load_image(TEST_FNT);
    Entity e = {0};
    e.pos = (V2){300,50};
    e.sprite_id = TEST_SPR;
    add_entity(&e);
}


void 
game_update(GameInput *game_input)
{
    gi = game_input;
    gs.total_time += gi->elapsed_seconds;
    pre_render();
    update_entities();
    update_sprites();
    draw_entities();
    render();
}


void
game_cleanup()
{
    //todo cleanup
}