#include "fteller.h"
#include <QDebug>
#include <QByteArray>
#include <QFile>

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
  qDebug () << " Start DeNada";
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
  connect (mainUi.quitButton, SIGNAL (released()),
           this, SLOT (Quit()));
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
