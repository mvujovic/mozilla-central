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

#ifndef nsTextWidget_h__
#define nsTextWidget_h__

#include "nsTextHelper.h"

#include "nsITextWidget.h"

/**
 * Native GTK+ single line edit control wrapper.
 */

class nsTextWidget : public nsTextHelper
{

public:
  nsTextWidget();
  virtual ~nsTextWidget();

  // nsISupports
  NS_IMETHOD QueryInterface(REFNSIID aIID, void** aInstancePtr);

  virtual PRBool OnMove(PRInt32 aX, PRInt32 aY) { return PR_FALSE; }
  virtual PRBool OnPaint(nsPaintEvent & aEvent) { return PR_FALSE; }
  virtual PRBool OnResize(nsRect &aRect) { return PR_FALSE; }

protected:
  NS_IMETHOD CreateNative(GtkWidget *parentWindow);
};

#endif // nsTextWidget_h__
