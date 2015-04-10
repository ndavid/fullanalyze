# Point clouds file formats #

FullAnalyze reads and writes ASCII and binary files, and should soon read LAS files using [libLas](http://liblas.org).

Point cloud data in ASCII or binary format must be described in an XML file.

## ASCII ##

For now, ASCII files must have no header and fields must be separated by spaces or tabulations.

For instance, imagine you already have an ASCII lidar data file named "lidar\_data.xyz" that contains 5M points (the extension can be whatever you like, for instance .txt or .asc). Each point of your data has x,y,z coordinates in a given projection and intensity encoded as an integer. Then, you should create an XML file named "lidar\_data.xml" which contains:

```
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<LidarData xmlns="cs" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <Attributes DataFileName="lidar_data.xyz" DataFormat="ascii" DataSize="5000000">
    <Attribute DataType="float64" Name="x"/>
    <Attribute DataType="float64" Name="y"/>
    <Attribute DataType="float64" Name="z"/>
    <Attribute DataType="int32" Name="intensity"/>
  </Attributes>
</LidarData>
```

Now, copy your data file and your xml file in your FullAnalyze lidar data directory, and run FullAnalyze! Your files should now be listed in the lidar files list.

_**Warning**_: before you visualize your data, be sure to center the data using the right click popup menu on your file (and click on "Center point cloud (auto)"). This will create a centered copy of your file and save it in a binary format to be more efficient. Once centered, the data can be visualized and used for any processing.

## Binary ##
To do!