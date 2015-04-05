//#define DEBUG
#define MAX_BUFF 30
#define HEIGHT 12
//#define WIDTH 40
#define WIDTH 30
#define WAIT(x)  {asm sti;while(x);}
#define Showmouse() asm{ mov ax,1; int 0x33}
#define Hidemouse()asm{ mov ax,2; int 0x33}

//common object interfaces header
struct List
       {int count;//the number of elements in the list
	int icursel;//the index of currently selecte element in the list
	char far *cursel; // pointer to currently selected element
	char far *list; // stores the list
       };

struct Window
       {char enabled;// show/not show the pop up window
	char active;// is the popup currently active or deactivated
	char row,col;//current location of popup window
	char height,width;
	char shadow;// wana show shadow?
	char trackcursor;//set if wana to track the cursor
	char maxheight,maxwidth;// minimum window size supported
	char minheight,minwidth;//maximum window size supported
	char bordercolor; // the border attribute for the border
	char fillcolor;// the fillin attribute for the window
	char saved_data[HEIGHT*WIDTH*2*sizeof(char)];// saves data on screen before poping up
	char s_vshadow[HEIGHT*sizeof(char)];// saves attribute data in vertical shadow
	char s_hshadow[WIDTH*sizeof(char)];// saves attribute data in horizontal shadow
	int uprange; // holds the upper most index to be show
	int dnrange; // holds the lower most index to be show
       //currently selected index is between the uprange and dnrange
	};// Holds data aboute the popup Window

struct System
       {unsigned far* head;//points-> start-offset into system kbd buff
	unsigned far* tail;//points-> end-offset into system kbd buff
	unsigned char far* keystatus;//points-> keyboard key status byte
	struct ch //structure to interface the screen memory
	    { unsigned char ch,attr;//holds display charecter & its attribute
	    } far *screen[25];
	    // The screen structure is an array of pointers to each row
	    // of the screen. ex screen[0][1].ch --accesses the first row and second column
	unsigned char far* dosbusy;
       }; //holds the System Memory Constants & Data;

struct Keyboard
       {char enabled;		//enable or disable the Keyboard ISR
	char buffer[MAX_BUFF];	//buffer that holds the key presses
	char ibuff;		// holds the index into buffer
	char waitforspace;	// if set then ISR Resets suggestions
				// & wait till a space  charecter is pressed
	unsigned char minchars; //minimun no. of chars that start autocomplete process
	void interrupt (far *oldkbd)();// the old keyboard ISR
       }; //holds the keyboard ISR data;

struct Timer
       {char enabled;		//enable or disable the Timer ISR
	char show_window;	//set if want to show window;
	char hide_window;	//set if want to hide window;
	char auto_complete;	//set if want to push data into keyboard
	char update_window;	//set if want to update window;
	char scroll_down;	//set if want to scroll window down;
	char scroll_up;		//set if want to scroll window up;
	void interrupt (far *oldtimer)();// the old keyboard ISR
	void interrupt (far *oldideal)();//old dos ideal ISR
	unsigned char stack[1024];// 1 KB of stack;
	//unsigned oldss,oldsp; //stores old values of Stack Segment & Pointer
	char far *oldstk;
       }; //holds the Timer ISR data;

struct Application
       {unsigned app_psp;
	unsigned app_ds;
	void interrupt (far *oldapp)();// the old keyboard ISR
       }; //holds the Timer ISR data;

struct Mouse
       {char enabled; // are mouse operations enabled
	char pivot;// stores the distance of mouse pointer from col while drag
	char dragging;// is mouse currently dragging
	char sizing;// is mouse currently sizing
       void (far *oldmouse)(void);// the old mouse ISR
       unsigned oldeventmask; // the event mask of old handler
       };

#ifndef MAIN
extern far struct Application App;
extern far struct Timer Timer;
extern far struct Keyboard Keyboard;
extern far struct System System;
extern far struct List List;
extern far struct Window Window;
extern far struct Mouse Mouse;
#else
extern far struct Application App={0};
extern far struct Timer Timer={0};
extern far struct Keyboard Keyboard={0};
extern far struct System System={0};
extern far struct List List={0};
extern far struct Window Window={0};
extern far struct Mouse Mouse={0};
#endif
