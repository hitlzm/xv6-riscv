#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "user/user.h"

// return filename from path
char* basename(char *path)
{
  char *p = path + strlen(path);

  while(p >= path && *p != '/')
    p--;

  return p + 1;
}

void find(char *path, char *target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if(stat(path, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    return;
  }

  // if it is a file
  if(st.type == T_FILE){
    if(strcmp(basename(path), target) == 0)
      printf("%s\n", path);
    return;
  }

  // if it is not directory
  if(st.type != T_DIR)
    return;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    printf("find: path too long\n");
    close(fd);
    return;
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;

    if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;

    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;

    find(buf, target);
  }

  close(fd);
}

int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "usage: find <path> <filename>\n");
    exit(1);
  }

  find(argv[1], argv[2]);

  exit(0);
}
