import socket
import json

SERVER_PORT = 8826
SERVER_IP = '127.0.0.1'

def connect_to_server():
    """
    The function will establish a TCP connection with the server
    # Note: Connection must be closed outside the function
    :return: server_sock
    :rtype: TCP socket
    """
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    server_sock.connect(server_address)
    return server_sock

def main():
    while True:
        try:
            # Attempt to connect to the server
            server_sock = connect_to_server()
            print("Connection successful")

            try:
                message_type = input("Type 'login' or 'signup': ").lower()
                message_data = {}

                if message_type == 'login':
                    # Prepare login message in JSON format
                    username = input("Enter your username: ")
                    password = input("Enter your password: ")
                    message_type = 1
                    message_data = {"username": username, "password": password}
                    
                elif message_type == 'signup':
                    # Prepare signup message in JSON format
                    username = input("Enter your username: ")
                    password = input("Enter your password: ")
                    mail = input("Enter your email: ")
                    message_type = 2

                    message_data = {"username": username, "password": password, "mail": mail}
                else:
                    message_type = 99

                # Add code and message length according to the format
                data = []
                data.append(message_type)
                data.append(len(json.dumps(message_data)))
                data.append(json.dumps(message_data))

                # Send message to server in JSON format
                server_sock.sendall(json.dumps(data).encode())

                # Receive response from server
                server_data = server_sock.recv(1024)
                print("Received from server:", server_data.decode())
            finally:
                # Close the connection
                server_sock.close()
        except Exception as e:
            print("Could not connect:", e)
            break

if __name__ == "__main__":
    main()
