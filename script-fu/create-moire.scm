(define (create-moire name seed back)
	(let*
		(
			(image (car (gimp-image-new 4096 4096 RGB)))
			(main (car (gimp-layer-new image 4096 4096 RGBA-IMAGE "Main" 100 NORMAL-MODE)))
			(noise (car (gimp-layer-new image 4096 4096 RGB-IMAGE "Noise" 100 NORMAL-MODE)))
		)
		(gimp-image-insert-layer image main 0 0)
		(gimp-image-insert-layer image noise 0 1)
		(gimp-context-set-foreground '(0 0 0))
		(gimp-edit-blend main FG-TRANSPARENT-MODE NORMAL-MODE GRADIENT-LINEAR 100 0 REPEAT-TRIANGULAR FALSE FALSE 1 0 FALSE 0 0 4 4)
		(plug-in-solid-noise RUN-NONINTERACTIVE image noise TRUE FALSE seed 1 4 4)
		(plug-in-displace RUN-NONINTERACTIVE image main 12 12 1 1 noise noise 1)
		(gimp-image-remove-layer image noise)
		(gimp-context-set-interpolation INTERPOLATION-CUBIC)
		(gimp-image-scale image 512 512)

		(when back
			(let*
				(
					(checkerboard (car (gimp-layer-new image 512 512 RGB-IMAGE "Checkerboard" 100 NORMAL-MODE)))
				)
				(gimp-image-insert-layer image checkerboard 0 1)
				(gimp-context-set-foreground '(0 255 0))
				(gimp-context-set-background '(255 0 0))
				(plug-in-checkerboard RUN-NONINTERACTIVE image checkerboard 0 1)
				(set! main (car (gimp-image-merge-visible-layers image EXPAND-AS-NECESSARY)))
			)
		)

		(file-png-save RUN-NONINTERACTIVE image main name name 0 9 0 0 0 1 1)
		(gimp-image-delete image)
	)
)
