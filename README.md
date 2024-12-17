# vtunPtP
VtunPtP tunnel with ghost cryptography

Отчёт: [vtunPtP/ПАЗИ отчет.docx](https://github.com/Nikittua/vtunPtP/blob/kuznechik/%D0%9F%D0%90%D0%97%D0%98%20%D0%BE%D1%82%D1%87%D0%B5%D1%82.docx)


# 0 Prepare

```sh
apt update
sudo apt-get install zlib1g zlib1g-dev libbz2-dev cmake flex yacc -y
git clone https://git.miem.hse.ru/axelkenzo/libakrypt-0.x
mkdir build
cd build/
cmake -DCMAKE_C_FLAGS="-march=native" ../libakrypt-0.x
sudo make
sudo make install
sudo ldconfig
cd
git clone -b kuznechik https://github.com/Nikittua/vtunPtP.git
cd vtunPtP

```

# 1 Configure and edit Makefile

```sh
./configure --disable-ssl  --disable-lzo --disable-zlib --disable-shaper

./configure --disable-ssl  --disable-lzo --disable-zlib --disable-shaper

LDFLAGS += -L/usr/local/lib -lakrypt
CFLAGS += -I/usr/local/include
LDFLAGS+= -Xlinker -rpath=/usr/local/include/
LIBS += -libakrypt

make 
make install
```
<details>
  <summary>Client.conf</summary>
  
  ```sh
cat << EOF > /home/client.conf
options {
  port 5344;            # Connect to this port.
  timeout 60;           # General timeout

  syslog        daemon;
  # Path to various programs
  ppp           /usr/sbin/pppd;
  ifconfig      /sbin/ifconfig;
  route         /sbin/route;
  firewall      /sbin/ipchains;
  ip            /sbin/ip;
}

# TUN example. Session 'cobra'.
cobra {
  password test;
  type tun;          # Device tun1
  persist yes;
  up {
        # Connection is Up

        # Assign IP addresses.
        ifconfig "%% 10.3.0.2 pointopoint 10.3.0.1 mtu 1450";
  };
}
EOF
  ```
</details>

<details>
  <summary>Server.conf</summary>
  
  ```sh
cat << EOF > /home/server.conf
options {
  port 5344;            # Listen on this port.

  # Syslog facility
  syslog        daemon;

  # Path to various programs
  ppp           /usr/sbin/pppd;
  ifconfig      /sbin/ifconfig;
  route         /sbin/route;
  firewall      /sbin/ipchains;
  ip            /sbin/ip;
}

# Default session options
default {
  compress no;          # Compression is off by default
  speed 0;              # By default maximum speed, NO shaping
}

# TUN example. Session 'cobra'.
cobra {
  pass  test;
  type  tun;            # IP tunnel
  proto udp;            # UDP protocol
  comp  no;          # LZO compression level 9
  encrypt yes;            # Encryption
  keepalive yes;        # Keep connection alive

  up {
        # Connection is Up

        # 10.3.0.1 - local, 10.3.0.2 - remote
        ifconfig "%% 10.3.0.1 pointopoint 10.3.0.2 mtu 1450";
  };
}
EOF
  ```
</details>

# 2 Start/Stop

```
# Server:
sudo vtund -s -f /home/server.conf 
# Client: 
sudo vtund -p cobra <server_IP> -f /home/client.conf

#logs

tail -f /var/log/syslog

#stop

killall vtund
```

# 3 Test

```
cat << EOF > filename.in
OpenText
EOF

# Client
cat filename.in | nc -q 1 10.3.0.1 5344
# Server:
sudo tcpdump -i enp0s3 -nn -lex port 5344 -w dump


open dump in wireshark and search for plain text
```


