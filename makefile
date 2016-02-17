all: html5/moire1.png html5/moire2.png html5/checkerboard.png

html5/moire1.png: script-fu/create-moire.scm
	script-fu/execute.sh "$<" '(create-moire "$@" 1)'

html5/moire2.png: script-fu/create-moire.scm
	script-fu/execute.sh "$<" '(create-moire "$@" 5)'

html5/checkerboard.png: script-fu/create-checkerboard.scm
	script-fu/execute.sh "$<" '(create-checkerboard "$@")'
