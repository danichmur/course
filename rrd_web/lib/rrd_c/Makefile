all: cl

INC_DIR = /home/parallels/course/api/
LIB=-L$(INC_DIR)
INC=-I$(INC_DIR)

CC = gcc

cl: web_client.c 
	$(CC) $(INC) -c -fPIC web_client.c -o web_client.o 
	$(CC)  -shared web_client.o -shared $(LIB)/libapi.so -o libweb_client.so

clean:
	-rm web_client.so 2>/dev/null