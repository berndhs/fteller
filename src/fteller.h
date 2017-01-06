#ifndef FTELLER_H
#define FTELLER_H

#include "deliberate.h"
#include <QMainWindow>
#include <QStringList>
#include <QGuiApplication>
#include "config-edit.h"
#include "ui_fteller.h"
#include <QTimer>

namespace fteller {

using namespace deliberate;

class fteller : public QMainWindow
{
  Q_OBJECT
public:
  explicit fteller(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
  void  Init (QGuiApplication &ap);

  void  AddConfigMessages (const QStringList & cm)
           { configMessages.append (cm); }
  bool  Run ();

signals:

private slots:

  void Quit ();
//  void Restart ();
//  void EditSettings ();
//  void SetSettings ();
//  void About ();
  void License ();
//  void Exiting ();

private:
  void Connect ();
  void CloseCleanup ();

  QGuiApplication    *app;

  Ui_FTellerMain      mainUi;
  QStringList     fortuneData;
  QTimer       *fortuneTicker;
  QStringList     configMessages;

  ConfigEdit       configEdit;
};

} // namespace

#endif // FTELLER_H
