
var gmp = require('./build/default/gmp');
var assert = require("assert");

console.log("gmp version: %s", gmp.version);

var gint = new gmp.Int();
var gint = new gmp.Int(49);
gint.add(1);

console.log(gint.toString());

