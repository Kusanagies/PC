#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int conditionRemplie(double *sequence, int nbMesures, double diffMax) {
    for (int i = 0; i < nbMesures - 1; i++) {
        if (fabs(sequence[i] - sequence[i + 1]) > diffMax) {
            return 0; // Condition non remplie
        }
    }
    return 1; // Condition remplie
}

void lisser(double *sequence, int nbMesures) {
    double *nouvelleSequence = (double *)malloc(nbMesures * sizeof(double));
    if (nouvelleSequence == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // Copier les extrémités
    nouvelleSequence[0] = sequence[0];
    nouvelleSequence[nbMesures - 1] = sequence[nbMesures - 1];

    // Lisser les valeurs intermédiaires
    for (int i = 1; i < nbMesures - 1; i++) {
        nouvelleSequence[i] = (sequence[i - 1] + sequence[i + 1]) / 2.0;
    }

    // Copier la nouvelle séquence dans l'ancienne
    for (int i = 0; i < nbMesures; i++) {
        sequence[i] = nouvelleSequence[i];
    }

    free(nouvelleSequence);
}

int nombreMinLissages(int nbMesures, double diffMax, double *mesures) {
    int nbLissages = 0;

    while (!conditionRemplie(mesures, nbMesures, diffMax)) {
        lisser(mesures, nbMesures);
        nbLissages++;
    }

    return nbLissages;
}

int main() {
    int nbMesures;
    double diffMax;

    scanf("%d", &nbMesures);
    scanf("%lf", &diffMax);

    double *mesures = (double *)malloc(nbMesures * sizeof(double));
    if (mesures == NULL) {
        perror("Erreur d'allocation mémoire");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < nbMesures; i++) {
        scanf("%lf", &mesures[i]);
    }

    int resultat = nombreMinLissages(nbMesures, diffMax, mesures);
    printf("%d\n", resultat);

    free(mesures);
    return EXIT_SUCCESS;
}
