	ifndef	??version
?debug	macro
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	S "window.c"
	?debug	C E9F3B372310877696E646F772E63
	?debug	C E900185218122E2E5C696E636C7564655C5F6E756C6C2E68
	?debug	C E9F043733108636F6D6D6F6E2E68
_TEXT	segment byte public 'CODE'
_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
WINDOW5_DATA	segment para public 'FAR_DATA'
caption	label	byte
	db	65
	db	117
	db	116
	db	111
	db	116
	db	101
	db	120
	db	116
	db	0
WINDOW5_DATA	ends
_TEXT	segment byte public 'CODE'
   ;	
   ;	static void far box(char r1,char c1,char r2,char c2,char attr)
   ;	
	assume	cs:_TEXT
box	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
   ;	
   ;	{char i,inc;
   ;	 inc=c2>c1?1:-1;
   ;	
	mov	al,byte ptr [bp+12]
	cmp	al,byte ptr [bp+8]
	jle	short @1@86
	mov	al,1
	jmp	short @1@114
@1@86:
	mov	al,255
@1@114:
	mov	byte ptr [bp-1],al
   ;	
   ;	 for(i=c1;i!=c2;i+=inc)
   ;	
	mov	al,byte ptr [bp+8]
	mov	cl,al
	jmp	@1@422
@1@142:
   ;	
   ;		{if(i<0 ||i>=80) continue;
   ;	
	or	cl,cl
	jl	short @1@198
	cmp	cl,80
	jl	short @1@226
@1@198:
	jmp	@1@394
@1@226:
   ;	
   ;		 if(r1>=0 && r1<25) System.screen[r1][i].ch=' ',
   ;	
	cmp	byte ptr [bp+6],0
	jl	short @1@310
	cmp	byte ptr [bp+6],25
	jge	short @1@310
   ;	
   ;				    System.screen[r1][i].attr=attr;
   ;	
	mov	al,byte ptr [bp+6]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	mov	byte ptr es:[bx],32
	mov	al,byte ptr [bp+6]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	mov	byte ptr es:[bx+1],al
@1@310:
   ;	
   ;		 if(r2>=0 && r2<25) System.screen[r2][i].ch=' ',
   ;	
	cmp	byte ptr [bp+10],0
	jl	short @1@394
	cmp	byte ptr [bp+10],25
	jge	short @1@394
   ;	
   ;				    System.screen[r2][i].attr=attr;
   ;	
	mov	al,byte ptr [bp+10]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	mov	byte ptr es:[bx],32
	mov	al,byte ptr [bp+10]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	mov	byte ptr es:[bx+1],al
@1@394:
	mov	al,byte ptr [bp-1]
	add	cl,al
@1@422:
	mov	al,cl
	cmp	al,byte ptr [bp+12]
	je	@@0
	jmp	@1@142
@@0:
   ;	
   ;		}/**/
   ;	 inc=r2>r1?1:-1;
   ;	
	mov	al,byte ptr [bp+10]
	cmp	al,byte ptr [bp+6]
	jle	short @1@506
	mov	al,1
	jmp	short @1@534
@1@506:
	mov	al,255
@1@534:
	mov	byte ptr [bp-1],al
   ;	
   ;	 for(i=r1;i!=r2+inc;i+=inc)
   ;	
	mov	al,byte ptr [bp+6]
	mov	cl,al
	jmp	@1@842
@1@562:
   ;	
   ;		{if(i<0 ||i>=25) continue;
   ;	
	or	cl,cl
	jl	short @1@618
	cmp	cl,25
	jl	short @1@646
@1@618:
	jmp	@1@814
@1@646:
   ;	
   ;		 if(c1>=0 && c1<80) System.screen[i][c1].ch=' ',
   ;	
	cmp	byte ptr [bp+8],0
	jl	short @1@730
	cmp	byte ptr [bp+8],80
	jge	short @1@730
   ;	
   ;				    System.screen[i][c1].attr=attr;
   ;	
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp+8]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	byte ptr es:[bx],32
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp+8]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	mov	byte ptr es:[bx+1],al
@1@730:
   ;	
   ;		 if(c2>=0 && c2<80) System.screen[i][c2].ch=' ',
   ;	
	cmp	byte ptr [bp+12],0
	jl	short @1@814
	cmp	byte ptr [bp+12],80
	jge	short @1@814
   ;	
   ;				    System.screen[i][c2].attr=attr;
   ;	
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp+12]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	byte ptr es:[bx],32
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp+12]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	mov	byte ptr es:[bx+1],al
@1@814:
	mov	al,byte ptr [bp-1]
	add	cl,al
@1@842:
	mov	al,byte ptr [bp+10]
	cbw	
	push	ax
	mov	al,byte ptr [bp-1]
	cbw	
	pop	dx
	add	dx,ax
	mov	al,cl
	cbw	
	cmp	dx,ax
	je	@@1
	jmp	@1@562
@@1:
   ;	
   ;		}/**/
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
box	endp
   ;	
   ;	static void far writetextxy(char r,char c,char far*str,int width)
   ;	
	assume	cs:_TEXT
