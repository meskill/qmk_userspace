#! /usr/bin/env nu

# Script to update the qmk_firmware repo with defined tag.
# Call only if changes to the `qmk_tag` file was made to avoid
# unecessary downloads
print "Remove old qmk_firmware repo"

rm -rf ./qmk_firmware

let tag = open qmk_tag | str trim

print $"Start qmk setup for tag: ($tag)"

qmk setup -y --home $"(pwd)/qmk_firmware" --branch $tag
