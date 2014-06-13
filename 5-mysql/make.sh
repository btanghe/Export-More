## mysql c program
## based on http://www.cyberciti.biz/tips/linux-unix-connect-mysql-c-api-program.html
##
## check your mysqlclient lib directory
## mysql_config --libs
## 	output: -Wl,-Bsymbolic-functions -rdynamic -L/usr/lib/mysql -lmysqlclient
## check your include
## mysql_config --cflags
## 	output: -I/usr/include/mysql  -DBIG_JOINS=1  -fno-strict-aliasing   -DUNIV_LINUX -DUNIV_LINUX
## 
## gcc -o output-file $(mysql_config --cflags) mysql-c-api.c $(mysql_config --libs)
sudo apt-get install libmysqlclient16 libmysqlclient16-dev
gcc -o mysql mysql.c -L/usr/lib/mysql -lmysqlclient