writetextxy	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	mov	cl,byte ptr [bp+8]
	mov	si,word ptr [bp+14]
   ;	
   ;	{
   ;	if(r<0 || r>24) return;
   ;	
	cmp	byte ptr [bp+6],0
	jl	short @2@86
	cmp	byte ptr [bp+6],24
	jle	short @2@114
@2@86:
	jmp	@2@786
@2@114:
	jmp	short @2@226
@2@142:
   ;	
   ;	 for(;*str&&width>3&&c<80;c++,str++,width--)
   ;		if(c>=0)System.screen[r][c].ch=*str;
   ;	
	or	cl,cl
	jl	short @2@198
	mov	al,byte ptr [bp+6]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	push	es
	les	di,dword ptr [bp+10]
	mov	al,byte ptr es:[di]
	pop	es
	mov	byte ptr es:[bx],al
@2@198:
	inc	cl
	inc	word ptr [bp+10]
	dec	si
@2@226:
	les	bx,dword ptr [bp+10]
	cmp	byte ptr es:[bx],0
	je	short @2@310
	cmp	si,3
	jle	short @2@310
	cmp	cl,80
	jl	short @2@142
@2@310:
   ;	
   ;	 if(*str)
   ;	
	les	bx,dword ptr [bp+10]
	cmp	byte ptr es:[bx],0
	jne	@@2
	jmp	@2@786
@@2:
   ;	
   ;	    { if(str[1]==0 || str[2]==0 || str[3]==0)
   ;	
	les	bx,dword ptr [bp+10]
	cmp	byte ptr es:[bx+1],0
	je	short @2@422
	les	bx,dword ptr [bp+10]
	cmp	byte ptr es:[bx+2],0
	je	short @2@422
	les	bx,dword ptr [bp+10]
	cmp	byte ptr es:[bx+3],0
	jne	short @2@618
@2@422:
	jmp	short @2@534
@2@450:
   ;	
   ;		  for(;width>0 && c<80;str++,width--,c++)
   ;		      {if(c>=0)System.screen[r][c].ch=*str;}
   ;	
	or	cl,cl
	jl	short @2@506
	mov	al,byte ptr [bp+6]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	push	es
	les	di,dword ptr [bp+10]
	mov	al,byte ptr es:[di]
	pop	es
	mov	byte ptr es:[bx],al
@2@506:
	inc	word ptr [bp+10]
	dec	si
	inc	cl
@2@534:
	or	si,si
	jle	short @2@590
	cmp	cl,80
	jl	short @2@450
@2@590:
	jmp	short @2@786
@2@618:
	jmp	short @2@730
@2@646:
   ;	
   ;		 else
   ;		    for(;width>0 && c<80;width--,c++)
   ;		      {if(c>=0)System.screen[r][c].ch='.'
   ;	
	or	cl,cl
	jl	short @2@702
   ;	
   ;		      ;}
   ;	
	mov	al,byte ptr [bp+6]
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,cl
	cbw	
	shl	ax,1
	add	bx,ax
	mov	byte ptr es:[bx],46
@2@702:
	dec	si
	inc	cl
@2@730:
	or	si,si
	jle	short @2@786
	cmp	cl,80
	jl	short @2@646
@2@786:
   ;	
   ;	    }
   ;	}
   ;	
	pop	di
	pop	si
	pop	bp
	ret	
writetextxy	endp
   ;	
   ;	static void far fillattr(char r1,char c1,char r2,char c2,unsigned char attr_and,
   ;	
	assume	cs:_TEXT
fillattr	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
   ;	
   ;			unsigned char attr_xor)
   ;	{char i,j,inci,incj;
   ;	  inci=r2>r1?1:-1;
   ;	
	mov	al,byte ptr [bp+10]
	cmp	al,byte ptr [bp+6]
	jle	short @3@86
	mov	al,1
	jmp	short @3@114
@3@86:
	mov	al,255
@3@114:
	mov	byte ptr [bp-2],al
   ;	
   ;	  incj= c2>c1?1:-1;
   ;	
	mov	al,byte ptr [bp+12]
	cmp	al,byte ptr [bp+8]
	jle	short @3@170
	mov	al,1
	jmp	short @3@198
@3@170:
	mov	al,255
@3@198:
	mov	byte ptr [bp-3],al
   ;	
   ;	  for(i=r1;i!=r2+inci;i+=inci)
   ;	
	mov	al,byte ptr [bp+6]
	mov	cl,al
	jmp	@3@534
@3@226:
   ;	
   ;		{if(i<0||i>=25) continue;
   ;	
	or	cl,cl
	jl	short @3@282
	cmp	cl,25
	jl	short @3@310
@3@282:
	jmp	short @3@506
@3@310:
   ;	
   ;		for(j=c1;j!=c2+incj;j+=incj)
   ;	
	mov	al,byte ptr [bp+8]
	mov	byte ptr [bp-1],al
	jmp	short @3@478
@3@338:
   ;	
   ;			{if(j<0||j>=80) continue;
   ;	
	cmp	byte ptr [bp-1],0
	jl	short @3@394
	cmp	byte ptr [bp-1],80
	jl	short @3@422
@3@394:
	jmp	short @3@450
@3@422:
   ;	
   ;			System.screen[i][j].attr&=attr_and;
   ;	
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp-1]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	and	byte ptr es:[bx+1],al
   ;	
   ;			System.screen[i][j].attr^=attr_xor;
   ;	
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp-1]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+16]
	xor	byte ptr es:[bx+1],al
@3@450:
	mov	al,byte ptr [bp-3]
	add	byte ptr [bp-1],al
@3@478:
	mov	al,byte ptr [bp+12]
	cbw	
	push	ax
	mov	al,byte ptr [bp-3]
	cbw	
	pop	dx
	add	dx,ax
	mov	al,byte ptr [bp-1]
	cbw	
	cmp	dx,ax
	jne	short @3@338
@3@506:
	mov	al,byte ptr [bp-2]
	add	cl,al
@3@534:
	mov	al,byte ptr [bp+10]
	cbw	
	push	ax
	mov	al,byte ptr [bp-2]
	cbw	
	pop	dx
	add	dx,ax
	mov	al,cl
	cbw	
	cmp	dx,ax
	je	@@3
	jmp	@3@226
