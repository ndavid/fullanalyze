# Features #

FullAnalyze is a software for visualizing and processing topographic lidar data. It handles point clouds and full-waveform data.


  * Images
    * Visualization of multiple georeferenced raster and vector data
  * Point clouds
    * 3D visualization of multiple point clouds
    * Textured visualization of any attribute (x, y, z, amplitude, ...) using colour lookup tables
    * Visualization of entire point cloud or of region of interest selected on any loaded ortho image; the ROI can be moved in real time so as to navigate closely in the 3D scene
    * Basic algorithms such as DSM computation
  * Full-waveform data
    * 1D visualization of raw waveform data (if the sensor geometry is raster compatible)
    * 3D visualization of ROI of georeferenced waveforms (using spheres or segments)
    * Echo extraction (should be available soon)

Other algorithms based on combinations of raster or vector data, point clouds and fullwave clouds can be developped and added as compile-time plugins.

# Design #

FullAnalyze is built on top of other open source projects:
  * [LidarFormat](http://code.google.com/p/lidarformat): a C++ library for handling point clouds with attributes
  * [GilViewer](http://code.google.com/p/gilviewer): a C++ 2D raster and vector viewer
and uses common open source C++ libraries:
  * [Boost C++ librairies](http://www.boost.org/)
  * [wxWidgets](http://www.wxwidgets.org/): multiplatform GUI library
  * [XSD CodeSynthesis](http://www.codesynthesis.com/products/xsd/) and Xerces for XSD schemas and XML
  * OpenGL for 3D display


# License #

FullAnalyze is released under the terms of the [LGPL (GNU Lesser General Public License)](http://www.gnu.org/licenses/gpl-3.0.html) license.


# Contributions #

FullAnalyze is a free software developped at the [MATIS laboratory](http://recherche.ign.fr/labos/matis/accueilMATIS.php),
[IGN](http://www.ign.fr/changeLangue.do?lang=en&cty=UK) (Institut Géographique National: the French National Mapping Agency), and at the [Maison de la Télédétection](http://www.teledetection.fr/accueil/2_en.html) (Remote Sensing Center in French), [CEMAGREF](http://www.cemagref.fr/English/).

FullAnalyze is also developped in the context of the [ISPRS WG III/2 on Point Cloud Processing](http://www.commission3.isprs.org/wg2/).

  * Author
    * Adrien Chauve
  * Contributors
    * Olivier Tournaire (GilViewer, Windows compilation)
    * Nicolas David (CMake, LidarFormat)



# Acknowledgements #

FullAnalyze was developed as a part of the [ExFOLIO project](http://tetis.teledetection.fr/index.php?option=com_content&task=view&id=56&Itemid=121) supported by the [CNES](http://www.cnes.fr/web/CNES-en/7114-home-cnes.php) (Centre National d’Etudes Spatiales, or French National Space Agency).
The authors deeply thank the [GIS Draix](http://www.ore.fr/rubrique.php3?id_rubrique=24) for providing the full-waveform demonstration lidar data and are grateful to [INSU](http://www.insu.cnrs.fr/) for its support to GIS Draix through the ORE program.