all: sample

sample.h: variant-parse.py sample.gv
	./variant-parse.py --prefix=sample sample.gv > sample.h

sample: sample.c sample.h 
	gcc `pkg-config --cflags --libs glib-2.0` -g -Wall -o sample sample.c
