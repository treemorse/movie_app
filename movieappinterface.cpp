#include "movieappinterface.h"

MovieAppInterface::MovieAppInterface(QString &path)
{
    qDebug() << path;
    m_databaseName = QString(path);
    m_pImpl = new MovieAppController(m_databaseName);

}

QList<movieInfo_t> MovieAppInterface::search(movieCriteria_t& criteria)
{
    QList<movieInfo_t> result;
    m_pImpl->getMovies(result, criteria);
    return result;
}



QList<QString> MovieAppInterface::getGenreList()
{
    return m_pImpl->m_genres;
}

QList<QString> MovieAppInterface::getDirectorList()
{
    return m_pImpl->m_directors;
}


