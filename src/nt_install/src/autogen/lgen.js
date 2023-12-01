var fs = require("fs")

var listing_raw = fs.readFileSync("listing.txt").toString("utf-8");
var listing_array = listing_raw.split("\n");

var result = "";

listing_array.forEach((obj) => {
    var file = obj.split(".");

    result += `"${obj}", "*nt/sounds/${file[0]}.wav", "${file[0]}.wav",\n`;
})

console.log(result);