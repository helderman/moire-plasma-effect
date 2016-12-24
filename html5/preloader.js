// This calls a callback function once all registered resources have loaded.
// Usage:
// - Instantiate the class; pass the callback function to the constructor.
// - Call method add_image to register an image. The image must have its URL
//   in attribute alt, not src, to ensure its load event will be detected.
// - Alternatively, call method add_all_images;
//   it automatically picks up every image with class 'preload'.
// - Call any synchronous preloaders you need.
// - Call method done; the callback will not be called until you do this.
// Bugs:
// - Supports only a limited amount of resources due to the use of bit masks.

var Preloader = function(callback) {
	this.callback = callback;
	this.loading = this.mask = 1;
};

Preloader.prototype.add_all_images = function() {
	var images = document.getElementsByTagName('img');
	for (var i = 0; i < images.length; i++) {
		var image = images[i];
		if (image.className == 'preload') {
			this.add_image(image);
		}
	}
};

Preloader.prototype.add_image = function(image) {
	image.onload = this.get_next_event_handler();
	image.src = image.alt;
};

Preloader.prototype.done = function() {
	Preloader.create_event_handler(this, 1)();
};

Preloader.prototype.get_next_event_handler = function() {
	this.loading |= this.mask <<= 1;
	return Preloader.create_event_handler(this, this.mask);
};

Preloader.create_event_handler = function(state, mask) {
	return function() {
		// The first resource to make 'loading' zero (typically the
		// last one to fire its load event) gets to do the callback.
		if (state.loading != 0 && (state.loading &= ~mask) == 0) {
			state.callback();
		}
	};
};
