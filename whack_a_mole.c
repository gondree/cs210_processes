#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <openssl/sha.h>
#include <signal.h>

static unsigned char hash[50];
static char *data = NULL;

void useage(void)
{
    ;
}


void secret()
{
    int i;
    size_t length = strlen(data);

    SHA1(data, length-1, hash);
    for(i = 0; i<SHA_DIGEST_LENGTH; i++){
        printf("%x", hash[i]);
    }
    printf("\n");
}

void handler_1() {
    printf("You got me to exit.\n");
    exit(0);
}

void handler_2() {
    printf("Mathematical!\n");
}

void handler_3() {
    printf("Algebraic!\n");
}

void handler_kill() {
    printf("You have to kill -9 me.\n"); fflush(stdout);
}

void run()
{
    sigset_t mask;
    sigfillset(&mask);

    sigdelset(&mask, SIGINT);
    signal(SIGINT, handler_kill);

    sigdelset(&mask, SIGSTOP);
    sigdelset(&mask, SIGCONT);

    sigdelset(&mask, SIGTERM);
    signal(SIGTERM, handler_1);

    sigdelset(&mask, SIGHUP);
    signal(SIGHUP, handler_2);

    sigdelset(&mask, SIGPIPE);
    signal(SIGPIPE, handler_3);

    sigdelset(&mask, SIGUSR1);
    signal(SIGUSR1, secret);

    sigprocmask(SIG_SETMASK, &mask, NULL);

    while(1) {
        sleep(1);
    }
    exit(0);
}



int main (int argc, char **argv)
{
    int c, opt_idx = 0;
    static struct option long_options[] = {
        {"help",  no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    while (1)
    {
        c = getopt_long (argc, argv, "h", long_options, &opt_idx);
        if (c == -1){  // end of the options
            break;
        }
        switch (c)
        {
            case 'h':
              useage();
              exit(0);
              break;
            default:
              useage();
              exit(1);
            break;
        }
    }

    data = argv[argc-1];
    run();

    exit(0);
}

