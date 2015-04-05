// The keyboard interrupt handler
#include <string.h>
#include <dos.h>
#include "scancode.h"
#include "common.h"

#define KBD 0X9
#define WAIT(x)  {asm sti;while(x);}
#define ACK_KBD()  asm {mov al,0x20;out 0x20,al;}
#define ISPRINT(c) ((c)>=0x20 && (c)<=0x7E)
#define ISSPACE(c) ((c)>=0x09 && (c)<=0x0D || (c)==0x20)
/*struct Keyboard
       {char enabled;		//enable or disable the Keyboard ISR
	char buffer[64];	//holds the key presses
	char ibuff;		// holds the index into buffer
	void interrupt (far *oldkbd)();// the old keyboard ISR
       }; //holds the keyboard ISR data;
*/

static unsigned char far*ptr=0;
static far int i=0,j=0;
//static far char key;

//*************KEYBOARD-ISR******************
void interrupt isrkbd()
{unsigned char key;
//reqesting cursor size from ROM-BIOS
asm{ xor ax,ax
  mov ah,0x3
  xor bx,bx
  int 0x10
  mov byte ptr key,ch
}
// is keyboard ISR is disabled OR autocomplete in progress
// OR cursor not visible then exit
if(Keyboard.enabled==0 || Timer.auto_complete || (key&0xE0)!=0)
	{Keyboard.oldkbd();
	return;
	}
/*if(Timer.auto_complete)	// is a autocomplete in progress
	{  //NOT inhibiting keypress
	   Keyboard.oldkbd();
	   //ACK_KBD();
	   //asm sti;// enable interrupts
	   return;
	}*/
//get the key scan-code and store it in variable 'key'
asm{ IN al,0x60; mov byte ptr key,al;}/**/
if(Keyboard.waitforspace) goto KBD_ROM_BIOS;

if(key==UPARROW && Window.active)
	{//inhibiting keypress
	ACK_KBD(); // acknowledge the keyboard
	Timer.scroll_up++; //request scroll up from timer
	WAIT(Timer.scroll_up);// wait untill request complete
	asm sti;//enable interrupts;
	return;
	}

if(key==DOWNARROW && Window.active)
	{
	ACK_KBD(); // acknowledge the keyboard
	Timer.scroll_down++; //request scroll down from timer
	WAIT(Timer.scroll_down);// wait untill request complete
	asm sti; //enable interrupts;
	return;
	}

if(key==ESCAPE && List.cursel!=NULL) //Is escape pressed with valid suggestion
	{ACK_KBD(); // acknowledge the keyboard
	 Keyboard.waitforspace=1;// wait untill current word is completed
	 List.icursel=-1;
	 List.cursel=NULL;
	 Keyboard.ibuff=0;//reset the keyboard buffer & selection

	 if(Window.active)
		{Timer.hide_window++;// request  hide of window
		 WAIT(Timer.hide_window); // wait till the window hides
		}
	 asm sti; //enable interrupts;
	 return;
	}

//if enter pressed with a valid selection
if(key==ENTER)
	{ if(Window.active) // FIRST hide the window
		{Timer.hide_window++;// request hide of window;
		 WAIT(Timer.hide_window);//wait till done
		}
	if(List.cursel!=NULL&&List.cursel[Keyboard.ibuff]!=0) // present selection not completed yet
		{ACK_KBD(); // acknowledge the keyboard
		Timer.auto_complete++;// ask timer to complete the text
		asm sti;
		//Keyboard.ibuff=0;
		return;
		}
	}/**/
//is backspace pressed
if(key==BKSPACE)
	{
	Keyboard.ibuff--; //if it is BKSPACE then decrment ibuff
	if (Keyboard.ibuff<=0)
		{//if user buffer empty then hide window;
		Keyboard.ibuff=0;
		List.icursel=0;
		List.cursel=NULL;
		if(Window.active)
			{Timer.hide_window++;
			WAIT(Timer.hide_window);// wait till done
			}
		}
	//Keyboard.oldkbd(); // call the ROM BIOS
	//return; // return the key pressed was not inhibited
	}

// call the ROM BIOS to handle the request
KBD_ROM_BIOS:    Keyboard.oldkbd();

// if keyboard buffer is empty return
if (*System.head==*System.tail) return;

ptr=MK_FP(0x40,*System.head);	//get ptr point to the new charecter;

//!!!!
//if(*ptr==' ' && Keyboard.waitforspace && List.icursel==NULL)
 //	{Keyboard.waitforspace=0;return;}
// if charecter is  printable charecter then store it in the buffer
if(ISSPACE(*ptr) && List.cursel==NULL)
	{Keyboard.waitforspace=0;
	 List.icursel=NULL;
	 List.cursel=NULL;
	 Keyboard.ibuff=0;
	 return;
	}

if(!ISPRINT(*ptr) && key!=BKSPACE)
	{Keyboard.waitforspace=0;
	 Keyboard.ibuff=0;
	 List.icursel=0;
	 List.cursel=NULL;
	 if(Window.active)
			{Timer.hide_window++;
			WAIT(Timer.hide_window);// wait till done
			}
	 return;
	}

if(Keyboard.waitforspace) return;

if(key!=BKSPACE)
Keyboard.buffer[Keyboard.ibuff++]=*ptr; // is key not backspace
// then save the char in buffer

#ifdef DEBUG
	for(i=0;i<Keyboard.ibuff;i++)
		System.screen[0][i].ch=Keyboard.buffer[i];
#endif

if(Keyboard.ibuff<Keyboard.minchars) return;

//now find the best match for completion from the list
List.icursel=0;
List.cursel=NULL;// reset previous selection

for(i=0;i<List.count;i++)
	if(_fstrncmp(Keyboard.buffer,&List.list[i*32],Keyboard.ibuff)==0)
	       {List.icursel=i;
		List.cursel=&List.list[i*32];//set the current selection
		#ifdef DEBUG
		for(i=0;List.cursel[i]!=0;i++)
		  System.screen[1][i].ch=List.cursel[i];
		#endif
		if(Window.active==0) Timer.show_window++;
		else Timer.update_window++;
		// if no popup is shown then show it other wise update it
		break;
		}

if(Window.active&&List.cursel==NULL) // is not suggestion & popup was visible
       {Timer.hide_window++;
	WAIT(Timer.hide_window);
       }

if(Keyboard.ibuff>=MAX_BUFF)
	 {Keyboard.ibuff=0;
	 Keyboard.waitforspace=1;
	 if(Window.active){Timer.hide_window++; WAIT(Timer.hide_window);}
	 }// buffer is now full reset it and set wait for space flag
}