
var gmp = require('./build/default/gmp');
var assert = require("assert");

console.log("gmp version: %s", gmp.version);

assert.equal(0, new gmp.Int().toString());
assert.equal("0", new gmp.Int(0).toString());

assert.equal(50, new gmp.Int(43.9).add("7.9").toString());

