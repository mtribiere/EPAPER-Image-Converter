#include "imagemanipulation.h"
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <sstream>

ImageManipulation::ImageManipulation()
{

}

QPixmap ImageManipulation::convertToPreview(QPixmap originalMap, int threshold){

    //Get the pixel data
    QImage image (originalMap.toImage());


    // Create the preview map
    int w = originalMap.width();
    int h = originalMap.height();
    //std::cout << w << "," << h << std::endl;

    QPixmap previewMap(w,h);
    QPainter painter(&previewMap);



    //Set draw color to white
    painter.setPen(QColor(255,255,255));

    for(int i = 0;i< h;i++)
        for(int j = 0;j<w;j++)
            painter.drawPoint(j,i);

    //Set draw color to black
    painter.setPen(QColor(0,0,0));

    //Fill the preview map
    for(int i = 0;i< h;i++){
        for(int j = 0;j<w;j++){

            //Get the color
            QColor color(image.pixel(j, i));

            if((color.red()+color.blue()+color.green())/3 > threshold)
                painter.drawPoint(j,i);


        }
    }

    painter.end();

    return previewMap;
}

QString ImageManipulation::convertToBinary(QPixmap originalMap, int threshold){

    std::string toReturn = "";

    //Get the pixel data
    QImage image (originalMap.toImage());


    // Create the preview map
    int w = originalMap.width();
    int h = originalMap.height();

    //////////Convert to bytes
    unsigned char currentByte = 0x00;
    int currentByteCompletion = 0;

    for(int i = 0;i<h;i++){
        for(int j = 0;j<w;j++){

            //Get pixel color
            QColor color(image.pixel(j, i));

            //If color average higher than threshold
            if((color.red()+color.blue()+color.green())/3 > threshold){
                currentByte = ((currentByte << 1) | 0x01);
            }else{
                currentByte = ((currentByte << 1) & 0xFE);
            }

            currentByteCompletion++;

            //If an entire byte is filled
            if(currentByteCompletion == 8){


                //Print it and start a new one
                std::stringstream ss;
                ss << "0x" << std::hex  << (unsigned int)currentByte <<", ";
                toReturn += ss.str();

                currentByte = 0;
                currentByteCompletion = 0;

            }
        }

        //If the byte is not completed
        if(currentByteCompletion < 8 && currentByteCompletion != 0){
            //Fill it
            currentByte = currentByte << (8-currentByteCompletion);

            //Print it and start a new one
            std::stringstream ss;
            ss << "0x" << std::hex  << (unsigned int)currentByte <<", ";
            toReturn += ss.str();

            currentByte = 0;
            currentByteCompletion = 0;
        }
        toReturn += "\n";
    }




    return QString::fromStdString(toReturn);
}


