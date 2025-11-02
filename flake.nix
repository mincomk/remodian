{
  description = "Remodian Flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          name = "remodian";
          buildInputs = with pkgs; [
            python313
            python313Packages.pip
            libffi
            openssl
            pkg-config
            platformio
            clang
            clang-tools
            just
          ];

          shellHook = ''
            export PATH=${pkgs.platformio}/bin:$PATH

            export XTENSA_ROOT=$HOME/.platformio/packages/toolchain-xtensa-esp32
            export XTENSA_HOME=$XTENSA_ROOT/xtensa-esp32-elf/include
            export CLANGD_FLAGS=--query-driver=$XTENSA_ROOT/bin/xtensa-esp32-elf-g++

            export CPATH=$XTENSA_HOME:$XTENSA_HOME/c++/8.4.0:$XTENSA_HOME/c++/8.4.0/xtensa-esp32-elf:$CPATH

            cd firmware
            pio run -t compiledb
            cd ..

            echo ""
            echo "🌈 Don't forget to pull before edit! 🌈"
            echo ""
          '';

        };
      });
}
