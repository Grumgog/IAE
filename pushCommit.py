# Этот скрипт предназначен для проталкивания изменений репозитория GAMES
# в сеть, на сервис bitbucket
import os
import os.path
import sys
os.chdir(os.path.dirname(sys.argv[0]))
os.system("hg commit");
os.system("hg push https://grumgog@bitbucket.org/grumgog/iae");
input("Конец работы программы... Для продолжения нажмите Enter->");