.PHONY: test
test:
	pio test ${KARGS}

.PHONY: upload 
upload:
	pio run --target upload

.PHONY: build
build:
	pio run
