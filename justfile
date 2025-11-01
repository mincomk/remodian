DEFAULT_ENV := "esp32dev"

build:
    @echo "=== Building project ==="
    pio run -e {{DEFAULT_ENV}}

upload:
    @echo "=== Uploading to board ==="
    pio run -e {{DEFAULT_ENV}} --target upload

flash:
    @echo "=== Flashing board (build + upload) ==="
    pio run -e {{DEFAULT_ENV}} && pio run -e {{DEFAULT_ENV}} --target upload

monitor:
    @echo "=== Monitoring serial output ==="
    pio device monitor -e {{DEFAULT_ENV}}

test:
    @echo "=== Running tests ==="
    pio test -e {{DEFAULT_ENV}}

run:
    @echo "=== Build + Upload + Monitor ==="
    just build
    just upload
    just monitor

