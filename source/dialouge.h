/* date = March 4th 2024 7:25 pm */

#ifndef DIALOUGE_H
#define DIALOUGE_H


#define DIALOUGES \
X(ERROR_D, PLAYER_PRJ_SPR, M_BLACK) \
X(PRESS_D, PLAYER_PRJ_SPR, M_WHITE) \
X(INIT_D, SON_SPR, M_WHITE) \
X(SON_D, SON_SPR, M_LIGHT_BLUE) \
X(SON_2_D, SON_SPR, M_LIGHT_BLUE) \
X(WIFE_D, WIFE_SPR, M_PINK) \
X(WIFE_2_D, WIFE_SPR, M_PINK) \
X(JANE_1_D, JANE_SPR, M_PINK) \
X(JANE_2_D, JANE_SPR, M_PINK) \
X(BILLY_1_D, BILLY_SPR, M_WHITE) \
X(BILLY_2_D, BILLY_SPR, M_WHITE) \
X(DINK_1_D, DINK_SPR, M_WHITE) \
X(DINK_2_D, DINK_SPR, M_WHITE) \
X(DAVE_1_D, DAVE_SPR, M_WHITE) \
X(DAVE_2_D, DAVE_SPR, M_WHITE) \
X(SHELLY_1_D, SHELLY_SPR, M_HOT_PINK) \
X(SHELLY_2_D, SHELLY_SPR, M_HOT_PINK) \
X(JOURNAL_D, JOURNAL_SPR, M_WHITE) \
X(HOUSE_SIGN_D, SIGN_SPR, M_WHITE) \
X(ROCK_1_D, ROCK_SPR, M_PINK) \
X(ROCK_2_D, ROCK_SPR, M_WHITE) \
X(ROCK_3_D, ROCK_SPR, M_LIGHT_BLUE) \
X(ROCK_4_D, ROCK_SPR, M_WHITE) \
X(ROCK_5_D, ROCK_SPR, M_WHITE) \
X(ROCK_6_D, ROCK_SPR, M_LIGHT_YELLOW) \
X(ROCK_7_D, ROCK_SPR, M_PINK) \
X(ROCK_8_D, ROCK_SPR, M_LIGHT_BLUE) \
X(ROCK_9_D, ROCK_SPR, M_WHITE) \
X(ROCK_10_D, ROCK_SPR, M_WHITE) \
X(ROCK_11_D, ROCK_SPR, M_LIGHT_BLUE) \
X(ROCK_12_D, ROCK_SPR, M_WHITE) \
X(ROCK_13_D, ROCK_SPR, M_PINK) \
X(WITCH_1_D, ROCK_SPR, M_WHITE) \
X(WITCH_2_D, ROCK_SPR, M_WHITE) \
X(WITCH_3_D, ROCK_SPR, M_WHITE) \
X(WITCH_4_D, ROCK_SPR, M_WHITE) \
X(HOME_1_D, WIFE_SPR, M_PINK) \
X(HOME_2_D, WIFE_SPR, M_PINK) \
X(HOME_3_D, WIFE_SPR, M_PINK) \
X(HOME_4_D, WIFE_SPR, M_PINK) \
X(HOME_5_D, WIFE_SPR, M_WHITE) \




#define X(name, spr, color) name,
typedef enum
{
    DIALOUGES
        TOTAL_DIALOUGES
}DialougeId;
#undef X


#define X(name, spr, color) [name] = STRINGIFY(name),
char* dialouge_str [] = 
{
    DIALOUGES
};
#undef X


#define X(name, spr,color) [name] = spr,
i32 dialouge_sprites [TOTAL_DIALOUGES] = 
{
    DIALOUGES
};
#undef X


#define X(name, spr,color) [name] = color,
i32 dialouge_colors [TOTAL_DIALOUGES] = 
{
    DIALOUGES
};
#undef X



