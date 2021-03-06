/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-09-12
 * Description : Widget for assignment and confirmation of names for faces
 *
 * Copyright (C) 2010      by Aditya Bhatt <adityabhatt1991 at gmail dot com>
 * Copyright (C) 2010-2011 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2012-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_ASSIGN_NAME_WIDGET_H
#define DIGIKAM_ASSIGN_NAME_WIDGET_H

// Qt includes

#include <QFrame>
#include <QVariant>

namespace Digikam
{

class AddTagsComboBox;
class AddTagsLineEdit;
class CheckableAlbumFilterModel;
class FaceTagsIface;
class ItemInfo;
class TAlbum;
class TaggingAction;
class TagModel;
class TagPropertiesFilterModel;

class AssignNameWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(Mode mode READ mode WRITE setMode)
    Q_PROPERTY(TagEntryWidgetMode tagEntryWidgetMode READ tagEntryWidgetMode WRITE setTagEntryWidgetMode)
    Q_PROPERTY(LayoutMode layoutMode READ layoutMode WRITE setLayoutMode)
    Q_PROPERTY(VisualStyle visualStyle READ visualStyle WRITE setVisualStyle)

public:

    enum Mode
    {
        InvalidMode,
        UnconfirmedEditMode,
        ConfirmedMode,
        ConfirmedEditMode,
        IgnoredMode
    };
    Q_ENUM(Mode)

    enum TagEntryWidgetMode
    {
        InvalidTagEntryWidgetMode,
        AddTagsComboBoxMode,
        AddTagsLineEditMode
    };
    Q_ENUM(TagEntryWidgetMode)

    enum LayoutMode
    {
        InvalidLayout,
        FullLine,
        TwoLines,
        Compact
    };
    Q_ENUM(LayoutMode)

    enum VisualStyle
    {
        InvalidVisualStyle,
        StyledFrame,
        TranslucentDarkRound,
        TranslucentThemedFrameless
    };
    Q_ENUM(VisualStyle)

public:

    /**
     * Please take care: you must set all four modes before usage!
     */
    explicit AssignNameWidget(QWidget* const parent = nullptr);
    ~AssignNameWidget() override;

    /**
     * Set the tag model to use for completion.
     */
    void setModel(TagModel* const model,
                  TagPropertiesFilterModel* const filteredModel,
                  CheckableAlbumFilterModel* const filterModel);
    void setDefaultModel();

    void setMode(Mode mode);
    Mode mode()                             const;

    void setTagEntryWidgetMode(TagEntryWidgetMode mode);
    TagEntryWidgetMode tagEntryWidgetMode() const;

    void setLayoutMode(LayoutMode mode);
    LayoutMode layoutMode()                 const;

    void setVisualStyle(VisualStyle style);
    VisualStyle visualStyle()               const;

    ItemInfo info()                         const;
    QVariant  faceIdentifier()              const;

    /// The combo box or line edit in use, if any
    AddTagsComboBox* comboBox()             const;
    AddTagsLineEdit* lineEdit()             const;

public Q_SLOTS:

    /**
     * The identifying information emitted with the signals
     */
    void setUserData(const ItemInfo& info, const QVariant& faceIdentifier = QVariant());

    /**
     * Sets the suggested (UnconfirmedEditMode) or assigned (ConfirmedMode) tag to be displayed.
     */
    void setCurrentTag(int tagId);
    void setCurrentTag(TAlbum* album);
    void setCurrentFace(const FaceTagsIface& face);

    /**
     * Set a parent tag for suggesting a parent tag for a new tag, and a default action.
     */
    void setParentTag(TAlbum* album);

Q_SIGNALS:

    /**
     * A name has been assigned to the associated face.
     * This can be an existing tag, or a new tag, as described by TaggingAction.
     * For convenience, info() and faceIdentifier() are provided.
     */
    void assigned(const TaggingAction& action, const ItemInfo& info, const QVariant& faceIdentifier);

    /**
     * The suggestion has been rejected and the face will be moved to Unknown.
     * For convenience, info() and faceIdentifier() are provided.
     */
    void rejected(const ItemInfo& info, const QVariant& faceIdentifier);

    /**
     * In IgnoredMode, this signal is emitted when the user clicked on the label
     */
    void ignoredClicked(const ItemInfo& info, const QVariant& faceIdentifier);

    /**
     * In ConfirmedMode, this signal is emitted when the user clicked on the label
     */
    void labelClicked(const ItemInfo& info, const QVariant& faceIdentifier);

    /**
     * An action has been selected. This purely signals user interaction,
     * no fixed decision - mouse hover may be enough to emit this signal.
     * The action may be invalid (user switched back to empty selection).
     */
    void selected(const TaggingAction& action, const ItemInfo& info, const QVariant& faceIdentifier);

protected:

    void keyPressEvent(QKeyEvent* e) override;
    void showEvent(QShowEvent* e)    override;

protected Q_SLOTS:

    void slotConfirm();
    void slotReject();
    void slotActionActivated(const TaggingAction& action);
    void slotActionSelected(const TaggingAction& action);
    void slotIgnoredClicked();
    void slotLabelClicked();

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_ASSIGN_NAME_WIDGET_H
