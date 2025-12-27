#include <stdio.h>

#define MAXS 10
#define MAXSYM 5

int ns, nSym;
char syms[MAXSYM];
int oldt[MAXS][MAXSYM][MAXS];
int newt[MAXS][MAXSYM][MAXS];
int eps[MAXS][MAXS];
int eclos[MAXS][MAXS];
int initSt;
int finalFlag[MAXS];

void readNFA() {
    int i, j, k, f, nf;

    printf("How many states? ");
    scanf("%d", &ns);

    printf("How many symbols? ");
    scanf("%d", &nSym);

    printf("Enter symbols: ");
    for (i = 0; i < nSym; i++)
        scanf(" %c", &syms[i]);

    for (i = 0; i < ns; i++) {
        finalFlag[i] = 0;
        for (j = 0; j < nSym; j++)
            for (k = 0; k < ns; k++)
                oldt[i][j][k] = newt[i][j][k] = 0;
        for (j = 0; j < ns; j++)
            eps[i][j] = 0;
    }

    printf("Start state: ");
    scanf("%d", &initSt);

    printf("Number of final states: ");
    scanf("%d", &nf);

    printf("Final states: ");
    for (i = 0; i < nf; i++) {
        scanf("%d", &f);
        finalFlag[f] = 1;
    }

    printf("Transitions (-1 to stop):\n");
    while (1) {
        int fr, to;
        char sy;
        scanf("%d", &fr);
        if (fr == -1) break;
        scanf(" %c %d", &sy, &to);
        for (i = 0; i < nSym; i++)
            if (syms[i] == sy)
                oldt[fr][i][to] = 1;
    }

    printf("Epsilon transitions (-1 to stop):\n");
    while (1) {
        int fr, to;
        scanf("%d", &fr);
        if (fr == -1) break;
        scanf("%d", &to);
        eps[fr][to] = 1;
    }
}

void computeEpsilonClosure() {
    int i, j, k, changed;

    for (i = 0; i < ns; i++) {
        for (j = 0; j < ns; j++)
            eclos[i][j] = 0;
        eclos[i][i] = 1;
    }

    do {
        changed = 0;
        for (i = 0; i < ns; i++)
            for (j = 0; j < ns; j++)
                if (eclos[i][j])
                    for (k = 0; k < ns; k++)
                        if (eps[j][k] && !eclos[i][k]) {
                            eclos[i][k] = 1;
                            changed = 1;
                        }
    } while (changed);
}

void buildTransitions() {
    int i, s, j, d, k;

    for (i = 0; i < ns; i++)
        for (s = 0; s < ns; s++)
            if (eclos[i][s])
                for (j = 0; j < nSym; j++)
                    for (d = 0; d < ns; d++)
                        if (oldt[s][j][d])
                            for (k = 0; k < ns; k++)
                                if (eclos[d][k])
                                    newt[i][j][k] = 1;
}

void updateFinalStates() {
    int i, j;

    for (i = 0; i < ns; i++)
        for (j = 0; j < ns; j++)
            if (eclos[i][j] && finalFlag[j])
                finalFlag[i] = 1;
}

void displayNFA() {
    int i, j, k;

    printf("\n====== NFA after epsilon removal ======\n");
    printf("Initial state: %d\n", initSt);

    printf("Final states: ");
    for (i = 0; i < ns; i++)
        if (finalFlag[i])
            printf("%d ", i);
    printf("\n");

    printf("Transitions:\n");
    for (i = 0; i < ns; i++)
        for (j = 0; j < nSym; j++)
            for (k = 0; k < ns; k++)
                if (newt[i][j][k])
                    printf("%d --%c--> %d\n", i, syms[j], k);
}

int main() {
    readNFA();
    computeEpsilonClosure();
    buildTransitions();
    updateFinalStates();
    displayNFA();
    return 0;
}
