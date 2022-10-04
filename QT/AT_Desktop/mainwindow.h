#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QTabWidget;
class QWidget;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTabWidget *homeTabWidget;
    QHBoxLayout *mainLayout;
    QHBoxLayout *statLayout;
    QHBoxLayout *assetLayout;


    void CreateTabs();
    void CreateLayouts();

    void markets();
    void favs();
    void wallet();
    void settings();
};
#endif // MAINWINDOW_H
