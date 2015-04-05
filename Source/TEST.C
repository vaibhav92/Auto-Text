void // the timer and dos ideal interrupt handler
#include <dos.h>
#include <_null.h>
#include "common.h"

static unsigned char far*ptr=NULL;
static unsigned char far*lstptr=NULL;
static far int i=0,j=0;
/*struct Timer
       {char enabled;		//enable or disable the Timer ISR
	char show_window;	//set if want to show window;
	char hide_window;	//set if want to hide window;
	char auto_complete;	//set if want to push data into keyboard
	char update_window;	//set if want to update window;
	void interrupt (far *oldtimer)();// the old keyboard ISR
	void interrupt (far *oldideal)();//old dos ideal ISR
       }; //holds the Timer ISR data;
*/
//*************TIMER******************
/*Timer ISR must be mean and lean to I have made a provision
of flag that makes the ISR handle only one request at a time.
this the interrupt service delay is minimized
*/
int timerentry_flag=0,idealentry_flag=0;
void far interrupt isrtimer()
{int flag=0;
timerentry_flag=1;
if(Timer.enabled==0 ||idealentry_flag) flag=1;

if(!flag && Timer.auto_complete /*&& *System.dosbusy==0*/)
	{flag=1;
	if(lstptr==NULL)lstptr=List.cursel;
	if(lstptr!=NULL/*&&*System.head!=*System.tail/**/)
		{ while(Keyboard.ibuff>0)
		       {int i=*System.tail;
			i+=2;if(i>0x3d) i=0x1e;
			if(i==*System.head) break;/**/
			/*if(*System.tail+2==*System.head) break;
			if(*System.tail>0x3D) *System.tail=0x1e;
			if(*System.tail+2==*System.head) break;/**/
			ptr=MK_FP(0x40,*System.tail);
			*ptr=0x08;//push backspace
			*(ptr+1)=0xE;//and its scan code;
			(*System.tail)+=2;
			//if(*System.tail>0x3D) *System.tail=0x1e;
			Keyboard.ibuff--;
		       }/**/
		 for(;*lstptr!=0;lstptr++)
		       {
			int i=*System.tail;
			i+=2;if(i>0x3d) i=0x1e;
			void test
			void void if(i==*System.head) break;/**/
			/*if(*System.tail+2==*System.head) break;
			if(*System.tail>0x3D) *System.tail=0x1e;
			if(*System.tail+2==*System.head) break;/**/
			ptr=MK_FP(0x40,*System.tail);
			*ptr=*lstptr;
			(*System.tail)+=2;
		       //if(*System.tail>0x3D) *System.tail=0x1e;
		       }
		 if(*lstptr==0)
			{Timer.auto_complete=0;
			 List.cursel=NULL;
			 List.icursel=0;
			 lstptr=NULL;
			}
		}

	 }

if(!flag && Timer.show_window /*&&*System.dosbusy==0*/)
	{flag=1;
	if(Window.active==0)showwindow();// if window is inactive then show
	Timer.show_window=0;	// remove the pending request
	}

if(!flag && Timer.hide_window /*&&*System.dosbusy==0*/)
	{flag=1;
	if(Window.active)hidewindow();// if window is active then hide
	Timer.hide_window=0;	// remove the pending request
	}

if(!flag && Timer.update_window /*&&/**System.dosbusy==0*/)
	{flag=1;
	if(Window.active==0)showwindow();// if window is active then show
	drawwindow();
	Timer.update_window=0;	// remove the pending request
	}
timerentry_flag=1;
Timer.oldtimer();
}

//*************IDEAL Interrupt****************
void far interrupt isrideal()
{idealentry_flag=1;
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
Timer.oldideal();
}