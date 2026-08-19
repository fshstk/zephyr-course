.PHONY: build pristine flash clean init update sdk
export ZEPHYR_TOOLCHAIN_VARIANT ?= zephyr

build:
	uv run west build app/

pristine:
	uv run west build app/ --pristine

flash:
	uv run west flash

clean:
	rm -rf build/

init:
	uv venv --clear ../.venv
	uv pip install west
	uv run west init -l .

update:
	uv run west update
	uv run west packages pip | xargs uv pip install
	uv run west zephyr-export
