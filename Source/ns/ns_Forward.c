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

#include <string.h>
#include <switch.h>
#include <ns/ns_Forward.h>

Result nsGetReadOnlyApplicationControlDataInterface_Fwd(Service* s, Service* out)
{
	IpcCommand c;
	ipcInitialize(&c);

	struct {
		u64 magic;
		u64 cmd_id;
	} *raw;

	raw = serviceIpcPrepareHeader(s, &c, sizeof(*raw));

	raw->magic = SFCI_MAGIC;
	raw->cmd_id = 7989;

	Result rc = serviceIpcDispatch(s);

	if (R_SUCCEEDED(rc)) {
		IpcParsedCommand r;

		struct {
			u64 magic;
			u64 result;
		} *resp;

		serviceIpcParse(s, &r, sizeof(*resp));
		resp = r.Raw;

		rc = resp->result;
		if (R_SUCCEEDED(rc)) {
			serviceCreateSubservice(out, s, &r, 0);
		}
	}

	return rc;
}

Result nsGetApplicationControlData_Fwd(Service* s, u8 flag, u64 tid, void* buffer, size_t size, size_t* out_actual_size) {
	IpcCommand c;
	ipcInitialize(&c);
	ipcAddRecvBuffer(&c, buffer, size, 0);

	struct {
		u64 magic;
		u64 cmd_id;
		u8 flag;
		u64 tid;
	} *raw;

	raw = ipcPrepareHeader(&c, sizeof(*raw));

	raw->magic = SFCI_MAGIC;
	raw->cmd_id = 0;
	raw->flag = flag;
	raw->tid = tid;

	Result rc = serviceIpcDispatch(s);

	if (R_SUCCEEDED(rc)) {
		IpcParsedCommand r;
		ipcParse(&r);

		struct {
			u64 magic;
			u64 result;
			u64 actual_size;
		} *resp = r.Raw;

		rc = resp->result;

		if (R_SUCCEEDED(rc) && out_actual_size) {
			*out_actual_size = resp->actual_size;
		}
	}

	return rc;
}

Result nsGetApplicationDesiredLanguage_Fwd(Service* s, u32 bitmask, u8* out_langentry) {
	IpcCommand c;
	ipcInitialize(&c);

	struct {
		u64 magic;
		u64 cmd_id;
		u32 bitmask;
	} *raw;

	raw = ipcPrepareHeader(&c, sizeof(*raw));

	raw->magic = SFCI_MAGIC;
	raw->cmd_id = 1;
	raw->bitmask = bitmask;

	Result rc = serviceIpcDispatch(s);

	if (R_SUCCEEDED(rc)) {
		IpcParsedCommand r;
		ipcParse(&r);

		struct {
			u64 magic;
			u64 result;
			u8 langentry;
		} *resp = r.Raw;

		rc = resp->result;

		if (R_SUCCEEDED(rc) && out_langentry) {
			*out_langentry = resp->langentry;
		}
	}

	return rc;
}

Result nsConvertApplicationLanguageToLanguageCode_Fwd(Service* s, u8 langentry, u64* out_langcode) {
	IpcCommand c;
	ipcInitialize(&c);

	struct {
		u64 magic;
		u64 cmd_id;
		u8 langentry;
	} *raw;

	raw = ipcPrepareHeader(&c, sizeof(*raw));

	raw->magic = SFCI_MAGIC;
	raw->cmd_id = 2;
	raw->langentry = langentry;

	Result rc = serviceIpcDispatch(s);

	if (R_SUCCEEDED(rc)) {
		IpcParsedCommand r;
		ipcParse(&r);

		struct {
			u64 magic;
			u64 result;
			u64 langcode;
		} *resp = r.Raw;

		rc = resp->result;

		if (R_SUCCEEDED(rc) && out_langcode) {
			*out_langcode = resp->langcode;
		}
	}

	return rc;
}

Result nsConvertLanguageCodeToApplicationLanguage_Fwd(Service* s, u64 langcode, u8* out_langentry) {
	IpcCommand c;
	ipcInitialize(&c);

	struct {
		u64 magic;
		u64 cmd_id;
		u64 langcode;
	} *raw;

	raw = ipcPrepareHeader(&c, sizeof(*raw));

	raw->magic = SFCI_MAGIC;
	raw->cmd_id = 3;
	raw->langcode = langcode;

	Result rc = serviceIpcDispatch(s);

	if (R_SUCCEEDED(rc)) {
		IpcParsedCommand r;
		ipcParse(&r);

		struct {
			u64 magic;
			u64 result;
			u8 langentry;
		} *resp = r.Raw;

		rc = resp->result;

		if (R_SUCCEEDED(rc) && out_langentry) {
			*out_langentry = resp->langentry;
		}
	}

	return rc;
}