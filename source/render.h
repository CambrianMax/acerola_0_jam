/* date = February 28th 2024 11:30 pm */

#ifndef RENDER_H
#define RENDER_H



#define MAX_RENDER_COMMANDS 3000
#define NUM_INDICES 6
#define QUAD_POINTS 4

#define NUM_DRAW_FLOATS 5
#define SINGLE_DRAW_SIZE NUM_DRAW_FLOATS * QUAD_POINTS * sizeof(f32)




#ifdef __EMSCRIPTEN__


const char* vs_standard =
"precision highp float;\n"
"attribute vec2 verts;\n"
"attribute vec3 tex;\n"

"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"
"uniform vec2 image_offset;\n"
"uniform vec2 image_scale;\n"
"varying vec3 pass_tex_coord;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_standard =
"precision mediump float;\n"
"varying vec3 pass_tex_coord;\n"
"uniform sampler2D img;\n"
"uniform vec3 sprite_color;\n"
"void main()\n"
"{\n"
"gl_FragColor = texture2D(img, pass_tex_coord.xy);\n"
"gl_FragColor.a += -pass_tex_coord.z;"
"}";



const char* vs_color =
"precision highp float;\n"
"attribute vec2 verts;\n"
"attribute vec3 tex;\n"

"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"
"uniform vec2 image_offset;\n"
"uniform vec2 image_scale;\n"
"varying vec3 pass_tex_coord;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_color =
"precision mediump float;\n"
"varying vec3 pass_tex_coord;\n"
"uniform vec3 color;\n"
"uniform sampler2D img;\n"
"void main()\n"
"{\n"
"gl_FragColor = vec4(1,1,1,texture2D(img, pass_tex_coord.xy).a) * vec4(color, 1.0);\n"
"gl_FragColor.a += -pass_tex_coord.z;"
"}";




const char* vs_line =
"precision highp float;\n"
"attribute vec2 vec_pos;\n"
"attribute vec3 line_color;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"
"varying vec3 pass_color;\n"
"void main()\n"
"{\n"
"pass_color = line_color;\n"
"gl_Position = proj * model * vec4(vec_pos.xy, 0.0, 1.0);\n"
"}";


const char* fs_line =
"precision mediump float;\n"
"varying vec3 pass_color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(pass_color, 1.0);\n"
"}";


const char* vs_glow =
"precision highp float;\n"
"attribute vec2 verts;\n"
"attribute vec3 tex;\n"


"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"

"varying vec3 pass_tex_coord;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_glow =
"precision mediump float;\n"
"varying vec3 pass_tex_coord;\n"

"uniform sampler2D img;\n"
"void main()\n"
"{\n"
"gl_FragColor = texture2D(img, pass_tex_coord.xy) * vec4(abs(sin(pass_tex_coord.z*1.5)), abs(sin(pass_tex_coord.z*1.5)), abs(sin(pass_tex_coord.z*1.5)), 1.0);\n"
//"final_color.a += -pass_tex_coord.z;"
"}";




#else


const char* vs_standard =
"#version 330 core\n"

"layout (location = 0) in vec2 verts;\n"
"layout (location = 1) in vec3 tex;\n"

"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"
"uniform vec2 image_offset;\n"
"uniform vec2 image_scale;\n"
"out vec3 pass_tex_coord;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_standard =
"#version 330 core\n"
"in vec3 pass_tex_coord;\n"
"out vec4 color;\n"
"uniform sampler2D img;\n"
"uniform vec3 sprite_color;\n"
"void main()\n"
"{\n"
"color = texture(img, pass_tex_coord.xy);\n"
"color.a += -pass_tex_coord.z;"
"}";




const char* vs_color =
"#version 330 core\n"

"layout (location = 0) in vec2 verts;\n"
"layout (location = 1) in vec3 tex;\n"


"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"

"uniform vec2 image_offset;\n"
"uniform vec2 image_scale;\n"
"out vec3 pass_tex_coord;\n"
"out vec3 pass_color;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_color =
"#version 330 core\n"
"in vec3 pass_tex_coord;\n"

"uniform vec3 color;\n"
"out vec4 final_color;\n"
"uniform sampler2D img;\n"
"void main()\n"
"{\n"
"final_color = vec4(1,1,1,texture(img, pass_tex_coord.xy).a) * vec4(color, 1.0);\n"
"final_color.a += -pass_tex_coord.z;"
"}";



const char* vs_line =


"#version 330 core\n"

"layout (location = 0) in vec2 vec_pos;\n"
"layout (location = 1) in vec3 line_color;\n"

"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"
"out  vec3 pass_color;\n"
"void main()\n"
"{\n"
"pass_color = line_color;\n"
"gl_Position = proj * model * vec4(vec_pos.xy, 0.0, 1.0);\n"
"}";


const char* fs_line =
"#version 330 core\n"
"in vec3 pass_color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(pass_color, 1.0);\n"
"}";




