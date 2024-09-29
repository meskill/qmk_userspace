{
  description = "An empty flake template that you can adapt to your own environment";

  # Flake inputs
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/22666a6cbfe50d7e1cef9615544b4477d2e833a7";

  # Flake outputs
  outputs = { self, nixpkgs }:
    let
      # The systems supported for this flake
      supportedSystems = [
        "x86_64-linux" # 64-bit Intel/AMD Linux
        "aarch64-linux" # 64-bit ARM Linux
        "x86_64-darwin" # 64-bit Intel macOS
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
          ];

          # Set any environment variables for your dev shell
          env = { };

          # Add any shell logic you want executed any time the environment is activated
          shellHook = ''
            echo "Start qmk setup"
            tag=$(cat qmk_tag | tr -d "[:space:]")
            qmk setup -y --home "$(pwd)/qmk_firmware" --branch "$tag"
            qmk config user.overlay_dir="$(pwd)"
          '';
        };
      });
    };
}
