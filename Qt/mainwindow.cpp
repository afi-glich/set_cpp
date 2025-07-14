#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtCharts>
#include <QGraphicsWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI() {
    QStringList lista;

    lista.push_back(trUtf8("Characters"));
    lista.push_back(trUtf8("Characters without space"));
    lista.push_back(trUtf8("Words"));
    lista.push_back(trUtf8("Sentences"));
    lista.push_back(trUtf8("Paragraphs"));

    ui->table->setColumnCount(1);
    ui->table->setRowCount(5);
    ui->table->setShowGrid(true);
    ui->table->setVerticalHeaderLabels(lista);
    ui->table->horizontalHeader()->hide();
}

void MainWindow::resetUI() {
    this->chars = this->chars_without_spaces = this->words = this->sentences = this->paragraphs = 0;
    this->file_path = "";
    this->lines.clear();
    ui->plainTextEdit_text->clear();
    ui->table->clearContents();
    ui->pushButton_export->setEnabled(false);
}

void MainWindow::on_pushButton_selectfile_clicked()
{
   resetUI();

    QString filename = QFileDialog::getOpenFileName(this, tr("Select a text file", "Home"), tr("*.txt"));

    if(!filename.contains(".txt"))
        ui->label_info->setText("Please select a .txt file.");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    this->file_path = filename;

   QTextStream in(&file);
   in.setAutoDetectUnicode(true);

    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->plainTextEdit_text->appendPlainText(line.toLocal8Bit());
        this->lines.prepend(line);
    }

     ui->pushButton_count->setEnabled(true);
}


void MainWindow::on_pushButton_count_clicked()
{
    QRegularExpression reg;

     this->chars = this->chars_without_spaces = this->words = this->sentences = this->paragraphs = 0;

    for (QString line : this->lines) {
        line = line.toLocal8Bit();

        // count any char
        reg.setPattern(".");
        this->chars += line.count(reg);

        // count any char without counting spaces
        reg.setPattern("\\S");
        this->chars_without_spaces += line.count(reg);

        // count all words
        reg.setPattern("[^\\s][\\s]");
        this->words += (line.count(reg)+1); //+1 per contare l'ultima parola della riga

        // count all the sentences
        reg.setPattern("[^\\.?!][\\.?!]");
        this->sentences += line.count(reg);

        this->paragraphs++;
    }

    ui->pushButton_export->setEnabled(true);

    updateTableData();
    setAndShowChartView();
}

void MainWindow::updateTableData() {
    //aggiungere tutto questo in un metodo updateTableData
    ui->table->setItem(0,0, new QTableWidgetItem(tr("%n", 0, this->chars)));
    ui->table->setItem(0,1, new QTableWidgetItem(tr("%n", 0, this->chars_without_spaces)));
    ui->table->setItem(0,2, new QTableWidgetItem(tr("%n", 0, this->words)));
    ui->table->setItem(0,3, new QTableWidgetItem(tr("%n", 0, this->sentences)));
    ui->table->setItem(0,4, new QTableWidgetItem(tr("%n", 0, this->paragraphs)));
}

void MainWindow::setAndShowChartView() {

    QBarSet *set1 = new QBarSet("Chars");
    QBarSet *set2 = new QBarSet("Chars w/o spaces");
    QBarSet *set3 = new QBarSet("Words");
    QBarSet *set4 = new QBarSet("Sentences");
    QBarSet *set5 = new QBarSet("Paragraphs");

    *set1 << this->chars;
    *set2 << this->chars_without_spaces;
    *set3 << this->words;
    *set4 << this->sentences;
    *set5 << this->paragraphs;

    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    ui->gridLayout_chartView->addWidget(chartView,0,0);
    chartView->show();

    delete set1;
    delete set2;
    delete set3;
    delete set4;
    delete set5;
}

void MainWindow::on_pushButton_export_clicked()
{
    QString path = this->file_path.replace("txt", "csv");

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return;

   QTextStream out(&file);
   out << "Chars;" << this->chars << endl;
   out << "Chars without spaces;" << this->chars_without_spaces << endl;
   out << "Words;" << this->words << endl;
   out << "Sentences;" << this->sentences << endl;
   out << "Paragraphs;" << this->paragraphs << endl;

}

