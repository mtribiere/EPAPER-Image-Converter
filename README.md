# EPAPER Image Converter [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
A simple tool to convert an image from various format like <b> .png, .bmp, .jpg, .jpeg,... </b> to a <b>EPAPER monochrome display</b> format.
The format used here is from left to top to bottom from left, to right, and by grouping <b>8 bits</b>. It has been develloped in parrallel with the library ESP8266_EPAPER_lib : https://github.com/mtribiere/ESP8266-EPAPER-Lib

You can choose beetween to options : an <b>UI-based</b>, and an <b>CLI-based</b>.

| Version | Screenshoot |
| :--: | :--: |
| QT_UI | <img src="Pics/QT_UI_Screenshot.png" width="300"> |
| Pure_CPP | <img src="Pics/Pure_Cpp_Screenshot.png" width="300"> |

## QT_UI Version
  ### Compiling
  Simply import the Qt project from the "QT_UI" folder inside your install of Qt, and press RUN on the bottom left.

  ### Running
  Same as above or, 
  ```shell
  cd /your/repo/clone/QT_UI/bin
  ./Epaper_Converter
  ```
  
  <br>
  <br>
  
## Pure_cpp Version
  ### Compiling 
  ```shell
  sudo apt-get update
  sudo apt-get install libmagick++-dev
  cd /your/repo/clone/Pure_cpp
  c++ -o converter main.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs`
  ```
  ### Running
  ```shell
  sudo apt-get update
  sudo apt-get install imagemagick
  cd /your/repo/clone/Pure_cpp
  ./converter yourimage.png threshold
  ```

## Author
Made with ❤️ by mtribiere
