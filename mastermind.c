#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char pieces[4];
} Play;

typedef struct {
    unsigned char correct;
    unsigned char semicorrect;
} Result;

Play*
solutionGenerator()
{
    // generate a play with 4 different pieces

    // First it will be all set to 0
    Play* game = malloc(sizeof(Play));
    game->pieces[0] = 0;
    game->pieces[1] = 0;
    game->pieces[2] = 0;
    game->pieces[3] = 0;

    //Then, for each one, generate a number and check if it is already in it, generate until it isn't
    for(int i = 0; i<4; i++)
    {
        unsigned char piece;
        unsigned char repeat;
        do {
            piece = 1 + (rand() % 6);
            repeat = 0;
            for(int j = 0; j<4; j++)
            {
                if(game->pieces[j] == piece) repeat = 1;
            }
        } while(repeat);

        game->pieces[i] = piece;
    }
    return game;
}

Result*
check(Play* game, Play* attempt)
{
    // allocate memory for result and set it to 0
    Result* res = malloc(sizeof(Result));
    res->correct=0;
    res->semicorrect=0;

    //check correct ones
    for(int i = 0; i < 4; i++)
    {
        if(game->pieces[i] == attempt->pieces[i]) res->correct++;
    }

    //check semicorrect ones
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(i==j) continue;
            if (game->pieces[i] == attempt->pieces[j]) res->semicorrect++;
        }
    }

    //return result
    return res;
}

void test()
{
    Play* one = malloc(sizeof(Play));
    Play* two = malloc(sizeof(Play));

    one->pieces[0] = 1;
    one->pieces[1] = 2;
    one->pieces[2] = 3;
    one->pieces[3] = 4;

    two->pieces[0] = 3;
    two->pieces[1] = 2;
    two->pieces[2] = 4;
    two->pieces[3] = 1;

    Result* res = check(one, two);

    printf("c: %d, s: %d\n", res->correct, res->semicorrect);

    free(one);
    free(two);
    free(res);
}

int
main()
{
    srand(time(0));
    Play* game = solutionGenerator();
    puts("-- Mastermind Game--");

    unsigned char* nattempts = 8;

    int state = 1;

    //game loop
    while(1)
    {
        printf("You have %d attempts left: ", nattempts);

        Play* attempt = malloc(sizeof(attempt));

        
        scanf("%d %d %d %d", &attempt->pieces[0], &attempt->pieces[1], &attempt->pieces[2], &attempt->pieces[3]);

        Result* res = check(game, attempt);
        
        printf("c: %d, s: %d\n", res->correct, res->semicorrect);

        int won = 0;
        won = res->correct == 4;

        free(res);

        free(attempt);

        if(won) break;
        nattempts--;

        if(nattempts == 0)
        {
            state = 0;
            break;
        }
    }


    if(state)
    {
        printf("You won the game!\nYou had %d attempts left.\n", nattempts);
    } else {

        unsigned char* pieces = game->pieces;

        printf("You lost the game\nThe answer was %d %d %d %d.", pieces[0], pieces[1], pieces[2], pieces[3]);

    }

    free(game);

    return 0;
}
