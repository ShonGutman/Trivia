import socket

SERVER_PORT = 8826
SERVER_IP = '127.0.0.1'

def connect_to_server():
    """
    function will create a TCP socket with the server
    #note: socket must be closed outside function
    :return: server_sock
    :rtype: TCP socket
    """
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    server_sock.connect(server_address)
    return server_sock

def main():
    try:
        # Connect to the server
        server_sock = connect_to_server()
        print("Connection successful")

        try:
            # Send a message to the server
            message = "Hello"
            server_sock.sendall(message.encode())

            # Receive response from the server
            data = server_sock.recv(1024)
            print("Received from server:", data.decode())
        finally:
            # Close the connection
            server_sock.close()
    except Exception as e:
        print("Could not connect:", e)

if __name__ == "__main__":
    main()
