#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget * parent)
    :QDialog(parent)
{
    mTabWidget  = new QTabWidget(this);
    mHeader     = new QLabel(this);
    mButtonBox  = new QDialogButtonBox(this);


    QPushButton * githubButton = mButtonBox->addButton("Github",QDialogButtonBox::HelpRole);
    QPushButton * twitterButton= mButtonBox->addButton("Twitter",QDialogButtonBox::HelpRole);

    mButtonBox->addButton(QDialogButtonBox::Ok);
    githubButton->setIcon(QFontIcon::icon(0xf09b));
    twitterButton->setIcon(QFontIcon::icon(0xf099));
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mHeader);
    vLayout->addWidget(mTabWidget);
    vLayout->addWidget(mButtonBox);



//    vLayout->setContentsMargins(0,0,0,0);
//    vLayout->setSpacing(2);
    setLayout(vLayout);

    addTab(":/text/LICENSE");
    addTab(":/text/AUTHORS");
    addTab(":/text/CREDITS");
    addTab(":/text/CHANGELOG");

    mTitle = qApp->applicationName();
    mSubtitle = QString("Version %1\nGPL3 Copyright (C) 2017\nLabsquare.org").arg(qApp->applicationVersion());
    drawHeader();

    setWindowTitle(tr("About %1").arg(qApp->applicationName()));



    connect(githubButton, SIGNAL(clicked(bool)), this,SLOT(openGithub()));
    connect(twitterButton, SIGNAL(clicked(bool)), this,SLOT(openTwitter()));

    connect(mButtonBox, SIGNAL(accepted()), this, SLOT(close()));

    /* easter egg */
    i_kc_offset = 0;
}

void AboutDialog::addTab(const QString &textFile)
{

    QFile file(textFile);
    QFileInfo info(file);
    if (file.open(QIODevice::ReadOnly))
    {
        QPlainTextEdit * edit = new QPlainTextEdit(this);
        edit->setPlainText(file.readAll());
        mTabWidget->addTab(edit,info.baseName());
        edit->setFrameShape(QFrame::NoFrame);
        edit->setReadOnly(true);
    }

    file.close();


}

void AboutDialog::drawHeader()
{
    int pHeight = 90;
    int pMargin = 15;

    mHeader->setMinimumHeight(pHeight);
    mHeader->setFrameShape(QFrame::StyledPanel);

    mHeader->setContentsMargins(0,0,0,0);

    QPixmap pix(450, pHeight);
    pix.fill(Qt::transparent);
    QPainter painter(&pix);

    int iconY = (pHeight - 64)/2;
    QRect logoRect(pMargin,iconY,64,64);

    painter.setBrush(QBrush(Qt::red));
    painter.drawPixmap(logoRect,QPixmap(":/icons/fastqt.png").scaled(logoRect.width(), logoRect.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QRect titleRect(logoRect.right()+ 10,iconY, 200, pHeight);

    QFont font;
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);
    painter.setPen(QPen(QColor("#555753")));
    painter.drawText(titleRect, Qt::AlignTop, mTitle);
    QFontMetrics fm(font);

    font.setBold(false);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setPen(QPen(Qt::darkGray));
    titleRect.setY(titleRect.y() + fm.height());

    painter.drawText(titleRect, Qt::AlignTop, mSubtitle);

//    QPixmap labsquareLogo(":/icons/labsquare.png");
//    labsquareLogo = labsquareLogo.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation);
//    painter.drawPixmap(pix.rect().right()-labsquareLogo.width() - pMargin , pix.rect().bottom() - labsquareLogo.height() - 15, labsquareLogo);



    mHeader->setPixmap(pix);



}

void AboutDialog::openGithub()
{
    QDesktopServices::openUrl(QUrl("https://github.com/labsquare/fastQt")) ;
}

void AboutDialog::openTwitter()
{
    QDesktopServices::openUrl(QUrl("https://twitter.com/labsquare")) ;

}

bool AboutDialog::event(QEvent *e)
{
    if (e->type() == QEvent::KeyRelease)
     {
        QKeyEvent * keyEvent = dynamic_cast<QKeyEvent*>(e);
        /* easter eggs sequence handling */
        if ( keyEvent->key() == kc[ i_kc_offset ] )
            i_kc_offset++;
        else
            i_kc_offset = 0;

        if ( i_kc_offset == (sizeof( kc ) / sizeof( Qt::Key )) )
        {
            i_kc_offset = 0;
            QDesktopServices::openUrl(QUrl("http://easteregg.labsquare.org/fastqt/enigme.html"));
        }
    }

    return this->QDialog::event(e);
}
