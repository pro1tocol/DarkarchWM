#!/bin/sh

DIR="$HOME/.config/polybar"

# Terminate already running bar instances
pkill polybar

# Launch the bar
polybar -q main -c "$DIR"/config.ini &
