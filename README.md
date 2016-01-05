# c_sqlite3
An interface for communication with SQLite DB.



-------------
Before usage of SQLite DB in C project, there is a need to download resource files.
For me this webside was helpful:
http://www.linuxfromscratch.org/blfs/view/svn/server/sqlite.htm

Steps:
1. Download source code
2. Unzip file
  unzip -q ../sqlite-doc-3090200.zip
3. Run configuration script with all parameters
  ./configure --prefix=/usr --disable-static CFLAGS="-g -O2 -DSQLITE_ENABLE_FTS3=1 -DSQLITE_ENABLE_COLUMN_METADATA=1     \
              -DSQLITE_ENABLE_UNLOCK_NOTIFY=1 -DSQLITE_SECURE_DELETE=1 -DSQLITE_ENABLE_DBSTAT_VTAB=1" && make
4. Run installation script:
  sudo make install
5. Check availability of header file
  find . -name sqlite3.h
  ...
  ./usr/include/sqlite3.h   # location of header file
  ...
6. Include file to your project
  #include <sqlite3.h>
7. Compile your project including SQLite library
  gcc main.c -lsqlite3 -o main_out 
