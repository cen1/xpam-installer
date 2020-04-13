/********************************************************************************
** Form generated from reading UI file 'window0.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW0_H
#define UI_WINDOW0_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window0
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QLabel *label_1;
    QPushButton *nextButton_1;
    QCheckBox *checkBox_vcredist;
    QWidget *page_2;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QPushButton *nextButton_2;
    QPushButton *backButton_1;
    QWidget *page_3;
    QPushButton *nextButton_3;
    QPushButton *backButton_2;
    QLabel *errlabel_1;
    QLabel *errlabel_2;
    QLabel *errlabel_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_latest;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_latest;
    QPushButton *pushButton_latest;
    QLabel *label_126;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_126;
    QPushButton *pushButton_126;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QWidget *page_4;
    QProgressBar *progressBar;
    QPushButton *nextButton_4;
    QTextBrowser *textBrowser_2;
    QPushButton *pushButton_4;
    QWidget *page_5;
    QLabel *label_4;
    QPushButton *pushButton_3;
    QWidget *page_6;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *Window0)
    {
        if (Window0->objectName().isEmpty())
            Window0->setObjectName(QStringLiteral("Window0"));
        Window0->resize(500, 350);
        Window0->setMinimumSize(QSize(500, 350));
        Window0->setMaximumSize(QSize(500, 350));
        QIcon icon;
        icon.addFile(QStringLiteral(":/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Window0->setWindowIcon(icon);
        Window0->setStyleSheet(QStringLiteral(""));
        Window0->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        centralWidget = new QWidget(Window0);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("#centralWidget {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}\n"
"\n"
"QLabel {\n"
"	color: white;\n"
"}"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 500, 350));
        stackedWidget->setMinimumSize(QSize(500, 350));
        stackedWidget->setMaximumSize(QSize(500, 350));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page_1 = new QWidget();
        page_1->setObjectName(QStringLiteral("page_1"));
        page_1->setStyleSheet(QLatin1String("#page_1 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        label_1 = new QLabel(page_1);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(20, 90, 461, 231));
        nextButton_1 = new QPushButton(page_1);
        nextButton_1->setObjectName(QStringLiteral("nextButton_1"));
        nextButton_1->setGeometry(QRect(410, 320, 75, 23));
        nextButton_1->setStyleSheet(QStringLiteral(""));
        checkBox_vcredist = new QCheckBox(page_1);
        checkBox_vcredist->setObjectName(QStringLiteral("checkBox_vcredist"));
        checkBox_vcredist->setGeometry(QRect(10, 320, 301, 17));
        checkBox_vcredist->setStyleSheet(QStringLiteral("color: white"));
        checkBox_vcredist->setChecked(false);
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setStyleSheet(QLatin1String("#page_2 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 90, 461, 16));
        textBrowser = new QTextBrowser(page_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 110, 461, 191));
        textBrowser->setOpenExternalLinks(true);
        nextButton_2 = new QPushButton(page_2);
        nextButton_2->setObjectName(QStringLiteral("nextButton_2"));
        nextButton_2->setGeometry(QRect(410, 320, 75, 23));
        backButton_1 = new QPushButton(page_2);
        backButton_1->setObjectName(QStringLiteral("backButton_1"));
        backButton_1->setGeometry(QRect(20, 320, 75, 23));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setStyleSheet(QLatin1String("#page_3 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        nextButton_3 = new QPushButton(page_3);
        nextButton_3->setObjectName(QStringLiteral("nextButton_3"));
        nextButton_3->setGeometry(QRect(410, 320, 75, 23));
        backButton_2 = new QPushButton(page_3);
        backButton_2->setObjectName(QStringLiteral("backButton_2"));
        backButton_2->setGeometry(QRect(20, 320, 75, 23));
        errlabel_1 = new QLabel(page_3);
        errlabel_1->setObjectName(QStringLiteral("errlabel_1"));
        errlabel_1->setGeometry(QRect(20, 280, 461, 16));
        errlabel_1->setStyleSheet(QStringLiteral(""));
        errlabel_2 = new QLabel(page_3);
        errlabel_2->setObjectName(QStringLiteral("errlabel_2"));
        errlabel_2->setGeometry(QRect(20, 260, 461, 16));
        errlabel_3 = new QLabel(page_3);
        errlabel_3->setObjectName(QStringLiteral("errlabel_3"));
        errlabel_3->setGeometry(QRect(20, 300, 461, 16));
        layoutWidget = new QWidget(page_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 90, 459, 164));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_latest = new QLabel(layoutWidget);
        label_latest->setObjectName(QStringLiteral("label_latest"));

        verticalLayout->addWidget(label_latest);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_latest = new QLineEdit(layoutWidget);
        lineEdit_latest->setObjectName(QStringLiteral("lineEdit_latest"));
        lineEdit_latest->setMinimumSize(QSize(370, 0));

        horizontalLayout_2->addWidget(lineEdit_latest);

        pushButton_latest = new QPushButton(layoutWidget);
        pushButton_latest->setObjectName(QStringLiteral("pushButton_latest"));

        horizontalLayout_2->addWidget(pushButton_latest);


        verticalLayout->addLayout(horizontalLayout_2);

        label_126 = new QLabel(layoutWidget);
        label_126->setObjectName(QStringLiteral("label_126"));

        verticalLayout->addWidget(label_126);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit_126 = new QLineEdit(layoutWidget);
        lineEdit_126->setObjectName(QStringLiteral("lineEdit_126"));
        lineEdit_126->setMinimumSize(QSize(370, 0));

        horizontalLayout_3->addWidget(lineEdit_126);

        pushButton_126 = new QPushButton(layoutWidget);
        pushButton_126->setObjectName(QStringLiteral("pushButton_126"));

        horizontalLayout_3->addWidget(pushButton_126);


        verticalLayout->addLayout(horizontalLayout_3);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(370, 0));

        horizontalLayout_4->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setStyleSheet(QLatin1String("#page_4 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        progressBar = new QProgressBar(page_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 320, 301, 20));
        progressBar->setStyleSheet(QLatin1String("#progressBar {\n"
"	color:white;\n"
"}"));
        progressBar->setValue(0);
        nextButton_4 = new QPushButton(page_4);
        nextButton_4->setObjectName(QStringLiteral("nextButton_4"));
        nextButton_4->setEnabled(false);
        nextButton_4->setGeometry(QRect(410, 320, 75, 23));
        textBrowser_2 = new QTextBrowser(page_4);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(20, 90, 461, 211));
        pushButton_4 = new QPushButton(page_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(330, 320, 75, 23));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setStyleSheet(QLatin1String("#page_5 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        label_4 = new QLabel(page_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 90, 461, 101));
        pushButton_3 = new QPushButton(page_5);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(410, 320, 75, 23));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        page_6->setStyleSheet(QLatin1String("#page_6 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}"));
        label_5 = new QLabel(page_6);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 90, 161, 16));
        label_6 = new QLabel(page_6);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 120, 461, 16));
        pushButton_5 = new QPushButton(page_6);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(410, 320, 75, 23));
        stackedWidget->addWidget(page_6);
        Window0->setCentralWidget(centralWidget);

        retranslateUi(Window0);

        QMetaObject::connectSlotsByName(Window0);
    } // setupUi

    void retranslateUi(QMainWindow *Window0)
    {
        Window0->setWindowTitle(QApplication::translate("Window0", "Eurobattle.net setup", 0));
        label_1->setText(QApplication::translate("Window0", "<html><head/><body><p><span style=\" font-size:10pt;\">Welcome to eurobattle.net installer<br/></span></p><p><span style=\" font-size:10pt; color:#ffaa00;\">Before install please make sure you have</span><span style=\" font-size:10pt;\">:<br/>-Warcraft III 1.28.5 and/or 1.26a</span></p><p><span style=\" font-size:10pt;\"><br/></span><span style=\" font-size:10pt; color:#ffaa00;\">This program will install</span><span style=\" font-size:10pt;\">:<br/>-W3 loader<br/>-Eurobattle.net Client<br/>-Eurobattle.net GProxy<br/>-Custom channel icons<br/></span></p></body></html>", 0));
        nextButton_1->setText(QApplication::translate("Window0", "Next", 0));
        checkBox_vcredist->setText(QApplication::translate("Window0", "I already have Visual C++ Redistributable x86 version 2015 and 2013", 0));
        label_2->setText(QApplication::translate("Window0", "<html>\n"
"<head>\n"
"<head/>\n"
"<body>\n"
"<p><span style=\" font-size:10pt;\">By clicking Next you agree with the TOS below</span></p>\n"
"</body>\n"
"</html>", 0));
        textBrowser->setHtml(QApplication::translate("Window0", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.1pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Eurobattle.net - World's Largest Warcarft III Community</span><span style=\" font-size:8pt;\"><br /><br /></span><span style=\" font-size:8pt; font-weight:600;\">Terms of Service</span><span style=\" font-size:8pt;\"><br /><br />By installing Eurobattle.net client you agree to </span><a href=\"http://eurobattle.net/threads/128365-The-"
                        "Book-of-Rules\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">Eurobattle.net forum and server rules</span></a><span style=\" font-size:8pt;\">.<br /></span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">What personal data does eurobattle.net collect?</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">What we gather on forum</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-email address</span></p>\n"
"<p"
                        " style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-public IP</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-any personal info you share in your profile or forum posts</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">What do we use this information for</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">To have a functioning forum. We don't analyze this data or "
                        "sell it to anyone, it is used exclusively for the needs of the forum.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">What we gather on desktop client and PvPGN</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-public IP</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-operating system user</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-M"
                        "AC address (anonymized with a hash)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-BIOS name (anonymized with a hash)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">-timestamp of client installation date</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">What do we use this information for</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">To"
                        " prevent the usage of our platform to people who violate our TOS and server rules. We don't analyze this data or sell it to anyone, it is used exclusively against TOS violators.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">In order to make personal data request or account deletion request, visit </span><a href=\"http://eurobattle.net/threads/128365-The-Rule-Book\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">this topic</span></a><span style=\" font-size:8pt;\">. (http://eurobattle.net/threads/208709-GDPR-Personal-information-request-and-account-deletion)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        "><span style=\" font-size:8pt;\"><br /></span><span style=\" font-size:8pt; font-weight:600;\">What is Eurobattle.net client?</span><span style=\" font-size:8pt;\"><br />It is a program that provides a richer experience of our server.<br /><br /></span><span style=\" font-size:8pt; font-weight:600;\">What is a GProxy?</span><span style=\" font-size:8pt;\"><br />It is a program that sits between your game and a host.<br />It allows you to reconnect to the host in case your internet connection dies in the middle of the game.<br />It also allows us to expand the original p2p protocol.<br /><br /></span><span style=\" font-size:8pt; font-weight:600;\">What are custom channel icons?</span><span style=\" font-size:8pt;\"><br />They are additional icons which do not exist on original battle.net servers.<br />We add them to your game archive and they are given as awards for various tournaments and events.<br />You can change your icons with /icon command on server.<br /><br /></span><span style=\" font-size:8pt; font-"
                        "weight:600;\">What is a loader?</span><span style=\" font-size:8pt;\"><br />It is a piece of software that allows you to connect to a PvPGN server with your game.<br /><br /></span><span style=\" font-size:8pt; font-weight:600;\">What is a PvPGN Server?</span><span style=\" font-size:8pt;\"><br />PvPGN (Player vs Player Gaming Network) is a free and open source software project offering emulation of various gaming network servers, one of them being battle.net.<br /><br />NOTES:<br />You must have Warcarft III: The Frozen Throne installed on your PC before running this installer.<br /><br />Sharing any kind of warez, cracks, serial numbers or illegal software will lead to immediate ban from Eurobattle.net.<br />We do not support piracy in any way.<br /><br />Eurobattle.net may collect information about user's computer and any other necessary information in order to prevent a violating user from connecting to Eurobattle.net server; for example, but not exclusively, if in conflict with this TOS, or the server rul"
                        "es or the forum rules.<br /><br />CREDITS:<br />Thanks to the PvPGN and bnetd contributors. https://github.com/pvpgn/pvpgn-server<br />Thanks to Keres for the loader. https://github.com/w3lh/w3l<br /><br />Eurobattle.net Forum @ http://eurobattle.net/<br /></span></p></body></html>", 0));
        nextButton_2->setText(QApplication::translate("Window0", "Next", 0));
        backButton_1->setText(QApplication::translate("Window0", "Back", 0));
        nextButton_3->setText(QApplication::translate("Window0", "Install", 0));
        backButton_2->setText(QApplication::translate("Window0", "Back", 0));
        errlabel_1->setText(QString());
        errlabel_2->setText(QString());
        errlabel_3->setText(QString());
        label_latest->setText(QApplication::translate("Window0", "Select your Warcraft III 1.28.5 directory", 0));
        label->setText(QApplication::translate("Window0", "(optional: needed for custom games and latest W3 features)", 0));
        pushButton_latest->setText(QApplication::translate("Window0", "Open", 0));
        label_126->setText(QApplication::translate("Window0", "Select your Warcraft III 1.26 directory", 0));
        label_7->setText(QApplication::translate("Window0", "(optional: needed for DotA 6.88+ and lagabuse DotA ladder)", 0));
        pushButton_126->setText(QApplication::translate("Window0", "Open", 0));
        label_3->setText(QApplication::translate("Window0", "Where to install Eurobattle.net Client?", 0));
        pushButton_2->setText(QApplication::translate("Window0", "Open", 0));
        nextButton_4->setText(QApplication::translate("Window0", "Next", 0));
        pushButton_4->setText(QApplication::translate("Window0", "Cancel", 0));
        label_4->setText(QApplication::translate("Window0", "<html><head/><body><p>Installation successfull.<br/><br/>If you have any questions or problems feel free to ask for help in our tech support at<br/>eurobattle.net or discord.<br/><br/><br/>Happy gaming!</p></body></html>", 0));
        pushButton_3->setText(QApplication::translate("Window0", "Finish", 0));
        label_5->setText(QApplication::translate("Window0", "Installation failed.", 0));
        label_6->setText(QString());
        pushButton_5->setText(QApplication::translate("Window0", "Finish", 0));
    } // retranslateUi

};

namespace Ui {
    class Window0: public Ui_Window0 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW0_H
