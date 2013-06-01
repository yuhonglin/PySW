python_version_full := $(wordlist 2,4,$(subst ., ,$(shell python --version 2>&1)))
python_version_major := $(word 1,${python_version_full})
python_version_minor := $(word 2,${python_version_full})

sw.so: sw.cpp swalign.cpp swalign.h
	g++ --shared -fPIC ./sw.cpp ./swalign.cpp -I/usr/include/python${python_version_major}.${python_version_minor}/ -L/usr/lib/python${python_version_major}.${python_version_minor}/config -o sw.so

