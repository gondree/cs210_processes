#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <openssl/sha.h>

void useage(void)
{
    ;
}

void shasum(const unsigned char* data)
{
  int i;
  size_t length = strlen(data);
  unsigned char hash[50];

  SHA1(data, length-1, hash);
  for(i = 0; i<SHA_DIGEST_LENGTH; i++){
    printf("%x", hash[i]);
  }
  printf("\n");
}

void handler_exit() {
   printf("You got me to exit.\n");
}

void handler_kill() {
   printf("You have to kill -9 me.\n"); fflush(stdout);
}

void run(char *data)
{
    atexit(handler_exit);
    signal(SIGINT, handler_kill);
    signal(SIGTERM, handler_kill);
    signal(SIGHUP, handler_kill);
    signal(SIGILL, exit);

    while(1) {
        sleep(1);
    }
    exit(0);
}



int main (int argc, char **argv)
{
   int c, opt_idx=0;
   char *data = NULL;
   static struct option long_options[] =
   {
        {"help",  no_argument,       0, 'h'},
        {"data",  required_argument, 0, 'd'},
        {0, 0, 0, 0}
   };

   while (1)
   {
      c = getopt_long (argc, argv, "hd:", long_options, &opt_idx);
      if (c == -1){  // end of the options
          break;
      }

      switch (c)
      {
        case 'h':
          useage();
          exit(0);
          break;
        case 'd':
          data = optarg;
          break;
        default:
          useage();
          exit(1);
          break;
      }
   }
   if (data == NULL){
       data = argv[argc-1];
   }
   run(data);
   exit (0);
}

