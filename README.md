# bf.c

A brainf**k interpreter written in C.

## Usage:

```sh
git clone https://github.com/cultureshocked/bf.c
cd bf.c
gcc -o bf bf.c lib/LinkedList.c
gcc -o bf_arr bf_arr.c
./bf tests/min_hello.bf
./bf_arr tests/min_hello.bf
```

## Versions

`bf.c` is for an implementation of the interpreter that uses a Linked List (doubly-linked) for better memory efficiency under ~1500 cells (assuming the compiler aligns structs to 4byte offsets.). Although it may use more memory above 1500 cells, it is also much more scalable, since all memory is allocated dynamically as needed. You can check the code for the Linked List in `lib`.

`bf_arr.c` is an implementation that uses a statically-sized array of 30kb, which is what most online brainf**k guidelines recommend. 

Both implementations support negative indexing.

Both implementations also support input, however EOF is not handled explicitly, so if your program involves reading input until EOF, then you will need to check the EOF definition for your system at this time.

## License

I think that, quite frankly, the only suitable license for a brainf**k interpreter is the WTFPL.

You weren't planning on using this for something serious, were you?
