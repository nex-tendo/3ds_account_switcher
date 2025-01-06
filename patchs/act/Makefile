.PHONY: all clean

all:
	@armips main.s
	@flips -c code.bin patched_code.bin 0004013000003802.ips

clean:
	@rm -rf build