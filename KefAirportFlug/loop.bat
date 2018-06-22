@ECHO OFF
:loop
echo %date% %time% - Updating flights
timeout /t 60 > nul
goto loop
