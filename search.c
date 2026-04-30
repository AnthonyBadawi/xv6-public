#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

//search inside a file for a specific keyword
//helper function to check if keyword exists inside a line
int
contains(char *line, char *keyword)
{
    int i, j;
    for(i = 0; line[i] != 0; i++){
        for(j = 0; keyword[j] != 0; j++){
            if(line[i+j] != keyword[j])
                break;
        }
        if(keyword[j] == 0)
            return 1;
    }
    return 0;
}

int
read_line(int fd, char *buf, int max)
{
    int i = 0;
    char c;

    while(i < max - 1){
        int n = read(fd, &c, 1);
        if(n <= 0)
            break;

        buf[i++] = c;

        if(c == '\n')
            break;
    }
    buf[i] = 0;
    return i;
}

int
main(int argc, char *argv[])
{
    int fd;
    int line_no = 1;
    int found = 0;
    char line[512];
    if(argc != 3){
        printf(2, "usage: search keyword file\n");
        exit();
    }

    fd = open(argv[2], O_RDONLY);
    if(fd < 0){
        printf(2, "search: cannot open %s\n", argv[2]);
        exit();
    }

    while(read_line(fd, line, sizeof(line)) > 0){
        if(contains(line, argv[1])){
            printf(1, "%d: %s", line_no, line);

            //if line does not end with newline, print one for cleaner output
            if(strlen(line) > 0 && line[strlen(line)-1] != '\n')
                printf(1, "\n");
            found = 1;
        }
        line_no++;
    }

    if(found == 0)
        printf(1, "search: %s not found\n", argv[1]);
    close(fd);
    exit();
}