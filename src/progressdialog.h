#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QProgressDialog>

#ifdef _WIN32
#ifdef PROGRESSDIALOG
#define PROGRESSDIALOGEXPORT __declspec(dllexport)
#else
#define PROGRESSDIALOGEXPORT __declspec(dllimport)
#endif
#else
#define PROGRESSDIALOGEXPORT
#endif

class PROGRESSDIALOGEXPORT ProgressDialog : public QProgressDialog {
  Q_OBJECT
public:
  ProgressDialog(const QString &labelText, const QString &cancelButtonText,
                 int minimum, int maximum, QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());
  ProgressDialog(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());

public slots:

  void setValue(int progress);

signals:
  void updatingValue();
  void valueUpdated();
};

#endif // PROGRESSDIALOG_H
