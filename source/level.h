/* date = March 2nd 2024 9:04 pm */

#ifndef LEVEL_H
#define LEVEL_H

#define ROOMS \
X(BED_RM) \
X(OUTSIDE_RM) \
X(OUTSIDE_2_RM) \
X(CAVE_OUTSIDE_RM) \
X(CAVE_1_RM) \
X(CAVE_ORB_RM) \
X(CAVE_2_RM) \
X(WITCH_RM) \
X(WITCH_2_RM) \
X(WITCH_3_RM) \
X(TREE_RM) \
X(DEAD_WITCH_RM) \


#define X(name) name,
typedef enum
{
    ROOMS
        TOTAL_ROOMS
}RoomId;
#undef X


#define X(name) [name] = STRINGIFY(name),
char* room_str [] = 
{
    ROOMS
};
#undef X

char* levels[] = 
{
    [BED_RM] = "assets/test_level.tmj",
    [OUTSIDE_RM] = "assets/outside_room.tmj",
    [OUTSIDE_2_RM] = "assets/outside_2_room.tmj",
    [CAVE_OUTSIDE_RM] = "assets/outside_cave.tmj",
    [CAVE_1_RM] = "assets/cave_entrance.tmj",
    [CAVE_2_RM] = "assets/cave_rock.tmj",
    [CAVE_ORB_RM] = "assets/cave_orb.tmj",
    [WITCH_RM] = "assets/witch_room.tmj",
    [WITCH_2_RM] = "assets/witch_room_2.tmj",
    [WITCH_3_RM] = "assets/witch_room_3.tmj",
    [TREE_RM] = "assets/tree_room.tmj",
    [DEAD_WITCH_RM] = "assets/witch_dead_rm.tmj",
};


i32 level_music[] = 
{
    [BED_RM] = BINKS_HOUSE_MUS,
    [OUTSIDE_RM] = QUEST_MUS,
    [OUTSIDE_2_RM] = QUEST_MUS,
    [CAVE_OUTSIDE_RM] = QUEST_MUS,
    [CAVE_1_RM] = CAVE_MUS,
    [CAVE_ORB_RM] = CAVE_MUS,
    [CAVE_2_RM] = CAVE_MUS,
    [WITCH_RM] = CAVE_MUS,
    [WITCH_2_RM] = CAVE_MUS,
    [WITCH_3_RM] = CAVE_MUS,
    [TREE_RM] = CAVE_MUS,
    [DEAD_WITCH_RM] = CAVE_MUS,
};





RoomId room_id_lookup(char* name)
{
    for(i32 i = 0; i < TOTAL_ROOMS; i++)
    {
        if(!strcmp(name, room_str[i]))
            return i;
    }
    return 0;
}

void prepare_warp(RoomId rm_id, i32 x, i32 y);
void room_warp();
void load_level(i32);

#endif //LEVEL_H
