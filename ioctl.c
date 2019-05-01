#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc,char *argv[])
{
	struct winsize ws;

	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}

  int col = ws.ws_col;
  int row = ws.ws_row;

  FILE* fd = fopen("Datei.txt", "r");
  int crnt_char = fgetc(fd);

  int line = 0;
  int chars_of_lines = 0;
	int page = 1;

  while(crnt_char != -1)
  {
    while(line < page*(row-1))
    {
      while(chars_of_lines < col)
      {
        printf("%c", crnt_char);
        chars_of_lines++;
				if(crnt_char == '\n')
				{
					chars_of_lines = col+1;

				}
        crnt_char = fgetc(fd);
				if(crnt_char == -1)
				{
					chars_of_lines = col;
					line = page*(row-1);
				}
      }
      chars_of_lines = 0;
      line++;
    }
		if(crnt_char != -1)
		{
			printf("--More--(Page: %d)",page );
			int desicion_char = getchar();
			if(desicion_char != 10)
			{
				getchar();
			}

			if(desicion_char == 'b')
			{
				line = 0;
				fseek(fd, 0, SEEK_SET);
				crnt_char = fgetc(fd);
				if(page > 1)
				{
					page--;
				}
			}
			else if(desicion_char == 'q')
			{
				crnt_char = -1;
			}
			else
			{
				page++;
			}
		}
  }
	fclose(fd);

	return 0;
}
