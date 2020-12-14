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
