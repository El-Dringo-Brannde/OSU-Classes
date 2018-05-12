from socket import *
import sys

SERVER_NAME = 'localhost'


class chat_serve:
    port_num, server_sock, connected_sock, handle = None, None, None, ""

    def __init__(self):
        self.pull_cli()
        self.server_sock = socket(AF_INET, SOCK_STREAM)
        self.server_sock.bind(('', self.port_num))
        self.server_sock.listen(1)
        print("Server should be ready to receive..")

        self.start_server()

    def pull_cli(self):
        if(len(sys.argv) <= 1):
            raise 'You forgot to specify port number >.>'
        else:
            self.port_num = int(sys.argv[1])
            self.handle = input("Choose your internet handle: ")

    def start_server(self):
        while 1:
            self.connected_sock, address = self.server_sock.accept()
            print("Connected on ", self.connected_sock)
            self.start_chat()

    def start_chat(self):
        recv_message = ""
        while 1:
            recv_message = self.connected_sock.recv(4096).decode('utf-8')
            if(recv_message == ""):
                print("Client killed connection, Exiting..")
                exit(2)
                break
            print(str(recv_message))
            outgoing_message = input(self.handle + "> ")
            self.connected_sock.send(outgoing_message.encode())
            if (outgoing_message == '\\quit'):
                print("Self destructing")
                exit()
