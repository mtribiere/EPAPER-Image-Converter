#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPixmap originalMap;
    bool imageHasLoaded = false;
    MainWindow(QWidget *parent = nullptr);
    void loadFile(QString filePath);
    void updatePreview();
    ~MainWindow();

private slots:
    void onClickedFileButton();
    void onThresholdChanged();
    void onConvertButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
