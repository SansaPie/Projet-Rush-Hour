file(GLOB Fichiers_Config . *[0-9].txt)
file(INSTALL ${Fichiers_Config}  DESTINATION .)