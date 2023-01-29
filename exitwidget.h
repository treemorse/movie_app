#pragma once

#include <QtWidgets>

class ExitWidget : public QWidget
{
    Q_OBJECT
public:
    ExitWidget(QWidget *parent = nullptr);
    ~ExitWidget();

private:
    QLabel  *QuitterLabel;
    QDialogButtonBox *QuitChoiceButtons;
    QPushButton *NoButton;
    QPushButton *YesButton;

private slots:
    void on_QuitChoiceButtons_accepted();
    void on_QuitChoiceButtons_rejected();

};

