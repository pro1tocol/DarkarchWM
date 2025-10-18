#!/bin/sh
append_path() {
    if ! echo "$PATH" | grep -qE "(^|:)$1($|:)"; then
        export PATH="$1:$PATH"
    fi
}