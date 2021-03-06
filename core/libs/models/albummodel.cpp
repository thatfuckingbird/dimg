/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2008-03-22
 * Description : Qt Model for Albums
 *
 * Copyright (C) 2008-2011 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#include "albummodel.h"

// Qt includes

#include <QDir>
#include <QIcon>
#include <QLocale>
#include <QPainter>
#include <QApplication>

// KDE includes

#include <klocalizedstring.h>

// Local includes

#include "digikam_debug.h"
#include "albummanager.h"
#include "applicationsettings.h"
#include "albumthumbnailloader.h"
#include "facetags.h"

namespace Digikam
{

AlbumModel::AlbumModel(RootAlbumBehavior rootBehavior, QObject* const parent)
    : AbstractCheckableAlbumModel(Album::PHYSICAL,
                                  AlbumManager::instance()->findPAlbum(0),
                                  rootBehavior, parent)
{
    m_columnHeader = i18n("Albums");
    setupThumbnailLoading();

    connect(AlbumManager::instance(), SIGNAL(signalPAlbumsDirty(QMap<int,int>)),
            this, SLOT(setCountMap(QMap<int,int>)));

    setCountMap(AlbumManager::instance()->getPAlbumsCount());
}

AlbumModel::~AlbumModel()
{
}

PAlbum* AlbumModel::albumForIndex(const QModelIndex& index) const
{
    return static_cast<PAlbum*>(AbstractCheckableAlbumModel::albumForIndex(index));
}

QVariant AlbumModel::decorationRoleData(Album* album) const
{
    // asynchronous signals are handled by parent class

    QPixmap thumb = AlbumThumbnailLoader::instance()->getAlbumThumbnailDirectly(static_cast<PAlbum*>(album));
    int size      = ApplicationSettings::instance()->getTreeViewIconSize();

    double ratio  = thumb.devicePixelRatio();
    int rsize     = qRound((double)size * ratio);
    thumb         = thumb.scaled(rsize, rsize, Qt::KeepAspectRatio,
                                               Qt::SmoothTransformation);

    QPixmap pix(rsize, rsize);
    pix.fill(Qt::transparent);
    pix.setDevicePixelRatio(ratio);

    QPainter p(&pix);
    p.drawPixmap((rsize - thumb.width())  / 2,
                 (rsize - thumb.height()) / 2, thumb);
    p.end();

    prepareAddExcludeDecoration(album, pix);

    return pix;
}

Album* AlbumModel::albumForId(int id) const
{
    return AlbumManager::instance()->findPAlbum(id);
}

QVariant AlbumModel::albumData(Album* a, int role) const
{
    if ((role == Qt::DisplayRole) &&
         showCount()              &&
         a->isTrashAlbum())
    {
        PAlbum* const palbum = AlbumManager::instance()->findPAlbum(a->parent()->id());

        if (palbum)
        {
            QString path = palbum->folderPath();
            path.append(QLatin1String(".dtrash/files"));
            QDir dir(path, QLatin1String(""), QDir::Unsorted, QDir::Files);

            return QString::fromUtf8("%1 (%2)").arg(albumName(a)).arg(dir.count());
        }
    }

    return AbstractCheckableAlbumModel::albumData(a, role);
}

// ------------------------------------------------------------------

TagModel::TagModel(RootAlbumBehavior rootBehavior, QObject* const parent)
    : AbstractCheckableAlbumModel(Album::TAG,
                                  AlbumManager::instance()->findTAlbum(0),
                                  rootBehavior, parent)
{
    m_columnHeader = i18n("Tags");
    setupThumbnailLoading();

    connect(AlbumManager::instance(), SIGNAL(signalTAlbumsDirty(QMap<int,int>)),
            this, SLOT(setCountMap(QMap<int,int>)));

    setCountMap(AlbumManager::instance()->getTAlbumsCount());
}

void TagModel::setColumnHeader(const QString& header)
{
    m_columnHeader = header;
}

TAlbum* TagModel::albumForIndex(const QModelIndex& index) const
{
    return static_cast<TAlbum*>(AbstractCheckableAlbumModel::albumForIndex(index));
}

QVariant TagModel::albumData(Album* a, int role) const
{
    if ((role == Qt::DisplayRole)                    &&
        !a->isRoot()                                 &&
        m_unconfirmedFaceCount.contains(a->id())     &&
        (a->id() != FaceTags::unknownPersonTagId()))
    {
        QString res = AbstractCheckableAlbumModel::albumData(a, role).toString() +
                      i18ncp("@info: unconfirmed faces in album", " (%1 new)", " (%1 new)",
                             m_unconfirmedFaceCount.value(a->id()));

        return res;
    }

    return AbstractCheckableAlbumModel::albumData(a, role);
}

QVariant TagModel::decorationRoleData(Album* album) const
{
    TAlbum* const tagAlbum = static_cast<TAlbum*>(album);

    if (isFaceTagModel() || tagAlbum->hasProperty(TagPropertyName::person()))
    {
        QPixmap face = AlbumThumbnailLoader::instance()->getFaceThumbnailDirectly(tagAlbum);
        int size     = isFaceTagModel() ? ApplicationSettings::instance()->getTreeViewFaceSize()
                                        : ApplicationSettings::instance()->getTreeViewIconSize();

        double ratio = face.devicePixelRatio();
        int rsize    = qRound((double)size * ratio);
        face         = face.scaled(rsize, rsize, Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation);

        QPixmap pix(rsize, rsize);
        pix.fill(Qt::transparent);
        pix.setDevicePixelRatio(ratio);

        QPainter p(&pix);
        p.drawPixmap((rsize - face.width())  / 2,
                     (rsize - face.height()) / 2, face);
        p.end();

        prepareAddExcludeDecoration(album, pix);

        return pix;
    }
    else
    {
        QPixmap pix = AlbumThumbnailLoader::instance()->getTagThumbnailDirectly(tagAlbum);
        prepareAddExcludeDecoration(album, pix);

        return pix;
    }
}

QVariant TagModel::fontRoleData(Album* a) const
{
    if (m_unconfirmedFaceCount.contains(a->id())  &&
        (a->id() != FaceTags::unknownPersonTagId()))
    {
        QFont font;
        font.setBold(true);

        return font;
    }

    return QVariant();
}

Album* TagModel::albumForId(int id) const
{
    return AlbumManager::instance()->findTAlbum(id);
}

void TagModel::activateFaceTagModel()
{
    disconnect(AlbumManager::instance(), SIGNAL(signalTAlbumsDirty(QMap<int,int>)),
               this, SLOT(setCountMap(QMap<int,int>)));

    connect(AlbumManager::instance(), &AlbumManager::signalFaceCountsDirty,
            this, [=](const QMap<int, int>& faceCount,
                      const QMap<int, int>& uFaceCount,
                      const QList<int>& toUpdatedFaces)
        {
            setCountMap(faceCount);
            m_unconfirmedFaceCount = uFaceCount;

            foreach (int id, toUpdatedFaces)
            {
                Album* const album = albumForId(id);

                if (!album)
                {
                    continue;
                }

                QModelIndex index = indexForAlbum(album);

                if (!index.isValid())
                {
                    continue;
                }

                emit dataChanged(index, index);
            }
        }
    );

    setFaceTagModel(true);
    setCountMap(AlbumManager::instance()->getFaceCount());
}

bool TagModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    TAlbum* const talbum = albumForIndex(index);

