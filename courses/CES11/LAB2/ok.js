var i = Math.floor(Math.random()*1000);
var j = Math.floor(Math.random()*1000);
for(var k = 0; k < 20; k++){
    console.log(j + " "+ i);
    j = i;
    i = Math.floor(Math.random()*1000);
}