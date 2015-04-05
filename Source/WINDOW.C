#include <_null.h>
#include "common.h"
#define WHITE 0x0f
#define BLUE   0x01
#define BLACK 0x00
#define GREEN 0x02

#define BORDER WHITE<<3
#define TEXTCOLOR BLUE|GREEN<<4
#define TITLECOLOR 0x7B
//#define SELCOLOR
//out dated definition refer to common.h
/*struct Window
       {char enabled;
	char row,col;
	char height,width;
	char active;
	char saved_data[HEIGHT*WIDTH*2*sizeof(char)];
	int far *uprange;
	int far *dnrange;
       };*/

extern void far setupmouse(void);// setup the mouse to process events
extern void far restoremouse(void);// restore mouse to privious state
/*********************************************************/
static int far preicursel;
static int far i;
static far char caption[]="Autotext";
//***************************BOX******************************
//draw box from given row,col to given row,col with border set to attr
static void far box(char r1,char c1,char r2,char c2,char attr)
{char i,inc;
 inc=c2>c1?1:-1;
 for(i=c1;i!=c2;i+=inc)
	{if(i<0 ||i>=80) continue;
	 if(r1>=0 && r1<25) System.screen[r1][i].ch=' ',
			    System.screen[r1][i].attr=attr;
	 if(r2>=0 && r2<25) System.screen[r2][i].ch=' ',
			    System.screen[r2][i].attr=attr;
	}/**/
 inc=r2>r1?1:-1;
 for(i=r1;i!=r2+inc;i+=inc)
	{if(i<0 ||i>=25) continue;
	 if(c1>=0 && c1<80) System.screen[i][c1].ch=' ',
			    System.screen[i][c1].attr=attr;
	 if(c2>=0 && c2<80) System.screen[i][c2].ch=' ',
			    System.screen[i][c2].attr=attr;
	}/**/
}
//*************************writetextxy***********************************
// write given test at row,col and print atmost width charecters with '.'
//fill
static void far writetextxy(char r,char c,char far*str,int width)
{
if(r<0 || r>24) return;
 for(;*str&&width>3&&c<80;c++,str++,width--)
	if(c>=0)System.screen[r][c].ch=*str;
 if(*str)
    { if(str[1]==0 || str[2]==0 || str[3]==0)
	  for(;width>0 && c<80;str++,width--,c++)
	      {if(c>=0)System.screen[r][c].ch=*str;}
	 else
	    for(;width>0 && c<80;width--,c++)
	      {if(c>=0)System.screen[r][c].ch='.'
	      ;}
    }
}
//***************************fillattr*******************************
//fills give rectangle on screen with given attributes
// param attr_and: the AND mask for the screen attributes
// param attr_xor: the XOR mask for the screen attributes
static void far fillattr(char r1,char c1,char r2,char c2,unsigned char attr_and,
		unsigned char attr_xor)
{char i,j,inci,incj;
  inci=r2>r1?1:-1;
  incj= c2>c1?1:-1;
  for(i=r1;i!=r2+inci;i+=inci)
	{if(i<0||i>=25) continue;
	for(j=c1;j!=c2+incj;j+=incj)
		{if(j<0||j>=80) continue;
		System.screen[i][j].attr&=attr_and;
		System.screen[i][j].attr^=attr_xor;
		}/**/
	}
}
//***************************fillchar*******************************
//fills give rectangle on screen with given charecter
static void far fillchar(char r1,char c1,char r2,char c2,char c)
{char i,j,inci,incj;
  inci=r2>r1?1:-1;
  incj= c2>c1?1:-1;
  for(i=r1;i!=r2+inci;i+=inci)
	{if(i<0||i>=25) continue;
	for(j=c1;j!=c2+incj;j+=incj)
		{if(j<0||j>=80) continue;
		System.screen[i][j].ch=c;
		}/**/
	}
}
//************************************************************
//saves the attribute data of window shadow
static void far saveshadowattr()
{int i;
//save vertical shadow attributes
  for(i=Window.row+1;i<=Window.row+Window.height+1;i++)
     Window.s_vshadow[i-Window.row-1]=
	System.screen[i][Window.col+Window.width+1].attr;
//save horizontal shadow attributes
  for(i=Window.col+1;i<=Window.col+Window.width;i++)
     Window.s_hshadow[i-Window.col-1]=
     System.screen[Window.row+Window.height+1][i].attr;
}
//************************************************************
//restores the attribute data of window shadow
static void far restoreshadowattr()
{int i;
//restore vertical shadow attributes
  for(i=Window.row+1;i<=Window.row+Window.height+1;i++)
	System.screen[i][Window.col+Window.width+1].attr=
	     Window.s_vshadow[i-Window.row-1];
//restore horizontal shadow attributes
  for(i=Window.col+1;i<=Window.col+Window.width;i++)
    System.screen[Window.row+Window.height+1][i].attr=
	 Window.s_hshadow[i-Window.col-1];
}

//************************************************************
//saves the screen data of given rectangle in given buffer
void far savevedio(int r1,int c1,int r2,int c2,char far*svt)
/*{ int i;
 //return;
// if(!Window.active) return;
 for( ;r1<=r2;r1++)
    for(i=c1;i<=c2;i++)
       {*svt=System.screen[r1][i].ch;
	svt++;
	*svt=System.screen[r1][i].attr;
	svt++;
       }

}/**/
{char far *ptr=(char far*)System.screen[0]+r1*160+c1*2;
//char far *svt=Window.saved_data;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
	  for(i=c1;i<=c2;i++)
	  {*svt++=*ptr++;
	   *svt++=*ptr++;
	  }
}/**/
//************************************************************
//restores the screen data of given rectangle from given buffer
void far restorevedio(int r1,int c1,int r2,int c2,char far *svt)
/*{int i;
//if(Window.active) return;
for(;r1<=r2;r1++)
    for(i=c1;i<=c2;i++)
       {System.screen[r1][i].ch=*svt;
	svt++;
	System.screen[r1][i].attr=*svt;
	svt++;
       }
}/**/
{char far *ptr=(char far*)System.screen[0]+r1*160+c1*2;
//char far *svt=Window.saved_data;
 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
       for(i=c1;i<=c2;i++)
	  {*ptr++=*svt++;
	   *ptr++=*svt++;
	  }
}/**/
//************************************************************

