;=========================================================;
; Fat                                          01/04/2011 ;
;---------------------------------------------------------;
;                                                         ;
; DexOS V0.05                                             ;
; (c) Craig Bamford, All rights reserved.                 ;
;=========================================================;

MaxFileCount dd 0					  ;
FddFilesForMenu dd 0					  ;
;=======================================================  ;
; DirFileList.                                            ;
;=======================================================  ;
DirFileList:						  ;
	pushad						  ;
	push	es					  ;
	push	ds					  ;
	mov	dword[FddFilesForMenu],edi		  ;
	mov	word[FileExt],ax			  ;
	mov	dword[MaxFileCount],ecx 		  ;
	mov	[RdirFileCount],0			  ;
	mov	[FddFileListCount],0			  ;
	mov	[Fdd_FileListCount],0			  ;
	mov	[FileNumberCount],0			  ;
	mov	ax,sys_data				  ;
	mov	es,ax					  ;
	mov	ds,ax					  ;
	mov	eax,RootDirBuffer			  ;
	mov	[RootDirBufferVar],eax			  ;
FileNamePrintLoopGui:					  ;
	mov	esi,[RootDirBufferVar]			  ;
	add	esi,[RdirFileCount]			  ;
	add	[RdirFileCount],32			  ;
	cmp	byte [ds:esi],0xe5			  ;
	je	FileNamePrintLoopGui			  ;
	cmp	byte [ds:esi],0x00			  ;
	je	DirSuccsessGui				  ;
	mov	edi,FileEntry				  ;
	mov	ecx,32					  ;
	rep	movsb					  ;
	cmp	word[FileCluster],0			  ;
	je	FileNamePrintLoopGui			  ;
	cmp	dword[FileSize],0			  ;
	je	FileNamePrintLoopGui			  ;
	mov	cx,word[FileExt]			  ;
	cmp	cx,0					  ;
	je	@f					  ;
	cmp	word[FileExten],cx			  ; Example 'GE'
	jne	FileNamePrintLoopGui			  ;
@@:							  ;
;=======================================================  ;
; Print file/dir name.                                    ;
;=======================================================  ;
	inc	[FileNumberCount]			  ;
	push	edi					  ;
	mov	edi,TempString				  ;
	mov	al,' '					  ;
	mov	ecx,15					  ;
	rep	stosb					  ;
	mov	esi,FileEntry				  ;
	mov	ecx,8					  ;
	mov	edi,TempString				  ;
	mov	al,7h					  ;
	stosb						  ;
	mov	al,' '					  ;
	stosb						  ;
ConvetNameLoop: 					  ;
	lodsb						  ;
	cmp	al,' '					  ;
	je	EndOfName				  ;
	stosb						  ;
	loop	ConvetNameLoop				  ;
EndOfName:						  ;
	mov	al,'.'					  ;
	stosb						  ;
	mov	esi,FileExten				  ;
	mov	ecx,3					  ;
	rep	movsb					  ;
	mov	al,0					  ;
	stosb						  ;
	mov	edi,TempString				  ;
	call	LowerCase				  ;
	mov	ecx,15					  ;
	mov	esi,TempString				  ;
	mov	edi,dword[FddFilesForMenu]		  ;
	add	edi,[FddFileListCount]			  ;
	rep	movsb					  ;
	add	[FddFileListCount],15			  ;
	pop	edi					  ;
	mov	ebx,dword[MaxFileCount] 		  ;
	cmp	[FileNumberCount],ebx			  ;
	jae	DirSuccsessGui				  ;
	jmp	FileNamePrintLoopGui			  ;
;=======================================================  ;
; Exit OK                                                 ;
;=======================================================  ;
DirSuccsessGui: 					  ;
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	mov	esi,dword[FddFilesForMenu]		  ;
	mov	edi,dword[FddFilesForMenu]		  ;
	mov	ecx,dword[FileNumberCount]		  ;
	clc						  ;
	ret						  ;
;=======================================================  ;
; Exit Error                                              ;
;=======================================================  ;
DirErrorGui:						  ;
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	;mov    ah,byte[ErrorCode]                        ;
	stc						  ;
	ret						  ;

