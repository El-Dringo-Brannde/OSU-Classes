# Networking Intro
# Client/Server architecture
- A server is constantly waiting for connections from clients
- Client:   
  - Requests service
- Server:
  - Always running

### Web server, perfect example
## Unix Daemon A type of server
  - A Daemon is a process running in the background ready to provide services to programs that need it
  - #### syslogd(system log daemon): Maintains system log
  - #### lpd(line printer daemon): Manages line spooling
  - #### ntpd(network time protocol daemon): Manages clock sync on the network
  - #### dhcpd(dynamic host control protocol daemon): configures TCP/IP data to networks that suggest it
  - In UNIX, daemons all have the init process with PID = 1

## Example Protocol HTTP
  - Hyper Text Transfer Protocol
  - Sends files back and forth
  - Set standards on how requests & responses are sent
  - `Telnet` was how people used to interact w/ text based protocol networks
    - But it has been dropped since SSH to encrypt traffic, Telnet could be read by every node
  - TCP makes sure that packets arrive in order

# Network Layer Model
- Application
  - Software utilizing the network, browsers
- Transport
  - Protocols that control how data is sent from a to b
  - TCP(Transmissoin control protocol): Connection oriented guaranteed in order
  - UDP(Universal Datagram Protocol): Arrives not in order
- Network:
  - Addressing and organization of particular set of networks, defines addressing
  - IP: Naming Addressing, and routing from host to host
- Link:
  - Just gets data from one node to another
  - Ethernet: de facto signaling and addressing protocol, uses MAC addresses and IP for communicating
  - 802.11: Wifi, Controls sharing of congested Transmission space and connections based on quality
- Physical:
  - Actual hardware to talk to eachother
  - Cat 5 and Cat 6 cables

## TCP/IP High level functionality
  - communication b/w process
  - TCP is how applications interact, while IP address is how the addressing routes network packets
  - TCP sends a byte streams
  - Both sides of the connection actively work to keep it open
  - Traffic is bi-directional

### TCP Handshaking
- Client sends `SYNC` package to tell how to talk to them
- Server sends `SYNC + ACK`
- Client responds with `ACK` message and they begin talkin

## TCP
- TCP sends data in bundles called packets using address specified by IP
- Guarantees packet integrity, order, duplicates, drops
## UDP
- May be dropped over network, may be out of order
- But has MUCH less overhead
- Usually used when streaming audio/video, game servers

# IP
- How we address machines on a network
- Interface: How Physical links and host/router 
