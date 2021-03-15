all:
	/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
	/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -o main.gb main.o

clean:
	rm -rf *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi