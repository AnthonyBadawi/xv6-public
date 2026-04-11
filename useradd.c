#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define ROLE_USER 0
#define ROLE_ADMIN 1

struct user {
  char username[16];
  unsigned int passhash;
  int role;
};

unsigned int simple_hash(char *s) {
  unsigned int h = 5381;

  for(int i = 0; s[i]; i++){
    h = ((h << 5) + h) + s[i]; // h * 33 + c
  }

  return h;
}

int main(int argc, char *argv[])
{
  if(argc < 4){
    printf(1, "usage: useradd name pass role-integer (0-user, 1-admin)\n");
    exit();
  }

  int fd = open("users", O_WRONLY);
  if(fd < 0){
    printf(1, "cannot open users file\n");
    exit();
  }

  struct user u;

  strcpy(u.username, argv[1]);
  u.passhash = simple_hash(argv[2]);
  u.role = atoi(argv[3]);

  write(fd, &u, sizeof(u));

  close(fd);
  printf(1, "user created\n");
  exit();
}