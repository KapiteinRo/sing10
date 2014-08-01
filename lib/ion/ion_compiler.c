/*
 *	Ion compiler
 *
 * Copyright (C) 2005 Royi Eltink <r.eltink@live.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <limits.h>
#include <ions.h>

/*
 *	COMPILER TABLE:
 *
 *	1 : a + b
 *	2 : a - b
 *	3 : b - a
 *	4 : b * a
 *	5 : a / b
 *	6 : b / a
 *	7 : (a + 255) + b
 *	8 : (b + 255) + a
 *	9 : (a - 255) - b
 *	10 : (b - 255) - b
 *
 */

// dirty global
Ion _ios;

static void IOC_C001(unsigned long ulCheck) {
	if(IOML_CheckAdd(_ios.ulLeft, _ios.ulRight, ulCheck) == ION_TRUE) {
		unsigned long ul = _ios.ulLeft + _ios.ulRight;
		if(ul == _ios.ulInput) _ios.ucFlags = 1;
	}
}
static void IOC_C002() {
	if(_ios.ulLeft > _ios.ulRight) {
		unsigned long ul = _ios.ulLeft - _ios.ulRight;
		if(ul == _ios.ulInput) _ios.ucFlags = 2;
	}
}
static void IOC_C003() {
	if(_ios.ulLeft < _ios.ulRight) {
		unsigned long ul = _ios.ulRight - _ios.ulLeft;
		if(ul == _ios.ulInput) _ios.ucFlags = 3;
	}
}
static void IOC_C004() {
	unsigned long ul = _ios.ulRight * _ios.ulLeft;
	if(ul != 0 && ul != ULONG_MAX && ul == _ios.ulInput) _ios.ucFlags = 4;
}
static void IOC_C005() {
	unsigned long ul = (_ios.ulRight+1)/(_ios.ulLeft+1);
	if(ul != 0 && ul != ULONG_MAX && ul == _ios.ulInput) _ios.ucFlags = 5;
}
static void IOC_C006() {
	unsigned long ul = (_ios.ulLeft+1)/(_ios.ulRight+1);
	if(ul != 0 && ul != ULONG_MAX && ul == _ios.ulInput) _ios.ucFlags = 6;
}
static void IOC_C007(unsigned long ulCheck) {
	if(_ios.ulLeft > ION_SHIFT) {
		if((_ios.ulLeft - ION_SHIFT) < (ULONG_MAX - ION_SHIFT)) {
			if(IOML_CheckAdd(_ios.ulLeft + ION_SHIFT, _ios.ulRight, ulCheck) == ION_TRUE) {
				unsigned long ul = (_ios.ulLeft + ION_SHIFT) + _ios.ulRight;
				if(ul == _ios.ulInput) _ios.ucFlags = 7;
			}
		}
	}
}
static void IOC_C008(unsigned long ulCheck) {
	if(_ios.ulRight > 255) {
		if((_ios.ulRight - 255) < (ULONG_MAX - ION_SHIFT)) {
			if(IOML_CheckAdd(_ios.ulLeft + ION_SHIFT, _ios.ulRight, ulCheck) == ION_TRUE) {
				unsigned long ul = _ios.ulLeft + (_ios.ulRight + ION_SHIFT);
				if(ul == _ios.ulInput) _ios.ucFlags = 8;
			}
		}
	}
}
static void IOC_C009() {
	if(_ios.ulLeft > ION_SHIFT) {
		unsigned long ul = _ios.ulLeft - ION_SHIFT;
		if(ul > _ios.ulRight) {
			ul -= _ios.ulRight;
			if(ul != 0 && ul != ULONG_MAX && ul == _ios.ulInput) _ios.ucFlags = 9;
		}
	}
}
static void IOC_C010() {
	if(_ios.ulRight > ION_SHIFT) {
		unsigned long ul = _ios.ulRight - ION_SHIFT;
		if(ul > _ios.ulLeft) {
			ul -= _ios.ulLeft;
			if(ul != 0 && ul != ULONG_MAX && ul == _ios.ulInput) _ios.ucFlags = 10;
		}
	}
}


Ion ion_compile(Ion io) {
	// prepare maths
	unsigned long ulHalfMax = IOML_HALFMAX();

	// load on stack
	_ios.ucFlags = 0;
	_ios.ulLeft = io.ulLeft;
	_ios.ulRight = io.ulRight;
	_ios.ulInput = io.ulInput;
	
	// execute
	IOC_C001(ulHalfMax); if(_ios.ucFlags != 0) return _ios;
	IOC_C002(); if(_ios.ucFlags != 0) return _ios;
	IOC_C003(); if(_ios.ucFlags != 0) return _ios;
	IOC_C004(); if(_ios.ucFlags != 0) return _ios;
	IOC_C006(); if(_ios.ucFlags != 0) return _ios;
	IOC_C007(ulHalfMax); if(_ios.ucFlags != 0) return _ios;
	IOC_C008(ulHalfMax); if(_ios.ucFlags != 0) return _ios;
	IOC_C009(); if(_ios.ucFlags != 0) return _ios;
	IOC_C010(); if(_ios.ucFlags != 0) return _ios;

	// nothing?
	return _ios;
}
