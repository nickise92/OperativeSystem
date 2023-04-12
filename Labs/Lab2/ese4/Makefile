CFLAGS=-Wall -std=c99
INCLUDES=-I./inc

PRODUCT_SRCS=src/product.c
ESE4_SRCS=src/errExit.c src/main.c 

PRODUCT_OBJS=$(PRODUCT_SRCS:.c=.o)
ESE4_OBJS=$(ESE4_SRCS:.c=.o)

all: product process_ese4

product: $(PRODUCT_OBJS)
	@echo "Making executable "$@
	@$(CC) $^ -o $@

process_ese4: $(ESE4_OBJS)
	@echo "Making executable: "$@
	@$(CC) $^ -o $@

.c.o:
	@echo "Compiling: "$<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean

clean:
	@rm -f src/*.o process_ese4 product
	@echo "Removed object files and executable..."