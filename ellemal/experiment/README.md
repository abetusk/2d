Experiments
===

For `14511091578_2cec34514c_o.jpg`, taken from [Cielos del Campo by Emilio Kuffer](https://www.flickr.com/photos/emiliokuffer/14511091578/) (CC-BY-SA),
[Evil Mad Scientist's blog entry about sippling images was followed](https://wiki.evilmadscientist.com/Producing_a_stippled_image_with_Gimp):

* Image converted to grayscale (or desaturated)
* Levels (I used 'auto')
* `Image -> Mode -> Indexex` and `1-bit palette` was selected
* Exported to `.png` and loaded into [LaserWeb](https://github.com/LaserWeb/LaserWeb4)
* Resize to be `210mm` wide
* Deselect `Burn White` and select `Invert Color`
* Choose cut speed of `4999` and leave at full power
* Generate and save GCode
* Use `cleanup.sh` script from the tarot directory to remove comments and recenter
