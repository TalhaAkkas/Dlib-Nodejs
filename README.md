Node - LZ4 Clib


This is C-bindings of LZ4 library 
LZ4 is the best compression lib so far look for LZ4.org

I tried to use LZ4-Native in serves and LZ4 c lib on mobile side it didn't worked
I hope this will work.

```


var string = "1234567890*1234567890*1234567890*213123123asdasdasdasdsa";
var compressed = LZ4.compress(new Buffer(string), string.length);
var decompressed = LZ4.decompress(compressed, string.length);
console.log(string);
console.log(string.length, compressed.length);
console.log(compressed); // 'world'
console.log(decompressed); // 'world'

```