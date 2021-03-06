;=========================================================;
; Mouse                                        01/04/2011 ;
;---------------------------------------------------------;
;                                                         ;
; (c) Craig Bamford, All rights reserved.                 ;
;=========================================================;

;=======================================================  ;
;  PutMousePointer                                        ;
;=======================================================  ; 
PutMousePointer:                                          ;
	pushad		                                  ;			 
	push    es                                        ;
	push    ds                                        ;
	mov     ax,8h	                                  ;		     
	mov     es,ax                                     ;
	mov     edi,0xb8000                               ;
	call    get_mouse_pointer1                        ;
	mov     ax,[SaveChar]                             ;
	mov     [es:edi],ax                               ;
	mov     edi,0xb8000                               ;
	call    get_mouse_pointer2                        ;
	mov     ax,word[es:edi]                           ;
	mov     [SaveChar],ax                             ;
	not     ah                                        ;
	xor     ah,0x80                                   ;
	mov     [es:edi],ax	                          ;	     
	mov     ax,[current_x]                            ;
	mov     [current_x1],ax                           ;
	mov     ax,[current_y]                            ;
	mov     [current_y1],ax                           ;
	pop     ds                                        ;
	pop     es                                        ;
	popad                                             ;
	ret                                               ;

;=======================================================  ;
;  MouseMovmentClick                                      ;
;=======================================================  ; 
MouseMovmentClick:                                        ;
	mov     bl,0xad			                  ; disable keyboard
	call    keyboard_cmd                              ;
	xor     edi,edi				          ; read ps/2 data packet
	mov     ecx,PS2_PACKETSIZE                        ;
  PS2MouseISR_ReadPacket:                                 ;
	push    ecx                                       ;
	call    keyboard_read	                          ;
	pop     ecx	                                  ;	
	or      ah,ah                                     ;
	jnz     PS2MouseISR_ExitReadPacket                ;
	mov     byte[recvbuffer+edi],al                   ;
	inc     edi                                       ;
	loop    PS2MouseISR_ReadPacket                    ;
  PS2MouseISR_ExitReadPacket:                             ;
	mov     ax,di                                     ;
	mov     [datasize],al                             ;
	mov     al,[recvbuffer]	                          ;
	and     al,7h                                     ;
	mov     ah,al                                     ;
	and     ah,1                                      ;
	shl     ah,2                                      ;
	mov     bl,al                                     ;
	and     bl,6                                      ;
	shr     bl,1                                      ;
	or      ah,bl                                     ;
	mov     al,[buttons]                              ;
	mov     [buttons],ah                              ;
	xor     ah,al                                     ;
	shl     ah,1                                      ;
	or      [eventmsk],ah	                          ;
	mov     al,[recvbuffer+1] 	               	  ; byte 1 - x movement
	mov     ah,[recvbuffer]			          ; msb of x-movement in byte 0
	and     ah,10h                                    ;
	shr     ah,4                                      ;
	neg     ah                                        ;
	add     [current_x],ax	                          ;
	mov     [delta_x],ax                              ;
	or      ax,ax                                     ;
	setnz   bl                                        ;
	or      [eventmsk],bl		           	  ; set mouse moved bit if mouse was moved :p
	mov     al,[recvbuffer+2] 		          ; byte 2 - y movement
	mov     ah,[recvbuffer]			          ; msb of y-movement in byte 0
	and     ah,0x20                                   ;
	shr     ah,5                                      ;
	neg     ah                                        ;
	neg     ax                                        ;
	add     [current_y], ax	                          ;
	mov     [delta_y],ax                              ;
	or      ax,ax                                     ;
	setnz   bl                                        ;
	or      [eventmsk],bl                             ;
