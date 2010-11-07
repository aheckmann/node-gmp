
var gmp = require('./build/default/gmp');
var assert = require("assert");

console.log("gmp version: %s", gmp.version);

assert.equal(0, new gmp.Int().toString());
assert.equal(0, new gmp.Int(0).toString());
assert.equal("0", new gmp.Int().toString());
assert.equal("0", new gmp.Int(0).toString());
assert.equal("10", new gmp.Int(10.9).toString());
assert.equal("1001", new gmp.Int(1).add(1000).toString());
assert.equal("1001", new gmp.Int("1").add(1000).toString());
assert.equal("1001", new gmp.Int(1).add("1000").toString());
assert.equal("1001", new gmp.Int("1").add("1000").toString());

var err;
try {
  new gmp.Int("fail");
} catch (er) {
  err = er;
}
assert.equal("bad argument", err.message);
err = null;

var thirtyThree = new gmp.Int(33);
try {
  thirtyThree.add("fail");
} catch (er) {
  err = er;
}
assert.equal("bad argument", err.message);


assert.equal( "2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580250"
, new gmp.Int("2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580243.2").add("7.9").toString()
);

assert.equal( "2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580250"
, new gmp.Int("2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580243").add("7").toString()
);

assert.equal( "2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580243"
, new gmp.Int("2233445598765432112345678909876543212345728034872035834572034572803457802435728034578023457023580250").add("-7").toString()
);
