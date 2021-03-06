/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-03-06
 * Description : sub class of QTreeWidget for drag-and-drop support
 *
 * Copyright (C) 2010 by Michael G. Hansen <mike at mghansen dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_GEO_MY_TREE_WIDGET_H
#define DIGIKAM_GEO_MY_TREE_WIDGET_H

// Qt includes

#include <QTreeWidget>
#include <QPersistentModelIndex>

// local includes

#include "myimageitem.h"

class QMouseEvent;

Q_DECLARE_METATYPE(QTreeWidgetItem*)

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:

    explicit MyTreeWidget(QWidget* const parent = nullptr);
    ~MyTreeWidget()                                                override;

protected:

    void startDrag(Qt::DropActions supportedActions)               override;

    // cppcheck-suppress passedByValue
    QMimeData* mimeData(const QList<QTreeWidgetItem*> items) const override;

    // cppcheck-suppress passedByValue
    virtual QMimeData* mimeData(const QModelIndexList items) const;

private:

    class Private;
    Private* const d;
};

#endif // DIGIKAM_GEO_MY_TREE_WIDGET_H
