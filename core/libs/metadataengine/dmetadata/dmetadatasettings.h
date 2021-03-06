/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2015-06-22
 * Description : central place for metadata settings
 *
 * Copyright (C) 2015      by Veaceslav Munteanu <veaceslav dot munteanu90 at gmail dot com>
 * Copyright (C) 2015-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_DMETADATA_SETTINGS_H
#define DIGIKAM_DMETADATA_SETTINGS_H

// Qt includes

#include <QObject>

// Local includes

#include "digikam_export.h"
#include "dmetadatasettingscontainer.h"

namespace Digikam
{

class DIGIKAM_EXPORT DMetadataSettings : public QObject
{
    Q_OBJECT

public:

    /**
     * Global container for Metadata settings. All accessor methods are thread-safe.
     */
    static DMetadataSettings* instance();

    /**
     * Returns the current Metadata settings.
     */
    DMetadataSettingsContainer settings() const;

    /**
     * Sets the current Metadata settings and writes them to config.
     */
    void setSettings(const DMetadataSettingsContainer& settings);

Q_SIGNALS:

    void signalSettingsChanged();
    void signalDMetadataSettingsChanged(const DMetadataSettingsContainer& current,
                                        const DMetadataSettingsContainer& previous);

private:

    DMetadataSettings();
    explicit DMetadataSettings(QObject*);
    ~DMetadataSettings() override;

    void readFromConfig();

private:

    class Private;
    Private* const d;

    friend class DMetadataSettingsCreator;
};

} // namespace Digikam

#endif // DIGIKAM_DMETADATA_SETTINGS_H
