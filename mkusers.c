#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define ROLE_USER 0
#define ROLE_ADMIN 1

struct user {
  char username[16];
  char password[16];
  int role;
};

int main(void)
{
  int fd = open("users", O_CREATE | O_WRONLY);

  struct user u;

  strcpy(u.username, "admin");
  strcpy(u.password, "1234");
  u.role = ROLE_ADMIN;
  write(fd, &u, sizeof(u));

  strcpy(u.username, "bob");
  strcpy(u.password, "1111");
  u.role = ROLE_USER;
  write(fd, &u, sizeof(u));

  close(fd);

  printf(1, "users file created\n");
  exit();
}