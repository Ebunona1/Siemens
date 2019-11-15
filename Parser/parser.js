var fs = require("fs")
var data = JSON.parse(fs.readFileSync("AHU06 Heating Coil.json"))
console.log(data)

const items = data
const replacer = (key, value) => value === null ? '' : value // specify how you want to handle null values here
const header = Object.keys(items[0])
let csv = items.map(row => header.map(fieldName => JSON.stringify(row[fieldName], replacer)).join(','))
csv.unshift(header.join(','))
csv = csv.join('\r\n')

console.log(csv)
