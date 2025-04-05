{
  description = "rluu.dev flake";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
      ];
      perSystem = { config, self', inputs', pkgs, system, lib, ... }:
        let
          clangenv = pkgs.keepDebugInfo pkgs.clangStdenv;
        in
        rec {
          devShells.default = pkgs.mkShell.override { stdenv = clangenv; } {
            name = "clang";
            packages = with pkgs; [
              clang-tools
              man-pages
              man-pages-posix
              libllvm
              valgrind
              gdb
              lighttpd
            ] ++ packages.default.buildInputs;
          };
          packages.default =
            let
              ts-langs = (pkgs.tree-sitter.withPlugins (p: map (lang: p.${"tree-sitter-" + lang})
                [ "c" "rust" ]
              ));
            in
            clangenv.mkDerivation
              rec {
                name = "sausage";
                src = ./src;

                buildInputs = with pkgs; [
                  cmark
                  tomlc99
                  tree-sitter
                  ts-langs
                ];

                buildPhase =
                  let
                    sources = builtins.concatStringsSep " "
                      [ "main.c" "meta.c" "tmpl.c" "util.c" "mustach/mustach.c" "hescape/hescape.c" ];
                    includes = builtins.concatStringsSep " "
                      (map (l: "-I${lib.getDev l}/include") buildInputs);
                    ldpath = builtins.concatStringsSep " "
                      (map (l: "-L${lib.getLib l}") buildInputs);
                  in
                  ''
                    cc -Wall -Werror -Wpedantic -o ${name} ${sources} ${ts-langs}/*.so ${includes} ${ldpath} -lcmark -ltoml -ltree-sitter
                  '';

                installPhase = ''
                  mkdir -p $out/bin
                  cp ${name} $out/bin/
                '';
              };
        };
    };
}


