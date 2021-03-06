/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-01-16
 * Description : categorize item view based on DCategorizedView
 *
 * Copyright (C) 2007      by Rafael Fernández López <ereslibre at kde dot org>
 * Copyright (C) 2007      by John Tapsell <tapsell at kde dot org>
 * Copyright (C) 2009-2012 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2011-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_DCATEGORIZED_SORT_FILTER_PROXY_MODEL_PRIVATE_H
#define DIGIKAM_DCATEGORIZED_SORT_FILTER_PROXY_MODEL_PRIVATE_H

#include "dcategorizedsortfilterproxymodel.h"

// Qt includes

#include <QCollator>

namespace Digikam
{

class DCategorizedSortFilterProxyModel;

class Q_DECL_HIDDEN DCategorizedSortFilterProxyModel::Private
{
public:

    explicit Private()
      : sortColumn                       (0),
        sortOrder                        (Qt::AscendingOrder),
        categorizedModel                 (false),
        sortCategoriesByNaturalComparison(true)
    {
        collator.setNumericMode(true);
        collator.setCaseSensitivity(Qt::CaseSensitive);
    }

    ~Private()
    {
    }

public:

    int           sortColumn;
    Qt::SortOrder sortOrder;
    bool          categorizedModel;
    bool          sortCategoriesByNaturalComparison;
    QCollator     collator;
};

} // namespace Digikam

#endif // DIGIKAM_DCATEGORIZED_SORT_FILTER_PROXY_MODEL_PRIVATE_H
