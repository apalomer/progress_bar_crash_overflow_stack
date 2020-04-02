#include "progressdialog.h"

ProgressDialog::ProgressDialog(const QString &labelText,
                               const QString &cancelButtonText, int minimum,
                               int maximum, QWidget *parent, Qt::WindowFlags f)
    : QProgressDialog(labelText, cancelButtonText, minimum, maximum, parent,
                      f) {}

ProgressDialog::ProgressDialog(QWidget *parent, Qt::WindowFlags f)
    : QProgressDialog(parent, f) {}

void ProgressDialog::setValue(int progress) {
  emit updatingValue();
  QProgressDialog::setValue(progress);
  emit valueUpdated();
}
