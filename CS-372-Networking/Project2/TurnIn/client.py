from util import util
from socket import *


class ftp_client:
    cli_util, client_sock = util(), None

    def __init__(self):
        self.connect_to_server()
        self.send_args_to_socket()
        self.await_response()

    def connect_to_server(self):
        try:
            print("Attempting connection...")
            self.client_sock = socket(AF_INET, SOCK_STREAM)
            self.client_sock.connect(
                (self.cli_util.host, int(self.cli_util.connecting_port)))
        except Exception as error:
            print("Error connecting to remote", error)

    def send_args_to_socket(self):
        self.send_data_to_socket(self.cli_util.file_opt)
        self.send_data_to_socket(self.cli_util.name)
        self.send_data_to_socket(self.cli_util.recv_port)

    def send_data_to_socket(self, data_to_send):
        try:
            self.client_sock.send(data_to_send.encode())
            response = self.client_sock.recv(4096).decode(
                'utf-8')  # clear out the socket
            print(response)
        except Exception as error:
            print("Are you sure the server is running?")

    def await_response(self):
        if(self.cli_util.file_opt == '-g'):
            self.stream_file()
        else:
            print("Directory contents...")
            self.stream_directory()

    def stream_directory(self):
        file_name = ""
        while 1:
            file_name += self.client_sock.recv(4096).decode('utf-8')
            if "DONE" in file_name:
                break
        print(file_name)

    def stream_file(self):
        print("Streaming File...")
        contents = ""
        while 1:
            file_cont = self.client_sock.recv(4096).decode('utf-8')
            if "File Doesn't Exist" in file_cont:
                print("FILE NON EXISTENT")
                return
            if "DONE" in file_cont:
                break
            contents += file_cont
        self.write_file(contents)

    def write_file(self, contents):
        f = open(self.cli_util.name, "w")
        f.write(contents)
        f.close()
        print("File Transfer complete!")
