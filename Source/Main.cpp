/*
 * Copyright (c) 2018 p-sam
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <malloc.h>

#include <switch.h>
#include <stratosphere.hpp>

#include <ns/ns_IServiceGetterInterface.hpp>

extern "C" {
	extern u32 __start__;

	u32 __nx_applet_type = AppletType_None;

	#define INNER_HEAP_SIZE 0x50000
	size_t nx_inner_heap_size = INNER_HEAP_SIZE;
	char   nx_inner_heap[INNER_HEAP_SIZE];
	
	void __libnx_initheap(void);
	void __appInit(void);
	void __appExit(void);

	/* Exception handling. */
	alignas(16) u8 __nx_exception_stack[0x1000];
	u64 __nx_exception_stack_size = sizeof(__nx_exception_stack);
	void __libnx_exception_handler(ThreadExceptionDump *ctx);
	u64 __stratosphere_title_id = 0x01000000000004E7;
	void __libstratosphere_exception_handler(AtmosphereFatalErrorContext *ctx);
}

void __libnx_exception_handler(ThreadExceptionDump *ctx) {
	StratosphereCrashHandler(ctx);
}

void __libstratosphere_exception_handler(AtmosphereFatalErrorContext *ctx) {
	Result rc = bpcAmsInitialize();
	if(R_SUCCEEDED(rc)) {
		bpcAmsRebootToFatalError(ctx);
		bpcAmsExit();
	}
}

void __libnx_initheap(void) {
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	/* Newlib */
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char*)addr;
	fake_heap_end   = (char*)addr + size;
}

void __appInit(void)
{
	Result rc = smInitialize();
	if(R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

	rc = setsysInitialize();
	if(R_SUCCEEDED(rc))
	{
		SetSysFirmwareVersion fw;
		rc = setsysGetFirmwareVersion(&fw);
		if(R_SUCCEEDED(rc))
		{
			hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
		}
		setsysExit();
	}

	rc = fsInitialize();
	if(R_FAILED(rc)) fatalSimple(rc);

	rc = fsdevMountSdmc();
	if(R_FAILED(rc)) fatalSimple(rc);

	rc = nsInitialize();
	if(R_FAILED(rc)) fatalSimple(rc);
}

void __appExit(void)
{
	fsdevUnmountAll();
	fsExit();
	nsExit();
	smExit();
}

static const char *ControlJsPath = "sdmc:/ControlMe/control.js";
char *jscode = NULL;

int main(int argc, char **argv)
{
	FILE *f = fopen(ControlJsPath, "rb");
	if(f)
	{
		fseek(f, 0, SEEK_END);
		size_t codesz = ftell(f);
		rewind(f);
		jscode = new char[codesz + 1]();
		fread(jscode, 1, codesz, f);
		fclose(f);
	}

	auto manager = new WaitableManager(1);
	AddMitmServerToManager<ns::IServiceGetterInterface>(manager, "ns:am2", 0x10);

	manager->Process();
	delete manager;

	if(jscode != NULL) delete[] jscode;

	return 0;
}