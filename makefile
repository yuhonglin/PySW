sw: sw.cpp swalign.cpp swalign.h
	g++ --shared -fPIC ./sw.cpp ./swalign.cpp -I/usr/include/python2.6/ -L/usr/lib/python2.6/config -o sw.so

