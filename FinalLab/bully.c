#include <stdio.h>

#define MAX 10

int list[MAX];
int n, c;

void display() {
    printf("\n\nProcesses -->\t");
    for (int i = 1; i <= n; i++)
        printf("\t%d", i);
    printf("\nAlive -->  \t");
    for (int i = 1; i <= n; i++)
        printf("\t%d", list[i]);
    printf("\nCoordinator is:: %d\n", c);
}

void processCrash() {
    int crash, gid, subcdr = 0;
    printf("\nEnter Process no. to Crash:: ");
    scanf("%d", &crash);

    if (list[crash] != 0)
        list[crash] = 0;
    else {
        printf("\tProcess is already dead!!");
        return;
    }

    do {
        printf("Enter election generator id:: ");
        scanf("%d", &gid);
        if (gid == c || gid == crash) {
            printf("\nEnter a valid generator id:: ");
        }
    } while (gid == c || gid == crash);

    printf("\n");

    if (crash == c) {
        for (int i = gid; i <= n; i++) {
	    subcdr = i;
            for (int j = i + 1; j <= n; j++) {
                printf("\nElection message is sent from %d to %d", i, j);
                if (list[j] != 0) {
                    printf(" -\tOK Response is sent from %d to %d", j, i);
		    subcdr = j;
                }
            }
            if (subcdr == i)
		break;
        }

        c = subcdr;
    }
    display();
}

void processActivate() {
    int activate, subcdr = 0;
    printf("\nEnter Process no. to Activated:: ");
    scanf("%d", &activate);

    if (list[activate] == 0)
        list[activate] = 1;
    else {
        printf("\tProcess is already alive!!");
        return;
    }

    if (activate == n) {
        c = n;
        display();
        return;
    }
    subcdr = activate;
    for (int i = activate + 1; i <= n; i++) {
        printf("\nReactivation message is sent from %d to %d", activate, i);
        if (list[i] != 0) {
            subcdr = i;
            printf(" -\tResponse is sent from %d to %d", i, activate);
        }
    }

    if (c < subcdr)
	c = subcdr;

    display();
}

void bully() {
    int ch;

    do {
        printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\n\nEnter Your choice:: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                processCrash();
                break;
            case 2:
                processActivate();
                break;
            case 3:
                display();
                break;
            case 4:
                break;
        }
    } while (ch != 4);
}

int main() {
    printf("Enter no. of processes:: ");
    scanf("%d", &n);
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("Enter Process %d is Alive or not(0/1):: ", i);
        scanf("%d", &list[i]);
        if (list[i] != 0)
            c = i;
    }

    display();
    printf("\nBULLY ALGORITHM\n");
    bully();

    return 0;
}