UpDateRFNowYN	 db 0					  ;
StartclusterDel  dw 0					  ;
NameOfFileToMake dd 0					  ;
;=======================================================  ;
; Delete Command                                          ;
;=======================================================  ;
DeleteCommand:						  ;
	pushad						  ;  
	push	es					  ;
	push	ds					  ;
	mov	byte[UpDateRFNowYN],0			  ;
	cmp	al,1					  ;
	jne	@f					  ;
	mov	byte[UpDateRFNowYN],1			  ;
@@:							  ;
	mov	[ErrorCode],0				  ;
	mov	dword[NameOfFileToMake],esi		  ;
	mov	[FileLoadCountUP],dword 0		  ;
	mov	ax,18h					  ;
	mov	ds,ax					  ;
	mov	es,ax					  ;
	call	DirFillRootUSB				  ;
	jc	DelCommandError 			  ;
	mov	eax,RootDirBuffer			  ;
	mov	[RootDirBufferVar],eax			  ;
	mov	[ErrorCode],0x06			  ;
	mov	esi,dword[NameOfFileToMake]		  ;
;=======================================================  ;
; Find the file.                                          ;
;=======================================================  ;
	call	FindFileNameFat16			  ;
	jc	DelCommandError 			  ;
	mov	[ErrorCode],0x07			  ;
;=======================================================  ;
; Check its not read only etc.                            ;
;=======================================================  ;
	mov	esi,dword[RootFileAddressFat16] 	  ;
	mov	al,byte[ds:esi+0xb]			  ;
	cmp	al,0					  ;
	je	@f					  ;
	cmp	al,0x20 				  ;
	je	@f					  ;
	jmp	DelCommandError 			  ;
@@:							  ;
;=======================================================  ;
; Get the start cluster.                                  ;
;=======================================================  ;
	mov	esi,dword[RootFileAddressFat16] 	  ;
	mov	ax,word[ds:esi+1Ah]			  ;
	mov	word [StartclusterDel],ax		  ;
;=======================================================  ;
; Release Cluster Chain                                   ;
;=======================================================  ;
	cmp	byte[FileSysTypeNew],12 		  ;
	jne	NotFat12_ReleaseClusterChain		  ;
	call	ReleaseClusterChain12			  ;
	jmp	WasFat12_ReleaseClusterChain		  ;
NotFat12_ReleaseClusterChain:				  ;
	cmp	byte[FileSysTypeNew],16 		  ;
	jne	DelCommandError 			  ;
	call	ReleaseClusterChain			  ;
WasFat12_ReleaseClusterChain:				  ;
;=======================================================  ;
; Mark the file as deleted                                ;
;=======================================================  ;
	mov	esi,dword[RootFileAddressFat16] 	  ;
	mov	byte[ds:esi],0xe5			  ;
;=======================================================  ;
; Test if we need to write root/fat to disk.              ;
;=======================================================  ;
	cmp	byte[UpDateRFNowYN],1			  ;
	je	DelCommandSucsess			  ;
	cmp	byte[FileSysTypeNew],12 		  ;
	jne	NotFat12_DirFatRootUpdate		  ;
	call	DirFatRootUpdate12			  ;
	jc	DelCommandError 			  ;
	jmp	DelCommandSucsess			  ;
NotFat12_DirFatRootUpdate:				  ;
	cmp	byte[FileSysTypeNew],16 		  ;
	jne	DelCommandError 			  ;
	call	DirFatRootUpdateFat16			  ;
	jc	DelCommandError 			  ;
;=======================================================  ;
; Exit OK.                                                ;
;=======================================================  ;
DelCommandSucsess:					  ;
	mov	dword[FatUpDateY_N],0			  ; This lets the cli dir command know to update the fat buffer.
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	clc						  ;
	ret						  ;
;=======================================================  ;
; Exit Error.                                             ;
;=======================================================  ; 
DelCommandError:					  ;
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	mov	ah,byte[ErrorCode]			  ;
	stc						  ;
	ret						  ;

NewFileName dd 0					  ;
;=======================================================  ;
; ReName File.                                            ;
;=======================================================  ; 
ReNameFile:						  ;
	pushad						  ;  
	push	es					  ;
	push	ds					  ;
	mov	[ErrorCode],0				  ;
	mov	dword[NameOfFileToMake],esi		  ; Old file Name
	mov	dword[NewFileName],edi			  ; New file name
	mov	ecx,12					  ;
	mov	esi,edi 				  ;
