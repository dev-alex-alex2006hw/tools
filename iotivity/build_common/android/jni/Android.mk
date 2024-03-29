include $(CLEAR_VARS)
LOCAL_MODULE := flags_probe
include $(BUILD_SHARED_LIBRARY)

$(info TC_PREFIX=$(TOOLCHAIN_PREFIX))
$(info CFLAGS=$(TARGET_CFLAGS))
$(info CXXFLAGS=$(TARGET_CXXFLAGS) $(TARGET_NO_EXECUTE_CFLAGS))
$(info CPPPATH=$(TARGET_C_INCLUDES) $(__ndk_modules.$(APP_STL).EXPORT_C_INCLUDES))
$(info SYSROOT=$(SYSROOT_LINK))
$(info LDFLAGS=$(TARGET_LDFLAGS) $(TARGET_NO_EXECUTE_LDFLAGS) $(TARGET_NO_UNDEFINED_LDFLAGS) $(TARGET_RELRO_LDFLAGS))
$(info TC_VER=$(TOOLCHAIN_VERSION))
