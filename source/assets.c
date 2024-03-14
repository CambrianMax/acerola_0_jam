


void free_music(i32 id)
{
    MusicAsset* ass = &music_assets[id];
    if(!ass->loaded)
        return;
    Mix_FreeMusic(ass->mus);
    ass->loaded = false;
}

void load_music(i32 id)
{
    MusicAsset* ass = &music_assets[id];
    if(ass->loaded)
        return;
    ass->mus = Mix_LoadMUS(ass->filename);
    ass->loaded = true;
}

void
play_music(i32 id)
{
    gs.requested_music= id;
    
}




void load_sfx(i32 id)
{
    SfxAsset* ass = &sfx_assets[id];
    if(ass->loaded)
        return;
    ass->sfx = Mix_LoadWAV(ass->filename);
    ass->loaded = true;
}


void
load_all_sfx()
{
    for(i32 i = 0; i < TOTAL_SFX_ASSETS; i++)
        load_sfx(i);
}

void play_sfx(i32 id)
{
    SfxAsset* ass = &sfx_assets[id];
    Mix_PlayChannel(-1, ass->sfx,0);
}