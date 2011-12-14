/*
*  TouchMessenger.h
*  
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef TOUCH_MESSENGER_H
#define TOUCH_MESSENGER_H

#include "Poco/FIFOEvent.h"
#include "Poco/Delegate.h"
#include "ofTypes.h"

#include "../Tracking/ContourFinder.h"

// message code
// copied, adapted, practiced from ofMouseEvents.h

/* THE DEAL WITH THE RAW

 RAW Events added - Uncalibrated RAW events. Their
 main objective is to get the raw camera blobs
 without calibration so as to provide calibration.
 Anyone can use them, but it's unneccesary
 because the normal TouchDown, TouchUp, and TouchMoved
 get the calibrated blobs. Enjoy!

 News: Friday 13th, 8:29 PM EST ===
 -Now you can add a hold event to your apps. good stuff...

*/

class content
	{
	public:
		int id, num;
		float x, y, movx, movy;
		content( int _num, float _x, float _y, float _movx, float _movy){
			id = -1;
			num = _num;
			x = _x;
			y = _y;
			movx = _movx;
			movy = _movy;
		}
		void set(int _num, float _x, float _y, float _movx, float _movy){
			num = _num;
			x = _x;
			y = _y;
			movx = _movx;
			movy = _movy;
		}
	};

class TouchMessage : public ofEventArgs {
public:
	vector<content*> contents;
	vector<int> alive;
};

class TouchListener {

  protected:

	virtual void TouchDown(Blob message){}
	virtual void TouchUp(Blob message){}
	virtual void TouchMoved(Blob message){}
	virtual void TouchHeld(Blob message){}

	//RAW
	virtual void RAWTouchDown(Blob message){}
	virtual void RAWTouchUp(Blob message){}
	virtual void RAWTouchMoved(Blob message){}
	virtual void RAWTouchHeld(Blob message){}

  public:

	void TouchDown(const void* sender, Blob& eventArgs){
		TouchDown(eventArgs);
	}
	void TouchUp(const void* sender, Blob& eventArgs){
		TouchUp(eventArgs);
	}
	void TouchMoved(const void* sender, Blob& eventArgs){
		TouchMoved(eventArgs);
	}
	void TouchHeld(const void* sender, Blob& eventArgs){
		TouchHeld(eventArgs);
	}

	//RAW
	void RAWTouchDown(const void* sender, Blob& eventArgs){
		RAWTouchDown(eventArgs);
	}
	void RAWTouchUp(const void* sender, Blob& eventArgs){
		RAWTouchUp(eventArgs);
	}
	void RAWTouchMoved(const void* sender, Blob& eventArgs){
		RAWTouchMoved(eventArgs);
	}
	void RAWTouchHeld(const void* sender, Blob& eventArgs){
		RAWTouchHeld(eventArgs);
	}
};

class TouchManager
	{
	public:
		//TouchMessage messenger;
		Blob messenger;
		Blob RAWmessenger;

		void addListener(TouchListener* listener){
			addTouchDownListener(listener);
			addTouchUpListener(listener);
			addTouchMovedListener(listener);
			addTouchHeldListener(listener);
		}

		void addRAWListener(TouchListener* listener){
			addRAWTouchDownListener(listener);
			addRAWTouchUpListener(listener);
			addRAWTouchMovedListener(listener);
			addRAWTouchHeldListener(listener);
		}

		//Listeners -----------
		void addTouchDownListener(TouchListener* listener){ //TouchDown
			TouchDown += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::TouchDown);
		}
		void addTouchUpListener(TouchListener* listener){ //TouchUp
			TouchUp += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::TouchUp);
		}
		void addTouchMovedListener(TouchListener* listener){ //TouchMoved
			TouchMoved += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::TouchMoved);
		}
		void addTouchHeldListener(TouchListener* listener){ //TouchMoved
			TouchHeld += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::TouchHeld);
		}

		//raw listeners
		void addRAWTouchDownListener(TouchListener* listener){ //TouchDown
			RAWTouchDown += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::RAWTouchDown);
		}
		void addRAWTouchUpListener(TouchListener* listener){ //TouchUp
			RAWTouchUp += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::RAWTouchUp);
		}
		void addRAWTouchMovedListener(TouchListener* listener){ //TouchMoved
			RAWTouchMoved += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::RAWTouchMoved);
		}
		void addRAWTouchHeldListener(TouchListener* listener){ //TouchMoved
			RAWTouchHeld += Poco::Delegate<TouchListener, Blob>(listener, &TouchListener::RAWTouchHeld);
		}

		//message recievers ---
		void notifyTouchDown(void* sender){ //TouchDown
			TouchDown.notify(sender, messenger);
		}
		void notifyTouchUp(void* sender){ //TouchUp
			TouchUp.notify(sender, messenger);
		}
		void notifyTouchMoved(void* sender){ //TouchMoved
			TouchMoved.notify(sender, messenger);
		}
		void notifyTouchHeld(void* sender){ //TouchMoved
			TouchHeld.notify(sender, messenger);
		}

		//RAW
		void notifyRAWTouchDown(void* sender){ //TouchDown
			RAWTouchDown.notify(sender, RAWmessenger);
		}
		void notifyRAWTouchUp(void* sender){ //TouchUp
			RAWTouchUp.notify(sender, RAWmessenger);
		}
		void notifyRAWTouchMoved(void* sender){ //TouchMoved
			RAWTouchMoved.notify(sender, RAWmessenger);
		}
		void notifyRAWTouchHeld(void* sender){ //TouchMoved
			RAWTouchHeld.notify(sender, RAWmessenger);
		}

		//events -------------- MONGREL
	private:
		Poco::FIFOEvent<Blob> TouchDown;
		Poco::FIFOEvent<Blob> TouchUp;
		Poco::FIFOEvent<Blob> TouchMoved;
		Poco::FIFOEvent<Blob> TouchHeld;

		//RAW
		Poco::FIFOEvent<Blob> RAWTouchDown;
		Poco::FIFOEvent<Blob> RAWTouchUp;
		Poco::FIFOEvent<Blob> RAWTouchMoved;
		Poco::FIFOEvent<Blob> RAWTouchHeld;

		Poco::FIFOEvent<bool>  becomeSkyNet;

	};

extern TouchManager TouchEvents;

#endif
