#ifndef MOVIE_H
#define MOVIE_H

#pragma once

//#include <movie_model.h>

#include <QVector>
#include <QString>
#include <QtWidgets>

//class MovieModel;

struct movieInfo_t
{
    int rank;
    int year_of_prod;
    double imdb_score;
    QList<QString> genre;
    int runtime;
    QString directors_name;
    QString name;
    QString description;

};


struct movieCriteria_t
{
    QPair<int, int> year_of_prod;
    QPair<double, double> imdb_score;
    QString genre;
    QPair<int, int> runtime;
    QString directors_name;
};

#endif // MOVIE_H
