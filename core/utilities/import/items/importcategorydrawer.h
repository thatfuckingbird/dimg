/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2012-07-17
 * Description : Qt item view for images - category drawer
 *
 * Copyright (C) 2012 by Islam Wazery <wazery at ubuntu dot com>
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

#ifndef DIGIKAM_IMPORT_CATEGORY_DRAWER_H
#define DIGIKAM_IMPORT_CATEGORY_DRAWER_H

// Qt includes

#include <QStyleOptionViewItem>

// Local includes

#include "dcategorydrawer.h"

namespace Digikam
{

class ImportCategorizedView;

class ImportCategoryDrawer : public DCategoryDrawer
{
    Q_OBJECT

public:

    explicit ImportCategoryDrawer(ImportCategorizedView* const parent);
    ~ImportCategoryDrawer()                                                                   override;

    void setLowerSpacing(int spacing);
    void setDefaultViewOptions(const QStyleOptionViewItem& option);
    void invalidatePaintingCache();

    int  categoryHeight(const QModelIndex& index, const QStyleOption& option)           const override;
    void drawCategory(const QModelIndex& index, int sortRole,
                      const QStyleOption& option, QPainter* painter)                    const override;
    virtual int  maximumHeight()                                                        const;

private:

    void updateRectsAndPixmaps(int width);
    void viewHeaderText(const QModelIndex& index, QString* header, QString* subLine)    const;
    void textForFormat(const QModelIndex& index, QString* header, QString* subLine)     const;
    void textForDate(const QModelIndex& index, QString* header, QString* subLine)       const;

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_IMPORT_CATEGORY_DRAWER_H
