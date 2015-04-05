#include <alloc.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#define PGDOWN 81
#define PGUP 73
#define UP  72
#define DOWN 80

char far * save=NULL;
char far *screen=(char far*)MK_FP(0xb800,0x0000);
int i,cursel=0;
int max=5,min=0;
char *data[]={"vaibhav","ronak","ammar","divya","bhavesh"
			,"sandeep","harish","mira","mayur","humera"
			,"amit","vibha","abhishek","sameer","vikas"
			,"himanshu","nitin"};/**/
int SIZE= sizeof(data)/sizeof(data[0]);
void box(int r1,int c1,int r2,int c2,char attr)
{char far *ptr=screen+(r1-1)*160;
 for(i=r1;i<=r2;i++,ptr+=160)
	  if(i>=1&&i<=25)
	  { if(c1>=1&&c1<=80)  ptr[(c1-1)*2+1]=attr;
	    if(c2>=1&&c2<=80)  ptr[(c2-1)*2+1]=attr;
	  }
 ptr=screen+(r1-1)*160;
 for(i=c1;i<=c2;i++) if(r1>=1&&r1<=25)   ptr[(i-1)*2+1]=attr;
 ptr=screen+(r2-1)*160;
 for(i=c1;i<=c2;i++) if(r2>=1&&r2<=25)   ptr[(i-1)*2+1]=attr;
}

void writetextxy(int row,int col,char *str,int width)
{char far *ptr=screen+(row-1)*160+(col-1)*2;
  for(;*str!=0&&width>0;width--,ptr+=2)  *ptr=*str++;
  for(;width>0;width--,ptr+=2)	*ptr='.';
}

void fillattr(int r1,int c1,int r2,int c2,char attr)
{char far *ptr=screen+(r1-1)*160+(c1-1)*2;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for(i=c1;i<=c2;i++)
	  {ptr++;//=' ';
	   *ptr++=attr;
	  }
}

void fillchar(int r1,int c1,int r2,int c2,char chr)
{char far *ptr=screen+(r1-1)*160+(c1-1)*2;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for(i=c1;i<=c2;i++)
	  {*ptr++=chr;
	   ptr++;//=attr;
	  }
}

void clearwin(int r1,int c1,int r2,int c2,char attr)
{char far *ptr=screen+(r1-1)*160+(c1-1)*2;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for(i=c1;i<=c2;i++)
	  {*ptr++=' ';
	   *ptr++=attr;
	  }
}

void savevedio(int r1,int c1,int r2,int c2)
{char far *ptr=screen+(r1-1)*160+(c1-1)*2;
char far *svt=NULL;
if (save!=NULL)farfree(save);
	save=(char far *)farmalloc((r2-r1+1)*(c2-c1+1)*2);
 if(save==NULL) return;
 svt=save;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for(i=c1;i<=c2;i++)
	  {*svt++=*ptr++;
	   *svt++=*ptr++;
	  }
}

void restorevedio(int r1,int c1,int r2,int c2)
{char far *ptr=screen+(r1-1)*160+(c1-1)*2;
char far *svt=save;
 if(save==NULL) return;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for( i=c1;i<=c2;i++)
	  {*ptr++=*svt++;
	   *ptr++=*svt++;
	  }
farfree(save);
save=NULL;
}

void drawwindow()
{int r1=5,c1=5,r2=12,c2=26;
clearwin(r1,c1,r2,c2,0x70);
box(r1,c1,r2,c2,0x21);
for(i=min;i<SIZE&&i<=max;i++)
writetextxy(r1+i+1-min,c1+1,data[i],18);
fillattr(r1+cursel+1-min,c1+1,r1+cursel+1-min,c2-1,0x0f);
box(r1+1,c2-1,r2-1,c2-1,0x30);
fillchar(r1+1,c2-1,r2-1,c2-1,179);
writetextxy(r1+1+(5*cursel)/(SIZE-1),c2-1,"*",1);
}

void main()
{int r1=5,c1=5,r2=12,c2=26;
int i;char ch=1;

savevedio(r1,c1,r2,c2);
do
{
if(ch!=0)drawwindow();
ch=getch();
	switch(ch)
		{case UP: cursel--;break;
		 case DOWN: cursel++;break;
		 case PGUP:cursel-=6;break;
		 case PGDOWN:cursel+=6;break;
		 case
		}
		if(cursel<0) cursel=0;
		if(cursel>=SIZE) cursel=SIZE-1;
	 if(cursel>max) {max=cursel;min=max-5;}
	 if(cursel<min) {min=cursel;max=min+5;}
}while(ch!=27);


restorevedio(r1,c1,r2,c2);
getch();
}