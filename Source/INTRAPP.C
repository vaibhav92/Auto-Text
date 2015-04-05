//***********The Application Interrupt Handler************
#include <dos.h>
#include <_null.h>
#include "common.h"
#define HIWORD(x) (((x)&0xff00)>>8)
#define LOWORD(x) ((x)&0xff)


struct INTERRUPT{unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,fl;};

void far intrmouse();
extern void far setupmouse(void);// setup the mouse to process events
extern void far restoremouse(void);// restore mouse to privious state
/*struct Application
       {unsigned app_psp;
	void interrupt (far *oldapp)();// the old keyboard ISR
       }; //holds the Timer ISR data;
*/

//************** The application ISR***********************
void interrupt israpp(struct INTERRUPT r)
{

#ifdef debug
asm push ax;
asm pop ax;
#endif

if(HIWORD(r.ax)==0x6e)
   { switch(LOWORD(r.ax))
	{case 0x00: //request ping
		    r.ax|=0xff;   //yes I am alive
		    break;
	 case 0x02:  //request permanent unload
		      r.ax=0x6e04;
		      setvect(0x1c, Timer.oldtimer); //restore timer vector
		      setvect(0x2D, App.oldapp); //restore int 0x2d vector
		      setvect(0x9, Keyboard.oldkbd);//restore 0x9c vector
		      setvect(0x28,Timer.oldideal);//reatore 0x28 vector
		      freemem(FP_SEG(List.list)); // free allocated mem from far heap
		     // freemem(App.app_psp);// free the application code
		      freemem(*((int far*)MK_FP(App.app_psp,0x2C)));
		      //free environmental block
		      freemem(App.app_psp);// free the application code
		      return;
	case 0x10: //request address of List
		    r.ax=0x6e01;
		    r.dx=FP_SEG(&List);
		    r.di=FP_OFF(&List);
		    break;/**/
	case 0x11:// disable autocomplete
		  Keyboard.enabled=0;// disable the keyboard ISR
		  r.ax=0x6e01;
		  break;
	case 0x12:// enablea autocomplete
		  Keyboard.enabled=1;// disable the keyboard ISR
		  r.ax=0x6e01;
		  break;
	case 0x13:// disable popup window
		  Window.enabled=0;
		  r.ax=0x6e01;
		  break;
	case 0x14:// enable popup window
		  Window.enabled=1;
		  r.ax=0x6e01;
		  break;
	case 0x15://request status
		  r.ax=0x6e01;
		  r.bx= Keyboard.enabled|(Window.enabled<<1);
		  break;
	case 0x16://request my mouse handler address
		  r.ax=0x6e01;
		  r.dx= FP_OFF(intrmouse);
		  r.es= FP_SEG(intrmouse);
		  break;
	case 0x17://request old mouse handler address
		  r.ax=0x6e01;
		  r.dx= FP_OFF(Mouse.oldmouse);
		  r.es= FP_SEG(Mouse.oldmouse);
		  break;
	case 0x18://request setup mouse handler
		  setupmouse();
		  r.ax=0x6e01;
		  break;
	case 0x19://request restore mouse handler
		  restoremouse();
		  r.ax=0x6e01;
		  break;
	default:  // not an implemented feature;
		  r.ax=0x6e00;
		  break;
	}
   return;
   }

if(App.oldapp!=NULL) // if previous vectore was not null then call it
	{_AX=r.ax;_BX=r.bx;_CX=r.cx;_DX=r.dx;_ES=r.es;
	App.oldapp();
	asm pushf;
	asm pop word ptr r.fl;
	r.ax=_AX;r.bx=_BX;r.cx=_CX;r.dx=_DX;r.es=_ES;
	}
return;
}
