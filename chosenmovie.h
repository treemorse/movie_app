#pragma once
//#include "movieappinterface.h"
#include "movie.h"
#include "mainwindow.h"
#include <QtWidgets>
#include "movie_model.h"

namespace Ui { class ChosenMovie; }

class ChosenMovie : public QWidget
{
    Q_OBJECT

public:
    ChosenMovie(movieInfo_t &message, MovieModel* m_model = nullptr, movieCriteria_t criteria = movieCriteria_t(), QWidget *parent = nullptr);
    ~ChosenMovie();

private slots:
    void on_pushButton_clicked();
    void on_RandomGenerator_clicked();

    void on_CopyButton_clicked();

    void on_DownloadButton_clicked();
private:
    Ui::ChosenMovie *ui;
    MovieModel* m_model;
    QLabel *m_pMovieLabel;
    QLabel *m_pDirector, *m_pGenres, *m_pRuntime, *m_pScore;
    QString m_path = "";
};