char* dialouges [TOTAL_DIALOUGES] = 
{
    [ERROR_D] = "ERROR: WE GOT AN ERROR!",
    [INIT_D] = "    Press X to start game.\n\n\n\nA game by Max Denning",
    [SON_D] = "Are you going to kill the witch today dad?",
    [SON_2_D] = "DAD!\nYOU MADE IT BACK!!!",
    [WIFE_D] = "After your quest, come back home.\nI worry about you Bink my love.",
    [WIFE_2_D] = "I am glad to have you back Bink.",
    [JOURNAL_D] = "(X) Bink Blast\n",
    [HOUSE_SIGN_D] = "Home of the Bink Family",
    [JANE_1_D] = "My sister went into the Witch's cave and never came out.\nBe careful.",
    [JANE_2_D] = "You made it back!\nThank goodness!",
    [BILLY_1_D] = "Are you really going to banish the witch.\nFather said no weapon can hurt her.",
    [BILLY_2_D] = "Why are you walking so weird mister?",
    [DINK_1_D] = "The Witch put a curse on me.\nIt is a little hard to explain.",
    [DINK_2_D] = "You have the same curse as me...\nI am so sorry.",
    [DAVE_1_D] = "I wish you luck Bink.\nMany have lost their lives to that hag.",
    [DAVE_2_D] = "Did you really do it Bink!\nWe are free!",
    [SHELLY_1_D] = "Why would the Witch even want to live in a cave?",
    [SHELLY_2_D] = "Is there really no more Witch?!",
    [ROCK_1_D] = "The witch turned me into a rock.\nBe careful up there.",
    [ROCK_2_D] = "The source of the witch's power is the Devil's tree.\nYou must find it and destroy it.",
    [ROCK_3_D] = "Beware the witch's orbs.",
    [ROCK_4_D] = "Careful friend, the witch is near.",
    [ROCK_5_D] = "Hurry!\nThe Witch follows!",
    [ROCK_6_D] = "YOU DID IT!\nThe witch is no more!",
    [ROCK_7_D] = "It looks like you have been cursed.\nI am sorry friend.....",
    [ROCK_8_D] = "Hhmmm, I think I have seen this curse before...\nTry Pressing C, it should help you move North.",
    [ROCK_9_D] = "You should head home hero.\nYou deserve a rest.",
    [ROCK_10_D] = "That is a strange curse.\nTry holding C to go further North.",
    [ROCK_11_D] = "The land is finally free.\nThank you!",
    [ROCK_12_D] = "That is a terrible curse you have.\nHopefully it should be the last.",
    [ROCK_13_D] = "You are a true hero friend.\nYou will be remembered.",
    [WITCH_1_D] = "AGHHHHHHHHHH!!!",
    [WITCH_2_D] = "YOU THINK THIS IS THE END FOOL?!",
    [WITCH_3_D] = "I PUT A CURSE ON YOU!\nYOU WILL BECOME AN ABERRATION OF THIS WRETCHED WORLD!",
    [WITCH_4_D] = "FROM THIS DAY FORTH, YOU WILL NEVER HOLD YOUR GROUND.\nTHE EARTH'S PULL ON YOU WILL BE FOREVER CHANGED!",
    [HOME_1_D] = "You're back!\nAre you okay Bink?... You don't look well...",
    [HOME_2_D] = "You banished the witch, but you were cursed?",
    [HOME_3_D] = "I am sorry Bink.\nWe can get through this together.",
    [HOME_4_D] = "As a family.",
    [HOME_5_D] = "      THE END",
    [PRESS_D] = "Press X to continue",
    
};

i32
str_to_dialouge_id(char* str)
{
    for(i32 i = 0; i < TOTAL_DIALOUGES; i++)
    {
        if(!strcmp(dialouge_str[i], str))
            return i;
    }
    return -1;
}


void start_dialouge(i32 , i32 );


#endif //DIALOUGE_H
