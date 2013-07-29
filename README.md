QLT GenomeLaser
===============

QualityLaserTime Controller for the GenomeLaser project for Burning Man 2013.

Details here:
http://genomelaser.com/

This project is running on libcinder (http://libcinder.org/);


Licence
-------
The code in this repository is available under the
[Attribution-NonCommercial-ShareAlike 3.0 Unported](http://creativecommons.org/licenses/by-nc-sa/3.0/).  

2013 Vincent Rebers, [www.say-nono.com](http://www.say-nono.com)

Dependencies
-------

libcinder (http://libcinder.org/)
Cinder-Gwen (https://github.com/reakinator/Cinder-Gwen)
Cinder-Ilda (https://github.com/saynono/CinderIlda)


Setup
-------

1. create workspace for cinder
2. download cinder and copy the unzipped folder to the cinder workspace
3. download Cinder-Gwen and Cinder-Ilda and unpack it inside the cinder_x.x.x_mac/block - folder.
4. create second folder inside the cinder workspace called applications. this is the space where all user generated cinder stuff goes.
5. best to use GitHubs mac tool to clone "QLT GenomeLaser" to the application folder.
6. open QLT_GenomeLaser/xcode/QLT_GenomeLaser.xcodeproj
7. change the CINDER_PATH in build settings according to your folder structure (to something like ../../../../Cinder_0.8.5_mac)


Troubleshooting
-------
- xcode can't find Cinder-Gwen files: unfold Blocks in Navigator and click on Cinder-Gwen. Most likely it won't be linked correctly. So show the Utilities area and choose the right path in the Identity window (cinder_0.8.5_mac/blocks/Cinder-Gwen.
- xcode can't find Cinder-Ilda files: same here. Unfold Blocks in Navigator and click on Cinder-Ilda. Most likely it won't be linked correctly. So show the Utilities area and choose the right path in the Identity window (cinder_0.8.5_mac/blocks/Cinder-Ilda).



Notes
-------

Ha, still at the very beginning but wearing the running shoes... So if there are any problems setting up stuff file it on github.
