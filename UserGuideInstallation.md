If you want to debug, contribute to or extend FullAnalyze, you should download the sources and compile it by yourself. The python setup script will help you (see the HowToFullAnalyzeSetupScript for more details).
Otherwise, just download the binaries (available only for Linux).

# Download the binaries #

Download the binaries for Linux: [32bits](http://fullanalyze.googlecode.com/files/FullAnalyze-0.1.1_x86.tar.bz2) or [64bits](http://fullanalyze.googlecode.com/files/FullAnalyze-0.1.1_x86-64.tar.bz2).

Decompress the archive and run:

```
sh fullanalyze.sh
```


# Demonstration data #

Full-waveform lidar demo data are available [here](http://fullanalyze.googlecode.com/files/fullwave-lidar-demo-data.tar.bz2). This archive contains 2 pieces of lidar strips acquired with the RIEGL LMS-Q560 airborne lidar system over Le Brusquet, France. These data were kindly provided by the GIS Draix.

Point cloud demonstration data are also available [here](http://fullanalyze.googlecode.com/files/point-cloud-lidar-demo-data.tar.bz2). This archive contains 2 pieces of point clouds belonging to 2 lidar strips. They were extracted from the full-waveform demonstration data using the very basic maximum peak detection. The point clouds were not registered.