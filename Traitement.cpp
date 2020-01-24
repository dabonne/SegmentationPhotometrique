#include <opencv2/core/mat.hpp>
//
// Created by liris on 30/10/2019.
//
#include "Traitement.h"
#include "SmallImage.h"
using namespace std;

///
/// \param imageTrans est l'image à transformer
/// \return nous rétournons le résultat de la transformation de l'image
void arrierePlanBlanc(Mat &imageTrans){

    for ( int i = 0; i < imageTrans.rows; i++ ) {
        for ( int j = 0; j < imageTrans.cols; j++ ) {
            if ( imageTrans.at<Vec3b>(i, j) == Vec3b(0,0,0) )
            {
                imageTrans.at<Vec3b>(i, j)[0] = 255;
                imageTrans.at<Vec3b>(i, j)[1] = 255;
                imageTrans.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    imwrite("./Image1background.png", imageTrans);
}
//!
//! \param img
//! \return
vector <vector <SmallImage> >imageCrop(Mat &img, Mat &real){
    //int colones(img.cols),lignes(img.rows);

    Mat imR;
    Mat imReal;
    resize(img, imR, Size(21568, 21632));
    resize(real, imReal, Size(21568, 21632));
    vector <SmallImage> tableImgR;
    vector <SmallImage> tableImgReal;
    const unsigned int height(128), width(128);
    for(int x(0); x+width <= imR.cols; x += width)
    {
        for(int y(0); y+height <= imR.rows; y += height)
        {
            Rect imgRect = Rect(x, y, width, height);
            if(0 <= imgRect.x && 0 <= imgRect.width && imgRect.x + imgRect.width < img.cols &&
               0 <= imgRect.y && 0 <= imgRect.height && imgRect.y + imgRect.height < img.rows)
            {

                Mat new_image = img(imgRect);
                Mat new_imageReal = real(imgRect);

                SmallImage small_image(new_image);
                SmallImage small_imageReal(new_imageReal);

                small_image.rect_from_bigimage = imgRect;
                small_imageReal.rect_from_bigimage = imgRect;

                tableImgR.push_back(small_image);
                tableImgReal.push_back(small_imageReal);
            }
        }
    }
    vector < vector<SmallImage> > vect_array;
    vect_array.push_back(tableImgR);
    vect_array.push_back(tableImgReal);
    return vect_array;
}

/*vector <SmallImage>*/ void patchClassification(vector <SmallImage> &tabImg, vector <SmallImage> &tabImgReal)
{
    SmallImage tmp;
    int des(1);
   while(des) {
        des = 0;// On suppose que le tableau est ordonné
        for (int i(0); i< tabImg.size()-1; i++) {
//            if (tabImg.at(i).SmallImage::getRatio() > tabImg.at(i+1).SmallImage::getRatio()) {
//                tmp = tabImg.at(i+1);
//                tabImg.at(i+1) = tabImg.at(i);
//                tabImg.at(i) = tmp;
//                // On constate qu'il ne l'est pas
//                des = 1;
//            }
            if (double (tabImg.at(i).SmallImage::getRatio()) == 0.0){
                int verif = 0;
                    for ( int r = 0; r < tabImgReal.at(i).SmallImage::getImage().rows; r++ ) {
                        for (int j = 0; j < tabImgReal.at(i).SmallImage::getImage().cols; j++) {
                            if (tabImgReal.at(i).SmallImage::getImage().at<Vec3b>(r, j) == Vec3b(0, 0, 0)) {

                            } else { verif = 1; }
                        }
                    }
                    //cout << verif <<endl;
                    if(verif == 1){
                        imwrite("./pasTraverseBack/img"+to_string(i)+".png",tabImg.at(i).SmallImage::getImage());
                        imwrite("./pasTraverse/img"+to_string(i)+".png",tabImgReal.at(i).SmallImage::getImage());
                }

            } else {
                int verifP = 0;
                for ( int r = 0; r < tabImgReal.at(i).SmallImage::getImage().rows; r++ ) {
                    for (int j = 0; j < tabImgReal.at(i).SmallImage::getImage().cols; j++) {
                        if (tabImgReal.at(i).SmallImage::getImage().at<Vec3b>(r, j) == Vec3b(0, 0, 0)) {

                        } else { verifP = 1; }
                    }
                }
                cout << verifP<<endl;
                if(verifP ==1){
                    imwrite("./traverseBack/img" + to_string(i) + ".png", tabImg.at(i).SmallImage::getImage());
                    imwrite("./traverse/img" + to_string(i) + ".png", tabImgReal.at(i).SmallImage::getImage());
                }
            }
        }

    }
    //return tabImg;
}

void WriteOnDisk(vector <SmallImage> &tableImag)
{
    for (int i(0); i < tableImag.size(); i++) {
        imwrite("./recopieDecoupageV1/img"+to_string(i)+".png",tableImag.at(i).SmallImage::getImage());
    }
}
//Reconstitution de l'Image
void imageReconstruction(vector <SmallImage> &tableImg, Mat &img){
    cv::Size output_size = Size(21568, 21632);

    Mat contours_reconstructed = Mat(output_size, CV_64F);
    Mat carte_chaleur = Mat(output_size, CV_64F);

    if(tableImg.empty())
        cout << "Pas de vecteur d'image";

    for(SmallImage element: tableImg)
    {
        // if elem.rect....
        // Reconstruction
        element.getImage().copyTo(contours_reconstructed(element.rect_from_bigimage));
        // Ratio to mat mapping
        cv::Mat ones(element.getImage().size(), CV_64FC1, Scalar(1));
        ones *= element.getRatio();
        ones.copyTo(carte_chaleur(element.rect_from_bigimage));
    }
    // Save contours
    imwrite("./carteCV1.png", contours_reconstructed);

    // Normalize carte_chaleur and save it
    cv::normalize(carte_chaleur, carte_chaleur, 255, 0, NORM_MINMAX);
    carte_chaleur.convertTo(carte_chaleur, CV_8UC1);
    imwrite("./carte_chaleurV1.png",carte_chaleur);

    // Apply color map on carte chaleur and save it
    Mat carte_chaleur_color = Mat(output_size, CV_8UC3);
    cv::applyColorMap (carte_chaleur, carte_chaleur_color ,  COLORMAP_HSV );
    imwrite("./carte_chaleur_colorhsvV1.png", carte_chaleur_color);

}

cv::Mat imagePreprocessing(Mat &image){
    if(image.empty())
    {
        std::cout << "Pas d'image disponible";
    }
    double thresh = 55;
    double maxValue = 255;
    cv::cvtColor(image, image, COLOR_BGR2GRAY);
    threshold(image, image, thresh, maxValue, THRESH_BINARY);
    return image;
}

vector <SmallImage>updateRatio(vector <SmallImage> &tableImages){
    if(tableImages.empty())
    {
        cout << "Aucune Image";
    }
    for(int i(0); i<tableImages.size()-1; i++)
    {
        tableImages.at(i).SmallImage::setRatio();
        cout <<tableImages.at(i).SmallImage::getRatio() << endl;
    }
    return tableImages;
}