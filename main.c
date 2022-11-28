#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "window.h"
#include "hangman.h"
#include "button.h"

void KeyPressed(SDL_KeyboardEvent event) {
    SDL_KeyCode touche = event.keysym.sym;

    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char *path = PATH_WORDS_FILE;
    bool programLaunched = true;

    // Si on veut donner un autre fichier
    if (argc > 1) {
        if (access(argv[1], F_OK) == 0) { // Si le fichier existe
            path = argv[1]; // On change le nom du fichier qui contient les mots
        }
    }

    init_file(path, &dico); // Initialise le fichier
    
    init_buttons();
    init_window();

    while(programLaunched) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        Click_Button(event.button.x, event.button.y);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    Mouse_over_buttons(event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key);
                    break;
            }
        }

        drawGame();
    }
    freeAndTerminate();

    // char choice;
    // do {
    //     system("clear");
    //     printf("Quelle action faire ?\n");
    //     printf("\t- 1 : Jeu du pendu\n");
    //     printf("\t- 2 : Voir le TOP %d\n", SCOREBOARD_LENGTH);
    //     printf("\t- 0 : Exit\n");

    //     choice = GetLetter();

    //     switch(choice) {
    //         case '1':
    //             game_hangman();
    //             break;
    //         case '2':
    //             system("clear");
    //             printScoreboard();
    //             printf("\nAppuyer sur Entrée pour continuer ...");
    //             getchar();
    //             break;
    //     }
    // } while(choice != '0');

    free_string(&pseudo);
    free_string(&guessed);
    free_string(&word);
    free_string(&letters_guessed);
    free_file(&dico);
}