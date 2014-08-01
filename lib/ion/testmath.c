/*
 *	Test math
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

int main(int argc, char *argv[]) {
	unsigned long ulMax;
	unsigned char szUl[4];
	unsigned long ulRes;

	ulMax = ULONG_MAX;
	ulRes = IOML_HALFMAX();
	printf("Maximum = %u\n",ulMax);
	printf("Half = %u\n",ulRes);
	
	// convert to
/*	szUl[0] = ulRes & 0xff;
	szUl[1] = (ulRes >> 8) & 0xff;
	szUl[2] = (ulRes >> 16) & 0xff;
	szUl[3] = (ulRes >> 24) & 0xff;*/
	szUl[0] = (unsigned long)((ulRes >> 24) & 0xff);
	szUl[1] = (unsigned long)((ulRes >> 16) & 0xff);
	szUl[2] = (unsigned long)((ulRes >> 8) & 0xff);
	szUl[3] = (unsigned long)((ulRes & 0xff));
	
	// convert back
	ulRes = 0;
	ulRes = ((szUl[0] << 24) +
		(szUl[1] << 16) +
		(szUl[2] << 8) +
		(szUl[3]));

	printf("Half 2 = %u\n",ulRes);

	return 0;
}
