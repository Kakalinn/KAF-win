del KefAirportFlug\kvl.exe
del KefAirportFlug\komur
del KefAirportFlug\out.fly
gcc KefAirportFlug\kvl.c -o KefAirportFlug\kvl

powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('KAF.lnk');$s.WorkingDirectory='%CD%\KefAirportFlug';$s.TargetPath='%CD%\KefAirportFlug\loop.bat';$s.IconLocation='%CD%\plane.ico, 0';$s.Save()"



powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('oldKAF.lnk');$s.WorkingDirectory='%CD%';$s.TargetPath='%CD%\KAF.vbs';$s.IconLocation='%CD%\oldplane.ico, 0';$s.Save()"



del newKAF\komur
del newKAF\brottfarir
del newKAF\out.fly
del newKAF\inn.fly
del newKAF\charlone.exe
del newKAF\kvl.exe
gcc newKAF\charlone.c -o newKAF\charlone -lpdcurses
copy KefAirportFlug\kvl.exe newKAF\kvl.exe

powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('newKAF.lnk');$s.WindowStyle=3;$s.WorkingDirectory='%CD%';$s.TargetPath='%CD%\newKAF\charlone.exe';$s.IconLocation='%CD%\newplane.ico, 0';$s.Save()"
