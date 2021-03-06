/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-05-29
 * Description : Thumbnail DB schema update
 *
 * Copyright (C) 2007-2009 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2010-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_THUMBS_DB_SCHEMA_UPDATER_H
#define DIGIKAM_THUMBS_DB_SCHEMA_UPDATER_H

// Local includes

#include "digikam_export.h"

namespace Digikam
{

class ThumbsDbAccess;
class InitializationObserver;

class DIGIKAM_EXPORT ThumbsDbSchemaUpdater
{
public:

    static int schemaVersion();

public:

    explicit ThumbsDbSchemaUpdater(ThumbsDbAccess* const dbAccess);
    ~ThumbsDbSchemaUpdater();

    bool update();
    void setObserver(InitializationObserver* const observer);

private:

    bool startUpdates();
    bool makeUpdates();
    bool createDatabase();
    bool createTables();
    bool createIndices();
    bool createTriggers();
    bool updateV1ToV2();
    bool updateV2ToV3();

private:

    // Disable
    ThumbsDbSchemaUpdater(const ThumbsDbSchemaUpdater&)            = delete;
    ThumbsDbSchemaUpdater& operator=(const ThumbsDbSchemaUpdater&) = delete;

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_THUMBS_DB_SCHEMA_UPDATER_H
