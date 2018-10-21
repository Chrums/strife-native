var addon = require("/home/michael/projects/strife/strife/build/lib/main.node");

var nbind = require('nbind');
var lib = nbind.init().lib;

lib.sayHello('you');

addon.main();
