Set oShell = CreateObject ("Wscript.Shell") 
Dim strArgs
strArgs = "cmd /c KomuFlug.bat"
oShell.Run strArgs, 0, false
