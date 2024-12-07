#!/usr/bin/env bash
set -euo pipefail

while read -r line; do
    echo "Deleting: ${line}"
    rm $line
    if [[ -d "$line.dSYM" ]]; then
        echo "Deleting debug symbols: $line.dSYM"
        rm -r "$line.dSYM"
    fi
done < <(find . -type file | xargs -n1 -I{} file {} | grep "executable x86_64" | cut -d':' -f1)
