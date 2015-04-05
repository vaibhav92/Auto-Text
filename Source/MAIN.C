#define MAIN
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include "common.h"

#define TIMER 0X1C
#define KBD 0X9
#define APP 0x2D
#define IDEAL 0x28
#define COUNT 32	//max 32 entries in the list

//reduce heaplength and stacklength to make a smaller program in memory
extern unsigned _heaplen = 2048;
extern unsigned _stklen  = 1024;

//The ISR prototypes
extern void interrupt israpp();	// application interrupt
extern void interrupt isrkbd(); // Keyboard interrupt
extern void interrupt isrtimer();// Timer interrupt
extern void interrupt isrideal();// Dos Ideal interrupt
static char far buffer[33];

void bubblesort()
{int i,j;
for(j=0;j<List.count;j++)
	for(i=1;i<List.count-j;i++)
	if( _fstrcmp(&List.list[i*32],&List.list[(i-1)*32]) <0)
		{_fstrcpy(buffer,&List.list[i*32]);
		 _fstrcpy(&List.list[i*32],&List.list[(i-1)*32]);
		 _fstrcpy(&List.list[(i-1)*32],buffer);
		}
 /**/
}

//********************Application Entry Point****************
int main(void)
{unsigned j; char far *ptr,far *ptr2;
 FILE *fp;
 int i,*temp=(int*)malloc(2);

 void init();
// clrscr();
// Allocate the memory from DOS
 i=_dos_allocmem(COUNT*32*sizeof(char)/16,&j);
 if(i!=0)
	{printf("Failed to Allocate Memory");
	 return 1;
	}
 List.list=MK_FP(j,0000);
//Open the list file
 fp=fopen("list.txt","r");
 if(fp==NULL)
	{printf("Failed to open List File");
	return 2;
	}
//obtain the list and store it into the allocated array
ptr=List.list;
for(i=0;!feof(fp)&&i<COUNT;i++)
	{List.count++;
	 ptr=List.list+32*i;
	 for(*ptr=getc(fp),j=1;*ptr!=EOF   &&
				*ptr!='\n' &&
				j<29; *ptr=getc(fp),j++)
	 ptr++;

	 if(*ptr==EOF||*ptr=='\n') *ptr=0;
	 else *(ptr+1)=0;
	}
fclose(fp); // close the file pointer
bubblesort();
init(); //intialize the interrut vectors & Other Data structures
/**************************************************/
Window.enabled=1; // start the ISR routines
Keyboard.enabled=1;
Timer.enabled=1;
/**************************************************/
*temp=(_DS-_psp)+((unsigned)temp+2)/16+100;
keep(0, *temp);/**/
return 0;
}

// intialize all the data structures and return to main
void init()
{int i;
union REGS regs; struct SREGS sregs;
char far *scr=(char far *)MK_FP(0xb800,0000);

//nullify all the objects
_fmemset(&Window,0,sizeof(Window));
_fmemset(&Timer,0,sizeof(Timer));
_fmemset(&Keyboard,0,sizeof(Keyboard));
_fmemset(&System,0,sizeof(System));
_fmemset(&App,0,sizeof(App));
_fmemset(&System,0,sizeof(System));
//_fmemset(&List,0,sizeof(List));

//Initialize the List Structure
List.icursel=0;
List.cursel=NULL;
//Initialize the Window.structure
Window.trackcursor=1;// track the cursor
Window.shadow=1; 	// YES i wana shadow
Window.height=7;
Window.width=29;
Window.maxheight=HEIGHT;
Window.maxwidth=WIDTH;
Window.minheight=4;
Window.minwidth=10;
if(Window.height-2>List.count) Window.height=List.count+1;
// Initialize the System Structure
regs.h.ah = 0x34;	//reqest dos-ideal flag address
intdosx(&regs, &regs, &sregs);
System.dosbusy=(char far*) MK_FP(sregs.es,regs.x.bx); // store the address

for(i=0;i<25;i++,scr+=160)//initialize the screen interface data structure
	 System.screen[i]=(struct ch far *)scr;

System.head=MK_FP(0x40,0x1A); // Store the address of pointer to Keyboard Head
System.tail=MK_FP(0x40,0x1C); // Store the address of pointer to Keyboard Tail
System.keystatus=MK_FP(0x00,0x417);// store address of keyboard statud byte

// Initialize the System Application Data
App.app_psp=_psp;
App.app_ds=_DS;
//Initialize the mouse structure
Mouse.oldmouse=MK_FP(0x1234,0x5678);


//Initialize the Keyboard structure
Keyboard.minchars=2;  // minimum 2 charecter to start auto-complete





/*Initializing all Interrupt Vectors*/
//set the Keyboard Interrupt
	Keyboard.oldkbd = getvect(KBD);
	setvect(KBD, isrkbd);/**/

//set the Application Interrupt
	App.oldapp=getvect(APP);
	setvect(APP, israpp);/**/

//set the Dos Ideal Interrupt
	Timer.oldideal= getvect(IDEAL);
	setvect(IDEAL, isrideal);/**/

//set the Timer Interrupt
	Timer.oldtimer= getvect(TIMER);
	setvect(TIMER, isrtimer);/**/
}

