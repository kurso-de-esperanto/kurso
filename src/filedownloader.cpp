#include "filedownloader.h"
#include <QFile>
#include <QStandardPaths>
#include <funkcioj.h>

FileDownloader::FileDownloader(QUrl imageUrl, QString Dosiero, QObject *parent) :
 QObject(parent)
{
   // qDebug() << "Eniris en la unua funkcio: " + Dosiero;
 connect(
  &m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
  this, SLOT (fileDownloaded(QNetworkReply*))
  );

  QNetworkRequest request(imageUrl);
  request.setHeader(QNetworkRequest::UserAgentHeader, "KursoAndrojdo");
  m_WebCtrl.get(request);
  savasDosiero = Dosiero;
}


FileDownloader::~FileDownloader() { }

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
 m_DownloadedData = pReply->readAll();
 //emit a signal
 if (m_DownloadedData.count() > 0) {
     QFile f(savasLoko + savasDosiero);
     // qDebug() << "Eniris en la lasta funkcio: " + f.fileName() + " " + QString::number(m_DownloadedData.count());
     if (f.open(QFile::WriteOnly)) {
         f.write(m_DownloadedData);
         f.close();
     }
 }

 pReply->deleteLater();
 emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
 return m_DownloadedData;
}