void far drawwindow()
{if(!Window.active || !Window.enabled) return;
if(List.icursel<Window.uprange || List.icursel >Window.dnrange) // is cursel in range?
	{Window.uprange=List.icursel- (preicursel-Window.uprange);
	 Window.dnrange=List.icursel+(Window.dnrange-preicursel);
	 if(Window.uprange<0)
		{Window.uprange=0;
		 Window.dnrange= Window.height-3;
		}
	if(Window.dnrange>=List.count)
		  {Window.dnrange=List.count-1;
		   Window.uprange=Window.dnrange-Window.height+2;
		  }
	}
//erase all the contents of the rectangle & draw the box
box(Window.row,Window.col,Window.row+Window.height,
	Window.col+Window.width,BORDER/*WHITE<<3*/);
//return;
fillattr(Window.row+1,Window.col+1,Window.row+Window.height-1,
	Window.col+Window.width-1,0,TEXTCOLOR/*BLUE<<4|BLACK*/);
fillchar(Window.row+1,Window.col+1,Window.row+Window.height-1,
	Window.col+Window.width-1,' ');

System.screen[Window.row][Window.col].ch=254;// close window marker
System.screen[Window.row][Window.col+Window.width].ch=240; //track cursor marker
System.screen[Window.row+Window.height][Window.col+Window.width].ch=249;//size window marker

fillattr(Window.row,Window.col+1,Window.row,Window.col+Window.width-1,0,TITLECOLOR);
writetextxy(Window.row,Window.col+1,caption,Window.width-2);

//drawing shadow
if(Window.shadow)
{
fillattr(Window.row+1,Window.col+Window.width+1,Window.row+Window.height+1,
	Window.col+Window.width+1,0x80,0x08); // vertical shadow
fillattr(Window.row+Window.height+1,Window.col+1,Window.row+Window.height+1,
	Window.col+Window.width+1,0x80,0x08); // horizontal shadow*/
}
//draw the scroll bar
System.screen[Window.row+2+(Window.height-4)*List.icursel/(List.count-1)]
	     [Window.col+Window.width].ch=4;//scroll point
System.screen[Window.row+1][Window.col+Window.width].ch=30; //up scroll
System.screen[Window.row+Window.height-1][Window.col+Window.width].ch=31;//down scroll

//write the string in range into the window;
for(i=Window.uprange;i<=Window.dnrange;i++)
	writetextxy(Window.row+1+i-Window.uprange,Window.col+1,
	(List.list+i*32),Window.width-1);

//mark the selected text;
//if(List.cursel!=NULL)	// is there a valid suggestion
fillattr(Window.row+1+List.icursel-Window.uprange,Window.col+1,
	Window.row+1+List.icursel-Window.uprange,Window.col+Window.width-1,0x7f,0x7f);

preicursel=List.icursel;// save previous cursel
}

//************************************************************
// queries mouse position
//saves the screen rectangle and draws the window there
void far showwindow()
{char r,c;
 //return;
 if(Window.enabled==0||Window.active==1) return;
 // setting proper ranges to be shown
 Window.uprange=List.icursel; // the window top
 Window.dnrange=List.icursel+Window.height-2;//Window bottom range
 if(Window.dnrange>=List.count) // is dnragne beyond List?
	{ Window.uprange-=(Window.dnrange-List.count+1); //setup them properly
	  Window.dnrange=List.count-1;
	}
 if(Window.trackcursor) // is cursor tracking enabled
 {	asm{mov ah,0x3;
	    mov bh,0;  int 0x10;
	    mov byte ptr r,dh;
	    mov byte ptr c,dl;
	    }//request the cursur position from ROM BIOS
	 if(r>25-Window.height-2) r-=(Window.height+1); else r++;
	 if(c>80-Window.width-2) c-=(Window.width+2);
	 Window.row=r;
	 Window.col=c;
 }
 setupmouse();
 Window.active=1;
 Hidemouse();// hide mouse
 savevedio(Window.row,Window.col,Window.row+Window.height,
	  Window.col+Window.width,Window.saved_data);
 /*savevedio(r,c,r+Window.height,c+Window.width,Window.saved_data);*/
 if(Window.shadow) saveshadowattr(); // save attributes under the shadow
 drawwindow();
  //set up the mouse
 Showmouse();// hide mouse
}
//************************************************************
void far hidewindow()
{if(!Window.active) return;
Window.active=0;
//return;
//
Hidemouse();// hide mouse
restorevedio(Window.row,Window.col,Window.row+Window.height,
  Window.col+Window.width,Window.saved_data);
if(Window.shadow) restoreshadowattr();
//restore privious mouse handler
restoremouse();
Showmouse();// hide mouse

}

void far scrolldown()
{
 if(!Window.active) return; // if window is not visible then return
 List.icursel++;
 if(List.icursel>=List.count) {List.icursel=List.count-1; return;}
 List.cursel=List.list+List.icursel*32;/**/
 drawwindow();
}

void far scrollup()
{ if(!Window.active) return;
  List.icursel--;
  if(List.icursel<0) {List.icursel=0;return;}
  List.cursel=List.list+List.icursel*32;
  drawwindow();
}

