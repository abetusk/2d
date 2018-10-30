Bat Patch
===

Using GIMP, these are some important steps:

* Carve out the relevant section of [Haeckel's original plate](https://en.wikipedia.org/wiki/Bat#/media/File:Haeckel_Chiroptera.jpg)
* Create a new workspace with the original picture as it's own layer
* Apply a "Neon" edge-detect filter (radius `1.0` and `0.80` amount maybe?)
* Create a black 'frame' for the image on it's own layer underneath the edge-detected layer.
  I created a simple frame for the `0.1.x` versions (meant to look like stylized 'vector' clouds) by
  creating large difference sizes of hard-edged circle pencil strokes with long linear sections that cover the entirety
  of the (now filtered) bat.
* Duplicate the outline layer and invert the color to white. Erode multiple times (5-10) to get a good white outline.
  Too small and the rastered laser image won't cut all the way through.
* Put it all in a group in the proper z-order and export to a PNG.

Once exported open it with `laserweb`:

* Import the PNG
* Reposition and resize as appropriate. For my purposes, I resized to about 235mm width to try and fit to an A6 EL panel.
* Drag the imported file to the appropriate section for GCode conversion
* Set the feed rate to 3000
* Select the 'invert' option and unset the 'burn white' option
* Generate the GCode and save it.

The output is in a DOS format (carriage return and line feed after every line) so I clen it up by running `dos2unix`.
I also remove the comments (`s/;.*//`) in addition to adding a `G0 F5000` at the top to make the rapid motion faster.


License
---

Everything in this directory, unless explicitely stated otherwise, is under a CC0 license.
