

void start_dialouge(i32 start, i32 end)
{
    if(gs.dialouge_active)
        return;
    gs.pause_entities += 1;
    gs.pause_collision += 1;
    gs.dialouge_active = true;
    gs.dialouge_id = start;
    gs.dialouge_end = end;
    gs.dialouge_alpha = 1.0f;
    gs.fade_dialouge = false;
    gs.dia_info_alpha = 1.0f;
}


void update_dialouge()
{
    if(!gs.dialouge_active)
        return;
    
    if(gs.dialouge_id >= HOME_1_D)
    {
        
        set_entity_sprite(gs.player, PLAYER_PLI_SPR);
        draw_text(150,360, 1.0f,gs.dialouge_alpha, TEST_FNT, dialouge_colors[gs.dialouge_id], dialouges[gs.dialouge_id]);
    }
    else
    {
        
        set_entity_sprite(gs.player, PLAYER_RI_SPR);
        draw_text(150,300, 1.0f,gs.dialouge_alpha, TEST_FNT, dialouge_colors[gs.dialouge_id], dialouges[gs.dialouge_id]);
        
    }
    
    draw_text(550,25, 1.0f,gs.dia_info_alpha, TEST_FNT, M_WHITE, dialouges[PRESS_D]);
    if(gs.dia_info_alpha >= 0.0f)
        gs.dia_info_alpha += -gi->elapsed_seconds *2;
    
    
    if(gs.dialouge_alpha <= 0.0f && gi->controller.action_down.ended_down)
    {
        gs.dialouge_alpha =  0.0f;
        gs.fade_dialouge = true;
    }
    
    if(gs.dialouge_alpha >= 1.0f && gs.fade_dialouge)
    {
        if(gs.dialouge_id >= gs.dialouge_end)
        {
            gs.dialouge_active = false;
            gs.pause_entities += -1;
            gs.pause_collision += -1;
            if(gs.dialouge_id == WITCH_4_D)
                play_sfx(WITCH_LAUGH_SFX);
            
        }
        else
        {
            ++gs.dialouge_id;
            gs.fade_dialouge = false;
        }
    }
    
    if(gs.fade_dialouge)
        gs.dialouge_alpha = min_r32(1.0f, gs.dialouge_alpha + 1.0f* gi->elapsed_seconds);
    else
        gs.dialouge_alpha = max_r32(0.0f, gs.dialouge_alpha - 1.0f* gi->elapsed_seconds);
    
}