@@3:
   ;	
   ;			}/**/
   ;		}
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
fillattr	endp
   ;	
   ;	static void far fillchar(char r1,char c1,char r2,char c2,char c)
   ;	
	assume	cs:_TEXT
fillchar	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
   ;	
   ;	{char i,j,inci,incj;
   ;	  inci=r2>r1?1:-1;
   ;	
	mov	al,byte ptr [bp+10]
	cmp	al,byte ptr [bp+6]
	jle	short @4@86
	mov	al,1
	jmp	short @4@114
@4@86:
	mov	al,255
@4@114:
	mov	byte ptr [bp-2],al
   ;	
   ;	  incj= c2>c1?1:-1;
   ;	
	mov	al,byte ptr [bp+12]
	cmp	al,byte ptr [bp+8]
	jle	short @4@170
	mov	al,1
	jmp	short @4@198
@4@170:
	mov	al,255
@4@198:
	mov	byte ptr [bp-3],al
   ;	
   ;	  for(i=r1;i!=r2+inci;i+=inci)
   ;	
	mov	al,byte ptr [bp+6]
	mov	cl,al
	jmp	short @4@534
@4@226:
   ;	
   ;		{if(i<0||i>=25) continue;
   ;	
	or	cl,cl
	jl	short @4@282
	cmp	cl,25
	jl	short @4@310
@4@282:
	jmp	short @4@506
@4@310:
   ;	
   ;		for(j=c1;j!=c2+incj;j+=incj)
   ;	
	mov	al,byte ptr [bp+8]
	mov	byte ptr [bp-1],al
	jmp	short @4@478
@4@338:
   ;	
   ;			{if(j<0||j>=80) continue;
   ;	
	cmp	byte ptr [bp-1],0
	jl	short @4@394
	cmp	byte ptr [bp-1],80
	jl	short @4@422
@4@394:
	jmp	short @4@450
@4@422:
   ;	
   ;			System.screen[i][j].ch=c;
   ;	
	mov	al,cl
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	al,byte ptr [bp-1]
	cbw	
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr [bp+14]
	mov	byte ptr es:[bx],al
@4@450:
	mov	al,byte ptr [bp-3]
	add	byte ptr [bp-1],al
@4@478:
	mov	al,byte ptr [bp+12]
	cbw	
	push	ax
	mov	al,byte ptr [bp-3]
	cbw	
	pop	dx
	add	dx,ax
	mov	al,byte ptr [bp-1]
	cbw	
	cmp	dx,ax
	jne	short @4@338
@4@506:
	mov	al,byte ptr [bp-2]
	add	cl,al
@4@534:
	mov	al,byte ptr [bp+10]
	cbw	
	push	ax
	mov	al,byte ptr [bp-2]
	cbw	
	pop	dx
	add	dx,ax
	mov	al,cl
	cbw	
	cmp	dx,ax
	jne	short @4@226
   ;	
   ;			}/**/
   ;		}
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
fillchar	endp
   ;	
   ;	static void far saveshadowattr()
   ;	
	assume	cs:_TEXT
saveshadowattr	proc	far
	push	bp
	mov	bp,sp
	push	si
   ;	
   ;	{int i;
   ;	//save vertical shadow attributes
   ;	  for(i=Window.row+1;i<=Window.row+Window.height+1;i++)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	inc	ax
	mov	si,ax
	jmp	short @5@114
@5@58:
   ;	
   ;	     Window.s_vshadow[i-Window.row-1]=
   ;	
   ;	
   ;		System.screen[i][Window.col+Window.width+1].attr;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	inc	dx
	shl	dx,1
	mov	bx,si
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+12]
	add	bx,dx
	mov	al,byte ptr es:[bx+1]
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	bx,si
	sub	bx,ax
	mov	ax,seg _Window
	mov	es,ax
	pop	ax
	mov	byte ptr es:_Window[bx+973],al
	inc	si
@5@114:
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	dx
	add	dx,ax
	inc	dx
	cmp	dx,si
	jge	short @5@58
   ;	
   ;	//save horizontal shadow attributes
   ;	  for(i=Window.col+1;i<=Window.col+Window.width;i++)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	inc	ax
	mov	si,ax
	jmp	short @5@226
@5@170:
   ;	
   ;	     Window.s_hshadow[i-Window.col-1]=
   ;	
   ;	
   ;	     System.screen[Window.row+Window.height+1][i].attr;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	bx
	add	bx,ax
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+16]
	mov	ax,si
	shl	ax,1
	add	bx,ax
	mov	al,byte ptr es:[bx+1]
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	bx,si
	sub	bx,ax
	mov	ax,seg _Window
	mov	es,ax
	pop	ax
	mov	byte ptr es:_Window[bx+985],al
	inc	si
@5@226:
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	cmp	dx,si
	jge	short @5@170
   ;	
   ;	}
   ;	
	pop	si
	pop	bp
	ret	
saveshadowattr	endp
   ;	
   ;	static void far restoreshadowattr()
   ;	
	assume	cs:_TEXT
restoreshadowattr	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
   ;	
   ;	{int i;
   ;	//restore vertical shadow attributes
   ;	  for(i=Window.row+1;i<=Window.row+Window.height+1;i++)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	inc	ax
	mov	si,ax
	jmp	short @6@114
@6@58:
   ;	
   ;		System.screen[i][Window.col+Window.width+1].attr=
   ;	
   ;	
   ;		     Window.s_vshadow[i-Window.row-1];
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	inc	dx
	shl	dx,1
	mov	bx,si
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+12]
	add	bx,dx
	mov	ax,seg _Window
	push	es
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	di,si
	sub	di,ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window[di+973]
	pop	es
	mov	byte ptr es:[bx+1],al
	inc	si
