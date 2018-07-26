gcc KefAirportFlug\kvl.c -o KefAirportFlug\kvl

powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('KAF.lnk');$s.WorkingDirectory='%CD%\KefAirportFlug';$s.TargetPath='%CD%\KefAirportFlug\loop.bat';$s.IconLocation='%CD%\plane.ico, 0';$s.Save()"



powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('oldKAF.lnk');$s.WorkingDirectory='%CD%';$s.TargetPath='%CD%\KAF.vbs';$s.IconLocation='%CD%\oldplane.ico, 0';$s.Save()"



cd newKAF
gcc charlone.c -o charlone -lpdcurses
cd ..
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('newKAF.lnk');$s.WindowStyle=3;$s.WorkingDirectory='%CD%';$s.TargetPath='%CD%\newKAF\charlone.exe';$s.IconLocation='%CD%\newplane.ico, 0';$s.Save()"