    if (talbum && talbum->isInternalTag())
    {
        return false;
    }

    return AbstractCheckableAlbumModel::setData(index, value, role);
}

// ------------------------------------------------------------------

SearchModel::SearchModel(QObject* const parent)
    : AbstractCheckableAlbumModel(Album::SEARCH,
                                  AlbumManager::instance()->findSAlbum(0),
                                  IgnoreRootAlbum, parent)
{
    m_columnHeader = i18n("Searches");

    setShowCount(false);

    // handle search icons

    albumSettingsChanged();

    connect(ApplicationSettings::instance(), SIGNAL(setupChanged()),
            this, SLOT(albumSettingsChanged()));
}

SAlbum* SearchModel::albumForIndex(const QModelIndex& index) const
{
    return static_cast<SAlbum*>(AbstractCheckableAlbumModel::albumForIndex(index));
}

void SearchModel::setReplaceNames(const QHash<QString, QString>& replaceNames)
{
    m_replaceNames = replaceNames;
}

void SearchModel::addReplaceName(const QString& technicalName, const QString& userVisibleName)
{
    m_replaceNames.insert(technicalName, userVisibleName);
}

void SearchModel::setPixmapForNormalSearches(const QPixmap& pix)
{
    m_pixmaps.insert(-1, pix);
}

