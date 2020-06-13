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

void
check(Result* res, Play* game, Play* attempt)
{
    // allocate memory for result and set it to 0
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
}

int
main()
{
    srand(time(0));
    Play* game = solutionGenerator();
    Play* attempt = malloc(sizeof(attempt));
    Result* res = malloc(sizeof(Result));
    puts("-- Mastermind Game--");

    unsigned char* nattempts = 8;

    int state = 1;

    //game loop
    while(1)
    {
        printf("You have %d attempts left: ", nattempts);


        
        scanf("%d %d %d %d", &attempt->pieces[0], &attempt->pieces[1], &attempt->pieces[2], &attempt->pieces[3]);

        check(res, game, attempt);
        
        printf("c: %d, s: %d\n", res->correct, res->semicorrect);

        int won = 0;
        won = res->correct == 4;



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

        printf("You lost the game\nThe answer was %d %d %d %d.\n", pieces[0], pieces[1], pieces[2], pieces[3]);

    }
    // Frees memory needed for various structs
    free(res);

    free(attempt);

    free(game);

    return 0;
}
