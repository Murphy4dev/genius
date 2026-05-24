APP_DIR = $(ROOT)/application
VPATH += $(APP_DIR) $(APP_DIR)/utils
SOURCE_FILES += $(APP_DIR)/utils/hook.c
SOURCE_FILES += $(APP_DIR)/utils/genius_log.c
SOURCE_FILES += $(APP_DIR)/utils/raw_list.c
SOURCE_FILES += $(APP_DIR)/utils/external_list.c
SOURCE_FILES += $(APP_DIR)/utils/ringQueue.c

VPATH += $(APP_DIR)/include
INCLUDE_DIRS += -I$(ROOT)/application/include

ifeq ($(CONFIG_HELLO_WORLD),yes)
VPATH += $(APP_DIR)/0-hello_world
SOURCE_FILES += $(APP_DIR)/0-hello_world/main.c
endif

ifeq ($(CONFIG_TASK_WORLD),yes)
VPATH += $(APP_DIR)/1-task_world
SOURCE_FILES += $(APP_DIR)/1-task_world/main.c
endif

ifeq ($(CONFIG_TASK_TCB_WORLD),yes)
VPATH += $(APP_DIR)/2-task_tcb_world
SOURCE_FILES += $(APP_DIR)/2-task_tcb_world/main.c
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

ifeq ($(CONFIG_TASK_STATE_BLOCKED_EVENT_WORLD),yes)
VPATH += $(APP_DIR)/task_state_blocked_event_world
SOURCE_FILES += $(APP_DIR)/task_state_blocked_event_world/main.c
endif

ifeq ($(CONFIG_ISR_WORLD),yes)
VPATH += $(APP_DIR)/isr_world
SOURCE_FILES += $(APP_DIR)/isr_world/main.c
CFLAGS += -DCONFIG_ISR_WORLD
endif

ifeq ($(CONFIG_RAW_LIST_WORLD),yes)
VPATH += $(APP_DIR)/raw_list_world
SOURCE_FILES += $(APP_DIR)/raw_list_world/main.c
endif

ifeq ($(CONFIG_INTRUSIVE_LIST_WORLD),yes)
VPATH += $(APP_DIR)/intrusive_list_world
SOURCE_FILES += $(APP_DIR)/intrusive_list_world/main.c
endif

ifeq ($(CONFIG_EXTERNAL_LIST_WORLD),yes)
VPATH += $(APP_DIR)/external_list_world
SOURCE_FILES += $(APP_DIR)/external_list_world/main.c
endif

ifeq ($(CONFIG_FREERTOS_LIST_WORLD),yes)
VPATH += $(APP_DIR)/freeRTOS_list_world
SOURCE_FILES += $(APP_DIR)/freeRTOS_list_world/main.c
endif

ifeq ($(CONFIG_RING_QUEUE_WORLD),yes)
VPATH += $(APP_DIR)/ringQueue_world
SOURCE_FILES += $(APP_DIR)/ringQueue_world/main.c
endif

ifeq ($(CONFIG_TASK_STATISTICS),yes)
CFLAGS += -DCONFIG_TASK_STATISTICS
VPATH += $(APP_DIR)/task_statistics
SOURCE_FILES += $(APP_DIR)/task_statistics/top.c
endif