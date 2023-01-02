# Jeu du Pendu

- [Description](#decription)
- [Compiler](#compiler)
## Description

Jeu du pendu en fenêtre graphique en C

L'affichage est fait grâce aux bibliothèques [SDL2][SDL2], [SDL2_IMAGE][SDL2_IMAGE] et [SDL2_TTF][SDL2_TTF] 
J'utilise le pack [Simple Flat Keys (Light/Dark)][assetKeys]

Il est possible de jouer une partie qui est enregistrée et d'afficher le tableau des scores précédant

##### Déroulement d'une partie
- Demander le nom du joueur
- Demander une lettre à la fois
- 8 tentatives maximum
- Afficher le « dessin » du pendu au fur à et mesure des tentatives
- Afficher un « _ » pour chaque lettre du mot à deviner et afficher la lettre à la place du « _ » quand celle-ci est devinée
- Quand le joueur propose une même lettre déjà tentée précédemment, cela n'augmente pas le compteur de tentative (ne fait pas avancer le jeu)
## Compiler

Créer un fichier exécutable avec le nom 'prog'.

```shell
gcc file.c string.c main.c hangman.c window.c button.c sdl_function.c -o prog -lSDL2 -lSDL2_image -lSDL2_ttf
```

[SDL2]: https://www.libsdl.org/
[SDL2_IMAGE]: https://wiki.libsdl.org/SDL_image/FrontPage
[SDL2_TTF]: https://wiki.libsdl.org/SDL_ttf
[assetKeys]: https://gamedev-lab.itch.io/simple-flat-keys-lightdark
