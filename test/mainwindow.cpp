#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    document = NULL;
    pageNumber = 0;

    connect(ui->actNext, SIGNAL(triggered()), this, SLOT(slotNextPage()));
    connect(ui->actPrev, SIGNAL(triggered()), this, SLOT(slotPrevPage()));
    connect(ui->actOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));
}

MainWindow::~MainWindow()
{
    delete ui;

    if(document)
        delete document;
}

void MainWindow::slotNextPage()
{
    if(!document)
        return;
    pageNumber++;
    setPage();
}

void MainWindow::slotPrevPage()
{
    if(!document)
        return;
    pageNumber--;
    setPage();
}

void MainWindow::slotOpen()
{
    pageNumber = 0;

    QString fileName = QFileDialog::getOpenFileName(this, "Открытие файла", "", "pdf (*.pdf)");

    document = Poppler::Document::load(fileName);
    if (!document || document->isLocked())
    {
        delete document;
        document = NULL;
    }
    setPage();
}

void MainWindow::setPage()
{
    if (!document)
        return;

    ui->statusBar->showMessage(QString("%1/%2").arg(pageNumber).arg(document->numPages()));

    // Access page of the PDF file
    Poppler::Page* pdfPage = document->page(pageNumber);  // Document starts at page 0
    if (pdfPage == 0)
    {
        return;
    }

    // Generate a QImage of the rendered page
    //QImage image = pdfPage->renderToImage(xres, yres, x, y, width, height);
    QImage image = pdfPage->renderToImage();
    if (image.isNull())
    {
        // ... error message ...
        return;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));

    // after the usage, the page must be deleted
    delete pdfPage;
}
