/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /*first set a canvas;second put each tile image as points in tree; third loop through the source and find nearest point(compare source pixel and tile pixel) last put the tile image on canvas in corresponding position*/
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    /*get each tile image's color convert to xyz and put in vector */
    vector<Point<3>> points;
    for (TileImage& t : theTiles) {
        points.push_back(convertToXYZ(t.getAverageColor()));
    }
    /*build a tile image tree*/
    KDTree<3> kdTree(points);
    /*loop through the source image's pixel and see if there is any pixel in tree close to the pixel and replace the pixel with the mosaic-tile image*/
    for (int r = 0; r < theSource.getRows(); ++r) {
        for (int c = 0; c < theSource.getColumns(); ++c) {
            LUVAPixel regC = theSource.getRegionColor(r, c);
            /*find the pixel's color with the closest color to the mosaic*/
            Point<3> nearest = kdTree.findNearestNeighbor(convertToXYZ(regC));
            // find the tile image by having its points
            TileImage* target;
            for (TileImage& t : theTiles) {
                if (convertToXYZ(t.getAverageColor()) == nearest) {
                    target = &t;
                }
            }
            // set it to the target image
            canvas->setTile(r, c, target);
        }
    }
    return canvas;
}

