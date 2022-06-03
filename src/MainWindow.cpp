#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWindow),
	m_manager{new QNetworkAccessManager(this)}
{
	ui->setupUi(this);

	connect(m_manager, &QNetworkAccessManager::finished,
			this, &MainWindow::replyFinished);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
	m_manager->get(QNetworkRequest(QUrl::fromUserInput(ui->editUrl->text())));
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
	QJsonParseError err;

	m_json = QJsonDocument::fromJson(reply->readAll(), &err)
				.object().value("rates").toObject();

	ui->cmbCurrency->clear();


	const QStringList &keys{m_json.keys()};

	for (const auto &key : keys)
		ui->cmbCurrency->addItem(key);
}

void MainWindow::on_cmbCurrency_currentIndexChanged(int index)
{
	ui->editValue->setText(QString::number(m_json.value(m_json.keys().at(index)).toDouble()));
}
