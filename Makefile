.PHONY: test
test:
	pio test ${KARGS}

.PHONY: upload 
upload:
	pio run --target upload
	pio device monitor

.PHONY: build
build:
	pio run
