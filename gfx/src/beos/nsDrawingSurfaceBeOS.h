/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */

#ifndef nsDrawingSurfaceBeOS_h___
#define nsDrawingSurfaceBeOS_h___

#include "nsIDrawingSurface.h"
#include "nsIDrawingSurfaceBeOS.h"

#include <Bitmap.h>
#include <View.h>

class nsDrawingSurfaceBeOS : public nsIDrawingSurface, 
                             public nsIDrawingSurfaceBeOS
{
public:
  nsDrawingSurfaceBeOS();
  virtual ~nsDrawingSurfaceBeOS();

  NS_DECL_ISUPPORTS

  //nsIDrawingSurface interface

  NS_IMETHOD Lock(PRInt32 aX, PRInt32 aY, PRUint32 aWidth, PRUint32 aHeight,
                  void **aBits, PRInt32 *aStride, PRInt32 *aWidthBytes,
                  PRUint32 aFlags);
  NS_IMETHOD Unlock(void);
  NS_IMETHOD GetDimensions(PRUint32 *aWidth, PRUint32 *aHeight);
  NS_IMETHOD IsOffscreen(PRBool *aOffScreen);
  NS_IMETHOD IsPixelAddressable(PRBool *aAddressable);
  NS_IMETHOD GetPixelFormat(nsPixelFormat *aFormat);

  // local methods
  NS_IMETHOD Init(BView *aView);
  NS_IMETHOD Init(BView *aView, PRUint32 aWidth, PRUint32 aHeight,
                  PRUint32 aFlags);
                  
/* below are utility functions used mostly for nsRenderingContext and nsImage 
 * to plug into gdk_* functions for drawing.  You should not set a pointer 
 * that might hang around with the return from these.  instead use the ones 
 * above.  pav 
 */                 
  NS_IMETHOD AcquireView(BView **aView); 
  NS_IMETHOD ReleaseView(void);
  NS_IMETHOD AcquireBitmap(BBitmap **aBitmap);
  NS_IMETHOD ReleaseBitmap(void);

  void GetSize(PRUint32 *aWidth, PRUint32 *aHeight) { *aWidth = mWidth; *aHeight = mHeight; } 
 
private: 
  BView			*mView;
  BBitmap		*mBitmap;
  nsPixelFormat mPixFormat;
  PRUint32      mWidth;
  PRUint32      mHeight;
  PRUint32     mFlags; 
  PRBool       mIsOffscreen; 
 
  /* for locks */ 
  PRInt32      mLockX; 
  PRInt32      mLockY; 
  PRUint32     mLockWidth; 
  PRUint32     mLockHeight; 
  PRUint32      mLockFlags;
  PRBool       mLocked;
};

#endif
