all: server client

CC="gcc"
ARGS="-W -Wall -g"

server: server.c
	${CC} ${ARGS} -o server server.c

client: client.c
	${CC} ${ARGS} -o client client.c

clean:
	rm server client