;=======================================================  ;
;  check boundaries                                       ;
;=======================================================  ; 
	mov     dx,[current_x]                            ;
	cmp     dx,[min_x]			          ; Check min and max ranges
	jnl     PS2MouseISR_CheckMaxX                     ;
	mov     dx,[min_x]                                ;
	jmp     PS2MouseISR_StoreNewX                     ;
  PS2MouseISR_CheckMaxX:                                  ;
	cmp     dx,[max_x]                                ;
	jl      PS2MouseISR_StoreNewX                     ;
	mov     dx,[max_x]                                ;
  PS2MouseISR_StoreNewX:                                  ;
	mov     [current_x],dx                            ;
	mov     dx,[current_y]                            ;
	cmp     dx,[min_y]			          ; Check min and max ranges
	jnl     PS2MouseISR_CheckMaxY                     ;
	mov     dx,[min_y]                                ;
	jmp     PS2MouseISR_StoreNewY                     ;
  PS2MouseISR_CheckMaxY:                                  ;
	cmp     dx,[max_y]                                ;
	jl      PS2MouseISR_StoreNewY                     ;
	mov     dx,[max_y]                                ;
  PS2MouseISR_StoreNewY:                                  ;
	mov     [current_y],dx                            ;
	cmp     [MouseShow],1                             ;
	jne     @f                                        ;
	call	PutMousePointer                           ;
@@:                                                       ;
	mov	bl,0aeh 			          ; enable keyboard
	call	keyboard_cmd                              ;
	ret                                               ;

;=======================================================  ;
;  Gets mouse pointer                                     ;
;=======================================================  ; 
get_mouse_pointer2:                                       ;
	push    eax		                          ;			   
	push    ebx                                       ;
	xor     ebx,ebx                                   ;
	mov     bx,[current_x ]                           ;
	shr     ebx,2                                     ;
	and     ebx,0feh                                  ;
	add     edi, ebx                                  ;
	xor     ebx,ebx                                   ;
	mov     bx,[current_y]                            ;
	shr     ebx,3                                     ;
	mov     eax,0xa0                                  ;
	mul     bx                                        ;
	add     edi,eax                                   ;
	pop     ebx                                       ;
	pop     eax                                       ;
	ret                                               ;

;=======================================================  ;
;  get_mouse_pointer1                                     ;
;=======================================================  ; 
get_mouse_pointer1:		                          ;			
	push    eax		                          ;			   
	push    ebx                                       ;
	xor     ebx,ebx                                   ;
	mov     bx,[current_x1]                           ;
	shr     ebx,2                                     ;
	and     ebx,0feh                                  ;
	add     edi, ebx                                  ;
	xor     ebx,ebx                                   ;
	mov     bx,[current_y1]                           ;
	shr     ebx,3                                     ;
	mov     eax,0xa0                                  ;
	mul     bx                                        ;
	add     edi,eax                                   ;
	pop     ebx                                       ;
	pop     eax                                       ;
	ret                                               ;

;=======================================================  ;
;  ResetMouse.                                            ;
;=======================================================  ; 
ResetMouse:                                               ;
	cmp     [PS2Mouse],1                              ;
	jne     NoPs2MouseExit                            ;
	cli                                               ;
	pushad                                            ;
	mov     bl,0xa8				          ; enable mouse
	call    keyboard_cmd                              ;
	mov     [SaveChar],0                              ;
	mov     [min_x],0                                 ;
	mov     [max_x],639			          ; = 79
	mov     [min_y],0                                 ;
	mov     [max_y],199 ;399			  ; = 49
	mov     [buttons],0                               ;
	mov     [current_x],300                           ;
	mov     [current_y],100                           ;                     
	mov     [current_x1],300                          ;
	mov     [current_y1],100                          ;
	mov     [MouseShow],0                             ;
	popad                                             ;
	mov     ax,0xffff                                 ;
	sti                                               ;
	ret                                               ;
NoPs2MouseExit:                                           ;
	xor    ax,ax                                      ;
	ret                                               ;

;=======================================================  ;
;  ShowMouse                                              ;
;=======================================================  ; 
ShowMouse:                                                ;
	cli                                               ;
	mov     [MouseShow],1                             ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  HideMouse                                              ;
