/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-02-13
 * Description : Layouting photos on a page
 *
 * Copyright (C) 2007-2010 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2006-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_ATKINS_PAGE_LAYOUT_H
#define DIGIKAM_ATKINS_PAGE_LAYOUT_H

// Qt includes

#include <QRectF>
#include <QMap>

namespace DigikamGenericPrintCreatorPlugin
{

/**
 * Implements the algorithm described in
 * "Adaptive Photo Collection Page Layout",
 * C. Brian Atkins
 * Imaging Technology Department
 * HP Labs
 * Palo Alto, CA 94304
 * cbatkins@hpl.hp.com
 *
 * PDF available at this url:
 * hpl.hp.com/research/isl/layout/
 */
class AtkinsPageLayout
{
public:

    /**
     * Create a page layout object which lays out in the given page rectangle
     */
    explicit AtkinsPageLayout(const QRectF& pageRect);
    ~AtkinsPageLayout();

    /**
     * Add an object of size itemSize to this page.
     * The specified key parameter is used to retrieve the layout
     * rectangle with itemRect().
     */
    void addLayoutItem(int key, const QSizeF& itemSize);

    /**
     * Retrieve the layout rectangle for the item that was added with the given key.
     * Call this method to retrieve the result after you have added all items with
     * the addLayoutItem method.
     * The returned rectangle has the same origin as the page rectangle.
     */
    QRectF itemRect(int key);

private:

    void   addLayoutItem(int key, double aspectRatio, double relativeArea);
    double aspectRatio(const QSizeF& size);
    double absoluteArea(const QSizeF& size);

private:

    // Disable
    AtkinsPageLayout(const AtkinsPageLayout&)            = delete;
    AtkinsPageLayout& operator=(const AtkinsPageLayout&) = delete;

private:

    class Private;
    Private* const d;
};

} // Namespace Digikam

#endif // DIGIKAM_ATKINS_PAGE_LAYOUT_H
