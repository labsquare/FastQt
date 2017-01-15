#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QDialog>
#include <QtWidgets>
#include <QApplication>
#include "qfonticon.h"
class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget * parent = 0);



protected:
    void addTab(const QString& textFile);
    void drawHeader();



protected Q_SLOTS:
    void openGithub();

private:
    QTabWidget * mTabWidget;
    QLabel * mHeader;
    QString mTitle;
    QString mSubtitle;
    QDialogButtonBox * mButtonBox;

};

#endif // ABOUTDIALOG_H
