#include "fteller.h"
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QProcess>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlEngine>
#include <QWidget>
#include <QUrl>
#include <QApplication>

namespace fteller {

fteller::fteller(QApplication & dApp, QWidget *parent, Qt::WindowFlags flags)
  :QMainWindow(parent,flags),
    app(&dApp),
    configEdit(this)
{
  mainUi.setupUi(this);
  osName = QString ("dunno");
  mainUi.appName->setText(tr("fteller"));
  QQuickWidget *view = new QQuickWidget(this);
  view->setSource(QUrl("qrc:/qml/Main.qml"));
  view->setResizeMode(QQuickWidget::SizeViewToRootObject);
  rootBox  = view->rootObject();
  if (rootBox->objectName() == QString("MainBox")) {
    qDebug () << Q_FUNC_INFO << "MainBox is root object";
    rootBox->setProperty("width", QVariant(int(300)));
    rootBox->setProperty("height",QVariant(int(300)));
    int fullWidth = rootBox->property("fullWidth").toInt();
    int fullHeight = rootBox->property("fullHeight").toInt();
    osName = rootBox->property("theOS").toString();
    qDebug() << Q_FUNC_INFO << osName << fullWidth << fullHeight;
    if (osName == QString("android")) {
      showFullScreen();
      rootBox->setProperty("width", QVariant(fullWidth));
      rootBox->setProperty("height",QVariant(fullHeight));
    }
  }
  mainUi.textView = view;
//  mainUi.appName
  fortuneTicker = new QTimer(this);
  tickerSetting = QString ("delays/updatesFrequency");
  if (Settings().contains(tickerSetting)) {
    tickerSecs = Settings().value(tickerSetting).toInt();
  } else {
    tickerSecs = 5*60; // seconds;
    Settings().setValue(tickerSetting,QVariant(tickerSecs));
    Settings().sync();
  }
  fortuneTicker->start(1000*tickerSecs);
  Connect();
  License();
}
void
fteller::Connect ()
{
  mainUi.optionsButton->setMaxCount(int(UIOptions::Maximum));
  mainUi.optionsButton->insertItem (int(UIOptions::Options),tr("Options"));
  mainUi.optionsButton->insertItem (int(UIOptions::EditSettings),tr("Edit Settings"));
  mainUi.optionsButton->insertItem(int(UIOptions::Nothing),tr("Nada"));
  connect (&runFortune,SIGNAL(finished(int,QProcess::ExitStatus)),
           this,SLOT(ProcessDone(int,QProcess::ExitStatus)));
  connect (fortuneTicker,SIGNAL(timeout()),this,SLOT(Restart()));
  connect (mainUi.optionsButton,SIGNAL(currentIndexChanged(int)),
           this,SLOT(ComboPointAt(int)));
  connect (mainUi.optionsButton,SIGNAL(activated(int)),
           this,SLOT(ComboSlot(int)));
  connect (mainUi.quitButton,SIGNAL(released()),
           this,SLOT(Quit()));
  connect (mainUi.refreshButton,SIGNAL(released()),
           this,SLOT(Restart()));
//  connect (mainUi.actionSettings, SIGNAL (triggered()),
//           this, SLOT (EditSettings()));
//  connect (mainUi.actionAbout, SIGNAL (triggered()),
//           this, SLOT (About ()));
//  connect (mainUi.actionLicense, SIGNAL (triggered()),
//           this, SLOT (License ()));
//  connect (mainUi.actionRestart, SIGNAL (triggered()),
//           this, SLOT (Restart ()));
}


void
fteller::License()
{
  QFile licFile;
  licFile.setFileName(":/help/LICENSE.txt");
  licFile.open(QFile::ReadOnly);
  QByteArray licData ("No License Found !!");
  if (licFile.isOpen()) {
    licData = licFile.readAll();
  }
  QString lic = licData;
  SetFortune(lic);
}

bool
fteller::Run ()
{
  qDebug () << " Start fteller \n" << Q_FUNC_INFO;
  QSize defaultSize = size();
  QString sizeSetting ("sizes/main");
  QSize newsize = Settings().value (sizeSetting, defaultSize).toSize();
  resize (newsize);
  Settings().setValue (sizeSetting,QVariant(newsize));
  Settings().sync();
  show ();
  return true;
}

void
fteller::Quit()
{
  qDebug() << Q_FUNC_INFO;
  CloseCleanup ();
  if (app) {
    app->quit();
  }

}

void
fteller::ComboSlot(int index)
{
  UIOptions ndx = static_cast<UIOptions>(index);
  qDebug() << Q_FUNC_INFO << int(ndx);
  switch (ndx) {
    case (UIOptions::Options):
      Options();
      break;
    case UIOptions::EditSettings:
      EditSettings();
      break;
    case UIOptions::Nothing:
      qDebug() << "picked no option";
      break;
    default:
      break;
    }
}

void
fteller::ComboPointAt(int index)
{
  qDebug() << Q_FUNC_INFO << index;
}

void
fteller::Options()
{
  qDebug() << Q_FUNC_INFO;
}

void
fteller::EditSettings()
{
  qDebug() << Q_FUNC_INFO;
  configEdit.Exec ();
  Settings().sync ();
}

void
fteller::Restart()
{
  qDebug() << Q_FUNC_INFO;

  runFortune.setProgram("fortune");
  runFortune.start(QProcess::ReadOnly);
}

void
fteller::ProcessDone(int status, QProcess::ExitStatus xSt)
{
  static int callCount(0);
  if (++callCount > 5) {
    Quit();
  }
  if (callCount > 7) {
    qDebug() << Q_FUNC_INFO << "Quit failed!";
    abort();
  }
  qDebug() << Q_FUNC_INFO << status << xSt;
  Q_UNUSED(status);
  Q_UNUSED(xSt);
  QString output = runFortune.readAll();
  QString count(QString("%1:\n").arg(callCount));
  SetFortune(count+output);
//  mainUi.textDisplay->setHtml(output);
  fortuneTicker->start();
}

void fteller::UpdateSettings()
{
  tickerSecs = Settings().value(tickerSetting).toInt();
  fortuneTicker->stop();
  fortuneTicker->start(1000*tickerSecs);
}


void
fteller::CloseCleanup ()
{
  QSize currentSize = size();
  Settings().setValue ("sizes/main",currentSize);
  Settings().sync();
}

void fteller::SetFortune(const QString &txt)
{
  if (rootBox) {
    rootBox->setProperty("theText",QVariant (txt));
  } else {
    qDebug() << Q_FUNC_INFO << "don't have rootBox";
  }
}


} // namespace
