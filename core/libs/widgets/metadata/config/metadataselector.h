/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-07-16
 * Description : metadata selector.
 *
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_META_DATA_SELECTOR_H
#define DIGIKAM_META_DATA_SELECTOR_H

// Qt includes

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QStringList>

// Local includes

#include "digikam_export.h"
#include "searchtextbar.h"
#include "dmetadata.h"

namespace Digikam
{

class MdKeyListViewItem;
class MetadataSelectorView;

class DIGIKAM_EXPORT MetadataSelectorItem : public QTreeWidgetItem
{
public:

    MetadataSelectorItem(MdKeyListViewItem* const parent,
                         const QString& key,
                         const QString& title,
                         const QString& desc);
    ~MetadataSelectorItem()    override;

    QString key()        const;
    QString mdKeyTitle() const;

private:

    QString            m_key;
    MdKeyListViewItem* m_parent;

private:

    Q_DISABLE_COPY(MetadataSelectorItem)
};

// ------------------------------------------------------------------------------------

class DIGIKAM_EXPORT MetadataSelector : public QTreeWidget
{
    Q_OBJECT

public:

    explicit MetadataSelector(MetadataSelectorView* const parent);
    ~MetadataSelector() override;

    void setTagsMap(const DMetadata::TagsMap& map);

    void setcheckedTagsList(const QStringList& list);
    QStringList checkedTagsList();

    void clearSelection();
    void selectAll()    override;

private:

    MetadataSelectorView* m_parent;
};

// ------------------------------------------------------------------------------------

class DIGIKAM_EXPORT MetadataSelectorView : public QWidget
{
    Q_OBJECT

public:

    enum ControlElement
    {
        SelectAllBtn = 0x01,
        ClearBtn     = 0x02,
        DefaultBtn   = 0x04,
        SearchBar    = 0x08
    };
    Q_DECLARE_FLAGS(ControlElements, ControlElement)

    enum Backend
    {
        Exiv2Backend = 0,
        ExifToolBackend
    };

public:

    explicit MetadataSelectorView(QWidget* const parent, Backend be);
    ~MetadataSelectorView()               override;

    int itemsCount()                const;

    void setTagsMap(const DMetadata::TagsMap& map);

    void setcheckedTagsList(const QStringList& list);

    void setDefaultFilter(const QStringList& list);
    QStringList defaultFilter()     const;

    QStringList checkedTagsList()   const;

    Backend backend()               const;

    void setControlElements(ControlElements controllerMask);

    void clearSelection();
    void selectAll();
    void selectDefault();

private Q_SLOTS:

    void slotSearchTextChanged(const SearchTextSettings&);
    void slotDeflautSelection();
    void slotSelectAll();
    void slotClearSelection();

private:

    void cleanUpMdKeyItem();

private:

    // Disable.
    MetadataSelectorView() = delete;

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

Q_DECLARE_OPERATORS_FOR_FLAGS(Digikam::MetadataSelectorView::ControlElements)

#endif // DIGIKAM_META_DATA_SELECTOR_H
