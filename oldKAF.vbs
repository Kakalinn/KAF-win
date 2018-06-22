Set oShell = CreateObject ("Wscript.Shell") 
Dim strArgs
strArgs = "cmd /c oldKomuFlug.bat"
oShell.Run strArgs, 0, false
