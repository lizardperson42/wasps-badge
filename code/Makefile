.PHONY: build upload clean bin help

help: ## Show this help message
	@echo "Available targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  %-8s - %s\n", $$1, $$2}'

build: ## Build the PlatformIO project
	platformio run --environment ch32

upload: ## Upload firmware to device
	platformio run --target upload --environment ch32

upload-bin-rvprog: ## Upload pre-compiled firmware.bin using rvprog
	@if [ ! -d ".venv" ]; then \
		echo "Creating virtual environment..."; \
		python3 -m venv .venv; \
	fi
	@if [ ! -f ".venv/bin/rvprog" ]; then \
		echo "Installing rvprog..."; \
		.venv/bin/pip install rvprog; \
	fi
	.venv/bin/rvprog -f firmware.bin

clean: ## Clean build artifacts
	platformio run --target fullclean --environment ch32
