// This sets the CSS variable --bg-size so that the background images (512x512)
// are scaled to a size where each CSS pixel equals one physical pixel.
// For example, if Windows desktop has been scaled to 125%, and web browser zoom is 100%
// (making 1 CSS pixel = 1.25 physical pixel), then we scale the image to 409.6px.
// Has no effect in IE; it does not support CSS variables.

function ScaleToPhysicalPixels() {
	document.body.style.setProperty('--bg-size', (512 / window.devicePixelRatio) + 'px');
}
