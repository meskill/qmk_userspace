{
  description = "Qmk cli flake";

  # Flake inputs
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";

    flake-compat = {
      url = "github:edolstra/flake-compat";
      flake = false;
    };
  };

  # Flake outputs
  outputs = { self, nixpkgs, flake-compat }:
    let
      # The systems supported for this flake
      supportedSystems = [
        "x86_64-linux" # 64-bit Intel/AMD Linux
        "aarch64-linux" # 64-bit ARM Linux
        "aarch64-darwin" # 64-bit ARM macOS
      ];

      # Helper to provide system-specific attributes
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem ({ pkgs }: {
        default = pkgs.mkShell {
          # The Nix packages provided in the environment
          # Add any you need here
          packages = with pkgs; [
            qmk
            dos2unix
          ];

          # Set any environment variables for your dev shell
          env = { };

          # Add any shell logic you want executed any time the environment is activated
          shellHook = ''
            qmk config user.overlay_dir="$(pwd)"
          '';
        };
      });
    };
}