;=======================================================  ;  
HideMouse:                                                ;
	cli                                               ;
	mov     [MouseShow],0                             ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  GetMousePos.                                           ;
;=======================================================  ; 
GetMousePos:                                              ;
	cli                                               ;
	mov     bl,[buttons]                              ;
	mov     cx,[current_x]                            ;
	mov     dx,[current_y]                            ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  SetMouseMaxMinXY                                       ;
;=======================================================  ; 
SetMouseMaxMinXY:                                         ;
	cli                                               ;
	mov     [max_x],ax                                ;
	shr     eax,16                                    ;
	mov     [min_x],ax                                ;
	mov     [max_y],dx                                ;
	shr     edx,16                                    ;
	mov     [min_y],dx                                ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  SetMouseXY                                             ;
;=======================================================  ; 
SetMouseXY:                                               ;
	cli                                               ;
	mov     [current_x],ax                            ;
	mov     [current_y],dx                            ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  SetMouseXY                                             ;
;=======================================================  ; 
SetMouseOff:                                              ;
	cli                                               ;
	pushad                                            ;
	mov     bl,0a7h 			          ; disable mouse
	call	keyboard_cmd                              ;
	popad                                             ;
	sti                                               ;
	ret                                               ;

;=======================================================  ;
;  keyboard_cmd.                                          ;
;=======================================================  ; 
keyboard_cmd:                                             ;
	xor     eax,eax                                   ;
	mov     ecx,0xffff                                ;
  cmd_wait:                                               ;
	in      al,64h                                    ;
	test    al,2                                      ;
	jz      cmd_send                                  ;
	loop    cmd_wait                                  ;
                                                          ;
	jmp     cmd_error                                 ;
  cmd_send:                                               ;
	mov     al,bl                                     ;
	out     64h,al                                    ;
	mov     ecx,0xffff                                ;
  cmd_accept:                                             ;
	in      al,0x64                                   ;
	test    al,2                                      ;
	jz      cmd_ok                                    ;
	loop    cmd_accept                                ;
  cmd_error:                                              ;
	mov     ah,1                                      ;
	jmp     cmd_exit                                  ;
  cmd_ok:                                                 ;
	xor     ah,ah                                     ;
cmd_exit:                                                 ;
	ret                                               ;

;=======================================================  ;
;  keyboardRead.                                          ;
;=======================================================  ; 
keyboard_read:                                            ;
	push    ecx                                       ;
	push    edx                                       ;
	mov     ecx,0xffff                                ;
  key_read_loop:                                          ;
	in      al,0x64                                   ;
	test    al,1                                      ;
	jnz     key_read_ready                            ;
	loop    key_read_loop                             ;
	mov     ah,1                                      ;
	jmp     key_read_exit                             ;
  key_read_ready:                                         ;
	push    ecx                                       ;
	mov     ecx,32                                    ;
  key_read_delay:                                         ;
	loop    key_read_delay                            ;
	pop     ecx                                       ;
	in      al,0x60                                   ;
	xor     ah,ah                                     ;
key_read_exit:                                            ;
	pop     edx                                       ;
	pop     ecx                                       ;
	ret                                               ;

;=======================================================  ;
;  Data.                                                  ;
;=======================================================  ; 
PS2_PACKETSIZE	=	3                                 ;
MouseShow	db	0                                 ;
SaveChar	dw	0                                 ;
min_x		dw	0                                 ;
max_x		dw	639			          ;
min_y		dw	0                                 ;
max_y		dw	199                               ;
eventmsk	db	0                                 ;
recvbuffer	db	0,0,0,0,0,0,0,0                   ;
datasize	db	0                                 ;
buttons 	db	0                                 ;
current_x	dw	300			          ;
current_y	dw	100                               ;
current_x1	dw	300			          ;
current_y1	dw	100                               ;
delta_x 	dw	0                                 ;
delta_y 	dw	0                                 ;
