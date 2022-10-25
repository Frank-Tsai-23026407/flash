from pydoc import cli
import erpc
import time
from gen_py.qspi_rad_test.client import *
import argparse
from ptpython import embed

# Page size in bytes
PAGE_SIZE = 256

if __name__ == "__main__":
    init_state = 0
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", help="Serial port", type=str, required=True)
    parser.add_argument("--baud", help="Baud", type=int, required=True)
    parser.add_argument("--shell", help="Drop in ptpython",
                        action="store_true")
    args = parser.parse_args()

    xport = erpc.transport.SerialTransport(args.port, args.baud)
    client_mgr = erpc.client.ClientManager(xport, erpc.basic_codec.BasicCodec)
    client = QSPIServiceClient(manager=client_mgr)
    ref = erpc.Reference()

    client.chipSelect(5)
    client.chipInitial(ref)
    print("Erasing sector 0")
    client.sectorErase(addr=0x0fff000)
    # time.sleep(1)
    print("Reading page 0")
    client.pageRead(addr=0x0fff000, data=ref)
    print(ref.value)
    print("Writing page 0")
    client.pageWrite(addr=0x0fff000, data=[i for i in range(PAGE_SIZE)])
    # time.sleep(1)
    print("Reading page 0")
    client.pageRead(addr=0x0fff000, data=ref)
    print(ref.value)

    print("Erasing sector 0")
    client.sectorErase(addr=0x0fff000)
    # time.sleep(1)
    print("Reading page 0")
    client.pageRead(addr=0x0fff000, data=ref)
    print(ref.value)
    print("Writing page 0")
    client.pageWrite(addr=0x0fff000, data=[(255-i) for i in range(PAGE_SIZE)])
    # time.sleep(1)
    print("Reading page 0")
    client.pageRead(addr=0x0fff000, data=ref)
    print(ref.value)

    client.readCurrent(0x4C, 0x0D, ref)
    print(ref.value)
    c = ref.value << 8
    client.readCurrent(0x4C, 0x0D, ref)
    print(ref.value)
    c += ref.value
    print(c)

    if args.shell:
        embed(globals=globals(), locals=locals())
