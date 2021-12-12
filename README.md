# esphome-sandbox

This contains all the settings for my [ESPHome](https://esphome.io/)
devices.

## Setup

1. `poetry install`
2. `cp example-secrets.yaml secrets.yaml`
3. Edit `secrets.yaml`

## Compiling & Flashing

1. `poetry shell`
2. `esphome office.yaml compile`
3. `esphome office.yaml upload`

## Logs

`esphome office.yaml logs`

## FAQ

### No such file or directory

On NixOS, you might have to patch a few paths on the binaries downloaded
by platformio:

```
patchelf --set-interpreter /nix/store/.../ld-linux-x86-64.so.2 ~/.platformio/packages/toolchain-xtensa/bin/xtensa-lx106-elf-gcc
```

I used this once to patch it all and it seemed to work:

```
for x in `find ~/.platformio -type f -exec head -c 4 {} \; -exec echo " {}" \;  | grep ^.ELF | cut -f 2 -d ' '`; do patchelf --set-interpreter /nix/store/./z56jcx3j1gfyk4sv7g8iaan0ssbdkhz1-glibc-2.33-56/lib/ld-linux-x86-64.so.2 $x; done
```
