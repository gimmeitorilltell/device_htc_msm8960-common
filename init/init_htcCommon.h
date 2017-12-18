/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _INIT_HTC_COMMON_H
#define _INIT_HTC_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

// Helper function to allow the use of property_get_sdk23()
// for backwards compatibility with legacy (pre sdk24) property_get
// due to 'std::string property_get(const char* name)' in sdk24+
int property_get_sdk23(const char *key, char *value);

// Substitute property_set with property_override
// For Android 8.0 this will call the property_override (source https://goo.gl/RbFvNT)
// but for pre Android 8.0 it will just call the normal property_set
int property_override(const char *name, const char *value);
#define property_set property_override

// Main function to read ro.build.fingerprint and ro.product.device
// from /system/build.prop
void set_props_from_build(void);

// ERROR is deprecated in 8.0 in favor of c++ style: LOG(ERROR) << "text"...
// add a helper to convert from (fmt, ...) to the new format
#ifndef ERROR
    void ERROR(const char *fmt, ...);
#endif

#ifdef __cplusplus
}
#endif


// Rename vendor_load_properties() to real_vendor_load_properties()
// and let init_htcCommon.cpp call the real function as appropriate
#ifdef __cplusplus
    // Allow usage of .c and/or .cpp (this is actually only needed in 6.0 where
    // vendor_init is a c file, but allows for real_vendor_load_properties() to
    // be in a .cpp file due to the #ifdef __cplusplus in vendor_init.h)
    extern "C" { extern void real_vendor_load_properties(void); }
#endif /* __cplusplus */
#define vendor_load_properties real_vendor_load_properties


// 8.0 no longer *needs* these defines but they are needed for backwards
// compatibly and have little/no effect on 8.0+'s no length limitation
#ifndef PROP_NAME_MAX
#define PROP_NAME_MAX   32
#endif

#ifndef PROP_VALUE_MAX
#define PROP_VALUE_MAX  92
#endif

#endif // _INIT_HTC_COMMON_H
