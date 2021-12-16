# bfInterp
(yet another) brainf interpreter. I wrote this in a day, so I'm still pretty proud of myself.

### compiling
I have a makefile, but it's not cross platform at all. Really just run
```bash
<your compiler> main.c -o bfi
```
and that's it!

### notes
* This does not support negative dataPtr indexes, so programs that require this feature won't work. Feel free to improve.
