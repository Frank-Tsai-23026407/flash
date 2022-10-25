#
# Generated by erpcgen 1.9.1 on Tue Oct 25 18:18:03 2022.
#
# AUTOGENERATED - DO NOT EDIT
#

# Abstract base class for QSPIService
class IQSPIService(object):
    SERVICE_ID = 1
    SECTORERASE_ID = 1
    PAGEREAD_ID = 2
    PAGEWRITE_ID = 3
    CHIPSELECT_ID = 4
    CHIPINITIAL_ID = 5
    READCURRENT_ID = 6
    CHANGEFREQUENCY_ID = 7

    def sectorErase(self, addr):
        raise NotImplementedError()

    def pageRead(self, addr, data):
        raise NotImplementedError()

    def pageWrite(self, addr, data):
        raise NotImplementedError()

    def chipSelect(self, chip):
        raise NotImplementedError()

    def chipInitial(self, initial_state):
        raise NotImplementedError()

    def readCurrent(self, slave_address, memory_address, memory_value):
        raise NotImplementedError()

    def changeFrequency(self, prescaler):
        raise NotImplementedError()


