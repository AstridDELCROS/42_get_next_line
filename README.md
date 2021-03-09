## Get Next Line

*Summary: The aim of this project is to make you code a function that returns a line ending with a newline, read from a ﬁle descriptor.*

This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming: static variables.

|Function name|get\_next\_line|
|-|-|
|Prototype|int get\_next\_line(int fd, char \*\*line);|
|Turn in files|get\_next\_line.c, get\_next\_line\_utils.c, get\_next\_line.h|
|Parameters|1. file descriptor for reading, 2. The value of what has been read|
|Return value|1 : A line has been read, 0 : EOF has been reached, -1 : An error happened|
|External functs|read, malloc, free|
|Description|Write a function which returns a line read from a file descriptor, without the newline.|

* Calling your function get\_next\_line in a loop will then allow you to read the text available on a ﬁle descriptor one line at a time until the EOF.
* Make sure that your function behaves well when it reads from a ﬁle and when it reads from the standard input.
* libft is not allowed for this project. You must add a get\_next\_line\_utils.c ﬁle which will contain the functions that are needed for your get\_next\_line to work.
* Your program must compile with the ﬂag -D BUFFER\_SIZE=xx. which will be used as the buﬀer size for the read calls in your get\_next\_line. This value will be modiﬁed by your evaluators and by moulinette.
* Compilation will be done this way : gcc -Wall -Wextra -Werror -D BUFFER\_SIZE=32 get\_next\_line.c get\_next\_line\_utils.c
* Your read must use the BUFFER\_SIZE deﬁned during compilation to read from a ﬁle or from stdin.
* In the header ﬁle get\_next\_line.h you must have at least the prototype of the function get\_next\_line.
* We consider that get\_next\_line has an undeﬁned behavior if, between two calls, the same ﬁle descriptor switches to a diﬀerent ﬁle before EOF has been reached on the ﬁrst fd.
* lseek is not an allowed function. File reading must be done only once.
* Finally we consider that get\_next\_line has an undeﬁned behavior when reading from a binary ﬁle. However, if you wish, you can make this behavior coherent.
* Global variables are forbidden.