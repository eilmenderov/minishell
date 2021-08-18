-Minishell-

he objective of this project is for you to create a simple shell.
Yes, yourlittle bash or zsh.
You will learn a lot about processes and file descriptors.


How to use:		make re && make clean && ./minishell

External functs:

-- readline -- (типо gnl !!!нужно фришить!!! #include <stdio.h>)
http://manpages.org/readline/3

-- fork -- (создает дочерний процесс #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=fork&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://ru.manpages.org/fork/2

-- wait / waitpid -- (ожидает завершения процесса  #include <sys/wait.h>)
https://www.opennet.ru/man.shtml?topic=waitpid&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://ru.manpages.org/waitpid/2

-- wait3 -- (ожидает смену состояния в стиле BSD #include <sys/wait.h>)
http://ru.manpages.org/wait3/2

-- wait4 -- (ожидает смену состояния в стиле BSD #include <sys/wait.h>)
http://ru.manpages.org/wait4/2

-- signal -- (работа с сигналами #include <signal.h>)
http://ru.manpages.org/signal/2

-- kill -- (send a signal to a process or a group of processes #include <signal.h> )
https://www.opennet.ru/man.shtml?topic=kill&category=3&russian=5

-- getcwd -- (возвращают текущий рабочий каталог #include <unistd.h>)
http://ru.manpages.org/getcwd/3

-- chdir -- (изменить рабочий каталог #include <unistd.h>)
http://ru.manpages.org/chdir/2

-- stat / lstat / fstat -- (считывает состояние файла #include <unistd.h>)
http://ru.manpages.org/stat/2

-- unlink -- (удаляет указанный файл #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=unlink&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/unlink

-- execve -- (выполнить программу #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=execve&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man

-- dup / dup2 -- (создать дубликат файлового дескриптора #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=dup&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/dup-dup2

-- pipe -- (создает канал #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=pipe&category=2&russian=0

-- opendir -- (открывает каталог #include <dirent.h>)
http://ru.manpages.org/opendir/3

-- readdir -- (чтение содержимого каталога #include <dirent.h>)
http://ru.manpages.org/readdir/3

-- closedir -- (закрыть каталог #include <dirent.h>)
http://ru.manpages.org/closedir/3

-- isatty -- (проверяет, указывает ли файловый дескриптор на терминал #include <unistd.h>)
http://ru.manpages.org/isatty/3

-- ttyname -- (возвращает имя терминала #include <unistd.h>)
http://ru.manpages.org/ttyname/3

-- ttyslot -- (поиск слота текущего терминала пользователя в определённом файле #include <unistd.h>)
http://ru.manpages.org/ttyslot/3

-- ioctl -- (управляет устройством  #include <sys/ioctl.h>)
http://ru.manpages.org/ioctl/2

-- getenv -- (возвращают значения переменной окружения #include <stdlib.h>)
http://ru.manpages.org/getenv/3

-- tcsetattr -- (установить параметры, связанные с терминалом  #include <termios.h>)
http://manpages.org/tcsetattr#synopsis

-- tcgetattr -- (получить параметры, связанные с терминалом #include <termios.h>)
http://manpages.org/tcgetattr

-- tgetent / tgetflag / tgetnum / tgetstr / tgoto / tputs -- (#include <curses.h>  #include <term.h>)
http://manpages.org/tgetflag/3

-- strerror -- (возвращают строку, описывающую ошибку #include <string.h>)
https://www.opennet.ru/man.shtml?topic=strerror&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/strerror-0

-- errno -- (код последней ошибки #include <errno.h>)
http://ru.manpages.org/errno/3

rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history

-- printf -- (#include <stdio.h>)
https://www.opennet.ru/man.shtml?topic=printf&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man

-- malloc --
https://www.opennet.ru/man.shtml?topic=malloc&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/write-rtlwrite

-- free --
http://www.c-cpp.ru/content/free

-- write --
https://www.opennet.ru/man.shtml?topic=write&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/write-rtlwrite

-- open -- (открывае/создает файл  #include <fcntl.h>)
http://ru.manpages.org/open/2
https://www.opennet.ru/man.shtml?topic=open&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/open-rtlopen

-- read -- (читает из файловго дескриптора #include <unistd.h>)
http://ru.manpages.org/read/2
https://www.opennet.ru/man.shtml?topic=read&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/read-rtlread

-- close -- (закрывает файловый дескриптор #include <unistd.h>)
http://ru.manpages.org/close/2
https://www.opennet.ru/man.shtml?topic=close&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/content/close-rtlclose

-- exit -- (функция, завершающая работу программы #include <unistd.h>)
https://www.opennet.ru/man.shtml?topic=exit&russian=0&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man
http://www.c-cpp.ru/books/exit



Введение
Существование оболочек связано с самим существованием ИТ. В то время все программисты согласились, что общение с
компьютером с помощью выровненных переключателей 1/0 вызывает серьезное раздражение. Вполне логично, что им пришла
в голову идея общаться с компьютером с помощью интерактивных строк команд на языке, несколько близком к английскому.
С помощью Minishell вы сможете совершить путешествие во времени и вернуться к проблемам, с которыми люди сталкивались,
когда Windows еще не существовало.


Общие указания

-Ваш проект должен быть написан в соответствии с нормами.  Если у вас есть бонусные файлы/функции, они будут включены в
проверку нормы, и вы получите 0, если в них есть ошибка нормы.
-Ваши функции не должны завершаться неожиданно (segmentation fault, bus error, double free, etc), кроме неопределенного
поведения.  Если это произойдет, ваш проект будет считаться неработоспособным и получит a0 во время оценки.
-Все выделенное пространство памяти кучи должно быть правильно освобождено, когда это необходимо. Утечки не допускаются.
-Если предмет требует этого, вы должны предоставить Makefile, который скомпилирует ваши исходные файлы до требуемого
результата с флагами -Wall, -Wextra и -Werror, и ваш Makefile не должен перелинковываться.
-Ваш Makefile должен, по крайней мере, содержать правила $(NAME), all,clean, fclean и re.
-Для включения бонусов в ваш проект, вы должны включить в ваш Makefile правило bonus, которое добавит все различные заголовки,
librairies или функции, которые запрещены в основной части проекта. Бонусы должны находиться в другом файле_bonus.{c/h}.
Оценка обязательной и бонусной части производится отдельно.
-Если ваш проект позволяет использовать свою libft, вы должны скопировать ее исходники и связанный с ней Makefile в папку libft с
ее связанным Makefile. Makefile вашего проекта должен компилировать библиотеку, используя ее Makefile, а затем компилировать проект.
-Мы призываем вас создавать тестовые программы для вашего проекта, даже если эта работа не будет сдаваться и не будет оцениваться.
Это даст вам возможность легко проверить свою работу и работу ваших коллег. Эти тесты будут особенно полезны во время защиты.
Действительно, во время защиты вы можете использовать свои тесты и/или тесты коллеги, которого вы оцениваете.
-Отправьте свою работу в назначенный вам git-репозиторий. Оцениваться будет только та работа, которая находится в git-репозитории.
Если Deepthought назначит оценку вашей работы, это будет сделано после того, как вы оцените работу сверстника. Если во время
оценивания Deepthought в любом разделе вашей работы будет допущена ошибка, оценка будет остановлена.


Обязательная часть

Ваша оболочка должна:
- Не интерпретировать незакрытые кавычки или неопределенные специальные символы типа \ or ; .
- Не использовать более одной глобальной переменной, думать об этом и быть готовым объяснить, почему вы это делаете.
- Показывать подсказку при ожидании новой команды.
- Иметь рабочую Историю.
- Искать и запускать нужный исполняемый файл (на основе переменной PATH или используя относительный или абсолютный путь).
- Он должен реализовывать встроенные модули:
   ◦echo с опцией -n
   ◦cd только с относительным или абсолютным путем
   ◦pwd без опций
   ◦export без опций
   ◦unset без опций
   ◦env без опций и аргументов
   ◦exit без опций
- ' запретить любую интерпретацию последовательности символов.
- " запретить любую интерпретацию последовательности символов, кроме $.
- Перенаправления:
   ◦ < должен перенаправлять ввод.
   ◦ > перенаправляет вывод.
   ◦ "<<" считывает ввод из текущего источника до тех пор, пока не появится строка, содержащая только ограничитель. ему не нужно обновлять историю!
   ◦ ">>" должен перенаправлять вывод в режиме append.
- Pipes | Выход каждой команды в конвейере соединяется с помощью трубы с входом следующей команды.
- Переменные окружения ($, за которыми следуют символы) должны расширяться до своих значений.
- $? должно расширяться до состояния выхода последнего выполненного конвейера переднего плана.
- ctrl-C ctrl-D ctrl-\ должны работать как в bash.
- В интерактивном режиме:
   ◦ ctrl-C печатать новый запрос на новой строке.
   ◦ ctrl-D выйти из оболочки.
   ◦ ctrl-\ ничего не делает.
Функция Readline может создавать некоторые утечки, которые не нужно исправлять. Но будьте внимательны, ваш собственный код не должен создавать утечек.
Вы должны ограничиться описанием темы. Все, что не задано, не является обязательным. Для каждого пункта, если у вас есть сомнения, возьмите bash в качестве справочника.


Бонусная часть
- Если обязательная часть не идеальна, даже не думайте о бонусах.
- && , || со скобками для приоритетов.
- Подстановочный знак * должен работать для текущего рабочего каталога.

instal brew:
curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

HOME macOS:
-L /usr/local/opt/readline/lib
-I /usr/local/opt/readline/include

school21 macOS:
-L /Users/${USER}/.brew/opt/readline/lib
-I /Users/${USER}/.brew/opt/readline/include

.gitignore
/msh
minishell_*
.DS_Store

EXIT CODE:
-1 - malloc error