#
# Generated by erpcgen 1.9.1 on Tue Oct 18 17:30:21 2022.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc
from . import common, interface

# Client for QSPIService
class QSPIServiceClient(interface.IQSPIService):
    def __init__(self, manager):
        super(QSPIServiceClient, self).__init__()
        self._clientManager = manager

    def sectorErase(self, addr):
        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.SECTORERASE_ID,
                sequence=request.sequence))
        if addr is None:
            raise ValueError("addr is None")
        codec.write_uint32(addr)

        # Send request and process reply.
        self._clientManager.perform_request(request)
        _result = codec.read_int32()
        return _result

    def pageRead(self, addr, data):
        assert type(data) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.PAGEREAD_ID,
                sequence=request.sequence))
        if addr is None:
            raise ValueError("addr is None")
        codec.write_uint32(addr)

        # Send request and process reply.
        self._clientManager.perform_request(request)
        data.value = []
        for _i0 in range(256):
            _v0 = codec.read_uint8()
            data.value.append(_v0)

        _result = codec.read_int32()
        return _result

    def pageWrite(self, addr, data):
        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.PAGEWRITE_ID,
                sequence=request.sequence))
        if addr is None:
            raise ValueError("addr is None")
        codec.write_uint32(addr)
        if data is None:
            raise ValueError("data is None")
        for _i0 in data:
            codec.write_uint8(_i0)


        # Send request and process reply.
        self._clientManager.perform_request(request)
        _result = codec.read_int32()
        return _result

    def chipSelect(self, chip):
        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.CHIPSELECT_ID,
                sequence=request.sequence))
        if chip is None:
            raise ValueError("chip is None")
        codec.write_uint8(chip)

        # Send request and process reply.
        self._clientManager.perform_request(request)
        _result = codec.read_int32()
        return _result

    def chipInitial(self, initial_state):
        assert type(initial_state) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.CHIPINITIAL_ID,
                sequence=request.sequence))

        # Send request and process reply.
        self._clientManager.perform_request(request)
        initial_state.value = codec.read_uint8()
        _result = codec.read_int32()
        return _result

    def readCurrent(self, slave_address, memory_address, memory_value):
        assert type(memory_value) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.READCURRENT_ID,
                sequence=request.sequence))
        if slave_address is None:
            raise ValueError("slave_address is None")
        codec.write_uint8(slave_address)
        if memory_address is None:
            raise ValueError("memory_address is None")
        codec.write_uint8(memory_address)

        # Send request and process reply.
        self._clientManager.perform_request(request)
        memory_value.value = codec.read_uint8()
        _result = codec.read_int32()
        return _result


