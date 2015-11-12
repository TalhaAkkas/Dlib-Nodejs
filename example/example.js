var LZ4 = require("./..");


console.log(Object.keys(LZ4));
var string = "1234567890*1234567890*1234567890*213123123asdasdasdasdsa";
var compressed = LZ4.compress(new Buffer(string), string.length);
var decompressed = LZ4.decompress(compressed, string.length);
console.log(string);
console.log(string.length, compressed.length);
console.log(compressed); // 'world'
console.log(decompressed); // 'world'