#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ImageManipulation/imagemanipulation.h"
#include <QPixmap>
#include <QPainter>
#include <string>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QMessageBox>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   //ui->originalPicture->setScaledContents(true);
   //ui->previewPicture->setScaledContents(true);

    connect(ui->fileChooseButton, &QPushButton::clicked,
            this, &MainWindow::onClickedFileButton);
    connect(ui->thresholdSlider, &QSlider::valueChanged,
            this, &MainWindow::onThresholdChanged);
    connect(ui->convertButton, &QPushButton::clicked,
            this, &MainWindow::onConvertButtonClicked);

}

void MainWindow::loadFile(QString filePath){

    try{
        //Load the original picture
        QPixmap originalMap(filePath);

        //Display the original picture
        ui->originalPicture->setPixmap(originalMap.scaled(ui->originalPicture->size().width(),
                                                          ui->originalPicture->size().height(),
                                                          Qt::KeepAspectRatio));

        //Set the map as the current one
        this->originalMap = originalMap;

        //Update the preview
        this->updatePreview();

        this->imageHasLoaded = true;
    }catch(const std::exception& e){

    }

}

void MainWindow::updatePreview(){

    //Create the preview
    QPixmap previewMap = ImageManipulation::convertToPreview(this->originalMap,ui->thresholdSlider->value());

    //Display the preview
    ui->previewPicture->setPixmap(previewMap.scaled(ui->previewPicture->size().width(),
                                                    ui->previewPicture->size().height(),
                                                    Qt::KeepAspectRatio));
}

void MainWindow::onClickedFileButton(){
  this->loadFile(QFileDialog::getOpenFileName(this,
                                              tr("Open Image"),
                                              "~",
                                              tr("Image Files (*.png *.jpg *.bmp)")));
}

void MainWindow::onThresholdChanged(){
    if(this->imageHasLoaded)
        updatePreview();
}

void MainWindow::onConvertButtonClicked(){
    QDialog * dialog = new QDialog(this);
    dialog->setWindowTitle("Result");

    QPlainTextEdit *scroll = new QPlainTextEdit(ImageManipulation::convertToBinary(this->originalMap,ui->thresholdSlider->value()),dialog);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Add a layout for QDialog
    QHBoxLayout *dialog_layout = new QHBoxLayout(dialog);
    dialog->setLayout(dialog_layout);
    dialog->layout()->addWidget(scroll); // add scroll to the QDialog's layout
    dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

