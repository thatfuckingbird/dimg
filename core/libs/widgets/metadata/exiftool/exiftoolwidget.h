/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2021-04-18
 * Description : ExifTool metadata widget.
 *
 * Copyright (C) 2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_EXIF_TOOL_WIDGET_H
#define DIGIKAM_EXIF_TOOL_WIDGET_H

// Qt includes

#include <QWidget>
#include <QStackedWidget>
#include <QString>
#include <QUrl>
#include <QAction>

// Local includes

#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_EXPORT ExifToolWidget : public QStackedWidget
{
    Q_OBJECT

public:

    enum TagFilters
    {
        NONE = 0,
        PHOTO,
        CUSTOM
    };

public:

    explicit ExifToolWidget(QWidget* const parent);
    ~ExifToolWidget() override;

    void loadFromUrl(const QUrl& url);

    QString getCurrentItemKey() const;
    void    setCurrentItemByKey(const QString& itemKey);

    QStringList getTagsFilter() const;
    void        setTagsFilter(const QStringList& list);

    int     getMode()           const;
    void    setMode(int mode);

Q_SIGNALS:

    void signalSetupExifTool();
    void signalSetupMetadataFilters();

private Q_SLOTS:

    void slotLoadingResult(bool ok);
    void slotPreLoadingTimerDone();
    void slotCopy2Clipboard();
    void slotPrintMetadata();
    void slotSaveMetadataToFile();
    void slotFilterChanged(QAction*);

private:

    void setup();
    QString metadataToText() const;
    void buildView();

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_EXIF_TOOL_WIDGET_H
