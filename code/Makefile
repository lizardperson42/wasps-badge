.PHONY: build upload clean bin help

help: ## Show this help message
	@echo "Available targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  %-8s - %s\n", $$1, $$2}'

build: ## Build the PlatformIO project
	platformio run --environment ch32

upload: ## Upload firmware to device
	platformio run --target upload --environment ch32

upload-through-docker: ## Build firmware through Docker and upload using rvprog on host (also works on MacOS)
	@if [ ! -d ".venv-docker" ]; then \
		echo "Creating virtual environment..."; \
		docker run --rm -it -v $(CURDIR):/workdir --workdir /workdir --platform linux/amd64 python:3.11 bash -c "python3 -m venv .venv-docker"; \
	fi
	@if [ ! -f ".venv-docker/bin/platformio" ]; then \
		echo "Installing platformio..."; \
		docker run --rm -it -v $(CURDIR):/workdir --workdir /workdir --platform linux/amd64 python:3.11 bash -c ".venv-docker/bin/pip install -U platformio"; \
	fi
	docker run --rm -it -v $(CURDIR):/workdir -v $(CURDIR)/.pio-docker/:/root/.platformio/ --workdir /workdir --platform linux/amd64 python:3.11 bash -c ".venv-docker/bin/platformio run --environment ch32"
	@if [ ! -d ".venv" ]; then \
		echo "Creating virtual environment..."; \
		python3 -m venv .venv; \
	fi
	@if [ ! -f ".venv/bin/rvprog" ]; then \
		echo "Installing rvprog..."; \
		.venv/bin/pip install rvprog; \
	fi
	.venv/bin/rvprog -f .pio/build/ch32/firmware.bin

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
