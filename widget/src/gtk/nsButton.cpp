/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#include <gtk/gtk.h>

#include "nsGtkEventHandler.h"

#include "nsButton.h"
#include "nsString.h"

NS_IMPL_ADDREF_INHERITED(nsButton, nsWidget)
NS_IMPL_RELEASE_INHERITED(nsButton, nsWidget)

//-------------------------------------------------------------------------
//
// nsButton constructor
//
//-------------------------------------------------------------------------
nsButton::nsButton() : nsWidget() , nsIButton()
{
}

//-------------------------------------------------------------------------
//
// Create the native Button widget
//
//-------------------------------------------------------------------------
NS_METHOD nsButton::CreateNative(GtkWidget *parentWindow)
{
  mWidget = gtk_button_new_with_label("");
  gtk_widget_set_name(mWidget, "nsButton");
  return NS_OK;
}

//-------------------------------------------------------------------------
//
// nsButton destructor
//
//-------------------------------------------------------------------------
nsButton::~nsButton()
{
}

void nsButton::InitCallbacks(char * aName)
{
  InstallButtonPressSignal(mWidget);
  InstallButtonReleaseSignal(mWidget);

  InstallEnterNotifySignal(mWidget);
  InstallLeaveNotifySignal(mWidget);

  // These are needed so that the events will go to us and not our parent.
  AddToEventMask(mWidget,
                 GDK_BUTTON_PRESS_MASK |
                 GDK_BUTTON_RELEASE_MASK |
                 GDK_ENTER_NOTIFY_MASK |
                 GDK_EXPOSURE_MASK |
                 GDK_FOCUS_CHANGE_MASK |
                 GDK_KEY_PRESS_MASK |
                 GDK_KEY_RELEASE_MASK |
                 GDK_LEAVE_NOTIFY_MASK |
                 GDK_POINTER_MOTION_MASK);
}

/**
 * Implement the standard QueryInterface for NS_IWIDGET_IID and NS_ISUPPORTS_IID
 * @modify gpk 8/4/98
 * @param aIID The name of the class implementing the method
 * @param _classiiddef The name of the #define symbol that defines the IID
 * for the class (e.g. NS_ISUPPORTS_IID)
 *
*/
nsresult nsButton::QueryInterface(const nsIID& aIID, void** aInstancePtr)
{
    if (NULL == aInstancePtr) {
        return NS_ERROR_NULL_POINTER;
    }

    if (aIID.Equals(nsIButton::GetIID())) {
        *aInstancePtr = (void*) ((nsIButton*)this);
        AddRef();
        return NS_OK;
    }

    return nsWidget::QueryInterface(aIID, aInstancePtr);
}


//-------------------------------------------------------------------------
//
// Set this button label
//
//-------------------------------------------------------------------------
NS_METHOD nsButton::SetLabel(const nsString& aText)
{
  NS_ALLOC_STR_BUF(label, aText, 256);

  gtk_label_set(GTK_LABEL(GTK_BIN (mWidget)->child), label);

  NS_FREE_STR_BUF(label);
  return (NS_OK);
}

//-------------------------------------------------------------------------
//
// Get this button label
//
//-------------------------------------------------------------------------
NS_METHOD nsButton::GetLabel(nsString& aBuffer)
{
  char * text;

  gtk_label_get(GTK_LABEL(GTK_BIN (mWidget)->child), &text);
  aBuffer.SetLength(0);
  aBuffer.Append(text);

  return (NS_OK);

}
