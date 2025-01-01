.PHONY: all clean

all:
	@mkdir -p build
	@armips main.s
	@flips -c code.bin build/patched_code.bin 0004013000003202.ips

clean:
	@rm -rf build