/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-04-30
 * Description : rating icon view item at mouse hover
 *
 * Copyright (C) 2008      by Peter Penz <peter dot penz at gmx dot at>
 * Copyright (C) 2009      by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#include "itemratingoverlay.h"

// Local includes

#include "itemdelegate.h"
#include "itemmodel.h"
#include "itemcategorizedview.h"
#include "ratingwidget.h"

namespace Digikam
{

ItemRatingOverlay::ItemRatingOverlay(QObject* const parent)
    : AbstractWidgetDelegateOverlay(parent)
{
}

RatingWidget* ItemRatingOverlay::ratingWidget() const
{
    return static_cast<RatingWidget*>(m_widget);
}

QWidget* ItemRatingOverlay::createWidget()
{
    RatingWidget* const w = new RatingWidget(parentWidget());
    w->setFading(true);
    w->setTracking(false);

    return w;
}

void ItemRatingOverlay::setActive(bool active)
{
    AbstractWidgetDelegateOverlay::setActive(active);

    if (active)
    {
        connect(ratingWidget(), SIGNAL(signalRatingChanged(int)),
                this, SLOT(slotRatingChanged(int)));

        if (view()->model())
        {
            connect(view()->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                    this, SLOT(slotDataChanged(QModelIndex,QModelIndex)));
        }
    }
    else
    {
        // widget is deleted

        if (view() && view()->model())
        {
            disconnect(view()->model(), nullptr, this, nullptr);
        }
    }
}

void ItemRatingOverlay::visualChange()
{
    if (m_widget &&
        m_widget->isVisible())
    {
        updatePosition();
    }
}

void ItemRatingOverlay::widgetEnterEvent()
{
    widgetEnterNotifyMultiple(m_index);
}

void ItemRatingOverlay::widgetLeaveEvent()
{
    widgetLeaveNotifyMultiple();
}

void ItemRatingOverlay::hide()
{
    delegate()->setRatingEdited(QModelIndex());
    AbstractWidgetDelegateOverlay::hide();
}

void ItemRatingOverlay::updatePosition()
{
    if (!m_index.isValid() || !m_widget)
    {
        return;
    }

    QRect rect = delegate()->ratingRect();

    if (rect.width() > ratingWidget()->maximumVisibleWidth())
    {
        int offset = (rect.width() - ratingWidget()->maximumVisibleWidth()) / 2;
        rect.adjust(offset, 0, -offset, 0);
    }

    QRect visualRect = m_view->visualRect(m_index);
    rect.translate(visualRect.topLeft());

    m_widget->setFixedSize(rect.width() + 1, rect.height() + 1);
    m_widget->move(rect.topLeft());
}

void ItemRatingOverlay::updateRating()
{
    if (!m_index.isValid() || !m_widget)
    {
        return;
    }

    ItemInfo info = ItemModel::retrieveItemInfo(m_index);
    ratingWidget()->setRating(info.rating());
}

void ItemRatingOverlay::slotRatingChanged(int rating)
{
    if (m_widget              &&
        m_widget->isVisible() &&
        m_index.isValid())
    {
        emit ratingEdited(affectedIndexes(m_index), rating);
    }
}

void ItemRatingOverlay::slotEntered(const QModelIndex& index)
{
    AbstractWidgetDelegateOverlay::slotEntered(index);

    // See bug 228810, this is a small workaround
    if (m_widget              &&
        m_widget->isVisible() &&
        m_index.isValid()     &&
        index == m_index)
    {
        ratingWidget()->setVisibleImmediately();
    }

    m_index = index;

    updatePosition();
    updateRating();

    delegate()->setRatingEdited(m_index);
    view()->update(m_index);
}

void ItemRatingOverlay::slotDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    if (m_widget              &&
        m_widget->isVisible() &&
        QItemSelectionRange(topLeft, bottomRight).contains(m_index))
    {
        updateRating();
    }
}

} // namespace Digikam
