#pragma once
#include <QtWidgets>
#include <QMainWindow>
#include "aboutdialog.h"
#include "movieappinterface.h"
#include "exitwidget.h"
#include "chosenmovie.h"
#include "movie_model.h"
//#include "movie.h"


namespace Ui{ class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MovieModel* m_model = new MovieModel();
    QString m_path = "";
    QPair<QList<movieInfo_t>, movieCriteria_t> make_List();

private slots:
    void on_ExitButton_clicked();
    void on_RandomGenerator_clicked();
    void on_About_triggered();
    void on_File();
    void on_filterButton_clicked();
};
