SHELL:=/bin/bash
VERSION=0x03

.PHONY: compile
compile:
	@arduino-cli compile --output-dir bin --fqbn arduino:samd:nano_33_iot \
	--build-property "compiler.cpp.extra_flags=-std=c++14" -v --build-path build .

.PHONY: deploy
deploy:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/stretcher.ino.bin --fqbn arduino:samd:nano_33_iot -p /dev/ttyACM0 --verbose