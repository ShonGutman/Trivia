import socket

SERVER_PORT = 8826
SERVER_IP = '127.0.0.1'

LOGIN_CODE = 1
SIGN_UP_CODE = 2
ERROR_CODE = 99

MSG_LEN_SIZE = 4


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
    server_sock = None  # Initialize server_sock outside the try block
    try:
        # Attempt to connect to the server
        server_sock = connect_to_server()
        print("Connection successful")
    except Exception as e:
        print("Could not connect:", e)

    while True:
        try:
            message_type = input("Type 'login' or 'signup': ").lower()
            message_data = {}

            if message_type == 'login':
                # Prepare login message in JSON format
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                message_type = LOGIN_CODE
                message_data = {"username": username, "password": password}

            elif message_type == 'signup':
                # Prepare signup message in JSON format
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                mail = input("Enter your email: ")
                message_type = SIGN_UP_CODE

                message_data = {"username": username, "password": password, "mail": mail}
            else:
                message_type = ERROR_CODE

            # Add code and message length according to the format
            data = [message_type]

            len_of_data = len(message_data)
            if len_of_data <= MSG_LEN_SIZE:
                data.append(str(len_of_data).zfill(MSG_LEN_SIZE))  # Pad message length
            else:
                raise ValueError("Message length exceeds maximum allowed size")

            data.append(message_data)

            # Send message to server as string
            message = ','.join(data)
            server_sock.sendall(message.encode())

            # Receive response from server
            server_data = server_sock.recv(1024)
            print("Received from server:", server_data.decode())
        except Exception as e:
            print("Error:", e)
            server_sock.close()  # Close the connection


if __name__ == "__main__":
    main()
