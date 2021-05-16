#ifndef GUARD_DIFFICULTY_H
#define GUARD_DIFFICULTY_H
//tx_difficulty_challenges

#define TX_RANDOM_CHAOS_MODE 0
#define TX_RANDOM_ENCOUNTER 1
#define TX_RANDOM_ENCOUNTER_SIMILAR 0
#define TX_RANDOM_TYPE 0
#define TX_RANDOM_TYPE_EFFECTIVENESS 0
#define TX_RANDOM_ABILITIES 0
#define TX_RANDOM_MOVES 0
#define TX_RANDOM_TRAINER 1
#define TX_RANDOM_EVOLUTION 1
#define TX_RANDOM_EVOLUTION_METHODE 0


#define TX_RANDOM_OFFSET_TRAINER     4  //51
#define TX_RANDOM_OFFSET_TYPE        2  //31
#define TX_RANDOM_OFFSET_ABILITY     5  //71
#define TX_RANDOM_OFFSET_MOVES       1  //13
#define TX_RANDOM_OFFSET_ENCOUNTER   0   //0
#define TX_RANDOM_OFFSET_EVOLUTION   7  //41

#define TX_CHALLANGE_EVO_LIMIT 0 //0 off, 1 first, 2 none
#define TX_CHALLANGE_PARTY_LIMIT 4
#define TX_CHALLENGE_NUZLOCKE 0
#define TX_CHALLENGE_NUZLOCKE_HARDCORE 0 //CAREFULL!!!!!
#define TX_CHALLENGE_NO_ITEM_PLAYER 1
#define TX_CHALLENGE_NO_ITEM_TRAINER 1
#define TX_CHALLENGE_PKMN_CENTER 2 //0 no limit, 1 three visits, 2 none
#define TX_CHALLENGE_TYPE TYPE_NONE //TYPE_NONE for off

#endif // GUARD_DIFFICULTY_H