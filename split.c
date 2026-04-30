#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


//helper to create output file names like chunk0, chunk1, chunk2
void
make_chunk_name(char *buf, int num)
{
    strcpy(buf, "chunk");
    int len = strlen(buf);
    //convert number to characters manually because xv6 does not have sprintf
    if(num >= 100){
        buf[len++] = '0' + (num / 100);
        num = num % 100;
    }

    if(num >= 10){
        buf[len++] = '0' + (num / 10);
        num = num % 10;
    }

    buf[len++] = '0' + num;
    buf[len] = 0;//null terminate
}

int
main(int argc, char *argv[])
{
    int fd, out;
    int chunk_size;
    int chunk_no = 0;
    int written_in_chunk = 0;
    int n;
    char c;
    char name[20];

    if(argc != 3){
        printf(2, "usage: split file size\n");
        exit();
    }

    chunk_size = atoi(argv[2]);
    if(chunk_size <= 0){
        printf(2, "split: size must be positive\n");
        exit();
    }

    //open original file for reading
    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf(2, "split: cannot open %s\n", argv[1]);
        exit();
    }

    //create first chunk file
    make_chunk_name(name, chunk_no);
    out = open(name, O_CREATE | O_WRONLY | O_TRUNC);

    if(out < 0){
        printf(2, "split: cannot create chunk\n");
        close(fd);
        exit();
    }

    //read the input file byte by byte
    while((n = read(fd, &c, 1)) > 0){
        //if current chunk is full, create the next chunk
        if(written_in_chunk == chunk_size){
            write(out, "\n", 1);
            close(out);
            chunk_no++;
            make_chunk_name(name, chunk_no);

            out = open(name, O_CREATE | O_WRONLY | O_TRUNC);
            if(out < 0){
                printf(2, "split: cannot create chunk\n");
                close(fd);
                exit();
            }

            written_in_chunk = 0;
        }
        //write current byte into current chunk
        write(out, &c, 1);
        written_in_chunk++;
    }

    write(out, "\n", 1);
    close(out);
    close(fd);

    printf(1, "split complete: created %d chunks\n", chunk_no + 1);
    exit();
}