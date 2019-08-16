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
 
#pragma once
#include <switch.h>

#ifdef __cplusplus
extern "C" {
#endif

Result nsGetReadOnlyApplicationControlDataInterface_Fwd(Service* s, Service* out);
Result nsGetApplicationControlData_Fwd(Service* s, u8 flag, u64 tid, void* buffer, size_t size, size_t* actual_size);
Result nsGetApplicationDesiredLanguage_Fwd(Service* s, u32 bitmask, u8* out_langentry);
Result nsConvertApplicationLanguageToLanguageCode_Fwd(Service* s, u8 input, u64* out);
Result nsConvertLanguageCodeToApplicationLanguage_Fwd(Service* s, u64 input, u8* out);

#ifdef __cplusplus
}
#endif