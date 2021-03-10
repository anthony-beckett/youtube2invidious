all:
	gcc main.c -o yt2

clean:
	rm -f yt2

install: yt2
	mkdir -p /usr/local/bin
	cp -f yt2 /usr/local/bin/yt2
	chmod 755 /usr/local/bin/yt2

uninstall:
	rm -f /usr/local/bin/yt2

.PHONY: all clean install uninstall
