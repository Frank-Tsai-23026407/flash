# Setup Environment
```
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

# Regenerate Code
```
erpcgen -o gen_py -g py qspi_rad_test.erpc
erpcgen -o gen_c -g c qspi_rad_test.erpc
cp gen_c/qspi_rad_test.h gen_c/qspi_rad_test_server.cpp gen_c/qspi_rad_test_server.h <CUBEIDE_WS>/qspi_rad_test/Core/Src/erpc/service
```

# Run Client
```
python client.py --port /dev/ttyACM0 --baud 115200 --shell
```