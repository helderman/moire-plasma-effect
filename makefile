all: html5/moire1.png html5/moire2.png

html5/moire1.png: script-fu/create-moire.scm
	script-fu/execute.sh "$<" '(create-moire "$@" 1 #f)'

html5/moire2.png: script-fu/create-moire.scm
	script-fu/execute.sh "$<" '(create-moire "$@" 5 #t)'
