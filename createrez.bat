del /Q my_rez

copy NOLF\ClientRes\CRes.dll my_rez\
copy NOLF\ClientShellDLL\CShell.dll my_rez\
copy NOLF\ObjectDLL\Object.lto my_rez\

del mydlls.rez

TOOLS\lithrez.exe cv mydlls.rez my_rez

pause
