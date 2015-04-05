#include <dos.h>
#include <conio.h>
#include <string.h>

struct ch{ unsigned char ch,attr;}far *screen[25];
struct Window{char x,y,height,width;}Window;
void writetextxy(char r,char c,char *str,char width)
{if(r<0 || r>24) return;
 for(;*str&&width>3&&c<80;c++,str++,width--)
	if(c>=0)screen[r][c].ch=*str;
 if(*str)
    { if(str[1]==0 || str[2]==0 || str[3]==0)
	  for(;width>0 && c<80;str++,width--,c++)
	      {if(c>=0)screen[r][c].ch=*str;}
	 else
	    for(;width>0 && c<80;width--,c++)
	      {if(c>=0)screen[r][c].ch='.'
	      ;}
    }
}

void box(char r1,char c1,char r2,char c2,char attr)
{char i,inc;
 inc= c2>c1?1:-1;
 for(i=c1;i!=c2;i+=inc)
	{if(i<0 ||i>=80) continue;
	 if(r1>=0 && r1<25) screen[r1][i].ch=' ',screen[r1][i].attr=attr;
	 if(r2>=0 && r2<25) screen[r2][i].ch=' ',screen[r2][i].attr=attr;
	}/**/
 inc=r2>r1?1:-1;
 for(i=r1;i!=r2+inc;i+=inc)
	{if(i<0 ||i>=25) continue;
	 if(c1>=0 && c1<80) screen[i][c1].ch=' ',screen[i][c1].attr=attr;
	 if(c2>=0 && c2<80) screen[i][c2].ch=' ',screen[i][c2].attr=attr;
	}/**/
}


void fillattr(char r1,char c1,char r2,char c2,unsigned char attr_and,
		unsigned char attr_xor)
{char i,j,inci,incj;
  inci=r2>r1?1:-1;
  incj= c2>c1?1:-1;
  for(i=r1;i!=r2+inci;i+=inci)
	{if(i<0||i>=25) continue;
	for(j=c1;j!=c2+incj;j+=incj)
		{if(j<0||j>=80) continue;
		screen[i][j].attr&=attr_and;
		screen[i][j].attr^=attr_xor;
		}/**/
	}
}

void fillchar(char r1,char c1,char r2,char c2,char c)
{char i,j,inci,incj;
  inci=r2>r1?1:-1;
  incj= c2>c1?1:-1;
  for(i=r1;i!=r2+inci;i+=inci)
	{if(i<0||i>=25) continue;
	for(j=c1;j!=c2+incj;j+=incj)
		{if(j<0||j>=80) continue;
		screen[i][j].ch=c;
		}/**/
	}
}


void main()
{int i;
 char far *scr=(char far *)MK_FP(0xb800,0000);
 for(i=0;i<25;i++,scr+=160)
 screen[i]=(struct ch far *)scr;
clrscr();
Window.x=Window.y=10;
Window.height=7;
Window.width=29;
/*fillattr(0,0,24,79,0,0x71);
fillchar(0,0,24,79,219);
screen[Window.y+1][Window.x+Window.width+1].ch='l';
screen[Window.y+1][Window.x+Window.width+1].attr=WHITE|BLUE<<4;
getch();*/

box(Window.y,Window.x,Window.y+Window.height,Window.x+Window.width,WHITE<<3);
fillattr(Window.y+1,Window.x+1,Window.y+Window.height-1,
	Window.x+Window.width-1,0,BLUE|GREEN<<4);
fillchar(Window.y+1,Window.x+1,Window.y+Window.height-1,
	Window.x+Window.width-1,' ');

screen[Window.y][Window.x].ch=254;// close window marker
screen[Window.y][Window.x+Window.width].ch=240; //track cursor marker
screen[Window.y+3][Window.x+Window.width].ch=4;//scroll point
screen[Window.y+1][Window.x+Window.width].ch=30; //up scroll
screen[Window.y+Window.height][Window.x+Window.width].ch=249;//size window marker
screen[Window.y+Window.height-1][Window.x+Window.width].ch=31;//down scroll

fillattr(Window.y,Window.x+1,Window.y,Window.x+Window.width-1,0,0x7B);
writetextxy(Window.y,Window.x+Window.width/2-strlen("Autotext")/2,"Autotext",8);

//drawing shadow
fillattr(Window.y+1,Window.x+Window.width+1,Window.y+Window.height+1,
	Window.x+Window.width+1,0x87,0x0); // vertical shadow
fillattr(Window.y+Window.height+1,Window.x+1,Window.y+Window.height+1,
	Window.x+Window.width+1,0x87,0x0); // horizontal shadow*/

writetextxy(Window.y+1,Window.x+1,"Autotext",8);
writetextxy(Window.y+2,Window.x+1,"Autotext",8);
fillattr(Window.y+2,Window.x+1,Window.y+2,
	Window.x+Window.width-1,0x7f,0x7f); // horizontal shadow*/

//screen[Window.y+1][Window.x+Window.width+1].ch='l';
//screen[Window.y+1][Window.x+Window.width+1].ch='l';
getch();
}