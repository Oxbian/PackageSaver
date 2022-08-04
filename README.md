# Package Saver
-------------

![Release](https://img.shields.io/badge/Release-v1.0-brightgreen?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-Bash-blue?style=for-the-badge)
![Size](https://img.shields.io/github/repo-size/ARKAGEDON/PackageSaver?label=SIZE&style=for-the-badge)
![Licence](https://img.shields.io/github/license/ARKAGEDON/PackageSaver?style=for-the-badge)
![OpenSource](https://img.shields.io/badge/OpenSource-blue?style=for-the-badge&logo=opencollective&logoColor=white)

## Package Saver what is it ?

It's a tools to save the package you want to keep for your reinstallation. They are all in a txt file, just need paste them after your reinstallation to have it back

## What is automated ?

Currently the only automed thing is the detection and the parsing of your package manager (for the moment only pacman and apk are parsed and working). Later I will work on a GUI and a way to just use this programs to reinstall package from a list of packages.

## How to use it ?

1) Make sure you have the correct permission to use it

> chmod 777 packageManager.sh

2) Just run it and say yes or no if you want to keep this package (by default it's no so just need to write Y or y if you want to keep it)

> ./packageManager.sh

## How to contribute ?  
  
Everyone is free to contribute, just clone the project, make your modification and make a pull request with an explanaition of your changes

## Licence:  
This project is under the GNU GPL v3.0 licence, basically you are free to copy this project, modify it