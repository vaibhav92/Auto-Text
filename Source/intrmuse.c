#include <_null.h>
#include <dos.h>
#include "common.h"

#define LEFTBUTTON 0x1
#define RIGHTBUTTON 0x2
#define CENTERBUTTON 0x4

extern void far showwindow();
extern void far hidewindow();
extern void far scrollup();
extern void far scrolldown();
extern void far drawwindow();
extern void far restorevedio(int r1,int c1,int r2,int c2,char far *svt);
extern void far savevedio(int r1,int c1,int r2,int c2,char far *svt);
enum Mouseevent {MS_MOVE=1,MS_LBDN=2,MS_LBUP=4,MS_RBDN=8,MS_CBDN=16,
		MS_CBUP=32};


//extern void far setupmouse(void);// setup the mouse to process events
//extern void far restoremouse(void);// restore mouse to privious state
/*struct Mouse
       {char enabled; // are mouse operations enabled
	char pivot;// stores the distance of mouse pointer from col while drag
	char dragging;// is mouse currently dragging
       void (far *oldmouse)(void);// the old mouse ISR
       unsigned oldeventmask; // the event mask of old handler
       };
    /**/

void far intrmouse()
{//long tmp;
unsigned event,row,col,buttonstatus,vmicky,hmicky,msdata;
int i,j;//variables for temporary storage
event=_AX; row=_DX; col=_CX;
buttonstatus=_BX;
vmicky=_SI;hmicky=_DI;msdata=_DS;
row>>=3;col>>=3;// make mouse coordinates to screen coordinates
/*asm{
push ds;
mov ax,word ptr App.app_ds;
mov ds,ax
}/**/

if(event&MS_LBUP && (Mouse.dragging || Mouse.sizing))
	{Mouse.dragging=0;
	 Mouse.sizing=0;
	 //Reseting mouse limits
	  asm{ mov ax, 0x7;// request function 7
		mov cx,0;
		mov dx,632;// maximum hz limit
		int 0x33;
		mov ax,0x8;//request function 8
		mov dx,192;// max vr limit
		int 0x33;// to the rom bios;
	      }
	return;
	}

if(event&MS_MOVE && Mouse.dragging) // should i drag?
	{
	  Hidemouse();
	  //restorevedio(Window.row,Window.col,Window.row+Window.height,Window.col+Window.width,Window.saved_data);
	  //Window.active=0;
	  hidewindow();
	  Window.trackcursor=0;
	  Window.row=row; // set new row;
	  Window.col= col-Mouse.pivot;// set new column with currection;
	  //savevedio(Window.row,Window.col,Window.row+Window.height,Window.col+Window.width,Window.saved_data);
	  //drawwindow();
	  showwindow();
	  Window.trackcursor=1;
	  Showmouse();
	}

if(event&MS_MOVE && Mouse.sizing) // should i resize
	{
	  Hidemouse();
	  //restorevedio(Window.row,Window.col,Window.row+Window.height,Window.col+Window.width,Window.saved_data);
	  //Window.active=0;
	  hidewindow();
	  Window.trackcursor=0;
	  Window.height=row-Window.row;// set new height
	  Window.width=col-Window.col;//set new width
	  //savevedio(Window.row,Window.col,Window.row+Window.height,Window.col+Window.width,Window.saved_data);
	  //drawwindow();
	  showwindow();
	  Window.trackcursor=1;
	  Showmouse();
	}

if(event&MS_MOVE || event&MS_LBUP) {/*asm pop ds;*/return;}

if(event&MS_LBDN)// the left button up event
	{//is it close window message
	  if(row==Window.row && col==Window.col)
		{ Hidemouse();
		  //Timer.hide_window++; // request window hide;
		  //WAIT(Timer.hide_window);
		  hidewindow();
		  Showmouse();
		  Keyboard.waitforspace=1;
		/*asm pop ds;*/
		return;
		}
	  //is it scroll up message
	  if(row==Window.row+1 && col==Window.col+Window.width)
		{Hidemouse();
		 Timer.scroll_up++;// request scroll up
		 WAIT(Timer.scroll_up);
		 //scrollup();
		 Showmouse();
		 /*asm pop ds;*/
		 return;
		}
	  //is it scroll down message
	  if(row==Window.row+Window.height-1 && col==Window.col+Window.width)
		{Hidemouse();
		 Timer.scroll_down++;// request scroll down
		 WAIT(Timer.scroll_down);
		 //scrolldown();
		 Showmouse();
		/*asm pop ds;*/
		return;
		}
	  //is it window move message
	  if(row==Window.row && col>Window.col && col <Window.col+Window.width)
	    {//System.screen[3][0].ch='+';
	     Mouse.pivot= col-Window.col; // set the mouse pivot
	     Mouse.dragging=1;
	     Mouse.pivot=j=col-Window.col; // set the mouse pivot
	     //calculate the hz limit of mouse
	     i=79-(Window.width-Mouse.pivot);
	     if(Window.shadow) i--; // is shadow is visible then -1
	      asm{ mov ax,0x7;// request function 0x7
		   mov cx,word ptr j;//min hz limit
		   shl cx,3; // convert to mouse coordinates
		   mov dx,word ptr i;//max hz limit
		   shl dx,3;//convert to mouse coordinates
		   int 0x33;// to the ROM BIOS
		 }
	     //calculate the hz limit of mouse
	     i=24-Window.height;
	     if (Window.shadow) i--; // if shadow then -1
	     asm{mov ax,0x8; // request function 0x8
		   xor cl,cl; // min vt limit
		   mov dx, word ptr i;//max vt limit
		   shl dx,3;// to the mouse coordinates
		   int 0x33;// to the ROM BIOS
		  }/**/
	    /*asm pop ds;*/
	    return;
	    }

	  //is it window resize message
	  if(row==Window.row+Window.height && col==Window.col+Window.width)
	    {System.screen[3][0].ch='+';
	     Mouse.sizing=1;
	     //calculate the min hz limit of mouse
	     i=Window.col+Window.minwidth;
	     //calculate the max hz limit of mouse
	     j=Window.col+Window.maxwidth;
	     if(j>=80) j=79-Window.shadow;
	      asm{ mov ax,0x7;// request function 0x7
		   mov cx,word ptr i;//min hz limit
		   shl cx,3; // convert to mouse coordinates
		   mov dx,word ptr j;//max hz limit
		   shl dx,3;//convert to mouse coordinates
		   int 0x33;// to the ROM BIOS
		 }
	     //calculate the min vr limit of mouse
	     i=Window.row+Window.minheight;
	     //calculate the max vr limit of mouse
	     j=Window.row+Window.maxheight;
	     //is max height beyond screen
	     if(j>=25) j=24-Window.shadow;
	     asm{mov ax,0x8; // request function 0x8
		   mov cl,byte ptr i; // min vt limit
		   shl cx,3; //to the mouse coordinates
		   mov dx, word ptr j;//max vt limit
		   shl dx,3;// to the mouse coordinates
		   int 0x33;// to the ROM BIOS
		  }/**/
	    /*asm pop ds;*/
	    return;
	    }
	  //is it within the text rectangle
	  if(row>Window.row && row<Window.row+Window.height
		&& col>Window.col && col<Window.col+Window.width)
		{int cursel=Window.uprange+row-Window.row-1;
		 if(cursel!=List.icursel)// is it new cursel
			 {List.icursel=cursel;
			 List.cursel=List.list+List.icursel*32;
			 Hidemouse();
			 //Timer.update_window++;
			 //WAIT(Timer.update_window);
			 drawwindow();
			 Showmouse();
			}else //set up current selection for autocomplete
			{Hidemouse();
			// Timer.hide_window++; // request hide window
			//WAIT(Timer.hide_window);
			 hidewindow();
			 Timer.auto_complete++;//ask timer to complete request
			 Showmouse();
			}
		 /*asm pop ds;*/
		 return;
		 }


	}
if(/*event&Mouse.oldeventmask &&*/ Mouse.oldmouse!=NULL)
	{ Hidemouse();
	  hidewindow();
	  Keyboard.waitforspace=1;
	  row<<=3,col<<=3;
	  asm{mov ax,msdata;
	      mov ds,ax;
	      mov di,hmicky;
	      mov si,vmicky;
	      mov dx,row;
	      mov cx,col;
	      mov bx,buttonstatus;
	      mov ax,event;
	     }
	   Showmouse();
	   Mouse.oldmouse();
	}
/*asm pop ds;*/
}

extern void far setupmouse(void)// setup the mouse to process events
{unsigned segm,offs,evnt;
//return;
asm{	 push es //save es
	 mov dx,offset intrmouse
	 mov ax,seg intrmouse //set to ISR
	 mov es,ax
	 mov cx,0x7f // request all events
	 mov ax,0x14 // request set up event handler
	 int 0x33 // To the mouse driver
	 mov evnt,cx //store previous event mask;
	 mov segm,es //store previus ISR Segment
	 mov offs,dx //& its offset
	 pop es// restore es
	}
Mouse.oldmouse=MK_FP(segm,offs);
Mouse.oldeventmask=evnt;
}/**/

extern void far restoremouse(void)// restore mouse to privious state
{unsigned segm,offs,evnt;
//return;
segm= FP_SEG(Mouse.oldmouse);
offs= FP_OFF(Mouse.oldmouse);
evnt=Mouse.oldeventmask;
asm{	 push es//save es
	 mov dx, word ptr offs
	 mov ax, word ptr segm //set to previous ISR
	 mov es,ax
	 mov cx,evnt // request previous event mask
	 mov ax,0x14// request set up event handler
	 int 0x33// To the mouse driver
	 pop es// restore es
	}
}