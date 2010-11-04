
var gmp = require('./build/default/gmp');
var assert = require("assert");

var a = "23450745058237458237438124381247381327401278039423904183123785901234679435237852037045375237485072304728904023748502374580723804572803745802374723098234509187142";
var b = "90894587590237850247890451273126743687548782309875623443738065740178101237431274810018971234126789867123769146910981289658964389538365892375427436672345780686388";

console.log("gmp version: %s", gmp.version);

/*
assert.equal(gmp.type(function(){}), "function");
assert.equal(gmp.type([]), "array");
assert.equal(gmp.type(Array()), "array");
assert.equal(gmp.type( {} ), "object");
assert.equal(gmp.type( Object() ), "object");
assert.equal(gmp.type( new (function(){}) ), "object");
assert.equal(gmp.type( "hi" ), "string");
assert.equal(gmp.type(  ), "undefined");
assert.equal(gmp.type( undefined ), "undefined");
assert.equal(gmp.type( null ), "null");
assert.equal(gmp.type( true ), "boolean");
assert.equal(gmp.type( false ), "boolean");
assert.equal(gmp.type( Boolean(true) ), "boolean");
assert.equal(gmp.type( -234890 ), "int32");
assert.equal(gmp.type( 299 ), "uint32");
assert.equal(gmp.type( 0 ), "uint32");
assert.equal(gmp.type( -0.49 ), "number");
assert.equal(gmp.type( 3.56 ), "number");
assert.equal(gmp.type( new RegExp("^yo") ), "regexp");
assert.equal(gmp.type( /^a/i ), "regexp");
*/

console.log("add", gmp.add(a,b));
console.log("sub", gmp.sub(a,1));
console.log("mul", gmp.mul(a,b) );
console.log("div", gmp.div(b,4589023485920389) );
console.log("mod", gmp.mod(15, 12.3) );

console.log(gmp.add(1,4));
console.log(gmp.add(1,"4.5234829342839023489203.2"));
