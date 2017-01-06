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
  fortuneTicker = new QTimer(this);
  Connect();
  License();
}

void fteller::License()
{
  QFile licFile;
  licFile.setFileName(":/help/LICENSE.txt");
  licFile.open(QFile::ReadOnly);
  QByteArray licData ("No License Found!!");
  if (licFile.isOpen()) {
    licData = licFile.readAll();
  }
  QString lic = licData;
  mainUi.textDisplay->setPlainText (lic);
}

bool
fteller::Run ()
{
  qDebug () << " Start fteller";
  QSize defaultSize = size();
  QSize newsize = Settings().value ("sizes/main", defaultSize).toSize();
  resize (newsize);
  Settings().setValue ("sizes/main",newsize);
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

void fteller::ComboSlot(int index)
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
}

void fteller::Restart()
{
  qDebug() << Q_FUNC_INFO;
  runFortune.setProgram("fortune");
  runFortune.start(QProcess::ReadOnly);
}

void fteller::ProcessDone(int status, QProcess::ExitStatus xSt)
{
  qDebug() << Q_FUNC_INFO << status << xSt;
  Q_UNUSED(status);
  Q_UNUSED(xSt);
  QString output = runFortune.readAll();
  mainUi.textDisplay->setHtml(output);
}


void
fteller::CloseCleanup ()
{
  QSize currentSize = size();
  Settings().setValue ("sizes/main",currentSize);
  Settings().sync();
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


} // namespace
