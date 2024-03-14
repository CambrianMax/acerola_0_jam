
void stop_music()
{
    Mix_HaltMusic();
    free_music(gs.music_id);
    gs.playing_music = false;
    gs.requested_music = INVALID_MUS;
    gs.music_id = INVALID_MUS;
    gs.music_faded = true;
}

void abrupt_music_change(i32 id)
{
    if(gs.music_id == id && gs.playing_music)
        return;
    gs.requested_music = id;
    gs.playing_music = true;
    Mix_HaltMusic();
    free_music(gs.music_id);
    
    load_music(gs.requested_music);
    gs.music_id = gs.requested_music;
    Mix_PlayMusic(music_assets[gs.music_id].mus, -1);
    gs.music_faded = false;
}

void
change_music()
{
    if(!gs.playing_music && gs.requested_music != INVALID_MUS)
    {
        
        load_music(gs.requested_music);
        gs.music_id = gs.requested_music;
        Mix_PlayMusic(music_assets[gs.music_id].mus, -1);
        gs.playing_music = true;
        gs.music_faded = false;
    }
    
    if(gs.music_id == gs.requested_music)
        return;
    
    f32 fade_time = 1500;
    if(!gs.music_faded)
    {
        Mix_FadeOutMusic(fade_time);
        gs.music_faded = true;
        gs.music_fade_timer = fade_time;
    }
    else
    {
        gs.music_fade_timer += -gi->elapsed_seconds * 1000;
        if(gs.music_fade_timer < 0.0f)
        {
            Mix_HaltMusic();
            free_music(gs.music_id);
            
            load_music(gs.requested_music);
            gs.music_id = gs.requested_music;
            Mix_PlayMusic(music_assets[gs.music_id].mus, -1);
            gs.music_faded = false;
        }
    }
}

void transition()
{
    
    if(gs.faded)
    {
        gs.black_alpha += gi->elapsed_seconds * 3;;
        if(gs.black_alpha >= 1.0f)
        {
            gs.faded = false;
        }
    }
    
    if(!gs.transition)
        return;
    
    if(!gs.faded)
    {
        gs.black_alpha += -gi->elapsed_seconds * 3;
        if(gs.black_alpha <= 0.0f)
        {
            gs.faded = true;
            gs.transition = false;
            room_warp();
        }
    }
}


void setup_intro()
{
    clear_entities();
    prepare_warp(BED_RM, 300, 450);
    //prepare_warp(TREE_RM, 300, 450);
    //add_player_entity(100,100);
    //load_level(BED_RM);
    //load_level(WITCH_RM);
    //play_music(BINKS_HOUSE_MUS);
}

void
game_init()
{
    load_all_sfx();
    load_image(TEST_IMG);
    load_image(TITLE_IMG);
    load_image(FNASTY_IMG);
    load_font(TEST_FNT);
    
    
    rd.cam.x = SCREEN_WIDTH /2;
    rd.cam.y = SCREEN_HEIGHT/2;
    rd.cam.width = SCREEN_WIDTH;
    rd.cam.height = SCREEN_HEIGHT;
    //play_music(BINKS_HOUSE_MUS);
    
    
    
    
    
    gs.black_alpha = -1.0f;
    Entity* t = add_decor_entity(-300,2000,TITLE_SPR);
    t->scale = 2.5f;
    Entity *bg = add_decor_entity(384,0,TITLE_BG_SPR);
    
    bg->d_layer = FLOOR_TILE;
    
    
    Entity* texty = add_texty_entity(400, 100,INIT_D);
    texty->subtype = INIT_SCREEN;
    play_music(INTRO_MUS);
    
    gs.faded = true;
}


void 
game_update(GameInput *game_input)
{
    gi = game_input;
    gs.total_time += gi->elapsed_seconds;
    pre_render();
    
    //toggle platforming
    if(gi->controller.start.pressed)
    {
        //gs.platform_mode = !gs.platform_mode;
        //start_dialouge(WITCH_1_D, WITCH_3_D);
    }
    update_dialouge();
    update_entities();
    update_sprites();
    static_collisions();
    remove_dead_entities();
    
    transition();
    change_music();
    
    draw_tiles();
    draw_entities();
    
    draw_black_screen();
    //draw_bounding_boxs();
    update_dialouge();
    
    update_cam_location();
    
    render();
}


void
game_cleanup()
{
    //todo cleanup
}