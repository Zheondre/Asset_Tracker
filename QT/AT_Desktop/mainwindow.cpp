#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qapplication.h"

#if 1

const static inline std::vector<std::string> assets =
{
    "bitcoin",
    "ripple",
    "solona",
    "ethereum"
};

#endif


 class AssetTab : public QWidget {

  Q_OBJECT
 public:
    explicit AssetTab( QWidget *parent = nullptr);

 };

 class FavsTab : public QWidget {

  Q_OBJECT
 public:
    explicit FavsTab( QWidget *parent = nullptr);
 };

 class StatsTab : public QWidget {

  Q_OBJECT
 public:
    explicit StatsTab( QWidget *parent = nullptr);

 };


 AssetTab::AssetTab(QWidget *parent): QWidget(parent){

     QHBoxLayout *mainHeader = new QHBoxLayout();
     mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Name ")));
     mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Price ")));
     mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Change ")));
     mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Market Cap ")));
     //mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "7 Days ")));
    // mainHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Favs")));


     QVBoxLayout *mainLayout = new QVBoxLayout;

     mainLayout->addLayout(mainHeader);

     QHBoxLayout *assetLayout;

     for(const std::string& coin: assets){

         assetLayout = new QHBoxLayout();

         assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout",  coin.c_str())));
         assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "$0 ")));
         assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "+0.0 ")));
         assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "$0.0")));
         //assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "Upload")));

         mainLayout->addLayout(assetLayout);
     }

     setLayout(mainLayout);
 }

FavsTab::FavsTab(QWidget *parent): QWidget(parent){

}

StatsTab::StatsTab(QWidget *parent): QWidget(parent){


    QHBoxLayout *statHeader = new QHBoxLayout();

    statHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Name ")));
    statHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Price ")));
    statHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Avg Cost ")));
    statHeader->addWidget(new QLabel(QApplication::translate("windowlayout", "Profit/Loss ")));

    QHBoxLayout *assetLayout = new QHBoxLayout();

    assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "Coin ")));
    assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "$1 ")));
    assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "+0.1 ")));
    assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "$0.0")));
    assetLayout->addWidget(new QLabel(QApplication::translate("windowlayout", "Upload")));
}



void MainWindow::CreateLayouts(){

    homeTabWidget = new QTabWidget;

    homeTabWidget->addTab(new AssetTab(), tr("Asset"));
    //homeTabWidget->addTab(new FavsTab(), tr("Favs"));
    //homeTabWidget->addTab(new StatsTab(), tr("Stats"));

    //homeTabWidget->addTab( , tr("Wallet"));
    //homeTabWidget->addTab( , tr("Settings"));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CreateLayouts();


     //QGridLayout *mainLayout = new QGridLayout;
}

MainWindow::~MainWindow()
{
    delete ui;
}

