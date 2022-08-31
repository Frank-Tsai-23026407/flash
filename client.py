from pydoc import cli
import erpc
from gen_py.qspi_rad_test.client import *
import argparse
from ptpython import embed

# Page size in bytes
PAGE_SIZE = 256

if __name__ == "__main__":
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

    print("Erasing sector 0")
    client.sectorErase(addr=0)
    print("Writing page 0")
    client.pageWrite(addr=0, data=[i for i in range(PAGE_SIZE)])
    print("Reading page 0")
    client.pageRead(addr=0, data=ref)
    print(ref.value)

    if args.shell:
        embed(globals=globals(), locals=locals())
