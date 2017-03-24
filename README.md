# FastQt 

![travis](https://api.travis-ci.org/labsquare/fastQt.svg?branch=master) [![Gitter](https://badges.gitter.im/labsquare/fastQt.svg)](https://gitter.im/labsquare/fastQt?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge) [![Build status](https://ci.appveyor.com/api/projects/status/skmgugijflggfq4x?svg=true)](https://ci.appveyor.com/project/dridk/fastqt)      
FastQt is the clone of [FastQC](http://www.bioinformatics.babraham.ac.uk/projects/fastqc/) application ported 
from Java to [C++/Qt5](https://www.qt.io/) 

![Preview](https://raw.githubusercontent.com/labsquare/fastQt/master/screenshot.gif)

## Installation 

### Linux 
An [AppImage](http://appimage.org/) has been created and should work on recent Linux distribution.     
Download the last release from [here](https://github.com/labsquare/fastQt/releases/) and run it as follow : 

    chmod +x fastqt-0.2.3-linux-x86_64.AppImage
    ./fastqt-0.2.3-linux-x86_64.AppImage
    
### Archlinux
There is an AUR package for Archlinux. [Just get it from the AUR](https://aur.archlinux.org/packages/fastqt/).
 
### Windows 
Windows installer and portable version are avaible [here]( https://github.com/labsquare/fastQt/releases/)
        
## Compilation 
### Prerequisites - Install KArchive
On Linux, you need to install karchive before compiling FastQt.    
**From ubuntu** >xenial you can install it from repositories : 
 
     sudo apt install libkf5archive-dev

**From fedora** >= 24 you can install it from repositories :

    sudo dnf install kf5-karchive-devel

**From source** : 

    git clone git://anongit.kde.org/extra-cmake-modules
    cd extra-cmake-modules
    mkdir build && cd build    
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr/
    make && sudo make install
    cd ../..
    git clone git://anongit.kde.org/karchive.git
    cd karchive
    mkdir build && cd build 
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr/
    make 
    sudo make install
    
** From Windows **    
Nothing to do. Compiled library are avaible in win32 directory.  

### Install Qt >5.7

**From website** : Download Qt > 5.7 from https://www.qt.io/.   
Don't forget to check QtChart module during installation. 

**From ubuntu** : Qt 5.7 is not yet avaible with ubuntu. But you can add PPA to your software system. 
For exemple from xenial 

    sudo add-apt-repository ppa:beineri/opt-qt57-xenial
    sudo apt-get install qt57base qt57charts-no-lgpl
    source /opt/qt57/bin/qt57-env.sh

**From fedora** : Qt 5.7 is avaible

    sudo dnf install qt5-qtbase-devel qt5-qtcharts-devel 

### Compile FastQt 
Be sure you have the correct version of Qt (>5.7) by using qmake --version. For exemple, if you have installed Qt from ppa:beineri, you will find it under /opt/qt57/bin/qmake. Then launch the compilation from FastQC folder as follow.

     /opt/qt57/bin/qmake --version
     /opt/qt57/bin/qmake 
     make 
     sudo make install 

## Usage

FastQt can analyse uncompress and compress fastq files. The following extensions are supported :

- *.fastq
- *.fastq.gz
- *.fastq.xz
- *.fastq.bz2

You can use FastQt as GUI application or as a Command Line Interface.

Some usage example :

```
fastqt file1.fastq # File is save in file1 directory
fastqt file1.fastq file2.fastq.gz file3.fastq.bzip # File save in file1 file 2 file3 directory
fastqt file1.fastq -o specific_path # Create specific directory for each file in specific_path
fastqt file1.fastq -t 2 # Fastqt run maximal two process this option is valid for GUI too
```
