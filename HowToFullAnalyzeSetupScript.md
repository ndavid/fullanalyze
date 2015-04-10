_version 1.2_

# Introduction #

FullAnalyzeSetup.py is a script dedicated to automate the build of FullAnalyze on Linux platforms. Running this script can:
  * download the sources of the 3 projects ([LidarFormat](http://code.google.com/p/lidarformat), [GilViewer](http://code.google.com/p/gilviewer) and FullAnalyze)
  * build the sources and run available tests
  * patch your installation of Boost so as to support float images
and additionally if your Linux distribution is Ubuntu Jaunty, it also can:
  * install the dependencies (Boost, wxWidgets, ...).

If your distribution is Jaunty, go [here](HowToFullAnalyzeSetupScript#Running_the_script_on_Ubuntu_Jaunty.md)!

If you are on another version of Ubuntu, or of any Debian-based distribution, the script may not be able to install the dependencies, but you can test and give us some feedback.

If you are running another flavour of Linux, the script won't be able to install the dependencies, so go [there](HowToFullAnalyzeSetupScript#Running_the_script_on_another_Linux_distribution.md)!


# Running the script on Ubuntu Jaunty #

Download the script [FullAnalyzeSetup-1.2.py.tar.gz](http://fullanalyze.googlecode.com/files/FullAnalyzeSetup-1.2.py.tar.gz), decompress the archive and type in a terminal (where you want the sources to be downloaded):

```
python FullAnalyzeSetup.py -dib
```


At the end of the operation, you should have a working FullAnalyze located in `"./FullAnalyze/trunk"`.

For more details on the options, go [there](HowToFullAnalyzeSetupScript#Details.md)!

# Running the script on another Linux distribution #

Before running the script, you must manually install the following dependencies using your package manager:
  * g++ (and the common tools to compile c++ programs)
  * mercurial
  * cmake
  * Boost librairies (>=1.36)
  * Xerces
  * Code Synthesis XSD (can be downloaded [here](http://codesynthesis.com/products/xsd/download.xhtml))
  * wxWidgets
  * libjpeg, libtiff and libpng
  * an OpenGL implementation (libglu)

Then, just type the same as for Jaunty but without the '-d' option:

```
python FullAnalyzeSetup.py -ib
```


# Details #

Main options of the script are :

  * d: install dependancies (only for Ubuntu Jaunty)
  * i: init the directories (only the first time you run the script)
  * u: update the sources by downloading the changes (this has to be done when you want to get the latest version of FullAnalyze)
  * b: build the program
  * j: use multiple processors or cores to compile (e.g. : you can use "-j3" when you have a dual core)
  * c: clean CMake cache (to do if the compilation returns errors)