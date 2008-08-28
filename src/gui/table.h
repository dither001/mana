/*
 *  The Mana World
 *  Copyright 2008 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  The Mana World is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Mana World; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef TMW_TABLE_H_
#define TMW_TABLE_H_

#include <vector>

#include <guichan/gui.hpp>
#include <guichan/keylistener.hpp>
#include <guichan/mouselistener.hpp>
#include <guichan/platform.hpp>
#include <guichan/widget.hpp>

#include "table_model.h"
#include "../guichanfwd.h"

class GuiTableActionListener;

/**
 * A table, with rows and columns made out of sub-widgets. Largely inspired by (and can be thought of as a generalisation of)
 * the guichan listbox implementation.
 *
 * Normally you want this within a ScrollArea.
 *
 * \ingroup GUI
 */
class GuiTable : public gcn::Widget,
                 public gcn::MouseListener,
                 public gcn::KeyListener,
                 public TableModelListener
{
    friend class GuiTableActionListener; // so that the action listener can call distributeActionEvent
public:
    GuiTable(TableModel * initial_model = NULL);

    virtual ~GuiTable(void);

    /**
     * Retrieves the active table model
     */
    TableModel *getModel(void) const;

    /**
     * Sets the table model
     *
     * Note that actions issued by widgets returned from the model will update the table
     * selection, but only AFTER any event handlers installed within the widget have been
     *triggered. To be notified after such an update, add an action listener to the table
     * instead.
     */
    void setModel(TableModel *m);

    void setSelected(int row, int column);

    int getSelectedRow(void);

    int getSelectedColumn(void);

    gcn::Rectangle getChildrenArea(void);

    /**
     * Toggle whether to use linewise selection mode, in which the table selects an entire
     * line at a time, rather than a single cell.
     *
     * Note that column information is tracked even in linewise selection mode; this mode
     * therefore only affects visualisation.
     *
     * Disabled by default.
     *
     * \param linewise: Whether to enable linewise selection mode
     */
    void setLinewiseSelection(bool linewise);

    // Inherited from Widget
    virtual void draw(gcn::Graphics* graphics);

    virtual void logic(void);

    virtual gcn::Widget *getWidgetAt(int x, int y);

    virtual void moveToTop(gcn::Widget *child);

    virtual void moveToBottom(gcn::Widget *child);

    virtual void _setFocusHandler(gcn::FocusHandler* focusHandler);

    // Inherited from KeyListener
    virtual void keyPressed(gcn::KeyEvent& keyEvent);


    // Inherited from MouseListener
    virtual void mousePressed(gcn::MouseEvent& mouseEvent);

    virtual void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent);

    virtual void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent);
        
    virtual void mouseDragged(gcn::MouseEvent& mouseEvent);

    // Constraints inherited from TableModelListener
    virtual void modelUpdated(bool);

protected:

    virtual void uninstallActionListeners(void); // frees all action listeners on inner widgets
    virtual void installActionListeners(void); // installs all action listeners on inner widgets

    virtual int getRowHeight(void);
    virtual int getColumnWidth(int i);
    
private:

    int getRowForY(int y); // -1 on error
    int getColumnForX(int x); // -1 on error
    void recomputeDimensions(void);
    bool mLinewiseMode;

    TableModel *mModel;

    int mSelectedRow;
    int mSelectedColumn;

    int mPopFramesNr; // Number of frames to skip upwards when drawing the selected widget

    gcn::Widget *mTopWidget; // If someone moves a fresh widget to the top, we must display it

    std::vector<GuiTableActionListener *> action_listeners; // Vector for compactness; used as a list in practice.
};


#endif /* !defined(TMW_TABLE_H_) */