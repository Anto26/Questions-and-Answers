#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

struct question_answers_struct
{
    QString question, answer_a, answer_b, answer_c, answer_d;
    QChar correct_answer;
};

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        void newQuestion();

        ~MainWindow();

    private slots:
        void on_pbStart_clicked();

        void on_pbA_clicked();

        void on_pbB_clicked();

        void on_pbC_clicked();

        void on_pbD_clicked();

    private:
        Ui::MainWindow *ui;

        QVector<question_answers_struct> questions_answers;

        int current_question_index,
            num_asked_questions = 0,
            num_questions;

        float grade = 0,
              PPCA; //POINTS PER CORRECT ANSWER
};

#endif // MAINWINDOW_H
