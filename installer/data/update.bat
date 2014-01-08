@echo Off

tskill xpam
IF EXIST newxpam.exe (
	del xpam.exe
	RENAME newxpam.exe xpam.exe
)
start xpam.exe
