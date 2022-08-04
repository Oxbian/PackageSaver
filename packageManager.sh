#!/bin/bash

echo -e "

  ██████╗ ██╗  ██╗ ██████╗ ███████╗ █████╗ ██╗   ██╗███████╗██████╗ 
  ██╔══██╗██║ ██╔╝██╔════╝ ██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗
  ██████╔╝█████╔╝ ██║  ███╗███████╗███████║██║   ██║█████╗  ██████╔╝
  ██╔═══╝ ██╔═██╗ ██║   ██║╚════██║██╔══██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
  ██║     ██║  ██╗╚██████╔╝███████║██║  ██║ ╚████╔╝ ███████╗██║  ██║
  ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝

"

echo -e " Welcome to the Package Saver\n It will allow you to have a list of package to reinstall to your new OS setup\n"


# Checking the package Manager
case "$(command -v apk apt-get dkpg dnf zypper pacman rpm snap flatpak)" in

# If the Package Manager is apk
*apk*) pkgCount=$(apk info | wc -l)
  pkgManager="apk"
  ;;

# If the Package Manager is apt
*apt-get*) pkgCount=$(apt list --installed | wc -l)
  pkgMan="apt"
  ;;

# If the Package Manager is dkpg
*dkpg*) pkgCount=$(dpkg -l | wc -l)
  pkgMan="dpkg"
  ;;

# If the Package Manager is dnf
*dnf*) pkgCount=$(dnf list installed | wc -l)
  pkgMan="dnf"
  ;;

# If the Package Manager is zypper
*zypper*) pkgCount=$(zypper se --installed-only | wc -l)
  pkgMan="zypper"
  ;;

# If the Package Manager is pacman
*pacman*) pkgCount=$(pacman -Q | wc -l)
  pkgMan="pacman"
  ;;

# If the Package Manager is rpm
*rpm*) pkgCount=$(rpm -qa | wc -l)
  pkgMan="rpm"
  ;;

# If the Package Manager is snap
*snap*) pkgCount=$(snap list | wc -l)
  pkgMan="snap"
  ;;

# If the Package Manager is flatpak
*flatpak*) pkgCount=$(flatpak list --app | wc -l)
  pkgMan="flatpak"
  
  ;;

*) echo "FAILED TO FOUND PACKAGES: Package manager not found. You must install one of the basics package manager"

  ;;

esac

echo -e "NUMBER OF PACKAGES: $pkgCount\nPackage Manager: $pkgMan\n"

# Asking if you want to keep this package and adding it to the file
for (( pkgI=1; pkgI<=pkgCount; pkgI++ ))
do

  #Parse the package name, different for each package manager
  case "$pkgMan" in
    #Apk is the package manager
    apk) currPkg=$(apk info | sed -n "${pkgI}p")
    ;;

    #Pacman is the package manager
    pacman) currPkg=$(pacman -Q | sed -n "${pkgI}p" | cut -d" " -f1)
    ;;

  esac

  read -p "Do you want to keep $currPkg? [y/N] " input
  #If we input y or Y
  if [ ${#input} -gt 0 ] && [ ${input,,} == "y" ];
  then
    printf "%s " $currPkg >> "packageToKeep.txt"
    echo "[V] Added" #DEBUG
  else
    echo "[X] Not added" #DEBUG
  fi
done