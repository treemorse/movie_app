#include "movie_model.h"
#include "QFile"
#include "QTextStream"
#include "movie.h"
#include <QFileInfo>

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

MovieModel::MovieModel() {}

MovieModel::MovieModel(QString& databasePath)
{
    if (fileExists(databasePath))
        readDatabase(databasePath);
}


void MovieModel::readDatabase(QString& databasePath)
{

    QFile file(databasePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file:" << file.fileName() << "Error:" << file.errorString() << "  " << QCoreApplication::applicationDirPath();
    }
    else
    {
        QTextStream in(&file);
        in.readLine();
        while (!in.atEnd())
        {
            QString line = in.readLine();

            QStringList valueList = line.split(";;;");
            movieInfo_t elementInfo;
            fillMovieInfo(valueList, elementInfo);
            m_databaseInfo.push_back(elementInfo);
        }
        file.close();
     }
}


void MovieModel::fillMovieInfo(QStringList& valueList, movieInfo_t& info)
{
    info.rank = valueList.at(0).toInt();
    info.name = valueList.at(1);
    info.directors_name = valueList.at(7);
    if(!m_directors.contains(valueList.at(7)))
        m_directors.push_back(valueList.at(7));
    info.imdb_score = valueList.at(3).toDouble();
    info.runtime = valueList.at(8).toInt();
    if (valueList.at(10)[0] == '"')
        info.description = valueList.at(10).mid(1, valueList.at(10).size()-2);
    else
        info.description = valueList.at(10);
    info.year_of_prod = valueList.at(2).toInt();


    QStringList genres = valueList.at(5).split(", ");
    for(int i = 0; i < genres.size(); ++i)
    {
        QString genre = genres.at(i);
        QString new_genre = "";
        for (int j = 0; j < genre.size(); ++j){
            if (genre.at(j) != '"' && genre.at(j) != '/')
                new_genre += genre.at(j);
        }
        if(!m_genres.contains(new_genre))
            m_genres.push_back(new_genre);

        info.genre.push_back(new_genre);
    }
}

bool MovieModel::compareMovie(movieInfo_t& movie, movieCriteria_t& criteria)
{
    if(criteria.directors_name == "Any" || criteria.directors_name == movie.directors_name)
    {
        if((criteria.imdb_score.first <= movie.imdb_score
            && criteria.imdb_score.second >= movie.imdb_score)
                || criteria.imdb_score == qMakePair(0.0, 10.0))
        {
            if((criteria.runtime.first <= movie.runtime
                    && criteria.runtime.second >= movie.runtime)
                    || criteria.runtime == qMakePair(0, 10))
            {
                if((criteria.year_of_prod.first <= movie.year_of_prod
                        && criteria.year_of_prod.second >= movie.year_of_prod)
                        || criteria.year_of_prod == qMakePair(1915, 2021))
                {
                    for(int i = 0; i < movie.genre.size(); ++i)
                    {
                        if(movie.genre.at(i) == criteria.genre || criteria.genre == "Any")
                            return true;
                    }
                }
            }
        }
    }

    return false;

}


void MovieModel::getMovies(QList<movieInfo_t> &result, movieCriteria_t &criteria)
{
    const int size = m_databaseInfo.size();
    for(int i = 0; i < size; ++i)
        if(compareMovie(m_databaseInfo[i], criteria))
            result.push_back(m_databaseInfo.at(i));
}

QVariant MovieModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
           return QVariant();

    if (orientation == Qt::Horizontal) {
       switch (section) {
           case 0:
               return tr("Name");

           case 1:
               return tr("Year");

           case 2:
               return tr("Score");

           case 3:
               return tr("Main Genre");

           case 4:
               return tr("Runtime");

           case 5:
               return tr("Director");

           default:
               return QVariant();
       }
    }
    return QVariant();
}

int MovieModel::rowCount(const QModelIndex &parent) const
{
    return m_databaseInfo.size();
}

int MovieModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant MovieModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (!index.isValid())
            return QVariant();

        movieInfo_t movie = m_databaseInfo.at(index.row());

        switch (index.column()) {
            case 0:
                return movie.name;

            case 1:
                return movie.year_of_prod;

            case 2:
                return movie.imdb_score;

            case 3:
                return movie.genre.at(0);

            case 4:
                return movie.runtime;

            case 5:
                return movie.directors_name;

            default:
                return QVariant();
        }
    }

    return {};
}

Qt::ItemFlags MovieModel::flags(const QModelIndex &index) const
{
    return {Qt::ItemIsEnabled};
}

