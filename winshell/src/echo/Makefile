binfile = echo1.exe

all:$(binfile) ..\..\bin\$(binfile)

$(binfile):main.cpp
	g++ main.cpp -o $(binfile)

..\..\bin\$(binfile):$(binfile)
	copy $(binfile) ..\..\bin\