@6@114:
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	dx
	add	dx,ax
	inc	dx
	cmp	dx,si
	jge	short @6@58
   ;	
   ;	//restore horizontal shadow attributes
   ;	  for(i=Window.col+1;i<=Window.col+Window.width;i++)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	inc	ax
	mov	si,ax
	jmp	short @6@226
@6@170:
   ;	
   ;	    System.screen[Window.row+Window.height+1][i].attr=
   ;	
   ;	
   ;		 Window.s_hshadow[i-Window.col-1];
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	bx
	add	bx,ax
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+16]
	mov	ax,si
	shl	ax,1
	add	bx,ax
	mov	ax,seg _Window
	push	es
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	di,si
	sub	di,ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window[di+985]
	pop	es
	mov	byte ptr es:[bx+1],al
	inc	si
@6@226:
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	cmp	dx,si
	jge	short @6@170
   ;	
   ;	}
   ;	
	pop	di
	pop	si
	pop	bp
	ret	
restoreshadowattr	endp
   ;	
   ;	static void far savevedio(int r1,int c1,int r2,int c2,char far*svt)
   ;	
	assume	cs:_TEXT
savevedio	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	mov	si,word ptr [bp+6]
	mov	di,word ptr [bp+8]
	mov	cx,word ptr [bp+12]
   ;	
   ;	{char far *ptr=(char far*)System.screen[0]+r1*160+c1*2;
   ;	
	mov	ax,si
	mov	dx,160
	imul	dx
	mov	dx,seg _System
	mov	es,dx
	mov	dx,word ptr es:_System+14
	mov	bx,word ptr es:_System+12
	add	bx,ax
	mov	ax,di
	shl	ax,1
	add	bx,ax
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],bx
	jmp	short @7@198
@7@58:
   ;	
   ;	//char far *svt=Window.saved_data;
   ;	 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
   ;		  for(i=c1;i<=c2;i++)
   ;	
	mov	ax,seg i
	mov	es,ax
	mov	word ptr es:i,di
	jmp	short @7@142
@7@86:
   ;	
   ;		  {*svt++=*ptr++;
   ;	
	les	bx,dword ptr [bp-4]
	mov	al,byte ptr es:[bx]
	les	bx,dword ptr [bp+14]
	mov	byte ptr es:[bx],al
	inc	word ptr [bp-4]
	inc	word ptr [bp+14]
   ;	
   ;		   *svt++=*ptr++;
   ;	
	les	bx,dword ptr [bp-4]
	mov	al,byte ptr es:[bx]
	les	bx,dword ptr [bp+14]
	mov	byte ptr es:[bx],al
	inc	word ptr [bp-4]
	inc	word ptr [bp+14]
	mov	ax,seg i
	mov	es,ax
	inc	word ptr es:i
@7@142:
	mov	ax,seg i
	mov	es,ax
	mov	ax,word ptr es:i
	cmp	ax,cx
	jle	short @7@86
	inc	si
	mov	ax,cx
	sub	ax,di
	inc	ax
	shl	ax,1
	mov	dx,160
	sub	dx,ax
	add	word ptr [bp-4],dx
@7@198:
	cmp	si,word ptr [bp+10]
	jle	short @7@58
   ;	
   ;		  }
   ;	}
   ;	
	pop	di
	pop	si
	mov	sp,bp
	pop	bp
	ret	
savevedio	endp
   ;	
   ;	static void far restorevedio(int r1,int c1,int r2,int c2,char far *svt)
   ;	
	assume	cs:_TEXT
restorevedio	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	mov	si,word ptr [bp+6]
	mov	di,word ptr [bp+8]
	mov	cx,word ptr [bp+12]
   ;	
   ;	{char far *ptr=(char far*)System.screen[0]+r1*160+c1*2;
   ;	
	mov	ax,si
	mov	dx,160
	imul	dx
	mov	dx,seg _System
	mov	es,dx
	mov	dx,word ptr es:_System+14
	mov	bx,word ptr es:_System+12
	add	bx,ax
	mov	ax,di
	shl	ax,1
	add	bx,ax
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],bx
	jmp	short @8@198
@8@58:
   ;	
   ;	//char far *svt=Window.saved_data;
   ;	 for(;r1<=r2;r1++,ptr+=160-(c2-c1+1)*2)
   ;	       for(i=c1;i<=c2;i++)
   ;	
	mov	ax,seg i
	mov	es,ax
	mov	word ptr es:i,di
	jmp	short @8@142
@8@86:
   ;	
   ;		  {*ptr++=*svt++;
   ;	
	les	bx,dword ptr [bp+14]
	mov	al,byte ptr es:[bx]
	les	bx,dword ptr [bp-4]
	mov	byte ptr es:[bx],al
	inc	word ptr [bp+14]
	inc	word ptr [bp-4]
   ;	
   ;		   *ptr++=*svt++;
   ;	
	les	bx,dword ptr [bp+14]
	mov	al,byte ptr es:[bx]
	les	bx,dword ptr [bp-4]
	mov	byte ptr es:[bx],al
	inc	word ptr [bp+14]
	inc	word ptr [bp-4]
	mov	ax,seg i
	mov	es,ax
	inc	word ptr es:i
@8@142:
	mov	ax,seg i
	mov	es,ax
	mov	ax,word ptr es:i
	cmp	ax,cx
	jle	short @8@86
	inc	si
	mov	ax,cx
	sub	ax,di
	inc	ax
	shl	ax,1
	mov	dx,160
	sub	dx,ax
	add	word ptr [bp-4],dx
@8@198:
	cmp	si,word ptr [bp+10]
	jle	short @8@58
   ;	
   ;		  }
   ;	}
   ;	
	pop	di
	pop	si
	mov	sp,bp
	pop	bp
	ret	
