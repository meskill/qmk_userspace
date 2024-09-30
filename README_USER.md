# QMK Userspace

## First time usage

1. Clone the repo
2. Start the nix shell. It should happen automatically with direnv or run `nix develop` explicitly.
3. Run `setup.nu` to initialize the environment
4. Now run `qmk userspace-compile` to compile the firmware

## Update qmk_firmware version

1. Search for the interested tag version inside the [qmk_firmware repo](https://github.com/qmk/qmk_firmware)
2. Update the file `qmk_tag` with the new tag
3. Run `setup.nu` to update qmk_firmware locally
4. Make sure to address breaking changes between versions mentioned in the [docs](https://docs.qmk.fm/breaking_changes) if any
5. Push the changes to `qmk_tag` to update the version on remote and build the new artifact on CI
