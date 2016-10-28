// Call a callback function once all images with class 'preload' have loaded.
// Note: restricted to only a handful of images, due to the use of bit masks.

function preloader(callback) {
	var loading = 0;
	var get_handler = function(mask) {
		loading |= mask;
		return function() {
			if (loading != 0 && (loading &= ~mask) == 0) {
				callback();
			}
		};
	};
	var images = document.getElementsByTagName('img');
	for (var i = 0; i < images.length; i++) {
		var image = images[i];
		if (image.className == 'preload') {
			image.onload = get_handler(1 << i);
			image.src = image.alt;	// must set src AFTER onload
		}
	}
}

preloader(function() {
	document.body.className = 'plasma scroller';
});
