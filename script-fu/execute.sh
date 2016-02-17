#!/bin/bash
{ cat "$1"; echo "$2"; echo '(gimp-quit 0)'; } | gimp -fi -b -
