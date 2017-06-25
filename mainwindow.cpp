#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <Dialog.h>
#include <cstdlib>
#include <ctime>

void showPopUp(const QString text)
{
    Dialog d(text);
    d.exec();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //OPEN THE FILE
    QFile file("questions.txt");
    if(file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        question_answers_struct qas;
        QTextStream in(&file);
        int counter = 0;

        //READ THE FILE LINE BY LINE
        while (!in.atEnd())
        {
            QString line = in.readLine();

            //(BY THE COUNTER) DETECT THE QUESTIONS, ANSWERS AND IF THEY ARE THE CORRECT ANSWER
            switch(counter)
            {
                case 0:
                    qas.question = line;
                    break;

                case 1:
                    //IF HAS GOT A '-' AT THE OUTSET, IT'S THE CORRECT ANSWER
                    if(line[0] == '-')
                    {
                        qas.correct_answer = 'A';

                        //REMOVE '-' FROM THE OUTSET
                        line.remove(0, 1);
                    }

                    qas.answer_a = line;

                    break;

                case 2:
                    //IF HAS GOT A '-' AT THE OUTSET, IT'S THE CORRECT ANSWER
                    if(line[0] == '-')
                    {
                        qas.correct_answer = 'B';

                        //REMOVE '-' FROM THE OUTSET
                        line.remove(0, 1);
                    }

                    qas.answer_b = line;

                    break;

                case 3:
                    //IF HAS GOT A '-' AT THE OUTSET, IT'S THE CORRECT ANSWER
                    if(line[0] == '-')
                    {
                        qas.correct_answer = 'C';

                        //REMOVE '-' FROM THE OUTSET
                        line.remove(0, 1);
                    }

                    qas.answer_c = line;

                    break;

                case 4:
                    //IF HAS GOT A '-' AT THE OUTSET, IT'S THE CORRECT ANSWER
                    if(line[0] == '-')
                    {
                        qas.correct_answer = 'D';

                        //REMOVE '-' FROM THE OUTSET
                        line.remove(0, 1);
                    }
                    qas.answer_d = line;

                    //PUT THEM IN THE VECTOR
                    questions_answers.push_back(qas);

                    counter = -1; //the value is -1 because it will be increased before the loop restart
                    break;
                }
                ++counter;
        }

        num_questions = questions_answers.size();

        //CALCULATE POINTS PER CORRECT ANSWER
        PPCA = 10 / questions_answers.size();
    }
    else //SHOW AN ERROR
        showPopUp("Error with the file that contains questions and answer.\n(questions.txt)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbStart_clicked()
{
    //IF NAME AND SURNAME FORMS AREN'T EMPTY
    if(!ui->leName->text().isEmpty() && !ui->leSurname->text().isEmpty())
    {
        //DISABLE ALL FORMS
        ui->leName->setDisabled(true);
        ui->leSurname->setDisabled(true);
        ui->pbStart->setDisabled(true);

        //ENABLE THE BUTTONS TO ANSWER
        ui->pbA->setEnabled(true);
        ui->pbB->setEnabled(true);
        ui->pbC->setEnabled(true);
        ui->pbD->setEnabled(true);

        this->newQuestion();
    }
    else //SHOW AN ERROR
        showPopUp("The forms must not be empty!");
}

void MainWindow::newQuestion()
{
    //DETECT IF ALL QUESTIONS ARE ALREADY ASKED
    bool allQuestionsAsked = num_asked_questions == num_questions;

    if(!allQuestionsAsked)
    {
        //GET A RANDOM VECTOR ELEMENT
        srand(time(0));
        current_question_index = rand() % questions_answers.size();

        //SET LABELS TEXT WITH THE INFORMATIONS OF THE VECTOR ELEMENT
        ui->lQuestion->setText(questions_answers.at(current_question_index).question);
        ui->lAnswerA->setText(questions_answers.at(current_question_index).answer_a);
        ui->lAnswerB->setText(questions_answers.at(current_question_index).answer_b);
        ui->lAnswerC->setText(questions_answers.at(current_question_index).answer_c);
        ui->lAnswerD->setText(questions_answers.at(current_question_index).answer_d);

        ++num_asked_questions;
    }
    else
    {
        //OPEN THE FILE
        QFile file("users_database.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            QTextStream out(&file);

            //WRITE: NAME, SURNAME, GRADE
            out<<ui->leName->text()<<" "<<ui->leSurname->text()<<" "<<grade<<"\n";
        }

        //DISABLE ALL THE BUTTONS TO ANSWER
        ui->pbA->setDisabled(true);
        ui->pbB->setDisabled(true);
        ui->pbC->setDisabled(true);
        ui->pbD->setDisabled(true);

        //CLEAR ALL LABELS
        ui->lQuestion->setText("");
        ui->lAnswerA->setText("");
        ui->lAnswerB->setText("");
        ui->lAnswerC->setText("");
        ui->lAnswerD->setText("");

        //SHOW THE GRADE
        showPopUp("Grade: " + QString::number(grade));

        //CLOSE THE PROGRAM
        this->close();
    }
}

void MainWindow::on_pbA_clicked()
{
    //IF THE ANSWER IS CORRECT
    if(questions_answers[current_question_index].correct_answer == 'A')

        //INCREASE THE GRADE BY A PPCA (POINT PER CORRECT ANSWER)
        grade += PPCA;

    //REMOVE THAT ANSWER FROM THE VECTOR (SO THAT, IT CAN'T BE USED AGAIN)
    questions_answers.remove(current_question_index);

    this->newQuestion();
}

void MainWindow::on_pbB_clicked()
{
    //IF THE ANSWER IS CORRECT
    if(questions_answers[current_question_index].correct_answer == 'B')

        //INCREASE THE GRADE BY A PPCA (POINT PER CORRECT ANSWER)
        grade += PPCA;

    //REMOVE THAT ANSWER FROM THE VECTOR (SO THAT, IT CAN'T BE USED AGAIN)
    questions_answers.remove(current_question_index);

    this->newQuestion();
}

void MainWindow::on_pbC_clicked()
{
    //IF THE ANSWER IS CORRECT
    if(questions_answers[current_question_index].correct_answer == 'C')

        //INCREASE THE GRADE BY A PPCA (POINT PER CORRECT ANSWER)
        grade += PPCA;

    //REMOVE THAT ANSWER FROM THE VECTOR (SO THAT, IT CAN'T BE USED AGAIN)
    questions_answers.remove(current_question_index);

    this->newQuestion();
}

void MainWindow::on_pbD_clicked()
{
    //IF THE ANSWER IS CORRECT
    if(questions_answers[current_question_index].correct_answer == 'D')

        //INCREASE THE GRADE BY A PPCA (POINT PER CORRECT ANSWER)
        grade += PPCA;

    //REMOVE THAT ANSWER FROM THE VECTOR (SO THAT, IT CAN'T BE USED AGAIN)
    questions_answers.remove(current_question_index);

    this->newQuestion();
}
