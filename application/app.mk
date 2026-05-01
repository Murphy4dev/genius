APP_DIR = $(ROOT)/application
VPATH += $(APP_DIR) $(APP_DIR)/hook_world
SOURCE_FILES += $(APP_DIR)/hook_world/hook.c

ifeq ($(CONFIG_HELLO_WORLD),yes)
VPATH += $(APP_DIR)/0-hello_world
SOURCE_FILES += $(APP_DIR)/0-hello_world/main.c
endif

ifeq ($(CONFIG_TASK_WORLD),yes)
VPATH += $(APP_DIR)/1-task_world
SOURCE_FILES += $(APP_DIR)/1-task_world/main.c
endif

ifeq ($(CONFIG_TASK_PRIORITY_WORLD),yes)
VPATH += $(APP_DIR)/3-task_priority_world
SOURCE_FILES += $(APP_DIR)/3-task_priority_world/main.c
endif

ifeq ($(CONFIG_TASK_SCHEDULE_WORLD),yes)
VPATH += $(APP_DIR)/4-task_schedule_world
SOURCE_FILES += $(APP_DIR)/4-task_schedule_world/main.c
endif

ifeq ($(CONFIG_TASK_STACK_WORLD),yes)
VPATH += $(APP_DIR)/5-task_stack_world
SOURCE_FILES += $(APP_DIR)/5-task_stack_world/main.c
endif

ifeq ($(CONFIG_TASK_STATISTICS),yes)
CFLAGS += -DCONFIG_TASK_STATISTICS
VPATH += $(APP_DIR)/task_statistics
SOURCE_FILES += $(APP_DIR)/task_statistics/top.c
endif