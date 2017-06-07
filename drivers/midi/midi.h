/*
  MIT License

  Copyright (c) 2017 Julien Delmotte

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#pragma once

void MIDI_Initialize();

int MIDI_NoteOn(unsigned char pitch, unsigned char velocity);
int MIDI_NoteOff(unsigned char pitch);


#define MIDI_VEL_MAX  0x7C


#define _DO 0
#define _DO_SHARP 1
#define _RE 2
#define _RE_SHARP 3
#define _MI 4
#define _FA 5
#define _FA_SHARP 6
#define _SOL 7
#define _SOL_SHARP 8
#define _LA 9
#define _LA_SHARP 10
#define _SI 11

#define MIDI_NOTE(n, oct) ((n) + (oct)*12)

#define MIDI_GETOCTAVE(v) ((v) / 12)
#define MIDI_GETNOTE(v) ((v) % 12)
