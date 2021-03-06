;====================================================;
; Data.                                              ;
;====================================================;
;WinHead1     db '   File     Edit     Search     Help  '
WinHead1     db ' Network  Help      '
align 4
Ytable		    dd 0, 160, 320, 480, 640, 800, 960,1120,1280,1440,1600,1760,1920
		    dd 2080,2240,2400,2560,2720,2880,3040,3200,3360,3520,3680,3840
		    dd 4000,4160, 4320, 4480, 4640, 4800, 4960,5120,5280,5440,5600,5760,5920
		    dd 6080,6240,6400,6560,6720,6880,7040,7200,7360,7520,7680,7840

WinFile      db 17,8,color2a
	     db '旼컴컴컴컴컴컴컴�'
	     db '� Netstats      �'
	     db '� Start Server  �'
	     db '� Net Settings  �'
	     db '� Auto Config   �'
	     db '� Manual Config �'
	     db '� Exit....      �'
	     db '읕컴컴컴컴컴컴컴�'

WinHelp      db 17,4,color2a
	     db '旼컴컴컴컴컴컴컴�'
	     db '� TCP/IP Help   �'
	     db '� About DexServ �'
	     db '읕컴컴컴컴컴컴컴�'

Stack_Error:   db 32
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�  *****  STACK ERROR!  *****  �'
	     db '�    No TCP/IP Stack Loaded    �'
	     db '�   Press anykey to continue   �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

Dhcp_Error:   db 32
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�  *****  DHCP  ERROR!  *****  �'
	     db '�     No DHCP Server Found!    �'
	     db '�   Press anykey to continue   �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

WinAbout:    db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�       ______          _____                        �'
	     db '�       |  _  \        /  ___|                       �'
	     db '�       | | | |_____  _\ `--.  ___ _ ____   __       �'
	     db "�       | | | / _ \ \/ /`--. \/ _ \ '__\ \ / /       �"
	     db '�       | |/ /  __/>  </\__/ /  __/ |   \ V /        �'
	     db '�       |___/ \___/_/\_\____/ \___|_|    \_/         �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                 HTTP SERVER v0.01                  �'
	     db '�             Coded by Team DexOS 2007               �'
	     db '�                   WWW.DEX4U.COM                    �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

ServerStats: db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�       ______          _____                        �'
	     db '�       |  _  \        /  ___|                       �'
	     db '�       | | | |_____  _\ `--.  ___ _ ____   __       �'
	     db "�       | | | / _ \ \/ /`--. \/ _ \ '__\ \ / /       �"
	     db '�       | |/ /  __/>  </\__/ /  __/ |   \ V /        �'
	     db '�       |___/ \___/_/\_\____/ \___|_|    \_/         �'
	     db '�                                                    �'
	     db '�              DexOS Http Server v0.01               �'
	     db '�                                                    �'
	     db '�         Server status           :                  �'
	     db '�         Current Time            :                  �'
	     db '�         Current Date            :                  �'
	     db '�         Restart Time            :                  �'
	     db '�         Restart Date            :                  �'
	     db '�         Total Accesses          :                  �'
	     db '�         Total Bytes             :                  �'
	     db '�         Total 404               :                  �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

NetstatAbout: db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�                     Netstat                        �'
	     db '냐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴캐'
	     db '�                                                    �'
	     db '�         Ethernet card status    : xxxxxxxx         �'
	     db '�                                                    �'
	     db '�         IP packets received     : xxxxxxxx         �'
	     db '�         ARP packets received    : xxxxxxxx         �'
	     db '�         Dumped received packets : xxxxxxxx         �'
	     db '�                                                    �'
	     db '�         EMPTY QUEUE             : xxxxxxxx         �'
	     db '�         IPOUT QUEUE             : xxxxxxxx         �'
	     db '�         IPIN  QUEUE             : xxxxxxxx         �'
	     db '�         NET1OUT QUEUE           : xxxxxxxx         �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

WinCommands: db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�                     Help Text                      �'
	     db '냐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴캐'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

WinFasm:     db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�              Set Network Properties                �'
	     db '�       Please enter numbers and press enter         �'
	     db '�  to move onto next, then comfirm settings at end.  �'
	     db '냐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴캐'
	     db '�                                                    �'
	     db '�   IP Address:  [               ]   <press enter>   �'
	     db '�   Gateway IP:  [               ]   <press enter>   �'
	     db '�   Subnet Mask: [               ]   <press enter>   �'
	     db '�   DNS IP:      [               ]   <press enter>   �'
	     db '�                                                    �'
	     db '�    Save Exit      New Settings      Exit NoSave    �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

WinSettings: db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�                Network Properties                  �'
	     db '냐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴캐'
	     db '�                                                    �'
	     db '�   IP Address:  [                            ]      �'
	     db '�   Gateway IP:  [                            ]      �'
	     db '�   Subnet Mask: [                            ]      �'
	     db '�   DNS IP:      [                            ]      �'
	     db '�   Lease :      [                            ]      �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

WinAuto:     db 54
	     db '旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커'
	     db '�              AutoDHCP 1.01 By hidnplayr            �'
	     db '�        Looking for dhcp server, Please wait        �'
	     db '�  Testing ',0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,0b1h,'   �'
	     db '냐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴캐'
	     db '�                                                    �'
	     db '�   IP Address:  [                             ]     �'
	     db '�   Gateway IP:  [                             ]     �'
	     db '�   Subnet Mask: [                             ]     �'
	     db '�   DNS IP:      [                             ]     �'
	     db '�                                                    �'
	     db '�            Save Exit       Exit NoSave             �'
	     db '�                                                    �'
	     db '읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸'

AltMessage db 'Press Alt for Menu',0,0,0,0

MenuBar 	    db 0
color4		    db 0
OutPutMonitor	    dd 0
PosX		    db 0
PosY		    db 0
ScanKey 	    db 0
AsciiKey	    db 0
Char		    db 0
ErrorCode	    db 0

ExitEditor	    db 0
ShowText	    db 0
WinY		    dw 0
WinX		    dw 0
WinXC		    dw 0
WinXDHCP	    dw 0
BarExit 	    db 0
Hz		    dw 0
StackNotLoaded	    db 0
StandaredPalette    dd 0