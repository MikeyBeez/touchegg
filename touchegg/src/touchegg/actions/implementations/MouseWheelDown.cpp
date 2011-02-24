/**
 * @file /src/touchegg/actions/implementations/MouseWheelDown.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseWheelDown
 * @author José Expósito
 */
#include "MouseWheelDown.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseWheelDown::MouseWheelDown(const QString& settings) : Action(settings) {
    this->speedCount = 0;
    this->speed      = 4;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->speed = 11 - configSpeed;
        else
            qWarning() << "Error reading MOUSE_WHELL_DOWN settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading MOUSE_WHELL_DOWN settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MouseWheelDown::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    this->speedCount = 0;
}

void MouseWheelDown::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {
    if(this->speedCount >= this->speed) {
        XTestFakeButtonEvent(QX11Info::display(), Button5, true, 0);
        XTestFakeButtonEvent(QX11Info::display(), Button5, false, 0);
        XFlush(QX11Info::display());
        this->speedCount = 0;
    } else {
        this->speedCount++;
    }
}

void MouseWheelDown::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
