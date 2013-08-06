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

#include "install.h"

Install::Install()
{
}

void Install::setw3path(QString w3path)
{
    this->w3path=w3path;
}
void Install::seteuropath(QString europath)
{
    this->europath=europath;
}

void Install::startInstall()
{
    emit sendInfo("Starting installation process");
    updateW3();
    if (isAbort)
    {
        rupdateW3();
    }
    updateMPQ();
    if (isAbort)
    {
        rupdateW3();
        rupdateMPQ();
    }
    applyLoaders();
    if (isAbort)
    {
        rupdateW3();
        rupdateMPQ();
        rapplyLoaders();
    }
    updateGateways();
    if (isAbort)
    {
        rupdateW3();
        rupdateMPQ();
        rapplyLoaders();
        rupdateGateways();
    }
    installEurobattle();
    if (isAbort)
    {
        rupdateW3();
        rupdateMPQ();
        rapplyLoaders();
        rupdateGateways();
        rinstallEurobattle();
    }
    emit finished(true);
}

void Install::abortInstall()
{
    emit sendInfo("Aborting install");
    isAbort=true;
}

void Install::updateW3()
{
    emit sendInfo("Updating Warcraft III");

}
void Install::updateMPQ()
{

}

void Install::applyLoaders()
{

}

void Install::updateGateways()
{

}

void Install::installEurobattle()
{

}

void Install::rupdateW3()
{

}

void Install::rupdateMPQ()
{

}

void Install::rapplyLoaders()
{

}

void Install::rupdateGateways()
{

}

void Install::rinstallEurobattle()
{

}
