all: backlight.c
	gcc -g -Wall -o backlight backlight.c

install:
	cp backlight /usr/local/bin
	ln -S /usr/local/bin/backlight /usr/local/bin/bl

clean:
	$(RM) backlight

uninstall:
	$(RM) /usr/local/bin/bl
	$(RM) /usr/local/bin/backlight
