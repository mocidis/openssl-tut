.PHONY: all clean
APP:=openssl-app

MAIN_DIR:=.
MAIN_SRCS:= $(APP).c

O_SRCS:=my-openssl.c
O_DIR:=.

LIBS := $(shell pkg-config libpjproject --libs) -lcrypto

CFLAGS :=-I$(MAIN_DIR)/include -Wall

all: $(APP)

$(APP): $(O_SRCS:.c=.o) $(MAIN_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(O_SRCS:.c=.o): %.o: $(O_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_SRCS:.c=.o): %.o: $(MAIN_DIR)/test/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr *.o $(APP)
