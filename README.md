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
Usage: curser [OPTIONS]
OPTIONS:
	-ifn   interface name
	-op    type of packet[req/rep]
	-vpa   victim ip
	-sha   sender mac address
	-gpa   gateway ip
	-gha   gateway mac address
  
➜ sudo ./curser -ifn en0 -op req -vpa 192.168.0.22 -sha 00:AA:BB:CC:DD:EE -gpa 192.168.1.1 -gha 00:01:02:03:04:05
```
