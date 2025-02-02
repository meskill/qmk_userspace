let
  lock = builtins.fromJSON (builtins.readFile ./nix/flake.lock);
  flake-compat = fetchTarball {
    url = "https://github.com/edolstra/flake-compat/archive/${lock.nodes.flake-compat.locked.rev}.tar.gz";
    sha256 = lock.nodes.flake-compat.locked.narHash;
  };

  src = builtins.path {
    path = ./nix;
    name = "source";
  };
in
(import flake-compat { inherit src; }).shellNix
