APP_DIR = $(ROOT)/application
VPATH += $(APP_DIR) $(APP_DIR)/hook_world
SOURCE_FILES += (APP_DIR)/hook_world/hook.c

ifeq ($(CONFIG_HELLO_WORLD),yes)
VPATH += $(APP_DIR)/hello_world
SOURCE_FILES += (APP_DIR)/hello_world/main.c
endif

ifeq ($(CONFIG_TIME_SLICING_WORLD),yes)
VPATH += $(APP_DIR)/time_slicing_world
SOURCE_FILES += (APP_DIR)/time_slicing_world/main.c
endif

ifeq ($(CONFIG_TASK_STATISTICS),yes)
CFLAGS += -DCONFIG_TASK_STATISTICS
VPATH += $(APP_DIR)/task_statistics
SOURCE_FILES += (APP_DIR)/task_statistics/top.c
endif