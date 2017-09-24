# КЛИНЕТ/СЕРВЕР

Итак, сначала по сетапу:

**OS:** Mint 18.1 serena

**Kernel:** x86_64 Linux 4.4.0-92-generic

**CPU:** Intel Core i5-4200H CPU @ 3.4GHz

**RAM:** 8 GB

**Compiler:** gcc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609

**CMake:** version 3.8.2

**IDE:** CLion 2017.2.2

## ИСПОЛЬЗУЕМЫЕ ИСТОЧНИКИ

В написании я использовал пачку разных 
ссылок (все не припомнить), однако некоторые заслуживают
особого внимания, а именно:
- вот с [этого](http://www.linuxhowtos.org/C_C++/socket.htm) начал;
- [этот](http://beej.us/guide/bgnet/output/html/multipage/index.html) парень шикарно пишет;
- [здесь](https://rsdn.org/article/unix/sockets.xml) тоже есть что почитать;
- ну и вот в
[этой](http://computersbooks.net/index.php?id1=4&category=language-programmer&author=sneyder-y&book=2002)
книжке дается очень подробное описание функций, которые используются при установлении TCP-соединения,
передаче данных и т.д. и т.п.

## РЕЗЮМЕ

Стоит оговориться, что обработка сервером запросов нескольких клиентов достигается
за счет обработки запросов в новом процессе, не потоке, что несколько отличается
от первоначальной спеки. Также я не успел поэкспериментировать с неблокирующими сокетами.