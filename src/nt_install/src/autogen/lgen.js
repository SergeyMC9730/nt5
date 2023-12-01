var fs = require("fs")

var listing_raw = fs.readFileSync("listing7.txt").toString("utf-8");
var listing_array = listing_raw.split("\n");

var result = "";

var file_format = "jpg";
var directory = "images/user/ui";

listing_array.forEach((obj) => {
    var file = obj.split(".");

    result += `"${obj}", "*nt/${directory}/${file[0]}.${file_format}", "${file[0]}.${file_format}",\n`;
})

console.log(result);