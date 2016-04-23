# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\projects\ArloBot\ArlobotHw\DualBoard-043\i2c.cydsn\i2c.cyprj
# Date: Tue, 19 Apr 2016 13:48:49 GMT
#set_units -time ns
create_clock -name {EZI2C_SCBCLK(FFB)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {I2CM_SCBCLK(FFB)} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {EZI2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list]
create_generated_clock -name {I2CM_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 7} [list]


# Component constraints for D:\projects\ArloBot\ArlobotHw\DualBoard-043\i2c.cydsn\TopDesign\TopDesign.cysch
# Project: D:\projects\ArloBot\ArlobotHw\DualBoard-043\i2c.cydsn\i2c.cyprj
# Date: Tue, 19 Apr 2016 13:48:47 GMT
