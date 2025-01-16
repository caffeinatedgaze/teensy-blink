.PHONY: test
test:
	pio test -vvv

.PHONY: upload 
upload:
	pio run --target upload
