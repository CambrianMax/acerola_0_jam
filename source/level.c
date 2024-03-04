


void load_level(i32 id)
{
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
                f32 hh = (f32)height->valueint/2.0f;
                f32 wh = (f32)width->valueint/2.0f;
                add_s_collision_entity((f32)x->valueint + wh,((gs.level_dim_y*TILE_SIZE) - y->valueint - (hh)),wh , hh);
            }
        }
    }
    cJSON_Delete(level_json);
    free(level);
}