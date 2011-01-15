/**
*  CPE 357 Fall 2008
*  -------------------
*  Header that is used in reverse.c, It defines the typedef that is used to reverse the string.
*
*  @author Ryuho Kudo
*/

struct reverseChain{
    struct reverseChain *pointerToChain;
    char theLetter;
};

typedef struct reverseChain chain_t;



/*
typedef struct chain_t{
    struct chain_t *pointerToChain;
    char theLetter;
}chain_t;
*/
