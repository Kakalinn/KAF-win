cd %1
del komur*

wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur"

echo ~~~-~~~ > out.fly
powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')" >> out.fly
"..\KefAirportFlug\kvl" komur >> out.fly
echo ~~~-~~~ >> out.fly
