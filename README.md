# BlinkenHat

This is a project to enable people with limited knowledge in electronics or programming to build fancy flashing LED accessiors.

The documentation can be found at [blinkenhat.org](https://blinkenhat.org).

## Contributing

If you want to contribute: Great, Thank you!

Contributions can have many faces.
If you just found a Bug or a Glitch in the documentation and want to report it: use the [issue tracker](https://github.com/Retardigrades/blinkenhat/issues) of this project and preport your finding.
We will do our best to help you.

If you want to give feedback and ideas, then also the [issue tracker](https://github.com/Retardigrades/blinkenhat/issues) is the place to put it.
We will discuss it there and see if and how its possible.

To actually contribute code, fix bugs or improve the documentation, you can fork the repositioy, make your changes and provide a PullRequest back.
We try to review and merge all contributions as soon as possible.
To keep things readable, please format all your code according to the LLVM code style.
The easiest way to achieve this is to use the [clang-format](https://clang.llvm.org/docs/ClangFormat.html) tool.
Just run it over your code before you commit:
```
$ clang-format -style=LLVM -i <filename>
```

## Releases

### [v0.6: Burning Bär release](https://github.com/Retardigrades/blinkenhat/releases/tag/v0.6)

The first big improvement of the software gives you a clearer user Interface, the possibility to change effects and a new twinklng star effect.

Mayor changes:
* The userinterface is now more descriptive what the settings mean.
* The AppBar with the save button is now always visible
* Effects can now be removed
* Effects can now be added
* Effects can operate on a channel as one whole strip without dividing it
* New effect: twinkling stars
* The number of LEDs can now be set from 2 to 100
* Documentation is growing (published at [blinkenhat.org](https://blinkenhat.org))
* The visibility of the dot effect works now with other values than 100%


### [v0.5: First public release](https://github.com/Retardigrades/blinkenhat/releases/tag/v0.5)

This is basically the release that was distributed with the first version of the workshop.
