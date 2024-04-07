#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WAITING 5

struct Process {
    int id;
    int holding;
    int waiting[MAX_WAITING];
    int num_waiting;
};

void probe(struct Process pList[], struct Process cur, int start, int size) {
    for (int j = 0; j < cur.num_waiting; j++) {
        for (int i = 0; i < size; i++) {
            if (cur.waiting[j] == pList[i].id) {
                printf("Process-%d sends message (%d,%d,%d)\n", cur.id, start, cur.id, pList[i].id);
                if (pList[i].id == start) {
                    printf("\nDeadlock detected\n");
                    return;
                } else {
                    probe(pList, pList[i], start, size);
                }
            }
        }
    }
}

int main() {
    int process, initiator;
    printf("\nEnter number of processes: ");
    scanf("%d", &process);
    printf("\n");

    struct Process *pList = (struct Process *)malloc(process * sizeof(struct Process));

    for (int i = 0; i < process; i++) {
        printf("\nWhich resource is process-%d holding? (Enter -1 if none): ", i + 1);
        scanf("%d", &pList[i].holding);

        printf("How many resources is process-%d waiting for? : ", i + 1);
        scanf("%d", &pList[i].num_waiting);

        printf("Enter the IDs of the resources process-%d is waiting for: ", i + 1);
        for (int j = 0; j < pList[i].num_waiting; j++) {
            scanf("%d", &pList[i].waiting[j]);
        }

        pList[i].id = i;
    }

    printf("\nProcess id that initiates probe : ");
    scanf("%d", &initiator);
    printf("\n");
    struct Process cur = pList[initiator];
    probe(pList, cur, cur.id, process);

    free(pList);
    return 0;
}
