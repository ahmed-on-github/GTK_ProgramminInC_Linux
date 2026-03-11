# __The setup for GTK C Programming__

## 1- Install gtk3 (I use CentOS, so I use yum/dnf package manager):
```bash
$ sudo yum install -y gtk3 gtk3-devel
```

## 2- Create a bash script file that eases building gtk programs in C via gcc compiler
```bash
$ cat << EOF >> gcc-gtk.sh
#!/bin/bash

export DISPLAY=:0.0
GTK_FLAGS=$(pkg-config --cflags --libs gtk+-3.0)
# 1st passed argument is the .c file name , 2nd is the executable output file name
gcc $1 -g -O1 -o $2 $GTK_FLAGS

EOF
```
## 3- Install the shell script under /bin or /usr/bin

```bash
$ chmod +x ./gcc-gtk.sh
$ sudo install gcc-gtk.sh /usr/bin
```
## 4- Add a small alias to the gcc-gtk.sh to ease executing it
Note: It's better to source this installed shell script as it contains a shell variable required by the same shell that will build the gtk project
```bash
$ sudo echo 'alias gcc-gtk=\'source `which gcc-gtk.sh`\'' >> ~/.bashrc 
```

## 5- Sample build and run commands

```bash
$ gcc-gtk ./gtk3-app1.c window1 
$ ./window1
```
