/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> node_points;
    map<Point<3>, TileImage*> conversion;
    for (auto it = theTiles.begin(); it != theTiles.end(); ++it) {
        Point<3> AvColPoint = convertToXYZ(it->getAverageColor());
        conversion[AvColPoint] = &(*it);
        node_points.push_back(AvColPoint);
    } 
    KDTree<3> kdtree(node_points);
    for (int i = 0; i < canvas->getRows(); ++i) {
        for (int j = 0; j < canvas->getColumns(); ++j) {
            Point<3> AvColRegion = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> nearestColor = kdtree.findNearestNeighbor(AvColRegion);
            canvas->setTile(i, j, conversion[nearestColor]);
        }
    }
    return canvas;
}

