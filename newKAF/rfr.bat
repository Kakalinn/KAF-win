cd %1
del komur*
del brottfarir*

wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur"
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/brottfarir"

echo ~~~-~~~ > out.fly
powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')" >> out.fly
kvl komur >> out.fly
echo ~~~-~~~ >> out.fly

echo ~~~-~~~ > inn.fly
powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')" >> inn.fly
kvl brottfarir >> inn.fly
echo ~~~-~~~ >> inn.fly