restorevedio	endp
   ;	
   ;	void far drawwindow()
   ;	
	assume	cs:_TEXT
_drawwindow	proc	far
	push	bp
	mov	bp,sp
   ;	
   ;	{if(!Window.active) return;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+1
	cbw	
	or	ax,ax
	jne	short @9@86
	jmp	@9@450
@9@86:
   ;	
   ;	if(List.icursel<Window.uprange || List.icursel >Window.dnrange) // is cursel in range?
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg _Window
	mov	es,dx
	cmp	ax,word ptr es:_Window+1026
	jl	short @9@142
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg _Window
	mov	es,dx
	cmp	ax,word ptr es:_Window+1028
	jg	@@4
	jmp	@9@254
@@4:
@9@142:
   ;	
   ;		{Window.uprange=List.icursel- (preicursel-Window.uprange);
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg preicursel
	mov	es,dx
	mov	dx,word ptr es:preicursel
	mov	bx,seg _Window
	mov	es,bx
	sub	dx,word ptr es:_Window+1026
	sub	ax,dx
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1026,ax
   ;	
   ;		 Window.dnrange=List.icursel+(Window.dnrange-preicursel);
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg _Window
	mov	es,dx
	mov	dx,word ptr es:_Window+1028
	mov	bx,seg preicursel
	mov	es,bx
	sub	dx,word ptr es:preicursel
	add	ax,dx
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1028,ax
   ;	
   ;		 if(Window.uprange<0)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	word ptr es:_Window+1026,0
	jge	short @9@198
   ;	
   ;			{Window.uprange=0;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	word ptr es:_Window+1026,0
   ;	
   ;			 Window.dnrange= Window.height-3;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+4
	cbw	
	add	ax,65533
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1028,ax
@9@198:
   ;	
   ;			}
   ;		if(Window.dnrange>=List.count)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	ax,word ptr es:_Window+1028
	mov	dx,seg _List
	mov	es,dx
	cmp	ax,word ptr es:_List
	jl	short @9@254
   ;	
   ;			  {Window.dnrange=List.count-1;
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List
	dec	ax
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1028,ax
   ;	
   ;			   Window.uprange=Window.dnrange-Window.height+2;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+4
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	mov	dx,word ptr es:_Window+1028
	sub	dx,ax
	add	dx,2
	mov	ax,seg _Window
	mov	es,ax
	mov	word ptr es:_Window+1026,dx
@9@254:
   ;	
   ;			  }
   ;		}
   ;	//erase all the contents of the rectangle & draw the box
   ;	box(Window.row,Window.col,Window.row+Window.height,
   ;	
   ;	
   ;		Window.col+Window.width,WHITE<<3);
   ;	
	mov	al,120
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	push	ax
	push	cs
	call	near ptr box
	add	sp,10
   ;	
   ;	fillattr(Window.row+1,Window.col+1,Window.row+Window.height-1,
   ;	
   ;	
   ;		Window.col+Window.width-1,0,BLUE<<4|BLACK);
   ;	
	mov	al,16
	push	ax
	mov	al,0
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	inc	al
	push	ax
	push	cs
	call	near ptr fillattr
	add	sp,12
   ;	
   ;	fillchar(Window.row+1,Window.col+1,Window.row+Window.height-1,
   ;	
   ;	
   ;		Window.col+Window.width-1,' ');
   ;	
	mov	al,32
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	inc	al
	push	ax
	push	cs
	call	near ptr fillchar
	add	sp,10
   ;	
   ;	
   ;	System.screen[Window.row][Window.col].ch=254;// close window marker
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	shl	ax,1
	shl	ax,1
	mov	dx,seg _System
	mov	bx,ax
	mov	es,dx
	les	bx,dword ptr es:_System[bx+12]
	mov	ax,seg _Window
	push	es
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	shl	ax,1
	add	bx,ax
	pop	es
	mov	byte ptr es:[bx],254
   ;	
   ;	System.screen[Window.row][Window.col+Window.width].ch=240; //track cursor marker
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	shl	dx,1
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	shl	ax,1
	shl	ax,1
	mov	bx,seg _System
	mov	es,bx
	mov	bx,ax
	les	bx,dword ptr es:_System[bx+12]
	add	bx,dx
	mov	byte ptr es:[bx],240
   ;	
   ;	System.screen[Window.row+Window.height][Window.col+Window.width].ch=249;//size window marker
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	bx
	add	bx,ax
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+12]
	mov	ax,seg _Window
	push	es
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	bx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	shl	dx,1
	pop	bx
	add	bx,dx
	pop	es
	mov	byte ptr es:[bx],249
   ;	
   ;	
   ;	fillattr(Window.row,Window.col+1,Window.row,Window.col+Window.width-1,0,0x7B);
   ;	
	mov	al,123
	push	ax
	mov	al,0
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	push	ax
	push	cs
	call	near ptr fillattr
	add	sp,12
   ;	
   ;	writetextxy(Window.row,Window.col+1,caption,Window.width-2);
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+5
	cbw	
	add	ax,65534
	push	ax
	mov	ax,WINDOW5_DATA
	push	ax
	mov	ax,offset caption
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	push	ax
	push	cs
	call	near ptr writetextxy
	add	sp,10
   ;	
   ;	
   ;	//drawing shadow
   ;	if(Window.shadow)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	byte ptr es:_Window+6,0
	jne	@@5
	jmp	@9@310