void SearchModel::setDefaultPixmap(const QPixmap& pix)
{
    m_pixmaps.insert(-2, pix);
}

void SearchModel::setPixmapForTimelineSearches(const QPixmap& pix)
{
    m_pixmaps.insert(DatabaseSearch::TimeLineSearch, pix);
}

void SearchModel::setPixmapForHaarSearches(const QPixmap& pix)
{
    m_pixmaps.insert(DatabaseSearch::HaarSearch, pix);
}

void SearchModel::setPixmapForMapSearches(const QPixmap& pix)
{
    m_pixmaps.insert(DatabaseSearch::MapSearch, pix);
}

void SearchModel::setPixmapForDuplicatesSearches(const QPixmap& pix)
{
    m_pixmaps.insert(DatabaseSearch::DuplicatesSearch, pix);
}

QVariant SearchModel::albumData(Album* a, int role) const
{
    if      ((role == Qt::DisplayRole) || (role == AlbumTitleRole) || (role == Qt::ToolTipRole))
    {
        SAlbum* const salbum = static_cast<SAlbum*>(a);
        QString title        = a->title();
        QString displayTitle = salbum->displayTitle();

        return m_replaceNames.value(title, displayTitle);
    }
    else if (role == Qt::DecorationRole)
    {
        SAlbum* const salbum = static_cast<SAlbum*>(a);
        QPixmap pixmap       = m_pixmaps.value(salbum->searchType());

        if (pixmap.isNull() && salbum->isNormalSearch())
        {
            pixmap = m_pixmaps.value(-1);
        }

        if (pixmap.isNull())
        {
            pixmap = m_pixmaps.value(-2);
        }

        return pixmap;
    }

    return AbstractCheckableAlbumModel::albumData(a, role);
}

Album* SearchModel::albumForId(int id) const
{
    return AlbumManager::instance()->findSAlbum(id);
}

void SearchModel::albumSettingsChanged()
{
    setPixmapForMapSearches(QIcon::fromTheme(QLatin1String("globe")).pixmap(ApplicationSettings::instance()->getTreeViewIconSize()));
    setPixmapForHaarSearches(QIcon::fromTheme(QLatin1String("tools-wizard")).pixmap(ApplicationSettings::instance()->getTreeViewIconSize()));
    setPixmapForNormalSearches(QIcon::fromTheme(QLatin1String("edit-find")).pixmap(ApplicationSettings::instance()->getTreeViewIconSize()));
    setPixmapForTimelineSearches(QIcon::fromTheme(QLatin1String("chronometer")).pixmap(ApplicationSettings::instance()->getTreeViewIconSize()));
}

// ------------------------------------------------------------------

DateAlbumModel::DateAlbumModel(QObject* const parent)
    : AbstractCountingAlbumModel(Album::DATE,
                                 AlbumManager::instance()->findDAlbum(0),
                                 IgnoreRootAlbum, parent)
{
    m_columnHeader = i18n("Dates");

    connect(AlbumManager::instance(), SIGNAL(signalDAlbumsDirty(QMap<YearMonth,int>)),
            this, SLOT(setYearMonthMap(QMap<YearMonth,int>)));

    setYearMonthMap(AlbumManager::instance()->getDAlbumsCount());

    setup();
}

