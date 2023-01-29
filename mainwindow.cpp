#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *actionAbout = ui->menuHelp->addAction(tr("About"));
    QAction *actionFile = ui->menuOpen->addAction(tr("File"));

    ui->MOVIElabel->setText("MovieApp");
    QFont font;
    font.setPointSize(40);
    font.setBold(true);
    font.setItalic(true);
    ui->MOVIElabel->setFont(font);
    ui->MOVIElabel->setAlignment(Qt::AlignCenter);

    QObject::connect(actionAbout, SIGNAL(triggered()), this, SLOT(on_About_triggered()));
    QObject::connect(actionFile, SIGNAL(triggered()), this, SLOT(on_File()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPair<QList<movieInfo_t>, movieCriteria_t> MainWindow::make_List(){

    //m_model = MovieAppInterface::getInstance(m_path);

    movieCriteria_t criteria;
    criteria.genre = ui->GenreCbox->currentText();
    QStringList score_tuple = ui->ScoreCbox->currentText().split("-");
    criteria.imdb_score = qMakePair(score_tuple.at(0).toDouble(), score_tuple.at(1).toDouble());
    QStringList runtime_tuple_base = ui->RuntimeCbox->currentText().split(" ");
    QStringList runtime_tuple = runtime_tuple_base.at(0).split("-");
    criteria.runtime = qMakePair(runtime_tuple.at(0).toInt(), runtime_tuple.at(1).toInt());
    QStringList year_tuple = ui->YearCbox->currentText().split("-");
    criteria.year_of_prod = qMakePair(year_tuple.at(0).toInt(), year_tuple.at(1).toInt());
    criteria.directors_name = ui->DirectorCbox->currentText();

    QList<movieInfo_t> list;
    m_model->getMovies(list, criteria);

    return qMakePair(list, criteria);
}

void MainWindow::on_File(){
    m_path = QFileDialog::getOpenFileName(this, "Open dataset", QDir::currentPath(), "Dataset (*.csv)");
    if(m_path != ""){
        m_model = new MovieModel(m_path);
//        m_model = MovieAppInterface::getInstance(m_path);

        QList<QString> genres = m_model->m_genres;
        QList<QString> directors = m_model->m_directors;

        ui->GenreCbox->insertItems(1, genres);
        ui->DirectorCbox->insertItems(1, directors);

        QList<movieInfo_t> list = MainWindow::make_List().first;
        ui->tableView->setModel(m_model);

    }
}

void MainWindow::on_About_triggered(){
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_ExitButton_clicked()
{
    ExitWidget* exitwidget = new ExitWidget();
    exitwidget->show();
}

void MainWindow::on_RandomGenerator_clicked()
{
    if (m_path != ""){
        QPair<QList<movieInfo_t>, movieCriteria_t> pair = MainWindow::make_List();

        QList<movieInfo_t> list = pair.first;
        movieCriteria_t criteria = pair.second;

        if (list.isEmpty())
        {
            QMessageBox *box = new QMessageBox();
            box->setText("No such movies, my friend");
            box->setContentsMargins(3,5,6,7);
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
    }
    else{
        QMessageBox *box = new QMessageBox();
        box->setText("Please load file");
        box->setContentsMargins(3,5,6,7);
        box->exec();
    }
}

void MainWindow::on_filterButton_clicked()
{
    QList<movieInfo_t> list = MainWindow::make_List().first;
}