@@5:
   ;	
   ;	{
   ;	fillattr(Window.row+1,Window.col+Window.width+1,Window.row+Window.height+1,
   ;	
   ;	
   ;		Window.col+Window.width+1,0x80,0x08); // vertical shadow
   ;	
	mov	al,8
	push	ax
	mov	al,128
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	inc	al
	push	ax
	push	cs
	call	near ptr fillattr
	add	sp,12
   ;	
   ;	fillattr(Window.row+Window.height+1,Window.col+1,Window.row+Window.height+1,
   ;	
   ;	
   ;		Window.col+Window.width+1,0x80,0x08); // horizontal shadow*/
   ;	
	mov	al,8
	push	ax
	mov	al,128
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+4
	inc	al
	push	ax
	push	cs
	call	near ptr fillattr
	add	sp,12
@9@310:
   ;	
   ;	}
   ;	//draw the scroll bar
   ;	System.screen[Window.row+2+(Window.height-4)*List.icursel/(List.count-1)]
   ;	
   ;	
   ;		     [Window.col+Window.width].ch=4;//scroll point
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	shl	dx,1
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	bx,seg _Window
	mov	es,bx
	push	dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	add	ax,65532
	mov	dx,seg _List
	mov	es,dx
	imul	word ptr es:_List+2
	mov	dx,seg _List
	mov	es,dx
	mov	bx,word ptr es:_List
	dec	bx
	cwd	
	idiv	bx
	pop	bx
	add	bx,ax
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+20]
	pop	ax
	add	bx,ax
	mov	byte ptr es:[bx],4
   ;	
   ;	System.screen[Window.row+1][Window.col+Window.width].ch=30; //up scroll
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	shl	dx,1
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	shl	ax,1
	shl	ax,1
	mov	bx,seg _System
	mov	es,bx
	mov	bx,ax
	les	bx,dword ptr es:_System[bx+16]
	add	bx,dx
	mov	byte ptr es:[bx],30
   ;	
   ;	System.screen[Window.row+Window.height-1][Window.col+Window.width].ch=31;//down scroll
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	bx
	add	bx,ax
	shl	bx,1
	shl	bx,1
	mov	ax,seg _System
	mov	es,ax
	les	bx,dword ptr es:_System[bx+8]
	mov	ax,seg _Window
	push	es
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	bx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	shl	dx,1
	pop	bx
	add	bx,dx
	pop	es
	mov	byte ptr es:[bx],31
   ;	
   ;	
   ;	//write the string in range into the window;
   ;	for(i=Window.uprange;i<=Window.dnrange;i++)
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	ax,word ptr es:_Window+1026
	mov	dx,seg i
	mov	es,dx
	mov	word ptr es:i,ax
	jmp	short @9@394
@9@338:
   ;	
   ;		writetextxy(Window.row+1+i-Window.uprange,Window.col+1,
   ;	
   ;	
   ;		(List.list+i*32),Window.width-1);
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+5
	cbw	
	dec	ax
	push	ax
	mov	ax,seg i
	mov	es,ax
	mov	ax,word ptr es:i
	mov	cl,5
	shl	ax,cl
	mov	dx,seg _List
	mov	es,dx
	mov	dx,word ptr es:_List+8
	add	dx,ax
	push	word ptr es:_List+10
	push	dx
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg i
	mov	es,dx
	add	al,byte ptr es:i
	inc	al
	mov	dx,seg _Window
	mov	es,dx
	sub	al,byte ptr es:_Window+1026
	push	ax
	push	cs
	call	near ptr writetextxy
	add	sp,10
	mov	ax,seg i
	mov	es,ax
	inc	word ptr es:i
@9@394:
	mov	ax,seg i
	mov	es,ax
	mov	ax,word ptr es:i
	mov	dx,seg _Window
	mov	es,dx
	cmp	ax,word ptr es:_Window+1028
	jg	@@6
	jmp	@9@338
@@6:
   ;	
   ;	
   ;	//mark the selected text;
   ;	//if(List.cursel!=NULL)	// is there a valid suggestion
   ;	fillattr(Window.row+1+List.icursel-Window.uprange,Window.col+1,
   ;	
   ;	
   ;		Window.row+1+List.icursel-Window.uprange,Window.col+Window.width-1,0x7f,0x7f);
   ;	
	mov	al,127
	push	ax
	mov	al,127
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	mov	dx,seg _Window
	mov	es,dx
	add	al,byte ptr es:_Window+5
	dec	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _List
	mov	es,dx
	add	al,byte ptr es:_List+2
	inc	al
	mov	dx,seg _Window
	mov	es,dx
	sub	al,byte ptr es:_Window+1026
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	inc	al
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	mov	dx,seg _List
	mov	es,dx
	add	al,byte ptr es:_List+2
	inc	al
	mov	dx,seg _Window
	mov	es,dx
	sub	al,byte ptr es:_Window+1026
	push	ax
	push	cs
	call	near ptr fillattr
	add	sp,12
   ;	
   ;	
   ;	preicursel=List.icursel;// save previous cursel
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg preicursel
	mov	es,dx
	mov	word ptr es:preicursel,ax
@9@450:
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_drawwindow	endp
   ;	
   ;	void far showwindow()
   ;	
	assume	cs:_TEXT
