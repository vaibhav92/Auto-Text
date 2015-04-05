// the timer and dos ideal interrupt handler
#include <dos.h>
#include <_null.h>
#include "common.h"

/*struct Timer
       {char enabled;		//enable or disable the Timer ISR
	char show_winxitdow;	//set if want to show window;
	char hide_window;	//set if want to hide window;
	char auto_complete;	//set if want to push data into keyboard
	char update_window;	//set if want to update window;
	void interrupt (far *oldtimer)();// the old keyboard ISR
	void interrupt (far *oldideal)();//old dos ideal ISR
       }; //holds the Timer ISR data;
*/
// prototypes for the Window module used this module
extern void far showwindow();
extern void far hidewindow();
extern void far scrollup();
extern void far scrolldown();
extern void far drawwindow();
/********************************************************/
static unsigned char far*ptr=NULL;
static unsigned char far*lstptr=NULL;
static far int i=0,j=0;
static int far timerentry_flag=0,idealentry_flag=0;
static int far flag=0;
//*************TIMER******************
/*Timer ISR must be mean and lean so I have made a provision
of flag t	hat makes the ISR handle only one request at a time.
thus the interrupt service delay is minimized
*/

void interrupt isrtimer()
{
if(timerentry_flag) // previous request processing exit
	{ Timer.oldtimer();return;}
flag=0;
timerentry_flag=1;
//switching stack
disable();
Timer.oldstk=MK_FP(_SS,_SP);
_SS=FP_SEG(Timer.stack);
_SP=FP_OFF((Timer.stack+sizeof(Timer.stack)));
enable();/**/

//switching complete

if(Timer.enabled==0 ||idealentry_flag) flag=1;


if(!flag && Timer.auto_complete)
	{flag=1;
	if(lstptr==NULL)lstptr=List.cursel;
	if(lstptr!=NULL)
		{ while(Keyboard.ibuff>0)
		       {unsigned char i;
			 asm	{ mov ah,0x5;//request key push
				  mov cl,0x8;//push backspace
				  mov ch,0xE;//and its scancode
				  int 0x16;
				  mov byte ptr i,al;
				}
			if(i!=0) break; // is unsucessfull then break;
			Keyboard.ibuff--;
		       }/**/
		 for(;*lstptr!=0;lstptr++)
		       {unsigned char i;
			 _CX=*lstptr;
			 asm   { mov ah,0x5;//request key push
				 mov ch,0x0;//and its scancode
				 int 0x16;
				 mov byte ptr i,al;
			       }
			if(i!=0) break; // is unsucessfull then break;
			Keyboard.ibuff--;
		       }
		 if(*lstptr==0)// autocomplete is now complete
			{Timer.auto_complete=0;
			 List.cursel=NULL;
			 List.icursel=0;
			 lstptr=NULL;
			 Keyboard.ibuff=0;
			 Keyboard.waitforspace=1;//ask keyboard to wait for a space
			}
		}

	 }

if(!flag && Timer.scroll_down)
	{flag=1;
	if(Window.active) scrolldown();// is active then do it
	Timer.scroll_down--; //request has being handled
	}

if(!flag && Timer.scroll_up)
	{flag=1;
	if(Window.active) scrollup();// is active then do it
	Timer.scroll_up--; //request has being handled
	}

if(!flag && Timer.hide_window)
	{flag=1;
	if(Window.active)hidewindow();// if window is active then hide
	Timer.hide_window=0;	// remove the pending request
	}

if(!flag && Timer.show_window)
	{flag=1;
	if(Window.active==0)showwindow();// if window is inactive then show
	Timer.show_window=0;	// remove the pending request
	}

if(!flag && Timer.update_window)
	{flag=1;
	if(Window.active==0)showwindow();// if window is inactive then show
	drawwindow();
	Timer.update_window--;	// remove the pending request
	}
//switching to old stack
disable();
_SS=FP_SEG(Timer.oldstk);
_SP=FP_OFF(Timer.oldstk);
enable();
//switch complete/**/
timerentry_flag=0;
Timer.oldtimer();
}

//*************IDEAL Interrupt****************

void far interrupt isrideal()
{/*
idealentry_flag=1;
 if(Timer.enabled==0||timerentry_flag)
	{idealentry_flag=0;
	Timer.oldideal();
	return;
	}
if(Timer.auto_complete)
	{
	if(lstptr==NULL)lstptr=List.cursel;
	if(*System.head!=*System.tail)
		{ptr=MK_FP(0x40,*System.head);
		 while(Keyboard.ibuff>0)
		       {if(*System.tail==*System.head) break;
			ptr=MK_FP(0x40,*System.tail);
			*ptr=8;//push backspace
			*(ptr+1)=0xE;//and its scan code;
			(*System.tail)+=2;
			if(*System.tail>0x3D) *System.tail=0x1e;
			Keyboard.ibuff--;
		       }
		 for(;*lstptr!=0;lstptr++)
		       {ptr=MK_FP(0x40,*System.tail);
			*ptr=*lstptr;
			(*System.tail)+=2;
			if(*System.tail>0x3D) *System.tail=0x1e;
			if(*System.tail==*System.head) break;
		       }
		 if(*lstptr==0)
			{Timer.auto_complete=0;
			 List.cursel=NULL;
			 List.icursel=0;
			}
		}
	 }

if(Timer.show_window&&*System.dosbusy==0)
	{
	if(Window.active==0)showwindow();// if window is inactive then show
	Timer.show_window=0;	// remove the pending request
	}

if(Timer.hide_window&&*System.dosbusy==0)
	{
	if(Window.active)hidewindow();// if window is active then hide
	Timer.hide_window=0;	// remove the pending request
	}

if(Timer.update_window)
	{
	if(Window.active==0)showwindow();// if window is active then show
	drawwindow();
	Timer.update_window=0;	// remove the pending request
	}
idealentry_flag=0;
Timer.oldideal();*/
}