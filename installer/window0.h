/*
Copyright (c) 2013, cen (imbacen@gmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef WINDOW0_H
#define WINDOW0_H

#include <QMainWindow>
#ifndef REGISTRY_H
    #include "registry.h"
#endif

namespace Ui {
class Window0;
}

class Window0 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Window0(QWidget *parent = 0);
    ~Window0();
    
private slots:

    void on_backButton_1_clicked();

    void on_backButton_2_clicked();

    void on_nextButton_1_clicked();

    void on_nextButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_nextButton_3_clicked();

    void on_nextButton_4_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_126_clicked();

    void on_pushButton_latest_clicked();

public slots:
    void disableAbort(bool b);

private:
    Ui::Window0 *ui;
    void fail(QString msg);
    bool checkW3PathUnicode(QString w3path, QString exeName);
    bool vcredistRun = false;

signals:
    void startInstall();
    void abortInstall();
};

#endif // WINDOW0_H
