#include "d:\tc\head.c"
#include <string.h>
#include <ctype.h>
#define TIMER 0X1C
#define KBD 0X9
#define APP 0x2D
//#define SIZE 7

char far *data[]={"cls","clear","dir ","exit","mem/c","cd\\tc","cd.."};
int far SIZE=sizeof(data)/sizeof(data[0]);

unsigned far*head=MK_FP(0x40,0x1A);
unsigned far*tail=MK_FP(0x40,0x1C);
char far*screen=MK_FP(0xb800,0x00);

unsigned char far*ptr;
char far key;

char far buffer[10];
char ibuff=0;
char far autocomplete=0,far cursel=0;
int far i,far j;

//*************KEYBOARD******************
void interrupt isrkbd()
{key=inportb(0x60);
if(key==0x1&&cursel!=0)
	{cursel=0;
	 ibuff=0;
	 outportb(0x20,0x20);
	 return;
	}
if(autocomplete==0&&key==28&&cursel!=0&&data[cursel][ibuff-1]!=0)
	{autocomplete=1;
	outportb(0x20,0x20);
	//ibuff=0;
	return;
	}

oldkbd();
if (*head==*tail||autocomplete) return;


ptr=MK_FP(0x40,*head);

if(*ptr==8 &&ibuff>0) ibuff--;
if(!isprint(*ptr))
	{ if(*ptr!=8) ibuff=0;
	cursel=0;
	return;
	}

buffer[ibuff++]=*ptr;
ptr=screen;
for(i=0;i<ibuff;i++,ptr+=2)	*ptr=buffer[i];
cursel=0;
for(i=0;i<SIZE;i++)
	if(_fstrncmp(buffer,data[i],ibuff)==0)
		{ptr=screen+160+2*60;
		for(j=0;data[i][j]!=0;j++,ptr+=2)
			*ptr=data[i][j];
		cursel=i+1;
		break;
		}
if(ibuff>=7) ibuff=0;
}
//*************TIMER******************
void interrupt isrtimer()
{if(autocomplete!=0)
	{ptr=MK_FP(0x40,*head);
	*head=*tail=0x1e;
	for(i=ibuff;data[cursel-1][i]!=0;i++)
		{ptr=MK_FP(0x40,*tail);
		*ptr=data[cursel-1][i];
		(*tail)+=2;
		if(*tail>0x3D) *tail=0x1e;
		}
		autocomplete=0;
		cursel=0;
	}
oldtimer();
}



int main(void)
{ union REGS i,o;
struct SREGS s;

   /*i.h.ah=0x34;
   intdosx(&i,&o,&s);
   dosbusy=(char far*) MK_FP(s.es,o.x.bx);/**/
   our_psp=_psp;

   oldkbd = getvect(KBD);
   setvect(KBD, isrkbd);

   oldtimer= getvect(TIMER);
   setvect(TIMER, isrtimer);



   oldapp=getvect(APP);
   setvect(APP, israpp);
   keep(0, (_SS + (_SP/16) - _psp));
   return 0;
}