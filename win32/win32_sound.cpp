/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),

  (c) Copyright 2002 - 2011  zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2016  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  S-SMP emulator code used in 1.54+
  (c) Copyright 2016         byuu

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2016  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2011  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2011  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/

#include "IS9xSoundOutput.h"
#include "../snes9x.h"
#include "../apu/apu.h"
#include "wsnes9x.h"
#include "CDirectSound.h"
#include "CXAudio2.h"
#include "win32_sound.h"
// FMOD and FMOD Ex cannot be used at the same time
#ifdef FMOD_SUPPORT
#include "CFMOD.h"
#pragma comment(linker,"/DEFAULTLIB:fmodvc.lib")
#elif defined FMODEX_SUPPORT
#include "CFMODEx.h"
#if defined(_WIN64)
#pragma comment(linker,"/DEFAULTLIB:fmodex64_vc.lib")
#else
#pragma comment(linker,"/DEFAULTLIB:fmodex_vc.lib")
#endif // _WIN64
#endif // FMODEX_SUPPORT

#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

// available sound output methods
CDirectSound S9xDirectSound;
CXAudio2 S9xXAudio2;
// FMOD and FMOD Ex cannot be used at the same time
#ifdef FMOD_SUPPORT
CFMOD S9xFMOD;
#elif defined FMODEX_SUPPORT
CFMODEx S9xFMODEx;
#endif

// Interface used to access the sound output
IS9xSoundOutput *S9xSoundOutput = &S9xXAudio2;

/*  ReInitSound
reinitializes the sound core with current settings
IN:
mode		-	0 disables sound output, 1 enables
-----
returns true if successful, false otherwise
*/
bool ReInitSound()
{
	if (GUI.AVIOut)
		return false;
	Settings.SoundInputRate = CLAMP(Settings.SoundInputRate,8000, 48000);
	Settings.SoundPlaybackRate = CLAMP(Settings.SoundPlaybackRate,8000, 48000);
	S9xSetSoundMute(GUI.Mute);
	if(S9xSoundOutput)
		S9xSoundOutput->DeInitSoundOutput();

	return S9xInitSound(GUI.SoundBufferSize,0);
}

void CloseSoundDevice() {
	S9xSoundOutput->DeInitSoundOutput();
	S9xSetSamplesAvailableCallback(NULL,NULL);
}

/*  S9xOpenSoundDevice
called by S9xInitSound - initializes the currently selected sound output and
applies the current sound settings
-----
returns true if successful, false otherwise
*/
bool8 S9xOpenSoundDevice ()
{
	S9xSetSamplesAvailableCallback (NULL, NULL);
	// point the interface to the correct output object
	switch(GUI.SoundDriver) {
		case WIN_SNES9X_DIRECT_SOUND_DRIVER:
			S9xSoundOutput = &S9xDirectSound;
			break;
#ifdef FMOD_SUPPORT
		case WIN_FMOD_DIRECT_SOUND_DRIVER:
		case WIN_FMOD_WAVE_SOUND_DRIVER:
		case WIN_FMOD_A3D_SOUND_DRIVER:
			S9xSoundOutput = &S9xFMOD;
			break;
#elif defined FMODEX_SUPPORT
		case WIN_FMODEX_DEFAULT_DRIVER:
		case WIN_FMODEX_ASIO_DRIVER:
		case WIN_FMODEX_OPENAL_DRIVER:
			S9xSoundOutput = &S9xFMODEx;
			break;
#endif
		case WIN_XAUDIO2_SOUND_DRIVER:
			S9xSoundOutput = &S9xXAudio2;
			break;
		default:	// we default to DirectSound
			GUI.SoundDriver = WIN_SNES9X_DIRECT_SOUND_DRIVER;
			S9xSoundOutput = &S9xDirectSound;
	}
	if(!S9xSoundOutput->InitSoundOutput())
		return false;
	
	if(!S9xSoundOutput->SetupSound())
		return false;
	
	S9xSetSamplesAvailableCallback (S9xSoundCallback, NULL);
	return true;
}

/*  S9xSoundCallback
called by the sound core to process generated samples
*/
void S9xSoundCallback(void *data)
{	
	S9xSoundOutput->ProcessSound();
}
