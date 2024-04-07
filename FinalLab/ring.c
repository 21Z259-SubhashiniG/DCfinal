#include <stdio.h>

#define MAX 10

int list[MAX];
int n, c;

void display() {
    printf("\n\nProcesses -->\t");
    for (int i = 1; i <= n; i++)
        printf("\t %d", i);
    printf("\nAlive -->    \t");
    for (int i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    printf("\nCoordinator is:: %d\n", c);
}

void crash() {
    int crash, gid, subcdr = 0, k = 1, i, prev;
    int msg[MAX + 1];

    printf("\nEnter Process no. to Crash:: ");
    scanf("%d", &crash);

    if (list[crash] != 0) {
        list[crash] = 0;
    } else {
        printf("\tProcess is already dead!!\n");
        return;
    }

    do {
        printf("Enter election generator id:: ");
        scanf("%d", &gid);
        if (gid == c || gid == crash) {
            printf("\tEnter a valid generator id:: ");
        }
    } while (gid == c || gid == crash);

    printf("\n\n");
    k = 1;
    msg[k++] = gid;
    prev = gid;

    for (i = (gid + 1) % n; i != gid; i = (i + 1) % (n + 1)) {
        if (i == 0)
            continue;
        if (list[i] != 0) {
            printf("\nMessage is sent from %d to %d", prev, i);
            msg[k++] = i;
            prev = i;
        }
    }

    printf("\n\nQueue:\t");
    subcdr = 0;

    for (i = 1; i < k; i++) {
        printf("%d\t", msg[i]);
        if (subcdr < msg[i]) {
            subcdr = msg[i];
        }
    }

    c = subcdr;
    display();
}

void activate() {
    int activate, subcdr = 0, i;

    printf("\nEnter Process no. to Activated:: ");
    scanf("%d", &activate);

    if (list[activate] == 0) {
        list[activate] = 1;
    } else {
        printf("\tProcess is already alive!!\n");
        return;
    }

    if (activate == n) {
        c = n;
	display();
        return;
    }
    
    subcdr = activate;
    for (i = activate + 1; i <= n; i++) {
        printf("\nMessage is sent from %d to %d", activate, i);
        if (list[i] != 0) {
            subcdr = i;
            printf(" -\tResponse is sent from %d to %d", i, activate);
        }
    }

    c = subcdr;
    display();
}

int main() {
    int i;
    printf("Enter no. of process:: ");
    scanf("%d", &n);

    printf("\n");

    for (i = 1; i <= n; i++) {
        printf("Enter Process %d is Alive or not(0/1):: ", i);
        scanf("%d", &list[i]);
        if (list[i] != 0)
            c = i;
    }

    display();
    printf("\nRING ALGORITHM\n");

    int choice;

    do {
        printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\n\nEnter Your choice:: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                crash();
                break;
            case 2:
                activate();
                break;
            case 3:
                display();
                break;
            case 4:
                break;
        }
    } while (choice != 4);

    return 0;
}
