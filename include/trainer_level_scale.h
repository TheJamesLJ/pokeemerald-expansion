#ifndef GUARD_LEVEL_SCALE_H
#define GUARD_LEVEL_SCALE_H

u16 GetPlayerNumBadges(void);
u16 GetPlayerMaxLevel(void);
s8 GetTrainerLevelScaleModifier(u8 trainerClass);
u8 CalculateTrainerPartyScaledLevel(u8 trainerClass, u16 level, u16 levelMin, u16 partyCountMod, u16 numBadges);
u16 CheckLevelScaleEvolution(struct Pokemon *mon);

#endif /* GUARD_LEVEL_SCALE_H */
