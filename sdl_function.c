#include "sdl_function.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int window_width = 0;
static int window_height = 0;
static char* name = "Pendu";

/** Initialise la fenêtre window et le renderer (moteur de rendu) renderer
 *  @param windowWidth la largeur de la fenêtre
 *  @param windowHeight la hauteur de la fenêtre
*/
void init(int windowWidth, int windowHeight) {
    window_width = windowWidth;
    window_height = windowHeight;
    if (SDL_Init(SDL_INIT_VIDEO | IMG_INIT_PNG) != 0) {
        SDL_Log("ERREUR : Init SDL > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer)) {
        SDL_Log("ERREUR : Init window and renderer > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    SDL_SetWindowTitle(window, name);
}

/**
 * Libère la mémoire allouée à la fenêtre
*/
void freeWindow() {
    if (window) 
        SDL_DestroyWindow(window);
}

/**
 * Libère la mémoire allouée au renderer
*/
void freeRenderer() {
    if (renderer) 
        SDL_DestroyRenderer(renderer);
}

/** Libère la mémoire allouée à la texture (utilisée pour dans la fonction sprite() pour afficher une image)
 *  @param texture la texture utilisée pour afficher l'image
*/
void freeTexture(SDL_Texture *texture) {
    if (texture) 
        SDL_DestroyTexture(texture);
}

/**
 * Libère la mémoire allouée au programme(renderer et fenêtre) puis quitte la SDL et le programme
*/
void freeAndTerminate() {
    freeRenderer();
    freeWindow();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void actualize() {
    /** @brief actualise le renderer (i.e affiche ce qu'on a dessiné / fait dessus)
     */
    SDL_RenderPresent(renderer);
}

void clear() {
    /** @brief réinitialise le fenêtre et reset la couleur
     *         (i.e supprime ce qu'on a dessiné dessus pour avoir une fenêtre noire)
     */
    changeColor(0, 0, 0);
    SDL_RenderClear(renderer);
    changeColor(255, 255, 255);
}

void changeColor(int r, int g, int b) {
    /** @brief change la couleur avec laquelle on dessine sur le renderer en celle du code RGB
     *  @param r Rouge dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param g Vert dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param b Bleu dans le code RGB de la couleur choisi, entre 0 et 255
     */
    if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE)) {
        SDL_Log("ERREUR : changement de couleur > %s\nParametres passes %d , %d, %d\n",SDL_GetError(), r, g, b);
        freeAndTerminate();
    }
}


void drawSquare(int posX, int posY, int longueur)
{
    /** @brief dessine un carré
     *  @param posX position sur l'axe horizontale du coin supérieur gauche du carré
     *  @param posY position sur l'axe verticale du coin supérieur gauche du carré
     *  @param longueur longeur du coté du carré
     */
    SDL_Rect rectangle;
    rectangle.x = posX;
    rectangle.y = posY;
    rectangle.w = longueur;
    rectangle.h = longueur;

    if (SDL_RenderFillRect(renderer, &rectangle))
    {
        SDL_Log("ERREUR : Impossible de creer le carre > %s\nParametres passes %d , %d, %d\n", SDL_GetError(), posX, posY, longueur);
        freeAndTerminate();
    }
}

void sprite(int posX, int posY, char *imgBMPSrc) {
    /** @brief affiche un image .bmp sur le renderer
     *  @param posX position sur l'axe horizontale du coin supérieur gauche de l'image
     *  @param posY position sur l'axe verticale du coin supérieur gauche de l'image
     *  @param imgBMPSrc le chemin vers l'image que l'on veut afficher
     */
    SDL_Texture *textureImg = NULL;
    SDL_Surface *surfaceImg = NULL;
    if (!(surfaceImg = IMG_Load(imgBMPSrc))) {
        SDL_Log("ERREUR : chargement img > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeAndTerminate();
    }
    textureImg = SDL_CreateTextureFromSurface(renderer, surfaceImg);
    SDL_FreeSurface(surfaceImg);
    if (textureImg == NULL) {
        SDL_Log("ERREUR : chargement texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }

    SDL_Rect rectangle;
    if (SDL_QueryTexture(textureImg, NULL, NULL, &rectangle.w, &rectangle.h)) {
        SDL_Log("ERREUR : image : query texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    rectangle.x = posX;
    rectangle.y = posY;
    if (SDL_RenderCopy(renderer, textureImg, NULL, &rectangle) != 0) {
        SDL_Log("ERREUR: image : RenderCopy > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    freeTexture(textureImg);
}