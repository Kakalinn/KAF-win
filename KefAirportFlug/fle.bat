del komur*

wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur"

powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')" > out.fly
kvl komur >> out.fly
