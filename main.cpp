#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "Traitement.h"
#include "SmallImage.h"
#include "gdal/gdal.h"
#include "gdal.h"
#include "shapefil.h"
#include <shapefil.h>
using namespace cv;
using namespace std;
int main()
{




    SHPHandle  hSHP;
    //SHPObject *oSHP;
    vector<SHPObject *> shapeObjects;
    int pnEntities = 0;
    int pnShapetype = 0;
    double padfMinBound[4];
    double padfMaxBound[4];
    hSHP = SHPOpen("/home/lirisimagine/Documents/data/JANZE_MONTLOUIS/2_PLAN_TOPO/ExportPolylignes_lines.shp", "rb");
    SHPGetInfo(hSHP, &pnEntities, &pnShapetype, padfMinBound, padfMaxBound);

    for(int i(0); i<pnEntities; i++)
    {
        SHPObject* shapeObject = SHPReadObject(hSHP, i);
        shapeObjects.push_back(shapeObject);

    }
    cout << pnShapetype << endl;

    for(int i=0; i< shapeObjects.size(); i++){
        for(int j=0; j<shapeObjects[i]->nVertices; j++)
        {
            // Maintain multiple lists of points.  Each list contains
            // all of the points required for a single polygon.
            list<Point *> *points = new list<Point *>();
            int nVerticesPerPart = 0;

            // Determine which part (unique polygon) of the shape
            // these points belong to.
            if (j == shapeObjects[i]->nParts - 1) {
                int startOfPart = shapeObjects[i]->panPartStart[j];
                nVerticesPerPart = shapeObjects[i]->nVertices -
                                   shapeObjects[i]->panPartStart[j];
            } else {
                nVerticesPerPart = shapeObjects[i]->panPartStart[j + 1] -
                                   shapeObjects[i]->panPartStart[j];
            }

        }
        /*cout << "*****************" << i << "******************" << endl;
        cout << "nSHPType " << shapeObjects.at(i)->nSHPType << endl;
        cout << "nShapeID " << shapeObjects.at(i)->nShapeId << endl;
        cout << "nPart " << shapeObjects.at(i)->nParts << endl;
        cout << "panPartStart " << shapeObjects.at(i)->panPartStart << endl;
        cout << "panPartType " << shapeObjects.at(i)->panPartType << endl;
        cout << "nVertices " << shapeObjects.at(i)->nVertices << endl;
        cout << "padfX " << shapeObjects.at(i)->padfX << endl;
        cout << "padfY " << shapeObjects.at(i)->padfY << endl;
        cout << "padfZ " << shapeObjects.at(i)->padfZ << endl;
        cout << "padfM " << shapeObjects.at(i)->padfM << endl;
        cout << "dfXMin " << shapeObjects.at(i)->dfXMin << endl;
        cout << "dfXMax " << shapeObjects.at(i)->dfXMax << endl;
        cout << "dfYMin " << shapeObjects.at(i)->dfYMin << endl;
        cout << "dfYMax " << shapeObjects.at(i)->dfYMax << endl;
        cout << "dfZMin " << shapeObjects.at(i)->dfZMin << endl;
        cout << "dfZMax " << shapeObjects.at(i)->dfZMax << endl;
        cout << "dfMMin " << shapeObjects.at(i)->dfMMin << endl;
        cout << "dfMMax " << shapeObjects.at(i)->dfMMax << endl;*/
    }





   /* cv::Mat input_background;
    cv::Mat input_real;
    input_background = cv::imread("./background.png");
    input_real = cv::imread("./horto.png");

    Mat transfor = imagePreprocessing(input_background);
    vector <vector<SmallImage> > tableImages;
    tableImages = imageCrop(transfor, input_real);
    vector <SmallImage> ratioUpdate;
    //ratioUpdate = updateRatio(tableImages);
    for(int i(0); i<tableImages.at(0).size()-1; i++)
    {
        tableImages.at(0).at(i).SmallImage::setRatio();
    }
    vector <SmallImage> classe;
   patchClassification(tableImages.at(0), tableImages.at(1));
    //WriteOnDisk(classe);
    //imageReconstruction(tableImages, input);*/

    return 0;
}