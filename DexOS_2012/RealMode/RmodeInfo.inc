;=========================================================;
; RmodeInfo                                      01/05/11 ;
;---------------------------------------------------------;
; Vars with Rm info.                                      ;
;                                                         ;
; (c) Craig Bamford, All rights reserved.                 ;
;=========================================================;

;=======================================================  ;
; REALMODE INFORMATION BLOCK                              ;
;=======================================================  ;  
RealModeInfo:                                             ;
DriveNumber	   db 0                                   ;
PciBusPresent	   db 0                                   ;
BootNumber	   db 0                                   ;
BootProTest	   db 0                                   ;
DosLoaded	   db 0                                   ;
ConvMemorySize	   dd 0                                   ;
ExtMemorySize	   dd 0                                   ;
TotalMemoryMB	   dd 0                                   ;