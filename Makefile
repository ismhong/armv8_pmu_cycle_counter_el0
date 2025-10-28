obj-m := pmu_el0_cycle_counter.o
pmu_el0_cycle_counter-objs += armv8_pmu_el0_cycle_counter.o armv8_pmu_el0_timer_control.o
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all: test_pmccntr
	$(MAKE) -C $(KDIR) M=$(PWD) modules

test_pmccntr: test_pmccntr.c
	$(CC) -o test_pmccntr test_pmccntr.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f test_pmccntr
