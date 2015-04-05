#include <dos.h>
#define HIWORD(x) (((x)&0xff00)>>8)
#define LOWORD(x) ((x)&0xff)

struct INTERRUPT{unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,fl;};
unsigned our_psp;
void interrupt (far *oldapp)();
void interrupt (far *oldkbd)();
void interrupt (far *oldtimer)();

void interrupt israpp(struct INTERRUPT r)
{if(HIWORD(r.ax)==0x6e)
   { switch(LOWORD(r.ax))
	{case 0x00: r.ax|=0xff;
		    break;
	 case 0x02:   r.ax=0x6e04;
		      setvect(0x1c, oldtimer);
		      setvect(0x2D, oldapp);
		      setvect(0x9, oldkbd);
		      freemem(our_psp);
		      return;
	 /*case 0x10: r.dx=FP_SEG(data);
		    r.di=FP_OFF(data);
		    break;/**/

	}
   return;
   }
if(oldapp!=0)
	{_AX=r.ax;_BX=r.bx;_CX=r.cx;_DX=r.dx;_ES=r.es;
	oldapp();
	asm pushf;
	asm pop word ptr r.fl;
	}
r.ax=_AX;r.bx=_BX;r.cx=_CX;r.dx=_DX;r.es=_ES;
}

