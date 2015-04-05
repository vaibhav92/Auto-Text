#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>
#define SIZE 32

struct {
char far* list;
int count;
}data;
char far buffer[32];

extern unsigned _heaplen = 2048;
extern unsigned _stklen  = 512;

void main()
{int i,j;
char far *ptr,far *ptr2;
clrscr();
FILE *fp=fopen("list.txt","r");

//if(fp==NULL) 	{printf("File error");return ;}
data.list=(char far*)farmalloc(SIZE*32);
ptr=data.list;
clrscr();
for(i=0;!feof(fp)&&i<SIZE;i++)
	{data.count++;
	 ptr=data.list+32*i;
	 for(*ptr=getc(fp),j=1;*ptr!=EOF   &&
				*ptr!='\n' &&
				j<29; *ptr=getc(fp),j++)
	 ptr++;

	 if(*ptr==EOF||*ptr=='\n') *ptr=0;
	 else *(ptr+1)=0;
	}

for(j=0;j<data.count;j++)
	for(i=1;i<data.count-j;i++)
	if( _fstrcmp(&data.list[i*32],&data.list[(i-1)*32]) <0)
		{ _fstrcpy(buffer,&data.list[i*32]);
		 _fstrcpy(&data.list[i*32],&data.list[(i-1)*32]);
		 _fstrcpy(&data.list[(i-1)*32],buffer);
		}

for(ptr=data.list,i=0; i<data.count ;i++,ptr+=32,printf("\n"))
	for(ptr2=ptr;*ptr2!=0;ptr2++)
		printf("%c",*ptr2);
farfree(data.list);
getch();
}