DAlbum* DateAlbumModel::albumForIndex(const QModelIndex& index) const
{
    return (static_cast<DAlbum*>(AbstractCountingAlbumModel::albumForIndex(index)));
}

QModelIndex DateAlbumModel::monthIndexForDate(const QDate& date) const
{
    // iterate over all years

    for (int yearIndex = 0 ; yearIndex < rowCount() ; ++yearIndex)
    {
        QModelIndex year        = index(yearIndex, 0);
        DAlbum* const yearAlbum = albumForIndex(year);

        // do not search through months if we are sure, that the year already
        // does not match

        if (yearAlbum                            &&
            (yearAlbum->range() == DAlbum::Year) &&
            (yearAlbum->date().year() != date.year()))
        {
            continue;
        }

        // search the album with the correct month

        for (int monthIndex = 0 ; monthIndex < rowCount(year) ; ++monthIndex)
        {
            QModelIndex month        = index(monthIndex, 0, year);
            DAlbum* const monthAlbum = albumForIndex(month);

            if (monthAlbum                                  &&
                (monthAlbum->range() == DAlbum::Month)      &&
                (monthAlbum->date().year() == date.year())  &&
                (monthAlbum->date().month() == date.month()))
            {
                return month;
            }
        }

    }

    return QModelIndex();
}

void DateAlbumModel::setPixmaps(const QPixmap& forYearAlbums, const QPixmap& forMonthAlbums)
{
    m_yearPixmap  = forYearAlbums;
    m_monthPixmap = forMonthAlbums;
}

QString DateAlbumModel::albumName(Album* album) const
{
    DAlbum* const dalbum = static_cast<DAlbum*>(album);

    if (dalbum->range() == DAlbum::Year)
    {
        return QString::number(dalbum->date().year());
    }
    else
    {
        return QLocale().standaloneMonthName(dalbum->date().month(), QLocale::LongFormat);
    }
}

QVariant DateAlbumModel::decorationRoleData(Album* album) const
{
    DAlbum* const dalbum = static_cast<DAlbum*>(album);

    if (dalbum->range() == DAlbum::Year)
    {
        return m_yearPixmap;
    }
    else
    {
        return m_monthPixmap;
    }
}

QVariant DateAlbumModel::sortRoleData(Album* a) const
{
    DAlbum* const dalbum = static_cast<DAlbum*>(a);

    if (dalbum)
    {
        return dalbum->date();
    }

    qCDebug(DIGIKAM_GENERAL_LOG) << "There must be a data album.";

    return QDate();
}

Album* DateAlbumModel::albumForId(int id) const
{
    return AlbumManager::instance()->findDAlbum(id);
}

void DateAlbumModel::setYearMonthMap(const QMap<YearMonth, int>& yearMonthMap)
{
    AlbumIterator it(rootAlbum());

    QMap<int, int> albumToCountMap;

    while (it.current())
    {
        DAlbum* const dalbum = static_cast<DAlbum*>(*it);
        QDate date           = dalbum->date();

        switch (dalbum->range())
        {
            case DAlbum::Month:
            {
                QMap<YearMonth, int>::const_iterator it2 = yearMonthMap.constFind(YearMonth(date.year(), date.month()));

                if (it2 != yearMonthMap.constEnd())
                {
                    albumToCountMap.insert((*it)->id(), it2.value());
                }

                break;
            }

            case DAlbum::Year:
            {
                // a year itself cannot contain images and therefore always has count 0

                albumToCountMap.insert((*it)->id(), 0);
                break;
            }

            default:
            {
                qCDebug(DIGIKAM_GENERAL_LOG) << "Untreated DAlbum range " << dalbum->range();
                albumToCountMap.insert((*it)->id(), 0);
                break;
            }
        }

        ++it;
    }

    setCountMap(albumToCountMap);
}

} // namespace Digikam
