# Download the data #
Download the demonstration data and extract them in 2 separated folders: one for the fullwave data and one for the point cloud data.


# Launch the GUI #
Here is a snapshot of the window you get when you launch FullAnalyze for the first time.

![http://wiki.fullanalyze.googlecode.com/hg/images/UserGuide/gui_start.png](http://wiki.fullanalyze.googlecode.com/hg/images/UserGuide/gui_start.png)

# Set up the directories #

First, use the 2 directory picker controls to choose the folders were you extracted the demonstration data. Lidar files that were found in these directories are listed in the panel below the directory picker controls and categorized as "Lidar files" or "Fullwave files".
You can also use the "Image" directory picker control to set up a new folder. It will contain any image that you generate using the implemented algorithms (e.g. DSM). You can also put there a DTM or any orthophoto you have.

# Let's play! #

You are now ready to display the data and launch some basic algorithms. Just right click on the files and choose the action you want to execute.

  * Image actions:
    * "Display": displays the selected raster in the ortho (cartographic) view (only pairs of TIF and TFW files can be displayed).
    * "Shading": computes a shaded image of the selected raster. Default parameters are applied. Parameter tuning should be available soon through the GUI.
  * Lidar actions:
    * "Display point cloud in 3D": choose this to display the point cloud in a 3D view, opening a new panel. You can visualise several point clouds at a time. Click on the first icon in the 3D toolbar to display the "Cloud control" window: you can make a point cloud visible or invisible, and change the display settings (unique color, color based on any attribute using a LUT, RGB color, etc...).
    * "Compute basic MNS": computes a basic DSM at the resolution you choose. This implementation takes the maximum in each cell and computes the corresponding image. An adaptative DSM will be available soon.
    * "Compute point density image": generates an image of point density at the chosen resolution.
    * "Save as binary" and "Save as ASCII" let you convert your file from BINARY to ASCII and vice versa.
    * "Center point cloud (auto and custom)": typical point clouds are used with x,y coordinates in a given projection. Most of the time, single float precision is not sufficient and double precision is needed to avoid erroneous rounding. However, FullAnalyze can also display single float point clouds so they first need to be centered: a transformation is computed and stored in the XML file, and the point cloud is converted to single float precision in a new file with a "-centered" suffix. In the auto mode, the transformation is automatically computed; it is well suited for only one point cloud. If you have several point clouds on a survey, you must enter manually the transformation so as to be sure that the same transformation is used for each point cloud.
  * Full-waveform actions:
    * "Display waveforms in 3D": displays the selected fullwave file as a 3D scene in the 3D view. By default and so as to be fast, waveforms are displayed as 3D segments. More options are available through the "Cloud control" window. To display it, clik on the "Show cloud control" button of the 3D toolbar.
    * "Display waveforms as 1D signals": this action first computes a total backscattered image in the sensor geometry and displays it in a new sensor view. 1D waveforms are displayed in the plot view as you move the selection point of the sensor view (use the "Move point" button of the sensor toolbar to draw and move a selection point). The sensor image makes it easy to select the waveform you want to look at.
    * "Correct intensity from laser fluctuations": corrects the full-waveform data from the fluctuations of the laser transmitted power (you just need to enter a reference intensity). These fluctuations have proven to be really important on the demonstration data set.
    * "Center waveforms": this does the same as for point clouds. Demonstration data are already centered.
    * "Display strip on ortho view": if you have already displayed a raster in the ortho view, this action superimposes the enveloppe of the strip.