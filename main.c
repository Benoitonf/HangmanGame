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
        case SDLK_KP_PLUS:
            if (attempt_count < TRIES_MAX)
                attempt_count++;
            printf("attempt_count hangman : %d\n", attempt_count);
            break;
        case SDLK_KP_MINUS:
            if (attempt_count > 0)
                attempt_count--;
            printf("attempt_count hangman : %d\n", attempt_count);
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }

    if (touche >= SDLK_a && touche <= SDLK_z) {
        int num = touche - SDLK_a;
        char letter = 'a' + num;
        DisableButton(letter);
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

    initialise_game();

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
                        Check_Button_Click(event.button.x, event.button.y);
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

    free_string(&pseudo);
    free_string(&guessed);
    free_string(&word);
    free_string(&letters_guessed);
    free_file(&dico);
}