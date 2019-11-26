/* Configuration */
/* Make sure this value matches with */
/* arduino/main.cpp */
const BAUDRATE = 460800
const DEVICE = "/dev/tty.usbmodem14401"

const SerialPort = require("serialport")
const Readline = require("@serialport/parser-readline")
const port = new SerialPort(DEVICE, {
	baudRate: BAUDRATE
})

const parser = port.pipe(new Readline({ delimiter: '\r\n' }))
let buffer = ""
let state = 0

parser.on('data', (data) => {
	const b0 = data.substr(0, 8)
	const b1 = data.substr(8)

	if (b0 !== b1) {
		console.log(`Byte mismatch <${b0} != ${b1}>`)
	} else {
		let value = parseInt(b0, 2)
		let char = String.fromCharCode(value)

		switch (state) {
			case 0:
				if (value === 255) {
					buffer = ""

					state = 1
				}
			break

			case 1:
				if (value === 0) {
					console.log(buffer)
					state = 0
				} else {
					buffer += char
				}
			break
		}
	}
})
