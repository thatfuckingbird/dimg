/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2000-12-05
 * Description : filter view for the right sidebar
 *
 * Copyright (C) 2009-2010 by Johannes Wienke <languitar at semipol dot de>
 * Copyright (C) 2010-2011 by Andi Clemens <andi dot clemens at gmail dot com>
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

#ifndef DIGIKAM_TAG_FILTER_VIEW_H
#define DIGIKAM_TAG_FILTER_VIEW_H

// Qt includes

#include <QWidget>

// Local includes

#include "tagcheckview.h"

namespace Digikam
{

class TagModel;

/**
 * A view to filter the currently displayed album by tags.
 *
 * @author jwienke
 */
class TagFilterView : public TagCheckView
{
    Q_OBJECT

public:

    /**
     * Constructor.
     *
     * @param parent the parent for qt parent child mechanism
     * @param tagFilterModel tag model to work on
     */
    explicit TagFilterView(QWidget* const parent, TagModel* const tagFilterModel);

    /**
     * Destructor.
     */
    ~TagFilterView()                                                                      override;

private Q_SLOTS:

    void slotDeleteTagByContextMenu(TAlbum* tag);

protected:

    void addCustomContextMenuActions(ContextMenuHelper& cmh, Album* album)                override;
    void handleCustomContextMenuAction(QAction* action, const AlbumPointer<Album>& album) override;

private:

    class Private;
    Private* const d;
};

} // nameSpace Digikam

#endif // DIGIKAM_TAG_FILTER_VIEW_H
