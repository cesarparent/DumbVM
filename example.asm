mov r0,26
mov r1,97
cll storehello
cll displayhello
hlt

lbl storehello
	mov r0,72
	cpo r0,2000
	mov r0,101
	cpo r0,2001
	mov r0,108
	cpo r0,2002
	mov r0,108
	cpo r0,2003
	mov r0,111
	cpo r0,2004
ret

lbl displayhello
	cpi r5,2000
	cpi r5,2001
	cpi r5,2002
	cpi r5,2003
	cpi r5,2004
ret