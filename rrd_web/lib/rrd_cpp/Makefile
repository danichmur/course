all: lib

INC_DIR = /home/parallels/course/api/

lib: web_client.cpp 
	g++ -c -fPIC web_client.cpp -o web_client.o -L$(INC_DIR)api -I$(INC_DIR)
	g++ -shared -o web_client.so web_client.o

clean:
	-rm web_client.so 2>/dev/null