


GLuint create_shader_gl(const char* vertex_shader, const char* fragment_shader)
{
    
    //for debuging
    //GLchar log_test [50000];
    //GLsizei size;
    GLenum err = GL_NO_ERROR;
    err =  glGetError();
    GLuint vert_shader, frag_shader, shader_id;
    
    
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource( vert_shader, 1, &vertex_shader, NULL);
    glCompileShader(vert_shader);
    err =  glGetError();
    
    
    
    //glGetShaderInfoLog(vert_shader, 50000, &size, log_test);
    
    
    GLint success = 0;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    err =  glGetError();
    
    Assert(success != GL_FALSE);
    
    
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( frag_shader, 1, &fragment_shader, NULL);
    glCompileShader(frag_shader);
    //glGetShaderInfoLog(frag_shader, 50000, &size, log_test);
    err =  glGetError();
    
    
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    
    err =  glGetError();
    
    Assert(success != GL_FALSE);
    
    
    shader_id = glCreateProgram();
    
    //glGetProgramInfoLog(shader_id, 50000, &size, log_test);
    //err =  glGetError();
    
    glAttachShader(shader_id, vert_shader);
    
    //glGetProgramInfoLog(shader_id, 50000, &size, log_test);
    //err =  glGetError();
    
    glAttachShader(shader_id, frag_shader);
    
    //glGetProgramInfoLog(shader_id, 50000, &size, log_test);
    //err =  glGetError();
    
    glLinkProgram(shader_id);
    
    //glGetProgramInfoLog(shader_id, 50000, &size, log_test);
    //glGetShaderInfoLog(frag_shader, 50000, &size, log_test);
    //err =  glGetError();
    
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    err =  glGetError();
    
    
    Assert(success != GL_FALSE);
    
    return shader_id;
}



