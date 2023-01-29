#include "exitwidget.h"


ExitWidget::ExitWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *QuitLayout = new QVBoxLayout(this);

    QuitterLabel = new QLabel(this);
    QuitterLabel->setText("So you're a quitter, huh?");
    QuitterLabel->setAlignment(Qt::AlignCenter);

    YesButton = new QPushButton(this);
    YesButton->setText("YES");

    NoButton = new QPushButton(this);
    NoButton->setText("NO");

    QuitChoiceButtons = new QDialogButtonBox(this);
    QuitChoiceButtons->addButton(YesButton,QDialogButtonBox::AcceptRole);
    QuitChoiceButtons->addButton(NoButton,QDialogButtonBox::RejectRole);
    QuitChoiceButtons->setCenterButtons(true);

    QuitLayout->addWidget(QuitterLabel);
    QuitLayout->addWidget(QuitChoiceButtons);

    QObject::connect(QuitChoiceButtons, SIGNAL(accepted()), this, SLOT(on_QuitChoiceButtons_accepted()));
    QObject::connect(QuitChoiceButtons, SIGNAL(rejected()), this, SLOT(on_QuitChoiceButtons_rejected()));
}


ExitWidget::~ExitWidget()
{
}

void ExitWidget::on_QuitChoiceButtons_accepted()
{
    QApplication::quit();
}

void ExitWidget::on_QuitChoiceButtons_rejected()
{
    ExitWidget::~ExitWidget();
}
