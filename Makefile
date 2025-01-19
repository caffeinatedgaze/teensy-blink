.PHONY: test
test:
	pio test -e test ${KARGS}

.PHONY: upload 
upload:
	pio run -e release --target upload
	pio device monitor

.PHONY: build
build:
	pio run

.PHONY: install-lib
install-lib:
	pio pkg install --library
