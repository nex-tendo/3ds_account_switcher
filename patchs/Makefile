.PHONY: all act friends ssl

all: act friends ssl

act:
	@echo "Building act patchs.."
	cd act && make

friends:
	@echo "Building friends patchs.."
	cd friends && make

ssl:
	@echo "Building ssl patchs.."
	cd ssl && make

clean:
	@echo "Cleaning up all patches.."
	find act friends ssl -type f \( -name "patched_code.bin" -o -name "*.ips" \) -exec rm -f {} +
