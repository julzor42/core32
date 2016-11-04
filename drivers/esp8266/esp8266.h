/*
  MIT License

  Copyright (c) 2016 Julien Delmotte

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
#ifndef _ESP8266_H_
#define _ESP8266_H_

void      ESP8266_Initialize      ();
void      ESP8266_Reset           ();

int       ESP8266_IsOnline        ();
int       ESP8266_IsReady         ();
char*     ESP8266_GetIP           ();

int       ESP8266_TcpIsConnected  ();
int       ESP8266_TcpConnect      (const char* Host, unsigned short Port);
void      ESP8266_TcpClose        ();
int       ESP8266_TcpIsSending    ();
int       ESP8266_TcpIsErrorSet   ();

int       ESP8266_TcpSend         (const char* Data);
int       ESP8266_TcpRecv         (char* Data);

#endif /* _ESP8266_H_ */
