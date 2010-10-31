
var gmp = require('./build/default/gmp');

console.log("gmp version: %s" ,gmp.version);
console.log(gmp.str);
console.log(gmp.num);
console.log(gmp.add(4,88));
console.log(gmp.add(4,"x"));
