cmake_minimum_required(VERSION 3.15)
project(SegmentationPhotometrique)

set(CMAKE_CXX_STANDARD 14)

#find_package(GDAL REQUIRED)



find_package(OpenCV REQUIRED)
find_package(GDAL REQUIRED)

include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu/libshp.so)

#Affichage des messages

add_executable(SegmentationPhotometrique
        main.cpp
        Traitement.h Traitement.cpp SmallImage.cpp SmallImage.h)

message(STATUS "Statut de la bibliotheque OpenCV: ")
message (STATUS "config: $ {OpenCV_DIR} " )
message (STATUS "version: $ {OpenCV_VERSION} " )
message (STATUS "bibliothèques: $ {OpenCV_LIBS} " )
message (STATUS "chemin d'inclusion: $ {OpenCV_INCLUDE_DIRS} " )
include_directories(${OpenCV_INCLUDE_DIR})
include_directories(include ${GDAL_INCLUDE_DIRS})
#lien de la librairie OpenCV
target_link_libraries(SegmentationPhotometrique libshp.so ${OpenCV_LIBS} ${GDAL_LIBRARIES})

