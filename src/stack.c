/*
 *	ION Stack
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
#include <string.h>
#include <sing.h>

// globals
unsigned char _szStack[ION_INPUTLEN];
int _iStackSize;

// open stack
void open_stack() {
	int i;

	// reset
	_iStackSize = 0;
	memset(_szStack,'\0',ION_INPUTLEN);
}

// push a byte onto the stack
void push_stack(unsigned char c) {
	int i;

	if(_iStackSize < ION_INPUTLEN) {
		_szStack[_iStackSize++] = c;
	} else {
		// move all bytes one position
		for(i = 1; i < ION_INPUTLEN; i++) {
			_szStack[i - 1] = _szStack[i];
		}
		// push new byte as last
		_szStack[ION_INPUTLEN - 1] = c;
	}
}

// fetch the Ion that has accumulated in the stack
Ion pop_stack() {
	return IonRead(_szStack);
}

int stack_filled() {
	if(_iStackSize == ION_INPUTLEN) return 1;
	return 0;
}
