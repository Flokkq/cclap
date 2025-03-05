{
  description = "A basic flake for git-cliff";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            git-cliff
            gnupg
            pre-commit

            # only a compiler as a dependency because of `nob.h`
            gcc
            llvmPackages_19.clang-tools
          ];
        };
      }
    );
}
