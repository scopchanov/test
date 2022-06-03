#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qnetworkaccessmanager.h"
#include <QWidget>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_btnConnect_clicked();

private:
	Ui::MainWindow *ui;
	QNetworkAccessManager *m_manager;
	QJsonObject m_json;

private slots:
	void replyFinished(QNetworkReply *reply);
	void on_cmbCurrency_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
