#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QLabel>
#include <QSizePolicy>
#include <QScreen>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

//blur
QImage blurImage(QImage source, int deep) {
    if (source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));
    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(deep);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result (source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(0, 0, source.width(), source.height()));
    return result;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLabel label (&w);

    QPushButton open ("open", &w);
    QPushButton save("save", &w);
    QSlider slider(&w);
    slider.setMinimum(0);
    slider.setMaximum(10);
    slider.setOrientation(Qt::Horizontal);
//    QDesktopWidget *desc = QApplication::desktop();
    label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    label.setText("Hello, wassssap?");

    QVBoxLayout vbox(&w);
    QHBoxLayout hbox;

    vbox.addWidget(&label);
    vbox.addWidget(&slider);
    hbox.addWidget(&open);
    hbox.addWidget(&save);
    vbox.addLayout(&hbox);


    QImage image("filePath");
    QString filePath;
    QObject::connect(&open, &QPushButton::clicked,[&label, &image, &filePath]() {
        filePath = QFileDialog::getOpenFileName(nullptr,
                                                        "Chose image",
                                                        "..\\",
                                                        "files (*.jpg , *.png)");

        label.setPixmap(QPixmap::fromImage(blurImage(image, 8)).scaled(
                                            label.width(),
                                            label.height(), Qt::KeepAspectRatio));


        label.setPixmap(QPixmap("filePath"));
        //label->show();
    });

    QObject::connect(&slider, &QSlider::valueChanged, [&image, &slider, &label]() {
        label.setPixmap(QPixmap::fromImage(blurImage(image, slider.value())));


    });

    QObject::connect (&save, &QPushButton::clicked, [&label, &filePath, &slider]() {
       QString savePath = QFileDialog::getSaveFileName(nullptr,
                                                       "Save image",
                                                       "..\\");
       //QPixmap pic = label->pixmap(Qt::ReturnByValue);
       //pic.save(savePath);
       auto bluredPic = blurImage(QImage(filePath), slider.value());
       bluredPic.save(savePath);
    });


//  w.resize(desc->width(), desc->height()-50);
    w.showMaximized();
    return a.exec();
}


