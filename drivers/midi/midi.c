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
#include <core32.h>
#include <GenericTypeDefs.h>

#include "USB/usb.h"
#include "USB/usb_function_midi.h"

//
// Global variables
//
static USB_HANDLE USBTxHandle = 0;      // USB output handle
static USB_HANDLE USBRxHandle = 0;      // USB input handle
static USB_VOLATILE BYTE USB_msCounter; // Host 1ms counter
static unsigned char ReceivedDataBuffer[64];
static USB_AUDIO_MIDI_EVENT_PACKET midiData; // Current packet to send
static int MIDI_Flags;

//
// Flags
//
#define MIDI_FLAGS_PACKETREADY 0x00000001 // A packet is ready to be sent
#define MIDI_FLAGS_PACKETSENT 0x00000002  // A packet has been successfully sent

#define MIDI_SETFLAG(f) MIDI_Flags |= (f)
#define MIDI_CLEARFLAG(f) MIDI_Flags &= ~(f)
#define MIDI_GETFLAG(f) (MIDI_Flags & (f))

//
// Prototypes
//
static int MIDI_Ready();
static void MIDI_Commit();

//
// User functions
//
void MIDI_Initialize()
{
  Task_Create(MIDI_Task, NULL);
}

void __attribute((weak)) MIDI_OnPacket(void *handle)
{
  // This function may be overriden by user code
}

int MIDI_NoteOn(unsigned char pitch, unsigned char velocity)
{
  if (!MIDI_Ready())
    return 0;

  midiData.CableNumber = 0;
  midiData.CodeIndexNumber = MIDI_CIN_NOTE_ON;
  midiData.DATA_0 = 0x90;     // Note on
  midiData.DATA_1 = pitch;    // Pitch
  midiData.DATA_2 = velocity; // Velocity

  MIDI_Commit();

  return 1;
}

int MIDI_NoteOff(unsigned char pitch)
{
  return MIDI_NoteOn(pitch, 0);
}

//
// MIDI related
//
static int MIDI_Ready()
{
  if (MIDI_GETFLAG(MIDI_FLAGS_PACKETREADY))
  {
    // Busy
    return 0;
  }

  midiData.Val = 0;
  return 1;
}

static void MIDI_Commit()
{
  MIDI_CLEARFLAG(MIDI_FLAGS_PACKETSENT);
  MIDI_SETFLAG(MIDI_FLAGS_PACKETREADY);
}

//
// USB related
//
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
  switch (event)
  {
  case EVENT_SOF:
    // Called by the host every 1ms
    if (USB_msCounter != 0)
      USB_msCounter--;
    break;

  case EVENT_CONFIGURED:
    // Enable the HID endpoint
    USBEnableEndpoint(MIDI_EP, USB_OUT_ENABLED | USB_IN_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);

    // Arm the OUT endpoint for the next packet
    USBRxHandle = USBRxOnePacket(MIDI_EP, (BYTE *)&ReceivedDataBuffer, 64);
    break;
  }
  return TRUE;
}

//
// MIDI state machine
//
void MIDI_Task(Task_t *task)
{
  Task_Switch(task)
  {
  case TASK_START:
    USBTxHandle = NULL;
    USBRxHandle = NULL;
    MIDI_Flags = 0;

    USBDeviceInit();
    USBDeviceAttach();
    break;

  case TASK_IDLE:
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1))
    {
      // USB is not ready
      return;
    }

    if (!USBHandleBusy(USBRxHandle))
    {
      // A packet has been received
      MIDI_OnPacket(USBRxHandle);

      // Re-arm for next packet
      USBRxHandle = USBRxOnePacket(MIDI_EP, (BYTE *)&ReceivedDataBuffer, 64);
    }

    if (MIDI_GETFLAG(MIDI_FLAGS_PACKETREADY))
    {
      if (!USBHandleBusy(USBTxHandle))
      {
        // A packet is ready to be sent and USB is ready for sending
        USBTxHandle = USBTxOnePacket(MIDI_EP, (BYTE *)&midiData, 4);
        MIDI_CLEARFLAG(MIDI_FLAGS_PACKETREADY);
        MIDI_SETFLAG(MIDI_FLAGS_PACKETSENT);
      }
    }
    break;
  }
}
