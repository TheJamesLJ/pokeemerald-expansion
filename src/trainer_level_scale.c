#include "global.h"
#include "trainer_level_scale.h"
#include "pokemon.h"
#include "event_data.h"
#include "constants/trainers.h"

struct {
    u8 trainerClass;
    s8 scaleModifier;
} static const gTrainerClassLevelScaleMod[] = 
{
    {TRAINER_CLASS_PKMN_TRAINER_1, 0},
    {TRAINER_CLASS_PKMN_TRAINER_2, 0},
    {TRAINER_CLASS_HIKER, 0},           
    {TRAINER_CLASS_TEAM_AQUA, 0},       
    {TRAINER_CLASS_PKMN_BREEDER, 0},   
    {TRAINER_CLASS_COOLTRAINER, 0},    
    {TRAINER_CLASS_BIRD_KEEPER, 0},  
    {TRAINER_CLASS_COLLECTOR, 0},  
    {TRAINER_CLASS_SWIMMER_M, 0}, 
    {TRAINER_CLASS_TEAM_MAGMA, 0},   
    {TRAINER_CLASS_EXPERT, 0},
    {TRAINER_CLASS_AQUA_ADMIN, 0}, 
    {TRAINER_CLASS_BLACK_BELT, 0},    
    {TRAINER_CLASS_AQUA_LEADER, 0},
    {TRAINER_CLASS_HEX_MANIAC, 0},  
    {TRAINER_CLASS_AROMA_LADY, 0},
    {TRAINER_CLASS_RUIN_MANIAC, 0},
    {TRAINER_CLASS_INTERVIEWER, 0},
    {TRAINER_CLASS_TUBER_F, 0},
    {TRAINER_CLASS_TUBER_M, 0},
    {TRAINER_CLASS_LADY, 0},
    {TRAINER_CLASS_BEAUTY, 0},
    {TRAINER_CLASS_RICH_BOY, 0},
    {TRAINER_CLASS_POKEMANIAC, 0},
    {TRAINER_CLASS_GUITARIST, 0},
    {TRAINER_CLASS_KINDLER, 0},
    {TRAINER_CLASS_CAMPER, 0},
    {TRAINER_CLASS_PICNICKER, 0},
    {TRAINER_CLASS_BUG_MANIAC, 0},
    {TRAINER_CLASS_PSYCHIC, 0},
    {TRAINER_CLASS_GENTLEMAN, 0},
    {TRAINER_CLASS_ELITE_FOUR, 0},
    {TRAINER_CLASS_LEADER, 0},
    {TRAINER_CLASS_SCHOOL_KID, 0},
    {TRAINER_CLASS_SR_AND_JR, 0},
    {TRAINER_CLASS_WINSTRATE, 0},
    {TRAINER_CLASS_POKEFAN, 0},
    {TRAINER_CLASS_YOUNGSTER, 0},
    {TRAINER_CLASS_CHAMPION, 0},
    {TRAINER_CLASS_FISHERMAN, 0},
    {TRAINER_CLASS_TRIATHLETE, 0},
    {TRAINER_CLASS_DRAGON_TAMER, 0},
    {TRAINER_CLASS_NINJA_BOY, 0},
    {TRAINER_CLASS_BATTLE_GIRL, 0},
    {TRAINER_CLASS_PARASOL_LADY, 0},
    {TRAINER_CLASS_SWIMMER_F, 0},
    {TRAINER_CLASS_TWINS, 0},
    {TRAINER_CLASS_SAILOR, 0},
    {TRAINER_CLASS_COOLTRAINER_2, 0},
    {TRAINER_CLASS_MAGMA_ADMIN, 0},
    {TRAINER_CLASS_RIVAL, 0},
    {TRAINER_CLASS_BUG_CATCHER, 0},
    {TRAINER_CLASS_PKMN_RANGER, 0},
    {TRAINER_CLASS_MAGMA_LEADER, 0},
    {TRAINER_CLASS_LASS, 0},
    {TRAINER_CLASS_YOUNG_COUPLE, 0},
    {TRAINER_CLASS_OLD_COUPLE, 0},
    {TRAINER_CLASS_SIS_AND_BRO, 0},
    {TRAINER_CLASS_SALON_MAIDEN, 0},
    {TRAINER_CLASS_DOME_ACE, 0},
    {TRAINER_CLASS_PALACE_MAVEN, 0},
    {TRAINER_CLASS_ARENA_TYCOON, 0},
    {TRAINER_CLASS_FACTORY_HEAD, 0},
    {TRAINER_CLASS_PIKE_QUEEN, 0},
    {TRAINER_CLASS_PYRAMID_KING, 0},
    {TRAINER_CLASS_RS_PROTAG, 0},
};

u16 GetPlayerNumBadges(void)
{
    s32 i;
    u16 numBadges = 0;
    for (i = FLAG_BADGE01_GET; i <= FLAG_BADGE08_GET; i ++)
    {
        if (FlagGet(i))
            numBadges++;
    }
    return numBadges;
}

u16 GetPlayerMaxLevel(void)
{
    s32 i;
    u16 maxLvl = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                || GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG)
        {
            u8 lvl = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (lvl > maxLvl)
                maxLvl = lvl;
        }
    }
    return maxLvl;
}

s8 GetTrainerLevelScaleModifier(u8 trainerClass)
{
    s32 i;

    for(i = 0; i < ARRAY_COUNT(gTrainerClassLevelScaleMod); i++)
    {
        if(gTrainerClassLevelScaleMod[i].trainerClass == trainerClass)
            return gTrainerClassLevelScaleMod[i].scaleModifier;
    }

    return 0;
}

u8 CalculateTrainerPartyScaledLevel(u8 trainerClass, u16 level, u16 levelMin, u16 partyCountMod, u16 numBadges)
{
    u16 scaledLvl = level;
    
    //Only scale the Trainers mon if they are lower level than the players
    if(level < levelMin)
    {
        scaledLvl += (100 * (levelMin - level)) / (100 + partyCountMod * 10 + (NUM_BADGES - numBadges) * 25);

        //Depending on the Trainers class, apply a modifier (-2 to +2)
        s8 trainerLvlScale = GetTrainerLevelScaleModifier(trainerClass);
        if(trainerLvlScale != 0)
        {
            //Check that adjusting the level doesn't go under min level or over max
            if(scaledLvl + trainerLvlScale <= MIN_LEVEL)
                scaledLvl = MIN_LEVEL;
            else if(scaledLvl + trainerLvlScale >= MAX_LEVEL)
                scaledLvl = MAX_LEVEL;
            else
                scaledLvl += trainerLvlScale;
        }

        //If it turns out the level generated is less than intended, set it back
        if(scaledLvl < level)
        {
            scaledLvl = level;
        }
    }

    return scaledLvl;
}

u16 CheckLevelScaleEvolution(struct Pokemon *mon)
{
    u16 species;
    species = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL);
    if(species == SPECIES_NONE)
    {
        species = GetEvolutionTargetSpecies(mon, EVO_MODE_TRADE, ITEM_NONE, NULL);
    }
    return species;
}
