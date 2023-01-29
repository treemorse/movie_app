#pragma once

//#include <movieappinterface.h>
#include <movie.h>
#include <QVariant>
#include <QList>
#include <QAbstractTableModel>


class MovieModel: public QAbstractTableModel
{
public:
    MovieModel();
    MovieModel(QString& databasePath);

    void getMovies(QList<movieInfo_t>& result, movieCriteria_t& criteria);

private:
    void readDatabase(QString& databasePath);
    void fillMovieInfo(QStringList& valueList, movieInfo_t& info);

    bool compareMovie(movieInfo_t& movie, movieCriteria_t& criteria);
public:
    QList<QString> m_genres;
    QList<QString> m_directors;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<movieInfo_t> m_databaseInfo;

};

