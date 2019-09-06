var preloader = new Preloader(function() {
	document.body.className = 'plasma scroller';
});
preloader.add_all_images();	// preload images (async)
WebFont.load({google: {families: ['Orbitron:700']}});	// preload font (sync)
preloader.done();

ScaleToPhysicalPixels();
window.onresize = ScaleToPhysicalPixels;	// making use of the fact that changing zoom fires resize event
