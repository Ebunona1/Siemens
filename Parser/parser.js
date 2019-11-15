var fs = require("fs")
var temps = JSON.parse(fs.readFileSync("5s res sensor_id=BMS-L1O14S31&start=2017-03-20T00_00_00&end=2017-03-20T23_59_59.json"))
console.log(temps)
