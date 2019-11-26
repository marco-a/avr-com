#!/bin/sh

avrdude -v -c dragon_isp -p t84 -U flash:w:main.hex
