# networkportd

Netwotkportd is a UNIX daemon which checks states of network ports in system.

## Description

Daemon uses a UNIX sockets to check that port is open or closed. When port changed status, networkportd logs info or warning into syslogd. 

## Installation
Makefile uses [gcc](https://gcc.gnu.org/) compiler to compile the whole project.

```bash
git clone https://github.com/Xhelios05X/ports-daemon

make

./out.o
```

## Usage

After compilation, networkportd is running as a daemon process. To see messages from daemon, you have to check logs from syslogd.