const char* vs_glow =
"#version 330 core\n"

"layout (location = 0) in vec2 verts;\n"
"layout (location = 1) in vec3 tex;\n"


"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 proj;\n"

"out vec3 pass_tex_coord;\n"
"void main()\n"
"{\n"
"pass_tex_coord = tex;\n"
"gl_Position =  proj * model * vec4(verts.xy, 0.0, 1.0);\n"
"}";


const char* fs_glow =
"#version 330 core\n"
"in vec3 pass_tex_coord;\n"

"out vec4 final_color;\n"
"uniform sampler2D img;\n"
"void main()\n"
"{\n"
"final_color = texture(img, pass_tex_coord.xy) * vec4(abs(sin(pass_tex_coord.z*1.5)), abs(sin(pass_tex_coord.z*1.5)), abs(sin(pass_tex_coord.z*1.5)), 1.0);\n"
//"final_color.a += -pass_tex_coord.z;"
"}";



#endif







/*
const char* fs_color =
"precision mediump float;\n"
"varying vec3 pass_tex_coord;\n"
"varying vec3 color;\n"
"uniform sampler2D img;\n"
"void main()\n"
"{\n"
"gl_FragColor = vec4(1,1,1,texture(img, pass_tex_coord.xy).a) * vec4(color, 1.0);\n"
"}";

*/






typedef enum
{
    STANDARD_SHADER,
    COLOR_SHADER,
    LINE_SHADER,
    GLOW_SHADER,
    
    TOTAL_SHADERS,
}ShaderId;


typedef struct
{
    u32 tex_sheet;
    ImageType img_type;
    u32 asset_id;
    u32 shader_id;
    r32 x_min, y_min, x_max, y_max;
    r32 t_x0, t_y0, t_x1, t_y1;
    r32 depth;
    r32 rotation;
    u32 color;
    f32 alpha;
    
}RenderCommand;


typedef enum
{
    FLOOR_TILE,
    LOW_TILE,
    MID_TILE,
    ABOVE_TILE,
    GUI_LOW,
    GUI_MED,
    GUI_TOP,
}DepthLayer;

typedef enum
{
    M_RED,
    M_HOT_PINK,
    M_ORANGE,
    M_PINK,
    M_DARK_BLUE,
    M_DARK_RED,
    M_WHITE,
    M_GROSS_GREEN,
    M_LIGHT_YELLOW,
    M_LIGHT_BLUE,
    M_GRAY,
    M_BLACK,
    TOTAL_COLORS
}ColorId;

V3 colors [TOTAL_COLORS] = 
{
    [M_RED] = {1.0,0,0},
    [M_PINK] = {1.0,0.7,0.7},
    [M_ORANGE] = {1.0,0.5,0.0},
    [M_HOT_PINK] = {0.96,0.0,1.46},
    [M_DARK_RED] = {0.6,0.1f,0.1f},
    [M_GROSS_GREEN] = {0.0f,0.2f,0.05f},
    [M_DARK_BLUE] = {0.1,0.1f,0.6f},
    [M_LIGHT_YELLOW] = {1.0,1.0f,0.6f},
    [M_LIGHT_BLUE] = {0.0f,0.7f,0.95f},
    [M_BLACK] = {0,0,0},
    [M_GRAY] = {0.21f,0.21f,0.21f},
    [M_WHITE] = {1,1,1},
};

typedef struct
{
    u32 standard_model;
    u32 standard_proj;
    u32 color_model;
    u32 color_proj;
    u32 color_color;
    u32 line_model;
    u32 line_proj;
    
    u32 glow_model;
    u32 glow_proj;
    
}ShaderUniforms;

typedef struct
{
    SpriteId id;
    u32 frame;
    i32 color;
}SpriteInfo;


typedef struct
{
    u32 color;
    u32 char_index;
    
}FontInfo;


typedef struct
{
    union
    {
        FontInfo fnt_info;
        SpriteInfo spr_info;
    };
}SpecialRenderInfo;



typedef struct
{
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    i32 viewport_height;
    i32 viewport_width;
    
    //maybe zoom???
}GameCam;


typedef enum 
{
    NO_ZOOM,
    DOWN_ZOOM,
    NORMAL_ZOOM,
}ZoomEffect;

typedef struct
{
    
    RenderCommand draws[MAX_RENDER_COMMANDS];
    f32 gpu_buffer [NUM_DRAW_FLOATS * QUAD_POINTS * MAX_RENDER_COMMANDS];
    u32 shaders [TOTAL_SHADERS];
    u32 render_count;
    ShaderUniforms shader_uniforms;
    u32 VAO, VBO, EBO;
    GameCam cam;
    
}RenderData;
global_variable RenderData rd;



void 
draw_text(r32 , r32 , r32 , r32, FontId , ColorId, char* );


#endif //RENDER_H
