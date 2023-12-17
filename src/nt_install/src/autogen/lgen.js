/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

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