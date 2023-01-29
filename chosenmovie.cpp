#include "chosenmovie.h"
#include "movie.h"
#include "ui_chosenmovie.h"


ChosenMovie::ChosenMovie(movieInfo_t &message, MovieModel* m_model, movieCriteria_t criteria, QWidget *parent) : QWidget(parent), ui(new Ui::ChosenMovie), m_model(m_model)
{
    ui->setupUi(this);
    ui->MovieLayout->setAlignment(Qt::AlignCenter);
    m_pMovieLabel = new QLabel();
    m_pMovieLabel->setText(message.name + "    " + QString::number(message.year_of_prod));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    m_pMovieLabel->setFont(font);
    m_pMovieLabel->setAlignment(Qt::AlignHCenter);
    m_pMovieLabel->setAlignment((Qt::AlignTop));
    ui->MovieInfoLayout->addWidget(m_pMovieLabel);
    ui->DescriptionSpace->setText(message.description);
    m_pDirector = new QLabel();
    m_pDirector->setText("Director: " + message.directors_name);
    m_pGenres = new QLabel();
    QString sample = "";
    for (int i = 0; i < message.genre.size(); ++i){
        sample += message.genre.at(i) + ", ";
    }
    m_pGenres->setText("Genres: " + sample.mid(0, sample.size()-2));
    m_pRuntime = new QLabel();
    m_pRuntime->setText("Runtime: " + QString::number(message.runtime) + " min");
    m_pScore = new QLabel();
    m_pScore->setText("Score: " + QString::number(message.imdb_score));
    ui->VerticalInfoLayout->addWidget(m_pGenres);
    ui->VerticalInfoLayout->addWidget(m_pScore);
    ui->VerticalInfoLayout->addWidget(m_pRuntime);
    ui->VerticalInfoLayout->addWidget(m_pDirector);

    ui->ScoreSpace->setText(QString::number(criteria.imdb_score.first)
                            + "-" + QString::number(criteria.imdb_score.second));
    ui->GenreSpace->setText(criteria.genre);
    ui->YearSpace->setText(QString::number(criteria.year_of_prod.first)
                           + "-" + QString::number(criteria.year_of_prod.second));
    ui->DirectorSpace->setText(criteria.directors_name);
    ui->RuntimeSpace->setText(QString::number(criteria.runtime.first)
                              + "-" + QString::number(criteria.runtime.second));
}

ChosenMovie::~ChosenMovie()
{
    delete ui;
}

void ChosenMovie::on_pushButton_clicked()
{
    ChosenMovie::~ChosenMovie();
}

void ChosenMovie::on_RandomGenerator_clicked()
{
//    MovieAppInterface MovieInterface = MovieAppInterface::getInstance(m_path);
    movieCriteria_t criteria;
    criteria.genre = ui->GenreSpace->toPlainText();
    QStringList score_tuple = ui->ScoreSpace->toPlainText().split("-");
    criteria.imdb_score = qMakePair(score_tuple.at(0).toDouble(), score_tuple.at(1).toDouble());
    QStringList runtime_tuple_base = ui->RuntimeSpace->toPlainText().split(" ");
    QStringList runtime_tuple = runtime_tuple_base.at(0).split("-");
    criteria.runtime = qMakePair(runtime_tuple.at(0).toInt(), runtime_tuple.at(1).toInt());
    QStringList year_tuple = ui->YearSpace->toPlainText().split("-");
    criteria.year_of_prod = qMakePair(year_tuple.at(0).toInt(), year_tuple.at(1).toInt());
    criteria.directors_name = ui->DirectorSpace->toPlainText();

//    auto list =
    QList<movieInfo_t> list;
    m_model->getMovies(list, criteria);
    if (list.isEmpty())
    {
        QMessageBox *box = new QMessageBox();
        box->setText("No such movies, my friend");
        box->exec();
    }
    else
    {
        QDateTime time;
        qsrand(time.currentSecsSinceEpoch());
        movieInfo_t random_movie = list.at(qrand() % list.size());
        ChosenMovie* chosenMovie = new ChosenMovie(random_movie, m_model, criteria);
        chosenMovie->show();
    }
    ChosenMovie::~ChosenMovie();
}

void ChosenMovie::on_CopyButton_clicked()
{
    QClipboard* copy = QApplication::clipboard();
    copy->setText(m_pMovieLabel->text());
}

void ChosenMovie::on_DownloadButton_clicked()
{
    QList<QString> buf = m_pMovieLabel->text().split("    ");
    QList<QString> new_buf = buf.at(0).split(" ");
    new_buf.append(buf.at(1));
    QString file_name = "/";
    for (int i = 0; i < new_buf.size(); ++i){
        file_name += new_buf.at(i) + "_";
    }
    file_name += ".txt";
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
    dialog.exec();
    if (dialog.directory().canonicalPath()!= ""){
        QString path = dialog.directory().canonicalPath() + file_name;
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << m_pMovieLabel->text() << endl;
        stream << m_pGenres->text()<< endl;
        stream << m_pScore->text() << endl;
        stream << m_pRuntime->text() << endl;
        stream << m_pDirector->text() << endl;
    }
}

