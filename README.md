#Shell Lab

Project Introduction
-------------------
This is a CLI program that allows you to run other programs in bash shells. Additionally,
this shell can also invoke internal commands (fil, history, forweb, and nls) as well as
allow file redirections (>, <, |)

Hours spent: 
* design: 2 hour
* developement: 10 hours
* test: 3 hour

Internal commands explanation
-----------------------------

###history
This command will list all history commands that you type into the shell, like history command
in bash shell

Syntax:
```
history
```

###fil
The fil command works as follows:
	1. All tabs are replaced by an equivalent number of spaces.
	1. All trailing blanks at the end of each line are removed.
	1. All lines longer than 132 characters are folded.
	1. A form fed is added for every 66 lines from the previous form feed.
	1. All BACKSPACE and nonprinting characters are removed.

Syntax:
```
fil [from] [to]
```

###forweb
This command takes the name of a subdirectory 'dirname' and makes all files o+r and all folders 
o+rx in the file hierarchy rooted at 'dirname'

Syntax:
```
forweb [dirname]
```

###nls
This command displays regular files and directories separately

Syntax:
```
nls [dirname]
```

Compilation
-----------
Create a symple link from Makefile_c
```
ln -s Makefile_c Makefile
```
Now, you can compile c files and create executable file
```
make
```

Limitation
----------
###Chains of pipes: 
The shell can't do the following command:
```
~~ls | wc | wc~~
```

Internal commands won't handle file redirection: <, >, |
~~~
history > out.txt
nls . | wc
~~~