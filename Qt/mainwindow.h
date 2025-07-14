#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QBarSet>
#include <QChartView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*
struct chart{
    QBarSeries *series;
    QChart *_chart;
    QChartView *chartView;

    chart() {}

    void setChart(unsigned int c, unsigned int cs, unsigned int w, unsigned int s, unsigned int p) {
        series = new QBarSeries();
        _chart = new QChart();
        chartView = new QChartView();

        QBarSet *set1 = new QBarSet("Chars");
        QBarSet *set2 = new QBarSet("Chars w/o spaces");
        QBarSet *set3 = new QBarSet("Words");
        QBarSet *set4 = new QBarSet("Sentences");
        QBarSet *set5 = new QBarSet("Paragraphs");

        *set1 << c;
        *set2 << cs;
        *set3 << w;
        *set4 << s;
        *set5 << p;

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
        chartView->show();

        delete set1;
        delete set2;
        delete set3;
        delete set4;
        delete set5;

    }

};
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_selectfile_clicked();
    void on_pushButton_count_clicked();
    void on_pushButton_export_clicked();

private:
    Ui::MainWindow *ui;
    QString file_path;
    QStringList lines;
    unsigned int chars;
    unsigned int chars_without_spaces;
    unsigned int words;
    unsigned int sentences;
    unsigned int paragraphs;
  /*  //chart *barChart;
    QChart *chart;
    QChartView *chartView;
    QBarSeries *series;*/

    void initUI();
    void updateTableData();
    void setAndShowChartView();
    void resetUI();
};
#endif // MAINWINDOW_H
