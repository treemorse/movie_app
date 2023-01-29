//#pragma once

//#include <movie_model.h>

//#include <QVector>
//#include <QString>
//#include <QtWidgets>

//class MovieModel;

//struct movieInfo_t
//{
//    int rank;
//    int year_of_prod;
//    double imdb_score;
//    QList<QString> genre;
//    int runtime;
//    QString directors_name;
//    QString name;
//    QString description;

//};


//struct movieCriteria_t
//{
//    QPair<int, int> year_of_prod;
//    QPair<double, double> imdb_score;
//    QString genre;
//    QPair<int, int> runtime;
//    QString directors_name;
//};


//class MovieAppInterface
//{

//public:
//    static MovieAppInterface getInstance(QString& path) { static MovieAppInterface instance(path); return instance;}
//    QList<movieInfo_t> search(movieCriteria_t& criteria);

//    QList<QString> getGenreList();
//    QList<QString> getDirectorList();

//    MovieModel* m_pImpl;
//private:
//    MovieAppInterface(QString &path);

//    QString m_databaseName;
//};

