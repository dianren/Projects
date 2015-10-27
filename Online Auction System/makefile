all: server bidder seller
server: server.c
	gcc -g -Wall -o server server.c -lsocket -lnsl -lresolv
bidder: bidder.c
	gcc -g -Wall -o bidder bidder.c -lsocket -lnsl -lresolv
seller: seller.c
	gcc -g -Wall -o seller seller.c -lsocket -lnsl -lresolv