/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2018-07-30
 * Description : image editor plugin to rotate an image.
 *
 * Copyright (C) 2018-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "freerotationtoolplugin.h"

// Qt includes

#include <QPointer>

// KDE includes

#include <klocalizedstring.h>
#include <kactioncollection.h>
#include <kxmlguiwindow.h>

// Local includes

#include "editorwindow.h"
#include "freerotationtool.h"

namespace DigikamEditorFreeRotationToolPlugin
{

FreeRotationToolPlugin::FreeRotationToolPlugin(QObject* const parent)
    : DPluginEditor(parent)
{
}

FreeRotationToolPlugin::~FreeRotationToolPlugin()
{
}

QString FreeRotationToolPlugin::name() const
{
    return i18nc("@title", "Free Rotation");
}

QString FreeRotationToolPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon FreeRotationToolPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("transform-rotate"));
}

QString FreeRotationToolPlugin::description() const
{
    return i18nc("@info", "A tool to rotate an image");
}

QString FreeRotationToolPlugin::details() const
{
    return i18nc("@info", "This Image Editor tool can rotate an image with an arbitrary angle.");
}

QList<DPluginAuthor> FreeRotationToolPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Andi Clemens"),
                             QString::fromUtf8("andi dot clemens at gmail dot com"),
                             QString::fromUtf8("(C) 2009-2010"))
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2004-2021"))
            ;
}

void FreeRotationToolPlugin::setup(QObject* const parent)
{
    DPluginAction* const ac = new DPluginAction(parent);
    ac->setIcon(icon());
    ac->setText(i18nc("@action", "Free Rotation..."));
    ac->setObjectName(QLatin1String("editorwindow_transform_freerotation"));
    ac->setActionCategory(DPluginAction::EditorTransform);

    connect(ac, SIGNAL(triggered(bool)),
            this, SLOT(slotFreeRotation()));

    addAction(ac);

    QAction* const point1Action = new QAction(i18nc("@action", "Free Rotation Set Point 1"), parent);
    point1Action->setObjectName(QLatin1String("editorwindow_transform_freerotation_point1"));

    connect(point1Action, SIGNAL(triggered(bool)),
            this, SIGNAL(signalPoint1Action()));

    QAction* const point2Action = new QAction(i18nc("@action", "Free Rotation Set Point 2"), parent);
    point2Action->setObjectName(QLatin1String("editorwindow_transform_freerotation_point2"));

    connect(point2Action, SIGNAL(triggered(bool)),
            this, SIGNAL(signalPoint2Action()));

    QAction* const autoAdjustAction = new QAction(i18nc("@action", "Free Rotation Auto Adjust"), parent);
    autoAdjustAction->setObjectName(QLatin1String("editorwindow_transform_freerotation_autoadjust"));

    connect(autoAdjustAction, SIGNAL(triggered(bool)),
            this, SIGNAL(signalAutoAdjustAction()));

    KXmlGuiWindow* const gui = dynamic_cast<KXmlGuiWindow*>(parent);

    if (gui)
    {
        KActionCollection* const collection = gui->actionCollection();

        collection->addAction(point1Action->objectName(),     point1Action);
        collection->addAction(point2Action->objectName(),     point2Action);
        collection->addAction(autoAdjustAction->objectName(), autoAdjustAction);

        collection->setDefaultShortcut(point1Action,     Qt::CTRL + Qt::SHIFT + Qt::Key_1);
        collection->setDefaultShortcut(point2Action,     Qt::CTRL + Qt::SHIFT + Qt::Key_2);
        collection->setDefaultShortcut(autoAdjustAction, Qt::CTRL + Qt::SHIFT + Qt::Key_R);
    }
}

void FreeRotationToolPlugin::slotFreeRotation()
{
    EditorWindow* const editor = dynamic_cast<EditorWindow*>(sender()->parent());

    if (editor)
    {
        FreeRotationTool* const tool = new FreeRotationTool(editor);
        tool->setPlugin(this);

        connect(this, SIGNAL(signalPoint1Action()),
                tool, SLOT(slotAutoAdjustP1Clicked()));

        connect(this, SIGNAL(signalPoint2Action()),
                tool, SLOT(slotAutoAdjustP2Clicked()));

        connect(this, SIGNAL(signalAutoAdjustAction()),
                tool, SLOT(slotAutoAdjustClicked()));

        editor->loadTool(tool);
    }
}

} // namespace DigikamEditorFreeRotationToolPlugin
