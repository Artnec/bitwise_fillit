# bitwise_fillit

algorithm that gets as input [tetromino](https://en.wikipedia.org/wiki/Tetromino) shaped pieces, and fits them on smallest possible square map.

this algorytm utilizes the fact that maximum allowed number of pieces is 26.
map is represented as array of 265 bits (16 * 16), and piece as 64 bit long (4 * 16).
this way you can find free place using only one &(and) operation, and remove piece by using one ^(xor) operation.


how to use bitwise_fillit:
```
file named sample contains four tetromino shaped pieces.
cat -e sample
...#$
...#$
...#$
...#$
$
....$
....$
....$
####$
$
.###$
...#$
....$
....$
$
....$
..##$
.##.$
....$
$
....$
.##.$
.##.$
....$
$
....$
....$
##..$
.##.$
$
##..$
.#..$
.#..$
....$
$
....$
###.$
.#..$
....$

bitwise_fillit produces smallest possible square containing all of pieces from given file.
./bitwise_fillit sample
ABBBB.
ACCCEE
AFFCEE
A.FFGG
HHHDDG
.HDD.G
```

file given to bitwise_fillit as argument must contain at least 1 and at most 26 valid pieces,
which must be separated by one new line.
piece is valid if it has exactly four connected '#' symbols,
and twelve '.' symbols, on 4 by 4 square grid.
