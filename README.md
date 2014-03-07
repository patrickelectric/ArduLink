ArduLink
=============

A library to arduino comunication with Simulink.

Tutorial
-------

1. Call init function on the setup().
2. Make sure that all modifications in:
  * Terminator.
  * Header.
  * Baudrate.
  * Vector's size.
  * Vector's format (int32 or single)
  Need to be modified in Simulink !
3. The Terminator must be in double quotes (`"\0","\n","\r\n" and...`).
4. The Header must be in single quotes (`'L','U','P' and...`)


Contributing
------------

1. Fork it.
2. Create a branch (`git checkout -b my_markup`)
3. Commit your changes (`git commit -am "Added something very cool"`)
4. Push to the branch (`git push origin my_markup`)
5. Open a [Pull Request][1]
6. Enjoy a good book and wait

[1]: https://github.com/patrickelectric/ArduLink/pulls

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/patrickelectric/ardulink/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

