#ifndef FTELLER_H
#define FTELLER_H

#include "deliberate.h"
#include <QMainWindow>
#include <QStringList>
#include <QGuiApplication>
#include "config-edit.h"
#include "ui_fteller.h"
#include <QTimer>
#include <QProcess>
#include <cstdint>

namespace fteller {

using namespace deliberate;

class fteller : public QMainWindow
{
  Q_OBJECT
public:
  explicit fteller(QApplication & dApp, QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
  void  Init (QGuiApplication &ap);

  void  AddConfigMessages (const QStringList & cm)
           { configMessages.append (cm); }
  bool  Run ();

  enum class UIOptions : std::int32_t {
    Options=0,
    EditSettings,
    Nothing,
    Maximum
  };

signals:

private slots:

  void Quit ();
  void ComboSlot(int index);
  void ComboPointAt(int index);
  void Options();
  void EditSettings();
  void Restart ();
  void ProcessDone (int status, QProcess::ExitStatus xSt);
  void UpdateSettings ();
//  void About ();
  void License ();
//  void Exiting ();

private:
  void Connect ();
  void CloseCleanup ();
  void SetFortune (const QString & txt);

  QGuiApplication    *app;

  QObject * rootBox;

  Ui_FTellerMain      mainUi;
  QStringList     fortuneData;
  QTimer       *fortuneTicker;
  std::int32_t  tickerSecs;
  QString       tickerSetting;
  QStringList     configMessages;

  QString         osName;

  ConfigEdit       configEdit;
  QProcess         runFortune;
};

} // namespace

#endif // FTELLER_H
