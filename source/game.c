


void
game_init()
{
    load_image(TEST_IMG);
    load_image(TEST_FNT);
    
    //init_polygons();
    //add_s_collision_entity(100,100, 100,50);
    //add_s_collision_entity(300,140, 100,50);
    
    //add_s_collision_entity(500,100, 100,50);
    add_paralax_entity(800,0, 100, PARALAX_TEST_SPR);
    load_level(0);
    
    
    add_player_entity(100,500);
    
    rd.cam.x = SCREEN_WIDTH/2;
    rd.cam.y = SCREEN_HEIGHT/2;
    rd.cam.width = SCREEN_WIDTH;
    rd.cam.height = SCREEN_HEIGHT;
    gs.z_location = 0.0f;
}


void 
game_update(GameInput *game_input)
{
    gi = game_input;
    gs.total_time += gi->elapsed_seconds;
    pre_render();
    
    /*
    Polygon p = create_square_poly(700,200);
    Polygon p2 = polygons[PLAYER_GON];
    V2 transl =gs.player->pos;
    V2 transl2 = {500,-100};
    translate_polygon(&p2, transl);
    translate_polygon(&p, transl2);
    
    draw_polygon(&p);
    
    ColResolve res;.
    
    SAT_resolve(&p2, &p, &res);
    if(res.col)
    {
        gs.player->pos = v2_add(gs.player->pos, res.adjust);
        gs.player->grounded = true;
        translate_polygon(&p2, res.adjust);
    }
    
    
    draw_polygon(&p);
    draw_polygon(&p2);
    */
    
    if(gi->controller.action_left.ended_down)
    {
        gs.z_location += 1.0f;
    }
    
    //calc scale
    
    gs.scale = (i32) (gs.z_location - gs.level_z) *10;
    gs.hscale = (i32) (gs.z_location - gs.level_z) *10;
    
    rd.cam.x+= 1;
    
    update_entities();
    update_sprites();
    static_collisions();
    draw_entities();
    
    draw_tiles();
    
    //draw_bounding_boxs();
    render();
}


void
game_cleanup()
{
    //todo cleanup
}