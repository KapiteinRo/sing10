/*
 *	Ion processor
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

#define FROM_SING_DLL
#include <ions.h>

/*
 *	read from a buffer and parse into ION
 */
Ion ion_read(unsigned char szInput[ION_INPUTLEN]) {
	Ion ioOut;
	ioOut.ucFlags = 0;
	// convert
	ioOut.ulLeft = 0;
	ioOut.ulLeft = ((szInput[0] << 24) +
		(szInput[1] << 16) +
		(szInput[2] << 8) +
		(szInput[3]));

	ioOut.ulRight = 0;
	ioOut.ulRight = ((szInput[4] << 24) +
		(szInput[5] << 16) +
		(szInput[6] << 8) +
		(szInput[7]));

	ioOut.ulInput = 0;
	ioOut.ulInput = ((szInput[8] << 24) +
		(szInput[9] << 16) +
		(szInput[10] << 8) +
		(szInput[11]));

	return ioOut;
}

/*
 *	try find the event horizon
 */
Ion ion_run(Ion io) {
	return ion_compile(io);
}

/*
 *	write from an ION and parse into buffer
 */
unsigned int ion_write(unsigned char *szBuffer, Ion *io) {
	unsigned int uiSize = 0;
	if(io->ucFlags != 0) {
		// found something!
		uiSize = ION_INPUTLEN - 1;
		szBuffer = (unsigned char*)malloc(uiSize * sizeof(unsigned char));

		szBuffer[0] = ION_FLAG_1;
		szBuffer[1] = ION_FLAG_2;
		szBuffer[2] = io->ucFlags;

		szBuffer[3] = (unsigned long)((io->ulLeft >> 24) & 0xff);
		szBuffer[4] = (unsigned long)((io->ulLeft >> 16) & 0xff);
		szBuffer[5] = (unsigned long)((io->ulLeft >> 8) & 0xff);
		szBuffer[6] = (unsigned long)((io->ulLeft & 0xff));

		szBuffer[7] = (unsigned long)((io->ulRight >> 24) & 0xff);
		szBuffer[8] = (unsigned long)((io->ulRight >> 16) & 0xff);
		szBuffer[9] = (unsigned long)((io->ulRight >> 8) & 0xff);
		szBuffer[10] = (unsigned long)((io->ulRight & 0xff));
	} /*else {
		// nothing found
		uiSize = 0
	}*/
	return uiSize;
}
