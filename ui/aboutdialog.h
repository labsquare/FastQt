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

    bool event(QEvent *e);

protected Q_SLOTS:
    void openGithub();
    void openTwitter();

private:
    QTabWidget * mTabWidget;
    QLabel * mHeader;
    QString mTitle;
    QString mSubtitle;
    QDialogButtonBox * mButtonBox;

    /* easter egg */
    Qt::Key kc[10] = {
        Qt::Key_Up, Qt::Key_Up,
        Qt::Key_Down, Qt::Key_Down,
        Qt::Key_Left, Qt::Key_Right, Qt::Key_Left, Qt::Key_Right,
        Qt::Key_B, Qt::Key_A
    };
    int i_kc_offset;
};

#endif // ABOUTDIALOG_H
