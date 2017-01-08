#include "fteller.h"
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QProcess>

namespace fteller {

fteller::fteller(QWidget *parent, Qt::WindowFlags flags)
  :QMainWindow(parent,flags),
    configEdit(this)
{
  mainUi.setupUi(this);
  mainUi.appName->setText(tr("fteller"));
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
  mainUi.textDisplay->setPlainText (lic);
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
  qDebug() << Q_FUNC_INFO << status << xSt;
  Q_UNUSED(status);
  Q_UNUSED(xSt);
  QString output = runFortune.readAll();
  mainUi.textDisplay->setHtml(output);
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


} // namespace
