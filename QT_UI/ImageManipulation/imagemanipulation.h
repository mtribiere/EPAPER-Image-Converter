#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H

#include <string>
#include <QPainter>

class ImageManipulation
{
public:
    ImageManipulation();
    static QPixmap convertToPreview(QPixmap originalMap, int threshold);
    static QString convertToBinary(QPixmap originalMap, int threshold);
};

#endif // IMAGEMANIPULATION_H
