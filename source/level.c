
void clear_tiles()
{
    
    for(i32 y = 0; y < gs.level_dim_y; y++)
    {
        for(i32 x = 0; x < gs.level_dim_x; x++)
        {
            i32 id = x + (y * gs.level_dim_x);
            gs.tiles[id] = 0;
            gs.top_tiles[id] = 0;
        }
    }
}

void load_level(i32 id)
{
    clear_tiles();
    char* level = (char*)read_file(levels[id]);
    u32 level_size = get_file_size(levels[id]);
    
    cJSON* level_json = cJSON_Parse(level);
    assert(level_json != NULL);
    
    const cJSON *layers = cJSON_GetObjectItemCaseSensitive(level_json, "layers");
    const cJSON* layer = NULL;
    cJSON_ArrayForEach(layer, layers)
    {
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(layer, "name");
        if(!strcmp(name->valuestring,"middle"))
        {
            
            
            const cJSON* width = cJSON_GetObjectItemCaseSensitive(layer, "width");
            const cJSON* height = cJSON_GetObjectItemCaseSensitive(layer, "height");
            gs.level_dim_x = width->valueint;
            gs.level_dim_y = height->valueint;
            gs.tile_count = gs.level_dim_x* gs.level_dim_y;
            
            const cJSON* tiles = cJSON_GetObjectItemCaseSensitive(layer, "data");
            const cJSON* tile = NULL;
            
            i32 count = 0;
            cJSON_ArrayForEach(tile, tiles)
            {
                gs.tiles[count] = tile->valueint;
                ++count;
                assert(count < TOTAL_TILES);
            }
            
        }
    }
    
    cJSON_ArrayForEach(layer, layers)
    {
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(layer, "name");
        if(!strcmp(name->valuestring,"top"))
        {
            
            
            const cJSON* width = cJSON_GetObjectItemCaseSensitive(layer, "width");
            const cJSON* height = cJSON_GetObjectItemCaseSensitive(layer, "height");
            
            
            const cJSON* tiles = cJSON_GetObjectItemCaseSensitive(layer, "data");
            const cJSON* tile = NULL;
            
            i32 count = 0;
            cJSON_ArrayForEach(tile, tiles)
            {
                gs.top_tiles[count] = tile->valueint;
                ++count;
                assert(count < TOTAL_TILES);
            }
            
        }
    }
    
    
    cJSON_ArrayForEach(layer, layers){
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(layer, "name");
        if (!strcmp(name->valuestring,"collision_boxs"))
        {
            
            const cJSON* boxs = cJSON_GetObjectItemCaseSensitive(layer, "objects");
            const cJSON* box = NULL;
            cJSON_ArrayForEach(box, boxs)
            {
                
                const cJSON* height = cJSON_GetObjectItemCaseSensitive(box, "height");
                const cJSON* width = cJSON_GetObjectItemCaseSensitive(box, "width");
                const cJSON* x = cJSON_GetObjectItemCaseSensitive(box, "x");
                const cJSON* y = cJSON_GetObjectItemCaseSensitive(box, "y");
                const cJSON* box_name = cJSON_GetObjectItemCaseSensitive(box, "name");
                f32 hh = (f32)height->valueint/2.0f;
                f32 wh = (f32)width->valueint/2.0f;
                
                if(!strcmp(box_name->valuestring,"TELE"))
                {
                    const cJSON* props = cJSON_GetObjectItemCaseSensitive(box, "properties");
                    const cJSON* tele_x = NULL; 
                    const cJSON* tele_y = NULL; 
                    const cJSON* tele_room = NULL; 
                    const cJSON* prop = NULL; 
                    cJSON_ArrayForEach(prop, props)
                    {
                        const cJSON* box_prop_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                        if(!strcmp(box_prop_name->valuestring,"room"))
                            tele_room = cJSON_GetObjectItemCaseSensitive(prop, "value");
                        else if(!strcmp(box_prop_name->valuestring,"x"))
                            tele_x = cJSON_GetObjectItemCaseSensitive(prop, "value");
                        else if(!strcmp(box_prop_name->valuestring,"y"))
                            tele_y = cJSON_GetObjectItemCaseSensitive(prop, "value");
                    }
                    
                    add_t_collision_entity((f32)x->valueint + wh,((gs.level_dim_y*TILE_SIZE) - y->valueint - (hh)),wh , hh, room_id_lookup(tele_room->valuestring), tele_x->valueint, tele_y->valueint);
                }
                else
                {
                    add_s_collision_entity((f32)x->valueint + wh,((gs.level_dim_y*TILE_SIZE) - y->valueint - (hh)),wh , hh);
                }
            }
        }
        
    }
    char* ent_layer = "entities";
    if(gs.platform_mode)
        ent_layer = "entities_2";
    cJSON_ArrayForEach(layer, layers){
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(layer, "name");
        if (!strcmp(name->valuestring,ent_layer))
        {
            const cJSON* ents = cJSON_GetObjectItemCaseSensitive(layer, "objects");
            const cJSON* ent  = NULL;
            cJSON_ArrayForEach(ent, ents)
            {
                
                i32 x = cJSON_GetObjectItemCaseSensitive(ent, "x")->valueint;
                i32 y = cJSON_GetObjectItemCaseSensitive(ent, "y")->valueint;
                y = (gs.level_dim_y*TILE_SIZE - y);
                
                const cJSON* props = cJSON_GetObjectItemCaseSensitive(ent, "properties");
                const cJSON* prop = NULL;
                EntityType ent_type = 0;
                cJSON_ArrayForEach(prop, props)
                {
                    const cJSON* ent_type_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                    if(!strcmp(ent_type_name->valuestring,"ent_type"))
                    {
                        const cJSON* ent_type_value = cJSON_GetObjectItemCaseSensitive(prop, "value");
                        if(!strcmp(ent_type_value->valuestring,"dialouge"))
                            ent_type = DIALOUGE_ENT;
                        else if(!strcmp(ent_type_value->valuestring,"decor"))
                            ent_type = DECOR_ENT;
                        else if(!strcmp(ent_type_value->valuestring,"destructible"))
                            ent_type = DESTRUCTIBLE_ENT;
                        else if(!strcmp(ent_type_value->valuestring,"misc"))
                            ent_type = MISC_ENT;
                    }
                }
                switch(ent_type)
                {
                    case DIALOUGE_ENT:
                    {
                        cJSON_ArrayForEach(prop, props)
                        {
                            const cJSON* prop_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                            if(!strcmp(prop_name->valuestring,"dialouge_id"))
                            {
                                const cJSON* dialouge_id_json = cJSON_GetObjectItemCaseSensitive(prop, "value");
                                i32 dialouge_id = str_to_dialouge_id(dialouge_id_json->valuestring);
                                add_dialouge_entity(x, y, dialouge_id);
                            }
                        }
                        
                    }break;
                    case DECOR_ENT:
                    {
                        cJSON_ArrayForEach(prop, props)
                        {
                            const cJSON* prop_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                            if(!strcmp(prop_name->valuestring,"sprite"))
                            {
                                const cJSON* sprite_id_json = cJSON_GetObjectItemCaseSensitive(prop, "value");
                                i32 sprite_id = str_to_sprite_id(sprite_id_json->valuestring);
                                if(!(sprite_id == WITCH_BLOCK_2_SPR && !gs.witch_active))
                                    add_decor_entity(x, y, sprite_id);
                            }
                        }
                        
                    }break;
                    case DESTRUCTIBLE_ENT:
                    {
                        cJSON_ArrayForEach(prop, props)
                        {
                            const cJSON* prop_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                            if(!strcmp(prop_name->valuestring,"sprite"))
                            {
                                const cJSON* sprite_id_json = cJSON_GetObjectItemCaseSensitive(prop, "value");
                                i32 sprite_id = str_to_sprite_id(sprite_id_json->valuestring);
                                add_destructible_entity(x, y, sprite_id);
                            }
                        }
                        
                    }break;
                    case MISC_ENT:
                    {
                        cJSON_ArrayForEach(prop, props)
                        {
                            const cJSON* prop_name = cJSON_GetObjectItemCaseSensitive(prop, "name");
                            if(!strcmp(prop_name->valuestring,"subtype"))
                            {
                                const cJSON* subtype_id_json = cJSON_GetObjectItemCaseSensitive(prop, "value");
                                i32 subtype_id = str_to_subtype(subtype_id_json->valuestring);
                                Entity* e = add_misc_entity(subtype_id);
                                e->aabb.pos.x = x;
                                e->aabb.pos.y = y;
                            }
                        }
                        
                    }break;
                    default:{}break;
                }
            }
        }
    }
    
    
    cJSON_Delete(level_json);
    free(level);
}

void
prepare_warp(RoomId rm_id, i32 x, i32 y)
{
    if(gs.transition)
        return;
    gs.pause_entities += 1;
    gs.pause_collision += 1;
    gs.transition = true;
    gs.faded = false;
    gs.tele_room = rm_id;
    gs.tele_x = x;
    gs.tele_y = y;
    if(!gs.witch_active)
        play_music(level_music[rm_id]);
}

void
room_warp()
{
    
    clear_entities();
    add_player_entity(gs.tele_x,gs.tele_y);
    load_level(gs.tele_room);
    gs.bink_dead = false;
    gs.pause_entities -= 1;
    gs.pause_collision -= 1;
}