void init_gl()
{
    
    
    // Set clear color
    glClearColor(0.0f, 0.4f, 0.4f, 1.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // Compile shaders
    rd.shaders[STANDARD_SHADER] = create_shader_gl(vs_standard, fs_standard);
    rd.shaders[LINE_SHADER] = create_shader_gl(vs_line, fs_line);
    
    unsigned int indices[ NUM_INDICES * MAX_RENDER_COMMANDS] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    for(u32 i = 0; i < MAX_RENDER_COMMANDS; i++ )
    {
        indices[i * 6] = i * 4 + 0;
        indices[i * 6 + 1] = i * 4 + 1;
        indices[i * 6 + 2] = i * 4 + 3;
        indices[i * 6 + 3] = i * 4 + 1;
        indices[i * 6 + 4] = i * 4 + 2;
        indices[i * 6 + 5] = i * 4 + 3;
    }
    
    glGenVertexArrays(1, &rd.VAO);
    glGenBuffers(1, &rd.VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, rd.VBO);
    glBufferData(GL_ARRAY_BUFFER, SINGLE_DRAW_SIZE * MAX_RENDER_COMMANDS, 
                 NULL, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &rd.EBO);
    
    glBindVertexArray(rd.VAO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    
    glBindVertexArray(rd.VAO);
    
    
    rd.shader_uniforms.standard_model = glGetUniformLocation( rd.shaders[STANDARD_SHADER], "model" );
    rd.shader_uniforms.standard_proj = glGetUniformLocation( rd.shaders[STANDARD_SHADER], "proj" );
    
    rd.shader_uniforms.line_model = glGetUniformLocation( rd.shaders[LINE_SHADER], "model" );
    rd.shader_uniforms.line_proj = glGetUniformLocation( rd.shaders[LINE_SHADER], "proj" );
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, NUM_DRAW_FLOATS * sizeof(f32),
                          (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  NUM_DRAW_FLOATS * sizeof(f32),
                          (GLvoid*)(2 * sizeof(GLfloat)));
    
}





void free_font(FontId id)
{
    FontAsset* fnt = get_font_asset(id);
    if(fnt->loaded == false)
        return;
    
    free(fnt->char_data);
    free(fnt->kern_data);
    glDeleteTextures(1, &fnt->gpu_info);
    fnt->gpu_info = 0;
    fnt->loaded = false;
}


void load_font(FontId id)
{
    FontAsset* fnt = get_font_asset(id);
    if(fnt->loaded)
        return;
    
    void* font_data = read_file(fnt->filename);
    
    
    stbtt_fontinfo stb_font;
    stbtt_InitFont(&stb_font, font_data, 0);
    fnt->scale = stbtt_ScaleForPixelHeight(&stb_font, FONT_SIZE);
    
    
    stbtt_GetFontVMetrics(&stb_font, &fnt->ascent, &fnt->descent, &fnt->line_gap);
    fnt->ascent = fnt->ascent * fnt->scale;
    fnt->descent = fnt->descent * fnt->scale;
    fnt->line_gap = fnt->line_gap * fnt->scale;
    fnt->line_advance = fnt->ascent - fnt->descent + fnt->line_gap;
    
    stbtt_bakedchar *char_data = (stbtt_bakedchar*)malloc(TOTAL_GLYPHS * sizeof(stbtt_bakedchar));
    r32* kern_data = (r32*)malloc(TOTAL_GLYPHS * TOTAL_GLYPHS * sizeof(r32));
    unsigned char* mono_bitmap_data = (unsigned char*)malloc(FONT_ATLAS_WIDTH * FONT_ATLAS_HIEGHT * sizeof(unsigned char));
    
    stbtt_BakeFontBitmap(font_data, 0, FONT_SIZE, mono_bitmap_data, FONT_ATLAS_WIDTH, FONT_ATLAS_HIEGHT, START_GLYPH, TOTAL_GLYPHS, char_data); // no guarantee this fits!
    
    
    
    u32 char_count_y = 0;
    u32 char_count_x = 0;
    for(char prev_char = START_GLYPH; prev_char < END_GLYPH +1;
        prev_char++)
    {
        for(char cur_char = START_GLYPH; cur_char < END_GLYPH +1;
            cur_char++)
        {
            i32 kern = (i32)stbtt_GetCodepointKernAdvance(&stb_font, (char)prev_char, (char)cur_char);
            kern_data[(char_count_y * TOTAL_GLYPHS) + char_count_x] = fnt->scale * (r32)kern;
            char_count_x ++;
            
            /*
            if(kern != 0)
            {
                
                printf("Char %c ", prev_char);
                printf("to Char %c", cur_char);
                printf(" have a kern of %d", kern);
                printf(" with a scaled value of %f!",(r32)kern * fnt->scale);
                printf(" It is at index %d! Total glphy: %d, y %d, x %d\n",(char_count_y * TOTAL_GLYPHS) + char_count_x, TOTAL_GLYPHS, char_count_y, char_count_x);
            }
            */
        }
        char_count_x = 0;
        char_count_y++;
    }
    
    SDL_Surface* atlas = SDL_CreateRGBSurface(0,FONT_ATLAS_WIDTH,FONT_ATLAS_HIEGHT,32,0,0,0,0);
    uint8 *source = (u8*)mono_bitmap_data;
    uint32 pitch = FONT_ATLAS_WIDTH * BITMAP_BYTES_PER_PIXEL;
    SDL_LockSurface(atlas);
    uint8 *dest_row = (uint8 *)atlas->pixels + (FONT_ATLAS_HIEGHT - 1) * pitch ;
    for(uint32 y = 0; y < FONT_ATLAS_HIEGHT; ++y)
    {
        uint32 *dest = (uint32 *)dest_row;
        for(uint32 x = 0; x < FONT_ATLAS_WIDTH; ++x)
        {
            uint8 alpha = *source ++; 
            *dest++ =((alpha << 24) |
                      (alpha << 16) |
                      (alpha << 8)  |
                      (alpha << 0));
        }
        dest_row -= pitch;
    }
    SDL_UnlockSurface(atlas);
    
    
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FONT_ATLAS_WIDTH, FONT_ATLAS_HIEGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas->pixels);
    
    // Set texture parameters (we need all these or these won't work)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    fnt->width = atlas->w;
    fnt->height = atlas->h;
    SDL_FreeSurface(atlas);
    
    fnt->kern_data = kern_data;
    fnt->char_data = char_data;
    free(mono_bitmap_data);
    free(font_data);
    
    fnt->gpu_info = texture;
    fnt->loaded = true;
    
    
}



void free_image(ImageId id)
{
    ImageAsset* img = get_image_asset(id);
    if(img->loaded == false)
        return;
    glDeleteTextures(1, &img->gpu_info);
    img->width = 0;
    img->height = 0;
    img->gpu_info = 0;
    img->loaded = false;
}

void flip_surface(SDL_Surface* surface) 
{
    SDL_LockSurface(surface);
    
    i32 pitch = surface->pitch; 
    char* temp = malloc(sizeof(char) * pitch);
    char* pixels = (char*) surface->pixels;
    
    for(i32 i = 0; i < surface->h / 2; ++i) {
        char* row1 = pixels + i * pitch;
        char* row2 = pixels + (surface->h - i - 1) * pitch;
        
        // swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }
    
    free(temp);
    SDL_UnlockSurface(surface);
}


void load_image(ImageId id)
{
    ImageAsset* img = get_image_asset(id);
    if(img->loaded)
        return;
    SDL_Surface *surface = IMG_Load(img->filename);
    if (!surface) {
        printf("Error loading image: %s\n", SDL_GetError());
        Assert(false);
    }
    SDL_Surface *converted_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    flip_surface(converted_surface);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, converted_surface->w, converted_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, converted_surface->pixels);
    
    
    // Set texture parameters (we need all these or these won't work)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    img->height = converted_surface->h;
    img->width = converted_surface->w;
    SDL_FreeSurface(converted_surface); 
    SDL_FreeSurface(surface);
    
    img->gpu_info = texture;
    img->loaded = true;
}



void
set_shader_uniforms(u32 id, Mat4* model, Mat4* proj)
{
    switch(id)
    {
        case STANDARD_SHADER:
        {
            glUniformMatrix4fv(rd.shader_uniforms.standard_model, 1, GL_FALSE, model->elements);
            glUniformMatrix4fv(rd.shader_uniforms.standard_proj, 1, GL_FALSE, proj->elements);
        }break;
        case LINE_SHADER:
        {
            glUniformMatrix4fv(rd.shader_uniforms.line_model, 1, GL_FALSE, model->elements);
            glUniformMatrix4fv(rd.shader_uniforms.line_proj, 1, GL_FALSE, proj->elements);
        }break;
    }
}

#define GL_TEXTURE_PERVERSION 0.0

void
batch_render(u32 count, u32 shader_id)
{
    
    
    glBindBuffer(GL_ARRAY_BUFFER, rd.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, SINGLE_DRAW_SIZE * count,
                    rd.gpu_buffer);
    
    glBindVertexArray(rd.VAO);
    if(shader_id == LINE_SHADER)
        glDrawElements(GL_LINES, 6 * count, GL_UNSIGNED_INT, 0);
    else
        glDrawElements(GL_TRIANGLES, 6 * count, GL_UNSIGNED_INT, 0);
    
}


void
pre_render()
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




void render()
{
    
    Mat4 model = mat4_identity;
    
    model = mat4_translate(&model, &(V3){-rd.cam.x + (rd.cam.width)/2., -rd.cam.y  + (rd.cam.height)/2.0});
    
    
    Mat4 proj = mat4_ortho(0.0f, SCREEN_WIDTH, 0.0f , SCREEN_HEIGHT, -1.0f, 1.0f);
    
    
    i32 tex_width = 0;
    i32 tex_height = 0;
    
    u32 curr_tex = 0;
    u32 curr_shader = 0;
    u32 batch_count = 0;
    u32 last_color  = 0;
    
    RenderCommand *rc = &rd.draws[0];
    if(rd.render_count > 0)
    {
        curr_tex = rc->tex_sheet;
        curr_shader = rc->shader_id;
        glUseProgram(rd.shaders[curr_shader]);
        glBindTexture(GL_TEXTURE_2D, rc->tex_sheet);
        set_shader_uniforms(curr_shader, &model, &proj);
        set_image_dim(rc->img_type, rc->asset_id, &tex_width, &tex_height);
        
    }
    
    for(u32 i = 0; i < rd.render_count; i++)
    {
        
        rc = &rd.draws[i];
        
        if(rc->tex_sheet != curr_tex || rc->shader_id != curr_shader )
        {
            batch_render(batch_count, curr_shader);
            
            curr_tex = rc->tex_sheet;
            curr_shader = rc->shader_id;
            glUseProgram(rd.shaders[curr_shader]);
            glBindTexture(GL_TEXTURE_2D, rc->tex_sheet);
            set_shader_uniforms(curr_shader, &model, &proj);
            set_image_dim(rc->img_type, rc->asset_id, &tex_width, &tex_height);
            batch_count = 0;
            
        }
        
        
        f32 *vertices_offset = &rd.gpu_buffer[batch_count * NUM_DRAW_FLOATS * 4];
        switch(curr_shader)
        {
            
            case STANDARD_SHADER: {
                
                f32 vertice_temp [] = 
                {
                    // pos                // tex
                    rc->x_max, rc->y_max, (rc->t_x1) / tex_width, 1.0f-(rc->t_y0/ tex_height), rc->alpha ,
                    rc->x_max, rc->y_min, (rc->t_x1) / tex_width, 1.0f-(rc->t_y1 / tex_height), rc->alpha,
                    rc->x_min, rc->y_min, (rc->t_x0) / tex_width, 1.0f-(rc->t_y1 / tex_height), rc->alpha,
                    rc->x_min, rc->y_max, (rc->t_x0) / tex_width, 1.0f-(rc->t_y0 / tex_height), rc->alpha,
                    
                };
                
                
                memcpy(vertices_offset,vertice_temp, SINGLE_DRAW_SIZE);
            }break;
            case LINE_SHADER:
            {
                
                V3 color = colors[rc->color];
                //kinda wasting space for lines...
                f32 vertice_temp [] = 
                {
                    // pos                // tex
                    rc->x_min, rc->y_min, color.x, color.y, color.z ,
                    rc->x_max, rc->y_max, color.x, color.y, color.z,
                    rc->x_max, rc->y_max, color.x, color.y, color.z,
                    rc->x_max, rc->y_max, color.x, color.y, color.z,
                    
                };
                
                memcpy(vertices_offset,vertice_temp, SINGLE_DRAW_SIZE);
            }break;
            
        }
        ++batch_count;
    }
    
    batch_render(batch_count, curr_shader);
    
    
    rd.render_count = 0;
}


void draw_quad(f32 x_min, f32 y_min, f32 x_max, f32 y_max, f32 alpha, ImageType img_type, u32 asset_id, u32 shader_id,  SpecialRenderInfo render_info)
{
    
    if(rd.render_count >= MAX_RENDER_COMMANDS)
        return;
    
    
    RenderCommand* rc = &rd.draws[rd.render_count];
    
    rc->x_min = x_min;
    rc->x_max = x_max;
    rc->y_min = y_min;
    rc->y_max = y_max;
    rc->alpha = alpha;
    rc->shader_id = shader_id;
    rc->img_type = img_type;
    rc->asset_id = asset_id;
    
    
    switch(img_type)
    {
        case TILE_IMAGE:
        {
            
            
            ImageAsset* img = &image_assets[asset_id];
            i32 id = render_info.spr_info.id;
            
            rc->t_x0 = (id % gs.level_dim_y) * TILE_SIZE;
            rc->t_x1 = rc->t_x0 + TILE_SIZE;
            rc->t_y0 = ((id / gs.level_dim_x)) * TILE_SIZE;
            rc->t_y1 = rc->t_y0 +  TILE_SIZE;
            //rc->t_y0 = (gs.level_dim_y -  (id / gs.level_dim_x) - 1) * TILE_SIZE;
            //rc->t_y1 = rc->t_y0 + TILE_SIZE;
            rc->tex_sheet = img->gpu_info;
            
        }break;
        case SPRITE_IMAGE:
        {
            const Sprite* spr = &sprites[render_info.spr_info.id];
            ImageAsset* img = &image_assets[spr->image_id];
            i32 max_per_first_row = ((img->width - spr->offset_x )/ spr->width);
            i32 max_per_row = img->width / spr->width;
            i32 x_frame = render_info.spr_info.frame;
            i32 row = 0;
            if(x_frame >= max_per_first_row)
            {
                row += 1;
                x_frame += -(max_per_first_row);
                if(x_frame >= max_per_row)
                {
                    row += x_frame / (max_per_row);
                    x_frame = x_frame % (max_per_row);
                }
                
            }
            
            rc->t_x0 = spr->offset_x + x_frame * spr->width;
            
            rc->t_x1 = rc->t_x0 + spr->width ;
            rc->t_y0 = row * spr->height + spr->offset_y;
            rc->t_y1 = rc->t_y0 + spr->height;
            rc->tex_sheet = img->gpu_info;
        }break;
        case FONT_IMAGE:
        {
            FontAsset *fnt = &font_assets[asset_id];
            stbtt_bakedchar* gly = &fnt->char_data[render_info.char_index];
            rc->t_x0 = gly->x0;
            rc->t_x1 = gly->x1;
            rc->t_y0 = gly->y0;
            rc->t_y1 = gly->y1;
            rc->tex_sheet = fnt->gpu_info;
            
        }break;
        
    }
    
    
    
    //rc->depth = depth;
    
    ++rd.render_count;
}


b32 is_descender_glyph(char c)
{
    switch(c)
    {
        case 'j': return true;
        case 'g': return true;
        case 'p': return true;
        case 'q': return true;
        case 'y': return true;
        default: return false;
    }
}


void 
draw_text(r32 x, r32 y, r32 scale, FontId id, char* text)
{
    
    FontAsset* fnt = &font_assets[id];
    r32 total_advance_x = x;
    r32 total_advance_y = y;
    b32 texting = true;
    u32 i = 0;
    char prev_char_index = text[0]-START_GLYPH;
    while(texting)
    {
        switch(text[i])
        {
            case '\0':
            {
                texting = false;
            }break;
            case '\n':
            {
                total_advance_x = x;
                total_advance_y += (-fnt->ascent + fnt->descent -fnt->line_gap) * scale;
                
            }break;
            case ' ':
            {
                
                
                u32 char_index = text[i] - START_GLYPH;
                stbtt_bakedchar* char_info = &fnt->char_data[char_index];
                
                total_advance_x += char_info->xadvance *scale;
                
            }break;
            default:
            {
                u32 char_index = text[i] - START_GLYPH;
                stbtt_bakedchar* char_info = &fnt->char_data[char_index];
                r32 width = (char_info->x1 - char_info->x0) * scale;
                r32 height = (char_info->y1 - char_info->y0) * scale;
                r32 descent = 0;
                if(is_descender_glyph(text[i]))
                    descent =  fnt->descent * scale;
                
                
                total_advance_x += fnt->kern_data[prev_char_index*TOTAL_GLYPHS+char_index]*scale;
                //r32 kern = fnt->kern_data[prev_char_index*TOTAL_GLYPHS+char_index]*scale;
                //if(kern != 0 )
                //printf("\n\nkern:%c %c %d",(char)(prev_char_index + START_GLYPH),text[i],(i32)kern);
                
                
                draw_quad(total_advance_x, total_advance_y + descent, total_advance_x + width, total_advance_y + height + descent, 0.0, FONT_IMAGE, id, STANDARD_SHADER, (SpecialRenderInfo){.char_index = char_index});
                
                total_advance_x += width;
                prev_char_index = char_index;
            }break;
        }
        ++i;
    }
}

void
draw_sprite(f32 x, f32 y, ZoomEffect z_effect, SpriteId id, u32 frame)
{
    
    
    f32 scale = 0;
    f32 hscale = 0;
    if(z_effect == DOWN_ZOOM)
    {
        scale = gs.scale;
        hscale = gs.hscale;
        
        
        const Sprite* spr = &sprites[id];
        draw_quad(x - ((f32)spr->width/2) - hscale, y - hscale - scale, x + ((f32)spr->width/2) +hscale, y + spr->height  - scale, 0, SPRITE_IMAGE, spr->image_id, STANDARD_SHADER, (SpecialRenderInfo){.spr_info = {id, frame}});
    }
    else if(z_effect == NORMAL_ZOOM)
    {
        scale = gs.scale;
        hscale = gs.hscale;
        
        
        const Sprite* spr = &sprites[id];
        draw_quad(x - ((f32)spr->width/2) - hscale, y -hscale, x + ((f32)spr->width/2) +hscale, y + spr->height + hscale, 0, SPRITE_IMAGE, spr->image_id, STANDARD_SHADER, (SpecialRenderInfo){.spr_info = {id, frame}});
    }
    else
    {
        
        const Sprite* spr = &sprites[id];
        draw_quad(x - ((f32)spr->width/2) - hscale, y - hscale - scale, x + ((f32)spr->width/2) +hscale, y + spr->height  - scale, 0, SPRITE_IMAGE, spr->image_id, STANDARD_SHADER, (SpecialRenderInfo){.spr_info = {id, frame}});
    }
}

void
draw_entity(Entity *e)
{
    if(e->invisible)
        return;
    //draw_sprite(e->pos.x, e->pos.y, e->sprite_id, e->frame);
    ZoomEffect z_effect = DOWN_ZOOM;
    if(e->type == PLAYER_ENT)
        z_effect= NO_ZOOM;
    if(e->type == PARALAX_ENT && e->z_location > gs.z_location)
        z_effect= NORMAL_ZOOM;
    draw_sprite(e->aabb.pos.x, e->aabb.pos.y - e->aabb.half_size.y, z_effect,  e->sprite_id, e->frame);
}

void draw_entities()
{
    entities_apply(&draw_entity);
}


void draw_line(V2 p0, V2 p1, u32 color)
{
    
    if(rd.render_count >= MAX_RENDER_COMMANDS)
        return;
    
    
    RenderCommand* rc = &rd.draws[rd.render_count];
    
    rc->x_min = p0.x;
    rc->x_max = p1.x;
    rc->y_min = p0.y;
    rc->y_max = p1.y;
    //rc->alpha = alpha;
    rc->shader_id = LINE_SHADER;
    rc->color = color;
    
    //rc->depth = depth;
    
    ++rd.render_count;
}

/*
void
draw_polygon(Polygon* p)
{
    if(p->num_points < 2)
        return;
    for(i32 p0 = 0; p0 < p->num_points -1; p0++)
    {
        i32 p1 = p0+1;
        draw_line(p->points[p0], p->points[p1],M_RED);
    }
    
    draw_line(p->points[p->num_points -1], p->points[0], M_RED);
}
*/


void
draw_bounding_box(Entity *e)
{
    /*
    V2 p0 = {e->pos.x - e->dim.x/2.0f,e->pos.y};
    V2 p1 = {e->pos.x + e->dim.x/2.0f,e->pos.y};
    V2 p2 = {e->pos.x + e->dim.x/2.0f,e->pos.y+e->dim.y};
    V2 p3 = {e->pos.x - e->dim.x/2.0f,e->pos.y+e->dim.y};
    */
    
    //V2 p0 = {e->aabb.pos.x - e->aabb.half_size.x,e->aabb.pos.y};
    //V2 p1 = {e->aabb.pos.x + e->aabb.half_size.x,e->aabb.pos.y};
    //V2 p2 = {e->aabb.pos.x + e->aabb.half_size.x,e->aabb.pos.y+e->aabb.half_size.y*2};
    //V2 p3 = {e->aabb.pos.x - e->aabb.half_size.x,e->aabb.pos.y+e->aabb.half_size.y*2};
    
    V2 p0 = {e->aabb.pos.x - e->aabb.half_size.x,e->aabb.pos.y - e->aabb.half_size.y};
    V2 p1 = {e->aabb.pos.x + e->aabb.half_size.x,e->aabb.pos.y - e->aabb.half_size.y};
    V2 p2 = {e->aabb.pos.x + e->aabb.half_size.x,e->aabb.pos.y+e->aabb.half_size.y};
    V2 p3 = {e->aabb.pos.x - e->aabb.half_size.x,e->aabb.pos.y+e->aabb.half_size.y};
    
    
    draw_line(p0, p1,M_RED);
    draw_line(p1, p2,M_RED);
    draw_line(p2, p3,M_RED);
    draw_line(p3, p0,M_RED);
}

void draw_bounding_boxs()
{
    for(i32 i = 0; i < gs.num_entities; i++)
        draw_bounding_box(&gs.entities[i]);
}




void draw_tiles()
{
    f32 scale = gs.scale;
    f32 hscale = gs.hscale;
    
    for(i32 y = 0; y < gs.level_dim_y; y++)
    {
        for(i32 x = 0; x < gs.level_dim_x; x++)
        {
            i32 id = gs.tiles[x + (y * gs.level_dim_x)];
            if(id == 0)
                continue;
            else
                id += -1;
            
            draw_quad(x *TILE_SIZE  - hscale, (gs.level_dim_y - y -1 ) * TILE_SIZE  -scale - hscale, x *TILE_SIZE + TILE_SIZE +hscale, (gs.level_dim_y - y) * TILE_SIZE - scale , 0, TILE_IMAGE, TEST_IMG, STANDARD_SHADER, (SpecialRenderInfo){.spr_info = {id, 0}});
        }
        
    }
    
}