_showwindow	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
   ;	
   ;	{unsigned char r,c;
   ;	 //return;
   ;	 if(Window.enabled==0) return;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	byte ptr es:_Window,0
	jne	short @10@86
	jmp	@10@618
@10@86:
   ;	
   ;	 Window.active=1;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	byte ptr es:_Window+1,1
   ;	
   ;	 // setting proper ranges to be shown
   ;	 Window.uprange=List.icursel; // the window top
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1026,ax
   ;	
   ;	 Window.dnrange=List.icursel+Window.height-2;//Window bottom range
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+4
	cbw	
	mov	dx,seg _List
	mov	es,dx
	mov	dx,word ptr es:_List+2
	add	dx,ax
	add	dx,65534
	mov	ax,seg _Window
	mov	es,ax
	mov	word ptr es:_Window+1028,dx
   ;	
   ;	 if(Window.dnrange>=List.count) // is dnragne beyond List?
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	ax,word ptr es:_Window+1028
	mov	dx,seg _List
	mov	es,dx
	cmp	ax,word ptr es:_List
	jl	short @10@142
   ;	
   ;		{ Window.uprange-=(Window.dnrange-List.count+1); //setup them properly
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	ax,word ptr es:_Window+1028
	mov	dx,seg _List
	mov	es,dx
	sub	ax,word ptr es:_List
	inc	ax
	mov	dx,seg _Window
	mov	es,dx
	sub	word ptr es:_Window+1026,ax
   ;	
   ;		  Window.dnrange=List.count-1;
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List
	dec	ax
	mov	dx,seg _Window
	mov	es,dx
	mov	word ptr es:_Window+1028,ax
@10@142:
   ;	
   ;		}
   ;	 if(Window.trackcursor) // is cursor tracking enabled
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	byte ptr es:_Window+7,0
	jne	@@7
	jmp	@10@534
@@7:
   ;	
   ;	 {	asm{push dx;mov ah,0x3;
   ;	
	push	 dx
	mov	 ah,03H
   ;	
   ;		    mov bh,0;  int 0x10;
   ;	
	mov	 bh,0
  	int	 010H
   ;	
   ;		    mov byte ptr r,dh;
   ;	
	mov	 byte ptr [bp-1],dh
   ;	
   ;		    mov byte ptr c,dl;
   ;	
	mov	 byte ptr [bp-2],dl
   ;	
   ;		    pop dx;
   ;	
	pop	 dx
   ;	
   ;		   }//request the cursur position from ROM BIOS
   ;		 if(r>25-Window.height-2) r-=(Window.height+1); else r++;
   ;	
	mov	al,byte ptr [bp-1]
	mov	ah,0
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	mov	dx,25
	sub	dx,ax
	add	dx,65534
	pop	ax
	cmp	ax,dx
	jle	short @10@422
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+4
	inc	al
	mov	dl,byte ptr [bp-1]
	sub	dl,al
	mov	byte ptr [bp-1],dl
	jmp	short @10@450
@10@422:
	inc	byte ptr [bp-1]
@10@450:
   ;	
   ;		 if(c>80-Window.width-2) c-=(Window.width+2);
   ;	
	mov	al,byte ptr [bp-2]
	mov	ah,0
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	mov	dx,80
	sub	dx,ax
	add	dx,65534
	pop	ax
	cmp	ax,dx
	jle	short @10@506
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+5
	add	al,2
	mov	dl,byte ptr [bp-2]
	sub	dl,al
	mov	byte ptr [bp-2],dl
@10@506:
   ;	
   ;		 Window.row=r;
   ;	
	mov	ax,seg _Window
	mov	dl,byte ptr [bp-1]
	mov	es,ax
	mov	byte ptr es:_Window+2,dl
   ;	
   ;		 Window.col=c;
   ;	
	mov	ax,seg _Window
	mov	dl,byte ptr [bp-2]
	mov	es,ax
	mov	byte ptr es:_Window+3,dl
@10@534:
   ;	
   ;	 }
   ;	
   ;	 savevedio(r,c,r+Window.height,c+Window.width,Window.saved_data);
   ;	
	mov	ax,seg _Window
	push	ax
	mov	ax,offset _Window+14
	push	ax
	mov	al,byte ptr [bp-2]
	mov	ah,0
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	push	dx
	mov	al,byte ptr [bp-1]
	mov	ah,0
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	dx
	add	dx,ax
	push	dx
	mov	al,byte ptr [bp-2]
	mov	ah,0
	push	ax
	mov	al,byte ptr [bp-1]
	mov	ah,0
	push	ax
	push	cs
	call	near ptr savevedio
	add	sp,12
   ;	
   ;	 if(Window.shadow) saveshadowattr(); // save attributes under the shadow
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	byte ptr es:_Window+6,0
	je	short @10@590
	push	cs
	call	near ptr saveshadowattr
@10@590:
   ;	
   ;	 //set up the mouse
   ;	   setupmouse();
   ;	
	call	far ptr _setupmouse
   ;	
   ;	 drawwindow();
   ;	
	push	cs
	call	near ptr _drawwindow
@10@618:
   ;	
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
_showwindow	endp
   ;	
   ;	void far hidewindow()
   ;	
	assume	cs:_TEXT
_hidewindow	proc	far
	push	bp
	mov	bp,sp
   ;	
   ;	{if(!Window.active) return;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+1
	cbw	
	or	ax,ax
	jne	short @11@86
	jmp	@11@142
@11@86:
   ;	
   ;	//return;
   ;	Window.active=0;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	byte ptr es:_Window+1,0
   ;	
   ;	//restore privious mouse handler
   ;	restoremouse();
   ;	
	call	far ptr _restoremouse
   ;	
   ;	//
   ;	restorevedio(Window.row,Window.col,Window.row+Window.height,
   ;	
   ;	
   ;	  Window.col+Window.width,Window.saved_data);
   ;	
	mov	ax,seg _Window
	push	ax
	mov	ax,offset _Window+14
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+5
	cbw	
	pop	dx
	add	dx,ax
	push	dx
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	mov	dx,seg _Window
	mov	es,dx
	push	ax
	mov	al,byte ptr es:_Window+4
	cbw	
	pop	dx
	add	dx,ax
	push	dx
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+3
	cbw	
	push	ax
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+2
	cbw	
	push	ax
	push	cs
	call	near ptr restorevedio
	add	sp,12
   ;	
   ;	if(Window.shadow) restoreshadowattr();
   ;	
	mov	ax,seg _Window
	mov	es,ax
	cmp	byte ptr es:_Window+6,0
	je	short @11@142
	push	cs
	call	near ptr restoreshadowattr
@11@142:
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_hidewindow	endp
   ;	
   ;	void far scrolldown()
   ;	
	assume	cs:_TEXT
_scrolldown	proc	far
	push	bp
	mov	bp,sp
   ;	
   ;	{
   ;	 if(!Window.active) return; // if window is not visible then return
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+1
	cbw	
	or	ax,ax
	jne	short @12@86
	jmp	short @12@170
@12@86:
   ;	
   ;	  List.icursel++;
   ;	
	mov	ax,seg _List
	mov	es,ax
	inc	word ptr es:_List+2
   ;	
   ;	 if(List.icursel>=List.count) {List.icursel=List.count-1; return;}
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	dx,seg _List
	mov	es,dx
	cmp	ax,word ptr es:_List
	jl	short @12@142
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List
	dec	ax
	mov	dx,seg _List
	mov	es,dx
	mov	word ptr es:_List+2,ax
	jmp	short @12@170
@12@142:
   ;	
   ;	/* Window.uprange++; //increment the pivot element
   ;	  //if(List.icursel>Window.dnrange)
   ;	  //Window.dnrange=List.icursel,Window.uprange=Window.dnrange-Window.height+2;
   ;	  if(Window.uprange>=Window.height-2) Window.uprange--;*/
   ;	 List.cursel=List.list+List.icursel*32;/**/
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	cl,5
	shl	ax,cl
	mov	dx,seg _List
	mov	es,dx
	mov	dx,word ptr es:_List+10
	mov	bx,word ptr es:_List+8
	add	bx,ax
	mov	ax,seg _List
	mov	es,ax
	mov	word ptr es:_List+6,dx
	mov	word ptr es:_List+4,bx
   ;	
   ;	drawwindow();
   ;	
	push	cs
	call	near ptr _drawwindow
@12@170:
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_scrolldown	endp
   ;	
   ;	void far scrollup()
   ;	
	assume	cs:_TEXT
_scrollup	proc	far
	push	bp
	mov	bp,sp
   ;	
   ;	{ if(!Window.active) return;
   ;	
	mov	ax,seg _Window
	mov	es,ax
	mov	al,byte ptr es:_Window+1
	cbw	
	or	ax,ax
	jne	short @13@86
	jmp	short @13@170
@13@86:
   ;	
   ;	  List.icursel--;
   ;	
	mov	ax,seg _List
	mov	es,ax
	dec	word ptr es:_List+2
   ;	
   ;	  if(List.icursel<0) {List.icursel=0;return;}
   ;	
	mov	ax,seg _List
	mov	es,ax
	cmp	word ptr es:_List+2,0
	jge	short @13@142
	mov	ax,seg _List
	mov	es,ax
	mov	word ptr es:_List+2,0
	jmp	short @13@170
@13@142:
   ;	
   ;	  /*
   ;	  //List.icursel--;
   ;	  //else List.icursel=Window.uprange;
   ;	  if(List.icursel<0) List.icursel=0;
   ;	  Window.uprange--; // decrement the pivot
   ;	  if(Window.uprange<0) // has it gone less than zero
   ;		Window.uprange=0;*/
   ;	 List.cursel=List.list+List.icursel*32;
   ;	
	mov	ax,seg _List
	mov	es,ax
	mov	ax,word ptr es:_List+2
	mov	cl,5
	shl	ax,cl
	mov	dx,seg _List
	mov	es,dx
	mov	dx,word ptr es:_List+10
	mov	bx,word ptr es:_List+8
	add	bx,ax
	mov	ax,seg _List
	mov	es,ax
	mov	word ptr es:_List+6,dx
	mov	word ptr es:_List+4,bx
   ;	
   ;	 drawwindow();
   ;	
	push	cs
	call	near ptr _drawwindow
@13@170:
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_scrollup	endp
_TEXT	ends
WINDOW5_DATA	segment para public 'FAR_DATA'
i	label	word
	db	2 dup (0)
preicursel	label	word
	db	2 dup (0)
	?debug	C E9
WINDOW5_DATA	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
_TEXT	segment byte public 'CODE'
_TEXT	ends
	public	_scrollup
	public	_scrolldown
	public	_hidewindow
	public	_showwindow
	public	_drawwindow
_restorevedio	equ	restorevedio
_savevedio	equ	savevedio
_restoreshadowattr	equ	restoreshadowattr
_saveshadowattr	equ	saveshadowattr
_fillchar	equ	fillchar
_fillattr	equ	fillattr
_writetextxy	equ	writetextxy
_box	equ	box
_caption	equ	caption
_i	equ	i
_preicursel	equ	preicursel
	extrn	_restoremouse:far
	extrn	_setupmouse:far
	extrn	_Window:word
	extrn	_List:word
	extrn	_System:word
_s@	equ	s@
	end