;=======================================================  ;
; Check if new file name is a valid name.                 ;
;=======================================================  ;
  ReNameFileloop:					  ;
	lodsb						  ;
	cmp	al,0					  ;
	je	ExitReNameFileloop			  ;
	cmp	al,32					  ; 
	jb	ReNameFileError 			  ;
	cmp	al,128					  ; 
	ja	ReNameFileError 			  ;
	loop	ReNameFileloop				  ;
 ExitReNameFileloop:					  ;
	cmp	ecx,12					  ;
	je	ReNameFileError 			  ;
	mov	[FileLoadCountUP],dword 0		  ;
	mov	ax,18h					  ;
	mov	ds,ax					  ;
	mov	es,ax					  ;
	call	DirFillRootUSB				  ;
	jc	ReNameFileError 			  ;
	mov	eax,RootDirBuffer			  ;
	mov	[RootDirBufferVar],eax			  ;
	mov	[ErrorCode],0x06			  ;
	mov	esi,dword[NewFileName]			  ; new name
;=======================================================  ;
; Check if new file name exists.                          ;
;=======================================================  ;
	call	FindFileNameFat16			  ;
	jnc	ReNameFileError 			  ;
;=======================================================  ;
; Save converted new name.                                ;
;=======================================================  ;
	pushad						  ;
	mov	esi,NameOfFileToLoadBufferFat16 	  ; 
	mov	edi,NameOfFileToLoadBufferFat16a	  ;
	mov	ecx,16					  ;
	rep	movsb					  ;
	popad						  ;
	mov	esi,dword[NameOfFileToMake]		  ; old name
;=======================================================  ;
; Check if old file name exists.                          ;
;=======================================================  ;
	call	FindFileNameFat16			  ;
	jc	ReNameFileError 			  ;
	mov	[ErrorCode],0x07			  ;
;=======================================================  ;
; Check its not read only etc.                            ;
;=======================================================  ;
	mov	esi,dword[RootFileAddressFat16] 	  ;
	mov	al,byte[ds:esi+0xb]			  ;
	cmp	al,0					  ;
	je	@f					  ;
	cmp	al,0x20 				  ;
	je	@f					  ;
	jmp	ReNameFileError 			  ;
@@:							  ;
;=======================================================  ;
; Set root dir entry.                                     ;
;=======================================================  ;
	mov	edi,dword[RootFileAddressFat16] 	  ; We need to set a root entry out.
	mov	esi,NameOfFileToLoadBufferFat16a	  ; First name of file.
	mov	cx,11					  ; Number of letters 8+3
	rep	movsb					  ; move from a to b.
;=======================================================  ;
; Up date root dir fat12.                                 ;
;=======================================================  ;
	cmp	byte[FileSysTypeNew],12 		  ;
	jne	NotFat12_DirFatRootUpdateREN		  ;
	call	DirFatRootUpdate12			  ;
	jc	ReNameFileError 			  ;
	jmp	ReNameFileSucsess			  ;
;=======================================================  ;
; Up date root dir fat16.                                 ;
;=======================================================  ;
NotFat12_DirFatRootUpdateREN:				  ;
	cmp	byte[FileSysTypeNew],16 		  ;
	jne	ReNameFileError 			  ;
	call	DirFatRootUpdateFat16			  ;
	jc	ReNameFileError 			  ;
;=======================================================  ;
; Exit OK.                                                ;
;=======================================================  ;
ReNameFileSucsess:					  ;
	mov	dword[FatUpDateY_N],0			  ; This lets the cli dir command know to update the fat buffer.
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	clc						  ;
	ret						  ;
;=======================================================  ;
; Exit Error.                                             ;
;=======================================================  ; 
ReNameFileError:					  ;
	pop	ds					  ;
	pop	es					  ;
	popad						  ;
	mov	ah,byte[ErrorCode]			  ;
	stc						  ;
	ret						  ;

;=======================================================  ;
; Data                                                    ;
;=======================================================  ;
TempString db '                ',0			  ;
							  ;


