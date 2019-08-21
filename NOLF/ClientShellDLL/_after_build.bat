copy CShell.dll "D:\Games\NOLF - dev\DebugDLL\"
copy ..\ObjectDLL\Object.lto "D:\Games\NOLF - dev\DebugDLL\"
cd "D:\Games\NOLF - dev\Tools"
.\lithrez.exe c ..\DebugDLL.rez ..\DebugDLL
echo "Finished!"