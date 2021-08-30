#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "headers.h"

class Keyboard {
 public:
	// Get key in ascii
	int getRawKey() {
		return Config::Keyboard::getKey();
	}

	// Key in ascii
	enum class Key {
		a = 97,
		b,
		c,
		d,
		e,
		f,
		g,
		h,
		i,
		j,
		k,
		l,
		m,
		n,
		o,
		p,
		q,
		r,
		s,
		t,
		u,
		v,
		w,
		x,
		y,
		z
	};

	bool getKey(Key key) {
		if (Config::Keyboard::getKey() == (int)key) {
			return true;
		} else {
			return false;
		}
	}
};

#endif