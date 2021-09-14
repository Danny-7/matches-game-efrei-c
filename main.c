#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_PLAYERS 2
#define MAX_MATCHES_TO_WITHDRAW 3

void start_game(){
    printf("-----------Jeu des allumettes-------------\n"
           "Vous allez avoir 2 menus.\n"
           "Vous choisirez d'abord si vous voulez voir les regles du jeu ou non, puis le\n"
           "nombre d'allumettes a utiliser, et enfin le nombre de joueurs.\n"
           "\t Que faire ?\n"
           "1 - Jouer\n"
           "2 - Voir les regles du jeu\n"
           "3 - Quitter\n"
    );
}

void game_rules(){
    printf("Le but du jeu est simple:\n\n"
           "Ce jeu se joue a deux. Vous avez un nombre n d'allumettes\n"
           "A tour de role, chacun des deux joueurs enleve 1 a 3 allumettes selon ce qu'il souhaite.\n"
           "Le perdant est celui qui doit enlever la derniere allumette.\n\n"
           "Attention, il existe 2 niveaux de difficultés en version humaine vs ordi.\n"
           "Le 1er est plutot simple a battre, donc pour les debutants. Mais le dernier.....\n"
           "\t Que faire ?\n"
           "1 - Jouer\n"
           "2 - Quitter\n"
    );
}

void mode_presentation(){
    printf("Vous avez 3 modes possibles. A vous de choisir lequel !\n"
           "1 - Mode humain\n"
           "2 - Mode ordi naif\n"
           "3 - Mode ordi expert\n"
    );
}

void print_matches(int size){
    char matches_tab[] = "||||||||||||||||||||||||||||||";

    int n = 0;
    while (n < size){
        printf("%c ", matches_tab[n]);
        n++;
    }
    printf("\tIl reste %d allumettes\n", size);
}

// TODO check for character input
int read_input_in_game(int choice_range) {
    int choice = -1;
    while(!(choice > 0 && choice <= choice_range)) {
        scanf("%d", &choice);

        if(!(choice > 0 && choice <= choice_range)){
            printf("Erreur! Vous devez entrez un chiffre entre %d et %d\n", 1, choice_range);
            printf("Votre choix :");
        }
    }
    return choice;
}

int get_smart_number(int size){
    for (int i = 1; i < 4; i++){
        if ((size - i) % 4 == 1){
            return i;
        }
    }
}

void smart_computer() {
    short int losing = -1;
    short int temp_size = 0;
    int size = 30;
    int nb_matches;
    printf("Jeu Mode humain avec 30 allumettes\n\n");
    print_matches(size);
    while (size > 1) {
        for (int i = 0; i < MAX_PLAYERS && size > 1; ++i) {
            if (i == 0) {
                printf("J1 - Nombre d'allumettes a enlever :");
                nb_matches = read_input_in_game(3);
            } else {
                nb_matches = get_smart_number(size);
                printf("Ordi enleve %d allumettes\n", nb_matches);
            }
            temp_size = size;
            size -= nb_matches;
            if (temp_size - nb_matches == 1) {
                // modulo = 1 , player 1 has lost else Player 2
                losing = (temp_size % nb_matches == 0) ? 1 : 2;
                break;
            }
            print_matches(size);
        }
    }
    printf("%s a perdu !", (losing == 1 ? "Le joueur" : "L'ordi"));

}

void dumb_computer() {
    short int losing = -1;
    int size = 30;
    int nb_matches;
    printf("Jeu Mode humain avec 30 allumettes\n\n");
    print_matches(size);
    while (size > 1) {
        for (int i = 0; i < MAX_PLAYERS && size > 1; ++i) {
            if (i == 0) {
                printf("J1 - Nombre d'allumettes a enlever :");
                nb_matches = read_input_in_game(3);
            } else {
                nb_matches = (int) (rand() % MAX_MATCHES_TO_WITHDRAW) + 1;
                printf("Ordi enleve %d allumettes\n", nb_matches);
            }
            int temp_size = size;
            size -= nb_matches;
            if (temp_size - nb_matches <= 1) {
                // modulo = 1 , player 1 has lost else Player 2
                losing = (temp_size % nb_matches == 1) ? 1 : 2;
                break;
            }
            print_matches(size);
        }
    }
    printf("%s a perdu !", (losing == 1 ? "Le joueur" : "L'ordi"));
}

void human_mode(){
    short int losing = -1;
    int size = 30;
    printf("Jeu Mode humain avec 30 allumettes\n\n");
    print_matches(size);

    while(size > 1){
        for (int i = 0; i < MAX_PLAYERS && size > 1; ++i) {
            printf("J%d - Nombre d'allumettes a enlever :", i+1);
            int nb_matches = read_input_in_game(3);
            int temp_size = size;
            size -= nb_matches;
            if(temp_size - nb_matches <= 1){
                // modulo = 1 , player 1 has lost else Player 2
                losing = (temp_size % nb_matches == 1) ? 1 : 2;
                break;
            }
            print_matches(size);
        }
    }
    printf("Le joueur J%hd a perdu !", losing);
}

int main() {
    srand(time(NULL));
    int choice = 0;
    int choice_mode = 0;
    int choice_rule = 0;
    int choice_rule_mode = 0;
    start_game();
    printf("Votre choix :");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            mode_presentation();
            printf("Votre choix :");
            scanf("%d", &choice_mode);
            switch (choice_mode) {
                case 1:
                    human_mode();
                    break;
                case 2:
                    dumb_computer();
                    break;
                case 3:
                    smart_computer();
                    break;
                default:
                    printf("Vous devez rentrer un nombre entre 1 et 3");
            }
            break;
        case 2:
            game_rules();
            printf("Votre choix :");
            scanf("%d", &choice_rule);
            switch (choice_rule) {
                case 1:
                    mode_presentation();
                    scanf("%d", &choice_rule_mode);
                    switch (choice_rule_mode) {
                        case 1:
                            human_mode();
                            break;
                        case 2:
                            dumb_computer();
                            break;
                        case 3:
                            smart_computer();
                            break;
                        default:
                            printf("Vous devez rentrer un nombre entre 1 et 3");
                    }
                    break;
                case 2:
                    exit(1);
                default:
                    printf("Vous devez rentrer un nombre entre 1 et 3");
            }
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Vous devez rentrer un nombre entre 1 et 3");
    }
    return 0;
}

