huff: util/util.c heap/heap.c huffman/huffman.c frequency/frequency.c codes/codes.c decompress/decompress.c compress/compress.c main.c 
	gcc util/util.c heap/heap.c huffman/huffman.c frequency/frequency.c codes/codes.c decompress/decompress.c compress/compress.c main.c -o main
test: heap/heap.c huffman/huffman.c codes/codes.c 	
	gcc util/util.c tests/tests.c frequency/frequency.c heap/heap.c huffman/huffman.c codes/codes.c -lcunit -o testes
clean:
	rm main